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
#include <cstdlib>

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

namespace qengine{

	namespace qtype_enc {

#pragma region Singleton

		extern bool is_init;

#pragma endregion

#pragma region Types

#pragma region Template / User Defined

		template<typename T>
		class qe_struct {

		private:

#pragma region Encrypted value

			mut noregister T _value;

#pragma endregion

		public:

#pragma region Ctor / Dtor

			__optimized_ctor qe_struct( imut T value = T{} ) nex {

				set(value);
			}

			__optimized_dtor ~qe_struct() nex {

				polyc::unregister_polyc_pointer(volatile_cast<T*>(&_value));

				RtlZeroMemory(volatile_cast<T*>(&this->_value), sizeof(T));
			}

#pragma endregion

#pragma region Accessors

			__compelled_inline imut T __stackcall get() imut nex {

				polyc::algo(volatile_cast<T*>(&_value), sizeof(_value));

				T value = *volatile_cast<T*>(&_value);

				polyc::algo(volatile_cast<T*>(&_value), sizeof(_value));

				return value;
			}

			template<typename _T>
			__compelled_inline decltype(auto) __regcall get( _T T::* member ) imut nex {

				T decrypted = get();

				return decrypted.*member;
			}

			__compelled_inline imut bool __regcall set(imut T value) nex {

				*volatile_cast<T*>(&_value) =  value;

				return polyc::algo(volatile_cast<T*>(&_value), sizeof(_value));
			}

			template<typename _T>
			__compelled_inline imut bool __regcall set( _T T::* member, _T value ) nex {

				polyc::algo(volatile_cast<T*>(&_value), sizeof(_value));

				(volatile_cast<T*>(&_value)->*member) = std::move(value);

				return polyc::algo(volatile_cast<T*>(&_value), sizeof(_value));
			}

#pragma endregion

#pragma region Operators

			__compelled_inline qe_struct<T>& __regcall operator=(imut T value) nex {
				set(value);
				return *this;
			}

			__compelled_inline __stackcall operator T() imut nex {
				return get();
			}

#pragma endregion

		};

#pragma endregion

#pragma region Other Primitive Types
		
		class qe_bool {

		private:

#pragma region Encrypted value

			mut noregister bool _value;

#pragma endregion

		public:

#pragma region Ctor / Dtor

			__optimized_ctor qe_bool(imut bool value = false) nex {

				set( value );
			}

			__optimized_dtor ~qe_bool() nex {
				
				polyc::unregister_polyc_pointer(volatile_cast<bool*>(&_value));

				RtlZeroMemory(volatile_cast<bool*>(&this->_value), sizeof(_value));
			}

#pragma endregion

#pragma region Accessors

			__compelled_inline imut std::int8_t __stackcall get() imut nex {

				polyc::algo(volatile_cast<bool*>(&_value) , sizeof(_value));

				auto value = _value;

				polyc::algo(volatile_cast<bool*>(&_value), sizeof(_value));

				return value;
			}

			__compelled_inline imut bool __regcall set(imut bool value) nex {

				// The current method COULD lead to an .data allocation rather than stack, which has it's own security vulnerabilities.
				// Revisit this later and try to perform all decryption routines directly to a local stack-allocated instance so any .data member are never plaintext

				_value = value;

				return polyc::algo(volatile_cast<bool*>(&_value), sizeof(_value));
			}

#pragma endregion

#pragma region Operators

			__compelled_inline qe_bool& __regcall operator=(imut bool value) nex {

				set(value);
				return *this;
			}

			__compelled_inline __stackcall operator bool() imut nex {

				return get();
			}

#pragma endregion
		};

#pragma endregion

#pragma region WORD

#pragma region 8-bit

		class qe_int8 {

		private:

#pragma region Encrypted value

			mut noregister std::int8_t _value;

#pragma endregion

		public:

#pragma region Ctor / Dtor

			__optimized_ctor qe_int8(imut std::int8_t value = 0) nex {

				set( value );
			}

			__optimized_dtor ~qe_int8() nex {
				
				polyc::unregister_polyc_pointer(volatile_cast<std::int8_t*>(&_value));

				RtlZeroMemory(volatile_cast<std::int8_t*>(&this->_value), sizeof(_value));
			}

#pragma endregion

#pragma region Accessors

			__compelled_inline imut std::int8_t __stackcall get() imut nex {

				polyc::algo(volatile_cast<std::int8_t*>(&_value) , sizeof(_value));

				auto value = _value;

				polyc::algo(volatile_cast<std::int8_t*>(&_value), sizeof(_value));

				return value;
			}

			__compelled_inline imut bool __regcall set(imut std::int8_t value) nex {

				// The current method COULD lead to an .data allocation rather than stack, which has it's own security vulnerabilities.
				// Revisit this later and try to perform all decryption routines directly to a local stack-allocated instance so any .data member are never plaintext

				_value = value;

				return polyc::algo(volatile_cast<std::int8_t*>(&_value), sizeof(_value));
			}

#pragma endregion

#pragma region Operators

			__compelled_inline qe_int8 __regcall operator+(imut std::int8_t value) imut nex {
				return qe_int8(get() + value);
			};

			__compelled_inline qe_int8 __regcall operator-(imut std::int8_t value) imut nex {
				return qe_int8(get() - value);
			}

			__compelled_inline qe_int8 __regcall operator/(imut std::int8_t value) imut nex {
				return qe_int8(get() / value);
			}

			__compelled_inline qe_int8 __regcall operator*(imut std::int8_t value) imut nex {
				return qe_int8(get() * value);
			}

			__compelled_inline qe_int8 __regcall operator&(imut std::int8_t value) imut nex {
				return qe_int8(get() & value);
			}

			__compelled_inline qe_int8 __regcall operator|(imut std::int8_t value) imut nex {
				return qe_int8(get() | value);
			}

			__compelled_inline qe_int8 __regcall operator%(imut std::int8_t value) imut nex {
				return qe_int8(get() % value);
			}

			__compelled_inline qe_int8 __regcall operator^(imut std::int8_t value) imut nex {
				return qe_int8(get() ^ value);
			}

			__compelled_inline qe_int8 __regcall operator<<(imut std::int8_t value) imut nex {
				return qe_int8(get() << value);
			}

			__compelled_inline qe_int8 __regcall operator>>(imut std::int8_t value) imut nex {
				return qe_int8(get() >> value);
			}

			__compelled_inline qe_int8& __regcall operator+=(imut std::int8_t value) {
				set(get() + value);
				return *this;
			}

			__compelled_inline qe_int8& __regcall operator-=(imut std::int8_t value) nex {
				set(get() - value);
				return *this;
			}

			__singleton qe_int8& __regcall operator*=(imut std::int8_t value) nex {

				set(get() * value);
				return *this;
			}

			__compelled_inline qe_int8& __regcall operator/=(imut std::int8_t value) nex {
				set(get() / value);
				return *this;
			}

			__compelled_inline qe_int8& __regcall operator%=(imut std::int8_t value) nex {
				set(get() % value);
				return *this;
			}

			__compelled_inline qe_int8& __regcall operator^=(imut std::int8_t value) nex {
				set(get() ^ value);
				return *this;
			}

			__compelled_inline qe_int8& __regcall operator&=(imut std::int8_t value) nex {
				set(get() & value);
				return *this;
			}

			__compelled_inline qe_int8& __regcall operator|=(imut std::int8_t value) nex {
				set(get() | value);
				return *this;
			}

			__compelled_inline qe_int8& __regcall operator<<=(imut std::int8_t value) nex {
				set(get() << value);
				return *this;
			}

			__compelled_inline qe_int8& __regcall operator>>=(imut std::int8_t value) nex {
				set(get() >> value);
				return *this;
			}

			__compelled_inline qe_int8& __regcall operator=(imut std::int8_t value) nex {
				set(value);
				return *this;
			}

			__compelled_inline __stackcall operator std::int8_t() imut nex {
				return get();
			}

#pragma endregion
		};

		class qe_uint8 {

		private:

#pragma region Encrypted value

			mut noregister std::uint8_t _value;

#pragma endregion

		public:

#pragma region Ctor / Dtor

			__optimized_ctor qe_uint8(imut std::uint8_t value = 0) nex {
				set(value);
			}

