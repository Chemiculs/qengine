#ifndef QHOOK_FN_H
#define QHOOK_FN_H

#include <Windows.h>
#include <Psapi.h>

#include <exception>

#include "qhook_util.hpp"
#include "../qhash/qhash.hpp"

namespace qengine {

	namespace qhook {

		class qhook_fn {

		private:

#pragma region Capstone Vars

			csh cs_handle_;

#ifdef _WIN64

			const cs_mode cs_mode_ = CS_MODE_64;

#else

			const cs_mode cs_mode_ = CS_MODE_32;

#endif
			const cs_arch cs_arch_ = CS_ARCH_X86;

#pragma endregion

#pragma region Instance Globals

			bool has_exception_triggered_ = false;

			void* fn_address_;

			size_t fn_length_;

			qhash::qhash_cpu_t hash_;

			unsigned char* fn_original_state_;

#pragma endregion

#pragma region Singleton Globals

			static bool is_module_info_init_;

			static MODULEINFO module_information_;

#pragma endregion

		public:

#pragma region Get Accessors

			inline const uintptr_t __cdecl function_address() const {
				return reinterpret_cast<const uintptr_t>(fn_address_);
			}

			inline const size_t function_length() const {
				return static_cast<const size_t>(fn_length_);
			}

			inline const LPMODULEINFO module_information() const {
				return static_cast<const LPMODULEINFO>(&module_information_);
			}

			inline const csh capstone_handle() const {
				return static_cast<const csh>(cs_handle_);
			}

			inline const bool& has_exception_triggered() const {
				return has_exception_triggered_;
			}

#pragma endregion

#pragma region Set Accessors

			inline void __fastcall has_exception_triggered(bool state) {
				has_exception_triggered_ = state;
			}

#pragma endregion

#pragma region Helper Functions

			inline void __cdecl free_fn() {

				try {

					if (fn_original_state_)
						free(fn_original_state_);
				}
				catch (std::exception& except) {}
			}

			inline void __cdecl get_module_information() {


				MODULEINFO information{};

				if (!GetModuleInformation(GetCurrentProcess(), GetModuleHandle(NULL), &information, sizeof(information)))
					throw std::bad_variant_access();

				module_information_ = information;

				is_module_info_init_ = true;
			}

#pragma endregion

#pragma region Ctor / Dtor

			

			qhook_fn& operator=(const qhook_fn& other) { // original error was from rucrsive call within this function rather than actually implementing it properly
				
				this->cs_handle_ = other.cs_handle_;

				this->fn_address_ = other.fn_address_;
				
				this->fn_length_ = other.fn_length_;

				this->hash_ = other.hash_;

				this->fn_original_state_ = other.fn_original_state_;

				return *this;
			};

			inline __fastcall qhook_fn(void* fn_address) : fn_address_(fn_address) {

				if (!fn_address)
					return;

				if (cs_open(cs_arch_, cs_mode_, &cs_handle_) != CS_ERR_OK)
					throw std::bad_alloc();

				cs_option(cs_handle_, CS_OPT_DETAIL, CS_OPT_ON);

				if (!is_module_info_init_)
					get_module_information();

				fn_length_ = qhook_util::analyze_fn_length(fn_address_, cs_handle_);

				if (!fn_length_)
					return;

				auto* fn_copy_alloc = malloc(fn_length_);

				memcpy(fn_copy_alloc, fn_address_, fn_length_);

				hash_ = qhash::qhash_cpu(fn_copy_alloc, fn_length_);

				fn_original_state_ = reinterpret_cast<unsigned char*>(fn_copy_alloc);
			}



			inline __cdecl ~qhook_fn() {}

#pragma endregion

		};

		bool qhook_fn::is_module_info_init_ = false;

		MODULEINFO qhook_fn::module_information_{};

		
	}
}

#endif