#ifndef ENC_T_H
#define ENC_T_H

#pragma region Imports

#include <string>
#include <vector>
#include <memory>
#include <cstdlib>
#include <exception>

#include "../../qbase/qdef.hpp"
#include "../../polyc/polyc.hpp"
using namespace qengine::polyc;

#ifdef NDEBUG

#pragma optimize("", on)
#pragma inline_depth(255)
#pragma inline_recursion(on) 

#endif

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

namespace qengine{

	namespace qenc_t {

	#pragma region Globals  =|=  Singleton

		extern unsigned long long seed;
		extern bool is_init;

	#pragma endregion

	#pragma region Static Methods

		// this must be called once at application startup / or when you wish to begin using any type included in this header
		static void __fastcall init_constants() {
			if (!is_init) {
				is_init = true;

				polyc::polyc_init();
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

			__forceinline __fastcall e_int8(char value = 0) {
				_value = algo_t_inst(value);
			}

	#pragma endregion

	#pragma region Accessors

			__forceinline char __fastcall get() const {
				return algo_t_inst(_value);
			}

			__forceinline void __fastcall set(char value) {
				_value = algo_t_inst(value);
			}

	#pragma endregion

			char false_get() {
				return _value;
			}

	#pragma region Operators

			__forceinline e_int8 __fastcall operator+(const char value) const {
				return e_int8(algo_t_inst(_value) + value);
			};

			__forceinline e_int8 __fastcall operator-(const char value) const {
				return e_int8(algo_t_inst(_value) - value);
			}

			__forceinline e_int8 __fastcall operator/(const char value) const {
				return e_int8(algo_t_inst(_value) / value);
			}

			__forceinline e_int8 __fastcall operator*(const char value) const {
				return e_int8(algo_t_inst(_value) * value);
			}

			__forceinline e_int8 __fastcall operator&(const char value) const {
				return e_int8(algo_t_inst(_value) & value);
			}

			__forceinline e_int8 __fastcall operator|(const char value) const {
				return e_int8(algo_t_inst(_value) | value);
			}

			__forceinline e_int8 __fastcall operator%(const char value) const {
				return e_int8(algo_t_inst(_value) % value);
			}

			__forceinline e_int8 __fastcall operator^(const char value) const {
				return e_int8(algo_t_inst(_value) ^ value);
			}

			__forceinline e_int8 __fastcall operator<<(const char value) const {
				return e_int8(algo_t_inst(_value) << value);
			}

			__forceinline e_int8 __fastcall operator>>(const char value) const {
				return e_int8(algo_t_inst(_value) >> value);
			}

			__forceinline e_int8& __fastcall operator+=(const char value) {
				this->_value = algo_t_inst(static_cast<char>(algo_t_inst(_value) + value));
				return *this;
			}

			__forceinline e_int8& __fastcall operator-=(const char value) {
				this->_value = algo_t_inst(static_cast<char>(algo_t_inst(_value) - value));
				return *this;
			}

			__forceinline e_int8& __fastcall operator*=(const char value) {
				this->_value = algo_t_inst(static_cast<char>(algo_t_inst(_value) * value));
				return *this;
			}

			__forceinline e_int8& __fastcall operator/=(const char value) {
				this->_value = algo_t_inst(static_cast<char>(algo_t_inst(_value) / value));
				return *this;
			}

			__forceinline e_int8& __fastcall operator%=(const char value) {
				this->_value = algo_t_inst(static_cast<char>(algo_t_inst(_value) % value));
				return *this;
			}

			__forceinline e_int8& __fastcall operator^=(const char value) {
				this->_value = algo_t_inst(static_cast<char>(algo_t_inst(_value) ^ value));
				return *this;
			}

			__forceinline e_int8& __fastcall operator&=(const char value) {
				this->_value = algo_t_inst(static_cast<char>(algo_t_inst(_value) & value));
				return *this;
			}

			__forceinline e_int8& __fastcall operator|=(const char value) {
				this->_value = algo_t_inst(static_cast<char>(algo_t_inst(_value) | value));
				return *this;
			}

			__forceinline e_int8& __fastcall operator<<=(const char value) {
				this->_value = algo_t_inst(static_cast<char>(algo_t_inst(_value) << value));
				return *this;
			}

			__forceinline e_int8& __fastcall operator>>=(const char value) {
				this->_value = algo_t_inst(static_cast<char>(algo_t_inst(_value) >> value));
				return *this;
			}

			__forceinline e_int8& __fastcall operator=(const char value) {
				_value = algo_t_inst(value);
				return *this;
			}

			__forceinline __fastcall operator char() const {
				return algo_t_inst(_value);
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

			__forceinline __fastcall e_uint8(unsigned char value = 0) {
				_value = algo_t_inst(value);
			}

	#pragma endregion

	#pragma region Accessors

			__forceinline unsigned char __fastcall get() const {
				return algo_t_inst(_value);
			}

			__forceinline void __fastcall set(unsigned char value) {
				_value = algo_t_inst(value);
			}

	#pragma endregion

	#pragma region Operators

			__forceinline e_uint8 __fastcall operator+(const unsigned char value) const {
				return e_uint8(algo_t_inst(_value) + value);
			};

			__forceinline e_uint8 __fastcall operator-(const unsigned char value) const {
				return e_uint8(algo_t_inst(_value) - value);
			}

			__forceinline e_uint8 __fastcall operator/(const unsigned char value) const {
				return e_uint8(algo_t_inst(_value) / value);
			}

			__forceinline e_uint8 __fastcall operator*(const unsigned char value) const {
				return e_uint8(algo_t_inst(_value) * value);
			}

			__forceinline e_uint8 __fastcall operator&(const unsigned char value) const {
				return e_uint8(algo_t_inst(_value) & value);
			}

			__forceinline e_uint8 __fastcall operator|(const unsigned char value) const {
				return e_uint8(algo_t_inst(_value) | value);
			}

			__forceinline e_uint8 __fastcall operator%(const unsigned char value) const {
				return e_uint8(algo_t_inst(_value) % value);
			}

			__forceinline e_uint8 __fastcall operator^(const unsigned char value) const {
				return e_uint8(algo_t_inst(_value) ^ value);
			}

			__forceinline e_uint8 __fastcall operator<<(const unsigned char value) const {
				return e_uint8(algo_t_inst(_value) << value);
			}

			__forceinline e_uint8 __fastcall operator>>(const unsigned char value) const {
				return e_uint8(algo_t_inst(_value) >> value);
			}

			__forceinline e_uint8& __fastcall operator+=(const unsigned char value) {
				this->_value = algo_t_inst(static_cast<unsigned char>(algo_t_inst(_value) + value));
				return *this;
			}

			__forceinline e_uint8& __fastcall operator-=(const unsigned char value) {
				this->_value = algo_t_inst(static_cast<unsigned char>(algo_t_inst(_value) - value));
				return *this;
			}

			__forceinline e_uint8& __fastcall operator*=(const unsigned char value) {
				this->_value = algo_t_inst(static_cast<unsigned char>(algo_t_inst(_value) * value));
				return *this;
			}

			__forceinline e_uint8& __fastcall operator/=(const unsigned char value) {
				this->_value = algo_t_inst(static_cast<unsigned char>(algo_t_inst(_value) / value));
				return *this;
			}

			__forceinline e_uint8& __fastcall operator%=(const unsigned char value) {
				this->_value = algo_t_inst(static_cast<unsigned char>(algo_t_inst(_value) % value));
				return *this;
			}

			__forceinline e_uint8& __fastcall operator^=(const unsigned char value) {
				this->_value = algo_t_inst(static_cast<unsigned char>(algo_t_inst(_value) ^ value));
				return *this;
			}

			__forceinline e_uint8& __fastcall operator&=(const unsigned char value) {
				this->_value = algo_t_inst(static_cast<unsigned char>(algo_t_inst(_value) & value));
				return *this;
			}

			__forceinline e_uint8& __fastcall operator|=(const unsigned char value) {
				this->_value = algo_t_inst(static_cast<unsigned char>(algo_t_inst(_value) | value));
				return *this;
			}

			__forceinline e_uint8& __fastcall operator<<=(const unsigned char value) {
				this->_value = algo_t_inst(static_cast<unsigned char>(algo_t_inst(_value) << value));
				return *this;
			}

			__forceinline e_uint8& __fastcall operator>>=(const unsigned char value) {
				this->_value = algo_t_inst(static_cast<unsigned char>(algo_t_inst(_value) >> value));
				return *this;
			}

			__forceinline e_uint8& __fastcall operator=(const unsigned char value) {
				_value = algo_t_inst(value);
				return *this;
			}

			__forceinline __fastcall operator unsigned char() const {
				return algo_t_inst(_value);
			}

	#pragma endregion
		};

	#pragma endregion

	#pragma region 16-bit

		class e_int16 {
		private:

	#pragma region Encrypted value

			short _value;

	#pragma endregion

		public:

	#pragma region CTOR

			__forceinline __fastcall e_int16(short value = 0) {
				_value = algo_t_inst(value);
			}

	#pragma endregion

	#pragma region Accessors

			__forceinline short __fastcall get() const {
				return algo_t_inst(_value);
			}

			__forceinline void __fastcall set(short value) {
				_value = algo_t_inst(value);
			}

	#pragma endregion

	#pragma region Operators

			__forceinline e_int16 __fastcall operator+(const short value) const {
				return e_int16(algo_t_inst(_value) + value);
			};

			__forceinline e_int16 __fastcall operator-(const short value) const {
				return e_int16(algo_t_inst(_value) - value);
			}

			__forceinline e_int16 __fastcall operator/(const short value) const {
				return e_int16(algo_t_inst(_value) / value);
			}

			__forceinline e_int16 __fastcall operator*(const short value) const {
				return e_int16(algo_t_inst(_value) * value);
			}

			__forceinline e_int16 __fastcall operator&(const short value) const {
				return e_int16(algo_t_inst(_value) & value);
			}

			__forceinline e_int16 __fastcall operator|(const short value) const {
				return e_int16(algo_t_inst(_value) | value);
			}

			__forceinline e_int16 __fastcall operator%(const short value) const {
				return e_int16(algo_t_inst(_value) % value);
			}

			__forceinline e_int16 __fastcall operator^(const short value) const {
				return e_int16(algo_t_inst(_value) ^ value);
			}

			__forceinline e_int16 __fastcall operator<<(const short value) const {
				return e_int16(algo_t_inst(_value) << value);
			}

			__forceinline e_int16 __fastcall operator>>(const short value) const {
				return e_int16(algo_t_inst(_value) >> value);
			}

			__forceinline e_int16& __fastcall operator+=(const short value) {
				this->_value = algo_t_inst(static_cast<short>(algo_t_inst(_value) + value));
				return *this;
			}

			__forceinline e_int16& __fastcall operator-=(const short value) {
				this->_value = algo_t_inst(static_cast<short>(algo_t_inst(_value) - value));
				return *this;
			}

			__forceinline e_int16& __fastcall operator*=(const short value) {
				this->_value = algo_t_inst(static_cast<short>(algo_t_inst(_value) * value));
				return *this;
			}

			__forceinline e_int16& __fastcall operator/=(const short value) {
				this->_value = algo_t_inst(static_cast<short>(algo_t_inst(_value) / value));
				return *this;
			}

			__forceinline e_int16& __fastcall operator%=(const short value) {
				this->_value = algo_t_inst(static_cast<short>(algo_t_inst(_value) % value));
				return *this;
			}

			__forceinline e_int16& __fastcall operator^=(const short value) {
				this->_value = algo_t_inst(static_cast<short>(algo_t_inst(_value) ^ value));
				return *this;
			}

			__forceinline e_int16& __fastcall operator&=(const short value) {
				this->_value = algo_t_inst(static_cast<short>(algo_t_inst(_value) & value));
				return *this;
			}

			__forceinline e_int16& __fastcall operator|=(const short value) {
				this->_value = algo_t_inst(static_cast<short>(algo_t_inst(_value) | value));
				return *this;
			}

			__forceinline e_int16& __fastcall operator<<=(const short value) {
				this->_value = algo_t_inst(static_cast<short>(algo_t_inst(_value) << value));
				return *this;
			}

			__forceinline e_int16& __fastcall operator>>=(const short value) {
				this->_value = algo_t_inst(static_cast<short>(algo_t_inst(_value) >> value));
				return *this;
			}

			__forceinline e_int16& __fastcall operator=(const short value) {
				_value = algo_t_inst(value);
				return *this;
			}

			__forceinline __fastcall operator short() const {
				return algo_t_inst(_value);
			}

	#pragma endregion
		};

		class e_uint16 {
		private:

	#pragma region Encrypted value

			unsigned short _value;

	#pragma endregion

		public:

	#pragma region CTOR

			__forceinline __fastcall e_uint16(unsigned short value = 0) {
				_value = algo_t_inst(value);
			}

	#pragma endregion

	#pragma region Accessors

			__forceinline unsigned short __fastcall get() const {
				return algo_t_inst(_value);
			}

			__forceinline void __fastcall set(unsigned short value) {
				_value = algo_t_inst(value);
			}

	#pragma endregion

	#pragma region Operators

			__forceinline e_uint16 __fastcall operator+(const unsigned short value) const {
				return e_uint16(algo_t_inst(_value) + value);
			};

			__forceinline e_uint16 __fastcall operator-(const unsigned short value) const {
				return e_uint16(algo_t_inst(_value) - value);
			}

			__forceinline e_uint16 __fastcall operator/(const unsigned short value) const {
				return e_uint16(algo_t_inst(_value) / value);
			}

			__forceinline e_uint16 __fastcall operator*(const unsigned short value) const {
				return e_uint16(algo_t_inst(_value) * value);
			}

			__forceinline e_uint16 __fastcall operator&(const unsigned short value) const {
				return e_uint16(algo_t_inst(_value) & value);
			}

			__forceinline e_uint16 __fastcall operator|(const unsigned short value) const {
				return e_uint16(algo_t_inst(_value) | value);
			}

			__forceinline e_uint16 __fastcall operator%(const unsigned short value) const {
				return e_uint16(algo_t_inst(_value) % value);
			}

			__forceinline e_uint16 __fastcall operator^(const unsigned short value) const {
				return e_uint16(algo_t_inst(_value) ^ value);
			}

			__forceinline e_uint16 __fastcall operator<<(const unsigned short value) const {
				return e_uint16(algo_t_inst(_value) << value);
			}

			__forceinline e_uint16 __fastcall operator>>(const unsigned short value) const {
				return e_uint16(algo_t_inst(_value) >> value);
			}

			__forceinline e_uint16& __fastcall operator+=(const unsigned short value) {
				this->_value = algo_t_inst(static_cast<unsigned short>(algo_t_inst(_value) + value));
				return *this;
			}

			__forceinline e_uint16& __fastcall operator-=(const unsigned short value) {
				this->_value = algo_t_inst(static_cast<unsigned short>(algo_t_inst(_value) - value));
				return *this;
			}

			__forceinline e_uint16& __fastcall operator*=(const unsigned short value) {
				this->_value = algo_t_inst(static_cast<unsigned short>(algo_t_inst(_value) * value));
				return *this;
			}

			__forceinline e_uint16& __fastcall operator/=(const unsigned short value) {
				this->_value = algo_t_inst(static_cast<unsigned short>(algo_t_inst(_value) / value));
				return *this;
			}

			__forceinline e_uint16& __fastcall operator%=(const unsigned short value) {
				this->_value = algo_t_inst(static_cast<unsigned short>(algo_t_inst(_value) % value));
				return *this;
			}

			__forceinline e_uint16& __fastcall operator^=(const unsigned short value) {
				this->_value = algo_t_inst(static_cast<unsigned short>(algo_t_inst(_value) ^ value));
				return *this;
			}

			__forceinline e_uint16& __fastcall operator&=(const unsigned short value) {
				this->_value = algo_t_inst(static_cast<unsigned short>(algo_t_inst(_value) & value));
				return *this;
			}

			__forceinline e_uint16& __fastcall operator|=(const unsigned short value) {
				this->_value = algo_t_inst(static_cast<unsigned short>(algo_t_inst(_value) | value));
				return *this;
			}

			__forceinline e_uint16& __fastcall operator<<=(const unsigned short value) {
				this->_value = algo_t_inst(static_cast<unsigned short>(algo_t_inst(_value) << value));
				return *this;
			}

			__forceinline e_uint16& __fastcall operator>>=(const unsigned short value) {
				this->_value = algo_t_inst(static_cast<unsigned short>(algo_t_inst(_value) >> value));
				return *this;
			}

			__forceinline e_uint16& __fastcall operator=(const unsigned short value) {
				_value = algo_t_inst(value);
				return *this;
			}

			__forceinline __fastcall operator unsigned short() const {
				return algo_t_inst(_value);
			}

	#pragma endregion
		};

	#pragma endregion

	#pragma region 32-bit

		class e_int32 {
		private:

	#pragma region Encrypted value

			int _value;

	#pragma endregion

		public:

	#pragma region CTOR

			__forceinline __fastcall e_int32(int value = 0) {
				_value = algo_t_inst(value);
			}

	#pragma endregion

	#pragma region Accessors

			__forceinline int __fastcall get() const {
				return algo_t_inst(_value);
			}

			__forceinline void __fastcall set(int value) {
				_value = algo_t_inst(value);
			}

	#pragma endregion

	#pragma region Operators

			__forceinline e_int32 __fastcall operator+(const int value) const {
				return e_int32(algo_t_inst(_value) + value);
			};

			__forceinline e_int32 __fastcall operator-(const int value) const {
				return e_int32(algo_t_inst(_value) - value);
			}

			__forceinline e_int32 __fastcall operator/(const int value) const {
				return e_int32(algo_t_inst(_value) / value);
			}

			__forceinline e_int32 __fastcall operator*(const int value) const {
				return e_int32(algo_t_inst(_value) * value);
			}

			__forceinline e_int32 __fastcall operator&(const int value) const {
				return e_int32(algo_t_inst(_value) & value);
			}

			__forceinline e_int32 __fastcall operator|(const int value) const {
				return e_int32(algo_t_inst(_value) | value);
			}

			__forceinline e_int32 __fastcall operator%(const int value) const {
				return e_int32(algo_t_inst(_value) % value);
			}

			__forceinline e_int32 __fastcall operator^(const int value) const {
				return e_int32(algo_t_inst(_value) ^ value);
			}

			__forceinline e_int32 __fastcall operator<<(const int value) const {
				return e_int32(algo_t_inst(_value) << value);
			}

			__forceinline e_int32 __fastcall operator>>(const int value) const {
				return e_int32(algo_t_inst(_value) >> value);
			}

			__forceinline e_int32& __fastcall operator+=(const int value) {
				this->_value = algo_t_inst(static_cast<int>(algo_t_inst(_value) + value));
				return *this;
			}

			__forceinline e_int32& __fastcall operator-=(const int value) {
				this->_value = algo_t_inst(static_cast<int>(algo_t_inst(_value) - value));
				return *this;
			}

			__forceinline e_int32& __fastcall operator*=(const int value) {
				this->_value = algo_t_inst(static_cast<int>(algo_t_inst(_value) * value));
				return *this;
			}

			__forceinline e_int32& __fastcall operator/=(const int value) {
				this->_value = algo_t_inst(static_cast<int>(algo_t_inst(_value) / value));
				return *this;
			}

			__forceinline e_int32& __fastcall operator%=(const int value) {
				this->_value = algo_t_inst(static_cast<int>(algo_t_inst(_value) % value));
				return *this;
			}

			__forceinline e_int32& __fastcall operator^=(const int value) {
				this->_value = algo_t_inst(static_cast<int>(algo_t_inst(_value) ^ value));
				return *this;
			}

			__forceinline e_int32& __fastcall operator&=(const int value) {
				this->_value = algo_t_inst(static_cast<int>(algo_t_inst(_value) & value));
				return *this;
			}

			__forceinline e_int32& __fastcall operator|=(const int value) {
				this->_value = algo_t_inst(static_cast<int>(algo_t_inst(_value) | value));
				return *this;
			}

			__forceinline e_int32& __fastcall operator<<=(const int value) {
				this->_value = algo_t_inst(static_cast<int>(algo_t_inst(_value) << value));
				return *this;
			}

			__forceinline e_int32& __fastcall operator>>=(const int value) {
				this->_value = algo_t_inst(static_cast<int>(algo_t_inst(_value) >> value));
				return *this;
			}

			__forceinline e_int32& __fastcall operator=(const int value) {
				_value = algo_t_inst(value);
				return *this;
			}

			__forceinline __fastcall operator int() const {
				return algo_t_inst(_value);
			}

	#pragma endregion
		};

		class e_uint32 {
		private:

	#pragma region Encrypted value

			unsigned int _value;

	#pragma endregion

		public:

	#pragma region CTOR

			__forceinline __fastcall e_uint32(unsigned int value = 0) {
				_value = algo_t_inst(value);
			}

	#pragma endregion

	#pragma region Accessors

			__forceinline unsigned int __fastcall get() const {
				return algo_t_inst(_value);
			}

			__forceinline void __fastcall set(unsigned int value) {
				_value = algo_t_inst(value);
			}

	#pragma endregion

	#pragma region Operators

			__forceinline e_uint32 __fastcall operator+(const unsigned int value) const {
				return e_uint32(algo_t_inst(_value) + value);
			};

			__forceinline e_uint32 __fastcall operator-(const unsigned int value) const {
				return e_uint32(algo_t_inst(_value) - value);
			}

			__forceinline e_uint32 __fastcall operator/(const unsigned int value) const {
				return e_uint32(algo_t_inst(_value) / value);
			}

			__forceinline e_uint32 __fastcall operator*(const unsigned int value) const {
				return e_uint32(algo_t_inst(_value) * value);
			}

			__forceinline e_uint32 __fastcall operator&(const unsigned int value) const {
				return e_uint32(algo_t_inst(_value) & value);
			}

			__forceinline e_uint32 __fastcall operator|(const unsigned int value) const {
				return e_uint32(algo_t_inst(_value) | value);
			}

			__forceinline e_uint32 __fastcall operator%(const unsigned int value) const {
				return e_uint32(algo_t_inst(_value) % value);
			}

			__forceinline e_uint32 __fastcall operator^(const unsigned int value) const {
				return e_uint32(algo_t_inst(_value) ^ value);
			}

			__forceinline e_uint32 __fastcall operator<<(const unsigned int value) const {
				return e_uint32(algo_t_inst(_value) << value);
			}

			__forceinline e_uint32 __fastcall operator>>(const unsigned int value) const {
				return e_uint32(algo_t_inst(_value) >> value);
			}

			__forceinline e_uint32& __fastcall operator+=(const unsigned int value) {
				this->_value = algo_t_inst(static_cast<int>(algo_t_inst(_value) + value));
				return *this;
			}

			__forceinline e_uint32& __fastcall operator-=(const unsigned int value) {
				this->_value = algo_t_inst(static_cast<int>(algo_t_inst(_value) - value));
				return *this;
			}

			__forceinline e_uint32& __fastcall operator*=(const unsigned int value) {
				this->_value = algo_t_inst(static_cast<int>(algo_t_inst(_value) * value));
				return *this;
			}

			__forceinline e_uint32& __fastcall operator/=(const unsigned int value) {
				this->_value = algo_t_inst(static_cast<int>(algo_t_inst(_value) / value));
				return *this;
			}

			__forceinline e_uint32& __fastcall operator%=(const unsigned int value) {
				this->_value = algo_t_inst(static_cast<int>(algo_t_inst(_value) % value));
				return *this;
			}

			__forceinline e_uint32& __fastcall operator^=(const unsigned int value) {
				this->_value = algo_t_inst(static_cast<int>(algo_t_inst(_value) ^ value));
				return *this;
			}

			__forceinline e_uint32& __fastcall operator&=(const unsigned int value) {
				this->_value = algo_t_inst(static_cast<int>(algo_t_inst(_value) & value));
				return *this;
			}

			__forceinline e_uint32& __fastcall operator|=(const unsigned int value) {
				this->_value = algo_t_inst(static_cast<int>(algo_t_inst(_value) | value));
				return *this;
			}

			__forceinline e_uint32& __fastcall operator<<=(const unsigned int value) {
				this->_value = algo_t_inst(static_cast<int>(algo_t_inst(_value) << value));
				return *this;
			}

			__forceinline e_uint32& __fastcall operator>>=(const unsigned int value) {
				this->_value = algo_t_inst(static_cast<int>(algo_t_inst(_value) >> value));
				return *this;
			}

			__forceinline e_uint32& __fastcall operator=(const unsigned int value) {
				_value = algo_t_inst(value);
				return *this;
			}

			__forceinline __fastcall operator int() const {
				return algo_t_inst(_value);
			}

	#pragma endregion
		};

	#pragma endregion

	#pragma region 64-bit

		class e_int64 {
		private:

	#pragma region Encrypted value

			long long _value;

	#pragma endregion

		public:

	#pragma region CTOR

			__forceinline __fastcall e_int64(long long value = 0) {
				_value = algo_t_inst(value);
			}

	#pragma endregion

	#pragma region Accessors

			__forceinline long long __fastcall get() const {
				return algo_t_inst(_value);
			}

			__forceinline void __fastcall set(long long value) {
				_value = algo_t_inst(value);
			}

	#pragma endregion

	#pragma region Operators

			__forceinline e_int64 __fastcall operator+(const long long value) const {
				return e_int64(algo_t_inst(_value) + value);
			};

			__forceinline e_int64 __fastcall operator-(const long long value) const {
				return e_int64(algo_t_inst(_value) - value);
			}

			__forceinline e_int64 __fastcall operator/(const long long value) const {
				return e_int64(algo_t_inst(_value) / value);
			}

			__forceinline e_int64 __fastcall operator*(const long long value) const {
				return e_int64(algo_t_inst(_value) * value);
			}

			__forceinline e_int64 __fastcall operator&(const long long value) const {
				return e_int64(algo_t_inst(_value) & value);
			}

			__forceinline e_int64 __fastcall operator|(const long long value) const {
				return e_int64(algo_t_inst(_value) | value);
			}

			__forceinline e_int64 __fastcall operator%(const long long value) const {
				return e_int64(algo_t_inst(_value) % value);
			}

			__forceinline e_int64 __fastcall operator^(const long long value) const {
				return e_int64(algo_t_inst(_value) ^ value);
			}

			__forceinline e_int64 __fastcall operator<<(const long long value) const {
				return e_int64(algo_t_inst(_value) << value);
			}

			__forceinline e_int64 __fastcall operator>>(const long long value) const {
				return e_int64(algo_t_inst(_value) >> value);
			}

			__forceinline e_int64& __fastcall operator+=(const long long value) {
				this->_value = algo_t_inst(static_cast<int>(algo_t_inst(_value) + value));
				return *this;
			}

			__forceinline e_int64& __fastcall operator-=(const long long value) {
				this->_value = algo_t_inst(static_cast<int>(algo_t_inst(_value) - value));
				return *this;
			}

			__forceinline e_int64& __fastcall operator*=(const long long value) {
				this->_value = algo_t_inst(static_cast<int>(algo_t_inst(_value) * value));
				return *this;
			}

			__forceinline e_int64& __fastcall operator/=(const long long value) {
				this->_value = algo_t_inst(static_cast<int>(algo_t_inst(_value) / value));
				return *this;
			}

			__forceinline e_int64& __fastcall operator%=(const long long value) {
				this->_value = algo_t_inst(static_cast<int>(algo_t_inst(_value) % value));
				return *this;
			}

			__forceinline e_int64& __fastcall operator^=(const long long value) {
				this->_value = algo_t_inst(static_cast<int>(algo_t_inst(_value) ^ value));
				return *this;
			}

			__forceinline e_int64& __fastcall operator&=(const long long value) {
				this->_value = algo_t_inst(static_cast<int>(algo_t_inst(_value) & value));
				return *this;
			}

			__forceinline e_int64& __fastcall operator|=(const long long value) {
				this->_value = algo_t_inst(static_cast<int>(algo_t_inst(_value) | value));
				return *this;
			}

			__forceinline e_int64& __fastcall operator<<=(const long long value) {
				this->_value = algo_t_inst(static_cast<int>(algo_t_inst(_value) << value));
				return *this;
			}

			__forceinline e_int64& __fastcall operator>>=(const long long value) {
				this->_value = algo_t_inst(static_cast<int>(algo_t_inst(_value) >> value));
				return *this;
			}

			__forceinline e_int64& __fastcall operator=(const long long value) {
				_value = algo_t_inst(value);
				return *this;
			}

			__forceinline __fastcall operator int() const {
				return algo_t_inst(_value);
			}

	#pragma endregion
		};

		class e_uint64 {
		private:

	#pragma region Encrypted value

			unsigned long long _value;

	#pragma endregion

		public:

	#pragma region CTOR

			__forceinline __fastcall e_uint64(unsigned long long value = 0) {
				_value = algo_t_inst(value);
			}

	#pragma endregion

	#pragma region Accessors

			__forceinline unsigned long long __fastcall get() const {
				return algo_t_inst(_value);
			}

			__forceinline void __fastcall set(unsigned long long value) {
				_value = algo_t_inst(value);
			}

	#pragma endregion

	#pragma region Operators

			__forceinline e_uint64 __fastcall operator+(const unsigned long long value) const {
				return e_uint64(algo_t_inst(_value) + value);
			};

			__forceinline e_uint64 __fastcall operator-(const unsigned long long value) const {
				return e_uint64(algo_t_inst(_value) - value);
			}

			__forceinline e_uint64 __fastcall operator/(const unsigned long long value) const {
				return e_uint64(algo_t_inst(_value) / value);
			}

			__forceinline e_uint64 __fastcall operator*(const unsigned long long value) const {
				return e_uint64(algo_t_inst(_value) * value);
			}

			__forceinline e_uint64 __fastcall operator&(const unsigned long long value) const {
				return e_uint64(algo_t_inst(_value) & value);
			}

			__forceinline e_uint64 __fastcall operator|(const unsigned long long value) const {
				return e_uint64(algo_t_inst(_value) | value);
			}

			__forceinline e_uint64 __fastcall operator%(const unsigned long long value) const {
				return e_uint64(algo_t_inst(_value) % value);
			}

			__forceinline e_uint64 __fastcall operator^(const unsigned long long value) const {
				return e_uint64(algo_t_inst(_value) ^ value);
			}

			__forceinline e_uint64 __fastcall operator<<(const unsigned long long value) const {
				return e_uint64(algo_t_inst(_value) << value);
			}

			__forceinline e_uint64 __fastcall operator>>(const unsigned long long value) const {
				return e_uint64(algo_t_inst(_value) >> value);
			}

			__forceinline e_uint64& __fastcall operator+=(const unsigned long long value) {
				this->_value = algo_t_inst(static_cast<int>(algo_t_inst(_value) + value));
				return *this;
			}

			__forceinline e_uint64& __fastcall operator-=(const unsigned long long value) {
				this->_value = algo_t_inst(static_cast<int>(algo_t_inst(_value) - value));
				return *this;
			}

			__forceinline e_uint64& __fastcall operator*=(const unsigned long long value) {
				this->_value = algo_t_inst(static_cast<int>(algo_t_inst(_value) * value));
				return *this;
			}

			__forceinline e_uint64& __fastcall operator/=(const unsigned long long value) {
				this->_value = algo_t_inst(static_cast<int>(algo_t_inst(_value) / value));
				return *this;
			}

			__forceinline e_uint64& __fastcall operator%=(const unsigned long long value) {
				this->_value = algo_t_inst(static_cast<int>(algo_t_inst(_value) % value));
				return *this;
			}

			__forceinline e_uint64& __fastcall operator^=(const unsigned long long value) {
				this->_value = algo_t_inst(static_cast<int>(algo_t_inst(_value) ^ value));
				return *this;
			}

			__forceinline e_uint64& __fastcall operator&=(const unsigned long long value) {
				this->_value = algo_t_inst(static_cast<int>(algo_t_inst(_value) & value));
				return *this;
			}

			__forceinline e_uint64& __fastcall operator|=(const unsigned long long value) {
				this->_value = algo_t_inst(static_cast<int>(algo_t_inst(_value) | value));
				return *this;
			}

			__forceinline e_uint64& __fastcall operator<<=(const unsigned long long value) {
				this->_value = algo_t_inst(static_cast<int>(algo_t_inst(_value) << value));
				return *this;
			}

			__forceinline e_uint64& __fastcall operator>>=(const unsigned long long value) {
				this->_value = algo_t_inst(static_cast<int>(algo_t_inst(_value) >> value));
				return *this;
			}

			__forceinline e_uint64& __fastcall operator=(const unsigned long long value) {
				_value = algo_t_inst(value);
				return *this;
			}

			__forceinline __fastcall operator int() const {
				return algo_t_inst(_value);
			}

	#pragma endregion
		};

	#pragma endregion

	#pragma endregion

	#pragma region Floating Point

	#pragma region Calling Convention Preprocessor

		/* specify vectorcall if the project is compiled using extended types as this is better than fastcall for floating point numbers */
	#ifndef __fpcall

	#ifdef __SSE2__

	#define __fpcall __vectorcall

	#else

	#define __fpcall __fastcall

	#endif

	#pragma endregion

	#endif

	#pragma endregion

	#pragma region 32-bit

		class e_float {
		private:

			float _value;

		public:

	#pragma region CTOR

			__forceinline __fpcall e_float(float value) {
				_value = algo_t_inst(value);
			}

	#pragma endregion

	#pragma region Accessors

			__forceinline float __cdecl get() const {
				return algo_t_inst(_value);
			}

			__forceinline void __fpcall set(float value) {
				_value = algo_t_inst(value);
			}

	#pragma endregion

	#pragma region Operators

			__forceinline e_float __fpcall operator+(const float value) const {
				return e_float(algo_t_inst(_value) + value);
			};

			__forceinline e_float __fpcall operator-(const float value) const {
				return e_float(algo_t_inst(_value) - value);
			}

			__forceinline e_float __fpcall operator/(const float value) const {
				return e_float(algo_t_inst(_value) / value);
			}

			__forceinline e_float __fpcall operator*(const float value) const {
				return e_float(algo_t_inst(_value) * value);
			}

			__forceinline e_float __fpcall operator^(const float value) const {
				return e_float(XOR_FORCE(algo_t_inst(_value), value));
			}

			__forceinline e_float& __fpcall operator+=(const float value) {
				_value = algo_t_inst(algo_t_inst(_value) + value);
				return *this;
			}

			__forceinline e_float& __fpcall operator-=(const float value) {
				_value = algo_t_inst(algo_t_inst(_value) - value);
				return *this;
			}

			__forceinline e_float& __fpcall operator*=(const float value) {
				_value = algo_t_inst(algo_t_inst(_value) * value);
				return *this;
			}

			__forceinline e_float& __fpcall operator/=(const float value) {
				_value = algo_t_inst(algo_t_inst(_value) / value);
				return *this;
			}

			__forceinline e_float& __fpcall operator^=(const float value) {
				_value = algo_t_inst(XOR_FORCE(algo_t_inst(_value), value));
				return *this;
			}

			__forceinline e_float& __fpcall operator=(const float value) {
				_value = algo_t_inst(value);
				return *this;
			}

			__forceinline  __cdecl operator float() const {
				return get();
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

			__forceinline __fpcall e_double(double value) {
				_value = algo_t_inst(value);
			}

	#pragma endregion

	#pragma region Accessors

			__forceinline double __cdecl get() const {
				return algo_t_inst(_value);
			}

			__forceinline void __fpcall set(double value) {
				_value = algo_t_inst(value);
			}

	#pragma endregion

	#pragma region Operators

			__forceinline e_double __fpcall operator+(const double value) const {
				return e_double(algo_t_inst(_value) + value);
			};

			__forceinline e_double __fpcall operator-(const double value) const {
				return e_double(algo_t_inst(_value) - value);
			}

			__forceinline e_double __fpcall operator/(const double value) const {
				return e_double(algo_t_inst(_value) / value);
			}

			__forceinline e_double __fpcall operator*(const double value) const {
				return e_double(algo_t_inst(_value) * value);
			}

			__forceinline e_double __fpcall operator^(const double value) const {
				return e_double(XOR_FORCE(algo_t_inst(_value), value));
			}

			__forceinline e_double& __fpcall operator+=(const double value) {
				_value = algo_t_inst(algo_t_inst(_value) + value);
				return *this;
			}

			__forceinline e_double& __fpcall operator-=(const double value) {
				_value = algo_t_inst(algo_t_inst(_value) - value);
				return *this;
			}

			__forceinline e_double& __fpcall operator*=(const double value) {
				_value = algo_t_inst(algo_t_inst(_value) * value);
				return *this;
			}

			__forceinline e_double& __fpcall operator/=(const double value) {
				_value = algo_t_inst(algo_t_inst(_value) / value);
				return *this;
			}

			__forceinline e_double& __fpcall operator^=(const double value) {
				_value = algo_t_inst(XOR_FORCE(algo_t_inst(_value), value));
				return *this;
			}

			__forceinline e_double& __fpcall operator=(const double value) {
				_value = algo_t_inst(value);
				return *this;
			}

			__forceinline  __cdecl operator double() const {
				return get();
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

			__forceinline __vectorcall e_m128(__m128 value) {
				_value = algo_t_inst(value);
			}

	#pragma endregion

	#pragma region Accessors
			__forceinline __m128 __cdecl get() const {
				return algo_t_inst(_value);
			}
			__forceinline void __vectorcall set(__m128 value) {
				_value = algo_t_inst(value);
			}
	#pragma endregion

	#pragma region Operators
	#ifdef __clang__ // msvc does not support math operators on vector types

			__forceinline e_m128 __vectorcall operator+(const __m128 value) const {
				return e_m128(algo_t_inst(_value) + value);
			};

			__forceinline e_m128 __vectorcall operator-(const __m128 value) const {
				return e_m128(algo_t_inst(_value) - value);
			}

			__forceinline e_m128 __vectorcall operator/(const __m128 value) const {
				return e_m128((const __m128)algo_t_inst(_value) / value);
			}

			__forceinline e_m128 __vectorcall operator*(const __m128 value) const {
				return e_m128(algo_t_inst(_value) * value);
			}

	#endif

			__forceinline e_m128 __vectorcall operator^(const __m128 value) const {
				return e_m128(XOR_FORCE(algo_t_inst(_value), value));
			}

	#ifdef __clang__

			__forceinline e_m128& __vectorcall operator+=(const __m128 value) {
				_value = algo_t_inst(algo_t_inst(value) + value);
				return *this;
			}

			__forceinline e_m128& __vectorcall operator-=(const __m128 value) {
				_value = algo_t_inst(algo_t_inst(_value) - value);
				return *this;
			}

			__forceinline e_m128& __vectorcall operator*=(const __m128 value) {
				_value = algo_t_inst(algo_t_inst(_value) * value);
				return *this;
			}

			__forceinline e_m128& __vectorcall operator/=(const __m128 value) {
				_value = algo_t_inst(algo_t_inst(_value) / value);
				return *this;
			}

	#endif

			__forceinline e_m128& __vectorcall operator^=(const __m128 value) {
				_value = algo_t_inst(XOR_FORCE(algo_t_inst(_value), value));
				return *this;
			}

			__forceinline e_m128& __vectorcall operator=(const __m128 value) {
				_value = algo_t_inst(value);
				return *this;
			}

			__forceinline __cdecl operator __m128() const {
				return get();
			}

	#pragma endregion
		};

	#ifdef __SSE2__

		class e_m128i {
		private:

			__m128i _value;

		public:

	#pragma region CTOR
			__forceinline __vectorcall e_m128i(__m128i value) {
				_value = algo_t_inst(value);
			}
	#pragma endregion

	#pragma region Accessors
			__forceinline __m128i __cdecl get() const {
				return algo_t_inst(_value);
			}
			__forceinline void __vectorcall set(__m128i value) {
				_value = algo_t_inst(value);
			}
	#pragma endregion

	#pragma region Operators

	#ifdef __clang__ // msvc does not support math operators on vector types

			__forceinline e_m128i __vectorcall operator+(const __m128i value) const {
				return e_m128i(algo_t_inst(_value) + value);
			};

			__forceinline e_m128i __vectorcall operator-(const __m128i value) const {
				return e_m128i(algo_t_inst(_value) - value);
			}

			__forceinline e_m128i __vectorcall operator/(const __m128i value) const {
				return e_m128i((const __m128i)algo_t_inst(_value) / value);
			}

			__forceinline e_m128i __vectorcall operator*(const __m128i value) const {
				return e_m128i(algo_t_inst(_value) * value);
			}

	#endif

			__forceinline e_m128i __vectorcall operator^(const __m128i value) const {
				return e_m128i(XOR_FORCE(algo_t_inst(_value), value));
			}

	#ifdef __clang__

			__forceinline e_m128i& __vectorcall operator+=(const __m128i value) {
				_value = algo_t_inst(algo_t_inst(value) + value);
				return *this;
			}

			__forceinline e_m128i& __vectorcall operator-=(const __m128i value) {
				_value = algo_t_inst(algo_t_inst(_value) - value);
				return *this;
			}

			__forceinline e_m128i& __vectorcall operator*=(const __m128i value) {
				_value = algo_t_inst(algo_t_inst(_value) * value);
				return *this;
			}

			__forceinline e_m128i& __vectorcall operator/=(const __m128i value) {
				_value = algo_t_inst(algo_t_inst(_value) / value);
				return *this;
			}

	#endif

			__forceinline e_m128i& __vectorcall operator^=(const __m128i value) {
				_value = algo_t_inst(XOR_FORCE(algo_t_inst(_value), value));
				return *this;
			}

			__forceinline e_m128i& __vectorcall operator=(const __m128i value) {
				_value = algo_t_inst(value);
				return *this;
			}

			__forceinline __cdecl operator __m128i() const {
				return get();
			}

	#pragma endregion
		};

		class e_m128d {
		private:

			__m128d _value;

		public:

	#pragma region CTOR

			__forceinline __vectorcall e_m128d(__m128d value) {
				_value = algo_t_inst(value);
			}

	#pragma endregion

	#pragma region Accessors
			__forceinline __m128d __cdecl get() const {
				return algo_t_inst(_value);
			}
			__forceinline void __vectorcall set(__m128d value) {
				_value = algo_t_inst(value);
			}
	#pragma endregion

	#pragma region Operators
	#ifdef __clang__ // msvc does not support math operators on vector types

			__forceinline e_m128d __vectorcall operator+(const __m128d value) const {
				return e_m128d(algo_t_inst(_value) + value);
			};

			__forceinline e_m128d __vectorcall operator-(const __m128d value) const {
				return e_m128d(algo_t_inst(_value) - value);
			}

			__forceinline e_m128d __vectorcall operator/(const __m128d value) const {
				return e_m128d((const __m128d)algo_t_inst(_value) / value);
			}

			__forceinline e_m128d __vectorcall operator*(const __m128d value) const {
				return e_m128d(algo_t_inst(_value) * value);
			}

	#endif

			__forceinline e_m128d __vectorcall operator^(const __m128d value) const {
				return e_m128d(XOR_FORCE(algo_t_inst(_value), value));
			}

	#ifdef __clang__

			__forceinline e_m128d& __vectorcall operator+=(const __m128d value) {
				_value = algo_t_inst(algo_t_inst(value) + value);
				return *this;
			}

			__forceinline e_m128d& __vectorcall operator-=(const __m128d value) {
				_value = algo_t_inst(algo_t_inst(_value) - value);
				return *this;
			}

			__forceinline e_m128d& __vectorcall operator*=(const __m128d value) {
				_value = algo_t_inst(algo_t_inst(_value) * value);
				return *this;
			}

			__forceinline e_m128d& __vectorcall operator/=(const __m128d value) {
				_value = algo_t_inst(algo_t_inst(_value) / value);
				return *this;
			}

	#endif

			__forceinline e_m128d& __vectorcall operator^=(const __m128d value) {
				_value = algo_t_inst(XOR_FORCE(algo_t_inst(_value), value));
				return *this;
			}

			__forceinline e_m128d& __vectorcall operator=(const __m128d value) {
				_value = algo_t_inst(value);
				return *this;
			}

			__forceinline __cdecl operator __m128d() const {
				return get();
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
			__forceinline __vectorcall e_m256(__m256 value) {
				_value = algo_t_inst(value);
			}
	#pragma endregion

	#pragma region Accessors
			__forceinline __m256 __cdecl get() const {
				return algo_t_inst(_value);
			}
			__forceinline void __vectorcall set(__m256 value) {
				_value = algo_t_inst(value);
			}
	#pragma endregion

	#pragma region Operators

	#ifdef __clang__ // msvc does not support math operators on vector types

			__forceinline e_m256 __vectorcall operator+(const __m256 value) const {
				return e_m256(algo_t_inst(_value) + value);
			};

			__forceinline e_m256 __vectorcall operator-(const __m256 value) const {
				return e_m256(algo_t_inst(_value) - value);
			}

			__forceinline e_m256 __vectorcall operator/(const __m256 value) const {
				return e_m256((const __m256)algo_t_inst(_value) / value);
			}

			__forceinline e_m256 __vectorcall operator*(const __m256 value) const {
				return e_m256(algo_t_inst(_value) * value);
			}

	#endif

			__forceinline e_m256 __vectorcall operator^(const __m256 value) const {
				return e_m256(XOR_FORCE(algo_t_inst(_value), value));
			}

	#ifdef __clang__

			__forceinline e_m256& __vectorcall operator+=(const __m256 value) {
				_value = algo_t_inst(algo_t_inst(value) + value);
				return *this;
			}

			__forceinline e_m256& __vectorcall operator-=(const __m256 value) {
				_value = algo_t_inst(algo_t_inst(_value) - value);
				return *this;
			}

			__forceinline e_m256& __vectorcall operator*=(const __m256 value) {
				_value = algo_t_inst(algo_t_inst(_value) * value);
				return *this;
			}

			__forceinline e_m256& __vectorcall operator/=(const __m256 value) {
				_value = algo_t_inst(algo_t_inst(_value) / value);
				return *this;
			}

	#endif

			__forceinline e_m256& __vectorcall operator^=(const __m256 value) {
				_value = algo_t_inst(XOR_FORCE(algo_t_inst(_value), value));
				return *this;
			}

			__forceinline e_m256& __vectorcall operator=(const __m256 value) {
				_value = algo_t_inst(value);
				return *this;
			}

			__forceinline __cdecl operator __m256() const {
				return get();
			}

	#pragma endregion
		};

		class e_m256i {
		private:

			__m256i _value;

		public:

	#pragma region CTOR
			__forceinline __vectorcall e_m256i(__m256i value) {
				_value = algo_t_inst(value);
			}
	#pragma endregion

	#pragma region Accessors
			__forceinline __m256i __cdecl get() const {
				return algo_t_inst(_value);
			}
			__forceinline void __vectorcall set(__m256i value) {
				_value = algo_t_inst(value);
			}
	#pragma endregion

	#pragma region Operators
	#ifdef __clang__ // msvc does not support math operators on vector types

			__forceinline e_m256i __vectorcall operator+(const __m256i value) const {
				return e_m256i(algo_t_inst(_value) + value);
			};

			__forceinline e_m256i __vectorcall operator-(const __m256i value) const {
				return e_m256i(algo_t_inst(_value) - value);
			}

			__forceinline e_m256i __vectorcall operator/(const __m256i value) const {
				return e_m256i((const __m256i)algo_t_inst(_value) / value);
			}

			__forceinline e_m256i __vectorcall operator*(const __m256i value) const {
				return e_m256i(algo_t_inst(_value) * value);
			}

	#endif

			__forceinline e_m256i __vectorcall operator^(const __m256i value) const {
				return e_m256i(XOR_FORCE(algo_t_inst(_value), value));
			}

	#ifdef __clang__

			__forceinline e_m256i& __vectorcall operator+=(const __m256i value) {
				_value = algo_t_inst(algo_t_inst(value) + value);
				return *this;
			}

			__forceinline e_m256i& __vectorcall operator-=(const __m256i value) {
				_value = algo_t_inst(algo_t_inst(_value) - value);
				return *this;
			}

			__forceinline e_m256i& __vectorcall operator*=(const __m256i value) {
				_value = algo_t_inst(algo_t_inst(_value) * value);
				return *this;
			}

			__forceinline e_m256i& __vectorcall operator/=(const __m256i value) {
				_value = algo_t_inst(algo_t_inst(_value) / value);
				return *this;
			}

	#endif

			__forceinline e_m256i& __vectorcall operator^=(const __m256i value) {
				_value = algo_t_inst(XOR_FORCE(algo_t_inst(_value), value));
				return *this;
			}

			__forceinline e_m256i& __vectorcall operator=(const __m256i value) {
				_value = algo_t_inst(value);
				return *this;
			}

			__forceinline __cdecl operator __m256i() const {
				return get();
			}

	#pragma endregion
		};

		class e_m256d {
		private:

			__m256d _value;

		public:

	#pragma region CTOR

			__forceinline __vectorcall e_m256d(__m256d value) {
				_value = algo_t_inst(value);
			}

	#pragma endregion

	#pragma region Accessors
			__forceinline __m256d __cdecl get() const {
				return algo_t_inst(_value);
			}
			__forceinline void __vectorcall set(__m256d value) {
				_value = algo_t_inst(value);
			}
	#pragma endregion

	#pragma region Operators

	#ifdef __clang__ // msvc does not support math operators on vector types

			__forceinline e_m256d __vectorcall operator+(const __m256d value) const {
				return e_m256d(algo_t_inst(_value) + value);
			};

			__forceinline e_m256d __vectorcall operator-(const __m256d value) const {
				return e_m256d(algo_t_inst(_value) - value);
			}

			__forceinline e_m256d __vectorcall operator/(const __m256d value) const {
				return e_m256d((const __m256d)algo_t_inst(_value) / value);
			}

			__forceinline e_m256d __vectorcall operator*(const __m256d value) const {
				return e_m256d(algo_t_inst(_value) * value);
			}

	#endif

			__forceinline e_m256d __vectorcall operator^(const __m256d value) const {
				return e_m256d(XOR_FORCE(algo_t_inst(_value), value));
			}

	#ifdef __clang__

			__forceinline e_m256d& __vectorcall operator+=(const __m256d value) {
				_value = algo_t_inst(algo_t_inst(value) + value);
				return *this;
			}

			__forceinline e_m256d& __vectorcall operator-=(const __m256d value) {
				_value = algo_t_inst(algo_t_inst(_value) - value);
				return *this;
			}

			__forceinline e_m256d& __vectorcall operator*=(const __m256d value) {
				_value = algo_t_inst(algo_t_inst(_value) * value);
				return *this;
			}

			__forceinline e_m256d& __vectorcall operator/=(const __m256d value) {
				_value = algo_t_inst(algo_t_inst(_value) / value);
				return *this;
			}

	#endif

			__forceinline e_m256d& __vectorcall operator^=(const __m256d value) {
				_value = algo_t_inst(XOR_FORCE(algo_t_inst(_value), value));
				return *this;
			}

			__forceinline e_m256d& __vectorcall operator=(const __m256d value) {
				_value = algo_t_inst(value);
				return *this;
			}

			__forceinline __cdecl operator __m256d() const {
				return get();
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

			__forceinline __cdecl e_string(const std::string& value) {
				_value = algo_str_inst(value);
			}

			__forceinline __fastcall e_string(const char* value = "") {
				if (!is_init) {
					init_constants();
				}

				_value = algo_str_inst(std::string(value));
			}

	#pragma endregion

	#pragma region Accessors

			__forceinline std::string __cdecl get() const {
				return algo_str_inst(std::string(_value));
			}

			__forceinline void __cdecl set(const std::string& value) {
				_value = algo_str_inst(value);
			}

			__forceinline e_string __cdecl operator+(const std::string& value) const {
				return e_string(algo_str_inst(std::string(_value)) + value);
			};

			__forceinline e_string& __cdecl operator+=(const std::string& value) {
				_value = algo_str_inst(static_cast<std::string>(algo_str_inst(_value) + value));
				return *this;
			}

			__forceinline e_string& __cdecl operator=(const std::string& value) {
				set(value);
				return *this;
			}

			__forceinline __cdecl operator std::string() const {
				return get();
			}

			__forceinline __cdecl ~e_string() {
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

	#pragma endregion

	#pragma region Wide String

		class e_wstring {
		private:

	#pragma region Encrypted value

			std::wstring _value = L"";

	#pragma endregion

		public:

	#pragma region CTOR

			__forceinline __cdecl e_wstring(const std::wstring& value) {
				_value = algo_wstr_inst(value);
			}

			__forceinline __fastcall e_wstring(const wchar_t* value = L"") {
				if (!is_init) {
					init_constants();
				}

				_value = algo_wstr_inst(std::wstring(value));
			}

			__forceinline __cdecl e_wstring() {
				_value = L"";
			}

	#pragma endregion

	#pragma region Accessors

			__forceinline std::wstring __cdecl get() const {
				return algo_wstr_inst(std::wstring(_value));
			}

			__forceinline void __cdecl set(const std::wstring& value) {
				_value = algo_wstr_inst(value);
			}

			__forceinline void __fastcall reserve(unsigned long count) {
				_value.reserve(count);
			}

			__forceinline bool __cdecl empty() const {
				return _value.empty();
			}

			__forceinline e_wstring __cdecl operator+(const std::wstring& value) const {
				return e_wstring(algo_wstr_inst(_value) + value);
			};

			__forceinline e_wstring& __cdecl operator+=(const std::wstring& value) {
				_value = algo_wstr_inst(static_cast<std::wstring>(algo_wstr_inst(_value) + value));
				return *this;
			}

			__forceinline e_wstring& __cdecl operator=(const std::wstring& value) {
				set(value);
				return *this;
			}
			// to-do use a subscript proxy to allow get set access through indexing
			__forceinline wchar_t& __fastcall operator[](const int index) {
				return algo_wstr_inst(_value)[index];
			}

			__forceinline __cdecl operator std::wstring() const {
				return algo_wstr_inst(_value);
			}

			__forceinline __cdecl ~e_wstring() {
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

				if (!local_alloc)
					throw std::bad_alloc();

				RtlZeroMemory(local_alloc, size);

				algo(local_alloc, size);
			}

			__forceinline __cdecl e_malloc() {
				if (!is_init) {
					init_constants();
				}
			}

	#pragma endregion

	#pragma region Get accessors

			__forceinline void* __fastcall get() {
				return algo_inst(local_alloc, alloc_size);
			}

			__forceinline void* __fastcall get(uintptr_t pos, size_t length) {
				auto dec_alloc = reinterpret_cast<uint8_t*>(get());

				auto get_alloc = malloc(length);

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

			__forceinline void* __cdecl get_data_pointer() {
				return local_alloc;
			}

			__forceinline size_t __cdecl get_data_size() {
				return alloc_size;
			}

	#pragma endregion

	#pragma region Set accessors

			//WARNING: appending length to the allocation here will cause exceptions / UB
			__forceinline void __fastcall set(void* src, uintptr_t pos, size_t length, bool free_src = false) {
				auto dec_alloc = get();

				memcpy(&reinterpret_cast<unsigned char*>(dec_alloc)[pos], src, length);

				auto enc_alloc = algo_inst(dec_alloc, length);
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

				auto enc_alloc = algo_inst(dec_alloc, alloc_size);
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

				auto enc_alloc = algo_inst(dec_alloc, alloc_size);
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

				auto enc_alloc = algo_inst(src, length);

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

				auto enc_alloc = algo_inst(n_local_alloc, size);
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
				set(0x0000000000000000ULL, 0x0ui8, alloc_size);
			}

	#pragma endregion

	#pragma region Operators

			__forceinline e_malloc& __fastcall operator=(const std::vector<uint8_t>& value) {
				swap(const_cast<std::vector<uint8_t>*>(&value)->data(), value.size());

				return *this;
			}

			__forceinline __cdecl operator void* () const {
				return algo_inst(local_alloc, alloc_size);
			}

			template<typename T>
			__forceinline __cdecl operator T* () const {
				return reinterpret_cast<T*>(algo_inst(local_alloc, alloc_size));
			}

			index_proxy __fastcall operator[](size_t index) {
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

			__forceinline void __cdecl secure_destroy() {
				destroy(true);
			}
			__forceinline __cdecl ~e_malloc() {
				secure_destroy();
			}

	#pragma endregion
		};

	#pragma endregion

#ifdef _WIN64

		typedef e_uint64 e_uintptr_t;
		typedef e_uint64 e_size_t;

#else

		typedef e_uint32 e_uintptr_t;
		typedef e_uint32 e_size_t;

#endif

	};

}

#endif