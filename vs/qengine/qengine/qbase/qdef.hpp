#pragma region Header Guard

#ifndef QDEF_H
#define QDEF_H

#pragma endregion

#pragma region Imports

#pragma region Operating System

#include <windows.h>

#pragma endregion

#pragma region std

#include <tuple>
#include <string>
#include <algorithm>
#include <cstdint>

#pragma endregion

#pragma endregion


#pragma region Preprocessor

#ifdef _MSC_VER
#define WINDOWS_IGNORE_PACKING_MISMATCH
#pragma warning(disable: 4700 4701 2362)
#endif

#pragma endregion

#pragma region Method Attributes

#define __statcall __declspec(noinline)

#pragma endregion

#pragma region SEH Obfuscation

//  Dereference a null pointer rather than call _CxxRaiseException() directly to avoid another import table entry
//	Basic CXX exception handling callback obfuscation, call WINAPI_SEH_INIT(); at beginning of scope && WINAPI_SEH_END() or ';' at the end of the scope and it will be executed from a statically compiled SEH table entry for x86_64, or SEH handled on stack for x86
#define WINAPI_SEH_INIT() __try { static volatile int* __INVALID_REGION__ = NULL; *__INVALID_REGION__ = 0xFFFFFFFFui32; } __except (GetExceptionCode() == EXCEPTION_ACCESS_VIOLATION ? EXCEPTION_EXECUTE_HANDLER : EXCEPTION_CONTINUE_SEARCH) {

#define WINAPI_SEH_END() }

//	Basic CXX exception handling callback obfuscation, call CXX_EH_INIT(); at beginning of scope && CXX_EH_END() or ';' at the end of the scope and it will be executed from a statically compiled EH fn
#define CXX_EH_INIT() try { int* __INVALID_ALLOC__ = new int[(std::size_t)std::numeric_limits<std::size_t>::max]; } catch ( const std::bad_alloc& except ) { 

#define CXX_EH_END() } 

#pragma endregion 

namespace qengine {

#pragma region Constants

#define NULL 0x0

#pragma endregion


#pragma region Macros

#define RAND(high, low) rand() % high + low \

#pragma region Memory

#define XORWORD(word, xval) for(auto m = 0; m < sizeof(decltype(xval)); ++m) word ^= reinterpret_cast<unsigned char*>(&xval)[m] \

#pragma endregion


#pragma endregion


#pragma region Xor Operations Floating Point

	// workaround for lack of support for bitwise operations on floating-point types by the C++ standard library
	// ensure the type of both arguments is the same. you must declare the argument before passing it, or use  a typecast or the apropriate declaration suffix (e.g 255ULL to declare an unsigned long long with a value of 255 so it won't default to int / short)
#ifdef __clang__

#define XOR_FORCE(val, xor_val) \
    ({ \
        auto _return = (val); \
        auto xor_val_c = (xor_val); \
        auto val_ptr = reinterpret_cast<unsigned char*>(const_cast<decltype(_return)*>(&(_return))); \
        auto xor_ptr = reinterpret_cast<unsigned char*>(const_cast<decltype(xor_val_c)*>(&(xor_val_c))); \
        for(auto x = 0; x < sizeof(decltype(_return)); ++x){ \
            val_ptr[x] ^= xor_ptr[x]; \
        } \
        _return;\
    })

#elif defined (_MSC_VER)

	template<typename T>
	__forceinline decltype(auto) XOR_FORCE(T val, T xor_val) {
		T _return = val;
		auto val_ptr = reinterpret_cast<unsigned char*>(&_return);
		auto xor_ptr = reinterpret_cast<unsigned char*>(&xor_val);
		for (auto x = 0; x < sizeof(T); ++x) {
			val_ptr[x] ^= xor_ptr[x];
		}
		return _return;
	}

#endif

#pragma endregion

#pragma endregion
}

#endif