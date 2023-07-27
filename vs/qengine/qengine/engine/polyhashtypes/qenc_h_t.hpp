#ifndef QENC_T_H
#define QENC_T_H

#include "../hashtypes/qhash_t.hpp"
#include "../../polyc/polyc.hpp"

#ifdef NDEBUG

#pragma optimize("", on)
#pragma inline_depth(255)
#pragma inline_recursion(on) 

#endif

using namespace qengine::polyc;

namespace qengine{

	namespace qenc_h_t {

	#pragma region Singleton 

		extern bool is_init;

	#pragma endregion

	#pragma region Static Methods

		__forceinline void __fastcall set_memory_violation_callback(qcallback::qmem_exception_rogue_c&& callback) {
			qhash_t::set_memory_violation_callback(callback);
		}

		__forceinline void __fastcall init_qenc_h_t(qcallback::qmem_exception_rogue_c callback = qhash_t::violation_callback_d) {

			if (is_init)
				return;

			qhash_t::set_memory_violation_callback(callback);

			is_init = true;
		}

	#pragma endregion

	#pragma region Types

	#pragma region WORD

	#pragma region 8-bit

		class q_int8 {

		private:

	#pragma region Encrypted value

			qhash_t::h_int8 _value;

	#pragma endregion

		public:

	#pragma region CTOR

			__forceinline __fastcall q_int8(char value = 0) : _value(algo_t_inst(value)) {

				if (!is_init)
					init_qenc_h_t();

				set(value);
			}

	#pragma endregion

	#pragma region Accessors

			__forceinline char __cdecl get() const {
				return algo_t_inst(_value.get());
			}

			__forceinline void __fastcall set(char value) {
				_value = algo_t_inst(value);
			}

			__forceinline void* __cdecl get_raw_memory_address() {
				return _value.get_raw_memory_address();
			}
	#pragma endregion

	#pragma region Operators

			__forceinline q_int8 __fastcall operator+(const char value) const {
				return q_int8(algo_t_inst(_value.get()) + value);
			};

			__forceinline q_int8 __fastcall operator-(const char value) const {
				return q_int8(algo_t_inst(_value.get()) - value);
			}

			__forceinline q_int8 __fastcall operator/(const char value) const {
				return q_int8(algo_t_inst(_value.get()) / value);
			}

			__forceinline q_int8 __fastcall operator*(const char value) const {
				return q_int8(algo_t_inst(_value.get()) * value);
			}

			__forceinline q_int8 __fastcall operator&(const char value) const {
				return q_int8(algo_t_inst(_value.get()) & value);
			}

			__forceinline q_int8 __fastcall operator|(const char value) const {
				return q_int8(algo_t_inst(_value.get()) | value);
			}

			__forceinline q_int8 __fastcall operator%(const char value) const {
				return q_int8(algo_t_inst(_value.get()) % value);
			}

			__forceinline q_int8 __fastcall operator^(const char value) const {
				return q_int8(algo_t_inst(_value.get()) ^ value);
			}

			__forceinline q_int8 __fastcall operator<<(const char value) const {
				return q_int8(algo_t_inst(_value.get()) << value);
			}

			__forceinline q_int8 __fastcall operator>>(const char value) const {
				return q_int8(algo_t_inst(_value.get()) >> value);
			}

			__forceinline q_int8& __fastcall operator+=(const char value) {
				this->_value = algo_t_inst(static_cast<char>(algo_t_inst(_value.get()) + value));
				return *this;
			}

			__forceinline q_int8& __fastcall operator-=(const char value) {
				this->_value = algo_t_inst(static_cast<char>(algo_t_inst(_value.get()) - value));
				return *this;
			}

			__forceinline q_int8& __cdecl operator++() {
				operator+=(1i8);
				return *this;
			}

			__forceinline q_int8& __cdecl operator--() {
				operator-=(1i8);
				return *this;
			}

			__forceinline q_int8& __fastcall operator*=(const char value) {
				this->_value = algo_t_inst(static_cast<char>(algo_t_inst(_value.get()) * value));
				return *this;
			}

			__forceinline q_int8& __fastcall operator/=(const char value) {
				this->_value = algo_t_inst(static_cast<char>(algo_t_inst(_value.get()) / value));
				return *this;
			}

			__forceinline q_int8& __fastcall operator%=(const char value) {
				this->_value = algo_t_inst(static_cast<char>(algo_t_inst(_value.get()) % value));
				return *this;
			}

			__forceinline q_int8& __fastcall operator^=(const char value) {
				this->_value = algo_t_inst(static_cast<char>(algo_t_inst(_value.get()) ^ value));
				return *this;
			}

			__forceinline q_int8& __fastcall operator&=(const char value) {
				this->_value = algo_t_inst(static_cast<char>(algo_t_inst(_value.get()) & value));
				return *this;
			}

			__forceinline q_int8& __fastcall operator|=(const char value) {
				this->_value = algo_t_inst(static_cast<char>(algo_t_inst(_value.get()) | value));
				return *this;
			}

			__forceinline q_int8& __fastcall operator<<=(const char value) {
				this->_value = algo_t_inst(static_cast<char>(algo_t_inst(_value.get()) << value));
				return *this;
			}

			__forceinline q_int8& __fastcall operator>>=(const char value) {
				this->_value = algo_t_inst(static_cast<char>(algo_t_inst(_value.get()) >> value));
				return *this;
			}

			__forceinline q_int8& __fastcall operator=(const char value) {
				_value = algo_t_inst(value);
				return *this;
			}

			__forceinline __cdecl operator char() const {
				return algo_t_inst(_value.get());
			}

			__forceinline __cdecl ~q_int8() {
				try {
					_value.~h_int8();
				}
				catch (std::exception& except) {}
			}
	#pragma endregion
		};

		class q_uint8 {

		private:

	#pragma region Encrypted value

			qhash_t::h_uint8 _value;

	#pragma endregion

		public:

	#pragma region CTOR

			__forceinline __fastcall q_uint8(byte value = 0) : _value(algo_t_inst(value)) {

				if (!is_init)
					init_qenc_h_t();

				set(value);
			}

	#pragma endregion

	#pragma region Accessors

			__forceinline byte __cdecl get() const {
				return algo_t_inst(_value.get());
			}

			__forceinline void __fastcall set(byte value) {
				_value = algo_t_inst(value);
			}

			__forceinline void* get_raw_memory_address() {
				return _value.get_raw_memory_address();
			}
	#pragma endregion

	#pragma region Operators

			__forceinline q_uint8 __fastcall operator+(const byte value) const {
				return q_uint8(algo_t_inst(_value.get()) + value);
			};

			__forceinline q_uint8 __fastcall operator-(const byte value) const {
				return q_uint8(algo_t_inst(_value.get()) - value);
			}

			__forceinline q_uint8 __fastcall operator/(const byte value) const {
				return q_uint8(algo_t_inst(_value.get()) / value);
			}

			__forceinline q_uint8 __fastcall operator*(const byte value) const {
				return q_uint8(algo_t_inst(_value.get()) * value);
			}

			__forceinline q_uint8 __fastcall operator&(const byte value) const {
				return q_uint8(algo_t_inst(_value.get()) & value);
			}

			__forceinline q_uint8 __fastcall operator|(const byte value) const {
				return q_uint8(algo_t_inst(_value.get()) | value);
			}

			__forceinline q_uint8 __fastcall operator%(const byte value) const {
				return q_uint8(algo_t_inst(_value.get()) % value);
			}

			__forceinline q_uint8 __fastcall operator^(const byte value) const {
				return q_uint8(algo_t_inst(_value.get()) ^ value);
			}

			__forceinline q_uint8 __fastcall operator<<(const byte value) const {
				return q_uint8(algo_t_inst(_value.get()) << value);
			}

			__forceinline q_uint8 __fastcall operator>>(const byte value) const {
				return q_uint8(algo_t_inst(_value.get()) >> value);
			}

			__forceinline q_uint8& __fastcall operator+=(const byte value) {
				this->_value = algo_t_inst(static_cast<byte>(algo_t_inst(_value.get()) + value));
				return *this;
			}

