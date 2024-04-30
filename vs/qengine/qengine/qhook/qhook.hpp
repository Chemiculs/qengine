#pragma region Header Guard

#ifndef QHOOK_H
#define QHOOK_H

#pragma endregion

#pragma region Imports

#pragma region std

#include <iostream>
#include <vector>
#include <thread>
#include <mutex>

#pragma endregion

#pragma region qengine

#include "qhook_fn.hpp"
#include "../qbase/qcallback.hpp"

#pragma endregion

#pragma endregion

namespace qengine {

	namespace qhook {

		class qhook_thread_pool {

		private:

#pragma region Singleton Globals

			static void(__regcall __singleton * callback_)(qhook_detection_t*);

			static bool is_cancel_flag;

			static bool is_pool_initialized;

			static std::vector<qhook_fn> qhook_scan_list;

			static std::thread* qhook_scan_thread;

			static std::mutex qhook_scan_mutex;

#pragma endregion

#pragma region Global Instantiation

			__inlineable void __stackcall initialize_globals() noexcept {

				qhook_scan_thread = new std::thread(&qhook_thread_pool::do_hook_scans);

				qhook_scan_thread->detach();

				is_pool_initialized = true;
			}

#pragma endregion

#pragma region Scan Loop

			static __singleton void __stackcall do_hook_scans() noexcept {

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

								try {
									delete fn_detect_o;
								}
								catch (const std::exception& except) {
									throw except;
								}

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

			__inlineable void __regcall apply_callback_fn( void(__regcall* fn)(qhook_detection_t*) ) noexcept {

				callback_ = fn;
			}

			__inlineable void __regcall append_fn(void* fn_address) {

				std::lock_guard<std::mutex> lock(qhook_scan_mutex);
				
				if (!is_pool_initialized)
					initialize_globals();

				qhook_scan_list.push_back(
					qhook_fn{ fn_address }
				);
				
			}

			__inlineable void __regcall remove_fn(const void* fn_address) noexcept {

				std::lock_guard<std::mutex> lock(qhook_scan_mutex);

				for (unsigned int i = 0; i < qhook_scan_list.size(); ++i)
					if (qhook_scan_list[i].function_address() == reinterpret_cast<uintptr_t>(fn_address))
						qhook_scan_list.erase( qhook_scan_list.begin() +  i );
			}

#pragma endregion

#pragma region Instanced Ctor / Static Dtor

			__optimized_ctor qhook_thread_pool(void* fn = nullptr) noexcept {

				if (!fn)
					return;

				append_fn(fn);
			}

			static __inlineable void __stackcall free_pool() noexcept {
				
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

#pragma region Static Declarators

		void(__regcall* qhook_thread_pool::callback_)(qhook_detection_t*);

		bool qhook_thread_pool::is_cancel_flag = false;

		bool qhook_thread_pool::is_pool_initialized = false;

		std::vector<qhook_fn> qhook_thread_pool::qhook_scan_list;

		std::thread* qhook_thread_pool::qhook_scan_thread = nullptr;

		std::mutex qhook_thread_pool::qhook_scan_mutex;

#pragma endregion

		class qhook_t {

		private:

#pragma region Singleton Globals

			static volatile bool is_callback_init;

			static qcallback::qmem_except_hook client_callback_fn_;

			static qhook_thread_pool hook_scan_pool_;

#pragma endregion

#pragma region Instanced Globals

			void* fn_address_;

#pragma endregion

#pragma region Low Level Exception Callback Routine

			static __singleton void __regcall base_exception_handler(qhook_detection_t* except) noexcept {

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

			__optimized_ctor qhook_t(void* fn) : fn_address_(fn) {
				
				if (!is_callback_init)
					hook_scan_pool_.apply_callback_fn(&qhook_t::base_exception_handler);

				hook_scan_pool_.append_fn(fn);
			}

#pragma endregion

#pragma region Helper Functions

			__inlineable void __stackcall remove_from_scan_pool() noexcept {

				if (!is_callback_init)
					return;

				if (!fn_address_)
					return;

				hook_scan_pool_.remove_fn(fn_address_);
			}

			static __inlineable void __regcall set_client_callback_fn(qcallback::qmem_except_hook callback) noexcept {

				if (!callback)
					return;

				client_callback_fn_ = callback;
			}

			static __inlineable void __stackcall terminate_scan_thread() noexcept {

				if (!is_callback_init) // while this singleton is not named in accordance with this usage, it is an accurate determination of whether this class has been initialized
					return;

				hook_scan_pool_.free_pool();
			}

#pragma endregion

		};

#pragma region Static Declarators

		volatile bool qhook_t::is_callback_init = false;

		qcallback::qmem_except_hook qhook_t::client_callback_fn_ = nullptr;

		qhook_thread_pool qhook_t::hook_scan_pool_;

#pragma endregion

	}

}

#endif