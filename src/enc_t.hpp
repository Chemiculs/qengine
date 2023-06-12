#ifndef ENC_T_H
#define ENC_T_H

#pragma region Imports

#include <chrono>
#include <string>
#include <vector>
#include <memory>
#include <cstdlib>
#include <exception>

#pragma endregion

#pragma region Preprocessor 

#pragma region SSE / AVX

#ifdef __AVX__
// fix for an msvc bug where __SSE__ preprocessor refuses to list as active when it should be as avx indicates this features presence as well

#ifndef __SSE__

#define __SSE__

#endif

#ifndef __SSE2__

#define __SSE2__

#endif

#endif

#ifdef __SSE__

#ifdef __clang__

#include <emmintrin.h>

#elif defined(_MSC_VER)

#include <xmmintrin.h> 

#endif

#endif

#ifdef __AVX__

#ifdef __clang__

#include <avxintrin.h>

#elif defined(_MSC_VER)

#include <immintrin.h> 

#endif

#endif

#pragma endregion

#pragma endregion


namespace crypto {

#pragma region Constants

#define NULL 0x0

#pragma endregion

#pragma region Type Definitions

    typedef unsigned char uint8_t;
    typedef unsigned short uint16_t;
    typedef unsigned int uint32_t;

#ifdef _WIN64

    typedef unsigned long long uint64_t;

#endif

    typedef char int8_t;
    typedef short int16_t;
    typedef int int32_t;

#ifdef _WIN64

    typedef long long int64_t;

#endif

#ifdef _WIN64

    typedef unsigned long long uintptr_t;
    typedef unsigned long long size_t;

#elif _WIN32

    typedef unsigned int uintptr_t;
    typedef unsigned int size_t;

#endif

#pragma endregion

#pragma region Globals  =|=  Singleton