			__forceinline q_uint8& __fastcall operator-=(const byte value) {
				this->_value = algo_t_inst(static_cast<byte>(algo_t_inst(_value.get()) - value));
				return *this;
			}

			__forceinline q_uint8& __cdecl operator++() {
				operator+=(1ui8);
				return *this;
			}

			__forceinline q_uint8& __cdecl operator--() {
				operator-=(1ui8);
				return *this;
			}

			__forceinline q_uint8& __fastcall operator*=(const byte value) {
				this->_value = algo_t_inst(static_cast<byte>(algo_t_inst(_value.get()) * value));
				return *this;
			}

			__forceinline q_uint8& __fastcall operator/=(const byte value) {
				this->_value = algo_t_inst(static_cast<byte>(algo_t_inst(_value.get()) / value));
				return *this;
			}

			__forceinline q_uint8& __fastcall operator%=(const byte value) {
				this->_value = algo_t_inst(static_cast<byte>(algo_t_inst(_value.get()) % value));
				return *this;
			}

			__forceinline q_uint8& __fastcall operator^=(const byte value) {
				this->_value = algo_t_inst(static_cast<byte>(algo_t_inst(_value.get()) ^ value));
				return *this;
			}

			__forceinline q_uint8& __fastcall operator&=(const byte value) {
				this->_value = algo_t_inst(static_cast<byte>(algo_t_inst(_value.get()) & value));
				return *this;
			}

			__forceinline q_uint8& __fastcall operator|=(const byte value) {
				this->_value = algo_t_inst(static_cast<byte>(algo_t_inst(_value.get()) | value));
				return *this;
			}

			__forceinline q_uint8& __fastcall operator<<=(const byte value) {
				this->_value = algo_t_inst(static_cast<byte>(algo_t_inst(_value.get()) << value));
				return *this;
			}

			__forceinline q_uint8& __fastcall operator>>=(const byte value) {
				this->_value = algo_t_inst(static_cast<byte>(algo_t_inst(_value.get()) >> value));
				return *this;
			}

			__forceinline q_uint8& __fastcall operator=(const byte value) {
				_value = algo_t_inst(value);
				return *this;
			}

			__forceinline __cdecl operator byte() const {
				return algo_t_inst(_value.get());
			}

			__forceinline __cdecl ~q_uint8() {
				try {
					_value.~h_uint8();
				}
				catch (std::exception& except) {}
			}
	#pragma endregion
		};

	#pragma endregion

	#pragma region 16-bit

		class q_int16 {

		private:

	#pragma region Encrypted value

			qhash_t::h_int16 _value;

	#pragma endregion

		public:

	#pragma region CTOR

			__forceinline __fastcall q_int16(short value = 0) : _value(algo_t_inst(value)) {

				if (!is_init)
					init_qenc_h_t();

				set(value);
			}

	#pragma endregion

	#pragma region Accessors

			__forceinline short __cdecl get() const {
				return algo_t_inst(_value.get());
			}

			__forceinline void __fastcall set(short value) {
				_value = algo_t_inst(value);
			}

			__forceinline void* __cdecl get_raw_memory_address() {
				return _value.get_raw_memory_address();
			}
	#pragma endregion

	#pragma region Operators

			__forceinline q_int16 __fastcall operator+(const short value) const {
				return q_int16(algo_t_inst(_value.get()) + value);
			};

			__forceinline q_int16 __fastcall operator-(const short value) const {
				return q_int16(algo_t_inst(_value.get()) - value);
			}

			__forceinline q_int16 __fastcall operator/(const short value) const {
				return q_int16(algo_t_inst(_value.get()) / value);
			}

			__forceinline q_int16 __fastcall operator*(const short value) const {
				return q_int16(algo_t_inst(_value.get()) * value);
			}

			__forceinline q_int16 __fastcall operator&(const short value) const {
				return q_int16(algo_t_inst(_value.get()) & value);
			}

			__forceinline q_int16 __fastcall operator|(const short value) const {
				return q_int16(algo_t_inst(_value.get()) | value);
			}

			__forceinline q_int16 __fastcall operator%(const short value) const {
				return q_int16(algo_t_inst(_value.get()) % value);
			}

			__forceinline q_int16 __fastcall operator^(const short value) const {
				return q_int16(algo_t_inst(_value.get()) ^ value);
			}

			__forceinline q_int16 __fastcall operator<<(const short value) const {
				return q_int16(algo_t_inst(_value.get()) << value);
			}

			__forceinline q_int16 __fastcall operator>>(const short value) const {
				return q_int16(algo_t_inst(_value.get()) >> value);
			}

			__forceinline q_int16& __fastcall operator+=(const short value) {
				this->_value = algo_t_inst(static_cast<short>(algo_t_inst(_value.get()) + value));
				return *this;
			}

			__forceinline q_int16& __fastcall operator-=(const short value) {
				this->_value = algo_t_inst(static_cast<short>(algo_t_inst(_value.get()) - value));
				return *this;
			}

			__forceinline q_int16& __cdecl operator++() {
				operator+=(1i16);
				return *this;
			}

			__forceinline q_int16& __cdecl operator--() {
				operator-=(1i16);
				return *this;
			}

			__forceinline q_int16& __fastcall operator*=(const short value) {
				this->_value = algo_t_inst(static_cast<short>(algo_t_inst(_value.get()) * value));
				return *this;
			}

			__forceinline q_int16& __fastcall operator/=(const short value) {
				this->_value = algo_t_inst(static_cast<short>(algo_t_inst(_value.get()) / value));
				return *this;
			}

			__forceinline q_int16& __fastcall operator%=(const short value) {
				this->_value = algo_t_inst(static_cast<short>(algo_t_inst(_value.get()) % value));
				return *this;
			}

			__forceinline q_int16& __fastcall operator^=(const short value) {
				this->_value = algo_t_inst(static_cast<short>(algo_t_inst(_value.get()) ^ value));
				return *this;
			}

			__forceinline q_int16& __fastcall operator&=(const short value) {
				this->_value = algo_t_inst(static_cast<short>(algo_t_inst(_value.get()) & value));
				return *this;
			}

			__forceinline q_int16& __fastcall operator|=(const short value) {
				this->_value = algo_t_inst(static_cast<short>(algo_t_inst(_value.get()) | value));
				return *this;
			}

			__forceinline q_int16& __fastcall operator<<=(const short value) {
				this->_value = algo_t_inst(static_cast<short>(algo_t_inst(_value.get()) << value));
				return *this;
			}

			__forceinline q_int16& __fastcall operator>>=(const short value) {
				this->_value = algo_t_inst(static_cast<short>(algo_t_inst(_value.get()) >> value));
				return *this;
			}

			__forceinline q_int16& __fastcall operator=(const short value) {
				_value = algo_t_inst(value);
				return *this;
			}

			__forceinline __cdecl operator short() const {
				return algo_t_inst(_value.get());
			}

			__forceinline __cdecl ~q_int16() {
				try {
					_value.~h_int16();
				}
				catch (std::exception& except) {}
			}
	#pragma endregion
		};

		class q_uint16 {

		private:

	#pragma region Encrypted value

			qhash_t::h_uint16 _value;

	#pragma endregion

		public:

	#pragma region CTOR

			__forceinline __fastcall q_uint16(ushort value = 0) : _value(algo_t_inst(value)) {

				if (!is_init)
					init_qenc_h_t();

				set(value);
			}

	#pragma endregion

	#pragma region Accessors

			__forceinline ushort __cdecl get() const {
				return algo_t_inst(_value.get());
			}

			__forceinline void __fastcall set(ushort value) {
				_value = algo_t_inst(value);
			}

			__forceinline void* __cdecl get_raw_memory_address() {
				return _value.get_raw_memory_address();
			}
	#pragma endregion

	#pragma region Operators

			__forceinline q_uint16 __fastcall operator+(const ushort value) const {
				return q_uint16(algo_t_inst(_value.get()) + value);
			};

