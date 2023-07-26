#ifndef HASH_T_H
#define HASH_T_H

/* TODO: make a thread pooling system to limit thread count, make each thread cover X amount of data  */

#pragma region Imports

#include <string>

#include "../../qhash/qhash.hpp"
#include "../../qbase/qbase.hpp"

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

namespace qengine {

	namespace qhash_t {
	   /*
	   /***************************************************************************************************************
	   *																											 *
	   *  QHash_T is the lower wrapper of the polymorphic type engine which ensures secure data access and integrity *
	   *																											 *
	   ****************************************************************************************************************
	   */

	#pragma region Globals

		extern qcallback::qmem_exception_rogue_c violation_callback;

		extern bool is_init;

	#pragma endregion

	#pragma region Global Static Methods / Callbacks

		static __jmpout void __fastcall violation_callback_d(qexcept::q_rogueaccess except, void* data) {

			if (except.id != qexcept::MEMORY_ALTERATION) // ensure this callback has been raised due to memory alteration
				return;
		}

		static __forceinline void __fastcall set_memory_violation_callback(qcallback::qmem_exception_rogue_c callback) {
			violation_callback = callback;
		}

		static __forceinline void __fastcall init_hash_t(qcallback::qmem_exception_rogue_c&& callback = violation_callback_d) {

			violation_callback = callback;

			is_init = true;
		}

	#pragma endregion

	#pragma region Types

	#pragma region WORD

	#pragma region 8-bit

		class h_int8{

		private:

	#pragma region Globals

			mutable char _value{};

			mutable qhash::qhash_cpu_t _hash{};

	#pragma endregion

		public:

	#pragma region CTOR

			__fastcall h_int8(char value) {

				if (!is_init)
					init_hash_t();

				set(value);
			}

			__forceinline __cdecl h_int8() {
			
				if (!is_init)
					init_hash_t();

				set(0); 
			}

	#pragma endregion

	#pragma region Accessors

			__forceinline char __fastcall get() const {

				auto hash = qhash::qhash_cpu(reinterpret_cast<void*>(&_value), sizeof(_value));

				if (hash != _hash)
					violation_callback(qexcept::q_rogueaccess(this->_hash.hash_obj.hash, hash.hash_obj.hash), reinterpret_cast<void*>(&_value));

				auto _return = _value;

				return _return;
			}

			__forceinline void __fastcall set(char value) {

				auto hash = qhash::qhash_cpu(&value, sizeof(value));

				this->_hash = hash;

				_value = value;
			}

			__forceinline decltype(_value)* get_raw_memory_address() {
				return &_value;
			}

	#pragma endregion

	#pragma region Operators

			__forceinline h_int8 __fastcall operator+(const char value) const {
				return h_int8(get() + value);
			};

			__forceinline h_int8 __fastcall operator-(const char value) const {
				return h_int8(get() - value);
			}

			__forceinline h_int8 __fastcall operator/(const char value) const {
				return h_int8(get() / value);
			}

			__forceinline h_int8 __fastcall operator*(const char value) const {
				return h_int8(get() * value);
			}

			__forceinline h_int8 __fastcall operator&(const char value) const {
				return h_int8(get() & value);
			}

			__forceinline h_int8 __fastcall operator|(const char value) const {
				return h_int8(get() | value);
			}

			__forceinline h_int8 __fastcall operator%(const char value) const {
				return h_int8(get() % value);
			}

			__forceinline h_int8 __fastcall operator^(const char value) const {
				return h_int8(get() ^ value);
			}

			__forceinline h_int8 __fastcall operator<<(const char value) const {
				return h_int8(get() << value);
			}

			__forceinline h_int8 __fastcall operator>>(const char value) const {
				return h_int8(get() >> value);
			}

			__forceinline h_int8& __fastcall operator+=(const char value) {
				set(static_cast<char>(get() + value));
				return *this;
			}

			__forceinline h_int8& __fastcall operator-=(const char value) {
				set(static_cast<char>(get() - value));
				return *this;
			}

			__forceinline h_int8& __fastcall operator++() {
				operator+=(1i8);
				return *this;
			}

			__forceinline h_int8& __fastcall operator--() {
				operator-=(1i8);
				return *this;
			}

			__forceinline h_int8& __fastcall operator*=(const char value) {
				set(static_cast<char>(get() * value));
				return *this;
			}

			__forceinline h_int8& __fastcall operator/=(const char value) {
				set(static_cast<char>(get() / value));
				return *this;
			}

			__forceinline h_int8& __fastcall operator%=(const char value) {
				set(static_cast<char>(get() % value));
				return *this;
			}

			__forceinline h_int8& __fastcall operator^=(const char value) {
				set(static_cast<char>(get() ^ value));
				return *this;
			}

			__forceinline h_int8& __fastcall operator&=(const char value) {
				set(static_cast<char>(get() & value));
				return *this;
			}

			__forceinline h_int8& __fastcall operator|=(const char value) {
				set(static_cast<char>(get() | value));
				return *this;
			}

			__forceinline h_int8& __fastcall operator<<=(const char value) {
				set(static_cast<char>(get() << value));
				return *this;
			}

			__forceinline h_int8& __fastcall operator>>=(const char value) {
				set(static_cast<char>(get() >> value));
				return *this;
			}

			__forceinline h_int8& __fastcall operator=(const char value) {
				set(value);
				return *this;
			}

			__forceinline __fastcall operator char() const {
				return get();
			}

			__forceinline ~h_int8() { }

	#pragma endregion

		};

		class h_uint8 {

		private:

	#pragma region Globals

			mutable byte _value{};

			mutable qhash::qhash_cpu_t _hash{};

	#pragma endregion

		public:

	#pragma region CTOR

			__forceinline __fastcall h_uint8(byte value) {

				if (!is_init)
					init_hash_t();

				set(value);
			}

			__forceinline __cdecl h_uint8() {

				if (!is_init)
					init_hash_t();

				set(0);
			}

	#pragma endregion

	#pragma region Accessors

			__forceinline byte __fastcall get() const {

				auto hash = qhash::qhash_cpu(reinterpret_cast<void*>(&_value), sizeof(_value));

				if (hash != _hash)
					violation_callback(qexcept::q_rogueaccess(this->_hash.hash_obj.hash, hash.hash_obj.hash), reinterpret_cast<void*>(&_value));

				auto _return = _value;

				return _return;
			}

			__forceinline void __fastcall set(byte value) {

				auto hash = qhash::qhash_cpu(&value, sizeof(value));

				this->_hash = hash;

				_value = value;
			}

			__forceinline decltype(_value)* get_raw_memory_address() {
				return &_value;
			}

	#pragma endregion

	#pragma region Operators

			__forceinline h_uint8 __fastcall operator+(const byte value) const {
				return h_uint8(get() + value);
			};

			__forceinline h_uint8 __fastcall operator-(const byte value) const {
				return h_uint8(get() - value);
			}

			__forceinline h_uint8 __fastcall operator/(const byte value) const {
				return h_uint8(get() / value);
			}

			__forceinline h_uint8 __fastcall operator*(const byte value) const {
				return h_uint8(get() * value);
			}

			__forceinline h_uint8 __fastcall operator&(const byte value) const {
				return h_uint8(get() & value);
			}

			__forceinline h_uint8 __fastcall operator|(const byte value) const {
				return h_uint8(get() | value);
			}

			__forceinline h_uint8 __fastcall operator%(const byte value) const {
				return h_uint8(get() % value);
			}

			__forceinline h_uint8 __fastcall operator^(const byte value) const {
				return h_uint8(get() ^ value);
			}

			__forceinline h_uint8 __fastcall operator<<(const byte value) const {
				return h_uint8(get() << value);
			}

			__forceinline h_uint8 __fastcall operator>>(const byte value) const {
				return h_uint8(get() >> value);
			}

