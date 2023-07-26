#ifndef QIMPORT_H
#define QIMPORT_H

#include <windows.h>

#include <vector>
#include <string>
#include <tuple>

#include "../engine/polytypes/qenc_t.hpp"

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
			static inline T WINAPI invoke_internal(uintptr_t fn, const args... arguments) {

				return static_cast<T>(reinterpret_cast<T(WINAPI*)(args...)>(reinterpret_cast<void*>(fn))(arguments...));
			}

		public:

			template<typename T, typename... args>
			static inline T WINAPI invoke(string_t library_name, std::string fn_str, const args... arguments) {

				auto handle = LoadLibrary(library_name.c_str());

				auto fn = GetProcAddress(handle, qenc_t::e_string(fn_str.c_str()).get().c_str());
				
				return invoke_internal<T>(reinterpret_cast<uintptr_t>(fn), arguments...);
			}

			template<typename T, typename... args>
			static inline T WINAPI invoke(string_t library_name, WORD ordinal_number, const args... arguments) {
				auto handle = LoadLibrary(library_name.c_str());

				auto fn = GetProcAddress(handle, qenc_t::e_string(MAKEINTRESOURCEA(ordinal_number)).get().c_str());

				return invoke_internal<T>(reinterpret_cast<uintptr_t>(fn), arguments...);
			}

		};

	}
}

#endif