			__forceinline q_uint16 __fastcall operator-(const ushort value) const {
				return q_uint16(algo_t_inst(_value.get()) - value);
			}

			__forceinline q_uint16 __fastcall operator/(const ushort value) const {
				return q_uint16(algo_t_inst(_value.get()) / value);
			}

			__forceinline q_uint16 __fastcall operator*(const ushort value) const {
				return q_uint16(algo_t_inst(_value.get()) * value);
			}

			__forceinline q_uint16 __fastcall operator&(const ushort value) const {
				return q_uint16(algo_t_inst(_value.get()) & value);
			}

			__forceinline q_uint16 __fastcall operator|(const ushort value) const {
				return q_uint16(algo_t_inst(_value.get()) | value);
			}

			__forceinline q_uint16 __fastcall operator%(const ushort value) const {
				return q_uint16(algo_t_inst(_value.get()) % value);
			}

			__forceinline q_uint16 __fastcall operator^(const ushort value) const {
				return q_uint16(algo_t_inst(_value.get()) ^ value);
			}

			__forceinline q_uint16 __fastcall operator<<(const ushort value) const {
				return q_uint16(algo_t_inst(_value.get()) << value);
			}

			__forceinline q_uint16 __fastcall operator>>(const ushort value) const {
				return q_uint16(algo_t_inst(_value.get()) >> value);
			}

			__forceinline q_uint16& __fastcall operator+=(const ushort value) {
				this->_value = algo_t_inst(static_cast<ushort>(algo_t_inst(_value.get()) + value));
				return *this;
			}

			__forceinline q_uint16& __fastcall operator-=(const ushort value) {
				this->_value = algo_t_inst(static_cast<ushort>(algo_t_inst(_value.get()) - value));
				return *this;
			}

			__forceinline q_uint16& __cdecl operator++() {
				operator+=(1ui16);
				return *this;
			}

			__forceinline q_uint16& __cdecl operator--() {
				operator-=(1ui16);
				return *this;
			}

			__forceinline q_uint16& __fastcall operator*=(const ushort value) {
				this->_value = algo_t_inst(static_cast<ushort>(algo_t_inst(_value.get()) * value));
				return *this;
			}

			__forceinline q_uint16& __fastcall operator/=(const ushort value) {
				this->_value = algo_t_inst(static_cast<ushort>(algo_t_inst(_value.get()) / value));
				return *this;
			}

			__forceinline q_uint16& __fastcall operator%=(const ushort value) {
				this->_value = algo_t_inst(static_cast<ushort>(algo_t_inst(_value.get()) % value));
				return *this;
			}

			__forceinline q_uint16& __fastcall operator^=(const ushort value) {
				this->_value = algo_t_inst(static_cast<ushort>(algo_t_inst(_value.get()) ^ value));
				return *this;
			}

			__forceinline q_uint16& __fastcall operator&=(const ushort value) {
				this->_value = algo_t_inst(static_cast<ushort>(algo_t_inst(_value.get()) & value));
				return *this;
			}

			__forceinline q_uint16& __fastcall operator|=(const ushort value) {
				this->_value = algo_t_inst(static_cast<ushort>(algo_t_inst(_value.get()) | value));
				return *this;
			}

			__forceinline q_uint16& __fastcall operator<<=(const ushort value) {
				this->_value = algo_t_inst(static_cast<ushort>(algo_t_inst(_value.get()) << value));
				return *this;
			}

			__forceinline q_uint16& __fastcall operator>>=(const ushort value) {
				this->_value = algo_t_inst(static_cast<ushort>(algo_t_inst(_value.get()) >> value));
				return *this;
			}

			__forceinline q_uint16& __fastcall operator=(const ushort value) {
				_value = algo_t_inst(value);
				return *this;
			}

			__forceinline __cdecl operator ushort() const {
				return algo_t_inst(_value.get());
			}

			__forceinline __cdecl ~q_uint16() {
				try {
					_value.~h_uint16();
				}
				catch (std::exception& except) {}
			}
	#pragma endregion
		};

	#pragma endregion

	#pragma region 32-bit

		class q_int32 {

		private:

	#pragma region Encrypted value

			qhash_t::h_int32 _value;

	#pragma endregion

		public:

	#pragma region CTOR

			__forceinline __fastcall q_int32(int value = 0) : _value(algo_t_inst(value)) {

				if (!is_init)
					init_qenc_h_t();

				set(value);
			}

	#pragma endregion

	#pragma region Accessors

			__forceinline int __cdecl get() const {
				return algo_t_inst(_value.get());
			}

			__forceinline void __fastcall set(int value) {
				_value = algo_t_inst(value);
			}

			__forceinline void* __cdecl get_raw_memory_address() {
				return _value.get_raw_memory_address();
			}
	#pragma endregion

	#pragma region Operators

			__forceinline q_int32 __fastcall operator+(const int value) const {
				return q_int32(algo_t_inst(_value.get()) + value);
			};

			__forceinline q_int32 __fastcall operator-(const int value) const {
				return q_int32(algo_t_inst(_value.get()) - value);
			}

			__forceinline q_int32 __fastcall operator/(const int value) const {
				return q_int32(algo_t_inst(_value.get()) / value);
			}

			__forceinline q_int32 __fastcall operator*(const int value) const {
				return q_int32(algo_t_inst(_value.get()) * value);
			}

			__forceinline q_int32 __fastcall operator&(const int value) const {
				return q_int32(algo_t_inst(_value.get()) & value);
			}

			__forceinline q_int32 __fastcall operator|(const int value) const {
				return q_int32(algo_t_inst(_value.get()) | value);
			}

			__forceinline q_int32 __fastcall operator%(const int value) const {
				return q_int32(algo_t_inst(_value.get()) % value);
			}

			__forceinline q_int32 __fastcall operator^(const int value) const {
				return q_int32(algo_t_inst(_value.get()) ^ value);
			}

			__forceinline q_int32 __fastcall operator<<(const int value) const {
				return q_int32(algo_t_inst(_value.get()) << value);
			}

			__forceinline q_int32 __fastcall operator>>(const int value) const {
				return q_int32(algo_t_inst(_value.get()) >> value);
			}

			__forceinline q_int32& __fastcall operator+=(const int value) {
				this->_value = algo_t_inst(static_cast<int>(algo_t_inst(_value.get()) + value));
				return *this;
			}

			__forceinline q_int32& __fastcall operator-=(const int value) {
				this->_value = algo_t_inst(static_cast<int>(algo_t_inst(_value.get()) - value));
				return *this;
			}

			__forceinline q_int32& __cdecl operator++() {
				operator+=(1i32);
				return *this;
			}

			__forceinline q_int32& __cdecl operator--() {
				operator-=(1i32);
				return *this;
			}

			__forceinline q_int32& __fastcall operator*=(const int value) {
				this->_value = algo_t_inst(static_cast<int>(algo_t_inst(_value.get()) * value));
				return *this;
			}

			__forceinline q_int32& __fastcall operator/=(const int value) {
				this->_value = algo_t_inst(static_cast<int>(algo_t_inst(_value.get()) / value));
				return *this;
			}

			__forceinline q_int32& __fastcall operator%=(const int value) {
				this->_value = algo_t_inst(static_cast<int>(algo_t_inst(_value.get()) % value));
				return *this;
			}

			__forceinline q_int32& __fastcall operator^=(const int value) {
				this->_value = algo_t_inst(static_cast<int>(algo_t_inst(_value.get()) ^ value));
				return *this;
			}

			__forceinline q_int32& __fastcall operator&=(const int value) {
				this->_value = algo_t_inst(static_cast<int>(algo_t_inst(_value.get()) & value));
				return *this;
			}

			__forceinline q_int32& __fastcall operator|=(const int value) {
				this->_value = algo_t_inst(static_cast<int>(algo_t_inst(_value.get()) | value));
				return *this;
			}

			__forceinline q_int32& __fastcall operator<<=(const int value) {
				this->_value = algo_t_inst(static_cast<int>(algo_t_inst(_value.get()) << value));
				return *this;
			}

