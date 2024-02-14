/*
/***********************************************************************************************************************************************
*																											                                  *
*	QTYPE_ENC uses polyc32/64 runtime-encryption algorithm(s) to encrypt variables during runtime and provide severe control flow obfuscation *
*																											                                  *
************************************************************************************************************************************************
*/


#pragma region Header Guard

#ifndef QTYPE_ENC_H
#define QTYPE_ENC_H

#pragma endregion

#pragma region Imports

#pragma region std

#include <string>
#include <vector>
#include <memory>
#include <cstdlib>
#include <exception>

#pragma endregion

#pragma region qengine

#include "../../qbase/qdef.hpp"
#include "../../polyc/polyc.hpp"

#pragma endregion

#pragma endregion

#pragma region Preprocessor

#ifdef NDEBUG

#pragma optimize("", on)
#pragma inline_depth(255)
#pragma inline_recursion(on) 

#endif

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

#pragma endregion

#pragma region Using Directives

using namespace qengine::polyc;

#pragma endregion

namespace qengine{

	namespace qtype_enc {

	#pragma region Singleton

		extern bool is_init;

	#pragma endregion

	#pragma region Static Methods

		// this must be called once at application startup / or when you wish to begin using any type included in this header
		static void __fastcall init_constants() noexcept {
			if (!is_init) {
				is_init = true;

				polyc::polyc_init();
			}
		}

	#pragma endregion

	#pragma region Types

	#pragma region WORD

	#pragma region 8-bit

		class qe_int8 {

		private:

	#pragma region Encrypted value

			std::int8_t _value;

	#pragma endregion

		public:

	#pragma region CTOR

			__forceinline __fastcall qe_int8(const std::int8_t value = 0) noexcept {
				_value = algo_t_inst(value);
			}

	#pragma endregion

	#pragma region Accessors

			__forceinline std::int8_t __fastcall get() const noexcept {
				return algo_t_inst(_value);
			}

			__forceinline void __fastcall set(const std::int8_t value) noexcept {
				_value = algo_t_inst(value);
			}

	#pragma endregion

	#pragma region Operators

			__forceinline qe_int8 __fastcall operator+(const std::int8_t value) const noexcept {
				return qe_int8(algo_t_inst(_value) + value);
			};

			__forceinline qe_int8 __fastcall operator-(const std::int8_t value) const noexcept {
				return qe_int8(algo_t_inst(_value) - value);
			}

			__forceinline qe_int8 __fastcall operator/(const std::int8_t value) const noexcept {
				return qe_int8(algo_t_inst(_value) / value);
			}

			__forceinline qe_int8 __fastcall operator*(const std::int8_t value) const noexcept {
				return qe_int8(algo_t_inst(_value) * value);
			}

			__forceinline qe_int8 __fastcall operator&(const std::int8_t value) const noexcept {
				return qe_int8(algo_t_inst(_value) & value);
			}

			__forceinline qe_int8 __fastcall operator|(const std::int8_t value) const noexcept {
				return qe_int8(algo_t_inst(_value) | value);
			}

			__forceinline qe_int8 __fastcall operator%(const std::int8_t value) const noexcept {
				return qe_int8(algo_t_inst(_value) % value);
			}

			__forceinline qe_int8 __fastcall operator^(const std::int8_t value) const noexcept {
				return qe_int8(algo_t_inst(_value) ^ value);
			}

			__forceinline qe_int8 __fastcall operator<<(const std::int8_t value) const noexcept {
				return qe_int8(algo_t_inst(_value) << value);
			}

			__forceinline qe_int8 __fastcall operator>>(const std::int8_t value) const noexcept {
				return qe_int8(algo_t_inst(_value) >> value);
			}

			__forceinline qe_int8& __fastcall operator+=(const std::int8_t value) {
				this->_value = algo_t_inst(static_cast<std::int8_t>(algo_t_inst(_value) + value));
				return *this;
			}

			__forceinline qe_int8& __fastcall operator-=(const std::int8_t value) noexcept {
				this->_value = algo_t_inst(static_cast<std::int8_t>(algo_t_inst(_value) - value));
				return *this;
			}

			__forceinline qe_int8& __fastcall operator*=(const std::int8_t value) noexcept {
				this->_value = algo_t_inst(static_cast<std::int8_t>(algo_t_inst(_value) * value));
				return *this;
			}

			__forceinline qe_int8& __fastcall operator/=(const std::int8_t value) noexcept {
				this->_value = algo_t_inst(static_cast<std::int8_t>(algo_t_inst(_value) / value));
				return *this;
			}

			__forceinline qe_int8& __fastcall operator%=(const std::int8_t value) noexcept {
				this->_value = algo_t_inst(static_cast<std::int8_t>(algo_t_inst(_value) % value));
				return *this;
			}

			__forceinline qe_int8& __fastcall operator^=(const std::int8_t value) noexcept {
				this->_value = algo_t_inst(static_cast<std::int8_t>(algo_t_inst(_value) ^ value));
				return *this;
			}

			__forceinline qe_int8& __fastcall operator&=(const std::int8_t value) noexcept {
				this->_value = algo_t_inst(static_cast<std::int8_t>(algo_t_inst(_value) & value));
				return *this;
			}

			__forceinline qe_int8& __fastcall operator|=(const std::int8_t value) noexcept {
				this->_value = algo_t_inst(static_cast<std::int8_t>(algo_t_inst(_value) | value));
				return *this;
			}

			__forceinline qe_int8& __fastcall operator<<=(const std::int8_t value) noexcept {
				this->_value = algo_t_inst(static_cast<std::int8_t>(algo_t_inst(_value) << value));
				return *this;
			}

			__forceinline qe_int8& __fastcall operator>>=(const std::int8_t value) noexcept {
				this->_value = algo_t_inst(static_cast<std::int8_t>(algo_t_inst(_value) >> value));
				return *this;
			}

			__forceinline qe_int8& __fastcall operator=(const std::int8_t value) noexcept {
				_value = algo_t_inst(value);
				return *this;
			}

			__forceinline __fastcall operator std::int8_t() const noexcept {
				return algo_t_inst(_value);
			}

	#pragma endregion
		};

		class qe_uint8 {

		private:

	#pragma region Encrypted value

			std::uint8_t _value;

	#pragma endregion

		public:

	#pragma region CTOR

			__forceinline __fastcall qe_uint8(const std::uint8_t value = 0) noexcept {
				_value = algo_t_inst(value);
			}

	#pragma endregion

	#pragma region Accessors

			__forceinline std::uint8_t __fastcall get() const noexcept {
				return algo_t_inst(_value);
			}

			__forceinline void __fastcall set(const std::uint8_t value) noexcept {
				_value = algo_t_inst(value);
			}

	#pragma endregion

	#pragma region Operators

			__forceinline qe_uint8 __fastcall operator+(const std::uint8_t value) const noexcept {
				return qe_uint8(algo_t_inst(_value) + value);
			};

			__forceinline qe_uint8 __fastcall operator-(const std::uint8_t value) const noexcept {
				return qe_uint8(algo_t_inst(_value) - value);
			}

			__forceinline qe_uint8 __fastcall operator/(const std::uint8_t value) const noexcept {
				return qe_uint8(algo_t_inst(_value) / value);
			}

			__forceinline qe_uint8 __fastcall operator*(const std::uint8_t value) const noexcept {
				return qe_uint8(algo_t_inst(_value) * value);
			}

			__forceinline qe_uint8 __fastcall operator&(const std::uint8_t value) const noexcept {
				return qe_uint8(algo_t_inst(_value) & value);
			}

			__forceinline qe_uint8 __fastcall operator|(const std::uint8_t value) const noexcept {
				return qe_uint8(algo_t_inst(_value) | value);
			}

			__forceinline qe_uint8 __fastcall operator%(const std::uint8_t value) const noexcept {
				return qe_uint8(algo_t_inst(_value) % value);
			}

			__forceinline qe_uint8 __fastcall operator^(const std::uint8_t value) const noexcept {
				return qe_uint8(algo_t_inst(_value) ^ value);
			}

			__forceinline qe_uint8 __fastcall operator<<(const std::uint8_t value) const noexcept {
				return qe_uint8(algo_t_inst(_value) << value);
			}

			__forceinline qe_uint8 __fastcall operator>>(const std::uint8_t value) const noexcept {
				return qe_uint8(algo_t_inst(_value) >> value);
			}

			__forceinline qe_uint8& __fastcall operator+=(const std::uint8_t value) noexcept {
				this->_value = algo_t_inst(static_cast<std::uint8_t>(algo_t_inst(_value) + value));
				return *this;
			}