			__forceinline h_uint8& __fastcall operator+=(const byte value) {
				set(static_cast<byte>(get() + value));
				return *this;
			}

			__forceinline h_uint8& __fastcall operator-=(const byte value) {
				set(static_cast<byte>(get() - value));
				return *this;
			}

			__forceinline h_uint8& __fastcall operator++() {
				operator+=(1i8);
				return *this;
			}

			__forceinline h_uint8& __fastcall operator--() {
				operator-=(1i8);
				return *this;
			}

			__forceinline h_uint8& __fastcall operator*=(const byte value) {
				set(static_cast<byte>(get() * value));
				return *this;
			}

			__forceinline h_uint8& __fastcall operator/=(const byte value) {
				set(static_cast<byte>(get() / value));
				return *this;
			}

			__forceinline h_uint8& __fastcall operator%=(const byte value) {
				set(static_cast<byte>(get() % value));
				return *this;
			}

			__forceinline h_uint8& __fastcall operator^=(const byte value) {
				set(static_cast<byte>(get() ^ value));
				return *this;
			}

			__forceinline h_uint8& __fastcall operator&=(const byte value) {
				set(static_cast<byte>(get() & value));
				return *this;
			}

			__forceinline h_uint8& __fastcall operator|=(const byte value) {
				set(static_cast<byte>(get() | value));
				return *this;
			}

			__forceinline h_uint8& __fastcall operator<<=(const byte value) {
				set(static_cast<byte>(get() << value));
				return *this;
			}

			__forceinline h_uint8& __fastcall operator>>=(const byte value) {
				set(static_cast<byte>(get() >> value));
				return *this;
			}

			__forceinline h_uint8& __fastcall operator=(const byte value) {
				set(value);
				return *this;
			}

			__forceinline __fastcall operator byte() const {
				return get();
			}

			__forceinline ~h_uint8() { }
	#pragma endregion
		};

	#pragma endregion

	#pragma region 16-bit

		class h_int16 {

		private:

	#pragma region Globals

			mutable short _value{};

			mutable qhash::qhash_cpu_t _hash{};

	#pragma endregion

		public:

	#pragma region CTOR

			__forceinline __fastcall h_int16(short value) {

				if (!is_init)
					init_hash_t();

				set(value);
			}

			__forceinline __cdecl h_int16() { 

				if (!is_init)
					init_hash_t();

				set(0);
			}

	#pragma endregion

	#pragma region Accessors

			__forceinline short __fastcall get() const {

				auto hash = qhash::qhash_cpu(reinterpret_cast<void*>(&_value), sizeof(_value));

				if (hash != _hash)
					violation_callback(qexcept::q_rogueaccess(this->_hash.hash_obj.hash, hash.hash_obj.hash), reinterpret_cast<void*>(&_value));

				auto _return = _value;

				return _return;
			}

			__forceinline void __fastcall set(short value) {

				auto hash = qhash::qhash_cpu(&value, sizeof(value));

				this->_hash = hash;

				_value = value;
			}

			__forceinline decltype(_value)* get_raw_memory_address() {
				return &_value;
			}

	#pragma endregion

	#pragma region Operators

			__forceinline h_int16 __fastcall operator+(const short value) const {
				return h_int16(get() + value);
			};

			__forceinline h_int16 __fastcall operator-(const short value) const {
				return h_int16(get() - value);
			}

			__forceinline h_int16 __fastcall operator/(const short value) const {
				return h_int16(get() / value);
			}

			__forceinline h_int16 __fastcall operator*(const short value) const {
				return h_int16(get() * value);
			}

			__forceinline h_int16 __fastcall operator&(const short value) const {
				return h_int16(get() & value);
			}

			__forceinline h_int16 __fastcall operator|(const short value) const {
				return h_int16(get() | value);
			}

			__forceinline h_int16 __fastcall operator%(const short value) const {
				return h_int16(get() % value);
			}

			__forceinline h_int16 __fastcall operator^(const short value) const {
				return h_int16(get() ^ value);
			}

			__forceinline h_int16 __fastcall operator<<(const short value) const {
				return h_int16(get() << value);
			}

			__forceinline h_int16 __fastcall operator>>(const short value) const {
				return h_int16(get() >> value);
			}

			__forceinline h_int16& __fastcall operator+=(const short value) {
				set(static_cast<short>(get() + value));
				return *this;
			}

			__forceinline h_int16& __fastcall operator-=(const short value) {
				set(static_cast<short>(get() - value));
				return *this;
			}

			__forceinline h_int16& __fastcall operator++() {
				operator+=(1i8);
				return *this;
			}

			__forceinline h_int16& __fastcall operator--() {
				operator-=(1i8);
				return *this;
			}

			__forceinline h_int16& __fastcall operator*=(const short value) {
				set(static_cast<short>(get() * value));
				return *this;
			}

			__forceinline h_int16& __fastcall operator/=(const short value) {
				set(static_cast<short>(get() / value));
				return *this;
			}

			__forceinline h_int16& __fastcall operator%=(const short value) {
				set(static_cast<short>(get() % value));
				return *this;
			}

			__forceinline h_int16& __fastcall operator^=(const short value) {
				set(static_cast<short>(get() ^ value));
				return *this;
			}

			__forceinline h_int16& __fastcall operator&=(const short value) {
				set(static_cast<short>(get() & value));
				return *this;
			}

			__forceinline h_int16& __fastcall operator|=(const short value) {
				set(static_cast<short>(get() | value));
				return *this;
			}

			__forceinline h_int16& __fastcall operator<<=(const short value) {
				set(static_cast<short>(get() << value));
				return *this;
			}

			__forceinline h_int16& __fastcall operator>>=(const short value) {
				set(static_cast<short>(get() >> value));
				return *this;
			}

			__forceinline h_int16& __fastcall operator=(const short value) {
				set(value);
				return *this;
			}

			__forceinline __fastcall operator short() const {
				return get();
			}

			__forceinline ~h_int16() { }
	#pragma endregion
		};

		class h_uint16 {

		private:

	#pragma region Globals

			mutable ushort _value{};

			mutable qhash::qhash_cpu_t _hash{};

	#pragma endregion

		public:

	#pragma region CTOR

			__forceinline __fastcall h_uint16(ushort value) {

				if (!is_init)
					init_hash_t();

				set(value);
			}

			__forceinline __cdecl h_uint16() { 

				if (!is_init)
					init_hash_t();

				set(0);
			}

	#pragma endregion

	#pragma region Accessors

			__forceinline ushort __fastcall get() const {

				auto hash = qhash::qhash_cpu(reinterpret_cast<void*>(&_value), sizeof(_value));

				if (hash != _hash)
					violation_callback(qexcept::q_rogueaccess(this->_hash.hash_obj.hash, hash.hash_obj.hash), reinterpret_cast<void*>(&_value));

				auto _return = _value;

				return _return;
			}

			__forceinline void __fastcall set(ushort value) {

				auto hash = qhash::qhash_cpu(&value, sizeof(value));

				this->_hash = hash;

				_value = value;
			}

			__forceinline decltype(_value)* get_raw_memory_address() {
				return &_value;
			}

	#pragma endregion

	#pragma region Operators

			__forceinline h_uint16 __fastcall operator+(const ushort value) const {
				return h_uint16(get() + value);
			};

			__forceinline h_uint16 __fastcall operator-(const ushort value) const {
				return h_uint16(get() - value);
			}

			__forceinline h_uint16 __fastcall operator/(const ushort value) const {
				return h_uint16(get() / value);
			}

			__forceinline h_uint16 __fastcall operator*(const ushort value) const {
				return h_uint16(get() * value);
			}

			__forceinline h_uint16 __fastcall operator&(const ushort value) const {
				return h_uint16(get() & value);
			}

			__forceinline h_uint16 __fastcall operator|(const ushort value) const {
				return h_uint16(get() | value);
			}