			__forceinline q_int32& __fastcall operator>>=(const int value) {
				this->_value = algo_t_inst(static_cast<int>(algo_t_inst(_value.get()) >> value));
				return *this;
			}

			__forceinline q_int32& __fastcall operator=(const int value) {
				_value = algo_t_inst(value);
				return *this;
			}

			__forceinline __cdecl operator int() const {
				return get();
			}

			__forceinline __cdecl ~q_int32() {
				try {
					_value.~h_int32();
				}
				catch (std::exception& except) {}
			}
	#pragma endregion
		};

		class q_uint32 {
		private:

	#pragma region Encrypted value

			qhash_t::h_uint32 _value;

	#pragma endregion

		public:

	#pragma region CTOR

			__forceinline __fastcall q_uint32(uint value = 0) : _value(algo_t_inst(value)) {

				if (!is_init)
					init_qenc_h_t();

				set(value);
			}

	#pragma endregion

	#pragma region Accessors

			__forceinline uint __cdecl get() const {
				return algo_t_inst(_value.get());
			}

			__forceinline void __fastcall set(uint value) {
				_value = algo_t_inst(value);
			}

			__forceinline void* __cdecl get_raw_memory_address() {
				return _value.get_raw_memory_address();
			}
	#pragma endregion

	#pragma region Operators

			__forceinline q_uint32 __fastcall operator+(const uint value) const {
				return q_uint32(algo_t_inst(_value.get()) + value);
			};

			__forceinline q_uint32 __fastcall operator-(const uint value) const {
				return q_uint32(algo_t_inst(_value.get()) - value);
			}

			__forceinline q_uint32 __fastcall operator/(const uint value) const {
				return q_uint32(algo_t_inst(_value.get()) / value);
			}

			__forceinline q_uint32 __fastcall operator*(const uint value) const {
				return q_uint32(algo_t_inst(_value.get()) * value);
			}

			__forceinline q_uint32 __fastcall operator&(const uint value) const {
				return q_uint32(algo_t_inst(_value.get()) & value);
			}

			__forceinline q_uint32 __fastcall operator|(const uint value) const {
				return q_uint32(algo_t_inst(_value.get()) | value);
			}

			__forceinline q_uint32 __fastcall operator%(const uint value) const {
				return q_uint32(algo_t_inst(_value.get()) % value);
			}

			__forceinline q_uint32 __fastcall operator^(const uint value) const {
				return q_uint32(algo_t_inst(_value.get()) ^ value);
			}

			__forceinline q_uint32 __fastcall operator<<(const uint value) const {
				return q_uint32(algo_t_inst(_value.get()) << value);
			}

			__forceinline q_uint32 __fastcall operator>>(const uint value) const {
				return q_uint32(algo_t_inst(_value.get()) >> value);
			}

			__forceinline q_uint32& __fastcall operator+=(const uint value) {
				this->_value = algo_t_inst(static_cast<int>(algo_t_inst(_value.get()) + value));
				return *this;
			}

			__forceinline q_uint32& __fastcall operator-=(const uint value) {
				this->_value = algo_t_inst(static_cast<int>(algo_t_inst(_value.get()) - value));
				return *this;
			}

			__forceinline q_uint32& __cdecl operator++() {
				operator+=(1ui32);
				return *this;
			}

			__forceinline q_uint32& __cdecl operator--() {
				operator-=(1ui32);
				return *this;
			}

			__forceinline q_uint32& __fastcall operator*=(const uint value) {
				this->_value = algo_t_inst(static_cast<uint>(algo_t_inst(_value.get()) * value));
				return *this;
			}

			__forceinline q_uint32& __fastcall operator/=(const uint value) {
				this->_value = algo_t_inst(static_cast<uint>(algo_t_inst(_value.get()) / value));
				return *this;
			}

			__forceinline q_uint32& __fastcall operator%=(const uint value) {
				this->_value = algo_t_inst(static_cast<uint>(algo_t_inst(_value.get()) % value));
				return *this;
			}

			__forceinline q_uint32& __fastcall operator^=(const uint value) {
				this->_value = algo_t_inst(static_cast<uint>(algo_t_inst(_value.get()) ^ value));
				return *this;
			}

			__forceinline q_uint32& __fastcall operator&=(const uint value) {
				this->_value = algo_t_inst(static_cast<uint>(algo_t_inst(_value.get()) & value));
				return *this;
			}

			__forceinline q_uint32& __fastcall operator|=(const uint value) {
				this->_value = algo_t_inst(static_cast<uint>(algo_t_inst(_value.get()) | value));
				return *this;
			}

			__forceinline q_uint32& __fastcall operator<<=(const uint value) {
				this->_value = algo_t_inst(static_cast<uint>(algo_t_inst(_value.get()) << value));
				return *this;
			}

			__forceinline q_uint32& __fastcall operator>>=(const uint value) {
				this->_value = algo_t_inst(static_cast<uint>(algo_t_inst(_value.get()) >> value));
				return *this;
			}

			__forceinline q_uint32& __fastcall operator=(const uint value) {
				_value = algo_t_inst(value);
				return *this;
			}

			__forceinline __cdecl operator uint() const {
				return algo_t_inst(_value.get());
			}

			__forceinline __cdecl ~q_uint32() {
				try {
					_value.~h_uint32();
				}
				catch (std::exception& except) {}
			}
	#pragma endregion
		};

	#pragma endregion

	#pragma region 64-bit

	#ifdef _WIN64

		class q_int64 {

		private:

	#pragma region Encrypted value

			qhash_t::h_int64 _value;

	#pragma endregion

		public:

	#pragma region CTOR

			__forceinline __fastcall q_int64(int64 value = 0) : _value(algo_t_inst(value)) {

				if (!is_init)
					init_qenc_h_t();

				set(value);
			}

	#pragma endregion

	#pragma region Accessors

			__forceinline int64 __cdecl get() const {
				return algo_t_inst(_value.get());
			}

			__forceinline void __fastcall set(int64 value) {
				_value = algo_t_inst(value);
			}

			__forceinline void* __cdecl get_raw_memory_address() {
				return _value.get_raw_memory_address();
			}
	#pragma endregion

	#pragma region Operators

			__forceinline q_int64 __fastcall operator+(const int64 value) const {
				return q_int64(algo_t_inst(_value.get()) + value);
			};

			__forceinline q_int64 __fastcall operator-(const int64 value) const {
				return q_int64(algo_t_inst(_value.get()) - value);
			}

			__forceinline q_int64 __fastcall operator/(const int64 value) const {
				return q_int64(algo_t_inst(_value.get()) / value);
			}

			__forceinline q_int64 __fastcall operator*(const int64 value) const {
				return q_int64(algo_t_inst(_value.get()) * value);
			}

			__forceinline q_int64 __fastcall operator&(const int64 value) const {
				return q_int64(algo_t_inst(_value.get()) & value);
			}

			__forceinline q_int64 __fastcall operator|(const int64 value) const {
				return q_int64(algo_t_inst(_value.get()) | value);
			}

			__forceinline q_int64 __fastcall operator%(const int64 value) const {
				return q_int64(algo_t_inst(_value.get()) % value);
			}

			__forceinline q_int64 __fastcall operator^(const int64 value) const {
				return q_int64(algo_t_inst(_value.get()) ^ value);
			}

			__forceinline q_int64 __fastcall operator<<(const int64 value) const {
				return q_int64(algo_t_inst(_value.get()) << value);
			}

			__forceinline q_int64 __fastcall operator>>(const int64 value) const {
				return q_int64(algo_t_inst(_value.get()) >> value);
			}

			__forceinline q_int64& __fastcall operator+=(const int64 value) {
				this->_value = algo_t_inst(static_cast<int64>(algo_t_inst(_value.get()) + value));
				return *this;
			}

			__forceinline q_int64& __fastcall operator-=(const int64 value) {
				this->_value = algo_t_inst(static_cast<int64>(algo_t_inst(_value.get()) - value));
				return *this;
			}

			__forceinline q_int64& __cdecl operator++() {
				operator+=(1i64);
				return *this;
			}

