#pragma region Header Guard

#ifndef QHOOK_FN_H
#define QHOOK_FN_H

#pragma endregion

#pragma region Imports

#pragma region Operating System

#include <Windows.h>
#include <Psapi.h>

#pragma endregion

#pragma region std

#include <exception>

#pragma endregion

#pragma region qengine

#include "qhook_util.hpp"
#include "../qhash/qhash.hpp"

#pragma endregion

#pragma endregion

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

			std::size_t fn_length_;

			qhash::qhash_cpu_t hash_;

			std::uint8_t* fn_original_state_;

#pragma endregion

#pragma region Singleton Globals

			static bool is_module_info_init_;

			static MODULEINFO module_information_;

#pragma endregion

		public:

#pragma region Get Accessors

			inline const uintptr_t __stackcall function_address() const noexcept {
				return reinterpret_cast<const uintptr_t>(fn_address_);
			}

			inline const size_t function_length() const noexcept {
				return static_cast<const size_t>(fn_length_);
			}

			inline const LPMODULEINFO module_information() const noexcept {
				return static_cast<const LPMODULEINFO>(&module_information_);
			}

			inline const csh capstone_handle() const noexcept {
				return static_cast<const csh>(cs_handle_);
			}

			inline const bool& has_exception_triggered() const noexcept {
				return has_exception_triggered_;
			}

#pragma endregion

#pragma region Set Accessors

			inline void __regcall has_exception_triggered(bool state) noexcept {
				has_exception_triggered_ = state;
			}

#pragma endregion

#pragma region Helper Functions

			inline void __stackcall free_fn() {

				try {

					if (fn_original_state_)
						free(fn_original_state_);
				}
				catch (std::exception& except) { throw except; } // allow caller to handle exception
			}

			inline void __stackcall get_module_information() {


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

			inline __regcall qhook_fn(const void* fn_address) 

					: fn_address_(const_cast<void*>(fn_address)
				) {

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

				if (!fn_copy_alloc)
					throw std::bad_alloc();

				memcpy(fn_copy_alloc, fn_address_, fn_length_);

				hash_ = qhash::qhash_cpu(fn_copy_alloc, fn_length_);

				fn_original_state_ = reinterpret_cast<std::uint8_t*>(fn_copy_alloc);
			}



			inline __stackcall ~qhook_fn() {}

#pragma endregion

		};

#pragma region Static Declarators

		bool qhook_fn::is_module_info_init_ = false;

		MODULEINFO qhook_fn::module_information_{};

#pragma endregion

		
	}
}

#endif