			__forceinline h_uint16 __fastcall operator%(const ushort value) const {
				return h_uint16(get() % value);
			}

			__forceinline h_uint16 __fastcall operator^(const ushort value) const {
				return h_uint16(get() ^ value);
			}

			__forceinline h_uint16 __fastcall operator<<(const ushort value) const {
				return h_uint16(get() << value);
			}

			__forceinline h_uint16 __fastcall operator>>(const ushort value) const {
				return h_uint16(get() >> value);
			}

			__forceinline h_uint16& __fastcall operator+=(const ushort value) {
				set(static_cast<ushort>(get() + value));
				return *this;
			}

			__forceinline h_uint16& __fastcall operator-=(const ushort value) {
				set(static_cast<ushort>(get() - value));
				return *this;
			}

			__forceinline h_uint16& __fastcall operator++() {
				operator+=(1i8);
				return *this;
			}

			__forceinline h_uint16& __fastcall operator--() {
				operator-=(1i8);
				return *this;
			}

			__forceinline h_uint16& __fastcall operator*=(const ushort value) {
				set(static_cast<ushort>(get() * value));
				return *this;
			}

			__forceinline h_uint16& __fastcall operator/=(const ushort value) {
				set(static_cast<ushort>(get() / value));
				return *this;
			}

			__forceinline h_uint16& __fastcall operator%=(const ushort value) {
				set(static_cast<ushort>(get() % value));
				return *this;
			}

			__forceinline h_uint16& __fastcall operator^=(const ushort value) {
				set(static_cast<ushort>(get() ^ value));
				return *this;
			}

			__forceinline h_uint16& __fastcall operator&=(const ushort value) {
				set(static_cast<ushort>(get() & value));
				return *this;
			}

			__forceinline h_uint16& __fastcall operator|=(const ushort value) {
				set(static_cast<ushort>(get() | value));
				return *this;
			}

			__forceinline h_uint16& __fastcall operator<<=(const ushort value) {
				set(static_cast<ushort>(get() << value));
				return *this;
			}

			__forceinline h_uint16& __fastcall operator>>=(const ushort value) {
				set(static_cast<ushort>(get() >> value));
				return *this;
			}

			__forceinline h_uint16& __fastcall operator=(const ushort value) {
				set(value);
				return *this;
			}

			__forceinline __fastcall operator ushort() const {
				return get();
			}

			__forceinline ~h_uint16() {	}
	#pragma endregion
		};

	#pragma endregion

	#pragma region 32-bit

		class h_int32 {

		private:

	#pragma region Globals

			mutable int _value{};

			mutable qhash::qhash_cpu_t _hash{};

	#pragma endregion

		public:

	#pragma region CTOR

			__forceinline __fastcall h_int32(int value) {

				if (!is_init)
					init_hash_t();

				set(value);
			}

			__forceinline __cdecl h_int32() { 

				if (!is_init)
					init_hash_t();

				set(0);
			}

	#pragma endregion

	#pragma region Accessors

			__forceinline int __fastcall get() const {

				auto hash = qhash::qhash_cpu(reinterpret_cast<void*>(&_value), sizeof(_value));

				if (hash != _hash) 
					violation_callback(qexcept::q_rogueaccess(this->_hash.hash_obj.hash, hash.hash_obj.hash), reinterpret_cast<void*>(&_value));

				auto _return = _value;

				return _return;
			}

			__forceinline void __fastcall set(int value) {

				auto hash = qhash::qhash_cpu(&value, sizeof(value));

				this->_hash = hash;

				_value = value;
			}

			__forceinline decltype(_value)* get_raw_memory_address() {
				return &_value;
			}

	#pragma endregion

	#pragma region Operators

			__forceinline h_int32 __fastcall operator+(const int value) const {
				return h_int32(get() + value);
			};

			__forceinline h_int32 __fastcall operator-(const int value) const {
				return h_int32(get() - value);
			}

			__forceinline h_int32 __fastcall operator/(const int value) const {
				return h_int32(get() / value);
			}

			__forceinline h_int32 __fastcall operator*(const int value) const {
				return h_int32(get() * value);
			}

			__forceinline h_int32 __fastcall operator&(const int value) const {
				return h_int32(get() & value);
			}

			__forceinline h_int32 __fastcall operator|(const int value) const {
				return h_int32(get() | value);
			}

			__forceinline h_int32 __fastcall operator%(const int value) const {
				return h_int32(get() % value);
			}

			__forceinline h_int32 __fastcall operator^(const int value) const {
				return h_int32(get() ^ value);
			}

			__forceinline h_int32 __fastcall operator<<(const int value) const {
				return h_int32(get() << value);
			}

			__forceinline h_int32 __fastcall operator>>(const int value) const {
				return h_int32(get() >> value);
			}

			__forceinline h_int32& __fastcall operator+=(const int value) {
				set(static_cast<int>(get() + value));
				return *this;
			}

			__forceinline h_int32& __fastcall operator-=(const int value) {
				set(static_cast<int>(get() - value));
				return *this;
			}

			__forceinline h_int32& __fastcall operator++() {
				operator+=(1i8);
				return *this;
			}

			__forceinline h_int32& __fastcall operator--() {
				operator-=(1i8);
				return *this;
			}

			__forceinline h_int32& __fastcall operator*=(const int value) {
				set(static_cast<int>(get() * value));
				return *this;
			}

			__forceinline h_int32& __fastcall operator/=(const int value) {
				set(static_cast<int>(get() / value));
				return *this;
			}

			__forceinline h_int32& __fastcall operator%=(const int value) {
				set(static_cast<int>(get() % value));
				return *this;
			}

			__forceinline h_int32& __fastcall operator^=(const int value) {
				set(static_cast<int>(get() ^ value));
				return *this;
			}

			__forceinline h_int32& __fastcall operator&=(const int value) {
				set(static_cast<int>(get() & value));
				return *this;
			}

			__forceinline h_int32& __fastcall operator|=(const int value) {
				set(static_cast<int>(get() | value));
				return *this;
			}

			__forceinline h_int32& __fastcall operator<<=(const int value) {
				set(static_cast<int>(get() << value));
				return *this;
			}

			__forceinline h_int32& __fastcall operator>>=(const int value) {
				set(static_cast<int>(get() >> value));
				return *this;
			}

			__forceinline h_int32& __fastcall operator=(const int value) {
				set(value);
				return *this;
			}

			__forceinline __fastcall operator int() const {
				return get();
			}

			__forceinline ~h_int32() { }
	#pragma endregion
		};

		class h_uint32 {
		private:

	#pragma region Globals

			mutable uint _value{};

			mutable qhash::qhash_cpu_t _hash{};

	#pragma endregion

		public:

	#pragma region CTOR

			__forceinline __fastcall h_uint32(uint value) {

				if (!is_init)
					init_hash_t();

				set(value);
			}

			__forceinline __cdecl h_uint32() {

				if (!is_init)
					init_hash_t();

				set(0);
			};

	#pragma endregion

	#pragma region Accessors

			__forceinline uint __fastcall get() const {

				auto hash = qhash::qhash_cpu(reinterpret_cast<void*>(&_value), sizeof(_value));

				if (hash != _hash)
					violation_callback(qexcept::q_rogueaccess(this->_hash.hash_obj.hash, hash.hash_obj.hash), reinterpret_cast<void*>(&_value));

				auto _return = _value;

				return _return;
			}

			__forceinline void __fastcall set(uint value) {

				auto hash = qhash::qhash_cpu(&value, sizeof(value));

				this->_hash = hash;

				_value = value;
			}

			__forceinline decltype(_value)* get_raw_memory_address() {
				return &_value;
			}

	#pragma endregion

	#pragma region Operators

			__forceinline h_uint32 __fastcall operator+(const uint value) const {
				return h_uint32(get() + value);
			};

			__forceinline h_uint32 __fastcall operator-(const uint value) const {
				return h_uint32(get() - value);
			}

