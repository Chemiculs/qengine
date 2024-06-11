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
		static void __regcall init_constants() noexcept {
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

#pragma region Ctor / Dtor

			__optimized_ctor qe_int8(imut std::int8_t value = 0) noexcept {

				set( value );
			}

			__optimized_dtor ~qe_int8() noexcept {
				
				polyc::unregister_polyc_pointer(&_value);
			}

#pragma endregion

#pragma region Accessors

			__compelled_inline imut std::int8_t __stackcall get() imut noexcept {

				polyc::algo(const_cast<std::int8_t*>(&_value) , sizeof(_value));

				auto value = _value;

				polyc::algo(const_cast<std::int8_t*>(&_value), sizeof(_value));

				return value;
			}

			__compelled_inline imut bool __regcall set(imut std::int8_t value) noexcept {

				// The current method COULD lead to an .data allocation rather than stack, which has it's own security vulnerabilities.
				// Revisit this later and try to perform all decryption routines directly to a local stack-allocated instance so any .data member are never plaintext

				_value = value;

				return polyc::algo(&_value, sizeof(_value));
			}

#pragma endregion

#pragma region Operators

			__compelled_inline qe_int8 __regcall operator+(imut std::int8_t value) imut noexcept {
				return qe_int8(get() + value);
			};

			__compelled_inline qe_int8 __regcall operator-(imut std::int8_t value) imut noexcept {
				return qe_int8(get() - value);
			}

			__compelled_inline qe_int8 __regcall operator/(imut std::int8_t value) imut noexcept {
				return qe_int8(get() / value);
			}

			__compelled_inline qe_int8 __regcall operator*(imut std::int8_t value) imut noexcept {
				return qe_int8(get() * value);
			}

			__compelled_inline qe_int8 __regcall operator&(imut std::int8_t value) imut noexcept {
				return qe_int8(get() & value);
			}

			__compelled_inline qe_int8 __regcall operator|(imut std::int8_t value) imut noexcept {
				return qe_int8(get() | value);
			}

			__compelled_inline qe_int8 __regcall operator%(imut std::int8_t value) imut noexcept {
				return qe_int8(get() % value);
			}

			__compelled_inline qe_int8 __regcall operator^(imut std::int8_t value) imut noexcept {
				return qe_int8(get() ^ value);
			}

			__compelled_inline qe_int8 __regcall operator<<(imut std::int8_t value) imut noexcept {
				return qe_int8(get() << value);
			}

			__compelled_inline qe_int8 __regcall operator>>(imut std::int8_t value) imut noexcept {
				return qe_int8(get() >> value);
			}

			__compelled_inline qe_int8& __regcall operator+=(imut std::int8_t value) {
				set(static_cast<std::int8_t>(get() + value));
				return *this;
			}

			__compelled_inline qe_int8& __regcall operator-=(imut std::int8_t value) noexcept {
				set(static_cast<std::int8_t>(get() - value));
				return *this;
			}

			__singleton qe_int8& __regcall operator*=(imut std::int8_t value) noexcept {

				set(static_cast<std::int8_t>(get() * value));
				return *this;
			}

			__compelled_inline qe_int8& __regcall operator/=(imut std::int8_t value) noexcept {
				set(static_cast<std::int8_t>(get() / value));
				return *this;
			}

			__compelled_inline qe_int8& __regcall operator%=(imut std::int8_t value) noexcept {
				set(static_cast<std::int8_t>(get() % value));
				return *this;
			}

			__compelled_inline qe_int8& __regcall operator^=(imut std::int8_t value) noexcept {
				set(static_cast<std::int8_t>(get() ^ value));
				return *this;
			}

			__compelled_inline qe_int8& __regcall operator&=(imut std::int8_t value) noexcept {
				set(static_cast<std::int8_t>(get() & value));
				return *this;
			}

			__compelled_inline qe_int8& __regcall operator|=(imut std::int8_t value) noexcept {
				set(static_cast<std::int8_t>(get() | value));
				return *this;
			}

			__compelled_inline qe_int8& __regcall operator<<=(imut std::int8_t value) noexcept {
				set(static_cast<std::int8_t>(get() << value));
				return *this;
			}

			__compelled_inline qe_int8& __regcall operator>>=(imut std::int8_t value) noexcept {
				set(static_cast<std::int8_t>(get() >> value));
				return *this;
			}

			__compelled_inline qe_int8& __regcall operator=(imut std::int8_t value) noexcept {
				set(value);
				return *this;
			}

			__compelled_inline __regcall operator std::int8_t() imut noexcept {
				return get();
			}

#pragma endregion
		};

		class qe_uint8 {

		private:

#pragma region Encrypted value

			std::uint8_t _value;

#pragma endregion

		public:

#pragma region Ctor / Dtor

			__optimized_ctor qe_uint8(imut std::uint8_t value = 0) noexcept {
				set(value);
			}

			__optimized_dtor ~qe_uint8() noexcept {

				polyc::unregister_polyc_pointer(&_value);
			}

#pragma endregion

#pragma region Accessors

			__compelled_inline imut std::uint8_t __stackcall get() imut noexcept {

				polyc::algo(const_cast<std::uint8_t*>(&_value), sizeof(_value));

				auto value = _value;

				polyc::algo(const_cast<std::uint8_t*>(&_value), sizeof(_value));

				return value;
			}

			__compelled_inline imut bool __regcall set(imut std::uint8_t value) noexcept {

				_value = value;

				return polyc::algo(&_value, sizeof(_value));
			}

#pragma endregion

#pragma region Operators

			__compelled_inline qe_uint8 __regcall operator+(imut std::uint8_t value) imut noexcept {
				return qe_uint8(get() + value);
			};

			__compelled_inline qe_uint8 __regcall operator-(imut std::uint8_t value) imut noexcept {
				return qe_uint8(get() - value);
			}

			__compelled_inline qe_uint8 __regcall operator/(imut std::uint8_t value) imut noexcept {
				return qe_uint8(get() / value);
			}

			__compelled_inline qe_uint8 __regcall operator*(imut std::uint8_t value) imut noexcept {
				return qe_uint8(get() * value);
			}

			__compelled_inline qe_uint8 __regcall operator&(imut std::uint8_t value) imut noexcept {
				return qe_uint8(get() & value);
			}

			__compelled_inline qe_uint8 __regcall operator|(imut std::uint8_t value) imut noexcept {
				return qe_uint8(get() | value);
			}

			__compelled_inline qe_uint8 __regcall operator%(imut std::uint8_t value) imut noexcept {
				return qe_uint8(get() % value);
			}

			__compelled_inline qe_uint8 __regcall operator^(imut std::uint8_t value) imut noexcept {
				return qe_uint8(get() ^ value);
			}

			__compelled_inline qe_uint8 __regcall operator<<(imut std::uint8_t value) imut noexcept {
				return qe_uint8(get() << value);
			}

			__compelled_inline qe_uint8 __regcall operator>>(imut std::uint8_t value) imut noexcept {
				return qe_uint8(get() >> value);
			}

			__compelled_inline qe_uint8& __regcall operator+=(imut std::uint8_t value) noexcept {
				set(static_cast<std::uint8_t>(get() + value));
				return *this;
			}

			__compelled_inline qe_uint8& __regcall operator-=(imut std::uint8_t value) noexcept {
				set(static_cast<std::uint8_t>(get() - value));
				return *this;
			}

			__compelled_inline qe_uint8& __regcall operator*=(imut std::uint8_t value) noexcept {
				set(static_cast<std::uint8_t>(get() * value));
				return *this;
			}

			__compelled_inline qe_uint8& __regcall operator/=(imut std::uint8_t value) noexcept {
				set(static_cast<std::uint8_t>(get() / value));
				return *this;
			}

			__compelled_inline qe_uint8& __regcall operator%=(imut std::uint8_t value) noexcept {
				set(static_cast<std::uint8_t>(get() % value));
				return *this;
			}

			__compelled_inline qe_uint8& __regcall operator^=(imut std::uint8_t value) noexcept {
				set(static_cast<std::uint8_t>(get() ^ value));
				return *this;
			}

			__compelled_inline qe_uint8& __regcall operator&=(imut std::uint8_t value) noexcept {
				set(static_cast<std::uint8_t>(get() & value));
				return *this;
			}

			__compelled_inline qe_uint8& __regcall operator|=(imut std::uint8_t value) noexcept {
				set(static_cast<std::uint8_t>(get() | value));
				return *this;
			}

			__compelled_inline qe_uint8& __regcall operator<<=(imut std::uint8_t value) noexcept {
				set(static_cast<std::uint8_t>(get() << value));
				return *this;
			}

			__compelled_inline qe_uint8& __regcall operator>>=(imut std::uint8_t value) noexcept {
				set(static_cast<std::uint8_t>(get() >> value));
				return *this;
			}

			__compelled_inline qe_uint8& __regcall operator=(imut std::uint8_t value) noexcept {
				set(value);
				return *this;
			}

			__compelled_inline __regcall operator std::uint8_t() imut noexcept {
				return get();
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

#pragma region Ctor / Dtor

			__optimized_ctor qe_int16(imut std::int16_t value = 0) noexcept {
				set(value);
			}

			__optimized_dtor ~qe_int16() noexcept {

				polyc::unregister_polyc_pointer(&_value);
			}

#pragma endregion

#pragma region Accessors

			__compelled_inline imut std::int16_t __stackcall get() imut noexcept {

				polyc::algo(const_cast<std::int16_t*>(const_cast<std::int16_t*>(&_value) ), sizeof(_value));	//	Return value unused, exceptions thrown here are due to improper compiler settings or end user environment

				auto value = _value;

				polyc::algo(const_cast<std::int16_t*>(&_value), sizeof(_value));

				return value;
			}

			__compelled_inline imut bool __regcall set(imut std::int16_t value) noexcept {

				_value = value;

				return polyc::algo(&_value, sizeof(_value));
			}

#pragma endregion

#pragma region Operators

			__compelled_inline qe_int16 __regcall operator+(imut std::int16_t value) imut noexcept {
				return qe_int16(get() + value);
			};

			__compelled_inline qe_int16 __regcall operator-(imut std::int16_t value) imut noexcept {
				return qe_int16(get() - value);
			}

			__compelled_inline qe_int16 __regcall operator/(imut std::int16_t value) imut noexcept {
				return qe_int16(get() / value);
			}

			__compelled_inline qe_int16 __regcall operator*(imut std::int16_t value) imut noexcept {
				return qe_int16(get() * value);
			}

			__compelled_inline qe_int16 __regcall operator&(imut std::int16_t value) imut noexcept {
				return qe_int16(get() & value);
			}

			__compelled_inline qe_int16 __regcall operator|(imut std::int16_t value) imut noexcept {
				return qe_int16(get() | value);
			}

			__compelled_inline qe_int16 __regcall operator%(imut std::int16_t value) imut noexcept {
				return qe_int16(get() % value);
			}

			__compelled_inline qe_int16 __regcall operator^(imut std::int16_t value) imut noexcept {
				return qe_int16(get() ^ value);
			}

			__compelled_inline qe_int16 __regcall operator<<(imut std::int16_t value) imut noexcept {
				return qe_int16(get() << value);
			}

			__compelled_inline qe_int16 __regcall operator>>(imut std::int16_t value) imut noexcept {
				return qe_int16(get() >> value);
			}

			__compelled_inline qe_int16& __regcall operator+=(imut std::int16_t value) noexcept {
				set(static_cast<std::int16_t>(get() + value));
				return *this;
			}

			__compelled_inline qe_int16& __regcall operator-=(imut std::int16_t value) noexcept {
				set(static_cast<std::int16_t>(get() - value));
				return *this;
			}

			__compelled_inline qe_int16& __regcall operator*=(imut std::int16_t value) noexcept {
				set(static_cast<std::int16_t>(get() * value));
				return *this;
			}

			__compelled_inline qe_int16& __regcall operator/=(imut std::int16_t value) noexcept {
				set(static_cast<std::int16_t>(get() / value));
				return *this;
			}

			__compelled_inline qe_int16& __regcall operator%=(imut std::int16_t value) noexcept {
				set(static_cast<std::int16_t>(get() % value));
				return *this;
			}

			__compelled_inline qe_int16& __regcall operator^=(imut std::int16_t value) noexcept {
				set(static_cast<std::int16_t>(get() ^ value));
				return *this;
			}

			__compelled_inline qe_int16& __regcall operator&=(imut std::int16_t value) noexcept {
				set(static_cast<std::int16_t>(get() & value));
				return *this;
			}

			__compelled_inline qe_int16& __regcall operator|=(imut std::int16_t value) noexcept {
				set(static_cast<std::int16_t>(get() | value));
				return *this;
			}

			__compelled_inline qe_int16& __regcall operator<<=(imut std::int16_t value) noexcept {
				set(static_cast<std::int16_t>(get() << value));
				return *this;
			}

			__compelled_inline qe_int16& __regcall operator>>=(imut std::int16_t value) noexcept {
				set(static_cast<std::int16_t>(get() >> value));
				return *this;
			}

			__compelled_inline qe_int16& __regcall operator=(imut std::int16_t value) noexcept {
				set(value);
				return *this;
			}

			__compelled_inline __regcall operator std::int16_t() imut noexcept {
				return get();
			}

#pragma endregion
		};

		class qe_uint16 {

		private:

#pragma region Encrypted value

			std::uint16_t _value;

#pragma endregion

		public:

#pragma region Ctor / Dtor

			__optimized_ctor qe_uint16(imut std::uint16_t value = 0) noexcept {
				set(value);
			}

			__optimized_dtor qe_uint16() noexcept {

				polyc::unregister_polyc_pointer(&_value);
			}

#pragma endregion

#pragma region Accessors

			__compelled_inline imut std::uint16_t __stackcall get() imut noexcept {

				polyc::algo(const_cast<std::uint16_t*>(&_value), sizeof(_value));

				auto value = _value;

				polyc::algo(const_cast<std::uint16_t*>(&_value), sizeof(_value));

				return value;
			}

			__compelled_inline imut bool __regcall set(imut std::uint16_t value) noexcept {

				_value = value;

				return polyc::algo(&_value, sizeof(_value));
			}

#pragma endregion

#pragma region Operators

			__compelled_inline qe_uint16 __regcall operator+(imut std::uint16_t value) imut noexcept {
				return qe_uint16(get() + value);
			};

			__compelled_inline qe_uint16 __regcall operator-(imut std::uint16_t value) imut noexcept {
				return qe_uint16(get() - value);
			}

			__compelled_inline qe_uint16 __regcall operator/(imut std::uint16_t value) imut noexcept {
				return qe_uint16(get() / value);
			}

			__compelled_inline qe_uint16 __regcall operator*(imut std::uint16_t value) imut noexcept {
				return qe_uint16(get() * value);
			}

			__compelled_inline qe_uint16 __regcall operator&(imut std::uint16_t value) imut noexcept {
				return qe_uint16(get() & value);
			}

			__compelled_inline qe_uint16 __regcall operator|(imut std::uint16_t value) imut noexcept {
				return qe_uint16(get() | value);
			}

			__compelled_inline qe_uint16 __regcall operator%(imut std::uint16_t value) imut noexcept {
				return qe_uint16(get() % value);
			}

			__compelled_inline qe_uint16 __regcall operator^(imut std::uint16_t value) imut noexcept {
				return qe_uint16(get() ^ value);
			}

			__compelled_inline qe_uint16 __regcall operator<<(imut std::uint16_t value) imut noexcept {
				return qe_uint16(get() << value);
			}

			__compelled_inline qe_uint16 __regcall operator>>(imut std::uint16_t value) imut noexcept {
				return qe_uint16(get() >> value);
			}

			__compelled_inline qe_uint16& __regcall operator+=(imut std::uint16_t value) noexcept {
				set(static_cast<std::uint16_t>(get() + value));
				return *this;
			}

			__compelled_inline qe_uint16& __regcall operator-=(imut std::uint16_t value) noexcept {
				set(static_cast<std::uint16_t>(get() - value));
				return *this;
			}

			__compelled_inline qe_uint16& __regcall operator*=(imut std::uint16_t value) noexcept {
				set(static_cast<std::uint16_t>(get() * value));
				return *this;
			}

			__compelled_inline qe_uint16& __regcall operator/=(imut std::uint16_t value) noexcept {
				set(static_cast<std::uint16_t>(get() / value));
				return *this;
			}

			__compelled_inline qe_uint16& __regcall operator%=(imut std::uint16_t value) noexcept {
				set(static_cast<std::uint16_t>(get() % value));
				return *this;
			}

			__compelled_inline qe_uint16& __regcall operator^=(imut std::uint16_t value) noexcept {
				set(static_cast<std::uint16_t>(get() ^ value));
				return *this;
			}

			__compelled_inline qe_uint16& __regcall operator&=(imut std::uint16_t value) noexcept {
				set(static_cast<std::uint16_t>(get() & value));
				return *this;
			}

			__compelled_inline qe_uint16& __regcall operator|=(imut std::uint16_t value) noexcept {
				set(static_cast<std::uint16_t>(get() | value));
				return *this;
			}

			__compelled_inline qe_uint16& __regcall operator<<=(imut std::uint16_t value) noexcept {
				set(static_cast<std::uint16_t>(get() << value));
				return *this;
			}

			__compelled_inline qe_uint16& __regcall operator>>=(imut std::uint16_t value) noexcept {
				set(static_cast<std::uint16_t>(get() >> value));
				return *this;
			}

			__compelled_inline qe_uint16& __regcall operator=(imut std::uint16_t value) noexcept {
				set(value);
				return *this;
			}

			__compelled_inline __regcall operator std::uint16_t() imut noexcept {
				return get();
			}

#pragma endregion
		};

#pragma endregion

#pragma region 32-bit

		class qe_int32 {

		private:

#pragma region Encrypted value

			std::int32_t _value;

#pragma endregion

		public:

#pragma region Ctor / Dtor

			__optimized_ctor qe_int32(imut int value = 0) noexcept {
				set(value);
			}

			__optimized_dtor ~qe_int32() noexcept {

				polyc::unregister_polyc_pointer(&_value);
			}

#pragma endregion

#pragma region Accessors

			__compelled_inline imut std::int32_t __stackcall get() imut noexcept {

				polyc::algo(const_cast<std::int32_t*>(&_value), sizeof(_value));

				auto value = _value;

				polyc::algo(const_cast<std::int32_t*>(&_value), sizeof(_value));

				return value;
			}

			__compelled_inline imut bool __regcall set(imut std::int32_t value) noexcept {

				_value = value;

				return polyc::algo(&_value, sizeof(_value));
			}

#pragma endregion

#pragma region Operators

			__compelled_inline qe_int32 __regcall operator+(imut int value) imut noexcept {
				return qe_int32(get() + value);
			};

			__compelled_inline qe_int32 __regcall operator-(imut int value) imut noexcept {
				return qe_int32(get() - value);
			}

			__compelled_inline qe_int32 __regcall operator/(imut int value) imut noexcept {
				return qe_int32(get() / value);
			}

			__compelled_inline qe_int32 __regcall operator*(imut int value) imut noexcept {
				return qe_int32(get() * value);
			}

			__compelled_inline qe_int32 __regcall operator&(imut int value) imut noexcept {
				return qe_int32(get() & value);
			}

			__compelled_inline qe_int32 __regcall operator|(imut int value) imut noexcept {
				return qe_int32(get() | value);
			}

			__compelled_inline qe_int32 __regcall operator%(imut int value) imut noexcept {
				return qe_int32(get() % value);
			}

			__compelled_inline qe_int32 __regcall operator^(imut int value) imut noexcept {
				return qe_int32(get() ^ value);
			}

			__compelled_inline qe_int32 __regcall operator<<(imut int value) imut noexcept {
				return qe_int32(get() << value);
			}

			__compelled_inline qe_int32 __regcall operator>>(imut int value) imut noexcept {
				return qe_int32(get() >> value);
			}

			__compelled_inline qe_int32& __regcall operator+=(imut int value) noexcept {
				set(static_cast<int>(get() + value));
				return *this;
			}

			__compelled_inline qe_int32& __regcall operator-=(imut int value) noexcept {
				set(static_cast<int>(get() - value));
				return *this;
			}

			__compelled_inline qe_int32& __regcall operator*=(imut int value) noexcept {
				set(static_cast<int>(get() * value));
				return *this;
			}

			__compelled_inline qe_int32& __regcall operator/=(imut int value) noexcept {
				set(static_cast<int>(get() / value));
				return *this;
			}

			__compelled_inline qe_int32& __regcall operator%=(imut int value) noexcept {
				set(static_cast<int>(get() % value));
				return *this;
			}

			__compelled_inline qe_int32& __regcall operator^=(imut int value) noexcept {
				set(static_cast<int>(get() ^ value));
				return *this;
			}

			__compelled_inline qe_int32& __regcall operator&=(imut int value) noexcept {
				set(static_cast<int>(get() & value));
				return *this;
			}

			__compelled_inline qe_int32& __regcall operator|=(imut int value) noexcept {
				set(static_cast<int>(get() | value));
				return *this;
			}

			__compelled_inline qe_int32& __regcall operator<<=(imut int value) noexcept {
				set(static_cast<int>(get() << value));
				return *this;
			}

			__compelled_inline qe_int32& __regcall operator>>=(imut int value) noexcept {
				set(static_cast<int>(get() >> value));
				return *this;
			}

			__compelled_inline qe_int32& __regcall operator=(imut int value) noexcept {
				set(value);
				return *this;
			}

			__compelled_inline __regcall operator int() imut noexcept {
				return get();
			}

#pragma endregion
		};

		class qe_uint32 {

		private:

#pragma region Encrypted value

			std::uint32_t _value;

#pragma endregion

		public:

#pragma region Ctor / Dtor

			__optimized_ctor qe_uint32(imut std::uint32_t value = 0) noexcept {
				set(value);
			}

			__optimized_dtor ~qe_uint32() noexcept {

				polyc::unregister_polyc_pointer(&_value);
			}

#pragma endregion

#pragma region Accessors

			__compelled_inline imut std::uint32_t __stackcall get() imut noexcept {

				polyc::algo(const_cast<std::uint32_t*>(&_value), sizeof(_value));

				auto value = _value;

				polyc::algo(const_cast<std::uint32_t*>(&_value), sizeof(_value));

				return value;
			}

			__compelled_inline imut bool __regcall set(imut std::uint32_t value) noexcept {

				_value = value;

				return polyc::algo(&_value, sizeof(_value));
			}

#pragma endregion

#pragma region Operators

			__compelled_inline qe_uint32 __regcall operator+(imut std::uint32_t value) imut noexcept {
				return qe_uint32(get() + value);
			};

			__compelled_inline qe_uint32 __regcall operator-(imut std::uint32_t value) imut noexcept {
				return qe_uint32(get() - value);
			}

			__compelled_inline qe_uint32 __regcall operator/(imut std::uint32_t value) imut noexcept {
				return qe_uint32(get() / value);
			}

			__compelled_inline qe_uint32 __regcall operator*(imut std::uint32_t value) imut noexcept {
				return qe_uint32(get() * value);
			}

			__compelled_inline qe_uint32 __regcall operator&(imut std::uint32_t value) imut noexcept {
				return qe_uint32(get() & value);
			}

			__compelled_inline qe_uint32 __regcall operator|(imut std::uint32_t value) imut noexcept {
				return qe_uint32(get() | value);
			}

			__compelled_inline qe_uint32 __regcall operator%(imut std::uint32_t value) imut noexcept {
				return qe_uint32(get() % value);
			}

			__compelled_inline qe_uint32 __regcall operator^(imut std::uint32_t value) imut noexcept {
				return qe_uint32(get() ^ value);
			}

			__compelled_inline qe_uint32 __regcall operator<<(imut std::uint32_t value) imut noexcept {
				return qe_uint32(get() << value);
			}

			__compelled_inline qe_uint32 __regcall operator>>(imut std::uint32_t value) imut noexcept {
				return qe_uint32(get() >> value);
			}

			__compelled_inline qe_uint32& __regcall operator+=(imut std::uint32_t value) noexcept {
				set(static_cast<int>(get() + value));
				return *this;
			}

			__compelled_inline qe_uint32& __regcall operator-=(imut std::uint32_t value) noexcept {
				set(static_cast<int>(get() - value));
				return *this;
			}

			__compelled_inline qe_uint32& __regcall operator*=(imut std::uint32_t value) noexcept {
				set(static_cast<int>(get() * value));
				return *this;
			}

			__compelled_inline qe_uint32& __regcall operator/=(imut std::uint32_t value) noexcept {
				set(static_cast<int>(get() / value));
				return *this;
			}

			__compelled_inline qe_uint32& __regcall operator%=(imut std::uint32_t value) noexcept {
				set(static_cast<int>(get() % value));
				return *this;
			}

			__compelled_inline qe_uint32& __regcall operator^=(imut std::uint32_t value) noexcept {
				set(static_cast<int>(get() ^ value));
				return *this;
			}

			__compelled_inline qe_uint32& __regcall operator&=(imut std::uint32_t value) noexcept {
				set(static_cast<int>(get() & value));
				return *this;
			}

			__compelled_inline qe_uint32& __regcall operator|=(imut std::uint32_t value) noexcept {
				set(static_cast<int>(get() | value));
				return *this;
			}

			__compelled_inline qe_uint32& __regcall operator<<=(imut std::uint32_t value) noexcept {
				set(static_cast<int>(get() << value));
				return *this;
			}

			__compelled_inline qe_uint32& __regcall operator>>=(imut std::uint32_t value) noexcept {
				set(static_cast<int>(get() >> value));
				return *this;
			}

			__compelled_inline qe_uint32& __regcall operator=(imut std::uint32_t value) noexcept {
				set(value);
				return *this;
			}

			__compelled_inline __regcall operator std::uint32_t() imut noexcept {
				return get();
			}

#pragma endregion
		};

#pragma endregion

#pragma region 64-bit

#ifdef _WIN64

		class qe_int64 {

		private:

#pragma region Encrypted value

			std::int64_t _value;

#pragma endregion

		public:

#pragma region Ctor / Dtor

			__optimized_ctor qe_int64(imut std::int64_t value = 0) noexcept {
				set(value);
			}

			__optimized_dtor ~qe_int64() noexcept {

				polyc::unregister_polyc_pointer(&_value);
			}

#pragma endregion

#pragma region Accessors

			__compelled_inline imut std::int64_t __stackcall get() imut noexcept {

				polyc::algo(const_cast<std::int64_t*>(&_value), sizeof(_value));

				auto value = _value;

				polyc::algo(const_cast<std::int64_t*>(&_value), sizeof(_value));

				return value;
			}

			__compelled_inline imut bool __regcall set(imut std::int64_t value) noexcept {

				_value = value;

				return polyc::algo(&_value, sizeof(_value));
			}
#pragma endregion

#pragma region Operators

			__compelled_inline qe_int64 __regcall operator+(imut std::int64_t value) imut noexcept {
				return qe_int64(get() + value);
			};

			__compelled_inline qe_int64 __regcall operator-(imut std::int64_t value) imut noexcept {
				return qe_int64(get() - value);
			}

			__compelled_inline qe_int64 __regcall operator/(imut std::int64_t value) imut noexcept {
				return qe_int64(get() / value);
			}

			__compelled_inline qe_int64 __regcall operator*(imut std::int64_t value) imut noexcept {
				return qe_int64(get() * value);
			}

			__compelled_inline qe_int64 __regcall operator&(imut std::int64_t value) imut noexcept {
				return qe_int64(get() & value);
			}

			__compelled_inline qe_int64 __regcall operator|(imut std::int64_t value) imut noexcept {
				return qe_int64(get() | value);
			}

			__compelled_inline qe_int64 __regcall operator%(imut std::int64_t value) imut noexcept {
				return qe_int64(get() % value);
			}

			__compelled_inline qe_int64 __regcall operator^(imut std::int64_t value) imut noexcept {
				return qe_int64(get() ^ value);
			}

			__compelled_inline qe_int64 __regcall operator<<(imut std::int64_t value) imut noexcept {
				return qe_int64(get() << value);
			}

			__compelled_inline qe_int64 __regcall operator>>(imut std::int64_t value) imut noexcept {
				return qe_int64(get() >> value);
			}

			__compelled_inline qe_int64& __regcall operator+=(imut std::int64_t value) noexcept {
				set(static_cast<int>(get() + value));
				return *this;
			}

			__compelled_inline qe_int64& __regcall operator-=(imut std::int64_t value) noexcept {
				set(static_cast<int>(get() - value));
				return *this;
			}

			__compelled_inline qe_int64& __regcall operator*=(imut std::int64_t value) noexcept {
				set(static_cast<int>(get() * value));
				return *this;
			}

			__compelled_inline qe_int64& __regcall operator/=(imut std::int64_t value) noexcept {
				set(static_cast<int>(get() / value));
				return *this;
			}

			__compelled_inline qe_int64& __regcall operator%=(imut std::int64_t value) noexcept {
				set(static_cast<int>(get() % value));
				return *this;
			}

			__compelled_inline qe_int64& __regcall operator^=(imut std::int64_t value) noexcept {
				set(static_cast<int>(get() ^ value));
				return *this;
			}

			__compelled_inline qe_int64& __regcall operator&=(imut std::int64_t value) noexcept {
				set(static_cast<int>(get() & value));
				return *this;
			}

			__compelled_inline qe_int64& __regcall operator|=(imut std::int64_t value) noexcept {
				set(static_cast<int>(get() | value));
				return *this;
			}

			__compelled_inline qe_int64& __regcall operator<<=(imut std::int64_t value) noexcept {
				set(static_cast<int>(get() << value));
				return *this;
			}

			__compelled_inline qe_int64& __regcall operator>>=(imut std::int64_t value) noexcept {
				set(static_cast<int>(get() >> value));
				return *this;
			}

			__compelled_inline qe_int64& __regcall operator=(imut std::int64_t value) noexcept {
				set(value);
				return *this;
			}

			__compelled_inline __stackcall operator std::int64_t() imut noexcept {
				return get();
			}

#pragma endregion
		};

		class qe_uint64 {

		private:

#pragma region Encrypted value

			std::uint64_t _value;

#pragma endregion

		public:

#pragma region Ctor / Dtor

			__optimized_ctor qe_uint64(imut std::uint64_t value = 0) {
				set(value);
			}

			__optimized_dtor ~qe_uint64() noexcept {

				polyc::unregister_polyc_pointer(&_value);
			}

#pragma endregion

#pragma region Accessors

			__compelled_inline imut std::uint64_t __stackcall get() imut noexcept {

				polyc::algo(const_cast<std::uint64_t*>(&_value), sizeof(_value));

				auto value = _value;

				polyc::algo(const_cast<std::uint64_t*>(&_value), sizeof(_value));

				return value;
			}

			__compelled_inline imut bool __regcall set(imut std::uint64_t value) noexcept {

				_value = value;

				return polyc::algo(&_value, sizeof(_value));
			}

#pragma endregion

#pragma region Operators

			__compelled_inline qe_uint64 __regcall operator+(imut std::uint64_t value) imut noexcept {
				return qe_uint64(get() + value);
			};

			__compelled_inline qe_uint64 __regcall operator-(imut std::uint64_t value) imut noexcept {
				return qe_uint64(get() - value);
			}

			__compelled_inline qe_uint64 __regcall operator/(imut std::uint64_t value) imut noexcept {
				return qe_uint64(get() / value);
			}

			__compelled_inline qe_uint64 __regcall operator*(imut std::uint64_t value) imut noexcept {
				return qe_uint64(get() * value);
			}

			__compelled_inline qe_uint64 __regcall operator&(imut std::uint64_t value) imut noexcept {
				return qe_uint64(get() & value);
			}

			__compelled_inline qe_uint64 __regcall operator|(imut std::uint64_t value) imut noexcept {
				return qe_uint64(get() | value);
			}

			__compelled_inline qe_uint64 __regcall operator%(imut std::uint64_t value) imut noexcept {
				return qe_uint64(get() % value);
			}

			__compelled_inline qe_uint64 __regcall operator^(imut std::uint64_t value) imut noexcept {
				return qe_uint64(get() ^ value);
			}

			__compelled_inline qe_uint64 __regcall operator<<(imut std::uint64_t value) imut noexcept {
				return qe_uint64(get() << value);
			}

			__compelled_inline qe_uint64 __regcall operator>>(imut std::uint64_t value) imut noexcept {
				return qe_uint64(get() >> value);
			}

			__compelled_inline qe_uint64& __regcall operator+=(imut std::uint64_t value) noexcept {
				set(static_cast<int>(get() + value));
				return *this;
			}

			__compelled_inline qe_uint64& __regcall operator-=(imut std::uint64_t value) noexcept {
				set(static_cast<int>(get() - value));
				return *this;
			}

			__compelled_inline qe_uint64& __regcall operator*=(imut std::uint64_t value) noexcept {
				set(static_cast<int>(get() * value));
				return *this;
			}

			__compelled_inline qe_uint64& __regcall operator/=(imut std::uint64_t value) noexcept {
				set(static_cast<int>(get() / value));
				return *this;
			}

			__compelled_inline qe_uint64& __regcall operator%=(imut std::uint64_t value) noexcept {
				set(static_cast<int>(get() % value));
				return *this;
			}

			__compelled_inline qe_uint64& __regcall operator^=(imut std::uint64_t value) noexcept {
				set(static_cast<int>(get() ^ value));
				return *this;
			}

			__compelled_inline qe_uint64& __regcall operator&=(imut std::uint64_t value) noexcept {
				set(static_cast<int>(get() & value));
				return *this;
			}

			__compelled_inline qe_uint64& __regcall operator|=(imut std::uint64_t value) noexcept {
				set(static_cast<int>(get() | value));
				return *this;
			}

			__compelled_inline qe_uint64& __regcall operator<<=(imut std::uint64_t value) noexcept {
				set(static_cast<int>(get() << value));
				return *this;
			}

			__compelled_inline qe_uint64& __regcall operator>>=(imut std::uint64_t value) noexcept {
				set(static_cast<int>(get() >> value));
				return *this;
			}

			__compelled_inline qe_uint64& __regcall operator=(imut std::uint64_t value) noexcept {
				set(value);
				return *this;
			}

			__compelled_inline __stackcall operator std::uint64_t() imut noexcept {
				return get();
			}

#pragma endregion
		};

#endif

#pragma endregion

#pragma endregion

#pragma region Floating Point

#pragma region 32-bit

		class qe_float {

		private:

			float _value;

		public:

#pragma region Ctor / Dtor

			__compelled_inline __fpcall qe_float(imut float value) noexcept {
				set(value);
			}

			__optimized_dtor ~qe_float() noexcept {

				polyc::unregister_polyc_pointer(&_value);
			}

#pragma endregion

#pragma region Accessors

			__compelled_inline imut float __stackcall get() imut noexcept {

				polyc::algo(const_cast<float*>(&_value), sizeof(_value));

				auto value = _value;

				polyc::algo(const_cast<float*>(&_value), sizeof(_value));

				return value;
			}

			__compelled_inline imut bool __fpcall set(imut float value) noexcept {

				_value = value;

				return polyc::algo(&_value, sizeof(_value));
			}

#pragma endregion

#pragma region Operators

			__compelled_inline qe_float __fpcall operator+(imut float value) imut noexcept {
				return qe_float(get() + value);
			};

			__compelled_inline qe_float __fpcall operator-(imut float value) imut noexcept {
				return qe_float(get() - value);
			}

			__compelled_inline qe_float __fpcall operator/(imut float value) imut noexcept {
				return qe_float(get() / value);
			}

			__compelled_inline qe_float __fpcall operator*(imut float value) imut noexcept {
				return qe_float(get() * value);
			}

			__compelled_inline qe_float& __fpcall operator+=(imut float value) noexcept {
				_value = algo_t_inst(get() + value);
				return *this;
			}

			__compelled_inline qe_float& __fpcall operator-=(imut float value) noexcept {
				_value = algo_t_inst(get() - value);
				return *this;
			}

			__compelled_inline qe_float& __fpcall operator*=(imut float value) noexcept {
				_value = algo_t_inst(get() * value);
				return *this;
			}

			__compelled_inline qe_float& __fpcall operator/=(imut float value) noexcept {
				_value = algo_t_inst(get() / value);
				return *this;
			}

			__compelled_inline qe_float& __fpcall operator=(imut float value) noexcept {
				set(value);
				return *this;
			}

			__compelled_inline __stackcall operator float() imut noexcept {
				return get();
			}

#pragma endregion
		};

#pragma endregion

#pragma region 64-bit

#ifdef _WIN64

		class qe_double {

		private:

			double _value;

		public:

#pragma region Ctor / Dtor

			__compelled_inline __fpcall qe_double(imut double value = static_cast<double>(0.0f)) {
				set(value);
			}

#pragma endregion

#pragma region Accessors

			__compelled_inline double __stackcall get() imut noexcept {
				return get();
			}

			__compelled_inline void __fpcall set(imut double value) noexcept {
				set(value);
			}

#pragma endregion

#pragma region Operators

			__compelled_inline qe_double __fpcall operator+(imut double value) imut noexcept {
				return qe_double(get() + value);
			};

			__compelled_inline qe_double __fpcall operator-(imut double value) imut noexcept {
				return qe_double(get() - value);
			}

			__compelled_inline qe_double __fpcall operator/(imut double value) imut noexcept {
				return qe_double(get() / value);
			}

			__compelled_inline qe_double __fpcall operator*(imut double value) imut noexcept {
				return qe_double(get() * value);
			}

			__compelled_inline qe_double& __fpcall operator+=(imut double value) noexcept {
				_value = algo_t_inst(get() + value);
				return *this;
			}

			__compelled_inline qe_double& __fpcall operator-=(imut double value) noexcept {
				_value = algo_t_inst(get() - value);
				return *this;
			}

			__compelled_inline qe_double& __fpcall operator*=(imut double value) noexcept {
				_value = algo_t_inst(get() * value);
				return *this;
			}

			__compelled_inline qe_double& __fpcall operator/=(imut double value) noexcept {
				_value = algo_t_inst(get() / value);
				return *this;
			}

			__compelled_inline qe_double& __fpcall operator=(imut double value) noexcept {
				set(value);
				return *this;
			}

			__compelled_inline __stackcall operator double() imut noexcept {
				return get();
			}

#pragma endregion
		};

#endif

#pragma endregion

#pragma endregion

#pragma region SSE Types

		//SSE
	#ifdef __SSE__

		class qe_m128 {

		private:

			__m128 _value;

		public:

#pragma region Ctor / Dtor

			__compelled_inline __fpcall qe_m128(imut __m128 value) noexcept {
				set(value);
			}

			__optimized_dtor ~qe_m128() noexcept {

				polyc::unregister_polyc_pointer(&_value);
			}

#pragma endregion

#pragma region Accessors

			__compelled_inline imut __m128 __stackcall get() imut noexcept {

				polyc::algo(const_cast<__m128*>(&_value), sizeof(_value));

				auto value = _value;

				polyc::algo(const_cast<__m128*>(&_value), sizeof(_value));

				return value;
			}

			__compelled_inline imut bool __fpcall set(imut __m128 value) noexcept {

				_value = value;

				return polyc::algo(&_value, sizeof(_value));
			}
#pragma endregion

#pragma region Operators
	#ifdef __clang__ // msvc does not support math operatotions on vector types

			__compelled_inline qe_m128 __fpcall operator+(imut __m128 value) imut noexcept {
				return qe_m128(get() + value);
			};

			__compelled_inline qe_m128 __fpcall operator-(imut __m128 value) imut noexcept {
				return qe_m128(get() - value);
			}

			__compelled_inline qe_m128 __fpcall operator/(imut __m128 value) imut noexcept {
				return qe_m128((imut __m128)get() / value);
			}

			__compelled_inline qe_m128 __fpcall operator*(imut __m128 value) imut noexcept {
				return qe_m128(get() * value);
			}

			__compelled_inline qe_m128& __fpcall operator+=(imut __m128 value) noexcept {
				_value = algo_t_inst(algo_t_inst(value) + value);
				return *this;
			}

			__compelled_inline qe_m128& __fpcall operator-=(imut __m128 value) noexcept {
				_value = algo_t_inst(get() - value);
				return *this;
			}

			__compelled_inline qe_m128& __fpcall operator*=(imut __m128 value) noexcept {
				_value = algo_t_inst(get() * value);
				return *this;
			}

			__compelled_inline qe_m128& __fpcall operator/=(imut __m128 value) noexcept {
				_value = algo_t_inst(get() / value);
				return *this;
			}

	#endif

			__compelled_inline qe_m128& __fpcall operator=(imut __m128 value) noexcept {
				set(value);
				return *this;
			}

			__compelled_inline __stackcall operator __m128() imut noexcept {
				return get();
			}

#pragma endregion
		};

	#ifdef __SSE2__

		class qe_m128i {

		private:

			__m128i _value;

		public:

#pragma region Ctor / Dtor

			__compelled_inline __fpcall qe_m128i(imut __m128i value) noexcept {
				set(value);
			}

			__optimized_dtor ~qe_m128i() noexcept {

				polyc::unregister_polyc_pointer(&_value);
			}

#pragma endregion

#pragma region Accessors

			__compelled_inline imut __m128i __stackcall get() imut noexcept {

				polyc::algo(const_cast<__m128i*>(&_value), sizeof(_value));

				auto value = _value;

				polyc::algo(const_cast<__m128i*>(&_value), sizeof(_value));

				return value;
			}

			__compelled_inline imut bool __fpcall set(imut __m128i value) noexcept {

				_value = value;

				return polyc::algo(&_value, sizeof(_value));
			}

#pragma endregion

#pragma region Operators

	#ifdef __clang__ // msvc does not support math operators on vector types

			__compelled_inline qe_m128i __fpcall operator+(imut __m128i value) imut noexcept {
				return qe_m128i(get() + value);
			};

			__compelled_inline qe_m128i __fpcall operator-(imut __m128i value) imut noexcept {
				return qe_m128i(get() - value);
			}

			__compelled_inline qe_m128i __fpcall operator/(imut __m128i value) imut noexcept {
				return qe_m128i((imut __m128i)get() / value);
			}

			__compelled_inline qe_m128i __fpcall operator*(imut __m128i value) imut noexcept {
				return qe_m128i(get() * value);
			}

			__compelled_inline qe_m128i& __fpcall operator+=(imut __m128i value) noexcept {
				_value = algo_t_inst(algo_t_inst(value) + value);
				return *this;
			}

			__compelled_inline qe_m128i& __fpcall operator-=(imut __m128i value) noexcept {
				_value = algo_t_inst(get() - value);
				return *this;
			}

			__compelled_inline qe_m128i& __fpcall operator*=(imut __m128i value) noexcept {
				_value = algo_t_inst(get() * value);
				return *this;
			}

			__compelled_inline qe_m128i& __fpcall operator/=(imut __m128i value) noexcept {
				_value = algo_t_inst(get() / value);
				return *this;
			}

	#endif

			__compelled_inline qe_m128i& __fpcall operator=(imut __m128i value) noexcept {
				set(value);
				return *this;
			}

			__compelled_inline __stackcall operator __m128i() imut noexcept {
				return get();
			}

#pragma endregion
		};

		class qe_m128d {

		private:

			__m128d _value;

		public:

#pragma region Ctor / Dtor

			__compelled_inline __fpcall qe_m128d(imut __m128d value) noexcept {
				set(value);
			}

			__optimized_dtor ~qe_m128d() noexcept {

				polyc::unregister_polyc_pointer(&_value);
			}

#pragma endregion

#pragma region Accessors

			__compelled_inline imut __m128d __stackcall get() imut noexcept {

				polyc::algo(const_cast<__m128d*>(&_value), sizeof(_value));

				auto value = _value;

				polyc::algo(const_cast<__m128d*>(&_value), sizeof(_value));

				return value;
			}

			__compelled_inline imut bool __fpcall set(imut __m128d value) noexcept {

				_value = value;

				return polyc::algo(&_value, sizeof(_value));
			}
#pragma endregion

#pragma region Operators
	#ifdef __clang__ // msvc does not support math operators on vector types

			__compelled_inline qe_m128d __fpcall operator+(imut __m128d value) imut noexcept {
				return qe_m128d(get() + value);
			};

			__compelled_inline qe_m128d __fpcall operator-(imut __m128d value) imut noexcept {
				return qe_m128d(get() - value);
			}

			__compelled_inline qe_m128d __fpcall operator/(imut __m128d value) imut noexcept {
				return qe_m128d((imut __m128d)get() / value);
			}

			__compelled_inline qe_m128d __fpcall operator*(imut __m128d value) imut noexcept {
				return qe_m128d(get() * value);
			}

	#endif

	#ifdef __clang__

			__compelled_inline qe_m128d& __fpcall operator+=(imut __m128d value) noexcept {
				_value = algo_t_inst(algo_t_inst(value) + value);
				return *this;
			}

			__compelled_inline qe_m128d& __fpcall operator-=(imut __m128d value) noexcept {
				_value = algo_t_inst(get() - value);
				return *this;
			}

			__compelled_inline qe_m128d& __fpcall operator*=(imut __m128d value) noexcept {
				_value = algo_t_inst(get() * value);
				return *this;
			}

			__compelled_inline qe_m128d& __fpcall operator/=(imut __m128d value) noexcept {
				_value = algo_t_inst(get() / value);
				return *this;
			}

	#endif

			__compelled_inline qe_m128d& __fpcall operator=(imut __m128d value) noexcept {
				set(value);
				return *this;
			}

			__compelled_inline __stackcall operator __m128d() imut noexcept {
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

#pragma region Ctor / Dtor

			__compelled_inline __fpcall qe_m256(imut __m256 value) noexcept {
				set(value);
			}
			
			__optimized_dtor ~qe_m256() noexcept {

				polyc::unregister_polyc_pointer(&_value);
			}

#pragma endregion

#pragma region Accessors

			__compelled_inline imut __m256 __stackcall get() imut noexcept {

				polyc::algo(const_cast<__m256*>(&_value), sizeof(_value));

				auto value = _value;

				polyc::algo(const_cast<__m256*>(&_value), sizeof(_value));

				return value;
			}

			__compelled_inline imut bool __fpcall set(imut __m256 value) noexcept {

				_value = value;

				return polyc::algo(&_value, sizeof(_value));
			}

#pragma endregion

#pragma region Operators

	#ifdef __clang__ // msvc does not support math operators on vector types

			__compelled_inline qe_m256 __fpcall operator+(imut __m256 value) imut noexcept {
				return qe_m256(get() + value);
			};

			__compelled_inline qe_m256 __fpcall operator-(imut __m256 value) imut noexcept {
				return qe_m256(get() - value);
			}

			__compelled_inline qe_m256 __fpcall operator/(imut __m256 value) imut noexcept {
				return qe_m256((imut __m256)get() / value);
			}

			__compelled_inline qe_m256 __fpcall operator*(imut __m256 value) imut noexcept {
				return qe_m256(get() * value);
			}

			__compelled_inline qe_m256& __fpcall operator+=(imut __m256 value) noexcept {
				_value = algo_t_inst(algo_t_inst(value) + value);
				return *this;
			}

			__compelled_inline qe_m256& __fpcall operator-=(imut __m256 value) noexcept {
				_value = algo_t_inst(get() - value);
				return *this;
			}

			__compelled_inline qe_m256& __fpcall operator*=(imut __m256 value) noexcept {
				_value = algo_t_inst(get() * value);
				return *this;
			}

			__compelled_inline qe_m256& __fpcall operator/=(imut __m256 value) noexcept {
				_value = algo_t_inst(get() / value);
				return *this;
			}

	#endif

			__compelled_inline qe_m256& __fpcall operator=(imut __m256 value) noexcept {
				set(value);
				return *this;
			}

			__compelled_inline __stackcall operator __m256() imut noexcept {
				return get();
			}

#pragma endregion
		};

		class qe_m256i {

		private:

			__m256i _value;

		public:

#pragma region Ctor / Dtor

			__compelled_inline __fpcall qe_m256i(imut __m256i value) noexcept {
				set(value);
			}

			__optimized_dtor ~qe_m256i() noexcept {

				polyc::unregister_polyc_pointer(&_value);
			}

#pragma endregion

#pragma region Accessors

			__compelled_inline imut __m256i __stackcall get() imut noexcept {

				polyc::algo(const_cast<__m256i*>(&_value), sizeof(_value));

				auto value = _value;

				polyc::algo(const_cast<__m256i*>(&_value), sizeof(_value));

				return value;
			}

			__compelled_inline imut bool __fpcall set(imut __m256i value) noexcept {

				_value = value;

				return polyc::algo(&_value, sizeof(_value));
			}

#pragma endregion

#pragma region Operators
	#ifdef __clang__ // msvc does not support math operators on vector types

			__compelled_inline qe_m256i __fpcall operator+(imut __m256i value) imut noexcept {
				return qe_m256i(get() + value);
			};

			__compelled_inline qe_m256i __fpcall operator-(imut __m256i value) imut noexcept {
				return qe_m256i(get() - value);
			}

			__compelled_inline qe_m256i __fpcall operator/(imut __m256i value) imut noexcept {
				return qe_m256i((imut __m256i)get() / value);
			}

			__compelled_inline qe_m256i __fpcall operator*(imut __m256i value) imut noexcept {
				return qe_m256i(get() * value);
			}

			__compelled_inline qe_m256i& __fpcall operator+=(imut __m256i value) noexcept {
				_value = algo_t_inst(algo_t_inst(value) + value);
				return *this;
			}

			__compelled_inline qe_m256i& __fpcall operator-=(imut __m256i value) noexcept {
				_value = algo_t_inst(get() - value);
				return *this;
			}

			__compelled_inline qe_m256i& __fpcall operator*=(imut __m256i value) noexcept {
				_value = algo_t_inst(get() * value);
				return *this;
			}

			__compelled_inline qe_m256i& __fpcall operator/=(imut __m256i value) noexcept {
				_value = algo_t_inst(get() / value);
				return *this;
			}

	#endif

			__compelled_inline qe_m256i& __fpcall operator=(imut __m256i value) noexcept {
				set(value);
				return *this;
			}

			__compelled_inline __stackcall operator __m256i() imut noexcept {
				return get();
			}

#pragma endregion
		};

		class qe_m256d {

		private:

			__m256d _value;

		public:

#pragma region Ctor / Dtor

			__compelled_inline __fpcall qe_m256d(imut __m256d value) noexcept {
				set(value);
			}

			__optimized_dtor ~qe_m256d() noexcept {

				polyc::unregister_polyc_pointer(&_value);
			}

#pragma endregion

#pragma region Accessors

			__compelled_inline imut __m256d __stackcall get() imut noexcept {

				polyc::algo(const_cast<__m256d*>(&_value), sizeof(_value));

				auto value = _value;

				polyc::algo(const_cast<__m256d*>(&_value), sizeof(_value));

				return value;
			}

			__compelled_inline imut bool __fpcall set(imut __m256d value) noexcept {

				_value = value;

				return polyc::algo(&_value, sizeof(_value));
			}


#pragma endregion

#pragma region Operators

	#ifdef __clang__ // msvc does not support math operators on vector types

			__compelled_inline qe_m256d __fpcall operator+(imut __m256d value) imut noexcept {
				return qe_m256d(get() + value);
			};

			__compelled_inline qe_m256d __fpcall operator-(imut __m256d value) imut noexcept {
				return qe_m256d(get() - value);
			}

			__compelled_inline qe_m256d __fpcall operator/(imut __m256d value) imut noexcept {
				return qe_m256d((imut __m256d)get() / value);
			}

			__compelled_inline qe_m256d __fpcall operator*(imut __m256d value) imut noexcept {
				return qe_m256d(get() * value);
			}

	#endif

	#ifdef __clang__

			__compelled_inline qe_m256d& __fpcall operator+=(imut __m256d value) noexcept {
				_value = algo_t_inst(algo_t_inst(value) + value);
				return *this;
			}

			__compelled_inline qe_m256d& __fpcall operator-=(imut __m256d value) noexcept {
				_value = algo_t_inst(get() - value);
				return *this;
			}

			__compelled_inline qe_m256d& __fpcall operator*=(imut __m256d value) noexcept {
				_value = algo_t_inst(get() * value);
				return *this;
			}

			__compelled_inline qe_m256d& __fpcall operator/=(imut __m256d value) noexcept {
				_value = algo_t_inst(get() / value);
				return *this;
			}

	#endif

			__compelled_inline qe_m256d& __fpcall operator=(imut __m256d value) noexcept {
				set(value);
				return *this;
			}

			__compelled_inline __stackcall operator __m256d() imut noexcept {
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

#pragma region Ctor / Dtor

			__compelled_inline __stackcall qe_string(imut std::string value) noexcept {

				if (!is_init) {
					init_constants();
				}
				
				set(value);
			}

			__optimized_ctor qe_string(imut char* value = "") noexcept {

				if (!is_init) {
					init_constants();
				}

				set(std::string(value));
			}

			__optimized_dtor ~qe_string() noexcept {

				polyc::unregister_polyc_pointer(_value.c_str());
			}

#pragma endregion

#pragma region Accessors

			__compelled_inline imut std::string __stackcall get() imut noexcept {

				polyc::algo(const_cast<char*>(_value.c_str()), _value.length());

				auto value = _value;

				polyc::algo(const_cast<char*>(_value.c_str()), _value.length());

				return value;
			}

			__compelled_inline imut bool __stackcall set( imut std::string value ) noexcept {

				_value = value;

				return polyc::algo(const_cast<char*>(_value.c_str()), _value.length());
			}

#pragma endregion	

#pragma region Operators

			__compelled_inline qe_string __stackcall operator+(imut std::string& value) imut noexcept {
				return qe_string( get() + value);
			};

			__compelled_inline qe_string& __stackcall operator+=(imut std::string& value) noexcept {
				set(static_cast<std::string>( get() + value ));
				return *this;
			}

			__compelled_inline qe_string& __stackcall operator=(imut std::string& value) noexcept {
				set(value);
				return *this;
			}

			__compelled_inline __stackcall operator std::string() imut noexcept {
				return get();
			}

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

#pragma region Ctor / Dtor

			__compelled_inline __stackcall qe_wstring(imut std::wstring value) noexcept {

				if (!is_init) {
					init_constants();
				}

				set(value);
			}

			__optimized_ctor qe_wstring(imut wchar_t* value = L"") noexcept {

				if (!is_init) {
					init_constants();
				}

				set(std::wstring(value));
			}

			__optimized_dtor ~qe_wstring() noexcept {

				polyc::unregister_polyc_pointer(_value.c_str());
			}

#pragma endregion

#pragma region Accessors

			__compelled_inline imut std::wstring __stackcall get() imut noexcept {

				polyc::algo(const_cast<wchar_t*>(_value.c_str()), _value.length() * sizeof(wchar_t));

				auto value = _value;

				polyc::algo(const_cast<wchar_t*>(_value.c_str()), _value.length() * sizeof(wchar_t));

				return value;
			}

			__compelled_inline imut bool __stackcall set(imut std::wstring value) noexcept {

				_value = value;

				return polyc::algo(const_cast<wchar_t*>(_value.c_str()), _value.length() * sizeof(wchar_t));
			}

#pragma endregion

#pragma region Operators

			__compelled_inline qe_wstring __stackcall operator+(imut std::wstring& value) imut noexcept {
				return qe_wstring(get() + value);
			};

			__compelled_inline qe_wstring& __stackcall operator+=(imut std::wstring& value) noexcept {
				set(get() + value);
				return *this;
			}

			__compelled_inline qe_wstring& __stackcall operator=(imut std::wstring& value) noexcept {
				set(value);
				return *this;
			}

			__compelled_inline __stackcall operator std::wstring() imut noexcept {
				return get();
			}

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

				index_proxy(imut std::size_t index_, qe_malloc& instance) noexcept : index(index_), parent(instance) { }

#pragma endregion

#pragma region Operator overrides

				uint8_t& operator=(uint8_t value) noexcept {

					parent.set(index, value);

					return value;   // return the passed assignment value rather than using up absurd resources to decrypt, re-encrypt everything using get()
				}

				__compelled_inline __stackcall operator uint8_t() imut noexcept {

					return parent.get(index);
				}

#pragma endregion
			};

#pragma endregion

#pragma endregion

#pragma region Ctor

			__optimized_ctor qe_malloc(imut std::size_t size)
				: 
				alloc_size(size),
				local_alloc(malloc(size))
			{

				if (!local_alloc)
					throw std::bad_alloc();

				RtlZeroMemory(local_alloc, size);

				algo(local_alloc, size, false);
			}

			__compelled_inline __stackcall qe_malloc() noexcept
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

			__compelled_inline void* __stackcall get() noexcept {
				return algo_inst(local_alloc, alloc_size, false);
			}

			__compelled_inline void* __regcall get(imut std::uintptr_t pos, imut std::size_t length) noexcept {
				auto dec_alloc = reinterpret_cast<uint8_t*>(get());

				auto get_alloc = malloc(length);

				if (!get_alloc)
					return nullptr;

				memcpy(get_alloc, &dec_alloc[pos], length);

				RtlZeroMemory(dec_alloc, alloc_size);
				free(dec_alloc);

				return get_alloc;
			}

			__compelled_inline std::uint8_t __regcall get(imut std::size_t index) noexcept {
				auto dec_alloc = reinterpret_cast<uint8_t*>(get());

				auto _return = dec_alloc[index];

				RtlZeroMemory(dec_alloc, alloc_size);
				free(dec_alloc);

				return _return;
			}

			template<typename T>
			__compelled_inline T& __regcall get_t(imut std::uintptr_t pos) noexcept {

				auto value_r = reinterpret_cast<T*>(get(pos, sizeof(T)));

				auto _return = *value_r;

				free(value_r);

				return std::move(
					_return
				);
			}

			__compelled_inline void* __stackcall get_data_pointer() noexcept {
				return local_alloc;
			}

			__compelled_inline std::size_t __stackcall get_data_size() noexcept {
				return alloc_size;
			}

#pragma endregion

#pragma region Set accessors

			//WARNING: appending length to the allocation here will cause exceptions / UB
			__compelled_inline void __regcall set(
				
				void* src,
				imut std::uintptr_t pos,
				imut std::size_t length,
				bool free_src = false
			) noexcept {

				auto dec_alloc = get();

				memcpy(&reinterpret_cast<std::uint8_t*>(dec_alloc)[pos], src, length);

				auto enc_alloc = algo_inst(dec_alloc, length, false);
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

			__compelled_inline void __regcall set(

				imut std::uintptr_t pos,
				imut std::uint8_t value,
				imut std::size_t size
			) noexcept {

				auto dec_alloc = reinterpret_cast<std::uint8_t*>(get());

				for (auto i = pos; i < (pos + size); ++i) {
					dec_alloc[i] = value;
				}

				auto enc_alloc = algo_inst(dec_alloc, alloc_size, false);

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
			__compelled_inline void __regcall set(uintptr_t pos, T value) noexcept {
				auto dec_alloc = reinterpret_cast<uint8_t*>(get()); // so we can properly index the allocation

				T* cast_t = reinterpret_cast<T*>(&dec_alloc[pos]);
				*cast_t = value;

				auto enc_alloc = algo_inst(dec_alloc, alloc_size, false);
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

			__compelled_inline void __regcall swap(void* src, imut std::size_t length, imut bool free_src = false) noexcept {
				//release current resources
				zero();
				free(local_alloc);
				local_alloc = nullptr;
				alloc_size = 0x0000000000000000ULL;

				auto enc_alloc = algo_inst(src, length, false);

				alloc_size = length;
				local_alloc = enc_alloc;

				if (free_src)
					free(src);
			}

			//size is only the length in bytes of the allocation to be appended or destroyed
			__compelled_inline bool __regcall resize(imut std::size_t size) noexcept {
				auto dec_alloc = get();

				auto n_local_alloc = realloc(dec_alloc, size);

				if (!n_local_alloc) {
					free(dec_alloc);
					return false;
				}

				dec_alloc = NULL; // zero  old pointer ;; useless even if realloc didnt need to move memory
				//zero out the extended memory (if it was being extended rather than shrunk)
				if ((size) > alloc_size)
					RtlZeroMemory(&(reinterpret_cast<uint8_t*>(n_local_alloc)[alloc_size]), (size - alloc_size));

				auto enc_alloc = algo_inst(n_local_alloc, size, false);
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

				return true;
			}

			__compelled_inline void __stackcall zero() noexcept {
				set(0x0000000000000000ULL, 0x0ui8, alloc_size);
			}

#pragma endregion

#pragma region Operators

			__compelled_inline qe_malloc& __regcall operator=(imut std::vector<uint8_t>& value) noexcept {
				swap(const_cast<std::vector<uint8_t>*>(&value)->data(), value.size());

				return *this;
			}

			__compelled_inline __stackcall operator void* () imut noexcept {
				return algo_inst(local_alloc, alloc_size, false);
			}

			template<typename T>
			__compelled_inline __stackcall operator T* () imut noexcept {
				return reinterpret_cast<T*>(algo_inst(local_alloc, alloc_size, false));
			}

			index_proxy __regcall operator[](std::size_t index) noexcept {
				return index_proxy(index, *this);
			}

#pragma endregion

#pragma region Destructor

			__compelled_inline void __regcall destroy() noexcept {
				if (local_alloc)
					free(local_alloc);
				
			}

			__compelled_inline __stackcall ~qe_malloc() noexcept {
				destroy();
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