			__forceinline q_int64& __cdecl operator--() {
				operator-=(1i64);
				return *this;
			}

			__forceinline q_int64& __fastcall operator*=(const int64 value) {
				this->_value = algo_t_inst(static_cast<int64>(algo_t_inst(_value.get()) * value));
				return *this;
			}

			__forceinline q_int64& __fastcall operator/=(const int64 value) {
				this->_value = algo_t_inst(static_cast<int64>(algo_t_inst(_value.get()) / value));
				return *this;
			}

			__forceinline q_int64& __fastcall operator%=(const int64 value) {
				this->_value = algo_t_inst(static_cast<int64>(algo_t_inst(_value.get()) % value));
				return *this;
			}

			__forceinline q_int64& __fastcall operator^=(const int64 value) {
				this->_value = algo_t_inst(static_cast<int64>(algo_t_inst(_value.get()) ^ value));
				return *this;
			}

			__forceinline q_int64& __fastcall operator&=(const int64 value) {
				this->_value = algo_t_inst(static_cast<int64>(algo_t_inst(_value.get()) & value));
				return *this;
			}

			__forceinline q_int64& __fastcall operator|=(const int64 value) {
				this->_value = algo_t_inst(static_cast<int64>(algo_t_inst(_value.get()) | value));
				return *this;
			}

			__forceinline q_int64& __fastcall operator<<=(const int64 value) {
				this->_value = algo_t_inst(static_cast<int64>(algo_t_inst(_value.get()) << value));
				return *this;
			}

			__forceinline q_int64& __fastcall operator>>=(const int64 value) {
				this->_value = algo_t_inst(static_cast<int64>(algo_t_inst(_value.get()) >> value));
				return *this;
			}

			__forceinline q_int64& __fastcall operator=(const int64 value) {
				_value = algo_t_inst(value);
				return *this;
			}

			__forceinline __cdecl operator int64() const {
				return algo_t_inst(_value.get());
			}

			__forceinline __cdecl ~q_int64() {
				try {
					_value.~h_int64();
				}
				catch (std::exception& except) {}
			}
	#pragma endregion
		};

		class q_uint64 {
		private:

	#pragma region Encrypted value

			qhash_t::h_uint64 _value;

	#pragma endregion

		public:

	#pragma region CTOR

			__forceinline __fastcall q_uint64(uint64 value = 0) : _value(algo_t_inst(value)) {

				if (!is_init)
					init_qenc_h_t();

				set(value);
			}

	#pragma endregion

	#pragma region Accessors

			__forceinline uint64 __cdecl get() const {
				return algo_t_inst(_value.get());
			}

			__forceinline void __fastcall set(uint64 value) {
				_value = algo_t_inst(value);
			}

			__forceinline void* __cdecl get_raw_memory_address() {
				return _value.get_raw_memory_address();
			}
	#pragma endregion

	#pragma region Operators

			__forceinline q_uint64 __fastcall operator+(const uint64 value) const {
				return q_uint64(algo_t_inst(_value.get()) + value);
			};

			__forceinline q_uint64 __fastcall operator-(const uint64 value) const {
				return q_uint64(algo_t_inst(_value.get()) - value);
			}

			__forceinline q_uint64 __fastcall operator/(const uint64 value) const {
				return q_uint64(algo_t_inst(_value.get()) / value);
			}

			__forceinline q_uint64 __fastcall operator*(const uint64 value) const {
				return q_uint64(algo_t_inst(_value.get()) * value);
			}

			__forceinline q_uint64 __fastcall operator&(const uint64 value) const {
				return q_uint64(algo_t_inst(_value.get()) & value);
			}

			__forceinline q_uint64 __fastcall operator|(const uint64 value) const {
				return q_uint64(algo_t_inst(_value.get()) | value);
			}

			__forceinline q_uint64 __fastcall operator%(const uint64 value) const {
				return q_uint64(algo_t_inst(_value.get()) % value);
			}

			__forceinline q_uint64 __fastcall operator^(const uint64 value) const {
				return q_uint64(algo_t_inst(_value.get()) ^ value);
			}

			__forceinline q_uint64 __fastcall operator<<(const uint64 value) const {
				return q_uint64(algo_t_inst(_value.get()) << value);
			}

			__forceinline q_uint64 __fastcall operator>>(const uint64 value) const {
				return q_uint64(algo_t_inst(_value.get()) >> value);
			}

			__forceinline q_uint64& __fastcall operator+=(const uint64 value) {
				this->_value = algo_t_inst(static_cast<uint64>(algo_t_inst(_value.get()) + value));
				return *this;
			}

			__forceinline q_uint64& __fastcall operator-=(const uint64 value) {
				this->_value = algo_t_inst(static_cast<uint64>(algo_t_inst(_value.get()) - value));
				return *this;
			}

			__forceinline q_uint64& __cdecl operator++() {
				operator+=(1ui64);
				return *this;
			}

			__forceinline q_uint64& __cdecl operator--() {
				operator-=(1ui64);
				return *this;
			}

			__forceinline q_uint64& __fastcall operator*=(const uint64 value) {
				this->_value = algo_t_inst(static_cast<uint64>(algo_t_inst(_value.get()) * value));
				return *this;
			}

			__forceinline q_uint64& __fastcall operator/=(const uint64 value) {
				this->_value = algo_t_inst(static_cast<uint64>(algo_t_inst(_value.get()) / value));
				return *this;
			}

			__forceinline q_uint64& __fastcall operator%=(const uint64 value) {
				this->_value = algo_t_inst(static_cast<uint64>(algo_t_inst(_value.get()) % value));
				return *this;
			}

			__forceinline q_uint64& __fastcall operator^=(const uint64 value) {
				this->_value = algo_t_inst(static_cast<uint64>(algo_t_inst(_value.get()) ^ value));
				return *this;
			}

			__forceinline q_uint64& __fastcall operator&=(const uint64 value) {
				this->_value = algo_t_inst(static_cast<uint64>(algo_t_inst(_value.get()) & value));
				return *this;
			}

			__forceinline q_uint64& __fastcall operator|=(const uint64 value) {
				this->_value = algo_t_inst(static_cast<uint64>(algo_t_inst(_value.get()) | value));
				return *this;
			}

			__forceinline q_uint64& __fastcall operator<<=(const uint64 value) {
				this->_value = algo_t_inst(static_cast<uint64>(algo_t_inst(_value.get()) << value));
				return *this;
			}

			__forceinline q_uint64& __fastcall operator>>=(const uint64 value) {
				this->_value = algo_t_inst(static_cast<uint64>(algo_t_inst(_value.get()) >> value));
				return *this;
			}

			__forceinline q_uint64& __fastcall operator=(const uint64 value) {
				_value = algo_t_inst(value);
				return *this;
			}

			__forceinline __cdecl operator uint64() const {
				return algo_t_inst(_value.get());
			}

			__forceinline __cdecl ~q_uint64() {
				try {
					_value.~h_uint64();
				}
				catch (std::exception& except) {}
			}
	#pragma endregion
		};

	#endif

	#pragma endregion

	#pragma endregion

	#pragma region Floating Point

	#pragma region 32-bit

		class q_float {

		private:

	#pragma region Encrypted value

			qhash_t::h_float _value;

	#pragma endregion

		public:

	#pragma region CTOR

			__forceinline __fpcall q_float(float value = 0.f) : _value(algo_t_inst(value)) {

				if (!is_init)
					init_qenc_h_t();

				set(value);
			}

	#pragma endregion

	#pragma region Accessors

			__forceinline float __cdecl get() const {
				return algo_t_inst(_value.get());
			}

			__forceinline void __fpcall set(float value) {
				_value = algo_t_inst(value);
			}

			__forceinline void* __cdecl get_raw_memory_address() {
				return _value.get_raw_memory_address();
			}
	#pragma endregion

	#pragma region Operators

			__forceinline q_float __fpcall operator+(const float value) const {
				return q_float(algo_t_inst(_value.get()) + value);
			};

			__forceinline q_float __fpcall operator-(const float value) const {
				return q_float(algo_t_inst(_value.get()) - value);
			}

