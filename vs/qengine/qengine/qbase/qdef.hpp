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

#define __singleton __declspec(noinline)	//	we only want a static instance of the declared fn, not OOP instancing

#define __nothrow __declspec(nothrow)	//	explicit instruction to compiler to disable any SEH related code generation (this does happen implicitly anyways, yes)

#define __compelled_inline_noseh __forceinline __nothrow	// compell function duplication / inlining and disable windows SEH 

#define __regcall __fastcall	//	pass up to two arguments through registers(?)

#define __stackcall __cdecl		//	pass arguments on stack / no arguments contained allow caller to cleanup stack

#define _auto_type_ decltype(auto)	//	automatic type deduction for function returns

#define __optimized_ctor __compelled_inline_noseh __regcall	//	this forces compiler optimization depending on the argument list, IF the function can be inlined it will be which is arguably the least expensive calling method, however if the compiler fails yet to inline, the argument will be passed through registers if the arguments match the bitwidth of the operating system

#define __inlineable inline	//	this is a suggestion, not a command. why was it included in the language standard as a commanding word that has garaunteed effect?

#pragma endregion

#pragma region SEH Obfuscation

//  Dereference a ring -3 pointer rather than call _CxxRaiseException() directly to avoid another import table entry
//	Basic CXX exception handling callback obfuscation, call WINAPI_SEH_INIT(); at beginning of scope && WINAPI_SEH_END() or ';' at the end of the scope and it will be executed from a statically compiled SEH table entry for x86_64, or SEH handled on stack for x86
#define WINAPI_SEH_INIT() __try { static volatile int* __INVALID_REGION__ = NULL; *__INVALID_REGION__ = 0xFFFFFFFFui32; } __except (GetExceptionCode() == EXCEPTION_ACCESS_VIOLATION ? EXCEPTION_EXECUTE_HANDLER : EXCEPTION_CONTINUE_SEARCH) {

#define WINAPI_SEH_END() }

//	Allocate un un-allocatable amount of memory to force EH trigger
//	Basic CXX exception handling callback obfuscation, call CXX_EH_INIT(); at beginning of scope && CXX_EH_END() or ';' at the end of the scope and it will be executed from a statically compiled EH fn
#define CXX_EH_INIT() try { int* __INVALID_ALLOC__ = new int[(std::size_t)std::numeric_limits<std::size_t>::max]; } catch ( const std::bad_alloc& except ) { 

#define CXX_EH_END() } 

#pragma endregion 

namespace qengine {

#pragma region Constants

#define NULL 0x0

#pragma endregion


#pragma region Macros

#define RAND(_high_, _low_) rand() % _high_ + _low_ 

#pragma region Memory

#define XORWORD(_word_, _xval_) for(auto _m_ = 0; _m_ < sizeof(decltype(_xval_)); ++_m_) _word_ ^= reinterpret_cast<unsigned char*>(&_xval_)[_m_] 

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
	__compelled_inline_noseh _auto_type_ __regcall XOR_FORCE(T val, T xor_val) {

		T _return = val;

		auto val_ptr = reinterpret_cast<unsigned char*>(&_return);
		auto xor_ptr = reinterpret_cast<unsigned char*>(&xor_val);

		for (auto x = 0; x < sizeof(T); ++x)
			val_ptr[x] ^= xor_ptr[x];

		return _return;
	}


#endif

#pragma endregion

#pragma endregion
}

#endif