			__forceinline h_uint32 __fastcall operator/(const uint value) const {
				return h_uint32(get() / value);
			}

			__forceinline h_uint32 __fastcall operator*(const uint value) const {
				return h_uint32(get() * value);
			}

			__forceinline h_uint32 __fastcall operator&(const uint value) const {
				return h_uint32(get() & value);
			}

			__forceinline h_uint32 __fastcall operator|(const uint value) const {
				return h_uint32(get() | value);
			}

			__forceinline h_uint32 __fastcall operator%(const uint value) const {
				return h_uint32(get() % value);
			}

			__forceinline h_uint32 __fastcall operator^(const uint value) const {
				return h_uint32(get() ^ value);
			}

			__forceinline h_uint32 __fastcall operator<<(const uint value) const {
				return h_uint32(get() << value);
			}

			__forceinline h_uint32 __fastcall operator>>(const uint value) const {
				return h_uint32(get() >> value);
			}

			__forceinline h_uint32& __fastcall operator+=(const uint value) {
				set(static_cast<uint>(get() + value));
				return *this;
			}

			__forceinline h_uint32& __fastcall operator-=(const uint value) {
				set(static_cast<uint>(get() - value));
				return *this;
			}

			__forceinline h_uint32& __fastcall operator++() {
				operator+=(1i8);
				return *this;
			}

			__forceinline h_uint32& __fastcall operator--() {
				operator-=(1i8);
				return *this;
			}

			__forceinline h_uint32& __fastcall operator*=(const uint value) {
				set(static_cast<uint>(get() * value));
				return *this;
			}

			__forceinline h_uint32& __fastcall operator/=(const uint value) {
				set(static_cast<uint>(get() / value));
				return *this;
			}

			__forceinline h_uint32& __fastcall operator%=(const uint value) {
				set(static_cast<uint>(get() % value));
				return *this;
			}

			__forceinline h_uint32& __fastcall operator^=(const uint value) {
				set(static_cast<uint>(get() ^ value));
				return *this;
			}

			__forceinline h_uint32& __fastcall operator&=(const uint value) {
				set(static_cast<uint>(get() & value));
				return *this;
			}

			__forceinline h_uint32& __fastcall operator|=(const uint value) {
				set(static_cast<uint>(get() | value));
				return *this;
			}

			__forceinline h_uint32& __fastcall operator<<=(const uint value) {
				set(static_cast<uint>(get() << value));
				return *this;
			}

			__forceinline h_uint32& __fastcall operator>>=(const uint value) {
				set(static_cast<uint>(get() >> value));
				return *this;
			}

			__forceinline h_uint32& __fastcall operator=(const uint value) {
				set(value);
				return *this;
			}

			__forceinline __fastcall operator uint() const {
				return get();
			}

			__forceinline ~h_uint32() { }
	#pragma endregion
		};

	#pragma endregion

	#pragma region 64-bit

	#ifdef _WIN64

		class h_int64 {

		private:

	#pragma region Globals

			mutable int64_t _value{};

			mutable qhash::qhash_cpu_t _hash{};

	#pragma endregion

		public:

	#pragma region CTOR

			__forceinline __fastcall h_int64(int64_t value) {

				if (!is_init)
					init_hash_t();

				set(value);
			}

			__forceinline __cdecl h_int64() { 

				if (!is_init)
					init_hash_t();

				set(0);
			}

	#pragma endregion

	#pragma region Accessors

			int64_t __fastcall get() const {

				auto hash = qhash::qhash_cpu(reinterpret_cast<void*>(&_value), sizeof(_value));

				if (hash != _hash)
					violation_callback(qexcept::q_rogueaccess(this->_hash.hash_obj.hash, hash.hash_obj.hash), reinterpret_cast<void*>(&_value)); // access violation executing location, make the argument for passing callback an rvalue ?

				auto _return = _value;

				return _return;
			}

			__forceinline void __fastcall set(int64_t value) {

				auto hash = qhash::qhash_cpu(&value, sizeof(value));

				this->_hash = hash;

				_value = value;
			}

			__forceinline decltype(_value)* get_raw_memory_address() {
				return &_value;
			}

	#pragma endregion

	#pragma region Operators

			__forceinline h_int64 __fastcall operator+(const int64_t value) const {
				return h_int64(get() + value);
			};

			__forceinline h_int64 __fastcall operator-(const int64_t value) const {
				return h_int64(get() - value);
			}

			__forceinline h_int64 __fastcall operator/(const int64_t value) const {
				return h_int64(get() / value);
			}

			__forceinline h_int64 __fastcall operator*(const int64_t value) const {
				return h_int64(get() * value);
			}

			__forceinline h_int64 __fastcall operator&(const int64_t value) const {
				return h_int64(get() & value);
			}

			__forceinline h_int64 __fastcall operator|(const int64_t value) const {
				return h_int64(get() | value);
			}

			__forceinline h_int64 __fastcall operator%(const int64_t value) const {
				return h_int64(get() % value);
			}

			__forceinline h_int64 __fastcall operator^(const int64_t value) const {
				return h_int64(get() ^ value);
			}

			__forceinline h_int64 __fastcall operator<<(const int64_t value) const {
				return h_int64(get() << value);
			}

			__forceinline h_int64 __fastcall operator>>(const int64_t value) const {
				return h_int64(get() >> value);
			}

			__forceinline h_int64& __fastcall operator+=(const int64_t value) {
				set(static_cast<int>(get() + value));
				return *this;
			}

			__forceinline h_int64& __fastcall operator-=(const int64_t value) {
				set(static_cast<int>(get() - value));
				return *this;
			}

			__forceinline h_int64& __fastcall operator++() {
				operator+=(1i8);
				return *this;
			}

			__forceinline h_int64& __fastcall operator--() {
				operator-=(1i8);
				return *this;
			}

			__forceinline h_int64& __fastcall operator*=(const int64_t value) {
				set(static_cast<int64>(get() * value));
				return *this;
			}

			__forceinline h_int64& __fastcall operator/=(const int64_t value) {
				set(static_cast<int64>(get() / value));
				return *this;
			}

			__forceinline h_int64& __fastcall operator%=(const int64_t value) {
				set(static_cast<int64>(get() % value));
				return *this;
			}

			__forceinline h_int64& __fastcall operator^=(const int64_t value) {
				set(static_cast<int64>(get() ^ value));
				return *this;
			}

			__forceinline h_int64& __fastcall operator&=(const int64_t value) {
				set(static_cast<int64>(get() & value));
				return *this;
			}

			__forceinline h_int64& __fastcall operator|=(const int64_t value) {
				set(static_cast<int64>(get() | value));
				return *this;
			}

			__forceinline h_int64& __fastcall operator<<=(const int64_t value) {
				set(static_cast<int64>(get() << value));
				return *this;
			}

			__forceinline h_int64& __fastcall operator>>=(const int64_t value) {
				set(static_cast<int64>(get() >> value));
				return *this;
			}

			__forceinline h_int64& __fastcall operator=(const int64_t value) {
				set(value);
				return *this;
			}

			__forceinline __fastcall operator int() const {
				return get();
			}

			__forceinline ~h_int64() { }
	#pragma endregion
		};

		class h_uint64 {

		private:

	#pragma region Globals

			mutable uint64_t _value{};

			mutable qhash::qhash_cpu_t _hash{};

	#pragma endregion

		public:

	#pragma region CTOR

			__forceinline __fastcall h_uint64(uint64_t value) {

				if (!is_init)
					init_hash_t();

				set(value);
			}

			__forceinline __cdecl h_uint64() {

				if (!is_init)
					init_hash_t();

				set(0);
			}

	#pragma endregion

	#pragma region Accessors