			__forceinline q_float __fpcall operator/(const float value) const {
				return q_float(algo_t_inst(_value.get()) / value);
			}

			__forceinline q_float __fpcall operator*(const float value) const {
				return q_float(algo_t_inst(_value.get()) * value);
			}

			__forceinline q_float& __fpcall operator+=(const float value) {
				this->_value = algo_t_inst(static_cast<float>(algo_t_inst(_value.get()) + value));
				return *this;
			}

			__forceinline q_float& __fpcall operator-=(const float value) {
				this->_value = algo_t_inst(static_cast<float>(algo_t_inst(_value.get()) - value));
				return *this;
			}

			__forceinline q_float& __cdecl operator++() {
				auto local_inst = 0.f;
				++local_inst;
				operator+=(local_inst);
				return *this;
			}

			__forceinline q_float& __cdecl operator--() {
				auto local_inst = 0.f;
				--local_inst;
				operator+=(local_inst);
				return *this;
			}

			__forceinline q_float& __fpcall operator*=(const float value) {
				this->_value = algo_t_inst(static_cast<float>(algo_t_inst(_value.get()) * value));
				return *this;
			}

			__forceinline q_float& __fpcall operator/=(const float value) {
				this->_value = algo_t_inst(static_cast<float>(algo_t_inst(_value.get()) / value));
				return *this;
			}

			__forceinline q_float& __fpcall operator=(const float value) {
				_value = algo_t_inst(value);
				return *this;
			}

			__forceinline __cdecl operator float() const {
				return algo_t_inst(_value.get());
			}

			__forceinline __cdecl ~q_float() {
				try {
					_value.~h_float();
				}
				catch (std::exception& except) {}
			}
	#pragma endregion
		};

	#pragma endregion

	#pragma region 64-bit

	#ifdef _WIN64

		class q_double {

		private:

	#pragma region Encrypted value

			qhash_t::h_double _value;

	#pragma endregion

		public:

	#pragma region CTOR

			__forceinline __fpcall q_double(double value = static_cast<double>(0.f)) : _value(algo_t_inst(value)) {

				if (!is_init)
					init_qenc_h_t();

				set(value);
			}

	#pragma endregion

	#pragma region Accessors

			__forceinline double __cdecl get() const {
				return algo_t_inst(_value.get());
			}

			__forceinline void __fpcall set(double value) {
				_value = algo_t_inst(value);
			}

			__forceinline void* __cdecl get_raw_memory_address() {
				return _value.get_raw_memory_address();
			}
	#pragma endregion

	#pragma region Operators

			__forceinline q_double __fpcall operator+(const double value) const {
				return q_double(algo_t_inst(_value.get()) + value);
			};

			__forceinline q_double __fpcall operator-(const double value) const {
				return q_double(algo_t_inst(_value.get()) - value);
			}

			__forceinline q_double __fpcall operator/(const double value) const {
				return q_double(algo_t_inst(_value.get()) / value);
			}

			__forceinline q_double __fpcall operator*(const double value) const {
				return q_double(algo_t_inst(_value.get()) * value);
			}

			__forceinline q_double& __fpcall operator+=(const double value) {
				this->_value = algo_t_inst(static_cast<double>(algo_t_inst(_value.get()) + value));
				return *this;
			}

			__forceinline q_double& __fpcall operator-=(const double value) {
				this->_value = algo_t_inst(static_cast<double>(algo_t_inst(_value.get()) - value));
				return *this;
			}

			__forceinline q_double& __cdecl operator++() {
				auto local_inst = static_cast<double>(0.f);
				++local_inst;
				operator+=(local_inst);
				return *this;
			}

			__forceinline q_double& __cdecl operator--() {
				auto local_inst = static_cast<double>(0.f);
				--local_inst;
				operator+=(local_inst);
				return *this;
			}

			__forceinline q_double& __fpcall operator*=(const double value) {
				this->_value = algo_t_inst(static_cast<double>(algo_t_inst(_value.get()) * value));
				return *this;
			}

			__forceinline q_double& __fpcall operator/=(const double value) {
				this->_value = algo_t_inst(static_cast<double>(algo_t_inst(_value.get()) / value));
				return *this;
			}

			__forceinline q_double& __fpcall operator=(const double value) {
				_value = algo_t_inst(value);
				return *this;
			}

			__forceinline __cdecl operator double() const {
				return algo_t_inst(_value.get());
			}

			__forceinline __cdecl ~q_double() {
				try {
					_value.~h_double();
				}
				catch (std::exception& except) {}
			}
	#pragma endregion
		};

	#endif

	#pragma endregion

	#pragma endregion

	#pragma region Extended Types

	#pragma region SSE

	#ifdef __SSE__

		class q_m128 {
		private:

	#pragma region Globals

			qhash_t::h_m128 _value;

	#pragma endregion

		public:

	#pragma region CTOR

			__forceinline __vectorcall q_m128(__m128 value) : _value(algo_t_inst(value)) {

				if (!is_init)
					init_qenc_h_t();

				set(value);
			}

	#pragma endregion

	#pragma region Accessors

			__forceinline __m128 __cdecl get() const {
				return algo_t_inst(_value.get());
			}

			__forceinline void __vectorcall set(__m128 value) {
				_value = algo_t_inst(value);
			}

			__forceinline decltype(_value)* get_raw_memory_address() {
				return &_value;
			}

	#pragma endregion

	#pragma region Operators

	#ifdef __clang__

			__forceinline q_m128 __vectorcall operator+(const __m128 value) const {
				return q_m128(get() + value);
			};

			__forceinline q_m128 __vectorcall operator-(const __m128 value) const {
				return q_m128(get() - value);
			}

			__forceinline q_m128 __vectorcall operator/(const __m128 value) const {
				return q_m128(get() / value);
			}

			__forceinline q_m128 __vectorcall operator*(const __m128 value) const {
				return q_m128(get() * value);
			}

			__forceinline q_m128& __vectorcall operator+=(const __m128 value) {
				set(static_cast<__m128>(get() + value));
				return *this;
			}

			__forceinline q_m128& __vectorcall operator-=(const __m128 value) {
				set(static_cast<__m128>(get() - value));
				return *this;
			}

			__forceinline q_m128& __vectorcall operator*=(const __m128 value) {
				set(static_cast<__m128>(get() * value));
				return *this;
			}

			__forceinline q_m128& __vectorcall operator/=(const __m128 value) {
				set(static_cast<__m128>(get() / value));
				return *this;
			}

	#endif

			__forceinline q_m128& __vectorcall operator=(const __m128 value) {
				set(value);
				return *this;
			}

			__forceinline __cdecl operator __m128() const {
				return get();
			}

			__forceinline __cdecl ~q_m128() {
				try {
					_value.~h_m128();
				}
				catch (std::exception& except) {}
			}
	#pragma endregion
		};

	#ifdef __SSE2__

		class q_m128i {

		private:

	#pragma region Globals

			qhash_t::h_m128i _value;

	#pragma endregion

		public:

	#pragma region CTOR

			__forceinline __vectorcall q_m128i(__m128i value) : _value(algo_t_inst(value)) {

				if (!is_init)
					init_qenc_h_t();

				set(value);
			}

	#pragma endregion

	#pragma region Accessors

			__forceinline __m128i __cdecl get() const {
				return algo_t_inst(_value.get());
			}

			__forceinline void __vectorcall set(__m128i value) {
				_value = algo_t_inst(value);
			}

			__forceinline decltype(_value)* get_raw_memory_address() {
				return &_value;
			}

	#pragma endregion

	#pragma region Operators

	#ifdef __clang__

			__forceinline q_m128i __vectorcall operator+(const __m128i value) const {
				return q_m128i(get() + value);
			};

			__forceinline q_m128i __vectorcall operator-(const __m128i value) const {
				return q_m128i(get() - value);
			}

			__forceinline q_m128i __vectorcall operator/(const __m128i value) const {
				return q_m128i(get() / value);
			}

			__forceinline q_m128i __vectorcall operator*(const __m128i value) const {
				return q_m128i(get() * value);
			}

