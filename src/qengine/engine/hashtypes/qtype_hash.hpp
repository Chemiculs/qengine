/*
/******************************************************************************************************************
*																											     *
*  QTYPE_HASH is the lower wrapper of the polymorphic type engine which ensures secure data access and integrity *
*																											     *
*******************************************************************************************************************
*/

#pragma region Header Guard

#ifndef QTYPE_HASH_H
#define QTYPE_HASH_H

#pragma endregion

#pragma region Imports

#pragma region std

#include <string>

#pragma endregion

#pragma region qengine

#include "../../qhash/qhash.hpp"
#include "../../qbase/qcallback.hpp"

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

namespace qengine {

	namespace qtype_hash {

#pragma region Globals

		extern noregister qengine::qcallback::qmem_exception_rogue_c violation_callback;

		extern bool is_init;

#pragma endregion

#pragma region Global Static Methods / Callbacks

		static __symbolic void __regcall violation_callback_d(qengine::qexcept::q_rogueaccess except, c_void data) nex {

			if (except.id != qengine::qexcept::MEMORY_ALTERATION) // ensure this callback has been raised due to memory alteration
				return;
		}

		static __compelled_inline void __regcall init_hash_t(qengine::qcallback::qmem_exception_rogue_c callback = violation_callback_d) nex {

			violation_callback = callback;

			is_init = true;
		}

#pragma endregion

#pragma region Types

#pragma region Template / User-Defined

template<typename T>
class qh_struct{

		private:

	#pragma region Globals

			mut noregister T _value;

			mut std::uintptr_t _hash;

			mut bool is_polyc_alteration;

	#pragma endregion

		public:

	#pragma region Ctor / Dtor

			__optimized_ctor qh_struct( imut T value = T{} ) nex {

				if (!is_init)
					init_hash_t();

				set(value);
			}

			__optimized_dtor ~qh_struct() nex {
			
				RtlZeroMemory(volatile_cast<T*>(&this->_value), sizeof(T));
				RtlZeroMemory(&this->_hash, sizeof(std::uintptr_t));
				RtlZeroMemory(&this->is_polyc_alteration, sizeof(bool));
			}
			
	#pragma endregion

	#pragma region Accessors

			__compelled_inline T* __stackcall open_data_ptr() imut nex {

				is_polyc_alteration = true;

				return volatile_cast<T*>(&_value);
			}

			__compelled_inline imut bool __stackcall close_data_ptr() imut nex {

				auto hash = qhash::qhash_cpu(volatile_cast<T*>(&_value), sizeof(_value));

				this->_hash = std::move(hash);

				is_polyc_alteration = false;

				return true;
			}

			__compelled_inline imut T __stackcall get() imut nex {

				if (!is_polyc_alteration) {

					auto hash = qhash::qhash_cpu(volatile_cast<T*>(&_value), sizeof(T));

					if (hash != _hash)
						violation_callback(qengine::qexcept::q_rogueaccess(this->_hash, hash), volatile_cast<T*>(&_value));
				}

				return *volatile_cast<T*>(&_value);
			}

			template<typename _T>
			__compelled_inline decltype(auto) __regcall get( _T T::* member ) imut nex {

				if (!is_polyc_alteration) {

					auto hash = qhash::qhash_cpu(volatile_cast<T*>(&_value), sizeof(T));

					if (hash != _hash)
						violation_callback(qengine::qexcept::q_rogueaccess(this->_hash, hash), volatile_cast<T*>(&_value));
				}

				return _value.*member;
			}

			__compelled_inline void __regcall set( imut T value ) nex {

				auto hash = qhash::qhash_cpu( imut_cast<T*>(&value), sizeof(T));

				this->_hash = std::move(hash);

				*volatile_cast<T*>(&_value) = std::move(value);
			}

			template<typename _T>
			__compelled_inline imut bool __regcall set( _T T::* member, imut _T value ) nex {

				_value.*member = std::move(value);

				auto hash = qhash::qhash_cpu(volatile_cast<T*>(&_value), sizeof(T));

				this->_hash = std::move(hash);

				return true;
			}

			__compelled_inline imut T* __stackcall get_raw_memory_address() imut nex {
				return volatile_cast<T*>(&_value);
			}

	#pragma endregion

	#pragma region Operators