			__forceinline uint64_t __fastcall get() const {

				auto hash = qhash::qhash_cpu(reinterpret_cast<void*>(&_value), sizeof(_value));

				if (hash != _hash)
					violation_callback(qexcept::q_rogueaccess(this->_hash.hash_obj.hash, hash.hash_obj.hash), reinterpret_cast<void*>(&_value));

				auto _return = _value;

				return _return;
			}

			__forceinline void __fastcall set(uint64_t value) {

				auto hash = qhash::qhash_cpu(&value, sizeof(value));

				this->_hash = hash;

				_value = value;
			}

			__forceinline decltype(_value)* get_raw_memory_address() {
				return &_value;
			}

	#pragma endregion

	#pragma region Operators

			__forceinline h_uint64 __fastcall operator+(const uint64_t value) const {
				return h_uint64(get() + value);
			};

			__forceinline h_uint64 __fastcall operator-(const uint64_t value) const {
				return h_uint64(get() - value);
			}

			__forceinline h_uint64 __fastcall operator/(const uint64_t value) const {
				return h_uint64(get() / value);
			}

			__forceinline h_uint64 __fastcall operator*(const uint64_t value) const {
				return h_uint64(get() * value);
			}

			__forceinline h_uint64 __fastcall operator&(const uint64_t value) const {
				return h_uint64(get() & value);
			}

			__forceinline h_uint64 __fastcall operator|(const uint64_t value) const {
				return h_uint64(get() | value);
			}

			__forceinline h_uint64 __fastcall operator%(const uint64_t value) const {
				return h_uint64(get() % value);
			}

			__forceinline h_uint64 __fastcall operator^(const uint64_t value) const {
				return h_uint64(get() ^ value);
			}

			__forceinline h_uint64 __fastcall operator<<(const uint64_t value) const {
				return h_uint64(get() << value);
			}

			__forceinline h_uint64 __fastcall operator>>(const uint64_t value) const {
				return h_uint64(get() >> value);
			}

			__forceinline h_uint64& __fastcall operator+=(const uint64_t value) {
				set(static_cast<uint64>(get() + value));
				return *this;
			}

			__forceinline h_uint64& __fastcall operator-=(const uint64_t value) {
				set(static_cast<uint64>(get() - value));
				return *this;
			}

			__forceinline h_uint64& __fastcall operator++() {
				operator+=(1i8);
				return *this;
			}

			__forceinline h_uint64& __fastcall operator--() {
				operator-=(1i8);
				return *this;
			}

			__forceinline h_uint64& __fastcall operator*=(const uint64_t value) {
				set(static_cast<uint64>(get() * value));
				return *this;
			}

			__forceinline h_uint64& __fastcall operator/=(const uint64_t value) {
				set(static_cast<uint64>(get() / value));
				return *this;
			}

			__forceinline h_uint64& __fastcall operator%=(const uint64_t value) {
				set(static_cast<uint64>(get() % value));
				return *this;
			}

			__forceinline h_uint64& __fastcall operator^=(const uint64_t value) {
				set(static_cast<uint64>(get() ^ value));
				return *this;
			}

			__forceinline h_uint64& __fastcall operator&=(const uint64_t value) {
				set(static_cast<uint64>(get() & value));
				return *this;
			}

			__forceinline h_uint64& __fastcall operator|=(const uint64_t value) {
				set(static_cast<uint64>(get() | value));
				return *this;
			}

			__forceinline h_uint64& __fastcall operator<<=(const uint64_t value) {
				set(static_cast<uint64>(get() << value));
				return *this;
			}

			__forceinline h_uint64& __fastcall operator>>=(const uint64_t value) {
				set(static_cast<uint64>(get() >> value));
				return *this;
			}

			__forceinline h_uint64& __fastcall operator=(const uint64_t value) {
				set(value);
				return *this;
			}

			__forceinline __fastcall operator int() const {
				return get();
			}

			__forceinline ~h_uint64() { }
	#pragma endregion
		};

	#endif

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

	#pragma region 32-bit

		class h_float {

		private:

	#pragma region Globals

			mutable float _value;

			mutable qhash::qhash_cpu_t _hash{};

	#pragma endregion

		public:

	#pragma region CTOR

			__forceinline __fpcall h_float(float value) {

				if (!is_init)
					init_hash_t();

				set(value);
			}

			__forceinline __cdecl h_float() { 

				if (!is_init)
					init_hash_t();

				set(0.f);
			}

	#pragma endregion

	#pragma region Accessors

			__forceinline float __fastcall get() const {

				auto hash = qhash::qhash_cpu(reinterpret_cast<void*>(&_value), sizeof(_value));

				if (hash != _hash)
					violation_callback(qexcept::q_rogueaccess(this->_hash.hash_obj.hash, hash.hash_obj.hash), reinterpret_cast<void*>(&_value));

				auto _return = _value;

				return _return;
			}

			__forceinline void __fastcall set(float value) {

				auto hash = qhash::qhash_cpu(&value, sizeof(value));

				this->_hash = hash;

				_value = value;
			}

			__forceinline decltype(_value)* get_raw_memory_address() {
				return &_value;
			}

	#pragma endregion

	#pragma region Operators

			__forceinline h_float __fpcall operator+(const float value) const {
				return h_float(get() + value);
			};

			__forceinline h_float __fpcall operator-(const float value) const {
				return h_float(get() - value);
			}

			__forceinline h_float __fpcall operator/(const float value) const {
				return h_float(get() / value);
			}

			__forceinline h_float __fpcall operator*(const float value) const {
				return h_float(get() * value);
			}

			__forceinline h_float& __fpcall operator+=(const float value) {
				set(static_cast<float>(get() + value));
				return *this;
			}

			__forceinline h_float& __fpcall operator-=(const float value) {
				set(static_cast<float>(get() - value));
				return *this;
			}

			__forceinline h_float& __cdecl operator++() {
				operator+=(1.f);
				return *this;
			}

			__forceinline h_float& __cdecl operator--() {
				operator-=(1.f);
				return *this;
			}

			__forceinline h_float& __fpcall operator*=(const float value) {
				set(static_cast<float>(get() * value));
				return *this;
			}

			__forceinline h_float& __fpcall operator/=(const float value) {
				set(static_cast<float>(get() / value));
				return *this;
			}

			__forceinline h_float& __fpcall operator=(const float value) {
				set(value);
				return *this;
			}

			__forceinline __cdecl operator float() const {
				return get();
			}

			__forceinline __cdecl ~h_float() { }

	#pragma endregion
		};

	#pragma endregion

	#pragma region 64-bit

	#ifdef _WIN64

		class h_double {

		private:

	#pragma region Globals

			mutable double _value;

			mutable qhash::qhash_cpu_t _hash{};

	#pragma endregion

		public:

	#pragma region CTOR

			__forceinline __fpcall h_double(double value) {

				if (!is_init)
					init_hash_t();

				set(value);
			}

			__forceinline __cdecl h_double() {

				if (!is_init)
					init_hash_t();

				set(0);
			}

	#pragma endregion

	#pragma region Accessors

			__forceinline double __fastcall get() const {

				auto hash = qhash::qhash_cpu(reinterpret_cast<void*>(&_value), sizeof(_value));

				if (hash != _hash)
					violation_callback(qexcept::q_rogueaccess(this->_hash.hash_obj.hash, hash.hash_obj.hash), reinterpret_cast<void*>(&_value));

				auto _return = _value;

				return _return;
			}

			__forceinline void __fastcall set(double value) {

				auto hash = qhash::qhash_cpu(&value, sizeof(value));

				this->_hash = hash;

				_value = value;
			}

			__forceinline decltype(_value)* get_raw_memory_address() {
				return &_value;
			}

	#pragma endregion

	#pragma region Operators

			__forceinline h_double __fpcall operator+(const double value) const {
				return h_double(get() + value);
			};

			__forceinline h_double __fpcall operator-(const double value) const {
				return h_double(get() - value);
			}

			__forceinline h_double __fpcall operator/(const double value) const {
				return h_double(get() / value);
			}