			__optimized_dtor ~qe_uint8() nex {

				polyc::unregister_polyc_pointer(volatile_cast<std::uint8_t*>(&_value));

				RtlZeroMemory(volatile_cast<std::uint8_t*>(&this->_value), sizeof(_value));
			}

#pragma endregion

#pragma region Accessors

			__compelled_inline imut std::uint8_t __stackcall get() imut nex {

				polyc::algo(volatile_cast<std::uint8_t*>(&_value), sizeof(_value));

				auto value = _value;

				polyc::algo(volatile_cast<std::uint8_t*>(&_value), sizeof(_value));

				return value;
			}

			__compelled_inline imut bool __regcall set(imut std::uint8_t value) nex {

				_value = value;

				return polyc::algo(volatile_cast<std::uint8_t*>(&_value), sizeof(_value));
			}

#pragma endregion

#pragma region Operators

			__compelled_inline qe_uint8 __regcall operator+(imut std::uint8_t value) imut nex {
				return qe_uint8(get() + value);
			};

			__compelled_inline qe_uint8 __regcall operator-(imut std::uint8_t value) imut nex {
				return qe_uint8(get() - value);
			}

			__compelled_inline qe_uint8 __regcall operator/(imut std::uint8_t value) imut nex {
				return qe_uint8(get() / value);
			}

			__compelled_inline qe_uint8 __regcall operator*(imut std::uint8_t value) imut nex {
				return qe_uint8(get() * value);
			}

			__compelled_inline qe_uint8 __regcall operator&(imut std::uint8_t value) imut nex {
				return qe_uint8(get() & value);
			}

			__compelled_inline qe_uint8 __regcall operator|(imut std::uint8_t value) imut nex {
				return qe_uint8(get() | value);
			}

			__compelled_inline qe_uint8 __regcall operator%(imut std::uint8_t value) imut nex {
				return qe_uint8(get() % value);
			}

			__compelled_inline qe_uint8 __regcall operator^(imut std::uint8_t value) imut nex {
				return qe_uint8(get() ^ value);
			}

			__compelled_inline qe_uint8 __regcall operator<<(imut std::uint8_t value) imut nex {
				return qe_uint8(get() << value);
			}

			__compelled_inline qe_uint8 __regcall operator>>(imut std::uint8_t value) imut nex {
				return qe_uint8(get() >> value);
			}

			__compelled_inline qe_uint8& __regcall operator+=(imut std::uint8_t value) nex {
				set(get() + value);
				return *this;
			}

			__compelled_inline qe_uint8& __regcall operator-=(imut std::uint8_t value) nex {
				set(get() - value);
				return *this;
			}

			__compelled_inline qe_uint8& __regcall operator*=(imut std::uint8_t value) nex {
				set(get() * value);
				return *this;
			}

			__compelled_inline qe_uint8& __regcall operator/=(imut std::uint8_t value) nex {
				set(get() / value);
				return *this;
			}

			__compelled_inline qe_uint8& __regcall operator%=(imut std::uint8_t value) nex {
				set(get() % value);
				return *this;
			}

			__compelled_inline qe_uint8& __regcall operator^=(imut std::uint8_t value) nex {
				set(get() ^ value);
				return *this;
			}

			__compelled_inline qe_uint8& __regcall operator&=(imut std::uint8_t value) nex {
				set(get() & value);
				return *this;
			}

			__compelled_inline qe_uint8& __regcall operator|=(imut std::uint8_t value) nex {
				set(get() | value);
				return *this;
			}

			__compelled_inline qe_uint8& __regcall operator<<=(imut std::uint8_t value) nex {
				set(get() << value);
				return *this;
			}

			__compelled_inline qe_uint8& __regcall operator>>=(imut std::uint8_t value) nex {
				set(get() >> value);
				return *this;
			}

			__compelled_inline qe_uint8& __regcall operator=(imut std::uint8_t value) nex {
				set(value);
				return *this;
			}

			__compelled_inline __stackcall operator std::uint8_t() imut nex {
				return get();
			}

#pragma endregion
		};

#pragma endregion

#pragma region 16-bit

		class qe_int16 {

		private:

#pragma region Encrypted value

			mut noregister std::int16_t _value;

#pragma endregion

		public:

#pragma region Ctor / Dtor

			__optimized_ctor qe_int16(imut std::int16_t value = 0) nex {
				set(value);
			}

			__optimized_dtor ~qe_int16() nex {

				polyc::unregister_polyc_pointer(volatile_cast<std::int16_t*>(&_value));

				RtlZeroMemory(volatile_cast<std::int16_t*>(&this->_value), sizeof(_value));
			}

#pragma endregion

#pragma region Accessors

			__compelled_inline imut std::int16_t __stackcall get() imut nex {

				polyc::algo(volatile_cast<std::int16_t*>(volatile_cast<std::int16_t*>(&_value) ), sizeof(_value));	//	Return value unused, exceptions thrown here are due to improper compiler settings or end user environment

				auto value = _value;

				polyc::algo(volatile_cast<std::int16_t*>(&_value), sizeof(_value));

				return value;
			}

			__compelled_inline imut bool __regcall set(imut std::int16_t value) nex {

				_value = value;

				return polyc::algo(volatile_cast<std::int16_t*>(&_value), sizeof(_value));
			}

#pragma endregion

#pragma region Operators

			__compelled_inline qe_int16 __regcall operator+(imut std::int16_t value) imut nex {
				return qe_int16(get() + value);
			};

			__compelled_inline qe_int16 __regcall operator-(imut std::int16_t value) imut nex {
				return qe_int16(get() - value);
			}

			__compelled_inline qe_int16 __regcall operator/(imut std::int16_t value) imut nex {
				return qe_int16(get() / value);
			}

			__compelled_inline qe_int16 __regcall operator*(imut std::int16_t value) imut nex {
				return qe_int16(get() * value);
			}

			__compelled_inline qe_int16 __regcall operator&(imut std::int16_t value) imut nex {
				return qe_int16(get() & value);
			}

			__compelled_inline qe_int16 __regcall operator|(imut std::int16_t value) imut nex {
				return qe_int16(get() | value);
			}

			__compelled_inline qe_int16 __regcall operator%(imut std::int16_t value) imut nex {
				return qe_int16(get() % value);
			}

			__compelled_inline qe_int16 __regcall operator^(imut std::int16_t value) imut nex {
				return qe_int16(get() ^ value);
			}

			__compelled_inline qe_int16 __regcall operator<<(imut std::int16_t value) imut nex {
				return qe_int16(get() << value);
			}

			__compelled_inline qe_int16 __regcall operator>>(imut std::int16_t value) imut nex {
				return qe_int16(get() >> value);
			}

			__compelled_inline qe_int16& __regcall operator+=(imut std::int16_t value) nex {
				set(get() + value);
				return *this;
			}

			__compelled_inline qe_int16& __regcall operator-=(imut std::int16_t value) nex {
				set(get() - value);
				return *this;
			}

			__compelled_inline qe_int16& __regcall operator*=(imut std::int16_t value) nex {
				set(get() * value);
				return *this;
			}

			__compelled_inline qe_int16& __regcall operator/=(imut std::int16_t value) nex {
				set(get() / value);
				return *this;
			}

			__compelled_inline qe_int16& __regcall operator%=(imut std::int16_t value) nex {
				set(get() % value);
				return *this;
			}

			__compelled_inline qe_int16& __regcall operator^=(imut std::int16_t value) nex {
				set(get() ^ value);
				return *this;
			}

			__compelled_inline qe_int16& __regcall operator&=(imut std::int16_t value) nex {
				set(get() & value);
				return *this;
			}

			__compelled_inline qe_int16& __regcall operator|=(imut std::int16_t value) nex {
				set(get() | value);
				return *this;
			}

			__compelled_inline qe_int16& __regcall operator<<=(imut std::int16_t value) nex {
				set(get() << value);
				return *this;
			}

			__compelled_inline qe_int16& __regcall operator>>=(imut std::int16_t value) nex {
				set(get() >> value);
				return *this;
			}

			__compelled_inline qe_int16& __regcall operator=(imut std::int16_t value) nex {
				set(value);
				return *this;
			}

			__compelled_inline __stackcall operator std::int16_t() imut nex {
				return get();
			}

#pragma endregion
		};

		class qe_uint16 {

		private:

#pragma region Encrypted value

			mut noregister std::uint16_t _value;

#pragma endregion

		public:

#pragma region Ctor / Dtor