			__forceinline qe_uint8& __fastcall operator-=(const std::uint8_t value) noexcept {
				this->_value = algo_t_inst(static_cast<std::uint8_t>(algo_t_inst(_value) - value));
				return *this;
			}

			__forceinline qe_uint8& __fastcall operator*=(const std::uint8_t value) noexcept {
				this->_value = algo_t_inst(static_cast<std::uint8_t>(algo_t_inst(_value) * value));
				return *this;
			}

			__forceinline qe_uint8& __fastcall operator/=(const std::uint8_t value) noexcept {
				this->_value = algo_t_inst(static_cast<std::uint8_t>(algo_t_inst(_value) / value));
				return *this;
			}

			__forceinline qe_uint8& __fastcall operator%=(const std::uint8_t value) noexcept {
				this->_value = algo_t_inst(static_cast<std::uint8_t>(algo_t_inst(_value) % value));
				return *this;
			}

			__forceinline qe_uint8& __fastcall operator^=(const std::uint8_t value) noexcept {
				this->_value = algo_t_inst(static_cast<std::uint8_t>(algo_t_inst(_value) ^ value));
				return *this;
			}

			__forceinline qe_uint8& __fastcall operator&=(const std::uint8_t value) noexcept {
				this->_value = algo_t_inst(static_cast<std::uint8_t>(algo_t_inst(_value) & value));
				return *this;
			}

			__forceinline qe_uint8& __fastcall operator|=(const std::uint8_t value) noexcept {
				this->_value = algo_t_inst(static_cast<std::uint8_t>(algo_t_inst(_value) | value));
				return *this;
			}

			__forceinline qe_uint8& __fastcall operator<<=(const std::uint8_t value) noexcept {
				this->_value = algo_t_inst(static_cast<std::uint8_t>(algo_t_inst(_value) << value));
				return *this;
			}

			__forceinline qe_uint8& __fastcall operator>>=(const std::uint8_t value) noexcept {
				this->_value = algo_t_inst(static_cast<std::uint8_t>(algo_t_inst(_value) >> value));
				return *this;
			}

			__forceinline qe_uint8& __fastcall operator=(const std::uint8_t value) noexcept {
				_value = algo_t_inst(value);
				return *this;
			}

			__forceinline __fastcall operator std::uint8_t() const noexcept {
				return algo_t_inst(_value);
			}

	#pragma endregion
		};

	#pragma endregion

	#pragma region 16-bit

		class qe_int16 {

		private:

	#pragma region Encrypted value

			std::int16_t _value;

	#pragma endregion

		public:

	#pragma region CTOR

			__forceinline __fastcall qe_int16(const std::int16_t value = 0) noexcept {
				_value = algo_t_inst(value);
			}

	#pragma endregion

	#pragma region Accessors

			__forceinline std::int16_t __fastcall get() const noexcept {
				return algo_t_inst(_value);
			}

			__forceinline void __fastcall set(const std::int16_t value) noexcept {
				_value = algo_t_inst(value);
			}

	#pragma endregion

	#pragma region Operators

			__forceinline qe_int16 __fastcall operator+(const std::int16_t value) const noexcept {
				return qe_int16(algo_t_inst(_value) + value);
			};

			__forceinline qe_int16 __fastcall operator-(const std::int16_t value) const noexcept {
				return qe_int16(algo_t_inst(_value) - value);
			}

			__forceinline qe_int16 __fastcall operator/(const std::int16_t value) const noexcept {
				return qe_int16(algo_t_inst(_value) / value);
			}

			__forceinline qe_int16 __fastcall operator*(const std::int16_t value) const noexcept {
				return qe_int16(algo_t_inst(_value) * value);
			}

			__forceinline qe_int16 __fastcall operator&(const std::int16_t value) const noexcept {
				return qe_int16(algo_t_inst(_value) & value);
			}

			__forceinline qe_int16 __fastcall operator|(const std::int16_t value) const noexcept {
				return qe_int16(algo_t_inst(_value) | value);
			}

			__forceinline qe_int16 __fastcall operator%(const std::int16_t value) const noexcept {
				return qe_int16(algo_t_inst(_value) % value);
			}

			__forceinline qe_int16 __fastcall operator^(const std::int16_t value) const noexcept {
				return qe_int16(algo_t_inst(_value) ^ value);
			}

			__forceinline qe_int16 __fastcall operator<<(const std::int16_t value) const noexcept {
				return qe_int16(algo_t_inst(_value) << value);
			}

			__forceinline qe_int16 __fastcall operator>>(const std::int16_t value) const noexcept {
				return qe_int16(algo_t_inst(_value) >> value);
			}

			__forceinline qe_int16& __fastcall operator+=(const std::int16_t value) noexcept {
				this->_value = algo_t_inst(static_cast<std::int16_t>(algo_t_inst(_value) + value));
				return *this;
			}

			__forceinline qe_int16& __fastcall operator-=(const std::int16_t value) noexcept {
				this->_value = algo_t_inst(static_cast<std::int16_t>(algo_t_inst(_value) - value));
				return *this;
			}

			__forceinline qe_int16& __fastcall operator*=(const std::int16_t value) noexcept {
				this->_value = algo_t_inst(static_cast<std::int16_t>(algo_t_inst(_value) * value));
				return *this;
			}

			__forceinline qe_int16& __fastcall operator/=(const std::int16_t value) noexcept {
				this->_value = algo_t_inst(static_cast<std::int16_t>(algo_t_inst(_value) / value));
				return *this;
			}

			__forceinline qe_int16& __fastcall operator%=(const std::int16_t value) noexcept {
				this->_value = algo_t_inst(static_cast<std::int16_t>(algo_t_inst(_value) % value));
				return *this;
			}

			__forceinline qe_int16& __fastcall operator^=(const std::int16_t value) noexcept {
				this->_value = algo_t_inst(static_cast<std::int16_t>(algo_t_inst(_value) ^ value));
				return *this;
			}

			__forceinline qe_int16& __fastcall operator&=(const std::int16_t value) noexcept {
				this->_value = algo_t_inst(static_cast<std::int16_t>(algo_t_inst(_value) & value));
				return *this;
			}

			__forceinline qe_int16& __fastcall operator|=(const std::int16_t value) noexcept {
				this->_value = algo_t_inst(static_cast<std::int16_t>(algo_t_inst(_value) | value));
				return *this;
			}

			__forceinline qe_int16& __fastcall operator<<=(const std::int16_t value) noexcept {
				this->_value = algo_t_inst(static_cast<std::int16_t>(algo_t_inst(_value) << value));
				return *this;
			}

			__forceinline qe_int16& __fastcall operator>>=(const std::int16_t value) noexcept {
				this->_value = algo_t_inst(static_cast<std::int16_t>(algo_t_inst(_value) >> value));
				return *this;
			}

			__forceinline qe_int16& __fastcall operator=(const std::int16_t value) noexcept {
				_value = algo_t_inst(value);
				return *this;
			}

			__forceinline __fastcall operator std::int16_t() const noexcept {
				return algo_t_inst(_value);
			}

	#pragma endregion
		};

		class qe_uint16 {

		private:

	#pragma region Encrypted value

			std::uint16_t _value;

	#pragma endregion

		public:

	#pragma region CTOR

			__forceinline __fastcall qe_uint16(const std::uint16_t value = 0) noexcept {
				_value = algo_t_inst(value);
			}

	#pragma endregion

	#pragma region Accessors

			__forceinline std::uint16_t __fastcall get() const noexcept {
				return algo_t_inst(_value);
			}

			__forceinline void __fastcall set(const std::uint16_t value) noexcept {
				_value = algo_t_inst(value);
			}

	#pragma endregion

	#pragma region Operators

			__forceinline qe_uint16 __fastcall operator+(const std::uint16_t value) const noexcept {
				return qe_uint16(algo_t_inst(_value) + value);
			};

			__forceinline qe_uint16 __fastcall operator-(const std::uint16_t value) const noexcept {
				return qe_uint16(algo_t_inst(_value) - value);
			}

			__forceinline qe_uint16 __fastcall operator/(const std::uint16_t value) const noexcept {
				return qe_uint16(algo_t_inst(_value) / value);
			}

			__forceinline qe_uint16 __fastcall operator*(const std::uint16_t value) const noexcept {
				return qe_uint16(algo_t_inst(_value) * value);
			}

			__forceinline qe_uint16 __fastcall operator&(const std::uint16_t value) const noexcept {
				return qe_uint16(algo_t_inst(_value) & value);
			}