			__forceinline h_double __fpcall operator*(const double value) const {
				return h_double(get() * value);
			}

			__forceinline h_double& __fpcall operator+=(const double value) {
				set(static_cast<double>(get() + value));
				return *this;
			}

			__forceinline h_double& __fpcall operator-=(const double value) {
				set(static_cast<double>(get() - value));
				return *this;
			}

			__forceinline h_double& __cdecl operator++() {
				operator+=(1.f);
				return *this;
			}

			__forceinline h_double& __cdecl operator--() {
				operator-=(1.f);
				return *this;
			}

			__forceinline h_double& __fpcall operator*=(const double value) {
				set(static_cast<double>(get() * value));
				return *this;
			}

			__forceinline h_double& __fpcall operator/=(const double value) {
				set(static_cast<double>(get() / value));
				return *this;
			}

			__forceinline h_double& __fpcall operator=(const double value) {
				set(value);
				return *this;
			}

			__forceinline __cdecl operator double() const {
				return get();
			}

			__forceinline __cdecl ~h_double() { }
	#pragma endregion
		};

	#endif

	#pragma endregion

	#pragma endregion

	#pragma region Extended Types

	#pragma region SSE

	#ifdef __SSE__

		class h_m128 {

		private:

	#pragma region Globals

			mutable __m128 _value;

			mutable qhash::qhash_cpu_t _hash{};

	#pragma endregion

		public:

	#pragma region CTOR

			__forceinline __vectorcall h_m128(__m128 value) {

				if (!is_init)
					init_hash_t();

				set(value);
			}

	#pragma endregion

	#pragma region Accessors

			__forceinline __m128 __fastcall get() const {

				auto hash = qhash::qhash_cpu(reinterpret_cast<void*>(&_value), sizeof(_value));

				if (hash != _hash)
					violation_callback(qexcept::q_rogueaccess(this->_hash.hash_obj.hash, hash.hash_obj.hash), reinterpret_cast<void*>(&_value));

				auto _return = _value;

				return _return;
			}

			__forceinline void __fastcall set(__m128 value) {

				auto hash = qhash::qhash_cpu(&value, sizeof(value));

				this->_hash = hash;

				_value = value;
			}

			__forceinline decltype(_value)* get_raw_memory_address() {
				return &_value;
			}

	#pragma endregion

	#pragma region Operators

	#ifdef __clang__

			__forceinline h_m128 __vectorcall operator+(const __m128 value) const {
				return h_m128(get() + value);
			};

			__forceinline h_m128 __vectorcall operator-(const __m128 value) const {
				return h_m128(get() - value);
			}

			__forceinline h_m128 __vectorcall operator/(const __m128 value) const {
				return h_m128(get() / value);
			}

			__forceinline h_m128 __vectorcall operator*(const __m128 value) const {
				return h_m128(get() * value);
			}

			__forceinline h_m128& __vectorcall operator+=(const __m128 value) {
				set(static_cast<__m128>(get() + value));
				return *this;
			}

			__forceinline h_m128& __vectorcall operator-=(const __m128 value) {
				set(static_cast<__m128>(get() - value));
				return *this;
			}

			__forceinline h_m128& __vectorcall operator*=(const __m128 value) {
				set(static_cast<__m128>(get() * value));
				return *this;
			}

			__forceinline h_m128& __vectorcall operator/=(const __m128 value) {
				set(static_cast<__m128>(get() / value));
				return *this;
			}

	#endif

			__forceinline h_m128& __vectorcall operator=(const __m128 value) {
				set(value);
				return *this;
			}

			__forceinline __vectorcall operator __m128() const {
				return get();
			}

			__forceinline ~h_m128() { }
	#pragma endregion
		};

	#ifdef __SSE2__

		class h_m128i {

		private:

	#pragma region Globals

			mutable __m128i _value;

			mutable qhash::qhash_cpu_t _hash{};

	#pragma endregion

		public:

	#pragma region CTOR

			__forceinline __vectorcall h_m128i(__m128i value) {

				if (!is_init)
					init_hash_t();

				set(value);
			}

	#pragma endregion

	#pragma region Accessors

			__forceinline __m128i __fastcall get() const {

				auto hash = qhash::qhash_cpu(reinterpret_cast<void*>(&_value), sizeof(_value));

				if (hash != _hash)
					violation_callback(qexcept::q_rogueaccess(this->_hash.hash_obj.hash, hash.hash_obj.hash), reinterpret_cast<void*>(&_value));

				auto _return = _value;

				return _return;
			}

			__forceinline void __fastcall set(__m128i value) {

				auto hash = qhash::qhash_cpu(&value, sizeof(value));

				this->_hash = hash;

				_value = value;
			}

			__forceinline decltype(_value)* get_raw_memory_address() {
				return &_value;
			}

	#pragma endregion

	#pragma region Operators

	#ifdef __clang__

			__forceinline h_m128i __vectorcall operator+(const __m128i value) const {
				return h_m128i(get() + value);
			};

			__forceinline h_m128i __vectorcall operator-(const __m128i value) const {
				return h_m128i(get() - value);
			}

			__forceinline h_m128i __vectorcall operator/(const __m128i value) const {
				return h_m128i(get() / value);
			}

			__forceinline h_m128i __vectorcall operator*(const __m128i value) const {
				return h_m128i(get() * value);
			}

			__forceinline h_m128i& __vectorcall operator+=(const __m128i value) {
				set(static_cast<__m128i>(get() + value));
				return *this;
			}

			__forceinline h_m128i& __vectorcall operator-=(const __m128i value) {
				set(static_cast<__m128i>(get() - value));
				return *this;
			}

			__forceinline h_m128i& __vectorcall operator*=(const __m128i value) {
				set(static_cast<__m128i>(get() * value));
				return *this;
			}

			__forceinline h_m128i& __vectorcall operator/=(const __m128i value) {
				set(static_cast<__m128i>(get() / value));
				return *this;
			}

	#endif

			__forceinline h_m128i& __vectorcall operator=(const __m128i value) {
				set(value);
				return *this;
			}

			__forceinline __cdecl operator __m128i() const {
				return get();
			}

			__forceinline ~h_m128i() { }
	#pragma endregion
		};

		class h_m128d {

		private:

	#pragma region Globals

			mutable __m128d _value;

			mutable qhash::qhash_cpu_t _hash{};

	#pragma endregion

		public:

	#pragma region CTOR

			__forceinline __vectorcall h_m128d(__m128d value) {

				if (!is_init)
					init_hash_t();

				set(value);
			}

	#pragma endregion

	#pragma region Accessors

			__forceinline __m128d __fastcall get() const {

				auto hash = qhash::qhash_cpu(reinterpret_cast<void*>(&_value), sizeof(_value));

				if (hash != _hash)
					violation_callback(qexcept::q_rogueaccess(this->_hash.hash_obj.hash, hash.hash_obj.hash), reinterpret_cast<void*>(&_value));

				auto _return = _value;

				return _return;
			}

			__forceinline void __fastcall set(__m128d value) {

				auto hash = qhash::qhash_cpu(&value, sizeof(value));

				this->_hash = hash;

				_value = value;
			}

			__forceinline decltype(_value)* get_raw_memory_address() {
				return &_value;
			}

	#pragma endregion

	#pragma region Operators

	#ifdef __clang__

			__forceinline h_m128d __vectorcall operator+(const __m128d value) const {
				return h_m128d(get() + value);
			};

			__forceinline h_m128d __vectorcall operator-(const __m128d value) const {
				return h_m128d(get() - value);
			}

			__forceinline h_m128d __vectorcall operator/(const __m128d value) const {
				return h_m128d(get() / value);
			}

			__forceinline h_m128d __vectorcall operator*(const __m128d value) const {
				return h_m128d(get() * value);
			}

			__forceinline h_m128d& __vectorcall operator+=(const __m128d value) {
				set(static_cast<__m128d>(get() + value));
				return *this;
			}