			__optimized_ctor qe_uint16(imut std::uint16_t value = 0) nex {
				set(value);
			}

			__optimized_dtor qe_uint16() nex {

				polyc::unregister_polyc_pointer(volatile_cast<std::uint16_t*>(&_value));

				RtlZeroMemory(volatile_cast<std::uint16_t*>(&this->_value), sizeof(_value));
			}

#pragma endregion

#pragma region Accessors

			__compelled_inline imut std::uint16_t __stackcall get() imut nex {

				polyc::algo(volatile_cast<std::uint16_t*>(&_value), sizeof(_value));

				auto value = _value;

				polyc::algo(volatile_cast<std::uint16_t*>(&_value), sizeof(_value));

				return value;
			}

			__compelled_inline imut bool __regcall set(imut std::uint16_t value) nex {

				_value = value;

				return polyc::algo(volatile_cast<std::uint16_t*>(&_value), sizeof(_value));
			}

#pragma endregion

#pragma region Operators

			__compelled_inline qe_uint16 __regcall operator+(imut std::uint16_t value) imut nex {
				return qe_uint16(get() + value);
			};

			__compelled_inline qe_uint16 __regcall operator-(imut std::uint16_t value) imut nex {
				return qe_uint16(get() - value);
			}

			__compelled_inline qe_uint16 __regcall operator/(imut std::uint16_t value) imut nex {
				return qe_uint16(get() / value);
			}

			__compelled_inline qe_uint16 __regcall operator*(imut std::uint16_t value) imut nex {
				return qe_uint16(get() * value);
			}

			__compelled_inline qe_uint16 __regcall operator&(imut std::uint16_t value) imut nex {
				return qe_uint16(get() & value);
			}

			__compelled_inline qe_uint16 __regcall operator|(imut std::uint16_t value) imut nex {
				return qe_uint16(get() | value);
			}

			__compelled_inline qe_uint16 __regcall operator%(imut std::uint16_t value) imut nex {
				return qe_uint16(get() % value);
			}

			__compelled_inline qe_uint16 __regcall operator^(imut std::uint16_t value) imut nex {
				return qe_uint16(get() ^ value);
			}

			__compelled_inline qe_uint16 __regcall operator<<(imut std::uint16_t value) imut nex {
				return qe_uint16(get() << value);
			}

			__compelled_inline qe_uint16 __regcall operator>>(imut std::uint16_t value) imut nex {
				return qe_uint16(get() >> value);
			}

			__compelled_inline qe_uint16& __regcall operator+=(imut std::uint16_t value) nex {
				set(get() + value);
				return *this;
			}

			__compelled_inline qe_uint16& __regcall operator-=(imut std::uint16_t value) nex {
				set(get() - value);
				return *this;
			}

			__compelled_inline qe_uint16& __regcall operator*=(imut std::uint16_t value) nex {
				set(get() * value);
				return *this;
			}

			__compelled_inline qe_uint16& __regcall operator/=(imut std::uint16_t value) nex {
				set(get() / value);
				return *this;
			}

			__compelled_inline qe_uint16& __regcall operator%=(imut std::uint16_t value) nex {
				set(get() % value);
				return *this;
			}

			__compelled_inline qe_uint16& __regcall operator^=(imut std::uint16_t value) nex {
				set(get() ^ value);
				return *this;
			}

			__compelled_inline qe_uint16& __regcall operator&=(imut std::uint16_t value) nex {
				set(get() & value);
				return *this;
			}

			__compelled_inline qe_uint16& __regcall operator|=(imut std::uint16_t value) nex {
				set(get() | value);
				return *this;
			}

			__compelled_inline qe_uint16& __regcall operator<<=(imut std::uint16_t value) nex {
				set(get() << value);
				return *this;
			}

			__compelled_inline qe_uint16& __regcall operator>>=(imut std::uint16_t value) nex {
				set(get() >> value);
				return *this;
			}

			__compelled_inline qe_uint16& __regcall operator=(imut std::uint16_t value) nex {
				set(value);
				return *this;
			}

			__compelled_inline __stackcall operator std::uint16_t() imut nex {
				return get();
			}

#pragma endregion
		};

#pragma endregion

#pragma region 32-bit

		class qe_int32 {

		private:

#pragma region Encrypted value

			mut noregister std::int32_t _value;

#pragma endregion

		public:

#pragma region Ctor / Dtor

			__optimized_ctor qe_int32(imut int value = 0) nex {
				set(value);
			}

			__optimized_dtor ~qe_int32() nex {

				polyc::unregister_polyc_pointer(volatile_cast<std::int32_t*>(&_value));

				RtlZeroMemory(volatile_cast<std::int32_t*>(&this->_value), sizeof(_value));
			}

#pragma endregion

#pragma region Accessors

			__compelled_inline imut std::int32_t __stackcall get() imut nex {

				polyc::algo(volatile_cast<std::int32_t*>(&_value), sizeof(_value));

				auto value = _value;

				polyc::algo(volatile_cast<std::int32_t*>(&_value), sizeof(_value));

				return value;
			}

			__compelled_inline imut bool __regcall set(imut std::int32_t value) nex {

				_value = value;

				return polyc::algo(volatile_cast<std::int32_t*>(&_value), sizeof(_value));
			}

#pragma endregion

#pragma region Operators

			__compelled_inline qe_int32 __regcall operator+(imut int value) imut nex {
				return qe_int32(get() + value);
			};

			__compelled_inline qe_int32 __regcall operator-(imut int value) imut nex {
				return qe_int32(get() - value);
			}

			__compelled_inline qe_int32 __regcall operator/(imut int value) imut nex {
				return qe_int32(get() / value);
			}

			__compelled_inline qe_int32 __regcall operator*(imut int value) imut nex {
				return qe_int32(get() * value);
			}

			__compelled_inline qe_int32 __regcall operator&(imut int value) imut nex {
				return qe_int32(get() & value);
			}

			__compelled_inline qe_int32 __regcall operator|(imut int value) imut nex {
				return qe_int32(get() | value);
			}

			__compelled_inline qe_int32 __regcall operator%(imut int value) imut nex {
				return qe_int32(get() % value);
			}

			__compelled_inline qe_int32 __regcall operator^(imut int value) imut nex {
				return qe_int32(get() ^ value);
			}

			__compelled_inline qe_int32 __regcall operator<<(imut int value) imut nex {
				return qe_int32(get() << value);
			}

			__compelled_inline qe_int32 __regcall operator>>(imut int value) imut nex {
				return qe_int32(get() >> value);
			}

			__compelled_inline qe_int32& __regcall operator+=(imut int value) nex {
				set(get() + value);
				return *this;
			}

			__compelled_inline qe_int32& __regcall operator-=(imut int value) nex {
				set(get() - value);
				return *this;
			}

			__compelled_inline qe_int32& __regcall operator*=(imut int value) nex {
				set(get() * value);
				return *this;
			}

			__compelled_inline qe_int32& __regcall operator/=(imut int value) nex {
				set(get() / value);
				return *this;
			}

			__compelled_inline qe_int32& __regcall operator%=(imut int value) nex {
				set(get() % value);
				return *this;
			}

			__compelled_inline qe_int32& __regcall operator^=(imut int value) nex {
				set(get() ^ value);
				return *this;
			}

			__compelled_inline qe_int32& __regcall operator&=(imut int value) nex {
				set(get() & value);
				return *this;
			}

			__compelled_inline qe_int32& __regcall operator|=(imut int value) nex {
				set(get() | value);
				return *this;
			}

			__compelled_inline qe_int32& __regcall operator<<=(imut int value) nex {
				set(get() << value);
				return *this;
			}

			__compelled_inline qe_int32& __regcall operator>>=(imut int value) nex {
				set(get() >> value);
				return *this;
			}

			__compelled_inline qe_int32& __regcall operator=(imut int value) nex {
				set(value);
				return *this;
			}

			__compelled_inline __stackcall operator int() imut nex {
				return get();
			}

#pragma endregion
		};

		class qe_uint32 {

		private:

#pragma region Encrypted value

			mut noregister std::uint32_t _value;

#pragma endregion

		public:

#pragma region Ctor / Dtor

			__optimized_ctor qe_uint32(imut std::uint32_t value = 0) nex {
				set(value);
			}

