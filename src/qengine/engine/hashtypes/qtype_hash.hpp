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

		extern volatile qcallback::qmem_exception_rogue_c violation_callback;

		extern bool is_init;

	#pragma endregion

	#pragma region Global Static Methods / Callbacks

		static __singleton void __regcall violation_callback_d(qexcept::q_rogueaccess except, void* data) noexcept {

			if (except.id != qexcept::MEMORY_ALTERATION) // ensure this callback has been raised due to memory alteration
				return;
		}

		static __compelled_inline_noseh void __stackcall init_hash_t(qcallback::qmem_exception_rogue_c callback = violation_callback_d) noexcept {

			violation_callback = callback;

			is_init = true;
		}

	#pragma endregion

	#pragma region Types

	#pragma region WORD

	#pragma region 8-bit

		class qh_int8{

		private:

	#pragma region Globals

			mutable std::int8_t _value{};

			mutable qhash::qhash_cpu_t _hash{};

	#pragma endregion

		public:

	#pragma region CTOR

			__optimized_ctor qh_int8(const char value = 0) noexcept {

				if (!is_init)
					init_hash_t();

				set(value);
			}
			
	#pragma endregion

	#pragma region Accessors

			__compelled_inline_noseh std::int8_t& __stackcall get() const noexcept {

				auto hash = qhash::qhash_cpu(reinterpret_cast<void*>(&_value), sizeof(_value));

				if (hash != _hash)
					violation_callback(qexcept::q_rogueaccess(this->_hash.hash_obj.hash, hash.hash_obj.hash), reinterpret_cast<void*>(&_value));

				auto _return = _value;

				return _return;
			}

			__compelled_inline_noseh void __regcall set(std::int8_t value) noexcept {

				auto hash = qhash::qhash_cpu(&value, sizeof(value));

				this->_hash = hash;

				_value = value;
			}

			__compelled_inline_noseh decltype(_value)* __stackcall get_raw_memory_address() const noexcept {
				return &_value;
			}

	#pragma endregion

	#pragma region Operators

			__compelled_inline_noseh qh_int8 __regcall operator+(const std::int8_t value) const noexcept {
				return qh_int8(get() + value);
			};

			__compelled_inline_noseh qh_int8 __regcall operator-(const std::int8_t value) const noexcept {
				return qh_int8(get() - value);
			}

			__compelled_inline_noseh qh_int8 __regcall operator/(const std::int8_t value) const noexcept {
				return qh_int8(get() / value);
			}

			__compelled_inline_noseh qh_int8 __regcall operator*(const std::int8_t value) const noexcept {
				return qh_int8(get() * value);
			}

			__compelled_inline_noseh qh_int8 __regcall operator&(const std::int8_t value) const noexcept {
				return qh_int8(get() & value);
			}

			__compelled_inline_noseh qh_int8 __regcall operator|(const std::int8_t value) const noexcept {
				return qh_int8(get() | value);
			}

			__compelled_inline_noseh qh_int8 __regcall operator%(const std::int8_t value) const noexcept {
				return qh_int8(get() % value);
			}

			__compelled_inline_noseh qh_int8 __regcall operator^(const std::int8_t value) const noexcept {
				return qh_int8(get() ^ value);
			}

			__compelled_inline_noseh qh_int8 __regcall operator<<(const std::int8_t value) const noexcept {
				return qh_int8(get() << value);
			}

			__compelled_inline_noseh qh_int8 __regcall operator>>(const std::int8_t value) const noexcept {
				return qh_int8(get() >> value);
			}

			__compelled_inline_noseh qh_int8& __regcall operator+=(const std::int8_t value) noexcept {
				set(static_cast<std::int8_t>(get() + value));
				return *this;
			}

			__compelled_inline_noseh qh_int8& __regcall operator-=(const std::int8_t value) noexcept {
				set(static_cast<std::int8_t>(get() - value));
				return *this;
			}

			__compelled_inline_noseh qh_int8& __stackcall operator++() noexcept {
				operator+=(1i8);
				return *this;
			}

			__compelled_inline_noseh qh_int8& __stackcall operator--() noexcept {
				operator-=(1i8);
				return *this;
			}

			__compelled_inline_noseh qh_int8& __regcall operator*=(const std::int8_t value) noexcept {
				set(static_cast<std::int8_t>(get() * value));
				return *this;
			}

			__compelled_inline_noseh qh_int8& __regcall operator/=(const std::int8_t value) noexcept {
				set(static_cast<std::int8_t>(get() / value));
				return *this;
			}

			__compelled_inline_noseh qh_int8& __regcall operator%=(const std::int8_t value) noexcept {
				set(static_cast<std::int8_t>(get() % value));
				return *this;
			}

			__compelled_inline_noseh qh_int8& __regcall operator^=(const std::int8_t value) noexcept {
				set(static_cast<std::int8_t>(get() ^ value));
				return *this;
			}

			__compelled_inline_noseh qh_int8& __regcall operator&=(const std::int8_t value) noexcept {
				set(static_cast<std::int8_t>(get() & value));
				return *this;
			}

			__compelled_inline_noseh qh_int8& __regcall operator|=(const std::int8_t value) noexcept {
				set(static_cast<std::int8_t>(get() | value));
				return *this;
			}

			__compelled_inline_noseh qh_int8& __regcall operator<<=(const std::int8_t value) noexcept {
				set(static_cast<std::int8_t>(get() << value));
				return *this;
			}

			__compelled_inline_noseh qh_int8& __regcall operator>>=(const std::int8_t value) noexcept {
				set(static_cast<std::int8_t>(get() >> value));
				return *this;
			}

			__compelled_inline_noseh qh_int8& __regcall operator=(const std::int8_t value) noexcept {
				set(value);
				return *this;
			}

			__compelled_inline_noseh __regcall operator std::int8_t() const noexcept {
				return get();
			}

			__compelled_inline_noseh ~qh_int8() noexcept { }

	#pragma endregion

		};

		class qh_uint8 {

		private:

	#pragma region Globals

			mutable std::uint8_t _value{};

			mutable qhash::qhash_cpu_t _hash{};

	#pragma endregion

		public:

	#pragma region CTOR

			__optimized_ctor qh_uint8(const std::uint8_t value = 0) noexcept {

				if (!is_init)
					init_hash_t();

				set(value);
			}

	#pragma endregion

	#pragma region Accessors

			__compelled_inline_noseh std::uint8_t& __stackcall get() const noexcept {

				auto hash = qhash::qhash_cpu(reinterpret_cast<void*>(&_value), sizeof(_value));

				if (hash != _hash)
					violation_callback(qexcept::q_rogueaccess(this->_hash.hash_obj.hash, hash.hash_obj.hash), reinterpret_cast<void*>(&_value));

				auto _return = _value;

				return _return;
			}

			__compelled_inline_noseh void __regcall set(std::uint8_t value) noexcept {

				auto hash = qhash::qhash_cpu(&value, sizeof(value));

				this->_hash = hash;

				_value = value;
			}

			__compelled_inline_noseh decltype(_value)* __stackcall get_raw_memory_address() const noexcept{
				return &_value;
			}

	#pragma endregion

	#pragma region Operators

			__compelled_inline_noseh qh_uint8 __regcall operator+(const std::uint8_t value) const noexcept {
				return qh_uint8(get() + value);
			};

			__compelled_inline_noseh qh_uint8 __regcall operator-(const std::uint8_t value) const noexcept {
				return qh_uint8(get() - value);
			}

			__compelled_inline_noseh qh_uint8 __regcall operator/(const std::uint8_t value) const noexcept {
				return qh_uint8(get() / value);
			}

			__compelled_inline_noseh qh_uint8 __regcall operator*(const std::uint8_t value) const noexcept {
				return qh_uint8(get() * value);
			}

			__compelled_inline_noseh qh_uint8 __regcall operator&(const std::uint8_t value) const noexcept {
				return qh_uint8(get() & value);
			}

			__compelled_inline_noseh qh_uint8 __regcall operator|(const std::uint8_t value) const noexcept {
				return qh_uint8(get() | value);
			}

			__compelled_inline_noseh qh_uint8 __regcall operator%(const std::uint8_t value) const noexcept {
				return qh_uint8(get() % value);
			}

			__compelled_inline_noseh qh_uint8 __regcall operator^(const std::uint8_t value) const noexcept {
				return qh_uint8(get() ^ value);
			}

			__compelled_inline_noseh qh_uint8 __regcall operator<<(const std::uint8_t value) const noexcept {
				return qh_uint8(get() << value);
			}

			__compelled_inline_noseh qh_uint8 __regcall operator>>(const std::uint8_t value) const noexcept {
				return qh_uint8(get() >> value);
			}

			__compelled_inline_noseh qh_uint8& __regcall operator+=(const std::uint8_t value) noexcept {
				set(static_cast<std::uint8_t>(get() + value));
				return *this;
			}

			__compelled_inline_noseh qh_uint8& __regcall operator-=(const std::uint8_t value) noexcept {
				set(static_cast<std::uint8_t>(get() - value));
				return *this;
			}

			__compelled_inline_noseh qh_uint8& __stackcall operator++() noexcept {
				operator+=(1i8);
				return *this;
			}

			__compelled_inline_noseh qh_uint8& __stackcall operator--() noexcept {
				operator-=(1i8);
				return *this;
			}

			__compelled_inline_noseh qh_uint8& __regcall operator*=(const std::uint8_t value) noexcept {
				set(static_cast<byte>(get() * value));
				return *this;
			}

			__compelled_inline_noseh qh_uint8& __regcall operator/=(const std::uint8_t value) noexcept {
				set(static_cast<byte>(get() / value));
				return *this;
			}

			__compelled_inline_noseh qh_uint8& __regcall operator%=(const std::uint8_t value) noexcept {
				set(static_cast<byte>(get() % value));
				return *this;
			}

			__compelled_inline_noseh qh_uint8& __regcall operator^=(const std::uint8_t value) noexcept {
				set(static_cast<byte>(get() ^ value));
				return *this;
			}

			__compelled_inline_noseh qh_uint8& __regcall operator&=(const std::uint8_t value) noexcept {
				set(static_cast<byte>(get() & value));
				return *this;
			}

			__compelled_inline_noseh qh_uint8& __regcall operator|=(const std::uint8_t value) noexcept {
				set(static_cast<byte>(get() | value));
				return *this;
			}

			__compelled_inline_noseh qh_uint8& __regcall operator<<=(const std::uint8_t value) noexcept {
				set(static_cast<byte>(get() << value));
				return *this;
			}

			__compelled_inline_noseh qh_uint8& __regcall operator>>=(const std::uint8_t value) noexcept {
				set(static_cast<byte>(get() >> value));
				return *this;
			}

			__compelled_inline_noseh qh_uint8& __regcall operator=(const std::uint8_t value) noexcept {
				set(value);
				return *this;
			}

			__compelled_inline_noseh __stackcall operator std::uint8_t() const noexcept {
				return get();
			}

			__compelled_inline_noseh ~qh_uint8() { }
	#pragma endregion
		};

	#pragma endregion

	#pragma region 16-bit

		class qh_int16 {

		private:

	#pragma region Globals

			mutable short _value{};

			mutable qhash::qhash_cpu_t _hash{};

	#pragma endregion

		public:

	#pragma region CTOR

			__optimized_ctor qh_int16(const short value = 0) noexcept {

				if (!is_init)
					init_hash_t();

				set(value);
			}

	#pragma endregion

	#pragma region Accessors

			__compelled_inline_noseh short __regcall get() const noexcept {

				auto hash = qhash::qhash_cpu(reinterpret_cast<void*>(&_value), sizeof(_value));

				if (hash != _hash)
					violation_callback(qexcept::q_rogueaccess(this->_hash.hash_obj.hash, hash.hash_obj.hash), reinterpret_cast<void*>(&_value));

				auto _return = _value;

				return _return;
			}

			__compelled_inline_noseh void __regcall set(short value) noexcept {

				auto hash = qhash::qhash_cpu(&value, sizeof(value));

				this->_hash = hash;

				_value = value;
			}

			__compelled_inline_noseh decltype(_value)* get_raw_memory_address() const noexcept {
				return &_value;
			}

	#pragma endregion

	#pragma region Operators

			__compelled_inline_noseh qh_int16 __regcall operator+(const short value) const noexcept {
				return qh_int16(get() + value);
			};

			__compelled_inline_noseh qh_int16 __regcall operator-(const short value) const noexcept {
				return qh_int16(get() - value);
			}

			__compelled_inline_noseh qh_int16 __regcall operator/(const short value) const noexcept {
				return qh_int16(get() / value);
			}

			__compelled_inline_noseh qh_int16 __regcall operator*(const short value) const noexcept {
				return qh_int16(get() * value);
			}

			__compelled_inline_noseh qh_int16 __regcall operator&(const short value) const noexcept {
				return qh_int16(get() & value);
			}

			__compelled_inline_noseh qh_int16 __regcall operator|(const short value) const noexcept {
				return qh_int16(get() | value);
			}

			__compelled_inline_noseh qh_int16 __regcall operator%(const short value) const noexcept {
				return qh_int16(get() % value);
			}

			__compelled_inline_noseh qh_int16 __regcall operator^(const short value) const noexcept {
				return qh_int16(get() ^ value);
			}

			__compelled_inline_noseh qh_int16 __regcall operator<<(const short value) const noexcept {
				return qh_int16(get() << value);
			}

			__compelled_inline_noseh qh_int16 __regcall operator>>(const short value) const noexcept {
				return qh_int16(get() >> value);
			}

			__compelled_inline_noseh qh_int16& __regcall operator+=(const short value) noexcept {
				set(static_cast<short>(get() + value));
				return *this;
			}

			__compelled_inline_noseh qh_int16& __regcall operator-=(const short value) noexcept {
				set(static_cast<short>(get() - value));
				return *this;
			}

			__compelled_inline_noseh qh_int16& __regcall operator++() noexcept {
				operator+=(1i8);
				return *this;
			}

			__compelled_inline_noseh qh_int16& __regcall operator--() noexcept {
				operator-=(1i8);
				return *this;
			}

			__compelled_inline_noseh qh_int16& __regcall operator*=(const short value) noexcept {
				set(static_cast<short>(get() * value));
				return *this;
			}

			__compelled_inline_noseh qh_int16& __regcall operator/=(const short value) noexcept {
				set(static_cast<short>(get() / value));
				return *this;
			}

			__compelled_inline_noseh qh_int16& __regcall operator%=(const short value) noexcept {
				set(static_cast<short>(get() % value));
				return *this;
			}

			__compelled_inline_noseh qh_int16& __regcall operator^=(const short value) noexcept {
				set(static_cast<short>(get() ^ value));
				return *this;
			}

			__compelled_inline_noseh qh_int16& __regcall operator&=(const short value) noexcept {
				set(static_cast<short>(get() & value));
				return *this;
			}

			__compelled_inline_noseh qh_int16& __regcall operator|=(const short value) noexcept {
				set(static_cast<short>(get() | value));
				return *this;
			}

			__compelled_inline_noseh qh_int16& __regcall operator<<=(const short value) noexcept {
				set(static_cast<short>(get() << value));
				return *this;
			}

			__compelled_inline_noseh qh_int16& __regcall operator>>=(const short value) noexcept {
				set(static_cast<short>(get() >> value));
				return *this;
			}

			__compelled_inline_noseh qh_int16& __regcall operator=(const short value) noexcept {
				set(value);
				return *this;
			}

			__compelled_inline_noseh __regcall operator short() const noexcept {
				return get();
			}

			__compelled_inline_noseh ~qh_int16() { }
	#pragma endregion
		};

		class qh_uint16 {

		private:

	#pragma region Globals

			mutable std::uint16_t _value{};

			mutable qhash::qhash_cpu_t _hash{};

	#pragma endregion

		public:

	#pragma region CTOR

			__optimized_ctor qh_uint16(std::uint16_t value = 0) noexcept {

				if (!is_init)
					init_hash_t();

				set(value);
			}

	#pragma endregion

	#pragma region Accessors

			__compelled_inline_noseh std::uint16_t __regcall get() const noexcept {

				auto hash = qhash::qhash_cpu(reinterpret_cast<void*>(&_value), sizeof(_value));

				if (hash != _hash)
					violation_callback(qexcept::q_rogueaccess(this->_hash.hash_obj.hash, hash.hash_obj.hash), reinterpret_cast<void*>(&_value));

				auto _return = _value;

				return _return;
			}

			__compelled_inline_noseh void __regcall set(std::uint16_t value) noexcept {

				auto hash = qhash::qhash_cpu(&value, sizeof(value));

				this->_hash = hash;

				_value = value;
			}

			__compelled_inline_noseh decltype(_value)* get_raw_memory_address() const noexcept {
				return &_value;
			}

	#pragma endregion

	#pragma region Operators

			__compelled_inline_noseh qh_uint16 __regcall operator+(const std::uint16_t value) const noexcept {
				return qh_uint16(get() + value);
			};

			__compelled_inline_noseh qh_uint16 __regcall operator-(const std::uint16_t value) const noexcept {
				return qh_uint16(get() - value);
			}

			__compelled_inline_noseh qh_uint16 __regcall operator/(const std::uint16_t value) const noexcept {
				return qh_uint16(get() / value);
			}

			__compelled_inline_noseh qh_uint16 __regcall operator*(const std::uint16_t value) const noexcept {
				return qh_uint16(get() * value);
			}

			__compelled_inline_noseh qh_uint16 __regcall operator&(const std::uint16_t value) const noexcept {
				return qh_uint16(get() & value);
			}

			__compelled_inline_noseh qh_uint16 __regcall operator|(const std::uint16_t value) const noexcept {
				return qh_uint16(get() | value);
			}

			__compelled_inline_noseh qh_uint16 __regcall operator%(const std::uint16_t value) const noexcept {
				return qh_uint16(get() % value);
			}

			__compelled_inline_noseh qh_uint16 __regcall operator^(const std::uint16_t value) const noexcept {
				return qh_uint16(get() ^ value);
			}

			__compelled_inline_noseh qh_uint16 __regcall operator<<(const std::uint16_t value) const noexcept {
				return qh_uint16(get() << value);
			}

			__compelled_inline_noseh qh_uint16 __regcall operator>>(const std::uint16_t value) const noexcept {
				return qh_uint16(get() >> value);
			}

			__compelled_inline_noseh qh_uint16& __regcall operator+=(const std::uint16_t value) noexcept {
				set(static_cast<std::uint16_t>(get() + value));
				return *this;
			}

			__compelled_inline_noseh qh_uint16& __regcall operator-=(const std::uint16_t value) noexcept {
				set(static_cast<std::uint16_t>(get() - value));
				return *this;
			}

			__compelled_inline_noseh qh_uint16& __regcall operator++() noexcept {
				operator+=(1i8);
				return *this;
			}

			__compelled_inline_noseh qh_uint16& __regcall operator--() noexcept {
				operator-=(1i8);
				return *this;
			}

			__compelled_inline_noseh qh_uint16& __regcall operator*=(const std::uint16_t value) noexcept {
				set(static_cast<std::uint16_t>(get() * value));
				return *this;
			}

			__compelled_inline_noseh qh_uint16& __regcall operator/=(const std::uint16_t value) noexcept {
				set(static_cast<std::uint16_t>(get() / value));
				return *this;
			}

			__compelled_inline_noseh qh_uint16& __regcall operator%=(const std::uint16_t value) noexcept {
				set(static_cast<std::uint16_t>(get() % value));
				return *this;
			}

			__compelled_inline_noseh qh_uint16& __regcall operator^=(const std::uint16_t value) noexcept {
				set(static_cast<std::uint16_t>(get() ^ value));
				return *this;
			}

			__compelled_inline_noseh qh_uint16& __regcall operator&=(const std::uint16_t value) noexcept {
				set(static_cast<std::uint16_t>(get() & value));
				return *this;
			}

			__compelled_inline_noseh qh_uint16& __regcall operator|=(const std::uint16_t value) noexcept {
				set(static_cast<std::uint16_t>(get() | value));
				return *this;
			}

			__compelled_inline_noseh qh_uint16& __regcall operator<<=(const std::uint16_t value) noexcept {
				set(static_cast<std::uint16_t>(get() << value));
				return *this;
			}

			__compelled_inline_noseh qh_uint16& __regcall operator>>=(const std::uint16_t value) noexcept {
				set(static_cast<std::uint16_t>(get() >> value));
				return *this;
			}

			__compelled_inline_noseh qh_uint16& __regcall operator=(const std::uint16_t value) noexcept {
				set(value);
				return *this;
			}

			__compelled_inline_noseh __regcall operator std::uint16_t() const noexcept {
				return get();
			}

			__compelled_inline_noseh ~qh_uint16() {	}
	#pragma endregion
		};

	#pragma endregion

	#pragma region 32-bit

		class qh_int32 {

		private:

	#pragma region Globals

			mutable int _value{};

			mutable qhash::qhash_cpu_t _hash{};

	#pragma endregion

		public:

	#pragma region CTOR

			__optimized_ctor qh_int32(int value = 0) noexcept {

				if (!is_init)
					init_hash_t();

				set(value);
			}

	#pragma endregion

	#pragma region Accessors

			__compelled_inline_noseh int __regcall get() const noexcept {

				auto hash = qhash::qhash_cpu(reinterpret_cast<void*>(&_value), sizeof(_value));

				if (hash != _hash) 
					violation_callback(qexcept::q_rogueaccess(this->_hash.hash_obj.hash, hash.hash_obj.hash), reinterpret_cast<void*>(&_value));

				auto _return = _value;

				return _return;
			}

			__compelled_inline_noseh void __regcall set(int value) noexcept {

				auto hash = qhash::qhash_cpu(&value, sizeof(value));

				this->_hash = hash;

				_value = value;
			}

			__compelled_inline_noseh decltype(_value)* get_raw_memory_address() const noexcept {
				return &_value;
			}

	#pragma endregion

	#pragma region Operators

			__compelled_inline_noseh qh_int32 __regcall operator+(const int value) const noexcept {
				return qh_int32(get() + value);
			};

			__compelled_inline_noseh qh_int32 __regcall operator-(const int value) const noexcept {
				return qh_int32(get() - value);
			}

			__compelled_inline_noseh qh_int32 __regcall operator/(const int value) const noexcept {
				return qh_int32(get() / value);
			}

			__compelled_inline_noseh qh_int32 __regcall operator*(const int value) const noexcept {
				return qh_int32(get() * value);
			}

			__compelled_inline_noseh qh_int32 __regcall operator&(const int value) const noexcept {
				return qh_int32(get() & value);
			}

			__compelled_inline_noseh qh_int32 __regcall operator|(const int value) const noexcept {
				return qh_int32(get() | value);
			}

			__compelled_inline_noseh qh_int32 __regcall operator%(const int value) const noexcept {
				return qh_int32(get() % value);
			}

			__compelled_inline_noseh qh_int32 __regcall operator^(const int value) const noexcept {
				return qh_int32(get() ^ value);
			}

			__compelled_inline_noseh qh_int32 __regcall operator<<(const int value) const noexcept {
				return qh_int32(get() << value);
			}

			__compelled_inline_noseh qh_int32 __regcall operator>>(const int value) const noexcept {
				return qh_int32(get() >> value);
			}

			__compelled_inline_noseh qh_int32& __regcall operator+=(const int value) noexcept {
				set(static_cast<int>(get() + value));
				return *this;
			}

			__compelled_inline_noseh qh_int32& __regcall operator-=(const int value) noexcept {
				set(static_cast<int>(get() - value));
				return *this;
			}

			__compelled_inline_noseh qh_int32& __regcall operator++() noexcept {
				operator+=(1i8);
				return *this;
			}

			__compelled_inline_noseh qh_int32& __regcall operator--() noexcept {
				operator-=(1i8);
				return *this;
			}

			__compelled_inline_noseh qh_int32& __regcall operator*=(const int value) noexcept {
				set(static_cast<int>(get() * value));
				return *this;
			}

			__compelled_inline_noseh qh_int32& __regcall operator/=(const int value) noexcept {
				set(static_cast<int>(get() / value));
				return *this;
			}

			__compelled_inline_noseh qh_int32& __regcall operator%=(const int value) noexcept {
				set(static_cast<int>(get() % value));
				return *this;
			}

			__compelled_inline_noseh qh_int32& __regcall operator^=(const int value) noexcept {
				set(static_cast<int>(get() ^ value));
				return *this;
			}

			__compelled_inline_noseh qh_int32& __regcall operator&=(const int value) noexcept {
				set(static_cast<int>(get() & value));
				return *this;
			}

			__compelled_inline_noseh qh_int32& __regcall operator|=(const int value) noexcept {
				set(static_cast<int>(get() | value));
				return *this;
			}

			__compelled_inline_noseh qh_int32& __regcall operator<<=(const int value) noexcept {
				set(static_cast<int>(get() << value));
				return *this;
			}

			__compelled_inline_noseh qh_int32& __regcall operator>>=(const int value) noexcept {
				set(static_cast<int>(get() >> value));
				return *this;
			}

			__compelled_inline_noseh qh_int32& __regcall operator=(const int value) noexcept {
				set(value);
				return *this;
			}

			__compelled_inline_noseh __regcall operator int() const noexcept {
				return get();
			}

			__compelled_inline_noseh ~qh_int32() noexcept { }
	#pragma endregion
		};

		class qh_uint32 {

		private:

	#pragma region Globals

			mutable std::uint32_t _value{};

			mutable qhash::qhash_cpu_t _hash{};

	#pragma endregion

		public:

	#pragma region CTOR

			__optimized_ctor qh_uint32(std::uint32_t value = 0) noexcept {

				if (!is_init)
					init_hash_t();

				set(value);
			}

	#pragma endregion

	#pragma region Accessors

			__compelled_inline_noseh std::uint32_t __regcall get() const noexcept {

				auto hash = qhash::qhash_cpu(reinterpret_cast<void*>(&_value), sizeof(_value));

				if (hash != _hash)
					violation_callback(qexcept::q_rogueaccess(this->_hash.hash_obj.hash, hash.hash_obj.hash), reinterpret_cast<void*>(&_value));

				auto _return = _value;

				return _return;
			}

			__compelled_inline_noseh void __regcall set(std::uint32_t value) noexcept {

				auto hash = qhash::qhash_cpu(&value, sizeof(value));

				this->_hash = hash;

				_value = value;
			}

			__compelled_inline_noseh decltype(_value)* get_raw_memory_address() const noexcept {
				return &_value;
			}

	#pragma endregion

	#pragma region Operators

			__compelled_inline_noseh qh_uint32 __regcall operator+(const std::uint32_t value) const noexcept {
				return qh_uint32(get() + value);
			};

			__compelled_inline_noseh qh_uint32 __regcall operator-(const std::uint32_t value) const noexcept {
				return qh_uint32(get() - value);
			}

			__compelled_inline_noseh qh_uint32 __regcall operator/(const std::uint32_t value) const noexcept {
				return qh_uint32(get() / value);
			}

			__compelled_inline_noseh qh_uint32 __regcall operator*(const std::uint32_t value) const noexcept {
				return qh_uint32(get() * value);
			}

			__compelled_inline_noseh qh_uint32 __regcall operator&(const std::uint32_t value) const noexcept {
				return qh_uint32(get() & value);
			}

			__compelled_inline_noseh qh_uint32 __regcall operator|(const std::uint32_t value) const noexcept {
				return qh_uint32(get() | value);
			}

			__compelled_inline_noseh qh_uint32 __regcall operator%(const std::uint32_t value) const noexcept {
				return qh_uint32(get() % value);
			}

			__compelled_inline_noseh qh_uint32 __regcall operator^(const std::uint32_t value) const noexcept {
				return qh_uint32(get() ^ value);
			}

			__compelled_inline_noseh qh_uint32 __regcall operator<<(const std::uint32_t value) const noexcept {
				return qh_uint32(get() << value);
			}

			__compelled_inline_noseh qh_uint32 __regcall operator>>(const std::uint32_t value) const noexcept {
				return qh_uint32(get() >> value);
			}

			__compelled_inline_noseh qh_uint32& __regcall operator+=(const std::uint32_t value) noexcept {
				set(static_cast<std::uint32_t>(get() + value));
				return *this;
			}

			__compelled_inline_noseh qh_uint32& __regcall operator-=(const std::uint32_t value) noexcept {
				set(static_cast<std::uint32_t>(get() - value));
				return *this;
			}

			__compelled_inline_noseh qh_uint32& __regcall operator++() noexcept {
				operator+=(1i8);
				return *this;
			}

			__compelled_inline_noseh qh_uint32& __regcall operator--() noexcept {
				operator-=(1i8);
				return *this;
			}

			__compelled_inline_noseh qh_uint32& __regcall operator*=(const std::uint32_t value) noexcept {
				set(static_cast<std::uint32_t>(get() * value));
				return *this;
			}

			__compelled_inline_noseh qh_uint32& __regcall operator/=(const std::uint32_t value) noexcept {
				set(static_cast<std::uint32_t>(get() / value));
				return *this;
			}

			__compelled_inline_noseh qh_uint32& __regcall operator%=(const std::uint32_t value) {
				set(static_cast<std::uint32_t>(get() % value));
				return *this;
			}

			__compelled_inline_noseh qh_uint32& __regcall operator^=(const std::uint32_t value) noexcept {
				set(static_cast<std::uint32_t>(get() ^ value));
				return *this;
			}

			__compelled_inline_noseh qh_uint32& __regcall operator&=(const std::uint32_t value) noexcept {
				set(static_cast<std::uint32_t>(get() & value));
				return *this;
			}

			__compelled_inline_noseh qh_uint32& __regcall operator|=(const std::uint32_t value) noexcept {
				set(static_cast<std::uint32_t>(get() | value));
				return *this;
			}

			__compelled_inline_noseh qh_uint32& __regcall operator<<=(const std::uint32_t value) noexcept {
				set(static_cast<std::uint32_t>(get() << value));
				return *this;
			}

			__compelled_inline_noseh qh_uint32& __regcall operator>>=(const std::uint32_t value) noexcept {
				set(static_cast<std::uint32_t>(get() >> value));
				return *this;
			}

			__compelled_inline_noseh qh_uint32& __regcall operator=(const std::uint32_t value) noexcept {
				set(value);
				return *this;
			}

			__compelled_inline_noseh __regcall operator std::uint32_t() const noexcept {
				return get();
			}

			__compelled_inline_noseh ~qh_uint32() noexcept { }
	#pragma endregion
		};

	#pragma endregion

	#pragma region 64-bit

	#ifdef _WIN64

		class qh_int64 {

		private:

	#pragma region Globals

			mutable std::int64_t _value{};

			mutable qhash::qhash_cpu_t _hash{};

	#pragma endregion

		public:

	#pragma region CTOR

			__optimized_ctor qh_int64(int64_t value = 0) noexcept {

				if (!is_init)
					init_hash_t();

				set(value);
			}

	#pragma endregion

	#pragma region Accessors

			int64_t __regcall get() const noexcept {

				auto hash = qhash::qhash_cpu(reinterpret_cast<void*>(&_value), sizeof(_value));

				if (hash != _hash)
					violation_callback(qexcept::q_rogueaccess(this->_hash.hash_obj.hash, hash.hash_obj.hash), reinterpret_cast<void*>(&_value)); // access violation executing location, make the argument for passing callback an rvalue ?

				auto _return = _value;

				return _return;
			}

			__compelled_inline_noseh void __regcall set(int64_t value) noexcept {

				auto hash = qhash::qhash_cpu(&value, sizeof(value));

				this->_hash = hash;

				_value = value;
			}

			__compelled_inline_noseh decltype(_value)* get_raw_memory_address() const noexcept {
				return &_value;
			}

	#pragma endregion

	#pragma region Operators

			__compelled_inline_noseh qh_int64 __regcall operator+(const std::int64_t value) const noexcept {
				return qh_int64(get() + value);
			};

			__compelled_inline_noseh qh_int64 __regcall operator-(const std::int64_t value) const noexcept {
				return qh_int64(get() - value);
			}

			__compelled_inline_noseh qh_int64 __regcall operator/(const std::int64_t value) const noexcept {
				return qh_int64(get() / value);
			}

			__compelled_inline_noseh qh_int64 __regcall operator*(const std::int64_t value) const noexcept {
				return qh_int64(get() * value);
			}

			__compelled_inline_noseh qh_int64 __regcall operator&(const std::int64_t value) const noexcept {
				return qh_int64(get() & value);
			}

			__compelled_inline_noseh qh_int64 __regcall operator|(const std::int64_t value) const noexcept {
				return qh_int64(get() | value);
			}

			__compelled_inline_noseh qh_int64 __regcall operator%(const std::int64_t value) const noexcept {
				return qh_int64(get() % value);
			}

			__compelled_inline_noseh qh_int64 __regcall operator^(const std::int64_t value) const noexcept {
				return qh_int64(get() ^ value);
			}

			__compelled_inline_noseh qh_int64 __regcall operator<<(const std::int64_t value) const noexcept {
				return qh_int64(get() << value);
			}

			__compelled_inline_noseh qh_int64 __regcall operator>>(const std::int64_t value) const noexcept {
				return qh_int64(get() >> value);
			}

			__compelled_inline_noseh qh_int64& __regcall operator+=(const std::int64_t value) noexcept {
				set(static_cast<int>(get() + value));
				return *this;
			}

			__compelled_inline_noseh qh_int64& __regcall operator-=(const std::int64_t value) noexcept {
				set(static_cast<int>(get() - value));
				return *this;
			}

			__compelled_inline_noseh qh_int64& __regcall operator++() noexcept {
				operator+=(1i8);
				return *this;
			}

			__compelled_inline_noseh qh_int64& __regcall operator--() noexcept {
				operator-=(1i8);
				return *this;
			}

			__compelled_inline_noseh qh_int64& __regcall operator*=(const std::int64_t value) noexcept {
				set(static_cast<std::int64_t>(get() * value));
				return *this;
			}

			__compelled_inline_noseh qh_int64& __regcall operator/=(const std::int64_t value) noexcept {
				set(static_cast<std::int64_t>(get() / value));
				return *this;
			}

			__compelled_inline_noseh qh_int64& __regcall operator%=(const std::int64_t value) noexcept {
				set(static_cast<std::int64_t>(get() % value));
				return *this;
			}

			__compelled_inline_noseh qh_int64& __regcall operator^=(const std::int64_t value) noexcept {
				set(static_cast<std::int64_t>(get() ^ value));
				return *this;
			}

			__compelled_inline_noseh qh_int64& __regcall operator&=(const std::int64_t value) noexcept {
				set(static_cast<std::int64_t>(get() & value));
				return *this;
			}

			__compelled_inline_noseh qh_int64& __regcall operator|=(const std::int64_t value) noexcept {
				set(static_cast<std::int64_t>(get() | value));
				return *this;
			}

			__compelled_inline_noseh qh_int64& __regcall operator<<=(const std::int64_t value) noexcept {
				set(static_cast<std::int64_t>(get() << value));
				return *this;
			}

			__compelled_inline_noseh qh_int64& __regcall operator>>=(const std::int64_t value) noexcept {
				set(static_cast<std::int64_t>(get() >> value));
				return *this;
			}

			__compelled_inline_noseh qh_int64& __regcall operator=(const std::int64_t value) noexcept {
				set(value);
				return *this;
			}

			__compelled_inline_noseh __regcall operator int() const noexcept {
				return get();
			}

			__compelled_inline_noseh ~qh_int64() noexcept { }
	#pragma endregion
		};

		class qh_uint64 {

		private:

	#pragma region Globals

			mutable std::uint64_t _value{};

			mutable qhash::qhash_cpu_t _hash{};

	#pragma endregion

		public:

	#pragma region CTOR

			__optimized_ctor qh_uint64(std::uint64_t value = 0) noexcept {

				if (!is_init)
					init_hash_t();

				set(value);
			}

	#pragma endregion

	#pragma region Accessors

			__compelled_inline_noseh std::uint64_t __regcall get() const noexcept {

				auto hash = qhash::qhash_cpu(reinterpret_cast<void*>(&_value), sizeof(_value));

				if (hash != _hash)
					violation_callback(qexcept::q_rogueaccess(this->_hash.hash_obj.hash, hash.hash_obj.hash), reinterpret_cast<void*>(&_value));

				auto _return = _value;

				return _return;
			}

			__compelled_inline_noseh void __regcall set(std::uint64_t value) noexcept {

				auto hash = qhash::qhash_cpu(&value, sizeof(value));

				this->_hash = hash;

				_value = value;
			}

			__compelled_inline_noseh decltype(_value)* get_raw_memory_address() const noexcept {
				return &_value;
			}

	#pragma endregion

	#pragma region Operators

			__compelled_inline_noseh qh_uint64 __regcall operator+(const std::uint64_t value) const noexcept {
				return qh_uint64(get() + value);
			};

			__compelled_inline_noseh qh_uint64 __regcall operator-(const std::uint64_t value) const noexcept {
				return qh_uint64(get() - value);
			}

			__compelled_inline_noseh qh_uint64 __regcall operator/(const std::uint64_t value) const noexcept {
				return qh_uint64(get() / value);
			}

			__compelled_inline_noseh qh_uint64 __regcall operator*(const std::uint64_t value) const noexcept {
				return qh_uint64(get() * value);
			}

			__compelled_inline_noseh qh_uint64 __regcall operator&(const std::uint64_t value) const noexcept {
				return qh_uint64(get() & value);
			}

			__compelled_inline_noseh qh_uint64 __regcall operator|(const std::uint64_t value) const noexcept {
				return qh_uint64(get() | value);
			}

			__compelled_inline_noseh qh_uint64 __regcall operator%(const std::uint64_t value) const noexcept {
				return qh_uint64(get() % value);
			}

			__compelled_inline_noseh qh_uint64 __regcall operator^(const std::uint64_t value) const noexcept {
				return qh_uint64(get() ^ value);
			}

			__compelled_inline_noseh qh_uint64 __regcall operator<<(const std::uint64_t value) const noexcept {
				return qh_uint64(get() << value);
			}

			__compelled_inline_noseh qh_uint64 __regcall operator>>(const std::uint64_t value) const noexcept {
				return qh_uint64(get() >> value);
			}

			__compelled_inline_noseh qh_uint64& __regcall operator+=(const std::uint64_t value) noexcept {
				set(static_cast<std::uint64_t>(get() + value));
				return *this;
			}

			__compelled_inline_noseh qh_uint64& __regcall operator-=(const std::uint64_t value) noexcept {
				set(static_cast<std::uint64_t>(get() - value));
				return *this;
			}

			__compelled_inline_noseh qh_uint64& __regcall operator++() noexcept {
				operator+=(1i8);
				return *this;
			}

			__compelled_inline_noseh qh_uint64& __regcall operator--() noexcept {
				operator-=(1i8);
				return *this;
			}

			__compelled_inline_noseh qh_uint64& __regcall operator*=(const std::uint64_t value) noexcept {
				set(static_cast<std::uint64_t>(get() * value));
				return *this;
			}

			__compelled_inline_noseh qh_uint64& __regcall operator/=(const std::uint64_t value) noexcept {
				set(static_cast<std::uint64_t>(get() / value));
				return *this;
			}

			__compelled_inline_noseh qh_uint64& __regcall operator%=(const std::uint64_t value) noexcept {
				set(static_cast<std::uint64_t>(get() % value));
				return *this;
			}

			__compelled_inline_noseh qh_uint64& __regcall operator^=(const std::uint64_t value) noexcept {
				set(static_cast<std::uint64_t>(get() ^ value));
				return *this;
			}

			__compelled_inline_noseh qh_uint64& __regcall operator&=(const std::uint64_t value) noexcept {
				set(static_cast<std::uint64_t>(get() & value));
				return *this;
			}

			__compelled_inline_noseh qh_uint64& __regcall operator|=(const std::uint64_t value) noexcept {
				set(static_cast<std::uint64_t>(get() | value));
				return *this;
			}

			__compelled_inline_noseh qh_uint64& __regcall operator<<=(const std::uint64_t value) noexcept {
				set(static_cast<std::uint64_t>(get() << value));
				return *this;
			}

			__compelled_inline_noseh qh_uint64& __regcall operator>>=(const std::uint64_t value) noexcept {
				set(static_cast<std::uint64_t>(get() >> value));
				return *this;
			}

			__compelled_inline_noseh qh_uint64& __regcall operator=(const std::uint64_t value) noexcept {
				set(value);
				return *this;
			}

			__compelled_inline_noseh __regcall operator std::uint64_t() const noexcept {
				return get();
			}

			__compelled_inline_noseh ~qh_uint64() noexcept { }
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

			mutable float _value;

			mutable qhash::qhash_cpu_t _hash{};

	#pragma endregion

		public:

	#pragma region CTOR

			__compelled_inline_noseh __fpcall qh_float(float value = 0.0f) noexcept {

				if (!is_init)
					init_hash_t();

				set(value);
			}

	#pragma endregion

	#pragma region Accessors

			__compelled_inline_noseh float __regcall get() const noexcept {

				auto hash = qhash::qhash_cpu(reinterpret_cast<void*>(&_value), sizeof(_value));

				if (hash != _hash)
					violation_callback(qexcept::q_rogueaccess(this->_hash.hash_obj.hash, hash.hash_obj.hash), reinterpret_cast<void*>(&_value));

				auto _return = _value;

				return _return;
			}

			__compelled_inline_noseh void __regcall set(float value) noexcept {

				auto hash = qhash::qhash_cpu(&value, sizeof(value));

				this->_hash = hash;

				_value = value;
			}

			__compelled_inline_noseh decltype(_value)* get_raw_memory_address() const noexcept {
				return &_value;
			}

	#pragma endregion

	#pragma region Operators

			__compelled_inline_noseh qh_float __fpcall operator+(const float value) const noexcept {
				return qh_float(get() + value);
			};

			__compelled_inline_noseh qh_float __fpcall operator-(const float value) const noexcept {
				return qh_float(get() - value);
			}

			__compelled_inline_noseh qh_float __fpcall operator/(const float value) const noexcept {
				return qh_float(get() / value);
			}

			__compelled_inline_noseh qh_float __fpcall operator*(const float value) const noexcept {
				return qh_float(get() * value);
			}

			__compelled_inline_noseh qh_float& __fpcall operator+=(const float value) noexcept {
				set(static_cast<float>(get() + value));
				return *this;
			}

			__compelled_inline_noseh qh_float& __fpcall operator-=(const float value) noexcept {
				set(static_cast<float>(get() - value));
				return *this;
			}

			__compelled_inline_noseh qh_float& __stackcall operator++() noexcept {
				operator+=(1.f);
				return *this;
			}

			__compelled_inline_noseh qh_float& __stackcall operator--() noexcept {
				operator-=(1.f);
				return *this;
			}

			__compelled_inline_noseh qh_float& __fpcall operator*=(const float value) noexcept {
				set(static_cast<float>(get() * value));
				return *this;
			}

			__compelled_inline_noseh qh_float& __fpcall operator/=(const float value) noexcept {
				set(static_cast<float>(get() / value));
				return *this;
			}

			__compelled_inline_noseh qh_float& __fpcall operator=(const float value) noexcept {
				set(value);
				return *this;
			}

			__compelled_inline_noseh __stackcall operator float() const noexcept {
				return get();
			}

			__compelled_inline_noseh __stackcall ~qh_float() noexcept { }

	#pragma endregion
		};

	#pragma endregion

	#pragma region 64-bit

	#ifdef _WIN64

		class qh_double {

		private:

	#pragma region Globals

			mutable double _value;

			mutable qhash::qhash_cpu_t _hash{};

	#pragma endregion

		public:

	#pragma region CTOR

			__compelled_inline_noseh __fpcall qh_double(double value = static_cast<double>(0.0f)) noexcept {

				if (!is_init)
					init_hash_t();

				set(value);
			}

	#pragma endregion

	#pragma region Accessors

			__compelled_inline_noseh double __fpcall get() const noexcept {

				auto hash = qhash::qhash_cpu(reinterpret_cast<void*>(&_value), sizeof(_value));

				if (hash != _hash)
					violation_callback(qexcept::q_rogueaccess(this->_hash.hash_obj.hash, hash.hash_obj.hash), reinterpret_cast<void*>(&_value));

				auto _return = _value;

				return _return;
			}

			__compelled_inline_noseh void __fpcall set(double value) noexcept {

				auto hash = qhash::qhash_cpu(&value, sizeof(value));

				this->_hash = hash;

				_value = value;
			}

			__compelled_inline_noseh decltype(_value)* get_raw_memory_address() const noexcept {
				return &_value;
			}

	#pragma endregion

	#pragma region Operators

			__compelled_inline_noseh qh_double __fpcall operator+(const double value) const noexcept {
				return qh_double(get() + value);
			};

			__compelled_inline_noseh qh_double __fpcall operator-(const double value) const noexcept {
				return qh_double(get() - value);
			}

			__compelled_inline_noseh qh_double __fpcall operator/(const double value) const noexcept {
				return qh_double(get() / value);
			}

			__compelled_inline_noseh qh_double __fpcall operator*(const double value) const noexcept {
				return qh_double(get() * value);
			}

			__compelled_inline_noseh qh_double& __fpcall operator+=(const double value) noexcept {
				set(static_cast<double>(get() + value));
				return *this;
			}

			__compelled_inline_noseh qh_double& __fpcall operator-=(const double value) noexcept {
				set(static_cast<double>(get() - value));
				return *this;
			}

			__compelled_inline_noseh qh_double& __stackcall operator++() noexcept {
				operator+=(1.f);
				return *this;
			}

			__compelled_inline_noseh qh_double& __stackcall operator--() noexcept {
				operator-=(1.f);
				return *this;
			}

			__compelled_inline_noseh qh_double& __fpcall operator*=(const double value) noexcept {
				set(static_cast<double>(get() * value));
				return *this;
			}

			__compelled_inline_noseh qh_double& __fpcall operator/=(const double value) noexcept {
				set(static_cast<double>(get() / value));
				return *this;
			}

			__compelled_inline_noseh qh_double& __fpcall operator=(const double value) noexcept {
				set(value);
				return *this;
			}

			__compelled_inline_noseh __stackcall operator double() const noexcept {
				return get();
			}

			__compelled_inline_noseh __stackcall ~qh_double() noexcept { }
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

			mutable __m128 _value;

			mutable qhash::qhash_cpu_t _hash{};

	#pragma endregion

		public:

	#pragma region CTOR

			__compelled_inline_noseh __fpcall qh_m128(__m128 value) noexcept {

				if (!is_init)
					init_hash_t();

				set(value);
			}

	#pragma endregion

	#pragma region Accessors

			__compelled_inline_noseh __m128 __fpcall get() const noexcept {

				auto hash = qhash::qhash_cpu(reinterpret_cast<void*>(&_value), sizeof(_value));

				if (hash != _hash)
					violation_callback(qexcept::q_rogueaccess(this->_hash.hash_obj.hash, hash.hash_obj.hash), reinterpret_cast<void*>(&_value));

				auto _return = _value;

				return _return;
			}

			__compelled_inline_noseh void __fpcall set(__m128 value) noexcept {

				auto hash = qhash::qhash_cpu(&value, sizeof(value));

				this->_hash = hash;

				_value = value;
			}

			__compelled_inline_noseh decltype(_value)* get_raw_memory_address() const noexcept {
				return &_value;
			}

	#pragma endregion

	#pragma region Operators

	#ifdef __clang__

			__compelled_inline_noseh qh_m128 __fpcall operator+(const __m128 value) const noexcept {
				return qh_m128(get() + value);
			};

			__compelled_inline_noseh qh_m128 __fpcall operator-(const __m128 value) const noexcept {
				return qh_m128(get() - value);
			}

			__compelled_inline_noseh qh_m128 __fpcall operator/(const __m128 value) const noexcept {
				return qh_m128(get() / value);
			}

			__compelled_inline_noseh qh_m128 __fpcall operator*(const __m128 value) const noexcept {
				return qh_m128(get() * value);
			}

			__compelled_inline_noseh qh_m128& __fpcall operator+=(const __m128 value) noexcept {
				set(static_cast<__m128>(get() + value));
				return *this;
			}

			__compelled_inline_noseh qh_m128& __fpcall operator-=(const __m128 value) noexcept {
				set(static_cast<__m128>(get() - value));
				return *this;
			}

			__compelled_inline_noseh qh_m128& __fpcall operator*=(const __m128 value) noexcept {
				set(static_cast<__m128>(get() * value));
				return *this;
			}

			__compelled_inline_noseh qh_m128& __fpcall operator/=(const __m128 value) noexcept {
				set(static_cast<__m128>(get() / value));
				return *this;
			}

	#endif

			__compelled_inline_noseh qh_m128& __fpcall operator=(const __m128 value) noexcept {
				set(value);
				return *this;
			}

			__compelled_inline_noseh __fpcall operator __m128() const noexcept {
				return get();
			}

			__compelled_inline_noseh ~qh_m128() noexcept { }
	#pragma endregion
		};

	#ifdef __SSE2__

		class qh_m128i {

		private:

	#pragma region Globals

			mutable __m128i _value;

			mutable qhash::qhash_cpu_t _hash{};

	#pragma endregion

		public:

	#pragma region CTOR

			__compelled_inline_noseh __fpcall qh_m128i(__m128i value) {

				if (!is_init)
					init_hash_t();

				set(value);
			}

	#pragma endregion

	#pragma region Accessors

			__compelled_inline_noseh __m128i __fpcall get() const {

				auto hash = qhash::qhash_cpu(reinterpret_cast<void*>(&_value), sizeof(_value));

				if (hash != _hash)
					violation_callback(qexcept::q_rogueaccess(this->_hash.hash_obj.hash, hash.hash_obj.hash), reinterpret_cast<void*>(&_value));

				auto _return = _value;

				return _return;
			}

			__compelled_inline_noseh void __fpcall set(__m128i value) {

				auto hash = qhash::qhash_cpu(&value, sizeof(value));

				this->_hash = hash;

				_value = value;
			}

			__compelled_inline_noseh decltype(_value)* get_raw_memory_address() {
				return &_value;
			}

	#pragma endregion

	#pragma region Operators

	#ifdef __clang__

			__compelled_inline_noseh qh_m128i __fpcall operator+(const __m128i value) const {
				return qh_m128i(get() + value);
			};

			__compelled_inline_noseh qh_m128i __fpcall operator-(const __m128i value) const {
				return qh_m128i(get() - value);
			}

			__compelled_inline_noseh qh_m128i __fpcall operator/(const __m128i value) const {
				return qh_m128i(get() / value);
			}

			__compelled_inline_noseh qh_m128i __fpcall operator*(const __m128i value) const {
				return qh_m128i(get() * value);
			}

			__compelled_inline_noseh qh_m128i& __fpcall operator+=(const __m128i value) {
				set(static_cast<__m128i>(get() + value));
				return *this;
			}

			__compelled_inline_noseh qh_m128i& __fpcall operator-=(const __m128i value) {
				set(static_cast<__m128i>(get() - value));
				return *this;
			}

			__compelled_inline_noseh qh_m128i& __fpcall operator*=(const __m128i value) {
				set(static_cast<__m128i>(get() * value));
				return *this;
			}

			__compelled_inline_noseh qh_m128i& __fpcall operator/=(const __m128i value) {
				set(static_cast<__m128i>(get() / value));
				return *this;
			}

	#endif

			__compelled_inline_noseh qh_m128i& __fpcall operator=(const __m128i value) noexcept {
				set(value);
				return *this;
			}

			__compelled_inline_noseh __stackcall operator __m128i() const noexcept {
				return get();
			}

			__compelled_inline_noseh ~qh_m128i() { }
	#pragma endregion
		};

		class qh_m128d {

		private:

	#pragma region Globals

			mutable __m128d _value;

			mutable qhash::qhash_cpu_t _hash{};

	#pragma endregion

		public:

	#pragma region CTOR

			__compelled_inline_noseh __fpcall qh_m128d(__m128d value) noexcept {

				if (!is_init)
					init_hash_t();

				set(value);
			}

	#pragma endregion

	#pragma region Accessors

			__compelled_inline_noseh __m128d __fpcall get() const noexcept {

				auto hash = qhash::qhash_cpu(reinterpret_cast<void*>(&_value), sizeof(_value));

				if (hash != _hash)
					violation_callback(qexcept::q_rogueaccess(this->_hash.hash_obj.hash, hash.hash_obj.hash), reinterpret_cast<void*>(&_value));

				auto _return = _value;

				return _return;
			}

			__compelled_inline_noseh void __fpcall set(__m128d value) noexcept {

				auto hash = qhash::qhash_cpu(&value, sizeof(value));

				this->_hash = hash;

				_value = value;
			}

			__compelled_inline_noseh decltype(_value)* get_raw_memory_address() const noexcept {
				return &_value;
			}

	#pragma endregion

	#pragma region Operators

	#ifdef __clang__

			__compelled_inline_noseh qh_m128d __fpcall operator+(const __m128d value) const noexcept {
				return qh_m128d(get() + value);
			};

			__compelled_inline_noseh qh_m128d __fpcall operator-(const __m128d value) const noexcept {
				return qh_m128d(get() - value);
			}

			__compelled_inline_noseh qh_m128d __fpcall operator/(const __m128d value) const noexcept {
				return qh_m128d(get() / value);
			}

			__compelled_inline_noseh qh_m128d __fpcall operator*(const __m128d value) const noexcept {
				return qh_m128d(get() * value);
			}

			__compelled_inline_noseh qh_m128d& __fpcall operator+=(const __m128d value) noexcept {
				set(static_cast<__m128d>(get() + value));
				return *this;
			}

			__compelled_inline_noseh qh_m128d& __fpcall operator-=(const __m128d value) noexcept {
				set(static_cast<__m128d>(get() - value));
				return *this;
			}

			__compelled_inline_noseh qh_m128d& __fpcall operator*=(const __m128d value) noexcept {
				set(static_cast<__m128d>(get() * value));
				return *this;
			}

			__compelled_inline_noseh qh_m128d& __fpcall operator/=(const __m128d value) noexcept {
				set(static_cast<__m128d>(get() / value));
				return *this;
			}

	#endif

			__compelled_inline_noseh qh_m128d& __fpcall operator=(const __m128d value) noexcept {
				set(value);
				return *this;
			}

			__compelled_inline_noseh __fpcall operator __m128d() const noexcept {
				return get();
			}

			__compelled_inline_noseh ~qh_m128d() noexcept { }
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

			mutable __m256 _value;

			mutable qhash::qhash_cpu_t _hash{};

	#pragma endregion

		public:

	#pragma region CTOR

			__compelled_inline_noseh __fpcall qh_m256(__m256 value) noexcept {

				if (!is_init)
					init_hash_t();

				set(value);
			}

	#pragma endregion

	#pragma region Accessors

			__compelled_inline_noseh __m256 __fpcall get() const noexcept {

				auto hash = qhash::qhash_cpu(reinterpret_cast<void*>(&_value), sizeof(_value));

				if (hash != _hash)
					violation_callback(qexcept::q_rogueaccess(this->_hash.hash_obj.hash, hash.hash_obj.hash), reinterpret_cast<void*>(&_value));

				auto _return = _value;

				return _return;
			}

			__compelled_inline_noseh void __fpcall set(__m256 value) noexcept {

				auto hash = qhash::qhash_cpu(&value, sizeof(value));

				this->_hash = hash;

				_value = value;
			}

			__compelled_inline_noseh decltype(_value)* get_raw_memory_address() const noexcept {
				return &_value;
			}

	#pragma endregion

	#pragma region Operators

	#ifdef __clang__

			__compelled_inline_noseh qh_m256 __fpcall operator+(const __m256 value) const noexcept {
				return qh_m256(get() + value);
			};

			__compelled_inline_noseh qh_m256 __fpcall operator-(const __m256 value) const noexcept {
				return qh_m256(get() - value);
			}

			__compelled_inline_noseh qh_m256 __fpcall operator/(const __m256 value) const noexcept {
				return qh_m256(get() / value);
			}

			__compelled_inline_noseh qh_m256 __fpcall operator*(const __m256 value) const noexcept {
				return qh_m256(get() * value);
			}

			__compelled_inline_noseh qh_m256& __fpcall operator+=(const __m256 value) noexcept {
				set(static_cast<__m256>(get() + value));
				return *this;
			}

			__compelled_inline_noseh qh_m256& __fpcall operator-=(const __m256 value) noexcept {
				set(static_cast<__m256>(get() - value));
				return *this;
			}

			__compelled_inline_noseh qh_m256& __fpcall operator*=(const __m256 value) noexcept {
				set(static_cast<__m256>(get() * value));
				return *this;
			}

			__compelled_inline_noseh qh_m256& __fpcall operator/=(const __m256 value) noexcept {
				set(static_cast<__m256>(get() / value));
				return *this;
			}

	#endif

			__compelled_inline_noseh qh_m256& __fpcall operator=(const __m256 value) noexcept {
				set(value);
				return *this;
			}

			__compelled_inline_noseh __fpcall operator __m256() const noexcept {
				return get();
			}

			__compelled_inline_noseh ~qh_m256() noexcept { }
	#pragma endregion
		};

		class qh_m256i {

		private:

	#pragma region Globals

			mutable __m256i _value;

			mutable qhash::qhash_cpu_t _hash{};

	#pragma endregion

		public:

	#pragma region CTOR

			__compelled_inline_noseh __fpcall qh_m256i(__m256i value) noexcept {

				if (!is_init)
					init_hash_t();

				set(value);
			}

	#pragma endregion

	#pragma region Accessors

			__compelled_inline_noseh __m256i __fpcall get() const noexcept {

				auto hash = qhash::qhash_cpu(reinterpret_cast<void*>(&_value), sizeof(_value));

				if (hash != _hash)
					violation_callback(qexcept::q_rogueaccess(this->_hash.hash_obj.hash, hash.hash_obj.hash), reinterpret_cast<void*>(&_value));

				auto _return = _value;

				return _return;
			}

			__compelled_inline_noseh void __fpcall set(__m256i value) noexcept {

				auto hash = qhash::qhash_cpu(&value, sizeof(value));

				this->_hash = hash;

				_value = value;
			}

			__compelled_inline_noseh decltype(_value)* get_raw_memory_address() const noexcept {
				return &_value;
			}

	#pragma endregion

	#pragma region Operators

	#ifdef __clang__

			__compelled_inline_noseh qh_m256i __fpcall operator+(const __m256i value) const noexcept {
				return qh_m256i(get() + value);
			};

			__compelled_inline_noseh qh_m256i __fpcall operator-(const __m256i value) const noexcept {
				return qh_m256i(get() - value);
			}

			__compelled_inline_noseh qh_m256i __fpcall operator/(const __m256i value) const noexcept {
				return qh_m256i(get() / value);
			}

			__compelled_inline_noseh qh_m256i __fpcall operator*(const __m256i value) const noexcept {
				return qh_m256i(get() * value);
			}

			__compelled_inline_noseh qh_m256i& __fpcall operator+=(const __m256i value) noexcept {
				set(static_cast<__m256i>(get() + value));
				return *this;
			}

			__compelled_inline_noseh qh_m256i& __fpcall operator-=(const __m256i value) noexcept {
				set(static_cast<__m256i>(get() - value));
				return *this;
			}

			__compelled_inline_noseh qh_m256i& __fpcall operator*=(const __m256i value) noexcept {
				set(static_cast<__m256i>(get() * value));
				return *this;
			}

			__compelled_inline_noseh qh_m256i& __fpcall operator/=(const __m256i value) noexcept {
				set(static_cast<__m256i>(get() / value));
				return *this;
			}

	#endif

			__compelled_inline_noseh qh_m256i& __fpcall operator=(const __m256i value) noexcept {
				set(value);
				return *this;
			}

			__compelled_inline_noseh __fpcall operator __m256i() const noexcept {
				return get();
			}

			__compelled_inline_noseh ~qh_m256i() noexcept { }
	#pragma endregion
		};

		class qh_m256d {

		private:

	#pragma region Globals

			mutable __m256d _value;

			mutable qhash::qhash_cpu_t _hash{};

	#pragma endregion

		public:

	#pragma region CTOR

			__compelled_inline_noseh __fpcall qh_m256d(__m256d value) noexcept {

				if (!is_init)
					init_hash_t();

				set(value);
			}

	#pragma endregion

	#pragma region Accessors

			__compelled_inline_noseh __m256d __fpcall get() const noexcept {

				auto hash = qhash::qhash_cpu(reinterpret_cast<void*>(&_value), sizeof(_value));

				if (hash != _hash)
					violation_callback(qexcept::q_rogueaccess(this->_hash.hash_obj.hash, hash.hash_obj.hash), reinterpret_cast<void*>(&_value));

				auto _return = _value;

				return _return;
			}

			__compelled_inline_noseh void __fpcall set(__m256d value) noexcept {

				auto hash = qhash::qhash_cpu(&value, sizeof(value));

				this->_hash = hash;

				_value = value;
			}

			__compelled_inline_noseh decltype(_value)* get_raw_memory_address() noexcept {
				return &_value;
			}

	#pragma endregion

	#pragma region Operators

	#ifdef __clang__

			__compelled_inline_noseh qh_m256d __fpcall operator+(const __m256d value) const noexcept {
				return qh_m256d(get() + value);
			};

			__compelled_inline_noseh qh_m256d __fpcall operator-(const __m256d value) const noexcept {
				return qh_m256d(get() - value);
			}

			__compelled_inline_noseh qh_m256d __fpcall operator/(const __m256d value) const noexcept {
				return qh_m256d(get() / value);
			}

			__compelled_inline_noseh qh_m256d __fpcall operator*(const __m256d value) const noexcept {
				return qh_m256d(get() * value);
			}

			__compelled_inline_noseh qh_m256d& __fpcall operator+=(const __m256d value) noexcept {
				set(static_cast<__m256d>(get() + value));
				return *this;
			}

			__compelled_inline_noseh qh_m256d& __fpcall operator-=(const __m256d value) noexcept {
				set(static_cast<__m256d>(get() - value));
				return *this;
			}

			__compelled_inline_noseh qh_m256d& __fpcall operator*=(const __m256d value) noexcept {
				set(static_cast<__m256d>(get() * value));
				return *this;
			}

			__compelled_inline_noseh qh_m256d& __fpcall operator/=(const __m256d value) noexcept {
				set(static_cast<__m256d>(get() / value));
				return *this;
			}

	#endif

			__compelled_inline_noseh qh_m256d& __fpcall operator=(const __m256d value) noexcept {
				set(value);
				return *this;
			}

			__compelled_inline_noseh __fpcall operator __m256d() const noexcept {
				return get();
			}

			__compelled_inline_noseh __stackcall ~qh_m256d() noexcept { }
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

			mutable std::string _value;

			mutable qhash::qhash_cpu_t _hash{};

	#pragma endregion

		public:

	#pragma region CTOR

			__compelled_inline_noseh __stackcall qh_string(const std::string value = "") noexcept {

				if (!is_init)
					init_hash_t();

				set(value);
			}

	#pragma endregion

	#pragma region Accessors

			__compelled_inline_noseh std::string __regcall get() const noexcept {

				auto hash = qhash::qhash_cpu(reinterpret_cast<void*>(const_cast<char*>(_value.c_str())), sizeof(char) * _value.length());

				if (hash != _hash)
					violation_callback(qexcept::q_rogueaccess(this->_hash.hash_obj.hash, hash.hash_obj.hash), reinterpret_cast<void*>(&_value));

				return _value;
			}

			__compelled_inline_noseh void __regcall set(std::string value) noexcept {

				auto hash = qhash::qhash_cpu(const_cast<char*>(value.c_str()), sizeof(char) * value.length());

				this->_hash = hash;

				_value = value;
			}

			__compelled_inline_noseh decltype(_value)* __stackcall get_raw_memory_address() noexcept {
				return &_value;
			}

	#pragma endregion

	#pragma region Operators

			__compelled_inline_noseh qh_string __stackcall operator+(const std::string& value) const noexcept {
				return qh_string(get() + value);
			}

			__compelled_inline_noseh qh_string& __stackcall operator+=(const std::string& value) noexcept {
				set(static_cast<std::string>(get() + value));
				return *this;
			}

			__compelled_inline_noseh qh_string& __stackcall operator=(const std::string value) noexcept {
				set(value);
				return *this;
			}

			__compelled_inline_noseh __stackcall operator std::string() const noexcept {
				return get();
			}

			__compelled_inline_noseh __stackcall ~qh_string() noexcept { }

	#pragma endregion
		};

	#pragma endregion

	#pragma region Wide String

		class qh_wstring {

		private:

	#pragma region Encrypted value

			mutable std::wstring _value = L"";

			mutable qhash::qhash_cpu_t _hash{};

	#pragma endregion

		public:

	#pragma region CTOR

			__compelled_inline_noseh __stackcall qh_wstring(const std::wstring& value = L"") noexcept {

				if (!is_init)
					init_hash_t();

				set(value);
			}

	#pragma endregion

	#pragma region Accessors

			__compelled_inline_noseh std::wstring __regcall get() const noexcept {

				auto hash = qhash::qhash_cpu(reinterpret_cast<void*>(const_cast<wchar_t*>(_value.c_str())), sizeof(wchar_t) * _value.length());

				if (hash != _hash)
					violation_callback(qexcept::q_rogueaccess(this->_hash.hash_obj.hash, hash.hash_obj.hash), reinterpret_cast<void*>(&_value));

				auto _return = _value;

				return _return;
			}

			__compelled_inline_noseh void __regcall set(std::wstring value) noexcept {

				auto hash = qhash::qhash_cpu(const_cast<wchar_t*>(value.c_str()), sizeof(wchar_t) * value.length());

				this->_hash = hash;

				_value = value;
			}

			__compelled_inline_noseh decltype(_value)* __stackcall get_raw_memory_address()const noexcept {
				return &_value;
			}

	#pragma endregion

	#pragma region Operators

			__compelled_inline_noseh qh_wstring __stackcall operator+(const std::wstring& value) const noexcept {
				return qh_wstring(get() + value);
			}

			__compelled_inline_noseh qh_wstring& __stackcall operator+=(const std::wstring& value) noexcept {
				set(static_cast<std::wstring>(get() + value));
				return *this;
			}

			__compelled_inline_noseh qh_wstring& __stackcall operator=(const std::wstring& value) noexcept {
				set(value);
				return *this;
			}

			__compelled_inline_noseh __stackcall operator std::wstring() const noexcept {
				return get();
			}

			__compelled_inline_noseh __stackcall ~qh_wstring() noexcept { }

	#pragma endregion
		};

	#pragma endregion

	#pragma region Heap Allocation

		class qh_malloc {

		private:

	#pragma region Globals

			mutable void* allocation;
			mutable size_t allocation_size;

			mutable qhash::qhash_cpu_t _hash{};

	#pragma endregion

	#pragma region Subscript proxy

			// nested class to support subscript assignment
			class index_proxy {

			private:

	#pragma region Globals

				qh_malloc& parent;
				size_t index;

	#pragma endregion

			public:
	#pragma region Ctor

				index_proxy(const std::size_t index_, qh_malloc& instance) : index(index_), parent(instance) { }

	#pragma endregion

	#pragma region Operator overrides

				__compelled_inline_noseh std::uint8_t& __regcall operator=(std::uint8_t value) noexcept {
					parent.set(index, value);
					return value;   // return the passed assignment value rather than using up absurd resources to decrypt, re-encrypt everything using get()
				}

				__compelled_inline_noseh __regcall operator std::uint8_t() const noexcept {
					return parent.get(index);
				}

	#pragma endregion
			};

	#pragma endregion

		public:

	#pragma region Ctor

			__compelled_inline_noseh __regcall qh_malloc(const size_t size = 0) : allocation_size(size) {

				if (!size)
					return;

				if (!is_init)
					init_hash_t();

				auto alloc = malloc(size);

				swap(alloc, size);

				if (!allocation)
					throw qexcept::q_badalloc();
			}

	#pragma endregion

	#pragma region Get / Set

			__compelled_inline_noseh bool __regcall get(void* destination, uintptr_t offset, size_t length) const noexcept {

				if (!allocation || !destination)
					return false;

				auto hash = qhash::qhash_cpu(allocation, allocation_size);

				if (hash != _hash) {
					violation_callback(qexcept::q_rogueaccess(_hash.hash_obj.hash, hash.hash_obj.hash), allocation);
					return false;
				}

				memcpy(destination, reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(allocation) + offset), length);

				return true;
			}

			__compelled_inline_noseh char __regcall get(uintptr_t offset) const noexcept {

				char _return{};

				if (!get(&_return, 0, sizeof(_return)))
					return NULL;

				return _return;
			}

			__compelled_inline_noseh void* __stackcall get() const noexcept {

				auto alloc_new = malloc(allocation_size);

				if (!alloc_new)
					return nullptr;

				if (!get(alloc_new, 0, allocation_size)) {

					free(alloc_new);

					return nullptr;
				}

				return alloc_new;
			}

			__compelled_inline_noseh bool __regcall set(void* source, uintptr_t offset, size_t length) noexcept {

				if (!allocation || !source)
					return false;

				memcpy(reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(allocation) + offset), source, length);

				_hash = qhash::qhash_cpu(allocation, allocation_size);

				return true;
			}

			__compelled_inline_noseh bool __regcall set(uintptr_t index, byte value) noexcept {

				if (!set(&value, index, sizeof(value)))
					return false;

				return true;
			}

	#pragma endregion

	#pragma region Property Accessors

			__compelled_inline_noseh size_t __stackcall length() const noexcept {

				return allocation_size;
			}

			__compelled_inline_noseh void* __stackcall get_raw_memory_address() const noexcept {

				return allocation;
			}

	#pragma endregion

	#pragma region Utility functions

			__compelled_inline_noseh const bool __stackcall zero() noexcept {

				auto alloc_z = malloc(allocation_size);

				if (!alloc_z)
					return false;

				RtlZeroMemory(alloc_z, allocation_size);

				set(alloc_z, 0, allocation_size);

				free(alloc_z);

				return true;
			}

			__compelled_inline_noseh const bool __regcall reallocate(size_t size) noexcept {

				auto alloc_r = realloc(allocation, size);

				if (!alloc_r)
					return false;

				allocation = std::move(alloc_r);

				allocation_size = size;

				_hash = qhash::qhash_cpu(allocation, size);

				return true;
			}

			__compelled_inline_noseh const bool __regcall swap(void* allocation_, size_t size) noexcept {

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

			__compelled_inline_noseh index_proxy __regcall operator[](size_t index) noexcept {
				return index_proxy(index, *this);
			}

	#pragma endregion

	#pragma region Destructor

			__compelled_inline_noseh __stackcall ~qh_malloc() noexcept {

				if (allocation) {
					free(allocation);
					allocation = nullptr;
				}
			}

	#pragma endregion
		};

	#pragma endregion

	}  

#pragma region Static Declarators

	volatile qcallback::qmem_exception_rogue_c qtype_hash::violation_callback;

	bool qtype_hash::is_init = false;

#pragma endregion
} 

#endif