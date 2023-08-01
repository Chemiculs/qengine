#ifndef QHOOK_H
#define QHOOK_H

#include <iostream>
#include <vector>
#include <thread>
#include <mutex>

#include "qhook_fn.hpp"
#include "../qbase/qcallback.hpp"

namespace qengine {

	namespace qhook {

		class qhook_thread_pool {

		private:

#pragma region Singleton Globals

			static void(__fastcall* callback_)(qhook_detection_t*);

			static bool is_cancel_flag;

			static bool is_pool_initialized;

			static std::vector<qhook_fn> qhook_scan_list;

			static std::thread* qhook_scan_thread;

			static std::mutex qhook_scan_mutex;

#pragma endregion

#pragma region Global Instantiation

			inline void __cdecl initialize_globals() {

				//std::lock_guard<std::mutex> lock(qhook_scan_mutex);

				qhook_scan_thread = new std::thread(&qhook_thread_pool::do_hook_scans);

				qhook_scan_thread->detach();

				is_pool_initialized = true;
			}

#pragma endregion

#pragma region Scan Loop

			static __jmpout void __cdecl do_hook_scans() {

				while (true) {

					// scanning operation(s)
					std::this_thread::sleep_for(std::chrono::milliseconds(1));

					std::lock_guard<std::mutex> lock(qhook_scan_mutex);

					if (is_cancel_flag) // condition must be checked here or race condition
						break;

					for (auto& fn : qhook_scan_list) {

						if (!fn.function_address())
							continue;

						if (fn.has_exception_triggered()) // to avoid multiple triggers for same except
							continue;

						qhook_detection_t* fn_detect_o = nullptr;

						if (fn_detect_o = qhook_util::analyze_fn_hook_presence(reinterpret_cast<const void*>(fn.function_address()), fn.function_length(), fn.module_information(), fn.capstone_handle())) {

							// hook detected
							if (!callback_) {

								delete fn_detect_o;

								continue;
							}

							fn.has_exception_triggered(true);

							callback_(fn_detect_o);
						}
					}


				}
			}

#pragma endregion

		public:

#pragma region Helper Functions

			inline void __fastcall apply_callback_fn(void(__fastcall* fn)(qhook_detection_t*)) {

				callback_ = fn;
			}

			inline void __fastcall append_fn(void* fn_address) {

				std::lock_guard<std::mutex> lock(qhook_scan_mutex);

				if (!is_pool_initialized)
					initialize_globals();

				qhook_scan_list.push_back(
					qhook_fn{ fn_address }
				);

			}

			inline void __fastcall remove_fn(void* fn_address) {

				std::lock_guard<std::mutex> lock(qhook_scan_mutex);

				for (unsigned int i = 0; i < qhook_scan_list.size(); ++i)
					if (qhook_scan_list[i].function_address() == reinterpret_cast<uintptr_t>(fn_address))
						qhook_scan_list.erase(qhook_scan_list.begin() + i);
			}

#pragma endregion

#pragma region Instanced Ctor / Static Dtor

			inline qhook_thread_pool(void* fn = nullptr) {

				if (!fn)
					return;

				append_fn(fn);
			}

			static inline void __cdecl free_pool() {

				if (!is_pool_initialized)
					return;

				std::lock_guard<std::mutex> lock(qhook_scan_mutex);

				is_cancel_flag = true;

				if (qhook_scan_thread->joinable())
					qhook_scan_thread->join(); // wait for thread to exit

				if (qhook_scan_thread)
					delete qhook_scan_thread; // free resources
			}

#pragma endregion

		};

#pragma region Singleton Instance

		void(__fastcall* qhook_thread_pool::callback_)(qhook_detection_t*);

		bool qhook_thread_pool::is_cancel_flag = false;

		bool qhook_thread_pool::is_pool_initialized = false;

		std::vector<qhook_fn> qhook_thread_pool::qhook_scan_list;

		std::thread* qhook_thread_pool::qhook_scan_thread = nullptr;

		std::mutex qhook_thread_pool::qhook_scan_mutex;

#pragma endregion

		class qhook_t {

		private:

#pragma region Singleton Globals

			static bool is_callback_init;

			static qcallback::qmem_except_hook client_callback_fn_;

			static qhook_thread_pool hook_scan_pool_;

#pragma endregion

#pragma region Instanced Globals

			void* fn_address_;

#pragma endregion

#pragma region Low Level Exception Callback Routine

			static __jmpout void __fastcall base_exception_handler(qhook_detection_t* except) {

				if (!client_callback_fn_)
					return;

				client_callback_fn_(qexcept::q_fn_alteration { // trigger higher-level callback fn
					except->is_hook,
						except
				});
			}

#pragma endregion

		public:

#pragma region Ctor

			inline __fastcall qhook_t(void* fn) : fn_address_(fn) {

				if (!is_callback_init)
					hook_scan_pool_.apply_callback_fn(&qhook_t::base_exception_handler);

				hook_scan_pool_.append_fn(fn);
			}

#pragma endregion

#pragma region Helper Functions

			inline void __cdecl remove_from_scan_pool() {

				if (!is_callback_init)
					return;

				if (!fn_address_)
					return;

				hook_scan_pool_.remove_fn(fn_address_);
			}

			static inline void __fastcall set_client_callback_fn(qcallback::qmem_except_hook callback) {

				if (!callback)
					return;

				client_callback_fn_ = callback;
			}

			static inline void __cdecl terminate_scan_thread() {

				if (!is_callback_init) // while this singleton is not named in accordance with this usage, it is an accurate determination of whether this class has been initialized
					return;

				hook_scan_pool_.free_pool();
			}

#pragma endregion

		};

		bool qhook_t::is_callback_init = false;

		qcallback::qmem_except_hook qhook_t::client_callback_fn_ = nullptr;

		qhook_thread_pool qhook_t::hook_scan_pool_;

	}

}

#endif