			__optimized_dtor ~qe_uint32() nex {

				polyc::unregister_polyc_pointer(volatile_cast<std::uint32_t*>(&_value));

				RtlZeroMemory(volatile_cast<std::uint32_t*>(&this->_value), sizeof(_value));
			}

#pragma endregion

#pragma region Accessors

			__compelled_inline imut std::uint32_t __stackcall get() imut nex {

				polyc::algo(volatile_cast<std::uint32_t*>(&_value), sizeof(_value));

				auto value = _value;

				polyc::algo(volatile_cast<std::uint32_t*>(&_value), sizeof(_value));

				return value;
			}

			__compelled_inline imut bool __regcall set(imut std::uint32_t value) nex {

				_value = value;

				return polyc::algo(volatile_cast<std::uint32_t*>(&_value), sizeof(_value));
			}

#pragma endregion

#pragma region Operators

			__compelled_inline qe_uint32 __regcall operator+(imut std::uint32_t value) imut nex {
				return qe_uint32(get() + value);
			};

			__compelled_inline qe_uint32 __regcall operator-(imut std::uint32_t value) imut nex {
				return qe_uint32(get() - value);
			}

			__compelled_inline qe_uint32 __regcall operator/(imut std::uint32_t value) imut nex {
				return qe_uint32(get() / value);
			}

			__compelled_inline qe_uint32 __regcall operator*(imut std::uint32_t value) imut nex {
				return qe_uint32(get() * value);
			}

			__compelled_inline qe_uint32 __regcall operator&(imut std::uint32_t value) imut nex {
				return qe_uint32(get() & value);
			}

			__compelled_inline qe_uint32 __regcall operator|(imut std::uint32_t value) imut nex {
				return qe_uint32(get() | value);
			}

			__compelled_inline qe_uint32 __regcall operator%(imut std::uint32_t value) imut nex {
				return qe_uint32(get() % value);
			}

			__compelled_inline qe_uint32 __regcall operator^(imut std::uint32_t value) imut nex {
				return qe_uint32(get() ^ value);
			}

			__compelled_inline qe_uint32 __regcall operator<<(imut std::uint32_t value) imut nex {
				return qe_uint32(get() << value);
			}

			__compelled_inline qe_uint32 __regcall operator>>(imut std::uint32_t value) imut nex {
				return qe_uint32(get() >> value);
			}

			__compelled_inline qe_uint32& __regcall operator+=(imut std::uint32_t value) nex {
				set(get() + value);
				return *this;
			}

			__compelled_inline qe_uint32& __regcall operator-=(imut std::uint32_t value) nex {
				set(get() - value);
				return *this;
			}

			__compelled_inline qe_uint32& __regcall operator*=(imut std::uint32_t value) nex {
				set(get() * value);
				return *this;
			}

			__compelled_inline qe_uint32& __regcall operator/=(imut std::uint32_t value) nex {
				set(get() / value);
				return *this;
			}

			__compelled_inline qe_uint32& __regcall operator%=(imut std::uint32_t value) nex {
				set(get() % value);
				return *this;
			}

			__compelled_inline qe_uint32& __regcall operator^=(imut std::uint32_t value) nex {
				set(get() ^ value);
				return *this;
			}

			__compelled_inline qe_uint32& __regcall operator&=(imut std::uint32_t value) nex {
				set(get() & value);
				return *this;
			}

			__compelled_inline qe_uint32& __regcall operator|=(imut std::uint32_t value) nex {
				set(get() | value);
				return *this;
			}

			__compelled_inline qe_uint32& __regcall operator<<=(imut std::uint32_t value) nex {
				set(get() << value);
				return *this;
			}

			__compelled_inline qe_uint32& __regcall operator>>=(imut std::uint32_t value) nex {
				set(get() >> value);
				return *this;
			}

			__compelled_inline qe_uint32& __regcall operator=(imut std::uint32_t value) nex {
				set(value);
				return *this;
			}

			__compelled_inline __stackcall operator std::uint32_t() imut nex {
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

			mut noregister std::int64_t _value;

#pragma endregion

		public:

#pragma region Ctor / Dtor

			__optimized_ctor qe_int64(imut std::int64_t value = 0) nex {
				set(value);
			}

			__optimized_dtor ~qe_int64() nex {

				polyc::unregister_polyc_pointer(volatile_cast<std::int64_t*>(&_value));

				RtlZeroMemory(volatile_cast<std::int64_t*>(&this->_value), sizeof(_value));
			}

#pragma endregion

#pragma region Accessors

			__compelled_inline imut std::int64_t __stackcall get() imut nex {

				polyc::algo(volatile_cast<std::int64_t*>(&_value), sizeof(_value));

				auto value = _value;

				polyc::algo(volatile_cast<std::int64_t*>(&_value), sizeof(_value));

				return value;
			}

			__compelled_inline imut bool __regcall set(imut std::int64_t value) nex {

				_value = value;

				return polyc::algo(volatile_cast<std::int64_t*>(&_value), sizeof(_value));
			}
#pragma endregion

#pragma region Operators

			__compelled_inline qe_int64 __regcall operator+(imut std::int64_t value) imut nex {
				return qe_int64(get() + value);
			};

			__compelled_inline qe_int64 __regcall operator-(imut std::int64_t value) imut nex {
				return qe_int64(get() - value);
			}

			__compelled_inline qe_int64 __regcall operator/(imut std::int64_t value) imut nex {
				return qe_int64(get() / value);
			}

			__compelled_inline qe_int64 __regcall operator*(imut std::int64_t value) imut nex {
				return qe_int64(get() * value);
			}

			__compelled_inline qe_int64 __regcall operator&(imut std::int64_t value) imut nex {
				return qe_int64(get() & value);
			}

			__compelled_inline qe_int64 __regcall operator|(imut std::int64_t value) imut nex {
				return qe_int64(get() | value);
			}

			__compelled_inline qe_int64 __regcall operator%(imut std::int64_t value) imut nex {
				return qe_int64(get() % value);
			}

			__compelled_inline qe_int64 __regcall operator^(imut std::int64_t value) imut nex {
				return qe_int64(get() ^ value);
			}

			__compelled_inline qe_int64 __regcall operator<<(imut std::int64_t value) imut nex {
				return qe_int64(get() << value);
			}

			__compelled_inline qe_int64 __regcall operator>>(imut std::int64_t value) imut nex {
				return qe_int64(get() >> value);
			}

			__compelled_inline qe_int64& __regcall operator+=(imut std::int64_t value) nex {
				set(get() + value);
				return *this;
			}

			__compelled_inline qe_int64& __regcall operator-=(imut std::int64_t value) nex {
				set(get() - value);
				return *this;
			}

			__compelled_inline qe_int64& __regcall operator*=(imut std::int64_t value) nex {
				set(get() * value);
				return *this;
			}

			__compelled_inline qe_int64& __regcall operator/=(imut std::int64_t value) nex {
				set(get() / value);
				return *this;
			}

			__compelled_inline qe_int64& __regcall operator%=(imut std::int64_t value) nex {
				set(get() % value);
				return *this;
			}

			__compelled_inline qe_int64& __regcall operator^=(imut std::int64_t value) nex {
				set(get() ^ value);
				return *this;
			}

			__compelled_inline qe_int64& __regcall operator&=(imut std::int64_t value) nex {
				set(get() & value);
				return *this;
			}

			__compelled_inline qe_int64& __regcall operator|=(imut std::int64_t value) nex {
				set(get() | value);
				return *this;
			}

			__compelled_inline qe_int64& __regcall operator<<=(imut std::int64_t value) nex {
				set(get() << value);
				return *this;
			}

			__compelled_inline qe_int64& __regcall operator>>=(imut std::int64_t value) nex {
				set(get() >> value);
				return *this;
			}

			__compelled_inline qe_int64& __regcall operator=(imut std::int64_t value) nex {
				set(value);
				return *this;
			}

			__compelled_inline __stackcall operator std::int64_t() imut nex {
				return get();
			}

#pragma endregion
		};

		class qe_uint64 {

		private:

#pragma region Encrypted value

			mut noregister std::uint64_t _value;

#pragma endregion

		public:

#pragma region Ctor / Dtor

			__optimized_ctor qe_uint64(imut std::uint64_t value = 0) {
				set(value);
			}