    extern unsigned long long seed;
    extern bool is_init;

#pragma endregion

#pragma region Macros

#pragma region Memory

#define RtlZeroMemory(block, size) (memset(block, 0x00ui8, size)) \

#define UNIQUE(param_) std::unique_ptr<unsigned char[], crypto::e_malloc::free_delete_t>(reinterpret_cast<unsigned char*>(param_)) \

#pragma endregion

#pragma region Encryption

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

// macro for raw / pool allocations arg1: pointer to allocation, arg2: length of allocation in bytes, arg3: encryption key as type reference( in our case unsigned long long / uint64_t)
#define XOR_RAW(val, len, xor_val) \
    ({ \
        auto _return = calloc(len, sizeof(unsigned char)); \
        memcpy(_return, val, len); \
        auto val_ptr = reinterpret_cast<unsigned char*>(_return); \
        auto xor_ptr = reinterpret_cast<unsigned char*>(&(xor_val)); \
        for (auto x = 0; x < len; ++x) { \
            for(auto y = 0; y < sizeof(decltype(xor_val)); ++y){ \
                val_ptr[x % sizeof(decltype(val))] ^= xor_ptr[y % sizeof(decltype(xor_val))]; \
            } \
            for(auto z = (sizeof(decltype(xor_val)) - 1); z > -1; --z){ \
                val_ptr[x % sizeof(decltype(val))] ^= xor_ptr[z % sizeof(decltype(xor_val))]; \
            } \
        } \
        reinterpret_cast<decltype(val)>(_return); \
    })

// macro for all native non-string datatypes (almost)
#define XOR_T(val, xor_val) \
    ({ \
        auto _return = (val); \
        auto val_ptr = reinterpret_cast<unsigned char*>(&(_return)); \
        auto xor_ptr = reinterpret_cast<unsigned char*>(&(xor_val)); \
        for (auto x = 0; x < sizeof(decltype(_return)); ++x) { \
            for(auto y = 0; y < sizeof(decltype(xor_val)); ++y){ \
                 val_ptr[x % sizeof(decltype(val))] ^= xor_ptr[y % sizeof(decltype(xor_val))]; \
            } \
            for(auto z = (sizeof(decltype(xor_val)) - 1); z > -1; --z){ \
                val_ptr[x % sizeof(decltype(val))] ^= xor_ptr[z % sizeof(decltype(xor_val))]; \
            } \
        } \
        _return; \
    })

// macro for ANSI charset string
#define XOR_STR_T(val, xor_val) \
    ({ \
        auto _return = (val); \
        auto val_ptr = reinterpret_cast<unsigned char*>(const_cast<char*>(_return.data())); \
        auto xor_ptr = reinterpret_cast<unsigned char*>(&(xor_val)); \
        for (auto x = 0; x < ((val.length() * sizeof(char)) + sizeof(char)); ++x) { \
            for(auto y = 0; y < sizeof(decltype(xor_val)) ; ++y){ \
                 val_ptr[x % ((val.length() * sizeof(char)) + sizeof(char))] ^= xor_ptr[y % sizeof(decltype(xor_val))]; \
            } \
            for(auto z = (sizeof(decltype(xor_val)) - 1); z > -1; --z){ \
                val_ptr[x % ((val.length() * sizeof(char)) + sizeof(char))] ^= xor_ptr[z % sizeof(decltype(xor_val))]; \
            } \
        } \
        _return; \
    })

//macro for unicode charset string
#define XOR_WSTR_T(val, xor_val) \
    ({ \
        auto _return = (val); \
        auto val_ptr = reinterpret_cast<unsigned char*>(const_cast<wchar_t*>(_return.data())); \
        auto xor_ptr = reinterpret_cast<unsigned char*>(&(xor_val)); \
        for (auto x = 0; x < ((val.length() * sizeof(wchar_t)) + sizeof(wchar_t)); ++x) { \
            for(auto y = 0; y < sizeof(decltype(xor_val)) ; ++y){ \
                 val_ptr[x % ((val.length() * sizeof(wchar_t)) + sizeof(wchar_t))] ^= xor_ptr[y % sizeof(decltype(xor_val))]; \
            } \
            for(auto z = (sizeof(decltype(xor_val)) - 1); z > -1; --z){ \
                val_ptr[x % ((val.length() * sizeof(wchar_t)) + sizeof(wchar_t))] ^= xor_ptr[z % sizeof(decltype(xor_val))]; \
            } \
        } \
        _return; \
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


    template<typename T>
    __forceinline decltype(auto) XOR_RAW(T* val, size_t len, uintptr_t xor_val) {
        auto _return = static_cast<T*>(malloc(len));
        memcpy(_return, val, len);
        auto val_ptr = reinterpret_cast<unsigned char*>(_return);
        auto xor_ptr = reinterpret_cast<unsigned char*>(&xor_val);
        for (auto x = 0; x < len; ++x) {
            for (auto y = 0; y < sizeof(decltype(xor_val)); ++y) {
                val_ptr[x % sizeof(decltype(val))] ^= xor_ptr[y % sizeof(decltype(xor_val))];
            }
            for (auto z = sizeof(decltype(xor_val)) - 1; z > -1; --z) {
                val_ptr[x % sizeof(decltype(val))] ^= xor_ptr[z % sizeof(decltype(xor_val))];
            }
        }
        return reinterpret_cast<decltype(val)>(_return);
    }


    template<typename T>
    __forceinline T XOR_T(T val, uintptr_t xor_val) {
        auto _return = val;
        auto val_ptr = reinterpret_cast<unsigned char*>(&_return);
        auto xor_ptr = reinterpret_cast<unsigned char*>(&xor_val);
        for (auto x = 0; x < sizeof(decltype(_return)); ++x) {
            for (auto y = 0; y < sizeof(xor_val); ++y) {
                val_ptr[x % sizeof(decltype(val))] ^= xor_ptr[y % sizeof(decltype(xor_val))];
            }
            for (auto z = (sizeof(decltype(xor_val)) - 1); z > -1; --z) {
                val_ptr[x % sizeof(decltype(val))] ^= xor_ptr[z % sizeof(decltype(xor_val))];
            }
        }
        return _return;
    }


    template<typename T>
    __forceinline decltype(auto) XOR_STR_T(T val, uintptr_t xor_val) {
        T _return = val;
        auto val_ptr = reinterpret_cast<unsigned char*>(const_cast<char*>(_return.data()));
        auto xor_ptr = reinterpret_cast<unsigned char*>(&xor_val);
        for (auto x = 0; x < ((val.length() * sizeof(typename T::value_type)) + sizeof(typename T::value_type)); ++x) {
            for (auto y = 0; y < sizeof(decltype(xor_val)); ++y) {
                val_ptr[x % ((val.length() * sizeof(typename T::value_type)) + sizeof(typename T::value_type))] ^= xor_ptr[y % sizeof(decltype(xor_val))];
            }
            for (auto z = (sizeof(decltype(xor_val)) - 1); z > -1; --z) {
                val_ptr[x % ((val.length() * sizeof(typename T::value_type)) + sizeof(typename T::value_type))] ^= xor_ptr[z % sizeof(decltype(xor_val))];
            }
        }
        return _return;
    }


    template<typename T>
    __forceinline decltype(auto) XOR_WSTR_T(T val, uintptr_t xor_val) {
        T _return = val;
        auto val_ptr = reinterpret_cast<unsigned char*>(const_cast<typename T::value_type*>(_return.data()));
        auto xor_ptr = reinterpret_cast<unsigned char*>(&xor_val);
        for (int x = 0; x < ((val.length() * sizeof(typename T::value_type)) + sizeof(typename T::value_type)); ++x) {
            for (int y = 0; y < sizeof(decltype(xor_val)); ++y) {
                val_ptr[x % ((val.length() * sizeof(typename T::value_type)) + sizeof(typename T::value_type))] ^= xor_ptr[y % sizeof(decltype(xor_val))];
            }
            for (int z = (sizeof(decltype(xor_val)) - 1); z > -1; --z) {
                val_ptr[x % ((val.length() * sizeof(typename T::value_type)) + sizeof(typename T::value_type))] ^= xor_ptr[z % sizeof(decltype(xor_val))];
            }
        }
        return _return;
    }


#endif

#pragma endregion

#pragma endregion

#pragma region Static Methods

    // this must be called once at application startup / or when you wish to begin using any type included in this header
    static void __fastcall init_constants() {
        if (!is_init) {
            auto time_n = std::chrono::high_resolution_clock::now();
            seed = static_cast<unsigned long long>(time_n.time_since_epoch().count());

            is_init = true;
        }
    }

#pragma endregion

#pragma region Types

#pragma region WORD

#pragma region 8-bit

    class e_int8 {

    private:

#pragma region Encrypted value

        char _value;

#pragma endregion

    public:

#pragma region CTOR

        __forceinline __fastcall e_int8(char value) {
            _value = XOR_T(value, crypto::seed);
        }

#pragma endregion

#pragma region Accessors

        __forceinline char __fastcall get() const {
            return XOR_T(_value, crypto::seed);
        }

        __forceinline void __fastcall set(char value) {
            _value = XOR_T(value, crypto::seed);
        }

#pragma endregion

#pragma region Operators

        __forceinline e_int8 __fastcall operator+(const char value) const {
            return e_int8(XOR_T(_value, crypto::seed) + value);
        };

        __forceinline e_int8 __fastcall operator-(const char value) const {
            return e_int8(XOR_T(_value, crypto::seed) - value);
        }

        __forceinline e_int8 __fastcall operator/(const char value) const {
            return e_int8(XOR_T(_value, crypto::seed) / value);
        }

        __forceinline e_int8 __fastcall operator*(const char value) const {
            return e_int8(XOR_T(_value, crypto::seed) * value);
        }

        __forceinline e_int8 __fastcall operator&(const char value) const {
            return e_int8(XOR_T(_value, crypto::seed) & value);
        }

        __forceinline e_int8 __fastcall operator|(const char value) const {
            return e_int8(XOR_T(_value, crypto::seed) | value);
        }

        __forceinline e_int8 __fastcall operator%(const char value) const {
            return e_int8(XOR_T(_value, crypto::seed) % value);
        }

        __forceinline e_int8 __fastcall operator^(const char value) const {
            return e_int8(XOR_T(_value, crypto::seed) ^ value);
        }

        __forceinline e_int8 __fastcall operator<<(const char value) const {
            return e_int8(XOR_T(_value, crypto::seed) << value);
        }

        __forceinline e_int8 __fastcall operator>>(const char value) const {
            return e_int8(XOR_T(_value, crypto::seed) >> value);
        }

        __forceinline e_int8& __fastcall operator+=(const char value) {
            this->_value = XOR_T(XOR_T(_value, crypto::seed) + value, crypto::seed);
            return *this;
        }

        __forceinline e_int8& __fastcall operator-=(const char value) {
            _value = XOR_T(XOR_T(_value, crypto::seed) - value, crypto::seed);
            return *this;
        }

        __forceinline e_int8& __fastcall operator*=(const char value) {
            _value = XOR_T(XOR_T(_value, crypto::seed) * value, crypto::seed);
            return *this;
        }

        __forceinline e_int8& __fastcall operator/=(const char value) {
            _value = XOR_T(XOR_T(_value, crypto::seed) / value, crypto::seed);
            return *this;
        }

        __forceinline e_int8& __fastcall operator%=(const char value) {
            _value = XOR_T(XOR_T(_value, crypto::seed) % value, crypto::seed);
            return *this;
        }

        __forceinline e_int8& __fastcall operator^=(const char value) {
            _value = XOR_T(XOR_T(_value, crypto::seed) ^ value, crypto::seed);
            return *this;
        }

        __forceinline e_int8& __fastcall operator&=(const char value) {
            _value = XOR_T(XOR_T(_value, crypto::seed) & value, crypto::seed);
            return *this;
        }

        __forceinline e_int8& __fastcall operator|=(const char value) {
            _value = XOR_T(XOR_T(_value, crypto::seed) | value, crypto::seed);
            return *this;
        }

        __forceinline e_int8& __fastcall operator<<=(const char value) {
            _value = XOR_T(XOR_T(_value, crypto::seed) << value, crypto::seed);
            return *this;
        }

        __forceinline e_int8& __fastcall operator>>=(const char value) {
            _value = XOR_T(XOR_T(_value, crypto::seed) >> value, crypto::seed);
            return *this;
        }

        __forceinline e_int8& __fastcall operator=(const char value) {
            _value = XOR_T(value, crypto::seed);
            return *this;
        }

        __forceinline __fastcall operator char() const {
            return XOR_T(_value, crypto::seed);
        }

#pragma endregion
    };

    class e_uint8 {
    private:

#pragma region Encrypted value
        unsigned char _value;
#pragma endregion

    public:

#pragma region CTOR
        __forceinline  __fastcall e_uint8(unsigned char value) {
            _value = XOR_T(value, crypto::seed);
        }
#pragma endregion

#pragma region Accessors
        __forceinline unsigned char __fastcall get() const {
            return XOR_T(_value, crypto::seed);
        }
        __forceinline void __fastcall set(unsigned char value) {
            _value = XOR_T(value, crypto::seed);
        }
#pragma endregion

#pragma region Operators

        __forceinline e_uint8 __fastcall operator+(const unsigned char value) const {
            return e_uint8(XOR_T(_value, crypto::seed) + value);
        };

        __forceinline e_uint8 __fastcall operator-(const unsigned char value) const {
            return e_uint8(XOR_T(_value, crypto::seed) - value);
        }

        __forceinline e_uint8 __fastcall operator/(const unsigned char value) const {
            return e_uint8(XOR_T(_value, crypto::seed) / value);
        }

        __forceinline e_uint8 __fastcall operator*(const unsigned char value) const {
            return e_uint8(XOR_T(_value, crypto::seed) * value);
        }

        __forceinline e_uint8 __fastcall operator&(const unsigned char value) const {
            return e_uint8(XOR_T(_value, crypto::seed) & value);
        }

        __forceinline e_uint8 __fastcall operator|(const unsigned char value) const {
            return e_uint8(XOR_T(_value, crypto::seed) | value);
        }

        __forceinline e_uint8 __fastcall operator%(const unsigned char value) const {
            return e_uint8(XOR_T(_value, crypto::seed) % value);
        }

        __forceinline e_uint8 __fastcall operator^(const unsigned char value) const {
            return e_uint8(XOR_T(_value, crypto::seed) ^ value);
        }

        __forceinline e_uint8 __fastcall operator<<(const char value) const {
            return e_uint8(XOR_T(_value, crypto::seed) << value);
        }

        __forceinline e_uint8 __fastcall operator>>(const char value) const {
            return e_uint8(XOR_T(_value, crypto::seed) >> value);
        }

        __forceinline e_uint8& __fastcall operator+=(const unsigned char value) {
            _value = XOR_T(XOR_T(_value, crypto::seed) + value, crypto::seed);
            return *this;
        }

        __forceinline e_uint8& __fastcall operator-=(const unsigned char value) {
            _value = XOR_T(XOR_T(_value, crypto::seed) - value, crypto::seed);
            return *this;
        }

        __forceinline e_uint8& __fastcall operator*=(const unsigned char value) {
            _value = XOR_T(XOR_T(_value, crypto::seed) * value, crypto::seed);
            return *this;
        }

        __forceinline e_uint8& __fastcall operator/=(const unsigned char value) {
            _value = XOR_T(XOR_T(_value, crypto::seed) / value, crypto::seed);
            return *this;
        }

        __forceinline e_uint8& __fastcall operator%=(const unsigned char value) {
            _value = XOR_T(XOR_T(_value, crypto::seed) % value, crypto::seed);
            return *this;
        }

        __forceinline e_uint8& __fastcall operator^=(const unsigned char value) {
            _value = XOR_T(XOR_T(_value, crypto::seed) ^ value, crypto::seed);
            return *this;
        }

        __forceinline e_uint8& __fastcall operator&=(const unsigned char value) {
            _value = XOR_T(XOR_T(_value, crypto::seed) & value, crypto::seed);
            return *this;
        }

        __forceinline e_uint8& __fastcall operator|=(const unsigned char value) {
            _value = XOR_T(XOR_T(_value, crypto::seed) | value, crypto::seed);
            return *this;
        }

        __forceinline e_uint8& __fastcall operator<<=(const unsigned char value) {
            _value = XOR_T(XOR_T(_value, crypto::seed) << value, crypto::seed);
            return *this;
        }

        __forceinline e_uint8& __fastcall operator>>=(const unsigned char value) {
            _value = XOR_T(XOR_T(_value, crypto::seed) >> value, crypto::seed);
            return *this;
        }

        __forceinline e_uint8& __fastcall operator=(const unsigned char value) {
            _value = XOR_T(value, crypto::seed);
            return *this;
        }

        __forceinline __fastcall operator unsigned char() const {
            return XOR_T(_value, crypto::seed);
        }

#pragma endregion
    };

#pragma endregion

#pragma region 16-bit

    class e_int16 {

    private:

        short _value;

    public:

#pragma region CTOR

        __forceinline __fastcall e_int16(short value) {
            _value = XOR_T(value, crypto::seed);
        }

#pragma endregion

#pragma region Accessors

        __forceinline short __fastcall get() const {
            return XOR_T(_value, crypto::seed);
        }

        __forceinline void __fastcall set(short value) {
            _value = XOR_T(value, crypto::seed);
        }

#pragma endregion

#pragma region Operators

        __forceinline e_int16 __fastcall operator+(const short value) const {
            return e_int16(XOR_T(_value, crypto::seed) + value);
        };

        __forceinline e_int16 __fastcall operator-(const short value) const {
            return e_int16(XOR_T(_value, crypto::seed) - value);
        }

        __forceinline e_int16 __fastcall operator/(const short value) const {
            return e_int16(XOR_T(_value, crypto::seed) / value);
        }

        __forceinline e_int16 __fastcall operator*(const short value) const {
            return e_int16(XOR_T(_value, crypto::seed) * value);
        }

        __forceinline e_int16 __fastcall operator&(const short value) const {
            return e_int16(XOR_T(_value, crypto::seed) & value);
        }

        __forceinline e_int16 __fastcall operator|(const short value) const {
            return e_int16(XOR_T(_value, crypto::seed) | value);
        }

        __forceinline e_int16 __fastcall operator%(const short value) const {
            return e_int16(XOR_T(_value, crypto::seed) % value);
        }

        __forceinline e_int16 __fastcall operator^(const short value) const {
            return e_int16(XOR_T(_value, crypto::seed) ^ value);
        }

        __forceinline e_int16 __fastcall operator<<(const short value) const {
            return e_int16(XOR_T(_value, crypto::seed) << value);
        }

        __forceinline e_int16 __fastcall operator>>(const short value) const {
            return e_int16(XOR_T(_value, crypto::seed) >> value);
        }

        __forceinline e_int16& __fastcall operator+=(const short value) {
            _value = XOR_T(XOR_T(_value, crypto::seed) + value, crypto::seed);
            return *this;
        }

        __forceinline e_int16& __fastcall operator-=(const short value) {
            _value = XOR_T(XOR_T(_value, crypto::seed) - value, crypto::seed);
            return *this;
        }

        __forceinline e_int16& __fastcall operator*=(const short value) {
            _value = XOR_T(XOR_T(_value, crypto::seed) * value, crypto::seed);
            return *this;
        }

        __forceinline e_int16& __fastcall operator/=(const short value) {
            _value = XOR_T(XOR_T(_value, crypto::seed) / value, crypto::seed);
            return *this;
        }

        __forceinline e_int16& __fastcall operator%=(const short value) {
            _value = XOR_T(XOR_T(_value, crypto::seed) % value, crypto::seed);
            return *this;
        }

        __forceinline e_int16& __fastcall operator^=(const short value) {
            _value = XOR_T(XOR_T(_value, crypto::seed) ^ value, crypto::seed);
            return *this;
        }

        __forceinline e_int16& __fastcall operator&=(const short value) {
            _value = XOR_T(XOR_T(_value, crypto::seed) & value, crypto::seed);
            return *this;
        }

        __forceinline e_int16& __fastcall operator|=(const short value) {
            _value = XOR_T(XOR_T(_value, crypto::seed) | value, crypto::seed);
            return *this;
        }

        __forceinline e_int16& __fastcall operator=(const short value) {
            _value = XOR_T(value, crypto::seed);
            return *this;
        }

        __forceinline e_int16& __fastcall operator<<=(const short value) {
            _value = XOR_T(XOR_T(_value, crypto::seed) << value, crypto::seed);
            return *this;
        }

        __forceinline e_int16& __fastcall operator>>=(const short value) {
            _value = XOR_T(XOR_T(_value, crypto::seed) >> value, crypto::seed);
            return *this;
        }

        __forceinline __fastcall operator short() const {
            return XOR_T(_value, crypto::seed);
        }

#pragma endregion
    };

    class e_uint16 {
    private:
        unsigned short _value;
    public:

#pragma region CTOR
        __forceinline __fastcall e_uint16(unsigned short value) {
            _value = XOR_T(value, crypto::seed);
        }
#pragma endregion

#pragma region Accessors
        __forceinline unsigned short __fastcall get() const {
            return XOR_T(_value, crypto::seed);
        }
        __forceinline void __fastcall set(unsigned short value) {
            _value = XOR_T(value, crypto::seed);
        }
#pragma endregion

#pragma region Operators

        __forceinline e_uint16 __fastcall operator+(const unsigned short value) const {
            return e_uint16(XOR_T(_value, crypto::seed) + value);
        };

        __forceinline e_uint16 __fastcall operator-(const unsigned short value) const {
            return e_uint16(XOR_T(_value, crypto::seed) - value);
        }

        __forceinline e_uint16 __fastcall operator/(const unsigned short value) const {
            return e_uint16(XOR_T(_value, crypto::seed) / value);
        }

        __forceinline e_uint16 __fastcall operator*(const unsigned short value) const {
            return e_uint16(XOR_T(_value, crypto::seed) * value);
        }

        __forceinline e_uint16 __fastcall operator&(const unsigned short value) const {
            return e_uint16(XOR_T(_value, crypto::seed) & value);
        }

        __forceinline e_uint16 __fastcall operator|(const unsigned short value) const {
            return e_uint16(XOR_T(_value, crypto::seed) | value);
        }

        __forceinline e_uint16 __fastcall operator%(const unsigned short value) const {
            return e_uint16(XOR_T(_value, crypto::seed) % value);
        }

        __forceinline e_uint16 __fastcall operator^(const unsigned short value) const {
            return e_uint16(XOR_T(_value, crypto::seed) ^ value);
        }

        __forceinline e_uint16 __fastcall operator<<(const unsigned short value) const {
            return e_uint16(XOR_T(_value, crypto::seed) << value);
        }

        __forceinline e_uint16 __fastcall operator>>(const unsigned short value) const {
            return e_uint16(XOR_T(_value, crypto::seed) >> value);
        }

        __forceinline e_uint16& __fastcall operator+=(const unsigned short value) {
            _value = XOR_T(XOR_T(_value, crypto::seed) + value, crypto::seed);
            return *this;
        }

        __forceinline e_uint16& __fastcall operator-=(const unsigned short value) {
            _value = XOR_T(XOR_T(_value, crypto::seed) - value, crypto::seed);
            return *this;
        }

        __forceinline e_uint16& __fastcall operator*=(const unsigned short value) {
            _value = XOR_T(XOR_T(_value, crypto::seed) * value, crypto::seed);
            return *this;
        }

        __forceinline e_uint16& __fastcall operator/=(const unsigned short value) {
            _value = XOR_T(XOR_T(_value, crypto::seed) / value, crypto::seed);
            return *this;
        }

        __forceinline e_uint16& __fastcall operator%=(const unsigned short value) {
            _value = XOR_T(XOR_T(_value, crypto::seed) % value, crypto::seed);
            return *this;
        }

        __forceinline e_uint16& __fastcall operator^=(const unsigned short value) {
            _value = XOR_T(XOR_T(_value, crypto::seed) ^ value, crypto::seed);
            return *this;
        }

        __forceinline e_uint16& __fastcall operator&=(const unsigned short value) {
            _value = XOR_T(XOR_T(_value, crypto::seed) & value, crypto::seed);
            return *this;
        }

        __forceinline e_uint16& __fastcall operator|=(const unsigned short value) {
            _value = XOR_T(XOR_T(_value, crypto::seed) | value, crypto::seed);
            return *this;
        }

        __forceinline e_uint16& __fastcall operator<<=(const unsigned short value) {
            _value = XOR_T(XOR_T(_value, crypto::seed) << value, crypto::seed);
            return *this;
        }

        __forceinline e_uint16& __fastcall operator>>=(const unsigned short value) {
            _value = XOR_T(XOR_T(_value, crypto::seed) >> value, crypto::seed);
            return *this;
        }

        __forceinline e_uint16& __fastcall operator=(const unsigned short value) {
            _value = XOR_T(value, crypto::seed);
            return *this;
        }

        __forceinline  __fastcall operator unsigned short() const {
            return XOR_T(_value, crypto::seed);
        }

#pragma endregion
    };

#pragma endregion

#pragma region 32-bit

    class e_int32 {
    private:
        int _value;
    public:

#pragma region CTOR
        __forceinline __fastcall e_int32(int value) {
            _value = XOR_T(value, crypto::seed);
        }
#pragma endregion

#pragma region Accessors
        __forceinline int __fastcall get() const {
            return XOR_T(_value, crypto::seed);
        }
        __forceinline void __fastcall set(int value) {
            _value = XOR_T(value, crypto::seed);
        }
#pragma endregion

#pragma region Operators

        __forceinline e_int32 __fastcall operator+(const int value) const {
            return e_int32(XOR_T(_value, crypto::seed) + value);
        };

        __forceinline e_int32 __fastcall operator-(const int value) const {
            return e_int32(XOR_T(_value, crypto::seed) - value);
        }

        __forceinline e_int32 __fastcall operator/(const int value) const {
            return e_int32(XOR_T(_value, crypto::seed) / value);
        }

        __forceinline e_int32 __fastcall operator*(const int value) const {
            return e_int32(XOR_T(_value, crypto::seed) * value);
        }

        __forceinline e_int32 __fastcall operator&(const int value) const {
            return e_int32(XOR_T(_value, crypto::seed) & value);
        }

        __forceinline e_int32 __fastcall operator|(const int value) const {
            return e_int32(XOR_T(_value, crypto::seed) | value);
        }

        __forceinline e_int32 __fastcall operator%(const int value) const {
            return e_int32(XOR_T(_value, crypto::seed) % value);
        }

        __forceinline e_int32 __fastcall operator^(const int value) const {
            return e_int32(XOR_T(_value, crypto::seed) ^ value);
        }

        __forceinline e_int32 __fastcall operator<<(const int value) const {
            return e_int32(XOR_T(_value, crypto::seed) << value);
        }

        __forceinline e_int32 __fastcall operator>>(const int value) const {
            return e_int32(XOR_T(_value, crypto::seed) >> value);
        }

        __forceinline e_int32& __fastcall operator+=(const int value) {
            _value = XOR_T(XOR_T(_value, crypto::seed) + value, crypto::seed);
            return *this;
        }

        __forceinline e_int32& __fastcall operator-=(const int value) {
            _value = XOR_T(XOR_T(_value, crypto::seed) - value, crypto::seed);
            return *this;
        }

        __forceinline e_int32& __fastcall operator*=(const int value) {
            _value = XOR_T(XOR_T(_value, crypto::seed) * value, crypto::seed);
            return *this;
        }

        __forceinline e_int32& __fastcall operator/=(const int value) {
            _value = XOR_T(XOR_T(_value, crypto::seed) / value, crypto::seed);
            return *this;
        }

        __forceinline e_int32& __fastcall operator%=(const int value) {
            _value = XOR_T(XOR_T(_value, crypto::seed) % value, crypto::seed);
            return *this;
        }

        __forceinline e_int32& __fastcall operator^=(const int value) {
            _value = XOR_T(XOR_T(_value, crypto::seed) ^ value, crypto::seed);
            return *this;
        }

        __forceinline e_int32& __fastcall operator&=(const int value) {
            _value = XOR_T(XOR_T(_value, crypto::seed) & value, crypto::seed);
            return *this;
        }

        __forceinline e_int32& __fastcall operator=(const int value) {
            _value = XOR_T(value, crypto::seed);
            return *this;
        }

        __forceinline e_int32& __fastcall operator|=(const int value) {
            _value = XOR_T(XOR_T(_value, crypto::seed) | value, crypto::seed);
            return *this;
        }

        __forceinline e_int32& __fastcall operator<<=(const int value) {
            _value = XOR_T(XOR_T(_value, crypto::seed) << value, crypto::seed);
            return *this;
        }

        __forceinline e_int32& __fastcall operator>>=(const int value) {
            _value = XOR_T(XOR_T(_value, crypto::seed) >> value, crypto::seed);
            return *this;
        }

        __forceinline __fastcall operator int() const {
            return XOR_T(_value, crypto::seed);
        }

#pragma endregion
    };

    class e_uint32 {
    private:
        unsigned int _value;
    public:

#pragma region CTOR
        __forceinline __fastcall e_uint32(unsigned int value) {
            _value = XOR_T(value, crypto::seed);
        }
#pragma endregion

#pragma region Accessors
        __forceinline unsigned int __fastcall get() const {
            return XOR_T(_value, crypto::seed);
        }
        __forceinline void __fastcall set(unsigned int value) {
            _value = XOR_T(value, crypto::seed);
        }
#pragma endregion

#pragma region Operators

        __forceinline e_uint32 __fastcall operator+(const unsigned int value) const {
            return e_uint32(XOR_T(_value, crypto::seed) + value);
        };

        __forceinline e_uint32 __fastcall operator-(const unsigned int value) const {
            return e_uint32(XOR_T(_value, crypto::seed) - value);
        }

        __forceinline e_uint32 __fastcall operator/(const unsigned int value) const {
            return e_uint32(XOR_T(_value, crypto::seed) / value);
        }

        __forceinline e_uint32 __fastcall operator*(const unsigned int value) const {
            return e_uint32(XOR_T(_value, crypto::seed) * value);
        }

        __forceinline e_uint32 __fastcall operator&(const unsigned int value) const {
            return e_uint32(XOR_T(_value, crypto::seed) & value);
        }

        __forceinline e_uint32 __fastcall operator|(const unsigned int value) const {
            return e_uint32(XOR_T(_value, crypto::seed) | value);
        }

        __forceinline e_uint32 __fastcall operator%(const unsigned int value) const {
            return e_uint32(XOR_T(_value, crypto::seed) % value);
        }

        __forceinline e_uint32 __fastcall operator^(const unsigned int value) const {
            return e_uint32(XOR_T(_value, crypto::seed) ^ value);
        }

        __forceinline e_uint32 __fastcall operator<<(const unsigned int value) const {
            return e_uint32(XOR_T(_value, crypto::seed) << value);
        }

        __forceinline e_uint32 __fastcall operator>>(const unsigned int value) const {
            return e_uint32(XOR_T(_value, crypto::seed) >> value);
        }

        __forceinline e_uint32& __fastcall operator+=(const unsigned int value) {
            _value = XOR_T(XOR_T(_value, crypto::seed) + value, crypto::seed);
            return *this;
        }

        __forceinline e_uint32& __fastcall operator-=(const unsigned int value) {
            _value = XOR_T(XOR_T(_value, crypto::seed) - value, crypto::seed);
            return *this;
        }

        __forceinline e_uint32& __fastcall operator*=(const unsigned int value) {
            _value = XOR_T(XOR_T(_value, crypto::seed) * value, crypto::seed);
            return *this;
        }

        __forceinline e_uint32& __fastcall operator/=(const unsigned int value) {
            _value = XOR_T(XOR_T(_value, crypto::seed) / value, crypto::seed);
            return *this;
        }

        __forceinline e_uint32& __fastcall operator%=(const unsigned int value) {
            _value = XOR_T(XOR_T(_value, crypto::seed) % value, crypto::seed);
            return *this;
        }

        __forceinline e_uint32& __fastcall operator^=(const unsigned int value) {
            _value = XOR_T(XOR_T(_value, crypto::seed) ^ value, crypto::seed);
            return *this;
        }

        __forceinline e_uint32& __fastcall operator&=(const unsigned int value) {
            _value = XOR_T(XOR_T(_value, crypto::seed) & value, crypto::seed);
            return *this;
        }

        __forceinline e_uint32& __fastcall operator|=(const unsigned int value) {
            _value = XOR_T(XOR_T(_value, crypto::seed) | value, crypto::seed);
            return *this;
        }

        __forceinline e_uint32& __fastcall operator=(const unsigned int value) {
            _value = XOR_T(value, crypto::seed);
            return *this;
        }

        __forceinline e_uint32& __fastcall operator<<=(const unsigned int value) {
            _value = XOR_T(XOR_T(_value, crypto::seed) << value, crypto::seed);
            return *this;
        }

        __forceinline e_uint32& __fastcall operator>>=(const unsigned int value) {
            _value = XOR_T(XOR_T(_value, crypto::seed) >> value, crypto::seed);
            return *this;
        }

        __forceinline __fastcall operator int() const {
            return XOR_T(_value, crypto::seed);
        }

#pragma endregion
    };

#pragma endregion

#pragma region 64-bit

    class e_int64 {

    private:

        long long _value;

    public:

#pragma region CTOR

        __forceinline __fastcall e_int64(long long value) {
            _value = XOR_T(value, crypto::seed);
        }

#pragma endregion

#pragma region Accessors

        __forceinline long long __fastcall get() const {
            return XOR_T(_value, crypto::seed);
        }

        __forceinline void __fastcall set(long long value) {
            _value = XOR_T(value, crypto::seed);
        }

#pragma endregion

#pragma region Operators

        __forceinline e_int64 __fastcall operator+(const long long value) const {
            return e_int64(XOR_T(_value, crypto::seed) + value);
        };

        __forceinline e_int64 __fastcall operator-(const long long value) const {
            return e_int64(XOR_T(_value, crypto::seed) - value);
        }

        __forceinline e_int64 __fastcall operator/(const long long value) const {
            return e_int64(XOR_T(_value, crypto::seed) / value);
        }

        __forceinline e_int64 __fastcall operator*(const long long value) const {
            return e_int64(XOR_T(_value, crypto::seed) * value);
        }

        __forceinline e_int64 __fastcall operator&(const long long value) const {
            return e_int64(XOR_T(_value, crypto::seed) & value);
        }

        __forceinline e_int64 __fastcall operator|(const long long value) const {
            return e_int64(XOR_T(_value, crypto::seed) | value);
        }

        __forceinline e_int64 __fastcall operator%(const long long value) const {
            return e_int64(XOR_T(_value, crypto::seed) % value);
        }

        __forceinline e_int64 __fastcall operator^(const long long value) const {
            return e_int64(XOR_T(_value, crypto::seed) ^ value);
        }

        __forceinline e_int64 __fastcall operator<<(const long long value) const {
            return e_int64(XOR_T(_value, crypto::seed) << value);
        }

        __forceinline e_int64 __fastcall operator>>(const long long value) const {
            return e_int64(XOR_T(_value, crypto::seed) >> value);
        }

        __forceinline e_int64& __fastcall operator+=(const long long value) {
            _value = XOR_T(XOR_T(_value, crypto::seed) + value, crypto::seed);
            return *this;
        }

        __forceinline e_int64& __fastcall operator-=(const long long value) {
            _value = XOR_T(XOR_T(_value, crypto::seed) - value, crypto::seed);
            return *this;
        }

        __forceinline e_int64& __fastcall operator*=(const long long value) {
            _value = XOR_T(XOR_T(_value, crypto::seed) * value, crypto::seed);
            return *this;
        }

        __forceinline e_int64& __fastcall operator/=(const long long value) {
            _value = XOR_T(XOR_T(_value, crypto::seed) / value, crypto::seed);
            return *this;
        }

        __forceinline e_int64& __fastcall operator%=(const long long value) {
            _value = XOR_T(XOR_T(_value, crypto::seed) % value, crypto::seed);
            return *this;
        }

        __forceinline e_int64& __fastcall operator^=(const long long value) {
            _value = XOR_T(XOR_T(_value, crypto::seed) ^ value, crypto::seed);
            return *this;
        }

        __forceinline e_int64& __fastcall operator&=(const long long value) {
            _value = XOR_T(XOR_T(_value, crypto::seed) & value, crypto::seed);
            return *this;
        }

        __forceinline e_int64& __fastcall operator|=(const long long value) {
            _value = XOR_T(XOR_T(_value, crypto::seed) | value, crypto::seed);
            return *this;
        }

        __forceinline e_int64& __fastcall operator=(const long long value) {
            _value = XOR_T(value, crypto::seed);
            return *this;
        }

        __forceinline e_int64& __fastcall operator<<=(const long long value) {
            _value = XOR_T(XOR_T(_value, crypto::seed) << value, crypto::seed);
            return *this;
        }

        __forceinline e_int64& __fastcall operator>>=(const long long value) {
            _value = XOR_T(XOR_T(_value, crypto::seed) >> value, crypto::seed);
            return *this;
        }

        __forceinline __fastcall operator long long() const {
            return XOR_T(_value, crypto::seed);
        }

#pragma endregion
    };

    class e_uint64 {
    private:
        unsigned long long _value;
    public:

#pragma region CTOR
        __forceinline __fastcall e_uint64(unsigned long long value) {
            _value = XOR_T(value, crypto::seed);
        }
#pragma endregion

#pragma region Accessors
        __forceinline unsigned long long __fastcall get() const {
            return XOR_T(_value, crypto::seed);
        }
        __forceinline void __fastcall set(unsigned long long value) {
            _value = XOR_T(value, crypto::seed);
        }
#pragma endregion

#pragma region Operators

        __forceinline e_uint64 __fastcall operator+(const unsigned long long value) const {
            return e_uint64(XOR_T(_value, crypto::seed) + value);
        };

        __forceinline e_uint64 __fastcall operator-(const unsigned long long value) const {
            return e_uint64(XOR_T(_value, crypto::seed) - value);
        }

        __forceinline e_uint64 __fastcall operator/(const unsigned long long value) const {
            return e_uint64(XOR_T(_value, crypto::seed) / value);
        }

        __forceinline e_uint64 __fastcall operator*(const unsigned long long value) const {
            return e_uint64(XOR_T(_value, crypto::seed) * value);
        }

        __forceinline e_uint64 __fastcall operator&(const unsigned long long value) const {
            return e_uint64(XOR_T(_value, crypto::seed) & value);
        }

        __forceinline e_uint64 __fastcall operator|(const unsigned long long value) const {
            return e_uint64(XOR_T(_value, crypto::seed) | value);
        }

        __forceinline e_uint64 __fastcall operator%(const unsigned long long value) const {
            return e_uint64(XOR_T(_value, crypto::seed) % value);
        }

        __forceinline e_uint64 __fastcall operator^(const unsigned long long value) const {
            return e_uint64(XOR_T(_value, crypto::seed) ^ value);
        }

        __forceinline e_uint64 __fastcall operator<<(const unsigned long long value) const {
            return e_uint64(XOR_T(_value, crypto::seed) << value);
        }

        __forceinline e_uint64 __fastcall operator>>(const unsigned long long value) const {
            return e_uint64(XOR_T(_value, crypto::seed) >> value);
        }

        __forceinline e_uint64& __fastcall operator+=(const unsigned long long value) {
            _value = XOR_T(XOR_T(_value, crypto::seed) + value, crypto::seed);
            return *this;
        }

        __forceinline e_uint64& __fastcall operator-=(const unsigned long long value) {
            _value = XOR_T(XOR_T(_value, crypto::seed) - value, crypto::seed);
            return *this;
        }

        __forceinline e_uint64& __fastcall operator*=(const unsigned long long value) {
            _value = XOR_T(XOR_T(_value, crypto::seed) * value, crypto::seed);
            return *this;
        }

        __forceinline e_uint64& __fastcall operator/=(const unsigned long long value) {
            _value = XOR_T(XOR_T(_value, crypto::seed) / value, crypto::seed);
            return *this;
        }

        __forceinline e_uint64& __fastcall operator%=(const unsigned long long value) {
            _value = XOR_T(XOR_T(_value, crypto::seed) % value, crypto::seed);
            return *this;
        }

        __forceinline e_uint64& __fastcall operator^=(const unsigned long long value) {
            _value = XOR_T(XOR_T(_value, crypto::seed) ^ value, crypto::seed);
            return *this;
        }

        __forceinline e_uint64& __fastcall operator&=(const unsigned long long value) {
            _value = XOR_T(XOR_T(_value, crypto::seed) & value, crypto::seed);
            return *this;
        }

        __forceinline e_uint64& __fastcall operator|=(const unsigned long long value) {
            _value = XOR_T(XOR_T(_value, crypto::seed) | value, crypto::seed);
            return *this;
        }

        __forceinline e_uint64& __fastcall operator<<=(const unsigned long long value) {
            _value = XOR_T(XOR_T(_value, crypto::seed) << value, crypto::seed);
            return *this;
        }

        __forceinline e_uint64& __fastcall operator>>=(const unsigned long long value) {
            _value = XOR_T(XOR_T(_value, crypto::seed) >> value, crypto::seed);
            return *this;
        }

        __forceinline e_uint64& __fastcall operator=(const unsigned long long value) {
            _value = XOR_T(value, crypto::seed);
            return *this;
        }

        __forceinline  __fastcall operator unsigned long long() const {
            return XOR_T(_value, crypto::seed);
        }

#pragma endregion
    };

#pragma endregion

#pragma endregion

#pragma region Floating Point

#pragma region 32-bit

    class e_float {
    private:
        float _value;
    public:

#pragma region CTOR

        __forceinline __fastcall e_float(float value) {
            _value = XOR_T(value, crypto::seed);
        }

#pragma endregion

#pragma region Accessors

        __forceinline float __fastcall get() const {
            return XOR_T(_value, crypto::seed);
        }

        __forceinline void __fastcall set(float value) {
            _value = XOR_T(value, crypto::seed);
        }

#pragma endregion

#pragma region Operators

        __forceinline e_float __fastcall operator+(const float value) const {
            return e_float(XOR_T(_value, crypto::seed) + value);
        };

        __forceinline e_float __fastcall operator-(const float value) const {
            return e_float(XOR_T(_value, crypto::seed) - value);
        }

        __forceinline e_float __fastcall operator/(const float value) const {
            return e_float(XOR_T(_value, crypto::seed) / value);
        }

        __forceinline e_float __fastcall operator*(const float value) const {
            return e_float(XOR_T(_value, crypto::seed) * value);
        }

        __forceinline e_float __fastcall operator^(const float value) const {
            return e_float(XOR_FORCE(XOR_T(_value, crypto::seed), value));
        }

        __forceinline e_float& __fastcall operator+=(const float value) {
            _value = XOR_T(XOR_T(_value, crypto::seed) + value, crypto::seed);
            return *this;
        }

        __forceinline e_float& __fastcall operator-=(const float value) {
            _value = XOR_T(XOR_T(_value, crypto::seed) - value, crypto::seed);
            return *this;
        }

        __forceinline e_float& __fastcall operator*=(const float value) {
            _value = XOR_T(XOR_T(_value, crypto::seed) * value, crypto::seed);
            return *this;
        }

        __forceinline e_float& __fastcall operator/=(const float value) {
            _value = XOR_T(XOR_T(_value, crypto::seed) / value, crypto::seed);
            return *this;
        }

        __forceinline e_float& __fastcall operator^=(const float value) {
            _value = XOR_T(XOR_T(_value, crypto::seed), crypto::seed);
            return *this;
        }

        __forceinline e_float& __fastcall operator=(const float value) {
            _value = XOR_T(value, crypto::seed);
            return *this;
        }

        __forceinline  __fastcall operator float() const {
            return XOR_T(_value, crypto::seed);
        }

#pragma endregion
    };

#pragma endregion

#pragma region 64-bit

    class e_double {
    private:
        double _value;
    public:

#pragma region CTOR
        __forceinline __fastcall e_double(double value) {
            _value = XOR_T(value, crypto::seed);
        }
#pragma endregion

#pragma region Accessors
        __forceinline double __fastcall get() const {
            return XOR_T(_value, crypto::seed);
        }
        __forceinline void __fastcall set(double value) {
            _value = XOR_T(value, crypto::seed);
        }
#pragma endregion

#pragma region Operators

        __forceinline e_double __fastcall operator+(const double value) const {
            return e_double(XOR_T(_value, crypto::seed) + value);
        };

        __forceinline e_double __fastcall operator-(const double value) const {
            return e_double(XOR_T(_value, crypto::seed) - value);
        }

        __forceinline e_double __fastcall operator/(const double value) const {
            return e_double(XOR_T(_value, crypto::seed) / value);
        }

        __forceinline e_double __fastcall operator*(const double value) const {
            return e_double(XOR_T(_value, crypto::seed) * value);
        }

        __forceinline e_double __fastcall operator^(const double value) const {
            return e_double(XOR_FORCE(XOR_T(_value, crypto::seed), value));
        }

        __forceinline e_double& __fastcall operator+=(const double value) {
            _value = XOR_T(XOR_T(_value, crypto::seed) + value, crypto::seed);
            return *this;
        }

        __forceinline e_double& __fastcall operator-=(const double value) {
            _value = XOR_T(XOR_T(_value, crypto::seed) - value, crypto::seed);
            return *this;
        }

        __forceinline e_double& __fastcall operator*=(const double value) {
            _value = XOR_T(XOR_T(_value, crypto::seed) * value, crypto::seed);
            return *this;
        }

        __forceinline e_double& __fastcall operator/=(const double value) {
            _value = XOR_T(XOR_T(_value, crypto::seed) / value, crypto::seed);
            return *this;
        }

        __forceinline e_double& __fastcall operator^=(const double value) {
            _value = XOR_T(XOR_FORCE(XOR_T(_value, crypto::seed), value), crypto::seed);
            return *this;
        }

        __forceinline e_double& __fastcall operator=(const double value) {
            _value = XOR_T(value, crypto::seed);
            return *this;
        }

        __forceinline __fastcall operator double() const {
            return XOR_T(_value, crypto::seed);
        }

#pragma endregion
    };

#pragma endregion

#pragma endregion

#pragma region SSE Types

    //SSE
#ifdef __SSE__

    class e_m128 {
    private:
        __m128 _value;
    public:

#pragma region CTOR
        __forceinline __fastcall e_m128(__m128 value) {
            _value = XOR_T(value, crypto::seed);
        }
#pragma endregion

#pragma region Accessors
        __forceinline __m128 __fastcall get() const {
            return XOR_T(_value, crypto::seed);
        }
        __forceinline void __fastcall set(__m128 value) {
            _value = XOR_T(value, crypto::seed);
        }
#pragma endregion

#pragma region Operators
#ifdef __clang__ // msvc does not support math operators on vector types

        __forceinline e_m128 __fastcall operator+(const __m128 value) const {
            return e_m128(XOR_T(_value, crypto::seed) + value);
        };

        __forceinline e_m128 __fastcall operator-(const __m128 value) const {
            return e_m128(XOR_T(_value, crypto::seed) - value);
        }

        __forceinline e_m128 __fastcall operator/(const __m128 value) const {
            return e_m128((const __m128)XOR_T(_value, crypto::seed) / value);
        }

        __forceinline e_m128 __fastcall operator*(const __m128 value) const {
            return e_m128(XOR_T(_value, crypto::seed) * value);
        }

#endif

        __forceinline e_m128 __fastcall operator^(const __m128 value) const {
            return e_m128(XOR_FORCE(XOR_T(_value, crypto::seed), value));
        }

#ifdef __clang__

        __forceinline e_m128& __fastcall operator+=(const __m128 value) {
            _value = XOR_T(XOR_T(_value, crypto::seed) + value, crypto::seed);
            return *this;
        }

        __forceinline e_m128& __fastcall operator-=(const __m128 value) {
            _value = XOR_T(XOR_T(_value, crypto::seed) - value, crypto::seed);
            return *this;
        }

        __forceinline e_m128& __fastcall operator*=(const __m128 value) {
            _value = XOR_T(XOR_T(_value, crypto::seed) * value, crypto::seed);
            return *this;
        }

        __forceinline e_m128& __fastcall operator/=(const __m128 value) {
            _value = XOR_T(XOR_T(_value, crypto::seed) / value, crypto::seed);
            return *this;
        }

#endif

        __forceinline e_m128& __fastcall operator^=(const __m128 value) {
            _value = XOR_T(XOR_FORCE(XOR_T(_value, crypto::seed), value), crypto::seed);
            return *this;
        }

        __forceinline e_m128& __fastcall operator=(const __m128 value) {
            _value = XOR_T(value, crypto::seed);
            return *this;
        }

        __forceinline __fastcall operator __m128() const {
            return XOR_T(_value, crypto::seed);
        }

#pragma endregion
    };

#ifdef __SSE2__

    class e_m128i {
    private:
        __m128i _value;
    public:

#pragma region CTOR
        __forceinline __fastcall e_m128i(__m128i value) {
            _value = XOR_T(value, crypto::seed);
        }
#pragma endregion

#pragma region Accessors
        __forceinline __m128i __fastcall get() const {
            return XOR_T(_value, crypto::seed);
        }
        __forceinline void __fastcall set(__m128i value) {
            _value = XOR_T(value, crypto::seed);
        }
#pragma endregion

#pragma region Operators

#ifdef __clang__

        __forceinline e_m128i __fastcall operator+(const __m128i value) const {
            return e_m128i(XOR_T(_value, crypto::seed) + value);
        };

        __forceinline e_m128i __fastcall operator-(const __m128i value) const {
            return e_m128i(XOR_T(_value, crypto::seed) - value);
        }

        __forceinline e_m128i __fastcall operator/(const __m128i value) const {
            return e_m128i(XOR_T(_value, crypto::seed) / value);
        }

        __forceinline e_m128i __fastcall operator*(const __m128i value) const {
            return e_m128i(XOR_T(_value, crypto::seed) * value);
        }

#endif

        __forceinline e_m128i __fastcall operator^(const __m128i value) const {
            return e_m128i(XOR_FORCE(XOR_T(_value, crypto::seed), value));
        }

#ifdef __clang__

        __forceinline e_m128i& __fastcall operator+=(const __m128i value) {
            _value = XOR_T(XOR_T(_value, crypto::seed) + value, crypto::seed);
            return *this;
        }

        __forceinline e_m128i& __fastcall operator-=(const __m128i value) {
            _value = XOR_T(XOR_T(_value, crypto::seed) - value, crypto::seed);
            return *this;
        }

        __forceinline e_m128i& __fastcall operator*=(const __m128i value) {
            _value = XOR_T(XOR_T(_value, crypto::seed) * value, crypto::seed);
            return *this;
        }

        __forceinline e_m128i& __fastcall operator/=(const __m128i value) {
            _value = XOR_T(XOR_T(_value, crypto::seed) / value, crypto::seed);
            return *this;
        }

#endif

        __forceinline e_m128i& __fastcall operator^=(const __m128i value) {
            _value = XOR_T(XOR_FORCE(XOR_T(_value, crypto::seed), value), crypto::seed);
            return *this;
        }

        __forceinline e_m128i& __fastcall operator=(const __m128i value) {
            _value = XOR_T(value, crypto::seed);
            return *this;
        }

        __forceinline __fastcall operator __m128i() const {
            return XOR_T(_value, crypto::seed);
        }

#pragma endregion
    };

    class e_m128d {
    private:
        __m128d _value;
    public:

#pragma region CTOR
        __forceinline __fastcall e_m128d(__m128d value) {
            _value = XOR_T(value, crypto::seed);
        }
#pragma endregion

#pragma region Accessors
        __forceinline __m128d __fastcall get() const {
            return XOR_T(_value, crypto::seed);
        }
        __forceinline void __fastcall set(__m128d value) {
            _value = XOR_T(value, crypto::seed);
        }
#pragma endregion

#pragma region Operators

#ifdef __clang__

        __forceinline e_m128d __fastcall operator+(const __m128d value) const {
            return e_m128d(XOR_T(_value, crypto::seed) + value);
        };

        __forceinline e_m128d __fastcall operator-(const __m128d value) const {
            return e_m128d(XOR_T(_value, crypto::seed) - value);
        }

        __forceinline e_m128d __fastcall operator/(const __m128d value) const {
            return e_m128d(XOR_T(_value, crypto::seed) / value);
        }

        __forceinline e_m128d __fastcall operator*(const __m128d value) const {
            return e_m128d(XOR_T(_value, crypto::seed) * value);
        }

#endif

        __forceinline e_m128d __fastcall operator^(const __m128d value) const {
            return e_m128d(XOR_FORCE(XOR_T(_value, crypto::seed), value));
        }

#ifdef __clang__

        __forceinline e_m128d& __fastcall operator+=(const __m128d value) {
            _value = XOR_T(XOR_T(_value, crypto::seed) + value, crypto::seed);
            return *this;
        }

        __forceinline e_m128d& __fastcall operator-=(const __m128d value) {
            _value = XOR_T(XOR_T(_value, crypto::seed) - value, crypto::seed);
            return *this;
        }

        __forceinline e_m128d& __fastcall operator*=(const __m128d value) {
            _value = XOR_T(XOR_T(_value, crypto::seed) * value, crypto::seed);
            return *this;
        }

        __forceinline e_m128d& __fastcall operator/=(const __m128d value) {
            _value = XOR_T(XOR_T(_value, crypto::seed) / value, crypto::seed);
            return *this;
        }

#endif

        __forceinline e_m128d& __fastcall operator^=(const __m128d value) {
            _value = XOR_T(XOR_FORCE(XOR_T(_value, crypto::seed), value), crypto::seed);
            return *this;
        }

        __forceinline e_m128d& __fastcall operator=(const __m128d value) {
            _value = XOR_T(value, crypto::seed);
            return *this;
        }

        __forceinline __fastcall operator __m128d() const {
            return XOR_T(_value, crypto::seed);
        }

#pragma endregion
    };

#endif

#endif

#pragma endregion

#pragma region AVX Types

#ifdef __AVX__

    class e_m256 {
    private:
        __m256 _value;
    public:

#pragma region CTOR
        __forceinline __fastcall e_m256(__m256 value) {
            _value = XOR_T(value, crypto::seed);
        }
#pragma endregion

#pragma region Accessors
        __forceinline __m256 __fastcall get() const {
            return XOR_T(_value, crypto::seed);
        }
        __forceinline void __fastcall set(__m256 value) {
            _value = XOR_T(value, crypto::seed);
        }
#pragma endregion

#pragma region Operators

#ifdef __clang__
        __forceinline e_m256 __fastcall operator+(const __m256 value) const {
            return e_m256(XOR_T(_value, crypto::seed) + value);
        };

        __forceinline e_m256 __fastcall operator-(const __m256 value) const {
            return e_m256(XOR_T(_value, crypto::seed) - value);
        }

        __forceinline e_m256 __fastcall operator/(const __m256 value) const {
            return e_m256(XOR_T(_value, crypto::seed) / value);
        }

        __forceinline e_m256 __fastcall operator*(const __m256 value) const {
            return e_m256(XOR_T(_value, crypto::seed) * value);
        }

#endif

        __forceinline e_m256 __fastcall operator^(const __m256 value) const {
            return e_m256(XOR_FORCE(XOR_T(_value, crypto::seed), value));
        }

#ifdef __clang__

        __forceinline e_m256& __fastcall operator+=(const __m256 value) {
            _value = XOR_T(XOR_T(_value, crypto::seed) + value, crypto::seed);
            return *this;
        }

        __forceinline e_m256& __fastcall operator-=(const __m256 value) {
            _value = XOR_T(XOR_T(_value, crypto::seed) - value, crypto::seed);
            return *this;
        }

        __forceinline e_m256& __fastcall operator*=(const __m256 value) {
            _value = XOR_T(XOR_T(_value, crypto::seed) * value, crypto::seed);
            return *this;
        }

        __forceinline e_m256& __fastcall operator/=(const __m256 value) {
            _value = XOR_T(XOR_T(_value, crypto::seed) / value, crypto::seed);
            return *this;
        }

#endif

        __forceinline e_m256& __fastcall operator^=(const __m256 value) {
            _value = XOR_T(XOR_FORCE(XOR_T(_value, crypto::seed), value), crypto::seed);
            return *this;
        }

        __forceinline e_m256& __fastcall operator=(const __m256 value) {
            _value = XOR_T(value, crypto::seed);
            return *this;
        }

        __forceinline __fastcall operator __m256() const {
            return XOR_T(_value, crypto::seed);
        }

#pragma endregion
    };

    class e_m256i {
    private:
        __m256i _value;
    public:

#pragma region CTOR
        __forceinline __fastcall e_m256i(__m256i value) {
            _value = XOR_T(value, crypto::seed);
        }
#pragma endregion

#pragma region Accessors
        __forceinline __m256i __fastcall get() const {
            return XOR_T(_value, crypto::seed);
        }
        __forceinline void __fastcall set(__m256i value) {
            _value = XOR_T(value, crypto::seed);
        }
#pragma endregion

#pragma region Operators

#ifdef __clang__

        __forceinline e_m256i __fastcall operator+(const __m256i value) const {
            return e_m256i(XOR_T(_value, crypto::seed) + value);
        };

        __forceinline e_m256i __fastcall operator-(const __m256i value) const {
            return e_m256i(XOR_T(_value, crypto::seed) - value);
        }

        __forceinline e_m256i __fastcall operator/(const __m256i value) const {
            return e_m256i(XOR_T(_value, crypto::seed) / value);
        }

        __forceinline e_m256i __fastcall operator*(const __m256i value) const {
            return e_m256i(XOR_T(_value, crypto::seed) * value);
        }

#endif

        __forceinline e_m256i __fastcall operator^(const __m256i value) const {
            return e_m256i(XOR_FORCE(XOR_T(_value, crypto::seed), value));
        }



#ifdef __clang__

        __forceinline e_m256i& __fastcall operator+=(const __m256i value) {
            _value = XOR_T(XOR_T(_value, crypto::seed) + value, crypto::seed);
            return *this;
        }

        __forceinline e_m256i& __fastcall operator-=(const __m256i value) {
            _value = XOR_T(XOR_T(_value, crypto::seed) - value, crypto::seed);
            return *this;
        }

        __forceinline e_m256i& __fastcall operator*=(const __m256i value) {
            _value = XOR_T(XOR_T(_value, crypto::seed) * value, crypto::seed);
            return *this;
        }

        __forceinline e_m256i& __fastcall operator/=(const __m256i value) {
            _value = XOR_T(XOR_T(_value, crypto::seed) / value, crypto::seed);
            return *this;
        }

#endif

        __forceinline e_m256i& __fastcall operator^=(const __m256i value) {
            _value = XOR_T(XOR_FORCE(XOR_T(_value, crypto::seed), value), crypto::seed);
            return *this;
        }

        __forceinline e_m256i& __fastcall operator=(const __m256i value) {
            _value = XOR_T(value, crypto::seed);
            return *this;
        }

        __forceinline __fastcall operator __m256i() const {
            return XOR_T(_value, crypto::seed);
        }

#pragma endregion
    };

    class e_m256d {
    private:
        __m256d _value;
    public:

#pragma region CTOR
        __forceinline __fastcall e_m256d(__m256d value) {
            _value = XOR_T(value, crypto::seed);
        }
#pragma endregion

#pragma region Accessors
        __forceinline __m256d __fastcall get() const {
            return XOR_T(_value, crypto::seed);
        }
        __forceinline void __fastcall set(__m256d value) {
            _value = XOR_T(value, crypto::seed);
        }
#pragma endregion

#pragma region Operators

#ifdef __clang__

        __forceinline e_m256d __fastcall operator+(const __m256d value) const {
            return e_m256d(XOR_T(_value, crypto::seed) + value);
        };

        __forceinline e_m256d __fastcall operator-(const __m256d value) const {
            return e_m256d(XOR_T(_value, crypto::seed) - value);
        }

        __forceinline e_m256d __fastcall operator/(const __m256d value) const {
            return e_m256d(XOR_T(_value, crypto::seed) / value);
        }

        __forceinline e_m256d __fastcall operator*(const __m256d value) const {
            return e_m256d(XOR_T(_value, crypto::seed) * value);
        }

#endif

        __forceinline e_m256d __fastcall operator^(const __m256d value) const {
            return e_m256d(XOR_FORCE(XOR_T(_value, crypto::seed), value));
        }

#ifdef __clang__

        __forceinline e_m256d& __fastcall operator+=(const __m256d value) {
            _value = XOR_T(XOR_T(_value, crypto::seed) + value, crypto::seed);
            return *this;
        }

        __forceinline e_m256d& __fastcall operator-=(const __m256d value) {
            _value = XOR_T(XOR_T(_value, crypto::seed) - value, crypto::seed);
            return *this;
        }

        __forceinline e_m256d& __fastcall operator*=(const __m256d value) {
            _value = XOR_T(XOR_T(_value, crypto::seed) * value, crypto::seed);
            return *this;
        }

        __forceinline e_m256d& __fastcall operator/=(const __m256d value) {
            _value = XOR_T(XOR_T(_value, crypto::seed) / value, crypto::seed);
            return *this;
        }

#endif

        __forceinline e_m256d& __fastcall operator^=(const __m256d value) {
            _value = XOR_T(XOR_FORCE(XOR_T(_value, crypto::seed), value), crypto::seed);
            return *this;
        }

        __forceinline e_m256d& __fastcall operator=(const __m256d value) {
            _value = XOR_T(value, crypto::seed);
            return *this;
        }

        __forceinline  __fastcall operator __m256d() const {
            return XOR_T(_value, crypto::seed);
        }

#pragma endregion
    };

#endif

#pragma endregion

#pragma endregion

#pragma region String

    class e_string {

    private:

#pragma region Encrypted value

        std::string _value = "";

#pragma endregion

    public:

#pragma region CTOR

        __forceinline __fastcall e_string(const std::string& value) {
            _value = XOR_STR_T(value, crypto::seed);
        }

        __forceinline __fastcall e_string(const char* value) {
            _value = XOR_STR_T(std::string(value), crypto::seed);
        }

#pragma endregion

#pragma region Accessors

        __forceinline std::string __fastcall get() const {
            return XOR_STR_T(std::string(_value), crypto::seed);
        }

        __forceinline void __fastcall set(const std::string& value) {
            _value = XOR_STR_T(value, crypto::seed);
        }

        __forceinline e_string __fastcall operator+(const std::string& value) const {
            return e_string(XOR_STR_T(std::string(_value), crypto::seed) + value);
        };

        __forceinline e_string& __fastcall operator+=(const std::string& value) {
            _value = XOR_STR_T(static_cast<std::string>(XOR_STR_T(_value, crypto::seed) + value)
                , crypto::seed);
            return *this;
        }

        __forceinline e_string& __fastcall operator=(const std::string& value) {
            set(value);
            return *this;
        }

        __forceinline __fastcall operator std::string() const {
            return XOR_STR_T(_value, crypto::seed);
        }

        __forceinline __fastcall ~e_string() {
            //attempt to trigger memory release
            try {
                std::string().swap(_value);
            }
            catch (std::exception& except) {}
        }

#pragma endregion

#pragma region Operators

#pragma endregion
    };

    class e_wstring {
    private:

#pragma region Encrypted value

        std::wstring _value = L"";

#pragma endregion

    public:

#pragma region CTOR

        __forceinline __fastcall e_wstring(const std::wstring& value) {
            _value = XOR_WSTR_T(value, crypto::seed);
        }

        __forceinline __fastcall e_wstring(const wchar_t* value) {
            _value = XOR_WSTR_T(std::wstring(value), crypto::seed);
        }

        __forceinline __fastcall e_wstring() {
            _value = L"";
        }

#pragma endregion

#pragma region Accessors

        __forceinline std::wstring __fastcall get() const {
            return XOR_WSTR_T(std::wstring(_value), crypto::seed);
        }

        __forceinline void __fastcall set(const std::wstring& value) {
            _value = XOR_WSTR_T(value, crypto::seed);
        }

        __forceinline void __fastcall reserve(unsigned long count) {
            _value.reserve(count);
        }

        __forceinline bool __fastcall empty() const {
            return _value.empty();
        }

        __forceinline e_wstring __fastcall operator+(const std::wstring& value) const {
            return e_wstring(XOR_WSTR_T(std::wstring(_value), crypto::seed) + value);
        };

        __forceinline e_wstring& __fastcall operator+=(const std::wstring& value) {
            _value = XOR_WSTR_T(static_cast<std::wstring>(XOR_WSTR_T(_value, crypto::seed) + value)
                , crypto::seed);
            return *this;
        }

        __forceinline e_wstring& __fastcall operator=(const std::wstring& value) {
            set(value);
            return *this;
        }

        __forceinline wchar_t& __fastcall operator[](const int index) {
            return XOR_WSTR_T(_value, crypto::seed)[index];
        }

        __forceinline __fastcall operator std::wstring() const {
            return XOR_WSTR_T(_value, crypto::seed);
        }

        __forceinline __fastcall ~e_wstring() {
            //attempt to trigger memory release
            try {
                std::wstring().swap(_value);
            }
            catch (std::exception& except) {}
        }

#pragma endregion

#pragma region Operators

#pragma endregion
    };

#pragma endregion

#pragma region Heap Allocation

    class e_malloc {

    private:

#pragma region Global Variables

        void* local_alloc;
        size_t alloc_size;
        // use this object to track all get() and similar calls throughout object lifespan, these will be explicitly freed in the destructor so the user won't have to explicitly free every time get() is called
        std::vector<void*> pointer_calls{};

#pragma endregion

    public:

#pragma region Proxy objects

#pragma region Decommission proxy

        struct free_delete_t
        {
            void operator()(void* pointer) const
            {
                free(pointer);
            }
        };

#pragma endregion

#pragma region Subscript proxy

        // nested class to support subscript assignment 
        class index_proxy {

        private:

#pragma region Globals

            e_malloc& parent;
            size_t index;

#pragma endregion

        public:
#pragma region Ctor

            index_proxy(size_t index_, e_malloc& instance) : index(index_), parent(instance) { }

#pragma endregion

#pragma region Operator overrides

            uint8_t& operator=(uint8_t value) {
                parent.set(index, value);
                return value;   // return the passed assignment value rather than using up absurd resources to decrypt, re-encrypt everything using get()
            }

            __forceinline __fastcall operator uint8_t() const {
                return parent.get(index);
            }

#pragma endregion

        };

#pragma endregion

#pragma endregion

#pragma region Ctor

        __forceinline __fastcall e_malloc(size_t size) {
            alloc_size = size;
            local_alloc = malloc(size);

            auto enc_alloc = XOR_RAW(local_alloc, size, crypto::seed);

            memcpy(local_alloc, enc_alloc, size);
            free(enc_alloc);
        }

        __forceinline __fastcall e_malloc() {

        }

#pragma endregion

#pragma region Get accessors

        __forceinline void* __fastcall get() {
            return XOR_RAW(local_alloc, alloc_size, crypto::seed);
        }

        __forceinline void* get(uintptr_t pos, size_t length) {
            auto dec_alloc = reinterpret_cast<uint8_t*>(get());

            auto get_alloc = calloc(length, sizeof(uint8_t));

            memcpy(get_alloc, &dec_alloc[pos], length);
            RtlZeroMemory(dec_alloc, alloc_size);
            free(dec_alloc);

            return get_alloc;
        }

        //overload get() for index operations to avoid unnecessary heap allocations and potential memory leaks
        __forceinline uint8_t __fastcall get(size_t index) {
            auto dec_alloc = reinterpret_cast<uint8_t*>(get());

            auto _return = dec_alloc[index];

            RtlZeroMemory(dec_alloc, alloc_size);
            free(dec_alloc);

            return _return;
        }

        template<typename T>
        __forceinline T __fastcall get_t(uintptr_t pos, T& value) {
            auto value_r = reinterpret_cast<T*>(get(pos, sizeof(T)));
            auto _return = *value_r;
            free(value_r);
            return _return;
        }

        __forceinline void* __fastcall get_data_pointer() {
            return local_alloc;
        }

        __forceinline size_t __fastcall get_data_size() {
            return alloc_size;
        }

#pragma endregion

#pragma region Set accessors

        //WARNING: appending length to the allocation here will cause exceptions / UB
        __forceinline void __fastcall set(void* src, uintptr_t pos, size_t length, bool free_src = false) {
            auto dec_alloc = get();

            memcpy(&reinterpret_cast<unsigned char*>(dec_alloc)[pos], src, length);

            auto enc_alloc = XOR_RAW(dec_alloc, length, crypto::seed);
            //free the decryption allocation and local alocation: reminder this class is performance-heavy and should not be used for large allocation pools
            //for security reasons
            RtlZeroMemory(dec_alloc, alloc_size);
            RtlZeroMemory(local_alloc, alloc_size);
            free(dec_alloc);
            dec_alloc = nullptr;
            free(local_alloc);
            local_alloc = nullptr;

            local_alloc = enc_alloc;

            if (free_src)
                free(src);
        }

        __forceinline void __fastcall set(uintptr_t pos, unsigned char value, size_t size) {
            auto dec_alloc = reinterpret_cast<uint8_t*>(get());

            for (auto i = pos; i < (pos + size); ++i) {
                dec_alloc[i] = value;
            }

            auto enc_alloc = XOR_RAW(dec_alloc, alloc_size, crypto::seed);
            //free the decryption allocation and local alocation: reminder this class is performance-heavy and should not be used for large allocation pools
            //for security reasons
            RtlZeroMemory(dec_alloc, alloc_size);
            RtlZeroMemory(local_alloc, alloc_size);
            free(dec_alloc);
            dec_alloc = nullptr;
            free(local_alloc);
            local_alloc = nullptr;

            local_alloc = enc_alloc;
        }

        template<typename T>
        __forceinline void __fastcall set(uintptr_t pos, T value) {
            auto dec_alloc = reinterpret_cast<uint8_t*>(get()); // so we can properly index the allocation 

            T* cast_t = reinterpret_cast<T*>(&dec_alloc[pos]);
            *cast_t = value;

            auto enc_alloc = XOR_RAW(dec_alloc, alloc_size, crypto::seed);
            //free the decryption allocation and local alocation: reminder this class is performance-heavy and should not be used for large allocation pools
            //for security reasons
            RtlZeroMemory(dec_alloc, alloc_size);
            RtlZeroMemory(local_alloc, alloc_size);
            free(local_alloc);
            local_alloc = nullptr;
            free(dec_alloc);
            dec_alloc = nullptr;
            cast_t = nullptr;

            local_alloc = enc_alloc;
        }

#pragma endregion

#pragma region Utility functions

        __forceinline void __fastcall swap(void* src, size_t length, bool free_src = false) {
            //release current resources 
            zero();
            free(local_alloc);
            local_alloc = nullptr;
            alloc_size = 0x0000000000000000ULL;

            auto enc_alloc = XOR_RAW(src, length, crypto::seed);

            alloc_size = length;
            local_alloc = enc_alloc;
        }

        //size is only the length in bytes of the allocation to be appended or destroyed
        __forceinline void __fastcall resize(size_t size) {
            auto dec_alloc = get();

            auto n_local_alloc = realloc(dec_alloc, size);

            if (!n_local_alloc) {
                free(dec_alloc);
                throw std::bad_alloc();
            }

            dec_alloc = NULL; // zero  old pointer ;; useless even if realloc didnt need to move memory
            //zero out the extended memory (if it was being extended rather than shrunk)
            if ((size) > alloc_size)
                RtlZeroMemory(&(reinterpret_cast<uint8_t*>(n_local_alloc)[alloc_size]), (size - alloc_size));

            auto enc_alloc = XOR_RAW(n_local_alloc, size, crypto::seed);
            //free the decryption allocation and local alocation: reminder this class is performance-heavy and should not be used for large allocation pools
            //for security reasons
            RtlZeroMemory(n_local_alloc, alloc_size);
            RtlZeroMemory(local_alloc, alloc_size);
            //realloc() should automatically free dec_alloc if it was moved to new memory
            free(local_alloc);
            local_alloc = nullptr;
            free(n_local_alloc);
            n_local_alloc = nullptr;

            alloc_size = size;
            local_alloc = enc_alloc;
        }

        __forceinline void __fastcall zero() {
            set(0x0000000000000000ULL, 0x00ui8, alloc_size);
        }

#pragma endregion

#pragma region Operators

        __forceinline e_malloc& __fastcall operator=(const std::vector<uint8_t>& value) {
            swap(const_cast<std::vector<uint8_t>*>(&value)->data(), value.size());

            return *this;
        }

        __forceinline __fastcall operator void* () const {
            return XOR_RAW(local_alloc, alloc_size, crypto::seed);
        }

        template<typename T>
        __forceinline __fastcall operator T* () const {
            return reinterpret_cast<T*>(XOR_RAW(local_alloc, alloc_size, crypto::seed));
        }

        index_proxy operator[](size_t index) {
            return index_proxy(index, *this);
        }



#pragma endregion

#pragma region Destructor

        __forceinline void __fastcall destroy(bool zero) {
            if (local_alloc) {
                try {
                    if (zero)
                        RtlZeroMemory(local_alloc, alloc_size);
                    free(local_alloc);
                    local_alloc = nullptr;
                }
                catch (std::exception& except) {}
            }
        }

        __forceinline void __fastcall secure_destroy() {
            destroy(true);
        }
        __forceinline __fastcall ~e_malloc() {
            secure_destroy();
        }

#pragma endregion

    };

#pragma endregion

};

#endif