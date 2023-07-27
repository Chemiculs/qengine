#ifndef QDEF_H
#define QDEF_H

#include <windows.h>

#include <tuple>
#include <string>
#include <algorithm>

#ifdef _MSC_VER
#define WINDOWS_IGNORE_PACKING_MISMATCH
#pragma warning(disable: 4700 4701 2362)
#endif


#pragma region Method Attributes

#define __jmpout __declspec(noinline)

#pragma endregion

namespace qengine {

#pragma region Constants

#define NULL 0x0

#pragma endregion

#pragma region Type Definitions

	typedef unsigned char byte, uchar;

	typedef char sbyte, schar;

	typedef short int16, int16_t;

	typedef unsigned short ushort, uint16, uint16_t;

	typedef int int32, int32_t;

	typedef unsigned int uint, uint32, uint32_t;

	typedef unsigned long ulong, ulong_t;

#ifdef _WIN64

	typedef long long int64, int64_t;

	typedef unsigned long long uint64, uint64_t;

	typedef unsigned long long uintptr_t, uintptr;

	typedef unsigned long long size_t, SIZE_T;

	typedef unsigned long long hash_t, void_t;

#elif defined(_WIN32)

	typedef unsigned int uintptr_t, uintptr;

	typedef unsigned int size_t;

	typedef unsigned int hash_t, void_t;

#endif

#pragma endregion

#pragma region Macros

#define RAND(high, low) rand() % high + low \

#pragma region Memory

#define XORWORD(word, xval) for(auto m = 0; m < sizeof(decltype(xval)); ++m) word ^= reinterpret_cast<unsigned char*>(&xval)[m] \

#define RtlZeroMemory(block, size) (memset(block, 0x00ui8, size)) \

#define UNIQUE(param_) std::unique_ptr<unsigned char[], crypto::e_malloc::free_delete_t>(reinterpret_cast<unsigned char*>(param_)) \

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