			__forceinline qe_uint16 __fastcall operator|(const std::uint16_t value) const noexcept {
				return qe_uint16(algo_t_inst(_value) | value);
			}

			__forceinline qe_uint16 __fastcall operator%(const std::uint16_t value) const noexcept {
				return qe_uint16(algo_t_inst(_value) % value);
			}

			__forceinline qe_uint16 __fastcall operator^(const std::uint16_t value) const noexcept {
				return qe_uint16(algo_t_inst(_value) ^ value);
			}

			__forceinline qe_uint16 __fastcall operator<<(const std::uint16_t value) const noexcept {
				return qe_uint16(algo_t_inst(_value) << value);
			}

			__forceinline qe_uint16 __fastcall operator>>(const std::uint16_t value) const noexcept {
				return qe_uint16(algo_t_inst(_value) >> value);
			}

			__forceinline qe_uint16& __fastcall operator+=(const std::uint16_t value) noexcept {
				this->_value = algo_t_inst(static_cast<std::uint16_t>(algo_t_inst(_value) + value));
				return *this;
			}

			__forceinline qe_uint16& __fastcall operator-=(const std::uint16_t value) noexcept {
				this->_value = algo_t_inst(static_cast<std::uint16_t>(algo_t_inst(_value) - value));
				return *this;
			}

			__forceinline qe_uint16& __fastcall operator*=(const std::uint16_t value) noexcept {
				this->_value = algo_t_inst(static_cast<std::uint16_t>(algo_t_inst(_value) * value));
				return *this;
			}

			__forceinline qe_uint16& __fastcall operator/=(const std::uint16_t value) noexcept {
				this->_value = algo_t_inst(static_cast<std::uint16_t>(algo_t_inst(_value) / value));
				return *this;
			}

			__forceinline qe_uint16& __fastcall operator%=(const std::uint16_t value) noexcept {
				this->_value = algo_t_inst(static_cast<std::uint16_t>(algo_t_inst(_value) % value));
				return *this;
			}

			__forceinline qe_uint16& __fastcall operator^=(const std::uint16_t value) noexcept {
				this->_value = algo_t_inst(static_cast<std::uint16_t>(algo_t_inst(_value) ^ value));
				return *this;
			}

			__forceinline qe_uint16& __fastcall operator&=(const std::uint16_t value) noexcept {
				this->_value = algo_t_inst(static_cast<std::uint16_t>(algo_t_inst(_value) & value));
				return *this;
			}

			__forceinline qe_uint16& __fastcall operator|=(const std::uint16_t value) noexcept {
				this->_value = algo_t_inst(static_cast<std::uint16_t>(algo_t_inst(_value) | value));
				return *this;
			}

			__forceinline qe_uint16& __fastcall operator<<=(const std::uint16_t value) noexcept {
				this->_value = algo_t_inst(static_cast<std::uint16_t>(algo_t_inst(_value) << value));
				return *this;
			}

			__forceinline qe_uint16& __fastcall operator>>=(const std::uint16_t value) noexcept {
				this->_value = algo_t_inst(static_cast<std::uint16_t>(algo_t_inst(_value) >> value));
				return *this;
			}

			__forceinline qe_uint16& __fastcall operator=(const std::uint16_t value) noexcept {
				_value = algo_t_inst(value);
				return *this;
			}

			__forceinline __fastcall operator std::uint16_t() const noexcept {
				return algo_t_inst(_value);
			}

	#pragma endregion
		};

	#pragma endregion

	#pragma region 32-bit

		class qe_int32 {

		private:

	#pragma region Encrypted value

			int _value;

	#pragma endregion

		public:

	#pragma region CTOR

			__forceinline __fastcall qe_int32(const int value = 0) noexcept {
				_value = algo_t_inst(value);
			}

	#pragma endregion

	#pragma region Accessors

			__forceinline int __fastcall get() const noexcept {
				return algo_t_inst(_value);
			}

			__forceinline void __fastcall set(const int value) noexcept {
				_value = algo_t_inst(value);
			}

	#pragma endregion

	#pragma region Operators

			__forceinline qe_int32 __fastcall operator+(const int value) const noexcept {
				return qe_int32(algo_t_inst(_value) + value);
			};

			__forceinline qe_int32 __fastcall operator-(const int value) const noexcept {
				return qe_int32(algo_t_inst(_value) - value);
			}

			__forceinline qe_int32 __fastcall operator/(const int value) const noexcept {
				return qe_int32(algo_t_inst(_value) / value);
			}

			__forceinline qe_int32 __fastcall operator*(const int value) const noexcept {
				return qe_int32(algo_t_inst(_value) * value);
			}

			__forceinline qe_int32 __fastcall operator&(const int value) const noexcept {
				return qe_int32(algo_t_inst(_value) & value);
			}

			__forceinline qe_int32 __fastcall operator|(const int value) const noexcept {
				return qe_int32(algo_t_inst(_value) | value);
			}

			__forceinline qe_int32 __fastcall operator%(const int value) const noexcept {
				return qe_int32(algo_t_inst(_value) % value);
			}

			__forceinline qe_int32 __fastcall operator^(const int value) const noexcept {
				return qe_int32(algo_t_inst(_value) ^ value);
			}

			__forceinline qe_int32 __fastcall operator<<(const int value) const noexcept {
				return qe_int32(algo_t_inst(_value) << value);
			}

			__forceinline qe_int32 __fastcall operator>>(const int value) const noexcept {
				return qe_int32(algo_t_inst(_value) >> value);
			}

			__forceinline qe_int32& __fastcall operator+=(const int value) noexcept {
				this->_value = algo_t_inst(static_cast<int>(algo_t_inst(_value) + value));
				return *this;
			}

			__forceinline qe_int32& __fastcall operator-=(const int value) noexcept {
				this->_value = algo_t_inst(static_cast<int>(algo_t_inst(_value) - value));
				return *this;
			}

			__forceinline qe_int32& __fastcall operator*=(const int value) noexcept {
				this->_value = algo_t_inst(static_cast<int>(algo_t_inst(_value) * value));
				return *this;
			}

			__forceinline qe_int32& __fastcall operator/=(const int value) noexcept {
				this->_value = algo_t_inst(static_cast<int>(algo_t_inst(_value) / value));
				return *this;
			}

			__forceinline qe_int32& __fastcall operator%=(const int value) noexcept {
				this->_value = algo_t_inst(static_cast<int>(algo_t_inst(_value) % value));
				return *this;
			}

			__forceinline qe_int32& __fastcall operator^=(const int value) noexcept {
				this->_value = algo_t_inst(static_cast<int>(algo_t_inst(_value) ^ value));
				return *this;
			}

			__forceinline qe_int32& __fastcall operator&=(const int value) noexcept {
				this->_value = algo_t_inst(static_cast<int>(algo_t_inst(_value) & value));
				return *this;
			}

			__forceinline qe_int32& __fastcall operator|=(const int value) noexcept {
				this->_value = algo_t_inst(static_cast<int>(algo_t_inst(_value) | value));
				return *this;
			}

			__forceinline qe_int32& __fastcall operator<<=(const int value) noexcept {
				this->_value = algo_t_inst(static_cast<int>(algo_t_inst(_value) << value));
				return *this;
			}

			__forceinline qe_int32& __fastcall operator>>=(const int value) noexcept {
				this->_value = algo_t_inst(static_cast<int>(algo_t_inst(_value) >> value));
				return *this;
			}

			__forceinline qe_int32& __fastcall operator=(const int value) noexcept {
				_value = algo_t_inst(value);
				return *this;
			}

			__forceinline __fastcall operator int() const noexcept {
				return algo_t_inst(_value);
			}

	#pragma endregion
		};

		class qe_uint32 {

		private:

	#pragma region Encrypted value

			std::uint32_t _value;

	#pragma endregion

		public:

	#pragma region CTOR

			__forceinline __fastcall qe_uint32(const std::uint32_t value = 0) noexcept {
				_value = algo_t_inst(value);
			}

	#pragma endregion

	#pragma region Accessors

			__forceinline std::uint32_t __fastcall get() const noexcept {
				return algo_t_inst(_value);
			}

			__forceinline void __fastcall set(std::uint32_t value) noexcept {
				_value = algo_t_inst(value);
			}

	#pragma endregion

	#pragma region Operators

			__forceinline qe_uint32 __fastcall operator+(const std::uint32_t value) const noexcept {
				return qe_uint32(algo_t_inst(_value) + value);
			};

			__forceinline qe_uint32 __fastcall operator-(const std::uint32_t value) const noexcept {
				return qe_uint32(algo_t_inst(_value) - value);
			}

