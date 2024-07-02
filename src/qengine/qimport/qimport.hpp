#pragma region Header Guard

#ifndef QIMPORT_H
#define QIMPORT_H

#pragma endregion

#pragma region Imports

#pragma region Operating System

#include <windows.h>

#pragma endregion

#pragma region std

#include <string>

#pragma endregion

#pragma region qengine

#include "../qbase/qdef.hpp"

#pragma endregion

#pragma endregion

namespace qengine {

	namespace qimport {

#pragma region Type Definitions

#ifdef _UNICODE 

		typedef std::wstring string_t;

#else

		typedef std::string string_t;

#endif

#pragma endregion


		class qimp {

		private:

			template<typename T, typename... args>
			static __inlineable T __apicall invoke_internal(std::uintptr_t fn, args... arguments) noexcept {

				return static_cast<T>(reinterpret_cast<T(WINAPI*)(args...)>(reinterpret_cast<c_void>(fn))(arguments...));
			}

		public:

			template<typename T, typename... args>
			static __inlineable T __apicall invoke(const string_t library_name, const std::string fn_str, args... arguments) noexcept {

				const auto handle = LoadLibrary(library_name.c_str());

				const auto fn = GetProcAddress(handle, fn_str.c_str());
				
				return invoke_internal<T>(reinterpret_cast<std::uintptr_t>(fn), arguments...);
			}

			template<typename T, typename... args>
			static __inlineable T __apicall invoke(const string_t library_name, const std::uint16_t ordinal_number, args... arguments) noexcept {

				const auto handle = LoadLibrary(library_name.c_str());

				const auto fn = GetProcAddress(handle, MAKEINTRESOURCEA(ordinal_number));

				return invoke_internal<T>(reinterpret_cast<std::uintptr_t>(fn), arguments...);
			}

			// this will improve performance for functions which are called repetetively throughout lifecycle

			template<typename T, typename... args>
			static __inlineable T(__apicall* get_fn_import_object(const string_t library_name, const std::string fn_str)) (args...) {

				const auto handle = LoadLibrary(library_name.c_str());

				const auto fn = GetProcAddress(handle, fn_str.c_str());

				return reinterpret_cast<T(__apicall*)(args...)>(reinterpret_cast<c_void>(fn));
			}

		};

	}
}

#endif