			__forceinline h_m128d& __vectorcall operator-=(const __m128d value) {
				set(static_cast<__m128d>(get() - value));
				return *this;
			}

			__forceinline h_m128d& __vectorcall operator*=(const __m128d value) {
				set(static_cast<__m128d>(get() * value));
				return *this;
			}

			__forceinline h_m128d& __vectorcall operator/=(const __m128d value) {
				set(static_cast<__m128d>(get() / value));
				return *this;
			}

	#endif

			__forceinline h_m128d& __vectorcall operator=(const __m128d value) {
				set(value);
				return *this;
			}

			__forceinline __vectorcall operator __m128d() const {
				return get();
			}

			__forceinline ~h_m128d() { }
	#pragma endregion
		};

	#endif

	#endif

	#pragma endregion

	#pragma region AVX

	#ifdef __AVX__

		class h_m256 {

		private:

	#pragma region Globals

			mutable __m256 _value;

			mutable qhash::qhash_cpu_t _hash{};

	#pragma endregion

		public:

	#pragma region CTOR

			__forceinline __vectorcall h_m256(__m256 value) {

				if (!is_init)
					init_hash_t();

				set(value);
			}

	#pragma endregion

	#pragma region Accessors

			__forceinline __m256 __fastcall get() const {

				auto hash = qhash::qhash_cpu(reinterpret_cast<void*>(&_value), sizeof(_value));

				if (hash != _hash)
					violation_callback(qexcept::q_rogueaccess(this->_hash.hash_obj.hash, hash.hash_obj.hash), reinterpret_cast<void*>(&_value));

				auto _return = _value;

				return _return;
			}

			__forceinline void __fastcall set(__m256 value) {

				auto hash = qhash::qhash_cpu(&value, sizeof(value));

				this->_hash = hash;

				_value = value;
			}

			__forceinline decltype(_value)* get_raw_memory_address() {
				return &_value;
			}

	#pragma endregion

	#pragma region Operators

	#ifdef __clang__

			__forceinline h_m256 __vectorcall operator+(const __m256 value) const {
				return h_m256(get() + value);
			};

			__forceinline h_m256 __vectorcall operator-(const __m256 value) const {
				return h_m256(get() - value);
			}

			__forceinline h_m256 __vectorcall operator/(const __m256 value) const {
				return h_m256(get() / value);
			}

			__forceinline h_m256 __vectorcall operator*(const __m256 value) const {
				return h_m256(get() * value);
			}

			__forceinline h_m256& __vectorcall operator+=(const __m256 value) {
				set(static_cast<__m256>(get() + value));
				return *this;
			}

			__forceinline h_m256& __vectorcall operator-=(const __m256 value) {
				set(static_cast<__m256>(get() - value));
				return *this;
			}

			__forceinline h_m256& __vectorcall operator*=(const __m256 value) {
				set(static_cast<__m256>(get() * value));
				return *this;
			}

			__forceinline h_m256& __vectorcall operator/=(const __m256 value) {
				set(static_cast<__m256>(get() / value));
				return *this;
			}

	#endif

			__forceinline h_m256& __vectorcall operator=(const __m256 value) {
				set(value);
				return *this;
			}

			__forceinline __vectorcall operator __m256() const {
				return get();
			}

			__forceinline ~h_m256() { }
	#pragma endregion
		};

		class h_m256i {

		private:

	#pragma region Globals

			mutable __m256i _value;

			mutable qhash::qhash_cpu_t _hash{};

	#pragma endregion

		public:

	#pragma region CTOR

			__forceinline __vectorcall h_m256i(__m256i value) {

				if (!is_init)
					init_hash_t();

				set(value);
			}

	#pragma endregion

	#pragma region Accessors

			__forceinline __m256i __fastcall get() const {

				auto hash = qhash::qhash_cpu(reinterpret_cast<void*>(&_value), sizeof(_value));

				if (hash != _hash)
					violation_callback(qexcept::q_rogueaccess(this->_hash.hash_obj.hash, hash.hash_obj.hash), reinterpret_cast<void*>(&_value));

				auto _return = _value;

				return _return;
			}

			__forceinline void __fastcall set(__m256i value) {

				auto hash = qhash::qhash_cpu(&value, sizeof(value));

				this->_hash = hash;

				_value = value;
			}

			__forceinline decltype(_value)* get_raw_memory_address() {
				return &_value;
			}

	#pragma endregion

	#pragma region Operators

	#ifdef __clang__

			__forceinline h_m256i __vectorcall operator+(const __m256i value) const {
				return h_m256i(get() + value);
			};

			__forceinline h_m256i __vectorcall operator-(const __m256i value) const {
				return h_m256i(get() - value);
			}

			__forceinline h_m256i __vectorcall operator/(const __m256i value) const {
				return h_m256i(get() / value);
			}

			__forceinline h_m256i __vectorcall operator*(const __m256i value) const {
				return h_m256i(get() * value);
			}

			__forceinline h_m256i& __vectorcall operator+=(const __m256i value) {
				set(static_cast<__m256i>(get() + value));
				return *this;
			}

			__forceinline h_m256i& __vectorcall operator-=(const __m256i value) {
				set(static_cast<__m256i>(get() - value));
				return *this;
			}

			__forceinline h_m256i& __vectorcall operator*=(const __m256i value) {
				set(static_cast<__m256i>(get() * value));
				return *this;
			}

			__forceinline h_m256i& __vectorcall operator/=(const __m256i value) {
				set(static_cast<__m256i>(get() / value));
				return *this;
			}

	#endif

			__forceinline h_m256i& __vectorcall operator=(const __m256i value) {
				set(value);
				return *this;
			}

			__forceinline __vectorcall operator __m256i() const {
				return get();
			}

			__forceinline ~h_m256i() { }
	#pragma endregion
		};

		class h_m256d {

		private:

	#pragma region Globals

			mutable __m256d _value;

			mutable qhash::qhash_cpu_t _hash{};

	#pragma endregion

		public:

	#pragma region CTOR

			__forceinline __vectorcall h_m256d(__m256d value) {

				if (!is_init)
					init_hash_t();

				set(value);
			}

	#pragma endregion

	#pragma region Accessors

			__forceinline __m256d __fastcall get() const {

				auto hash = qhash::qhash_cpu(reinterpret_cast<void*>(&_value), sizeof(_value));

				if (hash != _hash)
					violation_callback(qexcept::q_rogueaccess(this->_hash.hash_obj.hash, hash.hash_obj.hash), reinterpret_cast<void*>(&_value));

				auto _return = _value;

				return _return;
			}

			__forceinline void __fastcall set(__m256d value) {

				auto hash = qhash::qhash_cpu(&value, sizeof(value));

				this->_hash = hash;

				_value = value;
			}

			__forceinline decltype(_value)* get_raw_memory_address() {
				return &_value;
			}

	#pragma endregion

	#pragma region Operators

	#ifdef __clang__

			__forceinline h_m256d __vectorcall operator+(const __m256d value) const {
				return h_m256d(get() + value);
			};

			__forceinline h_m256d __vectorcall operator-(const __m256d value) const {
				return h_m256d(get() - value);
			}

			__forceinline h_m256d __vectorcall operator/(const __m256d value) const {
				return h_m256d(get() / value);
			}

			__forceinline h_m256d __vectorcall operator*(const __m256d value) const {
				return h_m256d(get() * value);
			}

			__forceinline h_m256d& __vectorcall operator+=(const __m256d value) {
				set(static_cast<__m256d>(get() + value));
				return *this;
			}

			__forceinline h_m256d& __vectorcall operator-=(const __m256d value) {
				set(static_cast<__m256d>(get() - value));
				return *this;
			}

			__forceinline h_m256d& __vectorcall operator*=(const __m256d value) {
				set(static_cast<__m256d>(get() * value));
				return *this;
			}