			__forceinline qe_uint32 __fastcall operator/(const std::uint32_t value) const noexcept {
				return qe_uint32(algo_t_inst(_value) / value);
			}

			__forceinline qe_uint32 __fastcall operator*(const std::uint32_t value) const noexcept {
				return qe_uint32(algo_t_inst(_value) * value);
			}

			__forceinline qe_uint32 __fastcall operator&(const std::uint32_t value) const noexcept {
				return qe_uint32(algo_t_inst(_value) & value);
			}

			__forceinline qe_uint32 __fastcall operator|(const std::uint32_t value) const noexcept {
				return qe_uint32(algo_t_inst(_value) | value);
			}

			__forceinline qe_uint32 __fastcall operator%(const std::uint32_t value) const noexcept {
				return qe_uint32(algo_t_inst(_value) % value);
			}

			__forceinline qe_uint32 __fastcall operator^(const std::uint32_t value) const noexcept {
				return qe_uint32(algo_t_inst(_value) ^ value);
			}

			__forceinline qe_uint32 __fastcall operator<<(const std::uint32_t value) const noexcept {
				return qe_uint32(algo_t_inst(_value) << value);
			}

			__forceinline qe_uint32 __fastcall operator>>(const std::uint32_t value) const noexcept {
				return qe_uint32(algo_t_inst(_value) >> value);
			}

			__forceinline qe_uint32& __fastcall operator+=(const std::uint32_t value) noexcept {
				this->_value = algo_t_inst(static_cast<int>(algo_t_inst(_value) + value));
				return *this;
			}

			__forceinline qe_uint32& __fastcall operator-=(const std::uint32_t value) noexcept {
				this->_value = algo_t_inst(static_cast<int>(algo_t_inst(_value) - value));
				return *this;
			}

			__forceinline qe_uint32& __fastcall operator*=(const std::uint32_t value) noexcept {
				this->_value = algo_t_inst(static_cast<int>(algo_t_inst(_value) * value));
				return *this;
			}

			__forceinline qe_uint32& __fastcall operator/=(const std::uint32_t value) noexcept {
				this->_value = algo_t_inst(static_cast<int>(algo_t_inst(_value) / value));
				return *this;
			}

			__forceinline qe_uint32& __fastcall operator%=(const std::uint32_t value) noexcept {
				this->_value = algo_t_inst(static_cast<int>(algo_t_inst(_value) % value));
				return *this;
			}

			__forceinline qe_uint32& __fastcall operator^=(const std::uint32_t value) noexcept {
				this->_value = algo_t_inst(static_cast<int>(algo_t_inst(_value) ^ value));
				return *this;
			}

			__forceinline qe_uint32& __fastcall operator&=(const std::uint32_t value) noexcept {
				this->_value = algo_t_inst(static_cast<int>(algo_t_inst(_value) & value));
				return *this;
			}

			__forceinline qe_uint32& __fastcall operator|=(const std::uint32_t value) noexcept {
				this->_value = algo_t_inst(static_cast<int>(algo_t_inst(_value) | value));
				return *this;
			}

			__forceinline qe_uint32& __fastcall operator<<=(const std::uint32_t value) noexcept {
				this->_value = algo_t_inst(static_cast<int>(algo_t_inst(_value) << value));
				return *this;
			}

			__forceinline qe_uint32& __fastcall operator>>=(const std::uint32_t value) noexcept {
				this->_value = algo_t_inst(static_cast<int>(algo_t_inst(_value) >> value));
				return *this;
			}

			__forceinline qe_uint32& __fastcall operator=(const std::uint32_t value) noexcept {
				_value = algo_t_inst(value);
				return *this;
			}

			__forceinline __fastcall operator std::uint32_t() const noexcept {
				return algo_t_inst(_value);
			}

	#pragma endregion
		};

	#pragma endregion

	#pragma region 64-bit

		class qe_int64 {

		private:

	#pragma region Encrypted value

			std::int64_t _value;

	#pragma endregion

		public:

	#pragma region CTOR

			__forceinline __fastcall qe_int64(const std::int64_t value = 0) noexcept {
				_value = algo_t_inst(value);
			}

	#pragma endregion

	#pragma region Accessors

			__forceinline std::int64_t __fastcall get() const noexcept {
				return algo_t_inst(_value);
			}

			__forceinline void __fastcall set(const std::int64_t value) noexcept {
				_value = algo_t_inst(value);
			}

	#pragma endregion

	#pragma region Operators

			__forceinline qe_int64 __fastcall operator+(const std::int64_t value) const noexcept {
				return qe_int64(algo_t_inst(_value) + value);
			};

			__forceinline qe_int64 __fastcall operator-(const std::int64_t value) const noexcept {
				return qe_int64(algo_t_inst(_value) - value);
			}

			__forceinline qe_int64 __fastcall operator/(const std::int64_t value) const noexcept {
				return qe_int64(algo_t_inst(_value) / value);
			}

			__forceinline qe_int64 __fastcall operator*(const std::int64_t value) const noexcept {
				return qe_int64(algo_t_inst(_value) * value);
			}

			__forceinline qe_int64 __fastcall operator&(const std::int64_t value) const noexcept {
				return qe_int64(algo_t_inst(_value) & value);
			}

			__forceinline qe_int64 __fastcall operator|(const std::int64_t value) const noexcept {
				return qe_int64(algo_t_inst(_value) | value);
			}

			__forceinline qe_int64 __fastcall operator%(const std::int64_t value) const noexcept {
				return qe_int64(algo_t_inst(_value) % value);
			}

			__forceinline qe_int64 __fastcall operator^(const std::int64_t value) const noexcept {
				return qe_int64(algo_t_inst(_value) ^ value);
			}

			__forceinline qe_int64 __fastcall operator<<(const std::int64_t value) const noexcept {
				return qe_int64(algo_t_inst(_value) << value);
			}

			__forceinline qe_int64 __fastcall operator>>(const std::int64_t value) const noexcept {
				return qe_int64(algo_t_inst(_value) >> value);
			}

			__forceinline qe_int64& __fastcall operator+=(const std::int64_t value) noexcept {
				this->_value = algo_t_inst(static_cast<int>(algo_t_inst(_value) + value));
				return *this;
			}

			__forceinline qe_int64& __fastcall operator-=(const std::int64_t value) noexcept {
				this->_value = algo_t_inst(static_cast<int>(algo_t_inst(_value) - value));
				return *this;
			}

			__forceinline qe_int64& __fastcall operator*=(const std::int64_t value) noexcept {
				this->_value = algo_t_inst(static_cast<int>(algo_t_inst(_value) * value));
				return *this;
			}

			__forceinline qe_int64& __fastcall operator/=(const std::int64_t value) noexcept {
				this->_value = algo_t_inst(static_cast<int>(algo_t_inst(_value) / value));
				return *this;
			}

			__forceinline qe_int64& __fastcall operator%=(const std::int64_t value) noexcept {
				this->_value = algo_t_inst(static_cast<int>(algo_t_inst(_value) % value));
				return *this;
			}

			__forceinline qe_int64& __fastcall operator^=(const std::int64_t value) noexcept {
				this->_value = algo_t_inst(static_cast<int>(algo_t_inst(_value) ^ value));
				return *this;
			}

			__forceinline qe_int64& __fastcall operator&=(const std::int64_t value) noexcept {
				this->_value = algo_t_inst(static_cast<int>(algo_t_inst(_value) & value));
				return *this;
			}

			__forceinline qe_int64& __fastcall operator|=(const std::int64_t value) noexcept {
				this->_value = algo_t_inst(static_cast<int>(algo_t_inst(_value) | value));
				return *this;
			}

			__forceinline qe_int64& __fastcall operator<<=(const std::int64_t value) noexcept {
				this->_value = algo_t_inst(static_cast<int>(algo_t_inst(_value) << value));
				return *this;
			}

			__forceinline qe_int64& __fastcall operator>>=(const std::int64_t value) noexcept {
				this->_value = algo_t_inst(static_cast<int>(algo_t_inst(_value) >> value));
				return *this;
			}

			__forceinline qe_int64& __fastcall operator=(const std::int64_t value) noexcept {
				_value = algo_t_inst(value);
				return *this;
			}

			__forceinline __cdecl operator std::int64_t() const noexcept {
				return algo_t_inst(_value);
			}

	#pragma endregion
		};

		class qe_uint64 {
		private:

	#pragma region Encrypted value

			std::uint64_t _value;

	#pragma endregion

		public:

	#pragma region CTOR

			__forceinline __fastcall qe_uint64(const std::uint64_t value = 0) {
				_value = algo_t_inst(value);
			}