			__optimized_dtor ~qe_uint64() nex {

				polyc::unregister_polyc_pointer(volatile_cast<std::uint64_t*>(&_value));

				RtlZeroMemory(volatile_cast<std::uint64_t*>(&this->_value), sizeof(_value));
			}

#pragma endregion

#pragma region Accessors

			__compelled_inline imut std::uint64_t __stackcall get() imut nex {

				polyc::algo(volatile_cast<std::uint64_t*>(&_value), sizeof(_value));

				auto value = _value;

				polyc::algo(volatile_cast<std::uint64_t*>(&_value), sizeof(_value));

				return value;
			}

			__compelled_inline imut bool __regcall set(imut std::uint64_t value) nex {

				_value = value;

				return polyc::algo(volatile_cast<std::uint64_t*>(&_value), sizeof(_value));
			}

#pragma endregion

#pragma region Operators

			__compelled_inline qe_uint64 __regcall operator+(imut std::uint64_t value) imut nex {
				return qe_uint64(get() + value);
			};

			__compelled_inline qe_uint64 __regcall operator-(imut std::uint64_t value) imut nex {
				return qe_uint64(get() - value);
			}

			__compelled_inline qe_uint64 __regcall operator/(imut std::uint64_t value) imut nex {
				return qe_uint64(get() / value);
			}

			__compelled_inline qe_uint64 __regcall operator*(imut std::uint64_t value) imut nex {
				return qe_uint64(get() * value);
			}

			__compelled_inline qe_uint64 __regcall operator&(imut std::uint64_t value) imut nex {
				return qe_uint64(get() & value);
			}

			__compelled_inline qe_uint64 __regcall operator|(imut std::uint64_t value) imut nex {
				return qe_uint64(get() | value);
			}

			__compelled_inline qe_uint64 __regcall operator%(imut std::uint64_t value) imut nex {
				return qe_uint64(get() % value);
			}

			__compelled_inline qe_uint64 __regcall operator^(imut std::uint64_t value) imut nex {
				return qe_uint64(get() ^ value);
			}

			__compelled_inline qe_uint64 __regcall operator<<(imut std::uint64_t value) imut nex {
				return qe_uint64(get() << value);
			}

			__compelled_inline qe_uint64 __regcall operator>>(imut std::uint64_t value) imut nex {
				return qe_uint64(get() >> value);
			}

			__compelled_inline qe_uint64& __regcall operator+=(imut std::uint64_t value) nex {
				set(get() + value);
				return *this;
			}

			__compelled_inline qe_uint64& __regcall operator-=(imut std::uint64_t value) nex {
				set(get() - value);
				return *this;
			}

			__compelled_inline qe_uint64& __regcall operator*=(imut std::uint64_t value) nex {
				set(get() * value);
				return *this;
			}

			__compelled_inline qe_uint64& __regcall operator/=(imut std::uint64_t value) nex {
				set(get() / value);
				return *this;
			}

			__compelled_inline qe_uint64& __regcall operator%=(imut std::uint64_t value) nex {
				set(get() % value);
				return *this;
			}

			__compelled_inline qe_uint64& __regcall operator^=(imut std::uint64_t value) nex {
				set(get() ^ value);
				return *this;
			}

			__compelled_inline qe_uint64& __regcall operator&=(imut std::uint64_t value) nex {
				set(get() & value);
				return *this;
			}

			__compelled_inline qe_uint64& __regcall operator|=(imut std::uint64_t value) nex {
				set(get() | value);
				return *this;
			}

			__compelled_inline qe_uint64& __regcall operator<<=(imut std::uint64_t value) nex {
				set(get() << value);
				return *this;
			}

			__compelled_inline qe_uint64& __regcall operator>>=(imut std::uint64_t value) nex {
				set(get() >> value);
				return *this;
			}

			__compelled_inline qe_uint64& __regcall operator=(imut std::uint64_t value) nex {
				set(value);
				return *this;
			}

			__compelled_inline __stackcall operator std::uint64_t() imut nex {
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

			noregister float _value;

		public:

#pragma region Ctor / Dtor

			__compelled_inline __fpcall qe_float(imut float value) nex {
				set(value);
			}

			__optimized_dtor ~qe_float() nex {

				polyc::unregister_polyc_pointer(volatile_cast<float*>(&_value));

				RtlZeroMemory(volatile_cast<float*>(&this->_value), sizeof(_value));
			}

#pragma endregion

#pragma region Accessors

			__compelled_inline imut float __stackcall get() imut nex {

				polyc::algo(volatile_cast<float*>(&_value), sizeof(_value));

				auto value = _value;

				polyc::algo(volatile_cast<float*>(&_value), sizeof(_value));

				return value;
			}

			__compelled_inline imut bool __fpcall set(imut float value) nex {

				_value = value;

				return polyc::algo(volatile_cast<float*>(&_value), sizeof(_value));
			}

#pragma endregion

#pragma region Operators

			__compelled_inline qe_float __fpcall operator+(imut float value) imut nex {
				return qe_float(get() + value);
			};

			__compelled_inline qe_float __fpcall operator-(imut float value) imut nex {
				return qe_float(get() - value);
			}

			__compelled_inline qe_float __fpcall operator/(imut float value) imut nex {
				return qe_float(get() / value);
			}

			__compelled_inline qe_float __fpcall operator*(imut float value) imut nex {
				return qe_float(get() * value);
			}

			__compelled_inline qe_float& __fpcall operator+=(imut float value) nex {
				set(get() + value);
				return *this;
			}

			__compelled_inline qe_float& __fpcall operator-=(imut float value) nex {
				set(get() - value);
				return *this;
			}

			__compelled_inline qe_float& __fpcall operator*=(imut float value) nex {
				set(get() * value);
				return *this;
			}

			__compelled_inline qe_float& __fpcall operator/=(imut float value) nex {
				set(get() / value);
				return *this;
			}

			__compelled_inline qe_float& __fpcall operator=(imut float value) nex {
				set(value);
				return *this;
			}

			__compelled_inline __stackcall operator float() imut nex {
				return get();
			}

#pragma endregion
		};

#pragma endregion

#pragma region 64-bit

#ifdef _WIN64

		class qe_double {

		private:

			noregister double _value;

		public:

#pragma region Ctor / Dtor

			__compelled_inline __fpcall qe_double(imut double value = static_cast<double>(0.0f)) {
				set(value);
			}

			__optimized_dtor ~qe_double() nex {

				polyc::unregister_polyc_pointer(volatile_cast<double*>(&_value));

				RtlZeroMemory(volatile_cast<double*>(&this->_value), sizeof(_value));
			}

#pragma endregion

#pragma region Accessors

			__compelled_inline imut double __stackcall get() imut nex {

				polyc::algo(volatile_cast<double*>(&_value), sizeof(_value));

				auto value = _value;

				polyc::algo(volatile_cast<double*>(&_value), sizeof(_value));

				return value;
			}

			__compelled_inline imut bool __fpcall set(imut double value) nex {

				_value = value;

				return polyc::algo(volatile_cast<double*>(&_value), sizeof(_value));
			}

#pragma endregion

#pragma region Operators

			__compelled_inline qe_double __fpcall operator+(imut double value) imut nex {
				return qe_double(get() + value);
			};

			__compelled_inline qe_double __fpcall operator-(imut double value) imut nex {
				return qe_double(get() - value);
			}

			__compelled_inline qe_double __fpcall operator/(imut double value) imut nex {
				return qe_double(get() / value);
			}

			__compelled_inline qe_double __fpcall operator*(imut double value) imut nex {
				return qe_double(get() * value);
			}

			__compelled_inline qe_double& __fpcall operator+=(imut double value) nex {
				set(get() + value);
				return *this;
			}

			__compelled_inline qe_double& __fpcall operator-=(imut double value) nex {
				set(get() - value);
				return *this;
			}

			__compelled_inline qe_double& __fpcall operator*=(imut double value) nex {
				set(get() * value);
				return *this;
			}

			__compelled_inline qe_double& __fpcall operator/=(imut double value) nex {
				set(get() / value);
				return *this;
			}

			__compelled_inline qe_double& __fpcall operator=(imut double value) nex {
				set(value);
				return *this;
			}

			__compelled_inline __stackcall operator double() imut nex {
				return get();
			}

#pragma endregion
		};

		class qe_longdouble {

		private:

			noregister long double _value;

		public:

#pragma region Ctor / Dtor