			__forceinline h_m256d& __vectorcall operator/=(const __m256d value) {
				set(static_cast<__m256d>(get() / value));
				return *this;
			}

	#endif

			__forceinline h_m256d& __vectorcall operator=(const __m256d value) {
				set(value);
				return *this;
			}

			__forceinline __vectorcall operator __m256d() const {
				return get();
			}

			__forceinline ~h_m256d() { }
	#pragma endregion
		};

	#endif

	#pragma endregion

	#pragma endregion

	#pragma region String Types

	#pragma region String

		class h_string {

		private:

	#pragma region Encrypted value

			mutable std::string _value = "";

			mutable qhash::qhash_cpu_t _hash{};

	#pragma endregion

		public:

	#pragma region CTOR

			__forceinline __cdecl h_string(const std::string& value) {

				if (!is_init)
					init_hash_t();

				set(value);
			}

			__forceinline __cdecl h_string(const char* value) {

				if (!is_init)
					init_hash_t();

				set(std::string(value));
			}

			__forceinline __cdecl h_string() { set(""); }

	#pragma endregion

	#pragma region Accessors

			__forceinline std::string __fastcall get() const {

				auto hash = qhash::qhash_cpu(reinterpret_cast<void*>(const_cast<char*>(_value.c_str())), sizeof(char) * _value.length());

				if (hash != _hash)
					violation_callback(qexcept::q_rogueaccess(this->_hash.hash_obj.hash, hash.hash_obj.hash), reinterpret_cast<void*>(&_value));

				auto _return = _value;

				return _return;
			}

			__forceinline void __fastcall set(std::string value) {

				auto hash = qhash::qhash_cpu(const_cast<char*>(value.c_str()), sizeof(char) * value.length());

				this->_hash = hash;

				_value = value;
			}

			__forceinline decltype(_value)* __cdecl get_raw_memory_address() {
				return &_value;
			}

	#pragma endregion

	#pragma region Operators

			__forceinline h_string __cdecl operator+(const std::string& value) const {
				return h_string(get() + value);
			}

			__forceinline h_string& __cdecl operator+=(const std::string& value) {
				set(static_cast<std::string>(get() + value));
				return *this;
			}

			__forceinline h_string& __cdecl operator=(const std::string& value) {
				set(value);
				return *this;
			}

			__forceinline __cdecl operator std::string() const {
				return get();
			}

			__forceinline __cdecl ~h_string() { }

	#pragma endregion
		};

	#pragma endregion

	#pragma region Wide String

		class h_wstring {

		private:

	#pragma region Encrypted value

			mutable std::wstring _value = L"";

			mutable qhash::qhash_cpu_t _hash{};

	#pragma endregion

		public:

	#pragma region CTOR

			__forceinline __cdecl h_wstring(const std::wstring& value) {

				if (!is_init)
					init_hash_t();

				set(value);
			}

			__forceinline __cdecl h_wstring(const wchar_t* value) {

				if (!is_init)
					init_hash_t();

				set(std::wstring(value));
			}

			__forceinline __cdecl h_wstring() { set(L""); }

	#pragma endregion

	#pragma region Accessors

			__forceinline std::wstring __fastcall get() const {

				auto hash = qhash::qhash_cpu(reinterpret_cast<void*>(const_cast<wchar_t*>(_value.c_str())), sizeof(wchar_t) * _value.length());

				if (hash != _hash)
					violation_callback(qexcept::q_rogueaccess(this->_hash.hash_obj.hash, hash.hash_obj.hash), reinterpret_cast<void*>(&_value));

				auto _return = _value;

				return _return;
			}

			__forceinline void __fastcall set(std::wstring value) {

				auto hash = qhash::qhash_cpu(const_cast<wchar_t*>(value.c_str()), sizeof(wchar_t) * value.length());

				this->_hash = hash;

				_value = value;
			}

			__forceinline decltype(_value)* __cdecl get_raw_memory_address() {
				return &_value;
			}

	#pragma endregion

	#pragma region Operators

			__forceinline h_wstring __cdecl operator+(const std::wstring& value) const {
				return h_wstring(get() + value);
			}

			__forceinline h_wstring& __cdecl operator+=(const std::wstring& value) {
				set(static_cast<std::wstring>(get() + value));
				return *this;
			}

			__forceinline h_wstring& __cdecl operator=(const std::wstring& value) {
				set(value);
				return *this;
			}

			__forceinline __cdecl operator std::wstring() const {
				return get();
			}

			__forceinline __cdecl ~h_wstring() { }

	#pragma endregion
		};

	#pragma endregion

	#pragma region Heap Allocation

		class h_malloc {

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

				h_malloc& parent;
				size_t index;

	#pragma endregion

			public:
	#pragma region Ctor

				index_proxy(size_t index_, h_malloc& instance) : index(index_), parent(instance) { }

	#pragma endregion

	#pragma region Operator overrides

				__forceinline byte& __fastcall operator=(byte value) {
					parent.set(index, value);
					return value;   // return the passed assignment value rather than using up absurd resources to decrypt, re-encrypt everything using get()
				}

				__forceinline __fastcall operator byte() const {
					return parent.get(index);
				}

	#pragma endregion
			};

	#pragma endregion

		public:

	#pragma region Ctor

			__forceinline __fastcall h_malloc(size_t size) : allocation_size(size) {

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

			__forceinline bool __fastcall get(void* destination, uintptr_t offset, size_t length) {

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

			__forceinline char __fastcall get(uintptr_t offset) {

				char _return{};

				if (!get(&_return, 0, sizeof(_return)))
					return NULL;

				return _return;
			}

			__forceinline void* __cdecl get() {

				auto alloc_new = malloc(allocation_size);

				if (!alloc_new)
					return nullptr;

				if (!get(alloc_new, 0, allocation_size)) {

					free(alloc_new);

					return nullptr;
				}

				return alloc_new;
			}

			__forceinline bool __fastcall set(void* source, uintptr_t offset, size_t length) {

				if (!allocation || !source)
					return false;

				memcpy(reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(allocation) + offset), source, length);

				_hash = qhash::qhash_cpu(allocation, allocation_size);

				return true;
			}

			__forceinline bool __fastcall set(uintptr_t index, byte value) {

				if (!set(&value, index, sizeof(value)))
					return false;

				return true;
			}

	#pragma endregion

	#pragma region Property Accessors

			__forceinline size_t __cdecl length() {

				return allocation_size;
			}

			__forceinline void* __cdecl get_raw_memory_address() {

				return allocation;
			}

	#pragma endregion

	#pragma region Utility functions

			__forceinline void __cdecl zero() {

				auto alloc_z = malloc(allocation_size);

				RtlZeroMemory(alloc_z, allocation_size);

				set(alloc_z, 0, allocation_size);

				free(alloc_z);
			}

			__forceinline void __fastcall reallocate(size_t size) {

				auto alloc_r = realloc(allocation, size);

				if (!alloc_r)
					throw qexcept::q_badalloc();

				allocation = std::move(alloc_r);

				allocation_size = size;

				_hash = qhash::qhash_cpu(allocation, size);
			}

			__forceinline void __fastcall swap(void* allocation_, size_t size) {

				if (!allocation_)
					return;
				try {

					if(allocation)
						free(allocation);

					allocation = allocation_;
					allocation_size = size;

					_hash = qhash::qhash_cpu(allocation_, size);
				}
				catch (std::exception& except) {};

			}

	#pragma endregion

	#pragma region Operators

			__forceinline index_proxy __fastcall operator[](size_t index) {
				return index_proxy(index, *this);
			}

	#pragma endregion

	#pragma region Destructor

			__forceinline __cdecl ~h_malloc() {
				try {

					if (allocation) {
						free(allocation);
						allocation = nullptr;
					}
				}
				catch (std::exception& except) {}
			}

	#pragma endregion
		};

	#pragma endregion
	}
}

#endif