	#pragma endregion

	#pragma region Accessors

			__forceinline std::uint64_t __fastcall get() const noexcept {
				return algo_t_inst(_value);
			}

			__forceinline void __fastcall set(const std::uint64_t value) noexcept {
				_value = algo_t_inst(value);
			}

	#pragma endregion

	#pragma region Operators

			__forceinline qe_uint64 __fastcall operator+(const std::uint64_t value) const noexcept {
				return qe_uint64(algo_t_inst(_value) + value);
			};

			__forceinline qe_uint64 __fastcall operator-(const std::uint64_t value) const noexcept {
				return qe_uint64(algo_t_inst(_value) - value);
			}

			__forceinline qe_uint64 __fastcall operator/(const std::uint64_t value) const noexcept {
				return qe_uint64(algo_t_inst(_value) / value);
			}

			__forceinline qe_uint64 __fastcall operator*(const std::uint64_t value) const noexcept {
				return qe_uint64(algo_t_inst(_value) * value);
			}

			__forceinline qe_uint64 __fastcall operator&(const std::uint64_t value) const noexcept {
				return qe_uint64(algo_t_inst(_value) & value);
			}

			__forceinline qe_uint64 __fastcall operator|(const std::uint64_t value) const noexcept {
				return qe_uint64(algo_t_inst(_value) | value);
			}

			__forceinline qe_uint64 __fastcall operator%(const std::uint64_t value) const noexcept {
				return qe_uint64(algo_t_inst(_value) % value);
			}

			__forceinline qe_uint64 __fastcall operator^(const std::uint64_t value) const noexcept {
				return qe_uint64(algo_t_inst(_value) ^ value);
			}

			__forceinline qe_uint64 __fastcall operator<<(const std::uint64_t value) const noexcept {
				return qe_uint64(algo_t_inst(_value) << value);
			}

			__forceinline qe_uint64 __fastcall operator>>(const std::uint64_t value) const noexcept {
				return qe_uint64(algo_t_inst(_value) >> value);
			}

			__forceinline qe_uint64& __fastcall operator+=(const std::uint64_t value) noexcept {
				this->_value = algo_t_inst(static_cast<int>(algo_t_inst(_value) + value));
				return *this;
			}

			__forceinline qe_uint64& __fastcall operator-=(const std::uint64_t value) noexcept {
				this->_value = algo_t_inst(static_cast<int>(algo_t_inst(_value) - value));
				return *this;
			}

			__forceinline qe_uint64& __fastcall operator*=(const std::uint64_t value) noexcept {
				this->_value = algo_t_inst(static_cast<int>(algo_t_inst(_value) * value));
				return *this;
			}

			__forceinline qe_uint64& __fastcall operator/=(const std::uint64_t value) noexcept {
				this->_value = algo_t_inst(static_cast<int>(algo_t_inst(_value) / value));
				return *this;
			}

			__forceinline qe_uint64& __fastcall operator%=(const std::uint64_t value) noexcept {
				this->_value = algo_t_inst(static_cast<int>(algo_t_inst(_value) % value));
				return *this;
			}

			__forceinline qe_uint64& __fastcall operator^=(const std::uint64_t value) noexcept {
				this->_value = algo_t_inst(static_cast<int>(algo_t_inst(_value) ^ value));
				return *this;
			}

			__forceinline qe_uint64& __fastcall operator&=(const std::uint64_t value) noexcept {
				this->_value = algo_t_inst(static_cast<int>(algo_t_inst(_value) & value));
				return *this;
			}

			__forceinline qe_uint64& __fastcall operator|=(const std::uint64_t value) noexcept {
				this->_value = algo_t_inst(static_cast<int>(algo_t_inst(_value) | value));
				return *this;
			}

			__forceinline qe_uint64& __fastcall operator<<=(const std::uint64_t value) noexcept {
				this->_value = algo_t_inst(static_cast<int>(algo_t_inst(_value) << value));
				return *this;
			}

			__forceinline qe_uint64& __fastcall operator>>=(const std::uint64_t value) noexcept {
				this->_value = algo_t_inst(static_cast<int>(algo_t_inst(_value) >> value));
				return *this;
			}

			__forceinline qe_uint64& __fastcall operator=(const std::uint64_t value) noexcept {
				_value = algo_t_inst(value);
				return *this;
			}