			__compelled_inline __fpcall qe_longdouble(imut long double value = static_cast<long double>(0.0f)) {
				set(value);
			}

			__optimized_dtor ~qe_longdouble() nex {

				polyc::unregister_polyc_pointer(volatile_cast<long double*>(&_value));

				RtlZeroMemory(volatile_cast<long double*>(&this->_value), sizeof(_value));
			}

#pragma endregion

#pragma region Accessors

			__compelled_inline imut long double __stackcall get() imut nex {

				polyc::algo(volatile_cast<long double*>(&_value), sizeof(_value));

				auto value = _value;

				polyc::algo(volatile_cast<long double*>(&_value), sizeof(_value));

				return value;
			}

			__compelled_inline imut bool __fpcall set(imut long double value) nex {

				_value = value;

				return polyc::algo(volatile_cast<long double*>(&_value), sizeof(_value));
			}

#pragma endregion

#pragma region Operators

			__compelled_inline qe_longdouble __fpcall operator+(imut long double value) imut nex {
				return qe_longdouble(get() + value);
			};

			__compelled_inline qe_longdouble __fpcall operator-(imut long double value) imut nex {
				return qe_longdouble(get() - value);
			}

			__compelled_inline qe_longdouble __fpcall operator/(imut long double value) imut nex {
				return qe_longdouble(get() / value);
			}

			__compelled_inline qe_longdouble __fpcall operator*(imut long double value) imut nex {
				return qe_longdouble(get() * value);
			}

			__compelled_inline qe_longdouble& __fpcall operator+=(imut long double value) nex {
				set(get() + value);
				return *this;
			}

			__compelled_inline qe_longdouble& __fpcall operator-=(imut long double value) nex {
				set(get() - value);
				return *this;
			}

			__compelled_inline qe_longdouble& __fpcall operator*=(imut long double value) nex {
				set(get() * value);
				return *this;
			}

			__compelled_inline qe_longdouble& __fpcall operator/=(imut long double value) nex {
				set(get() / value);
				return *this;
			}

			__compelled_inline qe_longdouble& __fpcall operator=(imut long double value) nex {
				set(value);
				return *this;
			}