			__compelled_inline qh_struct& __regcall operator=(imut T value) nex {
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

class qh_bool{

		private:

#pragma region Globals

			mut noregister bool _value;

			mut std::uintptr_t _hash;

			mut bool is_polyc_alteration;

#pragma endregion

		public:

#pragma region Ctor / Dtor

			__optimized_ctor qh_bool(imut bool value = false) nex {

				if (!is_init)
					init_hash_t();

				set(value);
			}

			__optimized_dtor ~qh_bool() nex {
			
				RtlZeroMemory(volatile_cast<bool*>(&this->_value), sizeof(bool));
				RtlZeroMemory(&this->_hash, sizeof(std::uintptr_t));
				RtlZeroMemory(&this->is_polyc_alteration, sizeof(bool));
			}
			
#pragma endregion

#pragma region Accessors

			__compelled_inline bool* __stackcall open_data_ptr() imut nex {

				is_polyc_alteration = true;

				return volatile_cast<bool*>(&_value);
			}

			__compelled_inline imut bool __stackcall close_data_ptr() imut nex {

				auto hash = qhash::qhash_cpu(volatile_cast<bool*>(&_value), sizeof(_value));

				this->_hash = std::move(hash);

				is_polyc_alteration = false;

				return true;
			}

			__compelled_inline bool __stackcall get() imut nex {

				if (!is_polyc_alteration) {

					auto hash = qhash::qhash_cpu(volatile_cast<bool*>(&_value), sizeof(_value));

					if (hash != _hash)
						violation_callback(qengine::qexcept::q_rogueaccess(this->_hash, hash), volatile_cast<bool*>(&_value));
				}

				return _value;
			}

			__compelled_inline void __regcall set( imut bool value ) nex {

				auto hash = qhash::qhash_cpu(imut_cast<bool*>(&value), sizeof(value));

				this->_hash = std::move(hash);

				_value = value;
			}

			__compelled_inline imut bool* __stackcall get_raw_memory_address() imut nex {
				return volatile_cast<bool*>(&_value);
			}

#pragma endregion

#pragma region Operators

			__compelled_inline qh_bool& __regcall operator=(imut bool value) nex {
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

		class qh_int8{

		private:

#pragma region Globals

			mut noregister std::int8_t _value;

			mut std::uintptr_t _hash;

			mut bool is_polyc_alteration;

#pragma endregion

		public:

#pragma region Ctor / Dtor

			__optimized_ctor qh_int8(imut std::int8_t value = 0) nex {

				if (!is_init)
					init_hash_t();

				set(value);
			}

			__optimized_dtor ~qh_int8() nex {
			
				RtlZeroMemory(volatile_cast<std::int8_t*>(&this->_value), sizeof(std::int8_t));
				RtlZeroMemory(&this->_hash, sizeof(std::uintptr_t));
				RtlZeroMemory(&this->is_polyc_alteration, sizeof(bool));
			}
			
#pragma endregion

#pragma region Accessors

			__compelled_inline std::int8_t* __stackcall open_data_ptr() imut nex {

				is_polyc_alteration = true;

				return volatile_cast<std::int8_t*>(&_value);
			}

			__compelled_inline imut bool __stackcall close_data_ptr() imut nex {

				auto hash = qhash::qhash_cpu(volatile_cast<std::int8_t*>(&_value), sizeof(_value));

				this->_hash = std::move(hash);

				is_polyc_alteration = false;

				return true;
			}

			__compelled_inline std::int8_t __stackcall get() imut nex {

				if (!is_polyc_alteration) {

					auto hash = qhash::qhash_cpu(volatile_cast<std::int8_t*>(&_value), sizeof(_value));

					if (hash != _hash)
						violation_callback(qengine::qexcept::q_rogueaccess(this->_hash, hash), volatile_cast<std::int8_t*>(&_value));
				}

				return _value;
			}

			__compelled_inline void __regcall set( imut std::int8_t value ) nex {

				auto hash = qhash::qhash_cpu(imut_cast<std::int8_t*>(&value), sizeof(value));

				this->_hash = std::move(hash);

				_value = value;
			}

			__compelled_inline imut std::int8_t* __stackcall get_raw_memory_address() imut nex {
				return volatile_cast<std::int8_t*>(&_value);
			}

#pragma endregion

#pragma region Operators

			__compelled_inline qh_int8 __regcall operator+(imut std::int8_t value) imut nex {
				return qh_int8(get() + value);
			};

			__compelled_inline qh_int8 __regcall operator-(imut std::int8_t value) imut nex {
				return qh_int8(get() - value);
			}

			__compelled_inline qh_int8 __regcall operator/(imut std::int8_t value) imut nex {
				return qh_int8(get() / value);
			}

			__compelled_inline qh_int8 __regcall operator*(imut std::int8_t value) imut nex {
				return qh_int8(get() * value);
			}

			__compelled_inline qh_int8 __regcall operator&(imut std::int8_t value) imut nex {
				return qh_int8(get() & value);
			}

			__compelled_inline qh_int8 __regcall operator|(imut std::int8_t value) imut nex {
				return qh_int8(get() | value);
			}

			__compelled_inline qh_int8 __regcall operator%(imut std::int8_t value) imut nex {
				return qh_int8(get() % value);
			}

			__compelled_inline qh_int8 __regcall operator^(imut std::int8_t value) imut nex {
				return qh_int8(get() ^ value);
			}

			__compelled_inline qh_int8 __regcall operator<<(imut std::int8_t value) imut nex {
				return qh_int8(get() << value);
			}

			__compelled_inline qh_int8 __regcall operator>>(imut std::int8_t value) imut nex {
				return qh_int8(get() >> value);
			}

			__compelled_inline qh_int8& __regcall operator+=(imut std::int8_t value) nex {
				set(static_cast<std::int8_t>(get() + value));
				return *this;
			}

			__compelled_inline qh_int8& __regcall operator-=(imut std::int8_t value) nex {
				set(static_cast<std::int8_t>(get() - value));
				return *this;
			}

			__compelled_inline qh_int8& __stackcall operator++() nex {
				operator+=(1i8);
				return *this;
			}

			__compelled_inline qh_int8& __stackcall operator--() nex {
				operator-=(1i8);
				return *this;
			}

			__compelled_inline qh_int8& __regcall operator*=(imut std::int8_t value) nex {
				set(static_cast<std::int8_t>(get() * value));
				return *this;
			}

			__compelled_inline qh_int8& __regcall operator/=(imut std::int8_t value) nex {
				set(static_cast<std::int8_t>(get() / value));
				return *this;
			}

			__compelled_inline qh_int8& __regcall operator%=(imut std::int8_t value) nex {
				set(static_cast<std::int8_t>(get() % value));
				return *this;
			}

			__compelled_inline qh_int8& __regcall operator^=(imut std::int8_t value) nex {
				set(static_cast<std::int8_t>(get() ^ value));
				return *this;
			}

			__compelled_inline qh_int8& __regcall operator&=(imut std::int8_t value) nex {
				set(static_cast<std::int8_t>(get() & value));
				return *this;
			}

			__compelled_inline qh_int8& __regcall operator|=(imut std::int8_t value) nex {
				set(static_cast<std::int8_t>(get() | value));
				return *this;
			}

			__compelled_inline qh_int8& __regcall operator<<=(imut std::int8_t value) nex {
				set(static_cast<std::int8_t>(get() << value));
				return *this;
			}

			__compelled_inline qh_int8& __regcall operator>>=(imut std::int8_t value) nex {
				set(static_cast<std::int8_t>(get() >> value));
				return *this;
			}

			__compelled_inline qh_int8& __regcall operator=(imut std::int8_t value) nex {
				set(value);
				return *this;
			}

			__compelled_inline __stackcall operator std::int8_t() imut nex {
				return get();
			}

#pragma endregion

		};

		class qh_uint8 {

		private:

#pragma region Globals

			mut noregister std::uint8_t _value;

			mut std::uintptr_t _hash;

			mut bool is_polyc_alteration;

#pragma endregion

		public:

#pragma region Ctor / Dtor

			__optimized_ctor qh_uint8(imut std::uint8_t value = 0) nex {

				if (!is_init)
					init_hash_t();

				set(value);
			}

			__optimized_dtor ~qh_uint8() nex {
			
				RtlZeroMemory(volatile_cast<std::uint8_t*>(&this->_value), sizeof(std::uint8_t));
				RtlZeroMemory(&this->_hash, sizeof(std::uintptr_t));
				RtlZeroMemory(&this->is_polyc_alteration, sizeof(bool));
			}

#pragma endregion

#pragma region Accessors

			__compelled_inline std::uint8_t* __stackcall open_data_ptr() imut nex {

				is_polyc_alteration = true;

				return volatile_cast<std::uint8_t*>(&_value);
			}

			__compelled_inline imut bool __stackcall close_data_ptr() imut nex {

				auto hash = qhash::qhash_cpu(volatile_cast<std::uint8_t*>(&_value), sizeof(_value));

				this->_hash = std::move(hash);

				is_polyc_alteration = false;

				return true;
			}

			__compelled_inline std::uint8_t __stackcall get() imut nex {

				if (!is_polyc_alteration) {

					auto hash = qhash::qhash_cpu(volatile_cast<std::uint8_t*>(&_value), sizeof(_value));

					if (hash != _hash)
						violation_callback(qengine::qexcept::q_rogueaccess(this->_hash, hash), volatile_cast<std::uint8_t*>(&_value));
				}

				return _value;
			}

			__compelled_inline void __regcall set( imut std::uint8_t value) nex {

				auto hash = qhash::qhash_cpu(imut_cast<std::uint8_t*>(&value), sizeof(value));

				this->_hash = std::move(hash);

				_value = value;
			}

			__compelled_inline imut std::uint8_t* __stackcall get_raw_memory_address() imut nex {
				return volatile_cast<std::uint8_t*>(&_value);
			}

#pragma endregion

#pragma region Operators

			__compelled_inline qh_uint8 __regcall operator+(imut std::uint8_t value) imut nex {
				return qh_uint8(get() + value);
			};

			__compelled_inline qh_uint8 __regcall operator-(imut std::uint8_t value) imut nex {
				return qh_uint8(get() - value);
			}

			__compelled_inline qh_uint8 __regcall operator/(imut std::uint8_t value) imut nex {
				return qh_uint8(get() / value);
			}

			__compelled_inline qh_uint8 __regcall operator*(imut std::uint8_t value) imut nex {
				return qh_uint8(get() * value);
			}

			__compelled_inline qh_uint8 __regcall operator&(imut std::uint8_t value) imut nex {
				return qh_uint8(get() & value);
			}

			__compelled_inline qh_uint8 __regcall operator|(imut std::uint8_t value) imut nex {
				return qh_uint8(get() | value);
			}

			__compelled_inline qh_uint8 __regcall operator%(imut std::uint8_t value) imut nex {
				return qh_uint8(get() % value);
			}

			__compelled_inline qh_uint8 __regcall operator^(imut std::uint8_t value) imut nex {
				return qh_uint8(get() ^ value);
			}

			__compelled_inline qh_uint8 __regcall operator<<(imut std::uint8_t value) imut nex {
				return qh_uint8(get() << value);
			}

			__compelled_inline qh_uint8 __regcall operator>>(imut std::uint8_t value) imut nex {
				return qh_uint8(get() >> value);
			}

			__compelled_inline qh_uint8& __regcall operator+=(imut std::uint8_t value) nex {
				set(static_cast<std::uint8_t>(get() + value));
				return *this;
			}

			__compelled_inline qh_uint8& __regcall operator-=(imut std::uint8_t value) nex {
				set(static_cast<std::uint8_t>(get() - value));
				return *this;
			}

			__compelled_inline qh_uint8& __stackcall operator++() nex {
				operator+=(1i8);
				return *this;
			}

			__compelled_inline qh_uint8& __stackcall operator--() nex {
				operator-=(1i8);
				return *this;
			}

			__compelled_inline qh_uint8& __regcall operator*=(imut std::uint8_t value) nex {
				set(static_cast<std::uint8_t>(get() * value));
				return *this;
			}

			__compelled_inline qh_uint8& __regcall operator/=(imut std::uint8_t value) nex {
				set(static_cast<std::uint8_t>(get() / value));
				return *this;
			}

			__compelled_inline qh_uint8& __regcall operator%=(imut std::uint8_t value) nex {
				set(static_cast<std::uint8_t>(get() % value));
				return *this;
			}

			__compelled_inline qh_uint8& __regcall operator^=(imut std::uint8_t value) nex {
				set(static_cast<std::uint8_t>(get() ^ value));
				return *this;
			}

			__compelled_inline qh_uint8& __regcall operator&=(imut std::uint8_t value) nex {
				set(static_cast<std::uint8_t>(get() & value));
				return *this;
			}

			__compelled_inline qh_uint8& __regcall operator|=(imut std::uint8_t value) nex {
				set(static_cast<std::uint8_t>(get() | value));
				return *this;
			}

			__compelled_inline qh_uint8& __regcall operator<<=(imut std::uint8_t value) nex {
				set(static_cast<std::uint8_t>(get() << value));
				return *this;
			}

			__compelled_inline qh_uint8& __regcall operator>>=(imut std::uint8_t value) nex {
				set(static_cast<std::uint8_t>(get() >> value));
				return *this;
			}

			__compelled_inline qh_uint8& __regcall operator=(imut std::uint8_t value) nex {
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

		class qh_int16 {

		private:

#pragma region Globals

			mut noregister std::int16_t _value;

			mut std::uintptr_t _hash;

			mut bool is_polyc_alteration;

#pragma endregion

		public:

#pragma region Ctor / Dtor

			__optimized_ctor qh_int16(imut std::int16_t value = 0) nex {

				if (!is_init)
					init_hash_t();

				set(value);
			}

			__optimized_dtor ~qh_int16() nex {
			
				RtlZeroMemory(volatile_cast<std::int16_t*>(&this->_value), sizeof(std::int16_t));
				RtlZeroMemory(&this->_hash, sizeof(std::uintptr_t));
				RtlZeroMemory(&this->is_polyc_alteration, sizeof(bool));
			}

#pragma endregion

#pragma region Accessors

			__compelled_inline std::int16_t* __stackcall open_data_ptr() imut nex {

				is_polyc_alteration = true;

				return volatile_cast<std::int16_t*>(&_value);
			}

			__compelled_inline imut bool __stackcall close_data_ptr() imut nex {

				auto hash = qhash::qhash_cpu(volatile_cast<std::int16_t*>(&_value), sizeof(_value));

				this->_hash = std::move(hash);

				is_polyc_alteration = false;

				return true;
			}

			__compelled_inline std::int16_t __stackcall get() imut nex {

				if (!is_polyc_alteration) {

					auto hash = qhash::qhash_cpu(volatile_cast<std::int16_t*>(&_value), sizeof(_value));

					if (hash != _hash)
						violation_callback(qengine::qexcept::q_rogueaccess(this->_hash, hash), volatile_cast<std::int16_t*>(&_value));
				}

				return _value;
			}

			__compelled_inline void __regcall set( imut std::int16_t value) nex {

				auto hash = qhash::qhash_cpu(imut_cast<std::int16_t*>(&value), sizeof(value));

				this->_hash = std::move(hash);

				_value = value;
			}

			__compelled_inline imut std::int16_t* __stackcall get_raw_memory_address() imut nex {
				return volatile_cast<std::int16_t*>(&_value);
			}

#pragma endregion

#pragma region Operators

			__compelled_inline qh_int16 __regcall operator+(imut std::int16_t value) imut nex {
				return qh_int16(get() + value);
			};

			__compelled_inline qh_int16 __regcall operator-(imut std::int16_t value) imut nex {
				return qh_int16(get() - value);
			}

			__compelled_inline qh_int16 __regcall operator/(imut std::int16_t value) imut nex {
				return qh_int16(get() / value);
			}

			__compelled_inline qh_int16 __regcall operator*(imut std::int16_t value) imut nex {
				return qh_int16(get() * value);
			}

			__compelled_inline qh_int16 __regcall operator&(imut std::int16_t value) imut nex {
				return qh_int16(get() & value);
			}

			__compelled_inline qh_int16 __regcall operator|(imut std::int16_t value) imut nex {
				return qh_int16(get() | value);
			}

			__compelled_inline qh_int16 __regcall operator%(imut std::int16_t value) imut nex {
				return qh_int16(get() % value);
			}

			__compelled_inline qh_int16 __regcall operator^(imut std::int16_t value) imut nex {
				return qh_int16(get() ^ value);
			}

			__compelled_inline qh_int16 __regcall operator<<(imut std::int16_t value) imut nex {
				return qh_int16(get() << value);
			}

			__compelled_inline qh_int16 __regcall operator>>(imut std::int16_t value) imut nex {
				return qh_int16(get() >> value);
			}

			__compelled_inline qh_int16& __regcall operator+=(imut std::int16_t value) nex {
				set(static_cast<short>(get() + value));
				return *this;
			}

			__compelled_inline qh_int16& __regcall operator-=(imut std::int16_t value) nex {
				set(static_cast<std::int16_t>(get() - value));
				return *this;
			}

			__compelled_inline qh_int16& __regcall operator++() nex {
				operator+=(1i8);
				return *this;
			}

			__compelled_inline qh_int16& __regcall operator--() nex {
				operator-=(1i8);
				return *this;
			}

			__compelled_inline qh_int16& __regcall operator*=(imut std::int16_t value) nex {
				set(static_cast<std::int16_t>(get() * value));
				return *this;
			}

			__compelled_inline qh_int16& __regcall operator/=(imut std::int16_t value) nex {
				set(static_cast<std::int16_t>(get() / value));
				return *this;
			}

			__compelled_inline qh_int16& __regcall operator%=(imut std::int16_t value) nex {
				set(static_cast<std::int16_t>(get() % value));
				return *this;
			}

			__compelled_inline qh_int16& __regcall operator^=(imut std::int16_t value) nex {
				set(static_cast<std::int16_t>(get() ^ value));
				return *this;
			}

			__compelled_inline qh_int16& __regcall operator&=(imut std::int16_t value) nex {
				set(static_cast<std::int16_t>(get() & value));
				return *this;
			}

			__compelled_inline qh_int16& __regcall operator|=(imut std::int16_t value) nex {
				set(static_cast<std::int16_t>(get() | value));
				return *this;
			}

			__compelled_inline qh_int16& __regcall operator<<=(imut std::int16_t value) nex {
				set(static_cast<std::int16_t>(get() << value));
				return *this;
			}

			__compelled_inline qh_int16& __regcall operator>>=(imut std::int16_t value) nex {
				set(static_cast<std::int16_t>(get() >> value));
				return *this;
			}

			__compelled_inline qh_int16& __regcall operator=(imut std::int16_t value) nex {
				set(value);
				return *this;
			}

			__compelled_inline __stackcall operator std::int16_t() imut nex {
				return get();
			}

#pragma endregion
		};

		class qh_uint16 {

		private:

#pragma region Globals

			mut noregister std::uint16_t _value;

			mut std::uintptr_t _hash;

			mut bool is_polyc_alteration;

#pragma endregion

		public:

#pragma region Ctor / Dtor

			__optimized_ctor qh_uint16(std::uint16_t value = 0) nex {

				if (!is_init)
					init_hash_t();

				set(value);
			}

			__optimized_dtor ~qh_uint16() nex {
			
				RtlZeroMemory(volatile_cast<std::uint16_t*>(&this->_value), sizeof(std::uint16_t));
				RtlZeroMemory(&this->_hash, sizeof(std::uintptr_t));
				RtlZeroMemory(&this->is_polyc_alteration, sizeof(bool));
			}

#pragma endregion

#pragma region Accessors

			__compelled_inline std::uint16_t* __stackcall open_data_ptr() imut nex {

				is_polyc_alteration = true;

				return volatile_cast<std::uint16_t*>(&_value);
			}

			__compelled_inline imut bool __stackcall close_data_ptr() imut nex {

				auto hash = qhash::qhash_cpu(volatile_cast<std::uint16_t*>(&_value), sizeof(_value));

				this->_hash = std::move(hash);

				is_polyc_alteration = false;

				return true;
			}

			__compelled_inline std::uint16_t __stackcall get() imut nex {

				if (!is_polyc_alteration) {

					auto hash = qhash::qhash_cpu(volatile_cast<std::uint16_t*>(&_value), sizeof(_value));

					if (hash != _hash)
						violation_callback(qengine::qexcept::q_rogueaccess(this->_hash, hash), volatile_cast<std::uint16_t*>(&_value));
				}

				return _value;
			}

			__compelled_inline void __regcall set( imut std::uint16_t value) nex {

				auto hash = qhash::qhash_cpu(imut_cast<std::uint16_t*>(&value), sizeof(value));

				this->_hash = std::move(hash);

				_value = value;
			}

			__compelled_inline imut std::uint16_t* get_raw_memory_address() imut nex {
				return volatile_cast<std::uint16_t*>(&_value);
			}

#pragma endregion

#pragma region Operators

			__compelled_inline qh_uint16 __regcall operator+(imut std::uint16_t value) imut nex {
				return qh_uint16(get() + value);
			};

			__compelled_inline qh_uint16 __regcall operator-(imut std::uint16_t value) imut nex {
				return qh_uint16(get() - value);
			}

			__compelled_inline qh_uint16 __regcall operator/(imut std::uint16_t value) imut nex {
				return qh_uint16(get() / value);
			}

			__compelled_inline qh_uint16 __regcall operator*(imut std::uint16_t value) imut nex {
				return qh_uint16(get() * value);
			}

			__compelled_inline qh_uint16 __regcall operator&(imut std::uint16_t value) imut nex {
				return qh_uint16(get() & value);
			}

			__compelled_inline qh_uint16 __regcall operator|(imut std::uint16_t value) imut nex {
				return qh_uint16(get() | value);
			}

			__compelled_inline qh_uint16 __regcall operator%(imut std::uint16_t value) imut nex {
				return qh_uint16(get() % value);
			}

			__compelled_inline qh_uint16 __regcall operator^(imut std::uint16_t value) imut nex {
				return qh_uint16(get() ^ value);
			}

			__compelled_inline qh_uint16 __regcall operator<<(imut std::uint16_t value) imut nex {
				return qh_uint16(get() << value);
			}

			__compelled_inline qh_uint16 __regcall operator>>(imut std::uint16_t value) imut nex {
				return qh_uint16(get() >> value);
			}

			__compelled_inline qh_uint16& __regcall operator+=(imut std::uint16_t value) nex {
				set(static_cast<std::uint16_t>(get() + value));
				return *this;
			}

			__compelled_inline qh_uint16& __regcall operator-=(imut std::uint16_t value) nex {
				set(static_cast<std::uint16_t>(get() - value));
				return *this;
			}

			__compelled_inline qh_uint16& __regcall operator++() nex {
				operator+=(1i8);
				return *this;
			}

			__compelled_inline qh_uint16& __regcall operator--() nex {
				operator-=(1i8);
				return *this;
			}

			__compelled_inline qh_uint16& __regcall operator*=(imut std::uint16_t value) nex {
				set(static_cast<std::uint16_t>(get() * value));
				return *this;
			}

			__compelled_inline qh_uint16& __regcall operator/=(imut std::uint16_t value) nex {
				set(static_cast<std::uint16_t>(get() / value));
				return *this;
			}

			__compelled_inline qh_uint16& __regcall operator%=(imut std::uint16_t value) nex {
				set(static_cast<std::uint16_t>(get() % value));
				return *this;
			}

			__compelled_inline qh_uint16& __regcall operator^=(imut std::uint16_t value) nex {
				set(static_cast<std::uint16_t>(get() ^ value));
				return *this;
			}

			__compelled_inline qh_uint16& __regcall operator&=(imut std::uint16_t value) nex {
				set(static_cast<std::uint16_t>(get() & value));
				return *this;
			}

			__compelled_inline qh_uint16& __regcall operator|=(imut std::uint16_t value) nex {
				set(static_cast<std::uint16_t>(get() | value));
				return *this;
			}

			__compelled_inline qh_uint16& __regcall operator<<=(imut std::uint16_t value) nex {
				set(static_cast<std::uint16_t>(get() << value));
				return *this;
			}

			__compelled_inline qh_uint16& __regcall operator>>=(imut std::uint16_t value) nex {
				set(static_cast<std::uint16_t>(get() >> value));
				return *this;
			}

			__compelled_inline qh_uint16& __regcall operator=(imut std::uint16_t value) nex {
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

		class qh_int32 {

		private:

#pragma region Globals

			mut noregister std::int32_t _value;

			mut std::uintptr_t _hash;

			mut bool is_polyc_alteration = false;

#pragma endregion

		public:

#pragma region Ctor / Dtor

			__optimized_ctor qh_int32(std::int32_t value = 0) nex {

				if (!is_init)
					init_hash_t();

				set(value);
			}

			__optimized_dtor ~qh_int32() nex {
			
				RtlZeroMemory(volatile_cast<std::int32_t*>(&this->_value), sizeof(std::int32_t));
				RtlZeroMemory(&this->_hash, sizeof(std::uintptr_t));
				RtlZeroMemory(&this->is_polyc_alteration, sizeof(bool));
			}

#pragma endregion

#pragma region Accessors

			__compelled_inline std::int32_t* __stackcall open_data_ptr() imut nex {

				is_polyc_alteration = true;

				return volatile_cast<std::int32_t*>(&_value);
			}

			__compelled_inline imut bool __stackcall close_data_ptr() imut nex {

				auto hash = qhash::qhash_cpu(volatile_cast<std::int32_t*>(&_value), sizeof(_value));

				this->_hash = std::move(hash);

				is_polyc_alteration = false;

				return true;
			}

			__compelled_inline std::int32_t __stackcall get() imut nex {

				if (!is_polyc_alteration) {

					auto hash = qhash::qhash_cpu(volatile_cast<std::int32_t*>(&_value), sizeof(_value));

					if (hash != _hash)
						violation_callback(qengine::qexcept::q_rogueaccess(this->_hash, hash), volatile_cast<std::int32_t*>(&_value));
				}

				return _value;
			}

			__compelled_inline void __regcall set( imut std::int32_t value) nex {

				auto hash = qhash::qhash_cpu(imut_cast<std::int32_t*>(&value), sizeof(value));

				this->_hash = std::move(hash);

				_value = value;
			}

			__compelled_inline imut std::int32_t* __stackcall get_raw_memory_address() imut nex {
				return volatile_cast<std::int32_t*>(&_value);
			}

#pragma endregion

#pragma region Operators

			__compelled_inline qh_int32 __regcall operator+(imut std::int32_t value) imut nex {
				return qh_int32(get() + value);
			};

			__compelled_inline qh_int32 __regcall operator-(imut std::int32_t value) imut nex {
				return qh_int32(get() - value);
			}

			__compelled_inline qh_int32 __regcall operator/(imut std::int32_t value) imut nex {
				return qh_int32(get() / value);
			}

			__compelled_inline qh_int32 __regcall operator*(imut std::int32_t value) imut nex {
				return qh_int32(get() * value);
			}

			__compelled_inline qh_int32 __regcall operator&(imut std::int32_t value) imut nex {
				return qh_int32(get() & value);
			}

			__compelled_inline qh_int32 __regcall operator|(imut std::int32_t value) imut nex {
				return qh_int32(get() | value);
			}

			__compelled_inline qh_int32 __regcall operator%(imut std::int32_t value) imut nex {
				return qh_int32(get() % value);
			}

			__compelled_inline qh_int32 __regcall operator^(imut std::int32_t value) imut nex {
				return qh_int32(get() ^ value);
			}

			__compelled_inline qh_int32 __regcall operator<<(imut std::int32_t value) imut nex {
				return qh_int32(get() << value);
			}

			__compelled_inline qh_int32 __regcall operator>>(imut std::int32_t value) imut nex {
				return qh_int32(get() >> value);
			}

			__compelled_inline qh_int32& __regcall operator+=(imut std::int32_t value) nex {
				set(static_cast<int>(get() + value));
				return *this;
			}

			__compelled_inline qh_int32& __regcall operator-=(imut std::int32_t value) nex {
				set(static_cast<int>(get() - value));
				return *this;
			}

			__compelled_inline qh_int32& __regcall operator++() nex {
				operator+=(1i8);
				return *this;
			}

			__compelled_inline qh_int32& __regcall operator--() nex {
				operator-=(1i8);
				return *this;
			}

			__compelled_inline qh_int32& __regcall operator*=(imut std::int32_t value) nex {
				set(static_cast<std::int32_t>(get() * value));
				return *this;
			}

			__compelled_inline qh_int32& __regcall operator/=(imut std::int32_t value) nex {
				set(static_cast<std::int32_t>(get() / value));
				return *this;
			}

			__compelled_inline qh_int32& __regcall operator%=(imut std::int32_t value) nex {
				set(static_cast<std::int32_t>(get() % value));
				return *this;
			}

			__compelled_inline qh_int32& __regcall operator^=(imut std::int32_t value) nex {
				set(static_cast<std::int32_t>(get() ^ value));
				return *this;
			}

			__compelled_inline qh_int32& __regcall operator&=(imut std::int32_t value) nex {
				set(static_cast<std::int32_t>(get() & value));
				return *this;
			}

			__compelled_inline qh_int32& __regcall operator|=(imut std::int32_t value) nex {
				set(static_cast<std::int32_t>(get() | value));
				return *this;
			}

			__compelled_inline qh_int32& __regcall operator<<=(imut std::int32_t value) nex {
				set(static_cast<std::int32_t>(get() << value));
				return *this;
			}

			__compelled_inline qh_int32& __regcall operator>>=(imut std::int32_t value) nex {
				set(static_cast<std::int32_t>(get() >> value));
				return *this;
			}

			__compelled_inline qh_int32& __regcall operator=(imut std::int32_t value) nex {
				set(value);
				return *this;
			}

			__compelled_inline __stackcall operator std::int32_t() imut nex {
				return get();
			}

#pragma endregion
		};

		class qh_uint32 {

		private:

#pragma region Globals

			mut noregister std::uint32_t _value;

			mut std::uintptr_t _hash;

			mut bool is_polyc_alteration;

#pragma endregion

		public:

#pragma region Ctor / Dtor

			__optimized_ctor qh_uint32(std::uint32_t value = 0) nex {

				if (!is_init)
					init_hash_t();

				set(value);
			}

			__optimized_dtor ~qh_uint32() nex {
			
				RtlZeroMemory(volatile_cast<std::uint32_t*>(&this->_value), sizeof(std::uint32_t));
				RtlZeroMemory(&this->_hash, sizeof(std::uintptr_t));
				RtlZeroMemory(&this->is_polyc_alteration, sizeof(bool));
			}

#pragma endregion

#pragma region Accessors

			__compelled_inline std::uint32_t* __stackcall open_data_ptr() imut nex {

				is_polyc_alteration = true;

				return volatile_cast<std::uint32_t*>(&_value);
			}

			__compelled_inline imut bool __stackcall close_data_ptr() imut nex {

				auto hash = qhash::qhash_cpu(volatile_cast<std::uint32_t*>(&_value), sizeof(_value));

				this->_hash = std::move(hash);

				is_polyc_alteration = false;

				return true;
			}

			__compelled_inline std::uint32_t __stackcall get() imut nex {

				if (!is_polyc_alteration) {

					auto hash = qhash::qhash_cpu(volatile_cast<std::uint32_t*>(&_value), sizeof(_value));

					if (hash != _hash)
						violation_callback(qengine::qexcept::q_rogueaccess(this->_hash, hash), volatile_cast<std::uint32_t*>(&_value));
				}

				return _value;
			}

			__compelled_inline void __regcall set( imut std::uint32_t value) nex {

				auto hash = qhash::qhash_cpu(imut_cast<std::uint32_t*>(&value), sizeof(value));

				this->_hash = std::move(hash);

				_value = value;
			}

			__compelled_inline imut std::uint32_t* __stackcall get_raw_memory_address() imut nex {
				return volatile_cast<std::uint32_t*>(&_value);
			}

#pragma endregion

#pragma region Operators

			__compelled_inline qh_uint32 __regcall operator+(imut std::uint32_t value) imut nex {
				return qh_uint32(get() + value);
			};

			__compelled_inline qh_uint32 __regcall operator-(imut std::uint32_t value) imut nex {
				return qh_uint32(get() - value);
			}

			__compelled_inline qh_uint32 __regcall operator/(imut std::uint32_t value) imut nex {
				return qh_uint32(get() / value);
			}

			__compelled_inline qh_uint32 __regcall operator*(imut std::uint32_t value) imut nex {
				return qh_uint32(get() * value);
			}

			__compelled_inline qh_uint32 __regcall operator&(imut std::uint32_t value) imut nex {
				return qh_uint32(get() & value);
			}

			__compelled_inline qh_uint32 __regcall operator|(imut std::uint32_t value) imut nex {
				return qh_uint32(get() | value);
			}

			__compelled_inline qh_uint32 __regcall operator%(imut std::uint32_t value) imut nex {
				return qh_uint32(get() % value);
			}

			__compelled_inline qh_uint32 __regcall operator^(imut std::uint32_t value) imut nex {
				return qh_uint32(get() ^ value);
			}

			__compelled_inline qh_uint32 __regcall operator<<(imut std::uint32_t value) imut nex {
				return qh_uint32(get() << value);
			}

			__compelled_inline qh_uint32 __regcall operator>>(imut std::uint32_t value) imut nex {
				return qh_uint32(get() >> value);
			}

			__compelled_inline qh_uint32& __regcall operator+=(imut std::uint32_t value) nex {
				set(static_cast<std::uint32_t>(get() + value));
				return *this;
			}

			__compelled_inline qh_uint32& __regcall operator-=(imut std::uint32_t value) nex {
				set(static_cast<std::uint32_t>(get() - value));
				return *this;
			}

			__compelled_inline qh_uint32& __regcall operator++() nex {
				operator+=(1i8);
				return *this;
			}

			__compelled_inline qh_uint32& __regcall operator--() nex {
				operator-=(1i8);
				return *this;
			}

			__compelled_inline qh_uint32& __regcall operator*=(imut std::uint32_t value) nex {
				set(static_cast<std::uint32_t>(get() * value));
				return *this;
			}

			__compelled_inline qh_uint32& __regcall operator/=(imut std::uint32_t value) nex {
				set(static_cast<std::uint32_t>(get() / value));
				return *this;
			}

			__compelled_inline qh_uint32& __regcall operator%=(imut std::uint32_t value) {
				set(static_cast<std::uint32_t>(get() % value));
				return *this;
			}

			__compelled_inline qh_uint32& __regcall operator^=(imut std::uint32_t value) nex {
				set(static_cast<std::uint32_t>(get() ^ value));
				return *this;
			}

			__compelled_inline qh_uint32& __regcall operator&=(imut std::uint32_t value) nex {
				set(static_cast<std::uint32_t>(get() & value));
				return *this;
			}

			__compelled_inline qh_uint32& __regcall operator|=(imut std::uint32_t value) nex {
				set(static_cast<std::uint32_t>(get() | value));
				return *this;
			}

			__compelled_inline qh_uint32& __regcall operator<<=(imut std::uint32_t value) nex {
				set(static_cast<std::uint32_t>(get() << value));
				return *this;
			}

			__compelled_inline qh_uint32& __regcall operator>>=(imut std::uint32_t value) nex {
				set(static_cast<std::uint32_t>(get() >> value));
				return *this;
			}

			__compelled_inline qh_uint32& __regcall operator=(imut std::uint32_t value) nex {
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

		class qh_int64 {

		private:

#pragma region Globals

			mut noregister std::int64_t _value;

			mut std::uintptr_t _hash;

			mut bool is_polyc_alteration;

#pragma endregion

		public:

#pragma region Ctor / Dtor

			__optimized_ctor qh_int64(std::int64_t value = 0) nex {

				if (!is_init)
					init_hash_t();

				set(value);
			}

			__optimized_dtor ~qh_int64() nex {
			
				RtlZeroMemory(volatile_cast<std::int64_t*>(&this->_value), sizeof(std::int64_t));
				RtlZeroMemory(&this->_hash, sizeof(std::uintptr_t));
				RtlZeroMemory(&this->is_polyc_alteration, sizeof(bool));
			}

#pragma endregion

#pragma region Accessors

			__compelled_inline std::int64_t* __stackcall open_data_ptr() imut nex {

				is_polyc_alteration = true;

				return volatile_cast<std::int64_t*>(&_value);
			}

			__compelled_inline imut bool __stackcall close_data_ptr() imut nex {

				auto hash = qhash::qhash_cpu(volatile_cast<std::int64_t*>(&_value), sizeof(_value));

				this->_hash = std::move(hash);

				is_polyc_alteration = false;

				return true;
			}

			__compelled_inline std::int64_t __stackcall get() imut nex {

				if (!is_polyc_alteration) {

					auto hash = qhash::qhash_cpu(volatile_cast<std::int64_t*>(&_value), sizeof(_value));

					if (hash != _hash)
						violation_callback(qengine::qexcept::q_rogueaccess(this->_hash, hash), volatile_cast<std::int64_t*>(&_value));
				}

				return _value;
			}

			__compelled_inline void __regcall set( imut std::int64_t value) nex {

				auto hash = qhash::qhash_cpu(imut_cast<std::int64_t*>(&value), sizeof(value));

				this->_hash = std::move(hash);

				_value = value;
			}

			__compelled_inline imut std::int64_t* __stackcall get_raw_memory_address() imut nex {
				return volatile_cast<std::int64_t*>(&_value);
			}

#pragma endregion

#pragma region Operators

			__compelled_inline qh_int64 __regcall operator+(imut std::int64_t value) imut nex {
				return qh_int64(get() + value);
			};

			__compelled_inline qh_int64 __regcall operator-(imut std::int64_t value) imut nex {
				return qh_int64(get() - value);
			}

			__compelled_inline qh_int64 __regcall operator/(imut std::int64_t value) imut nex {
				return qh_int64(get() / value);
			}

			__compelled_inline qh_int64 __regcall operator*(imut std::int64_t value) imut nex {
				return qh_int64(get() * value);
			}

			__compelled_inline qh_int64 __regcall operator&(imut std::int64_t value) imut nex {
				return qh_int64(get() & value);
			}

			__compelled_inline qh_int64 __regcall operator|(imut std::int64_t value) imut nex {
				return qh_int64(get() | value);
			}

			__compelled_inline qh_int64 __regcall operator%(imut std::int64_t value) imut nex {
				return qh_int64(get() % value);
			}

			__compelled_inline qh_int64 __regcall operator^(imut std::int64_t value) imut nex {
				return qh_int64(get() ^ value);
			}

			__compelled_inline qh_int64 __regcall operator<<(imut std::int64_t value) imut nex {
				return qh_int64(get() << value);
			}

			__compelled_inline qh_int64 __regcall operator>>(imut std::int64_t value) imut nex {
				return qh_int64(get() >> value);
			}

			__compelled_inline qh_int64& __regcall operator+=(imut std::int64_t value) nex {
				set(static_cast<int>(get() + value));
				return *this;
			}

			__compelled_inline qh_int64& __regcall operator-=(imut std::int64_t value) nex {
				set(static_cast<int>(get() - value));
				return *this;
			}

			__compelled_inline qh_int64& __regcall operator++() nex {
				operator+=(1i8);
				return *this;
			}

			__compelled_inline qh_int64& __regcall operator--() nex {
				operator-=(1i8);
				return *this;
			}

			__compelled_inline qh_int64& __regcall operator*=(imut std::int64_t value) nex {
				set(static_cast<std::int64_t>(get() * value));
				return *this;
			}

			__compelled_inline qh_int64& __regcall operator/=(imut std::int64_t value) nex {
				set(static_cast<std::int64_t>(get() / value));
				return *this;
			}

			__compelled_inline qh_int64& __regcall operator%=(imut std::int64_t value) nex {
				set(static_cast<std::int64_t>(get() % value));
				return *this;
			}

			__compelled_inline qh_int64& __regcall operator^=(imut std::int64_t value) nex {
				set(static_cast<std::int64_t>(get() ^ value));
				return *this;
			}

			__compelled_inline qh_int64& __regcall operator&=(imut std::int64_t value) nex {
				set(static_cast<std::int64_t>(get() & value));
				return *this;
			}

			__compelled_inline qh_int64& __regcall operator|=(imut std::int64_t value) nex {
				set(static_cast<std::int64_t>(get() | value));
				return *this;
			}

			__compelled_inline qh_int64& __regcall operator<<=(imut std::int64_t value) nex {
				set(static_cast<std::int64_t>(get() << value));
				return *this;
			}

			__compelled_inline qh_int64& __regcall operator>>=(imut std::int64_t value) nex {
				set(static_cast<std::int64_t>(get() >> value));
				return *this;
			}

			__compelled_inline qh_int64& __regcall operator=(imut std::int64_t value) nex {
				set(value);
				return *this;
			}

			__compelled_inline __stackcall operator std::int64_t() imut nex {
				return get();
			}


#pragma endregion
		};

		class qh_uint64 {

		private:

#pragma region Globals

			mut noregister std::uint64_t _value;

			mut std::uintptr_t _hash;

			mut bool is_polyc_alteration;

#pragma endregion

		public:

#pragma region Ctor / Dtor

			__optimized_ctor qh_uint64(std::uint64_t value = 0) nex {

				if (!is_init)
					init_hash_t();

				set(value);
			}

			__optimized_dtor ~qh_uint64() nex {
			
				RtlZeroMemory(volatile_cast<std::uint64_t*>(&this->_value), sizeof(std::uint64_t));
				RtlZeroMemory(&this->_hash, sizeof(std::uintptr_t));
				RtlZeroMemory(&this->is_polyc_alteration, sizeof(bool));
			}

#pragma endregion

#pragma region Accessors

			__compelled_inline std::uint64_t* __stackcall open_data_ptr() imut nex {

				is_polyc_alteration = true;

				return volatile_cast<std::uint64_t*>(&_value);
			}

			__compelled_inline imut bool __stackcall close_data_ptr() imut nex {

				auto hash = qhash::qhash_cpu(volatile_cast<std::uint64_t*>(&_value), sizeof(_value));

				this->_hash = std::move(hash);

				is_polyc_alteration = false;

				return true;
			}

			__compelled_inline std::uint64_t __stackcall get() imut nex {

				if (!is_polyc_alteration) {

					auto hash = qhash::qhash_cpu(volatile_cast<std::uint64_t*>(&_value), sizeof(_value));

					if (hash != _hash)
						violation_callback(qengine::qexcept::q_rogueaccess(this->_hash, hash), volatile_cast<std::uint64_t*>(&_value));
				}

				return _value;
			}
			__compelled_inline void __regcall set( imut std::uint64_t value) nex {

				auto hash = qhash::qhash_cpu(imut_cast<std::uint64_t*>(&value), sizeof(value));

				this->_hash = std::move(hash);

				_value = value;
			}

			__compelled_inline imut std::uint64_t* __stackcall get_raw_memory_address() imut nex {
				return volatile_cast<std::uint64_t*>(&_value);
			}

#pragma endregion

#pragma region Operators

			__compelled_inline qh_uint64 __regcall operator+(imut std::uint64_t value) imut nex {
				return qh_uint64(get() + value);
			};

			__compelled_inline qh_uint64 __regcall operator-(imut std::uint64_t value) imut nex {
				return qh_uint64(get() - value);
			}

			__compelled_inline qh_uint64 __regcall operator/(imut std::uint64_t value) imut nex {
				return qh_uint64(get() / value);
			}

			__compelled_inline qh_uint64 __regcall operator*(imut std::uint64_t value) imut nex {
				return qh_uint64(get() * value);
			}

			__compelled_inline qh_uint64 __regcall operator&(imut std::uint64_t value) imut nex {
				return qh_uint64(get() & value);
			}

			__compelled_inline qh_uint64 __regcall operator|(imut std::uint64_t value) imut nex {
				return qh_uint64(get() | value);
			}

			__compelled_inline qh_uint64 __regcall operator%(imut std::uint64_t value) imut nex {
				return qh_uint64(get() % value);
			}

			__compelled_inline qh_uint64 __regcall operator^(imut std::uint64_t value) imut nex {
				return qh_uint64(get() ^ value);
			}

			__compelled_inline qh_uint64 __regcall operator<<(imut std::uint64_t value) imut nex {
				return qh_uint64(get() << value);
			}

			__compelled_inline qh_uint64 __regcall operator>>(imut std::uint64_t value) imut nex {
				return qh_uint64(get() >> value);
			}

			__compelled_inline qh_uint64& __regcall operator+=(imut std::uint64_t value) nex {
				set(static_cast<std::uint64_t>(get() + value));
				return *this;
			}

			__compelled_inline qh_uint64& __regcall operator-=(imut std::uint64_t value) nex {
				set(static_cast<std::uint64_t>(get() - value));
				return *this;
			}

			__compelled_inline qh_uint64& __regcall operator++() nex {
				operator+=(1i8);
				return *this;
			}

			__compelled_inline qh_uint64& __regcall operator--() nex {
				operator-=(1i8);
				return *this;
			}

			__compelled_inline qh_uint64& __regcall operator*=(imut std::uint64_t value) nex {
				set(static_cast<std::uint64_t>(get() * value));
				return *this;
			}

			__compelled_inline qh_uint64& __regcall operator/=(imut std::uint64_t value) nex {
				set(static_cast<std::uint64_t>(get() / value));
				return *this;
			}

			__compelled_inline qh_uint64& __regcall operator%=(imut std::uint64_t value) nex {
				set(static_cast<std::uint64_t>(get() % value));
				return *this;
			}

			__compelled_inline qh_uint64& __regcall operator^=(imut std::uint64_t value) nex {
				set(static_cast<std::uint64_t>(get() ^ value));
				return *this;
			}

			__compelled_inline qh_uint64& __regcall operator&=(imut std::uint64_t value) nex {
				set(static_cast<std::uint64_t>(get() & value));
				return *this;
			}

			__compelled_inline qh_uint64& __regcall operator|=(imut std::uint64_t value) nex {
				set(static_cast<std::uint64_t>(get() | value));
				return *this;
			}

			__compelled_inline qh_uint64& __regcall operator<<=(imut std::uint64_t value) nex {
				set(static_cast<std::uint64_t>(get() << value));
				return *this;
			}

			__compelled_inline qh_uint64& __regcall operator>>=(imut std::uint64_t value) nex {
				set(static_cast<std::uint64_t>(get() >> value));
				return *this;
			}

			__compelled_inline qh_uint64& __regcall operator=(imut std::uint64_t value) nex {
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

		class qh_float {

		private:

#pragma region Globals 

			mut noregister float _value;

			mut std::uintptr_t _hash;

			mut bool is_polyc_alteration;

#pragma endregion

		public:

#pragma region Ctor / Dtor

			__compelled_inline __fpcall qh_float(imut float value = 0.0f) nex {

				if (!is_init)
					init_hash_t();

				set(value);
			}

			__optimized_dtor ~qh_float() nex {
			
				RtlZeroMemory(volatile_cast<float*>(&this->_value), sizeof(float));
				RtlZeroMemory(&this->_hash, sizeof(std::uintptr_t));
				RtlZeroMemory(&this->is_polyc_alteration, sizeof(bool));
			}

#pragma endregion

#pragma region Accessors

			__compelled_inline float* __stackcall open_data_ptr() imut nex {

				is_polyc_alteration = true;

				return volatile_cast<float*>(&_value);
			}

			__compelled_inline imut bool __stackcall close_data_ptr() imut nex {

				auto hash = qhash::qhash_cpu(volatile_cast<float*>(&_value), sizeof(_value));

				this->_hash = std::move(hash);

				is_polyc_alteration = false;

				return true;
			}

			__compelled_inline float __stackcall get() imut nex {

				if (!is_polyc_alteration) {

					auto hash = qhash::qhash_cpu(volatile_cast<float*>(&_value), sizeof(_value));

					if (hash != _hash)
						violation_callback(qengine::qexcept::q_rogueaccess(this->_hash, hash), volatile_cast<float*>(&_value));
				}

				return _value;
			}

			__compelled_inline void __regcall set( imut float value ) nex {

				auto hash = qhash::qhash_cpu(imut_cast<float*>(&value), sizeof(value));

				this->_hash = std::move(hash);

				_value = value;
			}

			__compelled_inline imut float* __stackcall get_raw_memory_address() imut nex {
				return volatile_cast<float*>(&_value);
			}

#pragma endregion

#pragma region Operators

			__compelled_inline qh_float __fpcall operator+(imut float value) imut nex {
				return qh_float(get() + value);
			};

			__compelled_inline qh_float __fpcall operator-(imut float value) imut nex {
				return qh_float(get() - value);
			}

			__compelled_inline qh_float __fpcall operator/(imut float value) imut nex {
				return qh_float(get() / value);
			}

			__compelled_inline qh_float __fpcall operator*(imut float value) imut nex {
				return qh_float(get() * value);
			}

			__compelled_inline qh_float& __fpcall operator+=(imut float value) nex {
				set(static_cast<float>(get() + value));
				return *this;
			}

			__compelled_inline qh_float& __fpcall operator-=(imut float value) nex {
				set(static_cast<float>(get() - value));
				return *this;
			}

			__compelled_inline qh_float& __stackcall operator++() nex {
				operator+=(1.f);
				return *this;
			}

			__compelled_inline qh_float& __stackcall operator--() nex {
				operator-=(1.f);
				return *this;
			}

			__compelled_inline qh_float& __fpcall operator*=(imut float value) nex {
				set(static_cast<float>(get() * value));
				return *this;
			}

			__compelled_inline qh_float& __fpcall operator/=(imut float value) nex {
				set(static_cast<float>(get() / value));
				return *this;
			}

			__compelled_inline qh_float& __fpcall operator=(imut float value) nex {
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

		class qh_double {

		private:

#pragma region Globals

			mut noregister double _value;

			mut std::uintptr_t _hash;

			mut bool is_polyc_alteration;

#pragma endregion

		public:

#pragma region Ctor / Dtor

			__compelled_inline __fpcall qh_double(imut double value = static_cast<double>(0.0f)) nex {

				if (!is_init)
					init_hash_t();

				set(value);
			}

			__optimized_dtor ~qh_double() nex {
			
				RtlZeroMemory(volatile_cast<double*>(&this->_value), sizeof(double));
				RtlZeroMemory(&this->_hash, sizeof(std::uintptr_t));
				RtlZeroMemory(&this->is_polyc_alteration, sizeof(bool));
			}

#pragma endregion

#pragma region Accessors

			__compelled_inline double* __stackcall open_data_ptr() imut nex {

				is_polyc_alteration = true;

				return volatile_cast<double*>(&_value);
			}

			__compelled_inline imut bool __stackcall close_data_ptr() imut nex {

				auto hash = qhash::qhash_cpu(volatile_cast<double*>(&_value), sizeof(double));

				this->_hash = std::move(hash);

				is_polyc_alteration = false;

				return true;
			}

			__compelled_inline double __stackcall get() imut nex {

				if (!is_polyc_alteration) {

					auto hash = qhash::qhash_cpu(volatile_cast<double*>(&_value), sizeof(double));

					if (hash != _hash)
						violation_callback(qengine::qexcept::q_rogueaccess(this->_hash, hash), volatile_cast<double*>(&_value));
				}

				return _value;
			}

			__compelled_inline void __fpcall set( imut double value) nex {

				auto hash = qhash::qhash_cpu(imut_cast<double*>(&value), sizeof(value));

				this->_hash = std::move(hash);

				_value = value;
			}

			__compelled_inline imut double* get_raw_memory_address() imut nex {
				return volatile_cast<double*>(&_value);
			}

#pragma endregion

#pragma region Operators

			__compelled_inline qh_double __fpcall operator+(imut double value) imut nex {
				return qh_double(get() + value);
			};

			__compelled_inline qh_double __fpcall operator-(imut double value) imut nex {
				return qh_double(get() - value);
			}

			__compelled_inline qh_double __fpcall operator/(imut double value) imut nex {
				return qh_double(get() / value);
			}

			__compelled_inline qh_double __fpcall operator*(imut double value) imut nex {
				return qh_double(get() * value);
			}

			__compelled_inline qh_double& __fpcall operator+=(imut double value) nex {
				set(static_cast<double>(get() + value));
				return *this;
			}

			__compelled_inline qh_double& __fpcall operator-=(imut double value) nex {
				set(get() - value);
				return *this;
			}

			__compelled_inline qh_double& __stackcall operator++() nex {
				operator+=(1.f);
				return *this;
			}

			__compelled_inline qh_double& __stackcall operator--() nex {
				operator-=(1.f);
				return *this;
			}

			__compelled_inline qh_double& __fpcall operator*=(imut double value) nex {
				set(get() * value);
				return *this;
			}

			__compelled_inline qh_double& __fpcall operator/=(imut double value) nex {
				set(get() / value);
				return *this;
			}

			__compelled_inline qh_double& __fpcall operator=(imut double value) nex {
				set(value);
				return *this;
			}

			__compelled_inline __stackcall operator double() imut nex {
				return get();
			}

#pragma endregion
		};

		class qh_longdouble {

		private:

#pragma region Globals

			mut noregister long double _value;

			mut std::uintptr_t _hash;

			mut bool is_polyc_alteration;

#pragma endregion

		public:

#pragma region Ctor / Dtor

			__compelled_inline __fpcall qh_longdouble(imut long double value = static_cast<long double>(0.0f)) nex {

				if (!is_init)
					init_hash_t();

				set(value);
			}

			__optimized_dtor ~qh_longdouble() nex {
			
				RtlZeroMemory(volatile_cast<long double*>(&this->_value), sizeof(long double));
				RtlZeroMemory(&this->_hash, sizeof(std::uintptr_t));
				RtlZeroMemory(&this->is_polyc_alteration, sizeof(bool));
			}

#pragma endregion

#pragma region Accessors

			__compelled_inline long double* __stackcall open_data_ptr() imut nex {

				is_polyc_alteration = true;

				return volatile_cast<long double*>(&_value);
			}

			__compelled_inline imut bool __stackcall close_data_ptr() imut nex {

				auto hash = qhash::qhash_cpu(volatile_cast<long double*>(&_value), sizeof(_value));

				this->_hash = std::move(hash);

				is_polyc_alteration = false;

				return true;
			}

			__compelled_inline long double __stackcall get() imut nex {

				if (!is_polyc_alteration) {

					auto hash = qhash::qhash_cpu(volatile_cast<long double*>(&_value), sizeof(long double));

					if (hash != _hash)
						violation_callback(qengine::qexcept::q_rogueaccess(this->_hash, hash), volatile_cast<long double*>(&_value));
				}

				return _value;
			}

			__compelled_inline void __fpcall set( imut long double value) nex {

				auto hash = qhash::qhash_cpu(imut_cast<long double*>(&value), sizeof(long double));

				this->_hash = std::move(hash);

				_value = value;
			}

			__compelled_inline imut long double* get_raw_memory_address() imut nex {
				return volatile_cast<long double*>(&_value);
			}

#pragma endregion

#pragma region Operators

			__compelled_inline qh_longdouble __fpcall operator+(imut long double value) imut nex {
				return qh_longdouble(get() + value);
			};

			__compelled_inline qh_longdouble __fpcall operator-(imut long double value) imut nex {
				return qh_longdouble(get() - value);
			}

			__compelled_inline qh_longdouble __fpcall operator/(imut long double value) imut nex {
				return qh_longdouble(get() / value);
			}

			__compelled_inline qh_longdouble __fpcall operator*(imut long double value) imut nex {
				return qh_longdouble(get() * value);
			}

			__compelled_inline qh_longdouble& __fpcall operator+=(imut long double value) nex {
				set(static_cast<double>(get() + value));
				return *this;
			}

			__compelled_inline qh_longdouble& __fpcall operator-=(imut long double value) nex {
				set(get() - value);
				return *this;
			}

			__compelled_inline qh_longdouble& __stackcall operator++() nex {
				operator+=(1.f);
				return *this;
			}

			__compelled_inline qh_longdouble& __stackcall operator--() nex {
				operator-=(1.f);
				return *this;
			}

			__compelled_inline qh_longdouble& __fpcall operator*=(imut long double value) nex {
				set(static_cast<double>(get() * value));
				return *this;
			}

			__compelled_inline qh_longdouble& __fpcall operator/=(imut long double value) nex {
				set(get() / value);
				return *this;
			}

			__compelled_inline qh_longdouble& __fpcall operator=(imut long double value) nex {
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

#pragma region Extended Types

#pragma region SSE

#ifdef __SSE__

		class qh_m128 {

		private:

#pragma region Globals

			mut __m128 _value;

			mut std::uintptr_t _hash;

			mut bool is_polyc_alteration;

#pragma endregion

		public:

#pragma region Ctor / Dtor

			__compelled_inline __fpcall qh_m128(imut __m128 value = _mm_setzero_ps()) nex {

				if (!is_init)
					init_hash_t();

				set(value);
			}

			__optimized_dtor ~qh_m128() nex {
			
				RtlZeroMemory(volatile_cast<__m128*>(&this->_value), sizeof(__m128));
				RtlZeroMemory(&this->_hash, sizeof(std::uintptr_t));
				RtlZeroMemory(&this->is_polyc_alteration, sizeof(bool));
			}

#pragma endregion

#pragma region Accessors

			__compelled_inline decltype(_value)* __stackcall open_data_ptr() imut nex {

				is_polyc_alteration = true;

				return &_value;
			}

			__compelled_inline imut bool __stackcall close_data_ptr() imut nex {

				auto hash = qhash::qhash_cpu(&_value, sizeof(_value));

				this->_hash = std::move(hash);

				is_polyc_alteration = false;

				return true;
			}

			__compelled_inline __m128 __stackcall get() imut nex {

				if (!is_polyc_alteration) {

					auto hash = qhash::qhash_cpu(reinterpret_cast<c_void>(&_value), sizeof(_value));

					if (hash != _hash)
						violation_callback(qengine::qexcept::q_rogueaccess(this->_hash, hash), reinterpret_cast<c_void>(&_value));
				}

				return _value;
			}

			__compelled_inline void __fpcall set( imut __m128 value) nex {

				auto hash = qhash::qhash_cpu(imut_cast<__m128*>(&value), sizeof(value));

				this->_hash = std::move(hash);

				_value = value;
			}

			__compelled_inline imut decltype(_value)* __stackcall get_raw_memory_address() imut nex {
				return &_value;
			}

#pragma endregion

#pragma region Operators

	#ifdef __clang__

			__compelled_inline qh_m128 __fpcall operator+(imut __m128 value) imut nex {
				return qh_m128(get() + value);
			};

			__compelled_inline qh_m128 __fpcall operator-(imut __m128 value) imut nex {
				return qh_m128(get() - value);
			}

			__compelled_inline qh_m128 __fpcall operator/(imut __m128 value) imut nex {
				return qh_m128(get() / value);
			}

			__compelled_inline qh_m128 __fpcall operator*(imut __m128 value) imut nex {
				return qh_m128(get() * value);
			}

			__compelled_inline qh_m128& __fpcall operator+=(imut __m128 value) nex {
				set(get() + value);
				return *this;
			}

			__compelled_inline qh_m128& __fpcall operator-=(imut __m128 value) nex {
				set(get() - value);
				return *this;
			}

			__compelled_inline qh_m128& __fpcall operator*=(imut __m128 value) nex {
				set(get() * value);
				return *this;
			}

			__compelled_inline qh_m128& __fpcall operator/=(imut __m128 value) nex {
				set(get() / value);
				return *this;
			}

	#endif

			__compelled_inline qh_m128& __fpcall operator=(imut __m128 value) nex {
				set(value);
				return *this;
			}

			__compelled_inline __fpcall operator __m128() imut nex {
				return get();
			}

#pragma endregion

		};

	#ifdef __SSE2__

		class qh_m128i {

		private:

#pragma region Globals

			mut __m128i _value;

			mut std::uintptr_t _hash;

			mut bool is_polyc_alteration;

#pragma endregion

		public:

#pragma region Ctor / Dtor

			__compelled_inline __fpcall qh_m128i(imut __m128i value = _mm_setzero_si128()) {

				if (!is_init)
					init_hash_t();

				set(value);
			}

			__optimized_dtor ~qh_m128i() nex {
			
				RtlZeroMemory(volatile_cast<__m128i*>(&this->_value), sizeof(__m128i));
				RtlZeroMemory(&this->_hash, sizeof(std::uintptr_t));
				RtlZeroMemory(&this->is_polyc_alteration, sizeof(bool));
			}

#pragma endregion

#pragma region Accessors

			__compelled_inline decltype(_value)* __stackcall open_data_ptr() imut nex {

				is_polyc_alteration = true;

				return &_value;
			}

			__compelled_inline imut bool __stackcall close_data_ptr() imut nex {

				auto hash = qhash::qhash_cpu(&_value, sizeof(_value));

				this->_hash = std::move(hash);

				is_polyc_alteration = false;

				return true;
			}

			__compelled_inline __m128i __stackcall get() imut nex {

				if (!is_polyc_alteration) {

					auto hash = qhash::qhash_cpu(reinterpret_cast<c_void>(&_value), sizeof(_value));

					if (hash != _hash)
						violation_callback(qengine::qexcept::q_rogueaccess(this->_hash, hash), reinterpret_cast<c_void>(&_value));
				}

				return _value;
			}

			__compelled_inline void __fpcall set( imut __m128i value) {

				auto hash = qhash::qhash_cpu(imut_cast<__m128i*>(&value), sizeof(value));

				this->_hash = std::move(hash);

				_value = value;
			}

			__compelled_inline imut decltype(_value)* __stackcall get_raw_memory_address() imut nex {
				return &_value;
			}

#pragma endregion

#pragma region Operators

	#ifdef __clang__

			__compelled_inline qh_m128i __fpcall operator+(imut __m128i value) imut {
				return qh_m128i(get() + value);
			};

			__compelled_inline qh_m128i __fpcall operator-(imut __m128i value) imut {
				return qh_m128i(get() - value);
			}

			__compelled_inline qh_m128i __fpcall operator/(imut __m128i value) imut {
				return qh_m128i(get() / value);
			}

			__compelled_inline qh_m128i __fpcall operator*(imut __m128i value) imut {
				return qh_m128i(get() * value);
			}

			__compelled_inline qh_m128i& __fpcall operator+=(imut __m128i value) {
				set(get() + value);
				return *this;
			}

			__compelled_inline qh_m128i& __fpcall operator-=(imut __m128i value) {
				set(get() - value);
				return *this;
			}

			__compelled_inline qh_m128i& __fpcall operator*=(imut __m128i value) {
				set(get() * value);
				return *this;
			}

			__compelled_inline qh_m128i& __fpcall operator/=(imut __m128i value) {
				set(get() / value);
				return *this;
			}

	#endif

			__compelled_inline qh_m128i& __fpcall operator=(imut __m128i value) nex {
				set(value);
				return *this;
			}

			__compelled_inline __stackcall operator __m128i() imut nex {
				return get();
			}

#pragma endregion
		};

		class qh_m128d {

		private:

#pragma region Globals

			mut __m128d _value;

			mut std::uintptr_t _hash;

			mut bool is_polyc_alteration;

#pragma endregion

		public:

#pragma region Ctor / Dtor

			__compelled_inline __fpcall qh_m128d(imut __m128d value = _mm_setzero_pd()) nex {

				if (!is_init)
					init_hash_t();

				set(value);
			}

			__optimized_dtor ~qh_m128d() nex {
			
				RtlZeroMemory(volatile_cast<__m128d*>(&this->_value), sizeof(__m128d));
				RtlZeroMemory(&this->_hash, sizeof(std::uintptr_t));
				RtlZeroMemory(&this->is_polyc_alteration, sizeof(bool));
			}

#pragma endregion

#pragma region Accessors

			__compelled_inline decltype(_value)* __stackcall open_data_ptr() imut nex {

				is_polyc_alteration = true;

				return &_value;
			}

			__compelled_inline imut bool __stackcall close_data_ptr() imut nex {

				auto hash = qhash::qhash_cpu(&_value, sizeof(_value));

				this->_hash = std::move(hash);

				is_polyc_alteration = false;

				return true;
			}

			__compelled_inline __m128d __stackcall get() imut nex {

				if (!is_polyc_alteration) {

					auto hash = qhash::qhash_cpu(reinterpret_cast<c_void>(&_value), sizeof(_value));

					if (hash != _hash)
						violation_callback(qengine::qexcept::q_rogueaccess(this->_hash, hash), reinterpret_cast<c_void>(&_value));
				}

				return _value;
			}

			__compelled_inline void __fpcall set( imut __m128d value) nex {

				auto hash = qhash::qhash_cpu(imut_cast<__m128d*>(&value), sizeof(value));

				this->_hash = std::move(hash);

				_value = value;
			}

			__compelled_inline imut decltype(_value)* __stackcall get_raw_memory_address() imut nex {
				return &_value;
			}

#pragma endregion

#pragma region Operators

	#ifdef __clang__

			__compelled_inline qh_m128d __fpcall operator+(imut __m128d value) imut nex {
				return qh_m128d(get() + value);
			};

			__compelled_inline qh_m128d __fpcall operator-(imut __m128d value) imut nex {
				return qh_m128d(get() - value);
			}

			__compelled_inline qh_m128d __fpcall operator/(imut __m128d value) imut nex {
				return qh_m128d(get() / value);
			}

			__compelled_inline qh_m128d __fpcall operator*(imut __m128d value) imut nex {
				return qh_m128d(get() * value);
			}

			__compelled_inline qh_m128d& __fpcall operator+=(imut __m128d value) nex {
				set(get() + value);
				return *this;
			}

			__compelled_inline qh_m128d& __fpcall operator-=(imut __m128d value) nex {
				set(get() - value);
				return *this;
			}

			__compelled_inline qh_m128d& __fpcall operator*=(imut __m128d value) nex {
				set(get() * value);
				return *this;
			}

			__compelled_inline qh_m128d& __fpcall operator/=(imut __m128d value) nex {
				set(get() / value);
				return *this;
			}

	#endif

			__compelled_inline qh_m128d& __fpcall operator=(imut __m128d value) nex {
				set(value);
				return *this;
			}

			__compelled_inline __fpcall operator __m128d() imut nex {
				return get();
			}

#pragma endregion

		};

	#endif

	#endif

#pragma endregion

#pragma region AVX

#ifdef __AVX__

		class qh_m256 {

		private:

#pragma region Globals

			mut __m256 _value;

			mut std::uintptr_t _hash;

			mut bool is_polyc_alteration;

#pragma endregion

		public:

#pragma region Ctor / Dtor

			__compelled_inline __fpcall qh_m256(imut __m256 value = _mm256_setzero_ps()) nex {

				if (!is_init)
					init_hash_t();

				set(value);
			}

			__optimized_dtor ~qh_m256() nex {
			
				RtlZeroMemory(volatile_cast<__m256*>(&this->_value), sizeof(__m256));
				RtlZeroMemory(&this->_hash, sizeof(std::uintptr_t));
				RtlZeroMemory(&this->is_polyc_alteration, sizeof(bool));
			}

#pragma endregion

#pragma region Accessors

			__compelled_inline decltype(_value)* __stackcall open_data_ptr() imut nex {

				is_polyc_alteration = true;

				return &_value;
			}

			__compelled_inline imut bool __stackcall close_data_ptr() imut nex {

				auto hash = qhash::qhash_cpu(&_value, sizeof(_value));

				this->_hash = std::move(hash);

				is_polyc_alteration = false;

				return true;
			}

			__compelled_inline __m256 __stackcall get() imut nex {

				if (!is_polyc_alteration) {

					auto hash = qhash::qhash_cpu(reinterpret_cast<c_void>(&_value), sizeof(_value));

					if (hash != _hash)
						violation_callback(qengine::qexcept::q_rogueaccess(this->_hash, hash), reinterpret_cast<c_void>(&_value));
				}

				return _value;
			}

			__compelled_inline void __fpcall set( imut __m256 value) nex {

				auto hash = qhash::qhash_cpu(imut_cast<__m256*>(&value), sizeof(value));

				this->_hash = std::move(hash);

				_value = value;
			}

			__compelled_inline imut decltype(_value)* get_raw_memory_address() imut nex {
				return &_value;
			}

#pragma endregion

#pragma region Operators

	#ifdef __clang__

			__compelled_inline qh_m256 __fpcall operator+(imut __m256 value) imut nex {
				return qh_m256(get() + value);
			};

			__compelled_inline qh_m256 __fpcall operator-(imut __m256 value) imut nex {
				return qh_m256(get() - value);
			}

			__compelled_inline qh_m256 __fpcall operator/(imut __m256 value) imut nex {
				return qh_m256(get() / value);
			}

			__compelled_inline qh_m256 __fpcall operator*(imut __m256 value) imut nex {
				return qh_m256(get() * value);
			}

			__compelled_inline qh_m256& __fpcall operator+=(imut __m256 value) nex {
				set(get() + value);
				return *this;
			}

			__compelled_inline qh_m256& __fpcall operator-=(imut __m256 value) nex {
				set(get() - value);
				return *this;
			}

			__compelled_inline qh_m256& __fpcall operator*=(imut __m256 value) nex {
				set(get() * value);
				return *this;
			}

			__compelled_inline qh_m256& __fpcall operator/=(imut __m256 value) nex {
				set(get() / value);
				return *this;
			}

	#endif

			__compelled_inline qh_m256& __fpcall operator=(imut __m256 value) nex {
				set(value);
				return *this;
			}

			__compelled_inline __fpcall operator __m256() imut nex {
				return get();
			}

#pragma endregion

		};

		class qh_m256i {

		private:

#pragma region Globals

			mut __m256i _value;

			mut std::uintptr_t _hash;

			mut bool is_polyc_alteration;

#pragma endregion

		public:

#pragma region Ctor / Dtor

			__compelled_inline __fpcall qh_m256i(imut __m256i value = _mm256_setzero_si256()) nex {

				if (!is_init)
					init_hash_t();

				set(value);
			}

			__optimized_dtor ~qh_m256i() nex {
			
				RtlZeroMemory(volatile_cast<__m256i*>(&this->_value), sizeof(__m256i));
				RtlZeroMemory(&this->_hash, sizeof(std::uintptr_t));
				RtlZeroMemory(&this->is_polyc_alteration, sizeof(bool));
			}

#pragma endregion

#pragma region Accessors

			__compelled_inline decltype(_value)* __stackcall open_data_ptr() imut nex {

				is_polyc_alteration = true;

				return &_value;
			}

			__compelled_inline imut bool __stackcall close_data_ptr() imut nex {

				auto hash = qhash::qhash_cpu(&_value, sizeof(_value));

				this->_hash = std::move(hash);

				is_polyc_alteration = false;

				return true;
			}

			__compelled_inline __m256i __stackcall get() imut nex {

				if (!is_polyc_alteration) {

					auto hash = qhash::qhash_cpu(reinterpret_cast<c_void>(&_value), sizeof(_value));

					if (hash != _hash)
						violation_callback(qengine::qexcept::q_rogueaccess(this->_hash, hash), reinterpret_cast<c_void>(&_value));
				}

				return _value;
			}

			__compelled_inline void __fpcall set( imut __m256i value) nex {

				auto hash = qhash::qhash_cpu(imut_cast<__m256i*>(&value), sizeof(value));

				this->_hash = std::move(hash);

				_value = value;
			}

			__compelled_inline imut decltype(_value)* __stackcall get_raw_memory_address() imut nex {
				return &_value;
			}

#pragma endregion

#pragma region Operators

	#ifdef __clang__

			__compelled_inline qh_m256i __fpcall operator+(imut __m256i value) imut nex {
				return qh_m256i(get() + value);
			};

			__compelled_inline qh_m256i __fpcall operator-(imut __m256i value) imut nex {
				return qh_m256i(get() - value);
			}

			__compelled_inline qh_m256i __fpcall operator/(imut __m256i value) imut nex {
				return qh_m256i(get() / value);
			}

			__compelled_inline qh_m256i __fpcall operator*(imut __m256i value) imut nex {
				return qh_m256i(get() * value);
			}

			__compelled_inline qh_m256i& __fpcall operator+=(imut __m256i value) nex {
				set(get() + value);
				return *this;
			}

			__compelled_inline qh_m256i& __fpcall operator-=(imut __m256i value) nex {
				set(get() - value);
				return *this;
			}

			__compelled_inline qh_m256i& __fpcall operator*=(imut __m256i value) nex {
				set(get() * value);
				return *this;
			}

			__compelled_inline qh_m256i& __fpcall operator/=(imut __m256i value) nex {
				set(get() / value);
				return *this;
			}

	#endif

			__compelled_inline qh_m256i& __fpcall operator=(imut __m256i value) nex {
				set(value);
				return *this;
			}

			__compelled_inline __fpcall operator __m256i() imut nex {
				return get();
			}

#pragma endregion
		};

		class qh_m256d {

		private:

#pragma region Globals

			mut __m256d _value;

			mut std::uintptr_t _hash;

			mut bool is_polyc_alteration;

#pragma endregion

		public:

#pragma region Ctor / Dtor

			__compelled_inline __fpcall qh_m256d(imut __m256d value = _mm256_setzero_pd()) nex {

				if (!is_init)
					init_hash_t();

				set(value);
			}

			__optimized_dtor ~qh_m256d() nex {
			
				RtlZeroMemory(volatile_cast<__m256d*>(&this->_value), sizeof(__m256d));
				RtlZeroMemory(&this->_hash, sizeof(std::uintptr_t));
				RtlZeroMemory(&this->is_polyc_alteration, sizeof(bool));
			}

#pragma endregion

#pragma region Accessors

			__compelled_inline decltype(_value)* __stackcall open_data_ptr() imut nex {

				is_polyc_alteration = true;

				return &_value;
			}

			__compelled_inline imut bool __stackcall close_data_ptr() imut nex {

				auto hash = qhash::qhash_cpu(&_value, sizeof(_value));

				this->_hash = std::move(hash);

				is_polyc_alteration = false;

				return true;
			}

			__compelled_inline __m256d __stackcall get() imut nex {

				if (!is_polyc_alteration) {

					auto hash = qhash::qhash_cpu(reinterpret_cast<c_void>(&_value), sizeof(_value));

					if (hash != _hash)
						violation_callback(qengine::qexcept::q_rogueaccess(this->_hash, hash), reinterpret_cast<c_void>(&_value));
				}

				return _value;
			}

			__compelled_inline void __fpcall set( imut __m256d value) nex {

				auto hash = qhash::qhash_cpu(imut_cast<__m256d*>(&value), sizeof(value));

				this->_hash = std::move(hash);

				_value = value;
			}

			__compelled_inline imut decltype(_value)* __stackcall get_raw_memory_address() imut nex {
				return &_value;
			}

#pragma endregion

#pragma region Operators

	#ifdef __clang__

			__compelled_inline qh_m256d __fpcall operator+(imut __m256d value) imut nex {
				return qh_m256d(get() + value);
			};

			__compelled_inline qh_m256d __fpcall operator-(imut __m256d value) imut nex {
				return qh_m256d(get() - value);
			}

			__compelled_inline qh_m256d __fpcall operator/(imut __m256d value) imut nex {
				return qh_m256d(get() / value);
			}

			__compelled_inline qh_m256d __fpcall operator*(imut __m256d value) imut nex {
				return qh_m256d(get() * value);
			}

			__compelled_inline qh_m256d& __fpcall operator+=(imut __m256d value) nex {
				set(get() + value);
				return *this;
			}

			__compelled_inline qh_m256d& __fpcall operator-=(imut __m256d value) nex {
				set(get() - value);
				return *this;
			}

			__compelled_inline qh_m256d& __fpcall operator*=(imut __m256d value) nex {
				set(get() * value);
				return *this;
			}

			__compelled_inline qh_m256d& __fpcall operator/=(imut __m256d value) nex {
				set(get() / value);
				return *this;
			}

	#endif

			__compelled_inline qh_m256d& __fpcall operator=(imut __m256d value) nex {
				set(value);
				return *this;
			}

			__compelled_inline __fpcall operator __m256d() imut nex {
				return get();
			}

#pragma endregion
		};

	#endif

#pragma endregion

#pragma endregion

#pragma region String Types

#pragma region String

		class qh_string {

		private:

#pragma region Encrypted value

			mut std::string _value;

			mut std::uintptr_t _hash;

			mut bool is_polyc_alteration;

#pragma endregion

		public:

#pragma region Ctor / Dtor

			__compelled_inline __stackcall qh_string(imut std::string value) nex {

				if (!is_init)
					init_hash_t();

				set(value);
			}

			__optimized_ctor qh_string(imut char* value = "") nex {
				
				if (!is_init)
					init_hash_t();

				set( std::string(value));
			}

			__optimized_dtor ~qh_string() nex {
			
				RtlZeroMemory(imut_cast<char*>(this->_value.c_str()), _value.length());
				RtlZeroMemory(&this->_hash, sizeof(std::uintptr_t));
				RtlZeroMemory(&this->is_polyc_alteration, sizeof(bool));
			}

#pragma endregion

#pragma region Accessors

			__compelled_inline std::string* __stackcall open_str_ptr() imut nex {

				is_polyc_alteration = true;

				return &_value;
			}

			__compelled_inline imut char* __stackcall open_data_ptr() imut nex {

				is_polyc_alteration = true;

				return _value.c_str();
			}

			__compelled_inline bool __stackcall close_data_ptr() imut nex {

				auto hash = qhash::qhash_cpu(imut_cast<char*>(_value.c_str()), _value.length());

				this->_hash = std::move(hash);

				is_polyc_alteration = false;

				return true;
			}

			__compelled_inline std::string __stackcall get() imut nex {

				if (!is_polyc_alteration) {

					auto hash = qhash::qhash_cpu(imut_cast<char*>(_value.c_str()), _value.length());

					if (hash != _hash)
						violation_callback(qengine::qexcept::q_rogueaccess(_hash, hash), reinterpret_cast<c_void>(&_value));
				}

				return _value;
			}

			__compelled_inline void __stackcall set( imut std::string value) nex {

				auto hash = qhash::qhash_cpu(imut_cast<char*>(value.c_str()), value.length());

				this->_hash = std::move(hash);

				_value = value;
			}

			__compelled_inline imut char* __stackcall get_raw_memory_address() imut nex {
				return _value.c_str();
			}

#pragma endregion

#pragma region Operators

			__compelled_inline qh_string __stackcall operator+(imut std::string& value) imut nex {
				return qh_string(get() + value);
			}

			__compelled_inline qh_string& __stackcall operator+=(imut std::string& value) nex {
				set(static_cast<std::string>(get() + value));
				return *this;
			}

			__compelled_inline qh_string& __stackcall operator=(imut std::string value) nex {
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

		class qh_wstring {

		private:

#pragma region Encrypted value

			mut std::wstring _value = L"";

			mut std::uintptr_t _hash;

			mut bool is_polyc_alteration;

#pragma endregion

		public:

#pragma region Ctor / Dtor

			__compelled_inline __stackcall qh_wstring(imut std::wstring value) nex {

				if (!is_init)
					init_hash_t();

				set(value);
			}

			__optimized_ctor qh_wstring(imut wchar_t* value = L"") nex {
				
				if (!is_init)
					init_hash_t();

				set( std::wstring(value));
			}

			__optimized_dtor ~qh_wstring() nex {
			
				RtlZeroMemory(imut_cast<wchar_t*>(this->_value.c_str()), _value.length() * sizeof(wchar_t));
				RtlZeroMemory(&this->_hash, sizeof(std::uintptr_t));
				RtlZeroMemory(&this->is_polyc_alteration, sizeof(bool));
			}

#pragma endregion

#pragma region Accessors

			__compelled_inline std::wstring* __stackcall open_wstr_ptr() imut nex {

				is_polyc_alteration = true;

				return &_value;
			}

			__compelled_inline imut wchar_t* __stackcall open_data_ptr() imut nex {

				is_polyc_alteration = true;

				return _value.c_str();
			}

			__compelled_inline bool __stackcall close_data_ptr() imut nex {

				auto hash = qhash::qhash_cpu(imut_cast<wchar_t*>(_value.c_str()), _value.length() * sizeof(wchar_t));

				this->_hash = std::move(hash);

				is_polyc_alteration = false;

				return true;
			}

			__compelled_inline std::wstring __stackcall get() imut nex {

				if (!is_polyc_alteration) {

					auto hash = qhash::qhash_cpu(imut_cast<wchar_t*>(_value.c_str()), sizeof(wchar_t) * _value.length());

					if (hash != _hash)
						violation_callback(qengine::qexcept::q_rogueaccess(_hash, hash), reinterpret_cast<c_void>(&_value));
				}

				auto _return = _value;

				return _return;
			}

			__compelled_inline void __regcall set( imut std::wstring value) nex {

				auto hash = qhash::qhash_cpu(imut_cast<wchar_t*>(value.c_str()), sizeof(wchar_t) * value.length());

				this->_hash = std::move(hash);

				_value = value;
			}

			__compelled_inline imut wchar_t* __stackcall get_raw_memory_address() imut nex {
				return _value.c_str();
			}

#pragma endregion

#pragma region Operators

			__compelled_inline qh_wstring __stackcall operator+(imut std::wstring& value) imut nex {
				return qh_wstring(get() + value);
			}

			__compelled_inline qh_wstring& __stackcall operator+=(imut std::wstring& value) nex {
				set(static_cast<std::wstring>(get() + value));
				return *this;
			}

			__compelled_inline qh_wstring& __stackcall operator=(imut std::wstring& value) nex {
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

		class qh_malloc {

		private:

#pragma region Globals

			mut c_void allocation;
			mut size_t allocation_size;

			mut std::uintptr_t _hash;

			mut bool is_polyc_alteration;

#pragma endregion

#pragma region Subscript proxy

			// nested class to support subscript assignment
			class index_proxy {

			private:

#pragma region Globals

				qh_malloc& parent;
				std::size_t index;

#pragma endregion

			public:
			
#pragma region Ctor

				index_proxy(imut std::size_t index_, qh_malloc& instance) : index(index_), parent(instance) { }

#pragma endregion

#pragma region Operator overrides

				__compelled_inline std::uint8_t& __regcall operator=(std::uint8_t value) nex {
					parent.set(index, value);
					return value;   // return the passed assignment value rather than using up absurd resources to decrypt, re-encrypt everything using get()
				}

				__compelled_inline __stackcall operator std::uint8_t() imut nex {
					return parent.get(index);
				}

#pragma endregion
			};

#pragma endregion

		public:

#pragma region Ctor

			__compelled_inline __regcall qh_malloc(imut std::size_t size = 0) nex : allocation_size(size) {

				if (!size)
					return;

				if (!is_init)
					init_hash_t();

				auto alloc = malloc(size);

				swap(alloc, size);
			}

#pragma endregion

#pragma region Get / Set

			__compelled_inline imut c_void __stackcall open_data_ptr() imut nex {

				is_polyc_alteration = true;

				return allocation;
			}

			__compelled_inline imut bool __stackcall close_data_ptr() imut nex {

				auto hash = qhash::qhash_cpu(allocation, allocation_size);

				this->_hash = std::move(hash);

				is_polyc_alteration = false;

				return true;
			}

			__compelled_inline imut bool __regcall get(c_void destination, std::uintptr_t offset, std::size_t length) imut nex {

				if (!allocation || !destination)
					return false;

				if (!is_polyc_alteration) {

					auto hash = qhash::qhash_cpu(allocation, allocation_size);

					if (hash != _hash) {
						violation_callback(qengine::qexcept::q_rogueaccess(_hash, hash), allocation);
						return false;
					}
				}

				memcpy(destination, reinterpret_cast<c_void>(reinterpret_cast<uintptr_t>(allocation) + offset), length);

				return true;
			}

			__compelled_inline char __regcall get(std::uintptr_t offset) imut nex {

				char _return{};

				if (!get(&_return, 0, sizeof(_return)))
					return NULL;

				return _return;
			}

			__compelled_inline c_void __stackcall get() imut nex {

				auto alloc_new = malloc(allocation_size);

				if (!alloc_new)
					return nullptr;

				if (!get(alloc_new, 0, allocation_size)) {

					free(alloc_new);

					return nullptr;
				}

				return alloc_new;
			}

			__compelled_inline bool __regcall set(c_void source, std::uintptr_t offset, std::size_t length) nex {

				if (!allocation || !source)
					return false;

				memcpy(reinterpret_cast<c_void>(reinterpret_cast<uintptr_t>(allocation) + offset), source, length);

				_hash = qhash::qhash_cpu(allocation, allocation_size);

				return true;
			}

			__compelled_inline bool __regcall set( imut std::uintptr_t index, std::int8_t value) nex {

				if (!set(&value, index, sizeof(value)))
					return false;

				return true;
			}

#pragma endregion

#pragma region Property Accessors

			__compelled_inline std::size_t __stackcall length() imut nex {

				return allocation_size;
			}

			__compelled_inline c_void __stackcall get_raw_memory_address() imut nex {

				return allocation;
			}

#pragma endregion

#pragma region Utility functions

			__compelled_inline imut bool __stackcall zero() nex {

				auto alloc_z = malloc(allocation_size);

				if (!alloc_z)
					return false;

				RtlZeroMemory(alloc_z, allocation_size);

				set(alloc_z, 0, allocation_size);

				free(alloc_z);

				return true;
			}

			__compelled_inline imut bool __regcall reallocate(std::size_t size) nex {

				auto alloc_r = realloc(allocation, size);

				if (!alloc_r)
					return false;

				allocation = std::move(alloc_r);

				allocation_size = size;

				_hash = qhash::qhash_cpu(allocation, size);

				return true;
			}

			__compelled_inline imut bool __regcall swap(c_void allocation_, std::size_t size) nex {

				if (!allocation_)
					return false;

				if(allocation)
					free(allocation);

				allocation = allocation_;
				allocation_size = size;

				_hash = qhash::qhash_cpu(allocation_, size);

				return true;
			}

#pragma endregion

#pragma region Operators

			__compelled_inline index_proxy __regcall operator[](std::size_t index) nex {
				return index_proxy(index, *this);
			}

#pragma endregion

#pragma region Destructor

			__compelled_inline __stackcall ~qh_malloc() nex {

				if (!allocation)
					return;

				RtlZeroMemory(allocation, allocation_size);	

				free(allocation);
			}

#pragma endregion
		};

#pragma endregion

#pragma region Extended Typedefs

	#ifdef _WIN64

			typedef qh_uint64 qh_uintptr_t;
			typedef qh_uint64 qh_size_t;

	#else

			typedef qh_uint32 qh_uintptr_t;
			typedef qh_uint32 qh_size_t;

	#endif

#pragma endregion

	}  

#pragma region Static Declarators

	noregister qcallback::qmem_exception_rogue_c qengine::qtype_hash::violation_callback;

	bool qengine::qtype_hash::is_init = false;

#pragma endregion
} 

#endif