			__forceinline __cdecl operator std::uint64_t() const noexcept {
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

		class qe_float {
		private:

			float _value;

		public:

	#pragma region CTOR

			__forceinline __fpcall qe_float(const float value) noexcept {
				_value = algo_t_inst(value);
			}

	#pragma endregion

	#pragma region Accessors

			__forceinline float __cdecl get() const noexcept {
				return algo_t_inst(_value);
			}

			__forceinline void __fpcall set(const float value) noexcept {
				_value = algo_t_inst(value);
			}

	#pragma endregion

	#pragma region Operators

			__forceinline qe_float __fpcall operator+(const float value) const noexcept {
				return qe_float(algo_t_inst(_value) + value);
			};

			__forceinline qe_float __fpcall operator-(const float value) const noexcept {
				return qe_float(algo_t_inst(_value) - value);
			}

			__forceinline qe_float __fpcall operator/(const float value) const noexcept {
				return qe_float(algo_t_inst(_value) / value);
			}

			__forceinline qe_float __fpcall operator*(const float value) const noexcept {
				return qe_float(algo_t_inst(_value) * value);
			}

			__forceinline qe_float __fpcall operator^(const float value) const noexcept {
				return qe_float(XOR_FORCE(algo_t_inst(_value), value));
			}

			__forceinline qe_float& __fpcall operator+=(const float value) noexcept {
				_value = algo_t_inst(algo_t_inst(_value) + value);
				return *this;
			}

			__forceinline qe_float& __fpcall operator-=(const float value) noexcept {
				_value = algo_t_inst(algo_t_inst(_value) - value);
				return *this;
			}

			__forceinline qe_float& __fpcall operator*=(const float value) noexcept {
				_value = algo_t_inst(algo_t_inst(_value) * value);
				return *this;
			}

			__forceinline qe_float& __fpcall operator/=(const float value) noexcept {
				_value = algo_t_inst(algo_t_inst(_value) / value);
				return *this;
			}

			__forceinline qe_float& __fpcall operator^=(const float value) noexcept {
				_value = algo_t_inst(XOR_FORCE(algo_t_inst(_value), value));
				return *this;
			}

			__forceinline qe_float& __fpcall operator=(const float value) noexcept {
				_value = algo_t_inst(value);
				return *this;
			}

			__forceinline  __cdecl operator float() const noexcept {
				return get();
			}

	#pragma endregion
		};

	#pragma endregion

	#pragma region 64-bit

		class qe_double {

		private:

			double _value;

		public:

	#pragma region CTOR

			__forceinline __fpcall qe_double(const double value = static_cast<double>(0.0f)) {
				_value = algo_t_inst(value);
			}

	#pragma endregion

	#pragma region Accessors

			__forceinline double __cdecl get() const noexcept {
				return algo_t_inst(_value);
			}

			__forceinline void __fpcall set(const double value) noexcept {
				_value = algo_t_inst(value);
			}

	#pragma endregion

	#pragma region Operators

			__forceinline qe_double __fpcall operator+(const double value) const noexcept {
				return qe_double(algo_t_inst(_value) + value);
			};

			__forceinline qe_double __fpcall operator-(const double value) const noexcept {
				return qe_double(algo_t_inst(_value) - value);
			}

			__forceinline qe_double __fpcall operator/(const double value) const noexcept {
				return qe_double(algo_t_inst(_value) / value);
			}

			__forceinline qe_double __fpcall operator*(const double value) const noexcept {
				return qe_double(algo_t_inst(_value) * value);
			}

			__forceinline qe_double __fpcall operator^(const double value) const noexcept {
				return qe_double(XOR_FORCE(algo_t_inst(_value), value));
			}

			__forceinline qe_double& __fpcall operator+=(const double value) noexcept {
				_value = algo_t_inst(algo_t_inst(_value) + value);
				return *this;
			}

			__forceinline qe_double& __fpcall operator-=(const double value) noexcept {
				_value = algo_t_inst(algo_t_inst(_value) - value);
				return *this;
			}

			__forceinline qe_double& __fpcall operator*=(const double value) noexcept {
				_value = algo_t_inst(algo_t_inst(_value) * value);
				return *this;
			}

			__forceinline qe_double& __fpcall operator/=(const double value) noexcept {
				_value = algo_t_inst(algo_t_inst(_value) / value);
				return *this;
			}

			__forceinline qe_double& __fpcall operator^=(const double value) noexcept {
				_value = algo_t_inst(XOR_FORCE(algo_t_inst(_value), value));
				return *this;
			}

			__forceinline qe_double& __fpcall operator=(const double value) noexcept {
				_value = algo_t_inst(value);
				return *this;
			}

			__forceinline  __cdecl operator double() const noexcept {
				return get();
			}

	#pragma endregion
		};

	#pragma endregion

	#pragma endregion

	#pragma region SSE Types

		//SSE
	#ifdef __SSE__

		class qe_m128 {
		private:

			__m128 _value;

		public:

	#pragma region CTOR

			__forceinline __fpcall qe_m128(const __m128 value) noexcept {
				_value = algo_t_inst(value);
			}

	#pragma endregion

	#pragma region Accessors
			__forceinline __m128 __cdecl get() const noexcept {
				return algo_t_inst(_value);
			}
			__forceinline void __fpcall set(const __m128 value) noexcept {
				_value = algo_t_inst(value);
			}
	#pragma endregion

	#pragma region Operators
	#ifdef __clang__ // msvc does not support math operators on vector types

			__forceinline qe_m128 __fpcall operator+(const __m128 value) const noexcept {
				return qe_m128(algo_t_inst(_value) + value);
			};

			__forceinline qe_m128 __fpcall operator-(const __m128 value) const noexcept {
				return qe_m128(algo_t_inst(_value) - value);
			}

			__forceinline qe_m128 __fpcall operator/(const __m128 value) const noexcept {
				return qe_m128((const __m128)algo_t_inst(_value) / value);
			}

			__forceinline qe_m128 __fpcall operator*(const __m128 value) const noexcept {
				return qe_m128(algo_t_inst(_value) * value);
			}

	#endif

			__forceinline qe_m128 __fpcall operator^(const __m128 value) const noexcept {
				return qe_m128(XOR_FORCE(algo_t_inst(_value), value));
			}

	#ifdef __clang__

			__forceinline qe_m128& __fpcall operator+=(const __m128 value) noexcept {
				_value = algo_t_inst(algo_t_inst(value) + value);
				return *this;
			}

			__forceinline qe_m128& __fpcall operator-=(const __m128 value) noexcept {
				_value = algo_t_inst(algo_t_inst(_value) - value);
				return *this;
			}

			__forceinline qe_m128& __fpcall operator*=(const __m128 value) noexcept {
				_value = algo_t_inst(algo_t_inst(_value) * value);
				return *this;
			}

			__forceinline qe_m128& __fpcall operator/=(const __m128 value) noexcept {
				_value = algo_t_inst(algo_t_inst(_value) / value);
				return *this;
			}

	#endif

			__forceinline qe_m128& __fpcall operator^=(const __m128 value) noexcept {
				_value = algo_t_inst(XOR_FORCE(algo_t_inst(_value), value));
				return *this;
			}

			__forceinline qe_m128& __fpcall operator=(const __m128 value) noexcept {
				_value = algo_t_inst(value);
				return *this;
			}

			__forceinline __cdecl operator __m128() const noexcept {
				return get();
			}

	#pragma endregion
		};

	#ifdef __SSE2__

		class qe_m128i {

		private:

			__m128i _value;

		public:

	#pragma region CTOR

			__forceinline __fpcall qe_m128i(const __m128i value) noexcept {
				_value = algo_t_inst(value);
			}

	#pragma endregion

	#pragma region Accessors
			__forceinline __m128i __cdecl get() const noexcept {
				return algo_t_inst(_value);
			}
			__forceinline void __fpcall set(const __m128i value) noexcept {
				_value = algo_t_inst(value);
			}
	#pragma endregion

	#pragma region Operators

	#ifdef __clang__ // msvc does not support math operators on vector types

			__forceinline qe_m128i __fpcall operator+(const __m128i value) const noexcept {
				return qe_m128i(algo_t_inst(_value) + value);
			};

			__forceinline qe_m128i __fpcall operator-(const __m128i value) const noexcept {
				return qe_m128i(algo_t_inst(_value) - value);
			}

			__forceinline qe_m128i __fpcall operator/(const __m128i value) const noexcept {
				return qe_m128i((const __m128i)algo_t_inst(_value) / value);
			}

			__forceinline qe_m128i __fpcall operator*(const __m128i value) const noexcept {
				return qe_m128i(algo_t_inst(_value) * value);
			}

	#endif

			__forceinline qe_m128i __fpcall operator^(const __m128i value) const noexcept {
				return qe_m128i(XOR_FORCE(algo_t_inst(_value), value));
			}

	#ifdef __clang__

			__forceinline qe_m128i& __fpcall operator+=(const __m128i value) noexcept {
				_value = algo_t_inst(algo_t_inst(value) + value);
				return *this;
			}

			__forceinline qe_m128i& __fpcall operator-=(const __m128i value) noexcept {
				_value = algo_t_inst(algo_t_inst(_value) - value);
				return *this;
			}

			__forceinline qe_m128i& __fpcall operator*=(const __m128i value) noexcept {
				_value = algo_t_inst(algo_t_inst(_value) * value);
				return *this;
			}

			__forceinline qe_m128i& __fpcall operator/=(const __m128i value) noexcept {
				_value = algo_t_inst(algo_t_inst(_value) / value);
				return *this;
			}

	#endif

			__forceinline qe_m128i& __fpcall operator^=(const __m128i value) noexcept {
				_value = algo_t_inst(XOR_FORCE(algo_t_inst(_value), value));
				return *this;
			}

			__forceinline qe_m128i& __fpcall operator=(const __m128i value) noexcept {
				_value = algo_t_inst(value);
				return *this;
			}

			__forceinline __cdecl operator __m128i() const noexcept {
				return get();
			}

	#pragma endregion
		};

		class qe_m128d {

		private:

			__m128d _value;

		public:

	#pragma region CTOR

			__forceinline __fpcall qe_m128d(const __m128d value) noexcept {
				_value = algo_t_inst(value);
			}

	#pragma endregion

	#pragma region Accessors
			__forceinline __m128d __cdecl get() const noexcept {
				return algo_t_inst(_value);
			}
			__forceinline void __fpcall set(const __m128d value) noexcept {
				_value = algo_t_inst(value);
			}
	#pragma endregion

	#pragma region Operators
	#ifdef __clang__ // msvc does not support math operators on vector types

			__forceinline qe_m128d __fpcall operator+(const __m128d value) const noexcept {
				return qe_m128d(algo_t_inst(_value) + value);
			};

			__forceinline qe_m128d __fpcall operator-(const __m128d value) const noexcept {
				return qe_m128d(algo_t_inst(_value) - value);
			}

			__forceinline qe_m128d __fpcall operator/(const __m128d value) const noexcept {
				return qe_m128d((const __m128d)algo_t_inst(_value) / value);
			}

			__forceinline qe_m128d __fpcall operator*(const __m128d value) const noexcept {
				return qe_m128d(algo_t_inst(_value) * value);
			}

	#endif

			__forceinline qe_m128d __fpcall operator^(const __m128d value) const noexcept {
				return qe_m128d(XOR_FORCE(algo_t_inst(_value), value));
			}

	#ifdef __clang__

			__forceinline qe_m128d& __fpcall operator+=(const __m128d value) noexcept {
				_value = algo_t_inst(algo_t_inst(value) + value);
				return *this;
			}

			__forceinline qe_m128d& __fpcall operator-=(const __m128d value) noexcept {
				_value = algo_t_inst(algo_t_inst(_value) - value);
				return *this;
			}

			__forceinline qe_m128d& __fpcall operator*=(const __m128d value) noexcept {
				_value = algo_t_inst(algo_t_inst(_value) * value);
				return *this;
			}

			__forceinline qe_m128d& __fpcall operator/=(const __m128d value) noexcept {
				_value = algo_t_inst(algo_t_inst(_value) / value);
				return *this;
			}

	#endif

			__forceinline qe_m128d& __fpcall operator^=(const __m128d value) noexcept {
				_value = algo_t_inst(XOR_FORCE(algo_t_inst(_value), value));
				return *this;
			}

			__forceinline qe_m128d& __fpcall operator=(const __m128d value) noexcept {
				_value = algo_t_inst(value);
				return *this;
			}

			__forceinline __cdecl operator __m128d() const noexcept {
				return get();
			}

	#pragma endregion
		};

	#endif

	#endif

	#pragma endregion

	#pragma region AVX Types

	#ifdef __AVX__

		class qe_m256 {

		private:

			__m256 _value;

		public:

	#pragma region CTOR
			__forceinline __fpcall qe_m256(const __m256 value) noexcept {
				_value = algo_t_inst(value);
			}
	#pragma endregion

	#pragma region Accessors
			__forceinline __m256 __cdecl get() const noexcept {
				return algo_t_inst(_value);
			}
			__forceinline void __fpcall set(const __m256 value) noexcept {
				_value = algo_t_inst(value);
			}
	#pragma endregion

	#pragma region Operators

	#ifdef __clang__ // msvc does not support math operators on vector types

			__forceinline qe_m256 __fpcall operator+(const __m256 value) const noexcept {
				return qe_m256(algo_t_inst(_value) + value);
			};

			__forceinline qe_m256 __fpcall operator-(const __m256 value) const noexcept {
				return qe_m256(algo_t_inst(_value) - value);
			}

			__forceinline qe_m256 __fpcall operator/(const __m256 value) const noexcept {
				return qe_m256((const __m256)algo_t_inst(_value) / value);
			}

			__forceinline qe_m256 __fpcall operator*(const __m256 value) const noexcept {
				return qe_m256(algo_t_inst(_value) * value);
			}

	#endif

			__forceinline qe_m256 __fpcall operator^(const __m256 value) const noexcept {
				return qe_m256(XOR_FORCE(algo_t_inst(_value), value));
			}

	#ifdef __clang__

			__forceinline qe_m256& __fpcall operator+=(const __m256 value) noexcept {
				_value = algo_t_inst(algo_t_inst(value) + value);
				return *this;
			}

			__forceinline qe_m256& __fpcall operator-=(const __m256 value) noexcept {
				_value = algo_t_inst(algo_t_inst(_value) - value);
				return *this;
			}

			__forceinline qe_m256& __fpcall operator*=(const __m256 value) noexcept {
				_value = algo_t_inst(algo_t_inst(_value) * value);
				return *this;
			}

			__forceinline qe_m256& __fpcall operator/=(const __m256 value) noexcept {
				_value = algo_t_inst(algo_t_inst(_value) / value);
				return *this;
			}

	#endif

			__forceinline qe_m256& __fpcall operator^=(const __m256 value) noexcept {
				_value = algo_t_inst(XOR_FORCE(algo_t_inst(_value), value));
				return *this;
			}

			__forceinline qe_m256& __fpcall operator=(const __m256 value) noexcept {
				_value = algo_t_inst(value);
				return *this;
			}

			__forceinline __cdecl operator __m256() const noexcept {
				return get();
			}

	#pragma endregion
		};

		class qe_m256i {

		private:

			__m256i _value;

		public:

	#pragma region CTOR
			__forceinline __fpcall qe_m256i(const __m256i value) noexcept {
				_value = algo_t_inst(value);
			}
	#pragma endregion

	#pragma region Accessors
			__forceinline __m256i __cdecl get() const noexcept {
				return algo_t_inst(_value);
			}
			__forceinline void __fpcall set(const __m256i value) noexcept {
				_value = algo_t_inst(value);
			}
	#pragma endregion

	#pragma region Operators
	#ifdef __clang__ // msvc does not support math operators on vector types

			__forceinline qe_m256i __fpcall operator+(const __m256i value) const noexcept {
				return qe_m256i(algo_t_inst(_value) + value);
			};

			__forceinline qe_m256i __fpcall operator-(const __m256i value) const noexcept {
				return qe_m256i(algo_t_inst(_value) - value);
			}

			__forceinline qe_m256i __fpcall operator/(const __m256i value) const noexcept {
				return qe_m256i((const __m256i)algo_t_inst(_value) / value);
			}

			__forceinline qe_m256i __fpcall operator*(const __m256i value) const noexcept {
				return qe_m256i(algo_t_inst(_value) * value);
			}

	#endif

			__forceinline qe_m256i __fpcall operator^(const __m256i value) const noexcept {
				return qe_m256i(XOR_FORCE(algo_t_inst(_value), value));
			}

	#ifdef __clang__

			__forceinline qe_m256i& __fpcall operator+=(const __m256i value) noexcept {
				_value = algo_t_inst(algo_t_inst(value) + value);
				return *this;
			}

			__forceinline qe_m256i& __fpcall operator-=(const __m256i value) noexcept {
				_value = algo_t_inst(algo_t_inst(_value) - value);
				return *this;
			}

			__forceinline qe_m256i& __fpcall operator*=(const __m256i value) noexcept {
				_value = algo_t_inst(algo_t_inst(_value) * value);
				return *this;
			}

			__forceinline qe_m256i& __fpcall operator/=(const __m256i value) noexcept {
				_value = algo_t_inst(algo_t_inst(_value) / value);
				return *this;
			}

	#endif

			__forceinline qe_m256i& __fpcall operator^=(const __m256i value) noexcept {
				_value = algo_t_inst(XOR_FORCE(algo_t_inst(_value), value));
				return *this;
			}

			__forceinline qe_m256i& __fpcall operator=(const __m256i value) noexcept {
				_value = algo_t_inst(value);
				return *this;
			}

			__forceinline __cdecl operator __m256i() const noexcept {
				return get();
			}

	#pragma endregion
		};

		class qe_m256d {

		private:

			__m256d _value;

		public:

	#pragma region CTOR

			__forceinline __fpcall qe_m256d(const __m256d value) noexcept {
				_value = algo_t_inst(value);
			}

	#pragma endregion

	#pragma region Accessors

			__forceinline __m256d __cdecl get() const noexcept {
				return algo_t_inst(_value);
			}
			__forceinline void __fpcall set(const __m256d value) noexcept {
				_value = algo_t_inst(value);
			}

	#pragma endregion

	#pragma region Operators

	#ifdef __clang__ // msvc does not support math operators on vector types

			__forceinline qe_m256d __fpcall operator+(const __m256d value) const noexcept {
				return qe_m256d(algo_t_inst(_value) + value);
			};

			__forceinline qe_m256d __fpcall operator-(const __m256d value) const noexcept {
				return qe_m256d(algo_t_inst(_value) - value);
			}

			__forceinline qe_m256d __fpcall operator/(const __m256d value) const noexcept {
				return qe_m256d((const __m256d)algo_t_inst(_value) / value);
			}

			__forceinline qe_m256d __fpcall operator*(const __m256d value) const noexcept {
				return qe_m256d(algo_t_inst(_value) * value);
			}

	#endif

			__forceinline qe_m256d __fpcall operator^(const __m256d value) const noexcept {
				return qe_m256d(XOR_FORCE(algo_t_inst(_value), value));
			}

	#ifdef __clang__

			__forceinline qe_m256d& __fpcall operator+=(const __m256d value) noexcept {
				_value = algo_t_inst(algo_t_inst(value) + value);
				return *this;
			}

			__forceinline qe_m256d& __fpcall operator-=(const __m256d value) noexcept {
				_value = algo_t_inst(algo_t_inst(_value) - value);
				return *this;
			}

			__forceinline qe_m256d& __fpcall operator*=(const __m256d value) noexcept {
				_value = algo_t_inst(algo_t_inst(_value) * value);
				return *this;
			}

			__forceinline qe_m256d& __fpcall operator/=(const __m256d value) noexcept {
				_value = algo_t_inst(algo_t_inst(_value) / value);
				return *this;
			}

	#endif

			__forceinline qe_m256d& __fpcall operator^=(const __m256d value) noexcept {
				_value = algo_t_inst(XOR_FORCE(algo_t_inst(_value), value));
				return *this;
			}

			__forceinline qe_m256d& __fpcall operator=(const __m256d value) noexcept {
				_value = algo_t_inst(value);
				return *this;
			}

			__forceinline __cdecl operator __m256d() const noexcept {
				return get();
			}

	#pragma endregion
		};

	#endif

	#pragma endregion

	#pragma endregion

	#pragma region String

		class qe_string {
		private:

	#pragma region Encrypted value

			std::string _value = "";

	#pragma endregion

		public:

	#pragma region CTOR

			__forceinline __cdecl qe_string(const std::string value) noexcept {
				_value = algo_str_inst(value);
			}

			__forceinline __fastcall qe_string(const char* value = "") {
				if (!is_init) {
					init_constants();
				}

				_value = algo_str_inst(std::string(value));
			}

	#pragma endregion

	#pragma region Accessors

			__forceinline std::string __cdecl get() const noexcept {
				return algo_str_inst(std::string(_value));
			}

			__forceinline void __cdecl set(const std::string& value) noexcept {
				_value = algo_str_inst(value);
			}

			__forceinline qe_string __cdecl operator+(const std::string& value) const noexcept {
				return qe_string(algo_str_inst(std::string(_value)) + value);
			};

			__forceinline qe_string& __cdecl operator+=(const std::string& value) noexcept {
				_value = algo_str_inst(static_cast<std::string>(algo_str_inst(_value) + value));
				return *this;
			}

			__forceinline qe_string& __cdecl operator=(const std::string& value) noexcept {
				set(value);
				return *this;
			}

			__forceinline __cdecl operator std::string() const noexcept {
				return get();
			}

			__forceinline __cdecl ~qe_string() noexcept { }

	#pragma endregion

	#pragma region Operators

	#pragma endregion
		};

	#pragma endregion

	#pragma region Wide String

		class qe_wstring {
		private:

	#pragma region Encrypted value

			std::wstring _value = L"";

	#pragma endregion

		public:

	#pragma region CTOR

			__forceinline __cdecl qe_wstring(const std::wstring& value) noexcept {
				_value = algo_wstr_inst(value);
			}

			__forceinline __fastcall qe_wstring(const wchar_t* value = L"") {
				if (!is_init) {
					init_constants();
				}

				_value = algo_wstr_inst(std::wstring(value));
			}

	#pragma endregion

	#pragma region Accessors

			__forceinline std::wstring __cdecl get() const noexcept {
				return algo_wstr_inst(std::wstring(_value));
			}

			__forceinline void __cdecl set(const std::wstring value) noexcept {
				_value = algo_wstr_inst(value);
			}

			__forceinline void __fastcall reserve(std::size_t count) noexcept {
				_value.reserve(count);
			}

			__forceinline bool __cdecl empty() const noexcept {
				return _value.empty();
			}

			__forceinline qe_wstring __cdecl operator+(const std::wstring& value) const noexcept {
				return qe_wstring(algo_wstr_inst(_value) + value);
			};

			__forceinline qe_wstring& __cdecl operator+=(const std::wstring& value) noexcept {
				_value = algo_wstr_inst(static_cast<std::wstring>(algo_wstr_inst(_value) + value));
				return *this;
			}

			__forceinline qe_wstring& __cdecl operator=(const std::wstring& value) noexcept {
				set(value);
				return *this;
			}
			// to-do use a subscript proxy to allow get set access through indexing
			__forceinline wchar_t& __fastcall operator[](const int index) noexcept {
				return algo_wstr_inst(_value)[index];
			}

			__forceinline __cdecl operator std::wstring() const noexcept {
				return algo_wstr_inst(_value);
			}

			__forceinline __cdecl ~qe_wstring() noexcept { }

	#pragma endregion

	#pragma region Operators

	#pragma endregion
		};

	#pragma endregion

	#pragma region Heap Allocation

		class qe_malloc {

		private:

	#pragma region Global Variables

			void* local_alloc;
			std::size_t alloc_size;

	#pragma endregion

		public:

	#pragma region Proxy objects

	#pragma region Subscript proxy

			// nested class to support subscript assignment
			class index_proxy {

			private:

	#pragma region Globals

				qe_malloc& parent;

				std::size_t index;

	#pragma endregion

			public:
	#pragma region Ctor

				index_proxy(const std::size_t index_, qe_malloc& instance) noexcept : index(index_), parent(instance) { }

	#pragma endregion

	#pragma region Operator overrides

				uint8_t& operator=(uint8_t value) noexcept {

					parent.set(index, value);

					return value;   // return the passed assignment value rather than using up absurd resources to decrypt, re-encrypt everything using get()
				}

				__forceinline __cdecl operator uint8_t() const noexcept {

					return parent.get(index);
				}

	#pragma endregion
			};

	#pragma endregion

	#pragma endregion

	#pragma region Ctor

			__forceinline __fastcall qe_malloc(const std::size_t size)
				: 
				alloc_size(size),
				local_alloc(malloc(size))
			{

				if (!local_alloc)
					throw std::bad_alloc();

				RtlZeroMemory(local_alloc, size);

				algo(local_alloc, size);
			}

			__forceinline __cdecl qe_malloc() noexcept
				:
				alloc_size(NULL),
				local_alloc(NULL)
			{
				if (!is_init) {
					init_constants();
				}
			}

	#pragma endregion

	#pragma region Get accessors

			__forceinline void* __fastcall get() noexcept {
				return algo_inst(local_alloc, alloc_size);
			}

			__forceinline void* __fastcall get(const std::uintptr_t pos, const std::size_t length) noexcept {
				auto dec_alloc = reinterpret_cast<uint8_t*>(get());

				auto get_alloc = malloc(length);

				if (!get_alloc)
					return nullptr;

				memcpy(get_alloc, &dec_alloc[pos], length);

				RtlZeroMemory(dec_alloc, alloc_size);
				free(dec_alloc);

				return get_alloc;
			}

			__forceinline std::uint8_t __fastcall get(const std::size_t index) noexcept {
				auto dec_alloc = reinterpret_cast<uint8_t*>(get());

				auto _return = dec_alloc[index];

				RtlZeroMemory(dec_alloc, alloc_size);
				free(dec_alloc);

				return _return;
			}

			template<typename T>
			__forceinline T& __fastcall get_t(const std::uintptr_t pos) noexcept {

				auto value_r = reinterpret_cast<T*>(get(pos, sizeof(T)));

				auto _return = *value_r;

				free(value_r);

				return std::move(
					_return
				);
			}

			__forceinline void* __cdecl get_data_pointer() noexcept {
				return local_alloc;
			}

			__forceinline std::size_t __cdecl get_data_size() noexcept {
				return alloc_size;
			}

	#pragma endregion

	#pragma region Set accessors

			//WARNING: appending length to the allocation here will cause exceptions / UB
			__forceinline void __fastcall set(
				
				void* src,
				const std::uintptr_t pos,
				const std::size_t length,
				bool free_src = false
			) noexcept {

				auto dec_alloc = get();

				memcpy(&reinterpret_cast<std::uint8_t*>(dec_alloc)[pos], src, length);

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

			__forceinline void __fastcall set(

				const std::uintptr_t pos,
				const std::uint8_t value,
				const std::size_t size
			) noexcept {

				auto dec_alloc = reinterpret_cast<std::uint8_t*>(get());

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
			__forceinline void __fastcall set(uintptr_t pos, T value) noexcept {
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

			__forceinline void __fastcall swap(void* src, const std::size_t length, const bool free_src = false) noexcept {
				//release current resources
				zero();
				free(local_alloc);
				local_alloc = nullptr;
				alloc_size = 0x0000000000000000ULL;

				auto enc_alloc = algo_inst(src, length);

				alloc_size = length;
				local_alloc = enc_alloc;

				if (free_src)
					free(src);
			}

			//size is only the length in bytes of the allocation to be appended or destroyed
			__forceinline void __fastcall resize(const std::size_t size) noexcept {
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

			__forceinline void __cdecl zero() noexcept {
				set(0x0000000000000000ULL, 0x0ui8, alloc_size);
			}

	#pragma endregion

	#pragma region Operators

			__forceinline qe_malloc& __fastcall operator=(const std::vector<uint8_t>& value) noexcept {
				swap(const_cast<std::vector<uint8_t>*>(&value)->data(), value.size());

				return *this;
			}

			__forceinline __cdecl operator void* () const noexcept {
				return algo_inst(local_alloc, alloc_size);
			}

			template<typename T>
			__forceinline __cdecl operator T* () const noexcept {
				return reinterpret_cast<T*>(algo_inst(local_alloc, alloc_size));
			}

			index_proxy __fastcall operator[](std::size_t index) noexcept {
				return index_proxy(index, *this);
			}

	#pragma endregion

	#pragma region Destructor

			__forceinline void __fastcall destroy(bool zero) noexcept {
				if (local_alloc) {

					if (zero)
						RtlZeroMemory(local_alloc, alloc_size);

					free(local_alloc);
					local_alloc = nullptr;
				}
			}

			__forceinline void __cdecl secure_destroy() noexcept {
				destroy(true);
			}
			__forceinline __cdecl ~qe_malloc() noexcept {
				secure_destroy();
			}

	#pragma endregion
		};

	#pragma endregion

#pragma region Extended Typedefs

#ifdef _WIN64

		typedef qe_uint64 qe_uintptr_t;
		typedef qe_uint64 qe_size_t;

#else

		typedef qe_uint32 qe_uintptr_t;
		typedef qe_uint32 qe_size_t;

#endif

#pragma endregion

	}

#pragma region Static Declarators

	bool qtype_enc::is_init = false;

#pragma endregion

}

#endif