			__forceinline q_m128i& __vectorcall operator+=(const __m128i value) {
				set(static_cast<__m128i>(get() + value));
				return *this;
			}

			__forceinline q_m128i& __vectorcall operator-=(const __m128i value) {
				set(static_cast<__m128i>(get() - value));
				return *this;
			}

			__forceinline q_m128i& __vectorcall operator*=(const __m128i value) {
				set(static_cast<__m128i>(get() * value));
				return *this;
			}

			__forceinline q_m128i& __vectorcall operator/=(const __m128i value) {
				set(static_cast<__m128i>(get() / value));
				return *this;
			}

	#endif

			__forceinline q_m128i& __vectorcall operator=(const __m128i value) {
				set(value);
				return *this;
			}

			__forceinline __cdecl operator __m128i() const {
				return get();
			}

			__forceinline __cdecl ~q_m128i() {
				try {
					_value.~h_m128i();
				}
				catch (std::exception& except) {}
			}
	#pragma endregion
		};

		class q_m128d {
		private:

	#pragma region Globals

			qhash_t::h_m128d _value;

	#pragma endregion

		public:

	#pragma region CTOR

			__forceinline __vectorcall q_m128d(__m128d value) : _value(algo_t_inst(value)) {

				if (!is_init)
					init_qenc_h_t();

				set(value);
			}

	#pragma endregion

	#pragma region Accessors

			__forceinline __m128d __cdecl get() const {
				return algo_t_inst(_value.get());
			}

			__forceinline void __vectorcall set(__m128d value) {
				_value = algo_t_inst(value);
			}

			__forceinline decltype(_value)* get_raw_memory_address() {
				return &_value;
			}

	#pragma endregion

	#pragma region Operators

	#ifdef __clang__

			__forceinline q_m128d __vectorcall operator+(const __m128d value) const {
				return q_m128d(get() + value);
			};

			__forceinline q_m128d __vectorcall operator-(const __m128d value) const {
				return q_m128d(get() - value);
			}

			__forceinline q_m128d __vectorcall operator/(const __m128d value) const {
				return q_m128d(get() / value);
			}

			__forceinline q_m128d __vectorcall operator*(const __m128d value) const {
				return q_m128d(get() * value);
			}

			__forceinline q_m128d& __vectorcall operator+=(const __m128d value) {
				set(static_cast<__m128d>(get() + value));
				return *this;
			}

			__forceinline q_m128d& __vectorcall operator-=(const __m128d value) {
				set(static_cast<__m128d>(get() - value));
				return *this;
			}

			__forceinline q_m128d& __vectorcall operator*=(const __m128d value) {
				set(static_cast<__m128d>(get() * value));
				return *this;
			}

			__forceinline q_m128d& __vectorcall operator/=(const __m128d value) {
				set(static_cast<__m128d>(get() / value));
				return *this;
			}

	#endif

			__forceinline q_m128d& __vectorcall operator=(const __m128d value) {
				set(value);
				return *this;
			}

			__forceinline __cdecl operator __m128d() const {
				return get();
			}

			__forceinline __cdecl ~q_m128d() {
				try {
					_value.~h_m128d();
				}
				catch (std::exception& except) {}
			}
	#pragma endregion
		};

	#endif

	#endif

	#pragma endregion

	#pragma region AVX

	#ifdef __AVX__

		class q_m256 {

		private:

	#pragma region Globals

			qhash_t::h_m256 _value;

	#pragma endregion

		public:

	#pragma region CTOR

			__forceinline __vectorcall q_m256(__m256 value) : _value(algo_t_inst(value)) {

				if (!is_init)
					init_qenc_h_t();

				set(value);
			}

	#pragma endregion

	#pragma region Accessors

			__forceinline __m256 __cdecl get() const {
				return algo_t_inst(_value.get());
			}

			__forceinline void __vectorcall set(__m256 value) {
				_value = algo_t_inst(value);
			}

			__forceinline decltype(_value)* get_raw_memory_address() {
				return &_value;
			}

	#pragma endregion

	#pragma region Operators

	#ifdef __clang__

			__forceinline q_m256 __vectorcall operator+(const __m256 value) const {
				return q_m256(get() + value);
			};

			__forceinline q_m256 __vectorcall operator-(const __m256 value) const {
				return q_m256(get() - value);
			}

			__forceinline q_m256 __vectorcall operator/(const __m256 value) const {
				return q_m256(get() / value);
			}

			__forceinline q_m256 __vectorcall operator*(const __m256 value) const {
				return q_m256(get() * value);
			}

			__forceinline q_m256& __vectorcall operator+=(const __m256 value) {
				set(static_cast<__m256>(get() + value));
				return *this;
			}

			__forceinline q_m256& __vectorcall operator-=(const __m256 value) {
				set(static_cast<__m256>(get() - value));
				return *this;
			}

			__forceinline q_m256& __vectorcall operator*=(const __m256 value) {
				set(static_cast<__m256>(get() * value));
				return *this;
			}

			__forceinline q_m256& __vectorcall operator/=(const __m256 value) {
				set(static_cast<__m256>(get() / value));
				return *this;
			}

	#endif

			__forceinline q_m256& __vectorcall operator=(const __m256 value) {
				set(value);
				return *this;
			}

			__forceinline __cdecl operator __m256() const {
				return get();
			}

			__forceinline __cdecl ~q_m256() {
				try {
					_value.~h_m256();
				}
				catch (std::exception& except) {}
			}
	#pragma endregion
		};

		class q_m256i {
		private:

	#pragma region Globals

			qhash_t::h_m256i _value;

	#pragma endregion

		public:

	#pragma region CTOR

			__forceinline __vectorcall q_m256i(__m256i value) : _value(algo_t_inst(value)) {

				if (!is_init)
					init_qenc_h_t();

				set(value);
			}

	#pragma endregion

	#pragma region Accessors

			__forceinline __m256i __cdecl get() const {
				return algo_t_inst(_value.get());
			}

			__forceinline void __vectorcall set(__m256i value) {
				_value = algo_t_inst(value);
			}

			__forceinline decltype(_value)* get_raw_memory_address() {
				return &_value;
			}

	#pragma endregion

	#pragma region Operators

	#ifdef __clang__

			__forceinline q_m256i __vectorcall operator+(const __m256i value) const {
				return q_m256i(get() + value);
			};

			__forceinline q_m256i __vectorcall operator-(const __m256i value) const {
				return q_m256i(get() - value);
			}

			__forceinline q_m256i __vectorcall operator/(const __m256i value) const {
				return q_m256i(get() / value);
			}

			__forceinline q_m256i __vectorcall operator*(const __m256i value) const {
				return q_m256i(get() * value);
			}

			__forceinline q_m256i& __vectorcall operator+=(const __m256i value) {
				set(static_cast<__m256i>(get() + value));
				return *this;
			}

			__forceinline q_m256i& __vectorcall operator-=(const __m256i value) {
				set(static_cast<__m256i>(get() - value));
				return *this;
			}

			__forceinline q_m256i& __vectorcall operator*=(const __m256i value) {
				set(static_cast<__m256i>(get() * value));
				return *this;
			}

			__forceinline q_m256i& __vectorcall operator/=(const __m256i value) {
				set(static_cast<__m256i>(get() / value));
				return *this;
			}

	#endif

			__forceinline q_m256i& __vectorcall operator=(const __m256i value) {
				set(value);
				return *this;
			}

			__forceinline __cdecl operator __m256i() const {
				return get();
			}

			__forceinline __cdecl ~q_m256i() {
				try {
					_value.~h_m256i();
				}
				catch (std::exception& except) {}
			}
	#pragma endregion
		};

		class q_m256d {

		private:

	#pragma region Globals

			qhash_t::h_m256d _value;

	#pragma endregion

		public:

	#pragma region CTOR

			__forceinline __vectorcall q_m256d(__m256d value) : _value(algo_t_inst(value)) {

				if (!is_init)
					init_qenc_h_t();

				set(value);
			}

	#pragma endregion

	#pragma region Accessors