			__compelled_inline __stackcall operator long double() imut nex {
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

			__compelled_inline __fpcall qe_m128(imut __m128 value) nex {
				set(value);
			}

			__optimized_dtor ~qe_m128() nex {

				polyc::unregister_polyc_pointer(&_value);

				RtlZeroMemory(volatile_cast<__m128*>(&this->_value), sizeof(_value));
			}

#pragma endregion

#pragma region Accessors

			__compelled_inline imut __m128 __stackcall get() imut nex {

				polyc::algo(volatile_cast<__m128*>(&_value), sizeof(_value));

				auto value = _value;

				polyc::algo(volatile_cast<__m128*>(&_value), sizeof(_value));

				return value;
			}

			__compelled_inline imut bool __fpcall set(imut __m128 value) nex {

				_value = value;

				return polyc::algo(&_value, sizeof(_value));
			}
#pragma endregion

#pragma region Operators
	#ifdef __clang__ // msvc does not support math operatotions on vector types

			__compelled_inline qe_m128 __fpcall operator+(imut __m128 value) imut nex {
				return qe_m128(get() + value);
			};

			__compelled_inline qe_m128 __fpcall operator-(imut __m128 value) imut nex {
				return qe_m128(get() - value);
			}

			__compelled_inline qe_m128 __fpcall operator/(imut __m128 value) imut nex {
				return qe_m128((imut __m128)get() / value);
			}

			__compelled_inline qe_m128 __fpcall operator*(imut __m128 value) imut nex {
				return qe_m128(get() * value);
			}

			__compelled_inline qe_m128& __fpcall operator+=(imut __m128 value) nex {
				set(get() + value);
				return *this;
			}

			__compelled_inline qe_m128& __fpcall operator-=(imut __m128 value) nex {
				set(get() - value);
				return *this;
			}

			__compelled_inline qe_m128& __fpcall operator*=(imut __m128 value) nex {
				set(get() * value);
				return *this;
			}

			__compelled_inline qe_m128& __fpcall operator/=(imut __m128 value) nex {
				set(get() / value);
				return *this;
			}

	#endif

			__compelled_inline qe_m128& __fpcall operator=(imut __m128 value) nex {
				set(value);
				return *this;
			}

			__compelled_inline __stackcall operator __m128() imut nex {
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

			__compelled_inline __fpcall qe_m128i(imut __m128i value) nex {
				set(value);
			}

			__optimized_dtor ~qe_m128i() nex {

				polyc::unregister_polyc_pointer(&_value);

				RtlZeroMemory(volatile_cast<__m128i*>(&this->_value), sizeof(_value));
			}

#pragma endregion

#pragma region Accessors

			__compelled_inline imut __m128i __stackcall get() imut nex {

				polyc::algo(volatile_cast<__m128i*>(&_value), sizeof(_value));

				auto value = _value;

				polyc::algo(volatile_cast<__m128i*>(&_value), sizeof(_value));

				return value;
			}

			__compelled_inline imut bool __fpcall set(imut __m128i value) nex {

				_value = value;

				return polyc::algo(&_value, sizeof(_value));
			}

#pragma endregion

#pragma region Operators

	#ifdef __clang__ // msvc does not support math operators on vector types

			__compelled_inline qe_m128i __fpcall operator+(imut __m128i value) imut nex {
				return qe_m128i(get() + value);
			};

			__compelled_inline qe_m128i __fpcall operator-(imut __m128i value) imut nex {
				return qe_m128i(get() - value);
			}

			__compelled_inline qe_m128i __fpcall operator/(imut __m128i value) imut nex {
				return qe_m128i((imut __m128i)get() / value);
			}

			__compelled_inline qe_m128i __fpcall operator*(imut __m128i value) imut nex {
				return qe_m128i(get() * value);
			}

			__compelled_inline qe_m128i& __fpcall operator+=(imut __m128i value) nex {
				set(get() + value);
				return *this;
			}

			__compelled_inline qe_m128i& __fpcall operator-=(imut __m128i value) nex {
				set(get() - value);
				return *this;
			}

			__compelled_inline qe_m128i& __fpcall operator*=(imut __m128i value) nex {
				set(get() * value);
				return *this;
			}

			__compelled_inline qe_m128i& __fpcall operator/=(imut __m128i value) nex {
				set(get() / value);
				return *this;
			}

	#endif

			__compelled_inline qe_m128i& __fpcall operator=(imut __m128i value) nex {
				set(value);
				return *this;
			}

			__compelled_inline __stackcall operator __m128i() imut nex {
				return get();
			}

#pragma endregion
		};

		class qe_m128d {

		private:

			__m128d _value;

		public:

#pragma region Ctor / Dtor

			__compelled_inline __fpcall qe_m128d(imut __m128d value) nex {
				set(value);
			}

			__optimized_dtor ~qe_m128d() nex {

				polyc::unregister_polyc_pointer(&_value);

				RtlZeroMemory(volatile_cast<__m128d*>(&this->_value), sizeof(_value));
			}

#pragma endregion

#pragma region Accessors

			__compelled_inline imut __m128d __stackcall get() imut nex {

				polyc::algo(volatile_cast<__m128d*>(&_value), sizeof(_value));

				auto value = _value;

				polyc::algo(volatile_cast<__m128d*>(&_value), sizeof(_value));

				return value;
			}

			__compelled_inline imut bool __fpcall set(imut __m128d value) nex {

				_value = value;

				return polyc::algo(&_value, sizeof(_value));
			}
#pragma endregion

#pragma region Operators
	#ifdef __clang__ // msvc does not support math operators on vector types

			__compelled_inline qe_m128d __fpcall operator+(imut __m128d value) imut nex {
				return qe_m128d(get() + value);
			};

			__compelled_inline qe_m128d __fpcall operator-(imut __m128d value) imut nex {
				return qe_m128d(get() - value);
			}

			__compelled_inline qe_m128d __fpcall operator/(imut __m128d value) imut nex {
				return qe_m128d((imut __m128d)get() / value);
			}

			__compelled_inline qe_m128d __fpcall operator*(imut __m128d value) imut nex {
				return qe_m128d(get() * value);
			}

	#endif

	#ifdef __clang__

			__compelled_inline qe_m128d& __fpcall operator+=(imut __m128d value) nex {
				set(get() + value);
				return *this;
			}

			__compelled_inline qe_m128d& __fpcall operator-=(imut __m128d value) nex {
				set(get() - value);
				return *this;
			}

			__compelled_inline qe_m128d& __fpcall operator*=(imut __m128d value) nex {
				set(get() * value);
				return *this;
			}

			__compelled_inline qe_m128d& __fpcall operator/=(imut __m128d value) nex {
				set(get() / value);
				return *this;
			}

	#endif

			__compelled_inline qe_m128d& __fpcall operator=(imut __m128d value) nex {
				set(value);
				return *this;
			}

			__compelled_inline __stackcall operator __m128d() imut nex {
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

			__compelled_inline __fpcall qe_m256(imut __m256 value) nex {
				set(value);
			}
			
			__optimized_dtor ~qe_m256() nex {

				polyc::unregister_polyc_pointer(&_value);

				RtlZeroMemory(volatile_cast<__m256*>(&this->_value), sizeof(_value));
			}

#pragma endregion

#pragma region Accessors

			__compelled_inline imut __m256 __stackcall get() imut nex {

				polyc::algo(volatile_cast<__m256*>(&_value), sizeof(_value));

				auto value = _value;

				polyc::algo(volatile_cast<__m256*>(&_value), sizeof(_value));

				return value;
			}

			__compelled_inline imut bool __fpcall set(imut __m256 value) nex {

				_value = value;

				return polyc::algo(&_value, sizeof(_value));
			}

#pragma endregion

#pragma region Operators

	#ifdef __clang__ // msvc does not support math operators on vector types

			__compelled_inline qe_m256 __fpcall operator+(imut __m256 value) imut nex {
				return qe_m256(get() + value);
			};

			__compelled_inline qe_m256 __fpcall operator-(imut __m256 value) imut nex {
				return qe_m256(get() - value);
			}

			__compelled_inline qe_m256 __fpcall operator/(imut __m256 value) imut nex {
				return qe_m256((imut __m256)get() / value);
			}

			__compelled_inline qe_m256 __fpcall operator*(imut __m256 value) imut nex {
				return qe_m256(get() * value);
			}

			__compelled_inline qe_m256& __fpcall operator+=(imut __m256 value) nex {
				set(get() + value);
				return *this;
			}

			__compelled_inline qe_m256& __fpcall operator-=(imut __m256 value) nex {
				set(get() - value);
				return *this;
			}

			__compelled_inline qe_m256& __fpcall operator*=(imut __m256 value) nex {
				set(get() * value);
				return *this;
			}

			__compelled_inline qe_m256& __fpcall operator/=(imut __m256 value) nex {
				set(get() / value);
				return *this;
			}

	#endif

			__compelled_inline qe_m256& __fpcall operator=(imut __m256 value) nex {
				set(value);
				return *this;
			}

			__compelled_inline __stackcall operator __m256() imut nex {
				return get();
			}

#pragma endregion
		};

		class qe_m256i {

		private:

			__m256i _value;

		public:

#pragma region Ctor / Dtor

			__compelled_inline __fpcall qe_m256i(imut __m256i value) nex {
				set(value);
			}

			__optimized_dtor ~qe_m256i() nex {

				polyc::unregister_polyc_pointer(&_value);

				RtlZeroMemory(volatile_cast<__m256i*>(&this->_value), sizeof(_value));
			}

#pragma endregion

#pragma region Accessors

			__compelled_inline imut __m256i __stackcall get() imut nex {

				polyc::algo(volatile_cast<__m256i*>(&_value), sizeof(_value));

				auto value = _value;

				polyc::algo(volatile_cast<__m256i*>(&_value), sizeof(_value));

				return value;
			}

			__compelled_inline imut bool __fpcall set(imut __m256i value) nex {

				_value = value;

				return polyc::algo(&_value, sizeof(_value));
			}

#pragma endregion

#pragma region Operators
	#ifdef __clang__ // msvc does not support math operators on vector types

			__compelled_inline qe_m256i __fpcall operator+(imut __m256i value) imut nex {
				return qe_m256i(get() + value);
			};

			__compelled_inline qe_m256i __fpcall operator-(imut __m256i value) imut nex {
				return qe_m256i(get() - value);
			}

			__compelled_inline qe_m256i __fpcall operator/(imut __m256i value) imut nex {
				return qe_m256i((imut __m256i)get() / value);
			}

			__compelled_inline qe_m256i __fpcall operator*(imut __m256i value) imut nex {
				return qe_m256i(get() * value);
			}

			__compelled_inline qe_m256i& __fpcall operator+=(imut __m256i value) nex {
				set(get() + value);
				return *this;
			}

			__compelled_inline qe_m256i& __fpcall operator-=(imut __m256i value) nex {
				set(get() - value);
				return *this;
			}

			__compelled_inline qe_m256i& __fpcall operator*=(imut __m256i value) nex {
				set(get() * value);
				return *this;
			}

			__compelled_inline qe_m256i& __fpcall operator/=(imut __m256i value) nex {
				set(get() / value);
				return *this;
			}

	#endif

			__compelled_inline qe_m256i& __fpcall operator=(imut __m256i value) nex {
				set(value);
				return *this;
			}

			__compelled_inline __stackcall operator __m256i() imut nex {
				return get();
			}

#pragma endregion
		};

		class qe_m256d {

		private:

			__m256d _value;

		public:

#pragma region Ctor / Dtor

			__compelled_inline __fpcall qe_m256d(imut __m256d value) nex {
				set(value);
			}

			__optimized_dtor ~qe_m256d() nex {

				polyc::unregister_polyc_pointer(&_value);

				RtlZeroMemory(volatile_cast<__m256d*>(&this->_value), sizeof(_value));
			}

#pragma endregion

#pragma region Accessors

			__compelled_inline imut __m256d __stackcall get() imut nex {

				polyc::algo(volatile_cast<__m256d*>(&_value), sizeof(_value));

				auto value = _value;

				polyc::algo(volatile_cast<__m256d*>(&_value), sizeof(_value));

				return value;
			}

			__compelled_inline imut bool __fpcall set(imut __m256d value) nex {

				_value = value;

				return polyc::algo(&_value, sizeof(_value));
			}


#pragma endregion

#pragma region Operators

	#ifdef __clang__ // msvc does not support math operators on vector types

			__compelled_inline qe_m256d __fpcall operator+(imut __m256d value) imut nex {
				return qe_m256d(get() + value);
			};

			__compelled_inline qe_m256d __fpcall operator-(imut __m256d value) imut nex {
				return qe_m256d(get() - value);
			}

			__compelled_inline qe_m256d __fpcall operator/(imut __m256d value) imut nex {
				return qe_m256d((imut __m256d)get() / value);
			}

			__compelled_inline qe_m256d __fpcall operator*(imut __m256d value) imut nex {
				return qe_m256d(get() * value);
			}

	#endif

	#ifdef __clang__

			__compelled_inline qe_m256d& __fpcall operator+=(imut __m256d value) nex {
				set(get() + value);
				return *this;
			}

			__compelled_inline qe_m256d& __fpcall operator-=(imut __m256d value) nex {
				set(get() - value);
				return *this;
			}

			__compelled_inline qe_m256d& __fpcall operator*=(imut __m256d value) nex {
				set(get() * value);
				return *this;
			}

			__compelled_inline qe_m256d& __fpcall operator/=(imut __m256d value) nex {
				set(get() / value);
				return *this;
			}

	#endif

			__compelled_inline qe_m256d& __fpcall operator=(imut __m256d value) nex {
				set(value);
				return *this;
			}

			__compelled_inline __stackcall operator __m256d() imut nex {
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

			__compelled_inline __stackcall qe_string(imut std::string value) nex {
				
				set(value);
			}

			__optimized_ctor qe_string(imut char* value = "") nex {

				set(std::string(value));
			}

			__optimized_dtor ~qe_string() nex {

				polyc::unregister_polyc_pointer(reinterpret_cast<c_void>( imut_cast<char*>(_value.c_str()) ));

				RtlZeroMemory(imut_cast<char*>( _value.c_str() ), _value.length());
			}

#pragma endregion

#pragma region Accessors

			__compelled_inline imut std::string __stackcall get() imut nex {

				polyc::algo(imut_cast<char*>(_value.c_str()), _value.length());

				auto value = _value;

				polyc::algo(imut_cast<char*>(_value.c_str()), _value.length());

				return value;
			}

			__compelled_inline imut bool __stackcall set( imut std::string value ) nex {

				_value = value;

				return polyc::algo(imut_cast<char*>(_value.c_str()), _value.length());
			}

#pragma endregion	

#pragma region Operators

			__compelled_inline qe_string __stackcall operator+(imut std::string& value) imut nex {
				return qe_string( get() + value);
			};

			__compelled_inline qe_string& __stackcall operator+=(imut std::string& value) nex {
				set(get() + value );
				return *this;
			}

			__compelled_inline qe_string& __stackcall operator=(imut std::string& value) nex {
				set(value);
				return *this;
			}

			__compelled_inline __stackcall operator std::string() imut nex {
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

			__compelled_inline __stackcall qe_wstring(imut std::wstring value) nex {

				set(value);
			}

			__optimized_ctor qe_wstring(imut wchar_t* value = L"") nex {

				set(std::wstring(value));
			}

			__optimized_dtor ~qe_wstring() nex {

				polyc::unregister_polyc_pointer(reinterpret_cast<c_void>( imut_cast<wchar_t*>(_value.c_str()) ));

				RtlZeroMemory(imut_cast<wchar_t*>(_value.c_str()), _value.length() * sizeof(wchar_t));
			}

#pragma endregion

#pragma region Accessors

			__compelled_inline imut std::wstring __stackcall get() imut nex {

				polyc::algo(imut_cast<wchar_t*>(_value.c_str()), _value.length() * sizeof(wchar_t));

				auto value = _value;

				polyc::algo(imut_cast<wchar_t*>(_value.c_str()), _value.length() * sizeof(wchar_t));

				return value;
			}

			__compelled_inline imut bool __stackcall set(imut std::wstring value) nex {

				_value = value;

				return polyc::algo(imut_cast<wchar_t*>(_value.c_str()), _value.length() * sizeof(wchar_t));
			}

#pragma endregion

#pragma region Operators

			__compelled_inline qe_wstring __stackcall operator+(imut std::wstring& value) imut nex {
				return qe_wstring(get() + value);
			};

			__compelled_inline qe_wstring& __stackcall operator+=(imut std::wstring& value) nex {
				set(get() + value);
				return *this;
			}

			__compelled_inline qe_wstring& __stackcall operator=(imut std::wstring& value) nex {
				set(value);
				return *this;
			}

			__compelled_inline __stackcall operator std::wstring() imut nex {
				return get();
			}

#pragma endregion

		};

#pragma endregion

#pragma region Heap Allocation

		class qe_malloc {

		private:

#pragma region Global Variables

			c_void local_alloc;
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

				index_proxy(imut std::size_t index_, qe_malloc& instance) nex : index(index_), parent(instance) { }

#pragma endregion

#pragma region Operator overrides

				std::uint8_t& operator=(std::uint8_t value) nex {

					parent.set(index, value);

					return value;   // return the passed assignment value rather than using up absurd resources to decrypt, re-encrypt everything using get()
				}

				__compelled_inline __stackcall operator std::uint8_t() imut nex {

					return parent.get(index);
				}

#pragma endregion
			};

#pragma endregion

#pragma endregion

#pragma region Ctor

			__optimized_ctor qe_malloc(imut std::size_t size = 1)
				: 
				alloc_size(size),
				local_alloc(malloc(size))
			{

				if (!local_alloc)
					return;

				RtlZeroMemory(local_alloc, size);

				polyc::algo(local_alloc, size, false);
			}

#pragma endregion

#pragma region Get accessors

			__compelled_inline c_void __stackcall get() nex {
				return polyc::algo_inst(local_alloc, alloc_size, false);
			}

			__compelled_inline c_void __regcall get(imut std::uintptr_t pos, imut std::size_t length) nex {
				auto dec_alloc = reinterpret_cast<uint8_t*>(get());

				auto get_alloc = malloc(length);

				if (!get_alloc)
					return nullptr;

				memcpy(get_alloc, &dec_alloc[pos], length);

				RtlZeroMemory(dec_alloc, alloc_size);
				free(dec_alloc);

				return get_alloc;
			}

			__compelled_inline std::uint8_t __regcall get(imut std::size_t index) nex {

				auto dec_alloc = reinterpret_cast<std::uint8_t*>(get());

				auto _return = dec_alloc[index];

				RtlZeroMemory(dec_alloc, alloc_size);
				free(dec_alloc);

				return _return;
			}

			template<typename T>
			__compelled_inline T& __regcall get_t(imut std::uintptr_t pos) nex {

				auto value_r = reinterpret_cast<T*>(get(pos, sizeof(T)));

				auto _return = *value_r;

				free(value_r);

				return std::move(
					_return
				);
			}

			__compelled_inline c_void __stackcall get_data_pointer() nex {
				return local_alloc;
			}

			__compelled_inline std::size_t __stackcall get_data_size() nex {
				return alloc_size;
			}

#pragma endregion

#pragma region Set accessors

			//WARNING: appending length to the allocation here will cause exceptions / UB
			__compelled_inline void __regcall set(
				
				c_void src,
				imut std::uintptr_t pos,
				imut std::size_t length,
				imut bool free_src = false
			) nex {

				auto dec_alloc = get();

				memcpy(&static_cast<std::uint8_t*>(dec_alloc)[pos], src, length);

				auto enc_alloc = polyc::algo_inst(dec_alloc, length, false);
				//free the decryption allocation and local alocation: reminder this class is performance-heavy and should not be used for large allocation pools
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
			) nex {

				auto dec_alloc = reinterpret_cast<std::uint8_t*>(get());

				for (auto i = pos; i < (pos + size); ++i) {
					dec_alloc[i] = value;
				}

				auto enc_alloc = polyc::algo_inst(dec_alloc, alloc_size, false);

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
			__compelled_inline void __regcall set(std::uintptr_t pos, T value) nex {
				auto dec_alloc = reinterpret_cast<std::uint8_t*>(get()); // so we can properly index the allocation

				T* cast_t = reinterpret_cast<T*>(&dec_alloc[pos]);
				*cast_t = value;

				auto enc_alloc = polyc::algo_inst(dec_alloc, alloc_size, false);
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

			__compelled_inline void __regcall swap(c_void src, imut std::size_t length, imut bool free_src = false) nex {
				//release current resources
				zero();
				free(local_alloc);
				local_alloc = nullptr;
				alloc_size = 0x0000000000000000ULL;

				auto enc_alloc = polyc::algo_inst(src, length, false);

				alloc_size = length;
				local_alloc = enc_alloc;

				if (free_src)
					free(src);
			}

			//size is only the length in bytes of the allocation to be appended or destroyed
			__compelled_inline bool __regcall resize(imut std::size_t size) nex {
				auto dec_alloc = get();

				auto n_local_alloc = realloc(dec_alloc, size);

				if (!n_local_alloc) {
					free(dec_alloc);
					return false;
				}

				dec_alloc = NULL; // zero  old pointer ;; useless even if realloc didnt need to move memory
				//zero out the extended memory (if it was being extended rather than shrunk)
				if ((size) > alloc_size)
					RtlZeroMemory(&(reinterpret_cast<std::uint8_t*>(n_local_alloc)[alloc_size]), (size - alloc_size));

				auto enc_alloc = polyc::algo_inst(n_local_alloc, size, false);
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

			__compelled_inline void __stackcall zero() nex {
				set(0x0000000000000000ULL, 0x0ui8, alloc_size);
			}

#pragma endregion

#pragma region Operators

			__compelled_inline qe_malloc& __regcall operator=(imut std::vector<std::uint8_t>& value) nex {
				swap(volatile_cast<std::vector<std::uint8_t>*>(&value)->data(), value.size());

				return *this;
			}

			template<typename T>
			__compelled_inline __stackcall operator T* () imut nex {
				return reinterpret_cast<T*>( polyc::algo_inst(local_alloc, alloc_size, false) );
			}

			index_proxy __regcall operator[](std::size_t index) nex {
				return index_proxy(index, *this);
			}

#pragma endregion

#pragma region Destructor

			__compelled_inline imut bool __stackcall destroy() nex {

				if (!local_alloc)
					return false;

				RtlZeroMemory(local_alloc, alloc_size);

				free(local_alloc);
			}

			__compelled_inline __stackcall ~qe_malloc() nex {
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