			__forceinline __m256d __cdecl get() const {
				return algo_t_inst(_value.get());
			}

			__forceinline void __vectorcall set(__m256d value) {
				_value = algo_t_inst(value);
			}

			__forceinline decltype(_value)* get_raw_memory_address() {
				return &_value;
			}

	#pragma endregion

	#pragma region Operators

	#ifdef __clang__

			__forceinline q_m256d __vectorcall operator+(const __m256d value) const {
				return q_m256d(get() + value);
			};

			__forceinline q_m256d __vectorcall operator-(const __m256d value) const {
				return q_m256d(get() - value);
			}

			__forceinline q_m256d __vectorcall operator/(const __m256d value) const {
				return q_m256d(get() / value);
			}

			__forceinline q_m256d __vectorcall operator*(const __m256d value) const {
				return q_m256d(get() * value);
			}

			__forceinline q_m256d& __vectorcall operator+=(const __m256d value) {
				set(static_cast<__m256d>(get() + value));
				return *this;
			}

			__forceinline q_m256d& __vectorcall operator-=(const __m256d value) {
				set(static_cast<__m256d>(get() - value));
				return *this;
			}

			__forceinline q_m256d& __vectorcall operator*=(const __m256d value) {
				set(static_cast<__m256d>(get() * value));
				return *this;
			}

			__forceinline q_m256d& __vectorcall operator/=(const __m256d value) {
				set(static_cast<__m256d>(get() / value));
				return *this;
			}

	#endif

			__forceinline q_m256d& __vectorcall operator=(const __m256d value) {
				set(value);
				return *this;
			}

			__forceinline __cdecl operator __m256d() const {
				return get();
			}

			__forceinline __cdecl ~q_m256d() {
				try {
					_value.~h_m256d();
				}
				catch (std::exception& except) {}
			}
	#pragma endregion
		};

	#endif

	#pragma endregion

	#pragma endregion

	#pragma endregion

	#pragma region String

		class q_string {
		private:

	#pragma region Encrypted value

			qhash_t::h_string _value = "";

	#pragma endregion

		public:

	#pragma region CTOR

			__forceinline __cdecl q_string(const std::string value) : _value(algo_str_inst(value)) {

				if (!is_init)
					init_qenc_h_t();

				set(value);
			}

			__forceinline __cdecl q_string(const char* value = "") {

				if (!is_init)
					init_qenc_h_t();

				set(std::string(value));
			}

	#pragma endregion

	#pragma region Accessors

			__forceinline std::string __cdecl get() const {
				return algo_str_inst(_value.get());
			}

			__forceinline void __cdecl set(const std::string& value) {
				_value = algo_str_inst(value);
			}

			__forceinline std::string* __cdecl get_raw_memory_address() {
				return _value.get_raw_memory_address();
			}

	#pragma endregion

	#pragma region Operators

			__forceinline q_string __cdecl operator+(const std::string& value) const {
				return q_string(get() + value);
			}

			__forceinline q_string& __cdecl operator+=(const std::string& value) {
				set(static_cast<std::string>(get() + value));
				return *this;
			}

			__forceinline q_string& __cdecl operator=(const std::string& value) {
				set(value);
				return *this;
			}

			__forceinline __cdecl operator std::string() const {
				return get();
			}

			__forceinline __cdecl ~q_string() {
				try {
					_value.~h_string();
				}
				catch (std::exception& except) {}
			}

	#pragma endregion
		};

	#pragma endregion

	#pragma region Wide String

		class q_wstring {
		private:

	#pragma region Encrypted value

			qhash_t::h_wstring _value = L"";

	#pragma endregion

		public:

	#pragma region CTOR

			__forceinline __cdecl q_wstring(const std::wstring value) : _value(algo_wstr_inst(value)) {

				if (!is_init)
					init_qenc_h_t();

				set(value);
			}

			__forceinline __cdecl q_wstring(const wchar_t* value = L"") {

				if (!is_init)
					init_qenc_h_t();

				set(std::wstring(value));
			}

	#pragma endregion

	#pragma region Accessors

			__forceinline std::wstring __cdecl get() const {
				return algo_wstr_inst(_value.get());
			}

			__forceinline void __cdecl set(const std::wstring& value) {
				_value = algo_wstr_inst(value);
			}

			__forceinline std::wstring* __cdecl get_raw_memory_address() {
				return _value.get_raw_memory_address();
			}

	#pragma endregion

	#pragma region Operators

			__forceinline q_wstring __cdecl operator+(const std::wstring& value) const {
				return q_wstring(get() + value);
			}

			__forceinline q_wstring& __cdecl operator+=(const std::wstring& value) {
				set(static_cast<std::wstring>(get() + value));
				return *this;
			}

			__forceinline q_wstring& __cdecl operator=(const std::wstring& value) {
				set(value);
				return *this;
			}

			__forceinline __cdecl operator std::wstring() const {
				return get();
			}

			__forceinline __cdecl ~q_wstring() {
				try {
					_value.~h_wstring();
				}
				catch (std::exception& except) {}
			}

	#pragma endregion
		};

	#pragma endregion

	#pragma region Heap Allocation

		class q_malloc {

		private:

	#pragma region Globals

			qhash_t::h_malloc allocation;

	#pragma endregion

	#pragma region Subscript proxy

			// nested class to support subscript assignment
			class index_proxy {
			private:

	#pragma region Globals

				q_malloc& parent;
				size_t index;

	#pragma endregion

			public:
	#pragma region Ctor

				index_proxy(size_t index_, q_malloc& instance) : index(index_), parent(instance) { }

	#pragma endregion

	#pragma region Operator overrides

				__forceinline byte& operator=(byte value) {
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

			__forceinline __fastcall q_malloc(size_t size) : allocation(size) {
				if (!size)
					return;

				if (!is_init)
					init_qenc_h_t();

				if (!allocation.get_raw_memory_address())
					throw qexcept::q_badalloc();

			}

	#pragma endregion

	#pragma region Get Accessors

			__forceinline void __fastcall get(uintptr_t source_position, void* destination, size_t length) {
				void* dec_alloc = allocation.get();

				algo(dec_alloc, allocation.length());

				memcpy(destination, reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(dec_alloc) + source_position), length);

				free(dec_alloc);
			}

			__forceinline byte __fastcall get(uintptr_t position) {
				byte _return = NULL;

				get(position, &_return, sizeof(_return));

				return _return;
			}

			__forceinline void* __fastcall get() {
				auto _return = allocation.get();

				algo(_return, allocation.length());

				return _return;
			}

	#pragma endregion

	#pragma region Set Accessors

			__forceinline void __fastcall set(uintptr_t position, void* data, size_t length) {
				auto dec_alloc = allocation.get();

				algo(dec_alloc, allocation.length());

				memcpy(reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(dec_alloc) + position), data, length);

				algo(dec_alloc, allocation.length());

				allocation.swap(dec_alloc, allocation.length());
			}

			template<typename T>
			__forceinline void __fastcall set(uintptr_t position, T&& value) {
				set(position, &value, sizeof(decltype(value)));
			}

	#pragma endregion

	#pragma region Utility functions

			__forceinline void __fastcall reallocate(size_t size) {
				allocation.reallocate(size);
			}

			__forceinline void __fastcall swap(void* allocation_, size_t size, bool free_source = false) {
				if (!size)
					throw qexcept::q_badalloc();

				void* enc_alloc = malloc(size);

				memcpy(enc_alloc, allocation_, size);

				algo(enc_alloc, size);

				if (free_source)
					free(allocation_);

				allocation.swap(enc_alloc, size);
			}

			__forceinline void* get_raw_memory_address() {
				return allocation.get_raw_memory_address();
			}

	#pragma endregion

	#pragma region Operators

			__forceinline index_proxy __fastcall operator[](size_t index) {
				return index_proxy(index, *this);
			}

	#pragma endregion

	#pragma region Destructor

			__forceinline ~q_malloc() {
				try {
					allocation.~h_malloc();
				}
				catch (std::exception& except) {}
			}

	#pragma endregion
		};

	#pragma endregion
	}
}

#endif