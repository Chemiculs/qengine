#pragma region Header Guard

#ifndef QENCHASH_T_H
#define QENCHASH_T_H

#pragma endregion

#pragma region Imports

#pragma region qengine

#include "../hashtypes/qtype_hash.hpp"
#include "../../polyc/polyc.hpp"

#pragma endregion

#pragma endregion

#pragma region Preprocessor

#ifdef NDEBUG

#pragma optimize("", on)
#pragma inline_depth(255)
#pragma inline_recursion(on) 

#endif

#pragma endregion

#pragma region Using Directives

using namespace qengine::polyc;

#pragma endregion

namespace qengine{

	namespace qtype_enchash {

	#pragma region Singleton 

		extern bool is_init;

	#pragma endregion

	#pragma region Static Methods

		__forceinline void __cdecl set_memory_violation_callback(qcallback::qmem_exception_rogue_c callback) noexcept {
			qtype_hash::set_memory_violation_callback(callback);
		}

		__forceinline void __cdecl init_qtype_hash(qcallback::qmem_exception_rogue_c callback = qtype_hash::violation_callback_d) noexcept {

			if (is_init)
				return;

			qtype_hash::set_memory_violation_callback(callback);

			is_init = true;
		}

	#pragma endregion

	#pragma region Types

	#pragma region WORD

	#pragma region 8-bit

		class qeh_int8 {

		private:

	#pragma region Encrypted value

			qtype_hash::qh_int8 _value;

	#pragma endregion

		public:

	#pragma region CTOR

			__forceinline __fastcall qeh_int8(const std::int8_t value = 0) noexcept : _value(algo_t_inst(value)) {

				if (!is_init)
					init_qtype_hash();

				set(value);
			}

	#pragma endregion

	#pragma region Accessors

			__forceinline char __cdecl get() const noexcept {
				return algo_t_inst(_value.get());
			}

			__forceinline void __fastcall set(const std::int8_t value) noexcept {
				_value = algo_t_inst(value);
			}

			__forceinline void* __cdecl get_raw_memory_address() const noexcept {
				return _value.get_raw_memory_address();
			}
	#pragma endregion

	#pragma region Operators

			__forceinline qeh_int8 __fastcall operator+(const std::int8_t value) const noexcept {
				return qeh_int8(algo_t_inst(_value.get()) + value);
			};

			__forceinline qeh_int8 __fastcall operator-(const std::int8_t value) const noexcept {
				return qeh_int8(algo_t_inst(_value.get()) - value);
			}

			__forceinline qeh_int8 __fastcall operator/(const std::int8_t value) const noexcept {
				return qeh_int8(algo_t_inst(_value.get()) / value);
			}

			__forceinline qeh_int8 __fastcall operator*(const std::int8_t value) const noexcept {
				return qeh_int8(algo_t_inst(_value.get()) * value);
			}

			__forceinline qeh_int8 __fastcall operator&(const std::int8_t value) const noexcept {
				return qeh_int8(algo_t_inst(_value.get()) & value);
			}

			__forceinline qeh_int8 __fastcall operator|(const std::int8_t value) const noexcept {
				return qeh_int8(algo_t_inst(_value.get()) | value);
			}

			__forceinline qeh_int8 __fastcall operator%(const std::int8_t value) const noexcept {
				return qeh_int8(algo_t_inst(_value.get()) % value);
			}

			__forceinline qeh_int8 __fastcall operator^(const std::int8_t value) const noexcept {
				return qeh_int8(algo_t_inst(_value.get()) ^ value);
			}

			__forceinline qeh_int8 __fastcall operator<<(const std::int8_t value) const noexcept {
				return qeh_int8(algo_t_inst(_value.get()) << value);
			}

			__forceinline qeh_int8 __fastcall operator>>(const std::int8_t value) const noexcept {
				return qeh_int8(algo_t_inst(_value.get()) >> value);
			}

			__forceinline qeh_int8& __fastcall operator+=(const std::int8_t value) noexcept {
				this->_value = algo_t_inst(static_cast<std::int8_t>(algo_t_inst(_value.get()) + value));
				return *this;
			}

			__forceinline qeh_int8& __fastcall operator-=(const std::int8_t value) noexcept {
				this->_value = algo_t_inst(static_cast<std::int8_t>(algo_t_inst(_value.get()) - value));
				return *this;
			}

			__forceinline qeh_int8& __cdecl operator++() noexcept {
				operator+=(1i8);
				return *this;
			}

			__forceinline qeh_int8& __cdecl operator--() noexcept {
				operator-=(1i8);
				return *this;
			}

			__forceinline qeh_int8& __fastcall operator*=(const std::int8_t value) noexcept {
				this->_value = algo_t_inst(static_cast<std::int8_t>(algo_t_inst(_value.get()) * value));
				return *this;
			}

			__forceinline qeh_int8& __fastcall operator/=(const std::int8_t value) noexcept {
				this->_value = algo_t_inst(static_cast<std::int8_t>(algo_t_inst(_value.get()) / value));
				return *this;
			}

			__forceinline qeh_int8& __fastcall operator%=(const std::int8_t value) noexcept {
				this->_value = algo_t_inst(static_cast<std::int8_t>(algo_t_inst(_value.get()) % value));
				return *this;
			}

			__forceinline qeh_int8& __fastcall operator^=(const std::int8_t value) noexcept {
				this->_value = algo_t_inst(static_cast<std::int8_t>(algo_t_inst(_value.get()) ^ value));
				return *this;
			}

			__forceinline qeh_int8& __fastcall operator&=(const std::int8_t value) noexcept {
				this->_value = algo_t_inst(static_cast<std::int8_t>(algo_t_inst(_value.get()) & value));
				return *this;
			}

			__forceinline qeh_int8& __fastcall operator|=(const std::int8_t value) noexcept {
				this->_value = algo_t_inst(static_cast<std::int8_t>(algo_t_inst(_value.get()) | value));
				return *this;
			}

			__forceinline qeh_int8& __fastcall operator<<=(const std::int8_t value) noexcept {
				this->_value = algo_t_inst(static_cast<std::int8_t>(algo_t_inst(_value.get()) << value));
				return *this;
			}

			__forceinline qeh_int8& __fastcall operator>>=(const std::int8_t value) noexcept {
				this->_value = algo_t_inst(static_cast<std::int8_t>(algo_t_inst(_value.get()) >> value));
				return *this;
			}

			__forceinline qeh_int8& __fastcall operator=(const std::int8_t value) noexcept {
				_value = algo_t_inst(value);
				return *this;
			}

			__forceinline __cdecl operator char() const noexcept {
				return algo_t_inst(_value.get());
			}

			__forceinline __cdecl ~qeh_int8() noexcept { }
	#pragma endregion
		};

		class qeh_uint8 {

		private:

	#pragma region Encrypted value

			qtype_hash::qh_uint8 _value;

	#pragma endregion

		public:

	#pragma region CTOR

			__forceinline __fastcall qeh_uint8(const std::uint8_t value = 0) noexcept : _value(algo_t_inst(value)) {

				if (!is_init)
					init_qtype_hash();

				set(value);
			}

	#pragma endregion

	#pragma region Accessors

			__forceinline std::uint8_t __cdecl get() const noexcept {
				return algo_t_inst(_value.get());
			}

			__forceinline void __fastcall set(const std::uint8_t value) noexcept {
				_value = algo_t_inst(value);
			}

			__forceinline void* get_raw_memory_address() const noexcept {
				return _value.get_raw_memory_address();
			}
	#pragma endregion

	#pragma region Operators

			__forceinline qeh_uint8 __fastcall operator+(const std::uint8_t value) const noexcept {
				return qeh_uint8(algo_t_inst(_value.get()) + value);
			};

			__forceinline qeh_uint8 __fastcall operator-(const std::uint8_t value) const noexcept {
				return qeh_uint8(algo_t_inst(_value.get()) - value);
			}

			__forceinline qeh_uint8 __fastcall operator/(const std::uint8_t value) const noexcept {
				return qeh_uint8(algo_t_inst(_value.get()) / value);
			}

			__forceinline qeh_uint8 __fastcall operator*(const std::uint8_t value) const noexcept {
				return qeh_uint8(algo_t_inst(_value.get()) * value);
			}

			__forceinline qeh_uint8 __fastcall operator&(const std::uint8_t value) const noexcept {
				return qeh_uint8(algo_t_inst(_value.get()) & value);
			}

			__forceinline qeh_uint8 __fastcall operator|(const std::uint8_t value) const noexcept {
				return qeh_uint8(algo_t_inst(_value.get()) | value);
			}

			__forceinline qeh_uint8 __fastcall operator%(const std::uint8_t value) const noexcept {
				return qeh_uint8(algo_t_inst(_value.get()) % value);
			}

			__forceinline qeh_uint8 __fastcall operator^(const std::uint8_t value) const noexcept {
				return qeh_uint8(algo_t_inst(_value.get()) ^ value);
			}

			__forceinline qeh_uint8 __fastcall operator<<(const std::uint8_t value) const noexcept {
				return qeh_uint8(algo_t_inst(_value.get()) << value);
			}

			__forceinline qeh_uint8 __fastcall operator>>(const std::uint8_t value) const noexcept {
				return qeh_uint8(algo_t_inst(_value.get()) >> value);
			}

			__forceinline qeh_uint8& __fastcall operator+=(const std::uint8_t value) noexcept {
				this->_value = algo_t_inst(static_cast<std::uint8_t>(algo_t_inst(_value.get()) + value));
				return *this;
			}

			__forceinline qeh_uint8& __fastcall operator-=(const std::uint8_t value) noexcept {
				this->_value = algo_t_inst(static_cast<std::uint8_t>(algo_t_inst(_value.get()) - value));
				return *this;
			}

			__forceinline qeh_uint8& __cdecl operator++() noexcept {
				operator+=(1ui8);
				return *this;
			}

			__forceinline qeh_uint8& __cdecl operator--() noexcept {
				operator-=(1ui8);
				return *this;
			}

			__forceinline qeh_uint8& __fastcall operator*=(const std::uint8_t value) noexcept {
				this->_value = algo_t_inst(static_cast<std::uint8_t>(algo_t_inst(_value.get()) * value));
				return *this;
			}

			__forceinline qeh_uint8& __fastcall operator/=(const std::uint8_t value) noexcept {
				this->_value = algo_t_inst(static_cast<std::uint8_t>(algo_t_inst(_value.get()) / value));
				return *this;
			}

			__forceinline qeh_uint8& __fastcall operator%=(const std::uint8_t value) noexcept {
				this->_value = algo_t_inst(static_cast<std::uint8_t>(algo_t_inst(_value.get()) % value));
				return *this;
			}

			__forceinline qeh_uint8& __fastcall operator^=(const std::uint8_t value) noexcept {
				this->_value = algo_t_inst(static_cast<std::uint8_t>(algo_t_inst(_value.get()) ^ value));
				return *this;
			}

			__forceinline qeh_uint8& __fastcall operator&=(const std::uint8_t value) noexcept {
				this->_value = algo_t_inst(static_cast<std::uint8_t>(algo_t_inst(_value.get()) & value));
				return *this;
			}

			__forceinline qeh_uint8& __fastcall operator|=(const std::uint8_t value) noexcept {
				this->_value = algo_t_inst(static_cast<std::uint8_t>(algo_t_inst(_value.get()) | value));
				return *this;
			}

			__forceinline qeh_uint8& __fastcall operator<<=(const std::uint8_t value) noexcept {
				this->_value = algo_t_inst(static_cast<std::uint8_t>(algo_t_inst(_value.get()) << value));
				return *this;
			}

			__forceinline qeh_uint8& __fastcall operator>>=(const std::uint8_t value) noexcept {
				this->_value = algo_t_inst(static_cast<std::uint8_t>(algo_t_inst(_value.get()) >> value));
				return *this;
			}

			__forceinline qeh_uint8& __fastcall operator=(const std::uint8_t value) noexcept {
				_value = algo_t_inst(value);
				return *this;
			}

			__forceinline __cdecl operator std::uint8_t() const noexcept {
				return algo_t_inst(_value.get());
			}

			__forceinline __cdecl ~qeh_uint8() noexcept { }
	#pragma endregion
		};

	#pragma endregion

	#pragma region 16-bit

		class qeh_int16 {

		private:

	#pragma region Encrypted value

			qtype_hash::qh_int16 _value;

	#pragma endregion

		public:

	#pragma region CTOR

			__forceinline __fastcall qeh_int16(const short value = 0) noexcept : _value(algo_t_inst(value)) {

				if (!is_init)
					init_qtype_hash();

				set(value);
			}

	#pragma endregion

	#pragma region Accessors

			__forceinline short __cdecl get() const noexcept {
				return algo_t_inst(_value.get());
			}

			__forceinline void __fastcall set(const short value) noexcept {
				_value = algo_t_inst(value);
			}

			__forceinline void* __cdecl get_raw_memory_address() noexcept {
				return _value.get_raw_memory_address();
			}
	#pragma endregion

	#pragma region Operators

			__forceinline qeh_int16 __fastcall operator+(const short value) const noexcept {
				return qeh_int16(algo_t_inst(_value.get()) + value);
			};

			__forceinline qeh_int16 __fastcall operator-(const short value) const noexcept {
				return qeh_int16(algo_t_inst(_value.get()) - value);
			}

			__forceinline qeh_int16 __fastcall operator/(const short value) const noexcept {
				return qeh_int16(algo_t_inst(_value.get()) / value);
			}

			__forceinline qeh_int16 __fastcall operator*(const short value) const noexcept {
				return qeh_int16(algo_t_inst(_value.get()) * value);
			}

			__forceinline qeh_int16 __fastcall operator&(const short value) const noexcept {
				return qeh_int16(algo_t_inst(_value.get()) & value);
			}

			__forceinline qeh_int16 __fastcall operator|(const short value) const noexcept {
				return qeh_int16(algo_t_inst(_value.get()) | value);
			}

			__forceinline qeh_int16 __fastcall operator%(const short value) const noexcept {
				return qeh_int16(algo_t_inst(_value.get()) % value);
			}

			__forceinline qeh_int16 __fastcall operator^(const short value) const noexcept {
				return qeh_int16(algo_t_inst(_value.get()) ^ value);
			}

			__forceinline qeh_int16 __fastcall operator<<(const short value) const noexcept {
				return qeh_int16(algo_t_inst(_value.get()) << value);
			}

			__forceinline qeh_int16 __fastcall operator>>(const short value) const noexcept {
				return qeh_int16(algo_t_inst(_value.get()) >> value);
			}

			__forceinline qeh_int16& __fastcall operator+=(const short value) noexcept {
				this->_value = algo_t_inst(static_cast<short>(algo_t_inst(_value.get()) + value));
				return *this;
			}

			__forceinline qeh_int16& __fastcall operator-=(const short value) noexcept {
				this->_value = algo_t_inst(static_cast<short>(algo_t_inst(_value.get()) - value));
				return *this;
			}

			__forceinline qeh_int16& __cdecl operator++() noexcept {
				operator+=(1i16);
				return *this;
			}

			__forceinline qeh_int16& __cdecl operator--() noexcept {
				operator-=(1i16);
				return *this;
			}

			__forceinline qeh_int16& __fastcall operator*=(const short value) noexcept {
				this->_value = algo_t_inst(static_cast<short>(algo_t_inst(_value.get()) * value));
				return *this;
			}

			__forceinline qeh_int16& __fastcall operator/=(const short value) noexcept {
				this->_value = algo_t_inst(static_cast<short>(algo_t_inst(_value.get()) / value));
				return *this;
			}

			__forceinline qeh_int16& __fastcall operator%=(const short value) noexcept {
				this->_value = algo_t_inst(static_cast<short>(algo_t_inst(_value.get()) % value));
				return *this;
			}

			__forceinline qeh_int16& __fastcall operator^=(const short value) noexcept {
				this->_value = algo_t_inst(static_cast<short>(algo_t_inst(_value.get()) ^ value));
				return *this;
			}

			__forceinline qeh_int16& __fastcall operator&=(const short value) noexcept {
				this->_value = algo_t_inst(static_cast<short>(algo_t_inst(_value.get()) & value));
				return *this;
			}

			__forceinline qeh_int16& __fastcall operator|=(const short value) noexcept {
				this->_value = algo_t_inst(static_cast<short>(algo_t_inst(_value.get()) | value));
				return *this;
			}

			__forceinline qeh_int16& __fastcall operator<<=(const short value) noexcept {
				this->_value = algo_t_inst(static_cast<short>(algo_t_inst(_value.get()) << value));
				return *this;
			}

			__forceinline qeh_int16& __fastcall operator>>=(const short value) noexcept {
				this->_value = algo_t_inst(static_cast<short>(algo_t_inst(_value.get()) >> value));
				return *this;
			}

			__forceinline qeh_int16& __fastcall operator=(const short value) noexcept {
				_value = algo_t_inst(value);
				return *this;
			}

			__forceinline __cdecl operator short() const noexcept {
				return algo_t_inst(_value.get());
			}

			__forceinline __cdecl ~qeh_int16() noexcept { }
	#pragma endregion
		};

		class qeh_uint16 {

		private:

	#pragma region Encrypted value

			qtype_hash::qh_uint16 _value;

	#pragma endregion

		public:

	#pragma region CTOR

			__forceinline __fastcall qeh_uint16(const std::uint16_t value = 0) noexcept : _value(algo_t_inst(value)) {

				if (!is_init)
					init_qtype_hash();

				set(value);
			}

	#pragma endregion

	#pragma region Accessors

			__forceinline std::uint16_t __cdecl get() const noexcept {
				return algo_t_inst(_value.get());
			}

			__forceinline void __fastcall set(const std::uint16_t value) noexcept {
				_value = algo_t_inst(value);
			}

			__forceinline void* __cdecl get_raw_memory_address() const noexcept {
				return _value.get_raw_memory_address();
			}
	#pragma endregion

	#pragma region Operators

			__forceinline qeh_uint16 __fastcall operator+(const std::uint16_t value) const noexcept {
				return qeh_uint16(algo_t_inst(_value.get()) + value);
			};

			__forceinline qeh_uint16 __fastcall operator-(const std::uint16_t value) const noexcept {
				return qeh_uint16(algo_t_inst(_value.get()) - value);
			}

			__forceinline qeh_uint16 __fastcall operator/(const std::uint16_t value) const noexcept {
				return qeh_uint16(algo_t_inst(_value.get()) / value);
			}

			__forceinline qeh_uint16 __fastcall operator*(const std::uint16_t value) const noexcept {
				return qeh_uint16(algo_t_inst(_value.get()) * value);
			}

			__forceinline qeh_uint16 __fastcall operator&(const std::uint16_t value) const noexcept {
				return qeh_uint16(algo_t_inst(_value.get()) & value);
			}

			__forceinline qeh_uint16 __fastcall operator|(const std::uint16_t value) const noexcept {
				return qeh_uint16(algo_t_inst(_value.get()) | value);
			}

			__forceinline qeh_uint16 __fastcall operator%(const std::uint16_t value) const noexcept {
				return qeh_uint16(algo_t_inst(_value.get()) % value);
			}

			__forceinline qeh_uint16 __fastcall operator^(const std::uint16_t value) const noexcept {
				return qeh_uint16(algo_t_inst(_value.get()) ^ value);
			}

			__forceinline qeh_uint16 __fastcall operator<<(const std::uint16_t value) const noexcept {
				return qeh_uint16(algo_t_inst(_value.get()) << value);
			}

			__forceinline qeh_uint16 __fastcall operator>>(const std::uint16_t value) const noexcept {
				return qeh_uint16(algo_t_inst(_value.get()) >> value);
			}

			__forceinline qeh_uint16& __fastcall operator+=(const std::uint16_t value) noexcept {
				this->_value = algo_t_inst(static_cast<std::uint16_t>(algo_t_inst(_value.get()) + value));
				return *this;
			}

			__forceinline qeh_uint16& __fastcall operator-=(const std::uint16_t value) noexcept {
				this->_value = algo_t_inst(static_cast<std::uint16_t>(algo_t_inst(_value.get()) - value));
				return *this;
			}

			__forceinline qeh_uint16& __cdecl operator++() noexcept {
				operator+=(1ui16);
				return *this;
			}

			__forceinline qeh_uint16& __cdecl operator--() noexcept {
				operator-=(1ui16);
				return *this;
			}

			__forceinline qeh_uint16& __fastcall operator*=(const std::uint16_t value) noexcept {
				this->_value = algo_t_inst(static_cast<std::uint16_t>(algo_t_inst(_value.get()) * value));
				return *this;
			}

			__forceinline qeh_uint16& __fastcall operator/=(const std::uint16_t value) noexcept {
				this->_value = algo_t_inst(static_cast<std::uint16_t>(algo_t_inst(_value.get()) / value));
				return *this;
			}

			__forceinline qeh_uint16& __fastcall operator%=(const std::uint16_t value) noexcept {
				this->_value = algo_t_inst(static_cast<std::uint16_t>(algo_t_inst(_value.get()) % value));
				return *this;
			}

			__forceinline qeh_uint16& __fastcall operator^=(const std::uint16_t value) noexcept {
				this->_value = algo_t_inst(static_cast<std::uint16_t>(algo_t_inst(_value.get()) ^ value));
				return *this;
			}

			__forceinline qeh_uint16& __fastcall operator&=(const std::uint16_t value) noexcept {
				this->_value = algo_t_inst(static_cast<std::uint16_t>(algo_t_inst(_value.get()) & value));
				return *this;
			}

			__forceinline qeh_uint16& __fastcall operator|=(const std::uint16_t value) noexcept {
				this->_value = algo_t_inst(static_cast<std::uint16_t>(algo_t_inst(_value.get()) | value));
				return *this;
			}

			__forceinline qeh_uint16& __fastcall operator<<=(const std::uint16_t value) noexcept {
				this->_value = algo_t_inst(static_cast<std::uint16_t>(algo_t_inst(_value.get()) << value));
				return *this;
			}

			__forceinline qeh_uint16& __fastcall operator>>=(const std::uint16_t value) noexcept {
				this->_value = algo_t_inst(static_cast<std::uint16_t>(algo_t_inst(_value.get()) >> value));
				return *this;
			}

			__forceinline qeh_uint16& __fastcall operator=(const std::uint16_t value) noexcept {
				_value = algo_t_inst(value);
				return *this;
			}

			__forceinline __cdecl operator std::uint16_t() const noexcept {
				return algo_t_inst(_value.get());
			}

			__forceinline __cdecl ~qeh_uint16() noexcept { }
	#pragma endregion
		};

	#pragma endregion

	#pragma region 32-bit

		class qeh_int32 {

		private:

	#pragma region Encrypted value

			qtype_hash::qh_int32 _value;

	#pragma endregion

		public:

	#pragma region CTOR

			__forceinline __fastcall qeh_int32(const int value = 0) noexcept : _value(algo_t_inst(value)) {

				if (!is_init)
					init_qtype_hash();

				set(value);
			}

	#pragma endregion

	#pragma region Accessors

			__forceinline int __cdecl get() const noexcept {
				return algo_t_inst(_value.get());
			}

			__forceinline void __fastcall set(const int value) noexcept {
				_value = algo_t_inst(value);
			}

			__forceinline void* __cdecl get_raw_memory_address() const noexcept {
				return _value.get_raw_memory_address();
			}
	#pragma endregion

	#pragma region Operators

			__forceinline qeh_int32 __fastcall operator+(const int value) const noexcept {
				return qeh_int32(algo_t_inst(_value.get()) + value);
			};

			__forceinline qeh_int32 __fastcall operator-(const int value) const noexcept {
				return qeh_int32(algo_t_inst(_value.get()) - value);
			}

			__forceinline qeh_int32 __fastcall operator/(const int value) const noexcept {
				return qeh_int32(algo_t_inst(_value.get()) / value);
			}

			__forceinline qeh_int32 __fastcall operator*(const int value) const noexcept {
				return qeh_int32(algo_t_inst(_value.get()) * value);
			}

			__forceinline qeh_int32 __fastcall operator&(const int value) const noexcept {
				return qeh_int32(algo_t_inst(_value.get()) & value);
			}

			__forceinline qeh_int32 __fastcall operator|(const int value) const noexcept {
				return qeh_int32(algo_t_inst(_value.get()) | value);
			}

			__forceinline qeh_int32 __fastcall operator%(const int value) const noexcept {
				return qeh_int32(algo_t_inst(_value.get()) % value);
			}

			__forceinline qeh_int32 __fastcall operator^(const int value) const noexcept {
				return qeh_int32(algo_t_inst(_value.get()) ^ value);
			}

			__forceinline qeh_int32 __fastcall operator<<(const int value) const noexcept {
				return qeh_int32(algo_t_inst(_value.get()) << value);
			}

			__forceinline qeh_int32 __fastcall operator>>(const int value) const noexcept {
				return qeh_int32(algo_t_inst(_value.get()) >> value);
			}

			__forceinline qeh_int32& __fastcall operator+=(const int value) noexcept {
				this->_value = algo_t_inst(static_cast<int>(algo_t_inst(_value.get()) + value));
				return *this;
			}

			__forceinline qeh_int32& __fastcall operator-=(const int value) noexcept {
				this->_value = algo_t_inst(static_cast<int>(algo_t_inst(_value.get()) - value));
				return *this;
			}

			__forceinline qeh_int32& __cdecl operator++() noexcept {
				operator+=(1i32);
				return *this;
			}

			__forceinline qeh_int32& __cdecl operator--() noexcept {
				operator-=(1i32);
				return *this;
			}

			__forceinline qeh_int32& __fastcall operator*=(const int value) noexcept {
				this->_value = algo_t_inst(static_cast<int>(algo_t_inst(_value.get()) * value));
				return *this;
			}

			__forceinline qeh_int32& __fastcall operator/=(const int value) noexcept {
				this->_value = algo_t_inst(static_cast<int>(algo_t_inst(_value.get()) / value));
				return *this;
			}

			__forceinline qeh_int32& __fastcall operator%=(const int value) noexcept {
				this->_value = algo_t_inst(static_cast<int>(algo_t_inst(_value.get()) % value));
				return *this;
			}

			__forceinline qeh_int32& __fastcall operator^=(const int value) noexcept {
				this->_value = algo_t_inst(static_cast<int>(algo_t_inst(_value.get()) ^ value));
				return *this;
			}

			__forceinline qeh_int32& __fastcall operator&=(const int value) noexcept {
				this->_value = algo_t_inst(static_cast<int>(algo_t_inst(_value.get()) & value));
				return *this;
			}

			__forceinline qeh_int32& __fastcall operator|=(const int value) noexcept {
				this->_value = algo_t_inst(static_cast<int>(algo_t_inst(_value.get()) | value));
				return *this;
			}

			__forceinline qeh_int32& __fastcall operator<<=(const int value) noexcept {
				this->_value = algo_t_inst(static_cast<int>(algo_t_inst(_value.get()) << value));
				return *this;
			}

			__forceinline qeh_int32& __fastcall operator>>=(const int value) noexcept {
				this->_value = algo_t_inst(static_cast<int>(algo_t_inst(_value.get()) >> value));
				return *this;
			}

			__forceinline qeh_int32& __fastcall operator=(const int value) noexcept {
				_value = algo_t_inst(value);
				return *this;
			}

			__forceinline __cdecl operator int() const noexcept {
				return get();
			}

			__forceinline __cdecl ~qeh_int32() noexcept { }
	#pragma endregion
		};

		class qeh_uint32 {
		private:

	#pragma region Encrypted value

			qtype_hash::qh_uint32 _value;

	#pragma endregion

		public:

	#pragma region CTOR

			__forceinline __fastcall qeh_uint32(const std::uint32_t value = 0) noexcept : _value(algo_t_inst(value)) {

				if (!is_init)
					init_qtype_hash();

				set(value);
			}

	#pragma endregion

	#pragma region Accessors

			__forceinline std::uint32_t __cdecl get() const noexcept {
				return algo_t_inst(_value.get());
			}

			__forceinline void __fastcall set(const std::uint32_t value) noexcept {
				_value = algo_t_inst(value);
			}

			__forceinline void* __cdecl get_raw_memory_address() const noexcept {
				return _value.get_raw_memory_address();
			}
	#pragma endregion

	#pragma region Operators

			__forceinline qeh_uint32 __fastcall operator+(const std::uint32_t value) const noexcept {
				return qeh_uint32(algo_t_inst(_value.get()) + value);
			};

			__forceinline qeh_uint32 __fastcall operator-(const std::uint32_t value) const noexcept {
				return qeh_uint32(algo_t_inst(_value.get()) - value);
			}

			__forceinline qeh_uint32 __fastcall operator/(const std::uint32_t value) const noexcept {
				return qeh_uint32(algo_t_inst(_value.get()) / value);
			}

			__forceinline qeh_uint32 __fastcall operator*(const std::uint32_t value) const noexcept {
				return qeh_uint32(algo_t_inst(_value.get()) * value);
			}

			__forceinline qeh_uint32 __fastcall operator&(const std::uint32_t value) const noexcept {
				return qeh_uint32(algo_t_inst(_value.get()) & value);
			}

			__forceinline qeh_uint32 __fastcall operator|(const std::uint32_t value) const noexcept {
				return qeh_uint32(algo_t_inst(_value.get()) | value);
			}

			__forceinline qeh_uint32 __fastcall operator%(const std::uint32_t value) const noexcept {
				return qeh_uint32(algo_t_inst(_value.get()) % value);
			}

			__forceinline qeh_uint32 __fastcall operator^(const std::uint32_t value) const noexcept {
				return qeh_uint32(algo_t_inst(_value.get()) ^ value);
			}

			__forceinline qeh_uint32 __fastcall operator<<(const std::uint32_t value) const noexcept {
				return qeh_uint32(algo_t_inst(_value.get()) << value);
			}

			__forceinline qeh_uint32 __fastcall operator>>(const std::uint32_t value) const noexcept {
				return qeh_uint32(algo_t_inst(_value.get()) >> value);
			}

			__forceinline qeh_uint32& __fastcall operator+=(const std::uint32_t value) noexcept {
				this->_value = algo_t_inst(static_cast<int>(algo_t_inst(_value.get()) + value));
				return *this;
			}

			__forceinline qeh_uint32& __fastcall operator-=(const std::uint32_t value) noexcept {
				this->_value = algo_t_inst(static_cast<int>(algo_t_inst(_value.get()) - value));
				return *this;
			}

			__forceinline qeh_uint32& __cdecl operator++() noexcept {
				operator+=(1ui32);
				return *this;
			}

			__forceinline qeh_uint32& __cdecl operator--() noexcept {
				operator-=(1ui32);
				return *this;
			}

			__forceinline qeh_uint32& __fastcall operator*=(const std::uint32_t value) noexcept {
				this->_value = algo_t_inst(static_cast<std::uint32_t>(algo_t_inst(_value.get()) * value));
				return *this;
			}

			__forceinline qeh_uint32& __fastcall operator/=(const std::uint32_t value) noexcept {
				this->_value = algo_t_inst(static_cast<std::uint32_t>(algo_t_inst(_value.get()) / value));
				return *this;
			}

			__forceinline qeh_uint32& __fastcall operator%=(const std::uint32_t value) noexcept {
				this->_value = algo_t_inst(static_cast<std::uint32_t>(algo_t_inst(_value.get()) % value));
				return *this;
			}

			__forceinline qeh_uint32& __fastcall operator^=(const std::uint32_t value) noexcept {
				this->_value = algo_t_inst(static_cast<std::uint32_t>(algo_t_inst(_value.get()) ^ value));
				return *this;
			}

			__forceinline qeh_uint32& __fastcall operator&=(const std::uint32_t value) noexcept {
				this->_value = algo_t_inst(static_cast<std::uint32_t>(algo_t_inst(_value.get()) & value));
				return *this;
			}

			__forceinline qeh_uint32& __fastcall operator|=(const std::uint32_t value) noexcept {
				this->_value = algo_t_inst(static_cast<std::uint32_t>(algo_t_inst(_value.get()) | value));
				return *this;
			}

			__forceinline qeh_uint32& __fastcall operator<<=(const std::uint32_t value) noexcept {
				this->_value = algo_t_inst(static_cast<std::uint32_t>(algo_t_inst(_value.get()) << value));
				return *this;
			}

			__forceinline qeh_uint32& __fastcall operator>>=(const std::uint32_t value) noexcept {
				this->_value = algo_t_inst(static_cast<std::uint32_t>(algo_t_inst(_value.get()) >> value));
				return *this;
			}

			__forceinline qeh_uint32& __fastcall operator=(const std::uint32_t value) noexcept {
				_value = algo_t_inst(value);
				return *this;
			}

			__forceinline __cdecl operator std::uint32_t() const noexcept {
				return algo_t_inst(_value.get());
			}

			__forceinline __cdecl ~qeh_uint32() noexcept { }
	#pragma endregion
		};

	#pragma endregion

	#pragma region 64-bit

	#ifdef _WIN64

		class qeh_int64 {

		private:

	#pragma region Encrypted value

			qtype_hash::qh_int64 _value;

	#pragma endregion

		public:

	#pragma region CTOR

			__forceinline __fastcall qeh_int64(const std::int64_t value = 0) noexcept : _value(algo_t_inst(value)) {

				if (!is_init)
					init_qtype_hash();

				set(value);
			}

	#pragma endregion

	#pragma region Accessors

			__forceinline std::int64_t __cdecl get() const noexcept {
				return algo_t_inst(_value.get());
			}

			__forceinline void __fastcall set(const std::int64_t value) noexcept {
				_value = algo_t_inst(value);
			}

			__forceinline void* __cdecl get_raw_memory_address() const noexcept {
				return _value.get_raw_memory_address();
			}
	#pragma endregion

	#pragma region Operators

			__forceinline qeh_int64 __fastcall operator+(const std::int64_t value) const noexcept {
				return qeh_int64(algo_t_inst(_value.get()) + value);
			};

			__forceinline qeh_int64 __fastcall operator-(const std::int64_t value) const noexcept {
				return qeh_int64(algo_t_inst(_value.get()) - value);
			}

			__forceinline qeh_int64 __fastcall operator/(const std::int64_t value) const noexcept {
				return qeh_int64(algo_t_inst(_value.get()) / value);
			}

			__forceinline qeh_int64 __fastcall operator*(const std::int64_t value) const noexcept {
				return qeh_int64(algo_t_inst(_value.get()) * value);
			}

			__forceinline qeh_int64 __fastcall operator&(const std::int64_t value) const noexcept {
				return qeh_int64(algo_t_inst(_value.get()) & value);
			}

			__forceinline qeh_int64 __fastcall operator|(const std::int64_t value) const noexcept {
				return qeh_int64(algo_t_inst(_value.get()) | value);
			}

			__forceinline qeh_int64 __fastcall operator%(const std::int64_t value) const noexcept {
				return qeh_int64(algo_t_inst(_value.get()) % value);
			}

			__forceinline qeh_int64 __fastcall operator^(const std::int64_t value) const noexcept {
				return qeh_int64(algo_t_inst(_value.get()) ^ value);
			}

			__forceinline qeh_int64 __fastcall operator<<(const std::int64_t value) const noexcept {
				return qeh_int64(algo_t_inst(_value.get()) << value);
			}

			__forceinline qeh_int64 __fastcall operator>>(const std::int64_t value) const noexcept {
				return qeh_int64(algo_t_inst(_value.get()) >> value);
			}

			__forceinline qeh_int64& __fastcall operator+=(const std::int64_t value) noexcept {
				this->_value = algo_t_inst(static_cast<std::int64_t>(algo_t_inst(_value.get()) + value));
				return *this;
			}

			__forceinline qeh_int64& __fastcall operator-=(const std::int64_t value) noexcept {
				this->_value = algo_t_inst(static_cast<std::int64_t>(algo_t_inst(_value.get()) - value));
				return *this;
			}

			__forceinline qeh_int64& __cdecl operator++() noexcept {
				operator+=(1i64);
				return *this;
			}

			__forceinline qeh_int64& __cdecl operator--() noexcept {
				operator-=(1i64);
				return *this;
			}

			__forceinline qeh_int64& __fastcall operator*=(const std::int64_t value) noexcept {
				this->_value = algo_t_inst(static_cast<std::int64_t>(algo_t_inst(_value.get()) * value));
				return *this;
			}

			__forceinline qeh_int64& __fastcall operator/=(const std::int64_t value) noexcept {
				this->_value = algo_t_inst(static_cast<std::int64_t>(algo_t_inst(_value.get()) / value));
				return *this;
			}

			__forceinline qeh_int64& __fastcall operator%=(const std::int64_t value) noexcept {
				this->_value = algo_t_inst(static_cast<std::int64_t>(algo_t_inst(_value.get()) % value));
				return *this;
			}

			__forceinline qeh_int64& __fastcall operator^=(const std::int64_t value) noexcept {
				this->_value = algo_t_inst(static_cast<std::int64_t>(algo_t_inst(_value.get()) ^ value));
				return *this;
			}

			__forceinline qeh_int64& __fastcall operator&=(const std::int64_t value) noexcept {
				this->_value = algo_t_inst(static_cast<std::int64_t>(algo_t_inst(_value.get()) & value));
				return *this;
			}

			__forceinline qeh_int64& __fastcall operator|=(const std::int64_t value) noexcept {
				this->_value = algo_t_inst(static_cast<std::int64_t>(algo_t_inst(_value.get()) | value));
				return *this;
			}

			__forceinline qeh_int64& __fastcall operator<<=(const std::int64_t value) noexcept {
				this->_value = algo_t_inst(static_cast<std::int64_t>(algo_t_inst(_value.get()) << value));
				return *this;
			}

			__forceinline qeh_int64& __fastcall operator>>=(const std::int64_t value) noexcept {
				this->_value = algo_t_inst(static_cast<std::int64_t>(algo_t_inst(_value.get()) >> value));
				return *this;
			}

			__forceinline qeh_int64& __fastcall operator=(const std::int64_t value) noexcept {
				_value = algo_t_inst(value);
				return *this;
			}

			__forceinline __cdecl operator std::int64_t() const noexcept {
				return algo_t_inst(_value.get());
			}

			__forceinline __cdecl ~qeh_int64() noexcept { }
	#pragma endregion
		};

		class qeh_uint64_t {
		private:

	#pragma region Encrypted value

			qtype_hash::qh_uint64 _value;

	#pragma endregion

		public:

	#pragma region CTOR

			__forceinline __fastcall qeh_uint64_t(const std::uint64_t value = 0) noexcept : _value(algo_t_inst(value)) {

				if (!is_init)
					init_qtype_hash();

				set(value);
			}

	#pragma endregion

	#pragma region Accessors

			__forceinline std::uint64_t __cdecl get() const noexcept {
				return algo_t_inst(_value.get());
			}

			__forceinline void __fastcall set(const std::uint64_t value) noexcept {
				_value = algo_t_inst(value);
			}

			__forceinline void* __cdecl get_raw_memory_address() const noexcept {
				return _value.get_raw_memory_address();
			}
	#pragma endregion

	#pragma region Operators

			__forceinline qeh_uint64_t __fastcall operator+(const std::uint64_t value) const noexcept {
				return qeh_uint64_t(algo_t_inst(_value.get()) + value);
			};

			__forceinline qeh_uint64_t __fastcall operator-(const std::uint64_t value) const noexcept {
				return qeh_uint64_t(algo_t_inst(_value.get()) - value);
			}

			__forceinline qeh_uint64_t __fastcall operator/(const std::uint64_t value) const noexcept {
				return qeh_uint64_t(algo_t_inst(_value.get()) / value);
			}

			__forceinline qeh_uint64_t __fastcall operator*(const std::uint64_t value) const noexcept {
				return qeh_uint64_t(algo_t_inst(_value.get()) * value);
			}

			__forceinline qeh_uint64_t __fastcall operator&(const std::uint64_t value) const noexcept {
				return qeh_uint64_t(algo_t_inst(_value.get()) & value);
			}

			__forceinline qeh_uint64_t __fastcall operator|(const std::uint64_t value) const noexcept {
				return qeh_uint64_t(algo_t_inst(_value.get()) | value);
			}

			__forceinline qeh_uint64_t __fastcall operator%(const std::uint64_t value) const noexcept {
				return qeh_uint64_t(algo_t_inst(_value.get()) % value);
			}

			__forceinline qeh_uint64_t __fastcall operator^(const std::uint64_t value) const noexcept {
				return qeh_uint64_t(algo_t_inst(_value.get()) ^ value);
			}

			__forceinline qeh_uint64_t __fastcall operator<<(const std::uint64_t value) const noexcept {
				return qeh_uint64_t(algo_t_inst(_value.get()) << value);
			}

			__forceinline qeh_uint64_t __fastcall operator>>(const std::uint64_t value) const noexcept {
				return qeh_uint64_t(algo_t_inst(_value.get()) >> value);
			}

			__forceinline qeh_uint64_t& __fastcall operator+=(const std::uint64_t value) noexcept {
				this->_value = algo_t_inst(static_cast<std::uint64_t>(algo_t_inst(_value.get()) + value));
				return *this;
			}

			__forceinline qeh_uint64_t& __fastcall operator-=(const std::uint64_t value) noexcept {
				this->_value = algo_t_inst(static_cast<std::uint64_t>(algo_t_inst(_value.get()) - value));
				return *this;
			}

			__forceinline qeh_uint64_t& __cdecl operator++() noexcept {
				operator+=(1ui64);
				return *this;
			}

			__forceinline qeh_uint64_t& __cdecl operator--() noexcept {
				operator-=(1ui64);
				return *this;
			}

			__forceinline qeh_uint64_t& __fastcall operator*=(const std::uint64_t value) noexcept {
				this->_value = algo_t_inst(static_cast<std::uint64_t>(algo_t_inst(_value.get()) * value));
				return *this;
			}

			__forceinline qeh_uint64_t& __fastcall operator/=(const std::uint64_t value) noexcept {
				this->_value = algo_t_inst(static_cast<std::uint64_t>(algo_t_inst(_value.get()) / value));
				return *this;
			}

			__forceinline qeh_uint64_t& __fastcall operator%=(const std::uint64_t value) noexcept {
				this->_value = algo_t_inst(static_cast<std::uint64_t>(algo_t_inst(_value.get()) % value));
				return *this;
			}

			__forceinline qeh_uint64_t& __fastcall operator^=(const std::uint64_t value) noexcept {
				this->_value = algo_t_inst(static_cast<std::uint64_t>(algo_t_inst(_value.get()) ^ value));
				return *this;
			}

			__forceinline qeh_uint64_t& __fastcall operator&=(const std::uint64_t value) noexcept {
				this->_value = algo_t_inst(static_cast<std::uint64_t>(algo_t_inst(_value.get()) & value));
				return *this;
			}

			__forceinline qeh_uint64_t& __fastcall operator|=(const std::uint64_t value) noexcept {
				this->_value = algo_t_inst(static_cast<std::uint64_t>(algo_t_inst(_value.get()) | value));
				return *this;
			}

			__forceinline qeh_uint64_t& __fastcall operator<<=(const std::uint64_t value) noexcept {
				this->_value = algo_t_inst(static_cast<std::uint64_t>(algo_t_inst(_value.get()) << value));
				return *this;
			}

			__forceinline qeh_uint64_t& __fastcall operator>>=(const std::uint64_t value) noexcept {
				this->_value = algo_t_inst(static_cast<std::uint64_t>(algo_t_inst(_value.get()) >> value));
				return *this;
			}

			__forceinline qeh_uint64_t& __fastcall operator=(const std::uint64_t value) noexcept {
				_value = algo_t_inst(value);
				return *this;
			}

			__forceinline __cdecl operator std::uint64_t() const noexcept {
				return algo_t_inst(_value.get());
			}

			__forceinline __cdecl ~qeh_uint64_t() noexcept { }
	#pragma endregion
		};

	#endif

	#pragma endregion

	#pragma endregion

	#pragma region Floating Point

	#pragma region 32-bit

		class qeh_float {

		private:

	#pragma region Encrypted value

			qtype_hash::qh_float _value;

	#pragma endregion

		public:

	#pragma region CTOR

			__forceinline __fpcall qeh_float(const float value = 0.f) noexcept : _value(algo_t_inst(value)) {

				if (!is_init)
					init_qtype_hash();

				set(value);
			}

	#pragma endregion

	#pragma region Accessors

			__forceinline float __cdecl get() const noexcept {
				return algo_t_inst(_value.get());
			}

			__forceinline void __fpcall set(const float value) noexcept {
				_value = algo_t_inst(value);
			}

			__forceinline void* __cdecl get_raw_memory_address() const noexcept {
				return _value.get_raw_memory_address();
			}
	#pragma endregion

	#pragma region Operators

			__forceinline qeh_float __fpcall operator+(const float value) const noexcept {
				return qeh_float(algo_t_inst(_value.get()) + value);
			};

			__forceinline qeh_float __fpcall operator-(const float value) const noexcept {
				return qeh_float(algo_t_inst(_value.get()) - value);
			}

			__forceinline qeh_float __fpcall operator/(const float value) const noexcept {
				return qeh_float(algo_t_inst(_value.get()) / value);
			}

			__forceinline qeh_float __fpcall operator*(const float value) const noexcept {
				return qeh_float(algo_t_inst(_value.get()) * value);
			}

			__forceinline qeh_float& __fpcall operator+=(const float value) noexcept {
				this->_value = algo_t_inst(static_cast<float>(algo_t_inst(_value.get()) + value));
				return *this;
			}

			__forceinline qeh_float& __fpcall operator-=(const float value) noexcept {
				this->_value = algo_t_inst(static_cast<float>(algo_t_inst(_value.get()) - value));
				return *this;
			}

			__forceinline qeh_float& __cdecl operator++() noexcept {
				auto local_inst = 0.f;
				++local_inst;
				operator+=(local_inst);
				return *this;
			}

			__forceinline qeh_float& __cdecl operator--() noexcept {
				auto local_inst = 0.f;
				--local_inst;
				operator+=(local_inst);
				return *this;
			}

			__forceinline qeh_float& __fpcall operator*=(const float value) noexcept {
				this->_value = algo_t_inst(static_cast<float>(algo_t_inst(_value.get()) * value));
				return *this;
			}

			__forceinline qeh_float& __fpcall operator/=(const float value) noexcept {
				this->_value = algo_t_inst(static_cast<float>(algo_t_inst(_value.get()) / value));
				return *this;
			}

			__forceinline qeh_float& __fpcall operator=(const float value) noexcept {
				_value = algo_t_inst(value);
				return *this;
			}

			__forceinline __cdecl operator float() const noexcept {
				return algo_t_inst(_value.get());
			}

			__forceinline __cdecl ~qeh_float() noexcept { }

	#pragma endregion

		};

	#pragma endregion

	#pragma region 64-bit

	#ifdef _WIN64

		class qeh_double {

		private:

	#pragma region Encrypted value

			qtype_hash::qh_double _value;

	#pragma endregion

		public:

	#pragma region CTOR

			__forceinline __fpcall qeh_double(double value = static_cast<double>(0.f)) noexcept : _value(algo_t_inst(value)) {

				if (!is_init)
					init_qtype_hash();

				set(value);
			}

	#pragma endregion

	#pragma region Accessors

			__forceinline double __cdecl get() const noexcept {
				return algo_t_inst(_value.get());
			}

			__forceinline void __fpcall set(double value) noexcept {
				_value = algo_t_inst(value);
			}

			__forceinline void* __cdecl get_raw_memory_address() const noexcept {
				return _value.get_raw_memory_address();
			}
	#pragma endregion

	#pragma region Operators

			__forceinline qeh_double __fpcall operator+(const double value) const noexcept {
				return qeh_double(algo_t_inst(_value.get()) + value);
			};

			__forceinline qeh_double __fpcall operator-(const double value) const noexcept {
				return qeh_double(algo_t_inst(_value.get()) - value);
			}

			__forceinline qeh_double __fpcall operator/(const double value) const noexcept {
				return qeh_double(algo_t_inst(_value.get()) / value);
			}

			__forceinline qeh_double __fpcall operator*(const double value) const noexcept {
				return qeh_double(algo_t_inst(_value.get()) * value);
			}

			__forceinline qeh_double& __fpcall operator+=(const double value) noexcept {
				this->_value = algo_t_inst(static_cast<double>(algo_t_inst(_value.get()) + value));
				return *this;
			}

			__forceinline qeh_double& __fpcall operator-=(const double value) noexcept {
				this->_value = algo_t_inst(static_cast<double>(algo_t_inst(_value.get()) - value));
				return *this;
			}

			__forceinline qeh_double& __cdecl operator++() noexcept {
				auto local_inst = static_cast<double>(0.f);
				++local_inst;
				operator+=(local_inst);
				return *this;
			}

			__forceinline qeh_double& __cdecl operator--() noexcept {
				auto local_inst = static_cast<double>(0.f);
				--local_inst;
				operator+=(local_inst);
				return *this;
			}

			__forceinline qeh_double& __fpcall operator*=(const double value) noexcept {
				this->_value = algo_t_inst(static_cast<double>(algo_t_inst(_value.get()) * value));
				return *this;
			}

			__forceinline qeh_double& __fpcall operator/=(const double value) noexcept {
				this->_value = algo_t_inst(static_cast<double>(algo_t_inst(_value.get()) / value));
				return *this;
			}

			__forceinline qeh_double& __fpcall operator=(const double value) noexcept {
				_value = algo_t_inst(value);
				return *this;
			}

			__forceinline __cdecl operator double() const noexcept {
				return algo_t_inst(_value.get());
			}

			__forceinline __cdecl ~qeh_double() noexcept { }
	#pragma endregion
		};

	#endif

	#pragma endregion

	#pragma endregion

	#pragma region Extended Types

	#pragma region SSE

	#ifdef __SSE__

		class qeh_m128 {

		private:

	#pragma region Globals

			qtype_hash::qh_m128 _value;

	#pragma endregion

		public:

	#pragma region CTOR

			__forceinline __fpcall qeh_m128(__m128 value) noexcept : _value(algo_t_inst(value)) {

				if (!is_init)
					init_qtype_hash();

				set(value);
			}

	#pragma endregion

	#pragma region Accessors

			__forceinline __m128 __cdecl get() const noexcept {
				return algo_t_inst(_value.get());
			}

			__forceinline void __fpcall set(__m128 value) noexcept {
				_value = algo_t_inst(value);
			}

			__forceinline decltype(_value)* get_raw_memory_address() noexcept {
				return &_value;
			}

	#pragma endregion

	#pragma region Operators

	#ifdef __clang__

			__forceinline qeh_m128 __fpcall operator+(const __m128 value) const noexcept {
				return qeh_m128(get() + value);
			};

			__forceinline qeh_m128 __fpcall operator-(const __m128 value) const noexcept {
				return qeh_m128(get() - value);
			}

			__forceinline qeh_m128 __fpcall operator/(const __m128 value) const noexcept {
				return qeh_m128(get() / value);
			}

			__forceinline qeh_m128 __fpcall operator*(const __m128 value) const noexcept {
				return qeh_m128(get() * value);
			}

			__forceinline qeh_m128& __fpcall operator+=(const __m128 value) noexcept {
				set(static_cast<__m128>(get() + value));
				return *this;
			}

			__forceinline qeh_m128& __fpcall operator-=(const __m128 value) noexcept {
				set(static_cast<__m128>(get() - value));
				return *this;
			}

			__forceinline qeh_m128& __fpcall operator*=(const __m128 value) noexcept {
				set(static_cast<__m128>(get() * value));
				return *this;
			}

			__forceinline qeh_m128& __fpcall operator/=(const __m128 value) noexcept {
				set(static_cast<__m128>(get() / value));
				return *this;
			}

	#endif

			__forceinline qeh_m128& __fpcall operator=(const __m128 value) noexcept {
				set(value);
				return *this;
			}

			__forceinline __cdecl operator __m128() const noexcept {
				return get();
			}

			__forceinline __cdecl ~qeh_m128() noexcept {  }
	#pragma endregion
		};

	#ifdef __SSE2__

		class qeh_m128i {

		private:

	#pragma region Globals

			qtype_hash::qh_m128i _value;

	#pragma endregion

		public:

	#pragma region CTOR

			__forceinline __fpcall qeh_m128i(__m128i value) noexcept : _value(algo_t_inst(value)) {

				if (!is_init)
					init_qtype_hash();

				set(value);
			}

	#pragma endregion

	#pragma region Accessors

			__forceinline __m128i __cdecl get() const noexcept {
				return algo_t_inst(_value.get());
			}

			__forceinline void __fpcall set(__m128i value) noexcept {
				_value = algo_t_inst(value);
			}

			__forceinline decltype(_value)* get_raw_memory_address() noexcept {
				return &_value;
			}

	#pragma endregion

	#pragma region Operators

	#ifdef __clang__

			__forceinline qeh_m128i __fpcall operator+(const __m128i value) const noexcept {
				return qeh_m128i(get() + value);
			};

			__forceinline qeh_m128i __fpcall operator-(const __m128i value) const noexcept {
				return qeh_m128i(get() - value);
			}

			__forceinline qeh_m128i __fpcall operator/(const __m128i value) const noexcept {
				return qeh_m128i(get() / value);
			}

			__forceinline qeh_m128i __fpcall operator*(const __m128i value) const noexcept {
				return qeh_m128i(get() * value);
			}

			__forceinline qeh_m128i& __fpcall operator+=(const __m128i value) noexcept {
				set(static_cast<__m128i>(get() + value));
				return *this;
			}

			__forceinline qeh_m128i& __fpcall operator-=(const __m128i value) noexcept {
				set(static_cast<__m128i>(get() - value));
				return *this;
			}

			__forceinline qeh_m128i& __fpcall operator*=(const __m128i value) noexcept {
				set(static_cast<__m128i>(get() * value));
				return *this;
			}

			__forceinline qeh_m128i& __fpcall operator/=(const __m128i value) noexcept {
				set(static_cast<__m128i>(get() / value));
				return *this;
			}

	#endif

			__forceinline qeh_m128i& __fpcall operator=(const __m128i value) noexcept {
				set(value);
				return *this;
			}

			__forceinline __cdecl operator __m128i() const noexcept {
				return get();
			}

			__forceinline __cdecl ~qeh_m128i() noexcept { }
	#pragma endregion
		};

		class qeh_m128d {

		private:

	#pragma region Globals

			qtype_hash::qh_m128d _value;

	#pragma endregion

		public:

	#pragma region CTOR

			__forceinline __fpcall qeh_m128d(__m128d value) noexcept : _value(algo_t_inst(value)) {

				if (!is_init)
					init_qtype_hash();

				set(value);
			}

	#pragma endregion

	#pragma region Accessors

			__forceinline __m128d __cdecl get() const noexcept {
				return algo_t_inst(_value.get());
			}

			__forceinline void __fpcall set(__m128d value) noexcept {
				_value = algo_t_inst(value);
			}

			__forceinline decltype(_value)* get_raw_memory_address() noexcept {
				return &_value;
			}

	#pragma endregion

	#pragma region Operators

	#ifdef __clang__

			__forceinline qeh_m128d __fpcall operator+(const __m128d value) const noexcept {
				return qeh_m128d(get() + value);
			};

			__forceinline qeh_m128d __fpcall operator-(const __m128d value) const noexcept {
				return qeh_m128d(get() - value);
			}

			__forceinline qeh_m128d __fpcall operator/(const __m128d value) const noexcept {
				return qeh_m128d(get() / value);
			}

			__forceinline qeh_m128d __fpcall operator*(const __m128d value) const noexcept {
				return qeh_m128d(get() * value);
			}

			__forceinline qeh_m128d& __fpcall operator+=(const __m128d value) noexcept {
				set(static_cast<__m128d>(get() + value));
				return *this;
			}

			__forceinline qeh_m128d& __fpcall operator-=(const __m128d value) noexcept {
				set(static_cast<__m128d>(get() - value));
				return *this;
			}

			__forceinline qeh_m128d& __fpcall operator*=(const __m128d value) noexcept {
				set(static_cast<__m128d>(get() * value));
				return *this;
			}

			__forceinline qeh_m128d& __fpcall operator/=(const __m128d value) noexcept {
				set(static_cast<__m128d>(get() / value));
				return *this;
			}

	#endif

			__forceinline qeh_m128d& __fpcall operator=(const __m128d value) noexcept {
				set(value);
				return *this;
			}

			__forceinline __cdecl operator __m128d() const noexcept {
				return get();
			}

			__forceinline __cdecl ~qeh_m128d() noexcept { }
	#pragma endregion
		};

	#endif

	#endif

	#pragma endregion

	#pragma region AVX

	#ifdef __AVX__

		class qeh_m256 {

		private:

	#pragma region Globals

			qtype_hash::qh_m256 _value;

	#pragma endregion

		public:

	#pragma region CTOR

			__forceinline __fpcall qeh_m256(__m256 value) noexcept : _value(algo_t_inst(value)) {

				if (!is_init)
					init_qtype_hash();

				set(value);
			}

	#pragma endregion

	#pragma region Accessors

			__forceinline __m256 __cdecl get() const noexcept {
				return algo_t_inst(_value.get());
			}

			__forceinline void __fpcall set(__m256 value) noexcept {
				_value = algo_t_inst(value);
			}

			__forceinline decltype(_value)* get_raw_memory_address() noexcept {
				return &_value;
			}

	#pragma endregion

	#pragma region Operators

	#ifdef __clang__

			__forceinline qeh_m256 __fpcall operator+(const __m256 value) const noexcept {
				return qeh_m256(get() + value);
			};

			__forceinline qeh_m256 __fpcall operator-(const __m256 value) const noexcept {
				return qeh_m256(get() - value);
			}

			__forceinline qeh_m256 __fpcall operator/(const __m256 value) const noexcept {
				return qeh_m256(get() / value);
			}

			__forceinline qeh_m256 __fpcall operator*(const __m256 value) const noexcept {
				return qeh_m256(get() * value);
			}

			__forceinline qeh_m256& __fpcall operator+=(const __m256 value) noexcept {
				set(static_cast<__m256>(get() + value));
				return *this;
			}

			__forceinline qeh_m256& __fpcall operator-=(const __m256 value) noexcept {
				set(static_cast<__m256>(get() - value));
				return *this;
			}

			__forceinline qeh_m256& __fpcall operator*=(const __m256 value) noexcept {
				set(static_cast<__m256>(get() * value));
				return *this;
			}

			__forceinline qeh_m256& __fpcall operator/=(const __m256 value) noexcept {
				set(static_cast<__m256>(get() / value));
				return *this;
			}

	#endif

			__forceinline qeh_m256& __fpcall operator=(const __m256 value) noexcept {
				set(value);
				return *this;
			}

			__forceinline __cdecl operator __m256() const noexcept {
				return get();
			}

			__forceinline __cdecl ~qeh_m256() noexcept { }
	#pragma endregion
		};

		class qeh_m256i {
		private:

	#pragma region Globals

			qtype_hash::qh_m256i _value;

	#pragma endregion

		public:

	#pragma region CTOR

			__forceinline __fpcall qeh_m256i(__m256i value) noexcept : _value(algo_t_inst(value)) {

				if (!is_init)
					init_qtype_hash();

				set(value);
			}

	#pragma endregion

	#pragma region Accessors

			__forceinline __m256i __cdecl get() const noexcept {
				return algo_t_inst(_value.get());
			}

			__forceinline void __fpcall set(__m256i value) noexcept {
				_value = algo_t_inst(value);
			}

			__forceinline decltype(_value)* get_raw_memory_address() noexcept {
				return &_value;
			}

	#pragma endregion

	#pragma region Operators

	#ifdef __clang__

			__forceinline qeh_m256i __fpcall operator+(const __m256i value) const noexcept {
				return qeh_m256i(get() + value);
			};

			__forceinline qeh_m256i __fpcall operator-(const __m256i value) const noexcept {
				return qeh_m256i(get() - value);
			}

			__forceinline qeh_m256i __fpcall operator/(const __m256i value) const noexcept {
				return qeh_m256i(get() / value);
			}

			__forceinline qeh_m256i __fpcall operator*(const __m256i value) const noexcept {
				return qeh_m256i(get() * value);
			}

			__forceinline qeh_m256i& __fpcall operator+=(const __m256i value) noexcept {
				set(static_cast<__m256i>(get() + value));
				return *this;
			}

			__forceinline qeh_m256i& __fpcall operator-=(const __m256i value) noexcept {
				set(static_cast<__m256i>(get() - value));
				return *this;
			}

			__forceinline qeh_m256i& __fpcall operator*=(const __m256i value) noexcept {
				set(static_cast<__m256i>(get() * value));
				return *this;
			}

			__forceinline qeh_m256i& __fpcall operator/=(const __m256i value) noexcept {
				set(static_cast<__m256i>(get() / value));
				return *this;
			}

	#endif

			__forceinline qeh_m256i& __fpcall operator=(const __m256i value) noexcept {
				set(value);
				return *this;
			}

			__forceinline __cdecl operator __m256i() const noexcept {
				return get();
			}

			__forceinline __cdecl ~qeh_m256i() noexcept { }
	#pragma endregion
		};

		class qeh_m256d {

		private:

	#pragma region Globals

			qtype_hash::qh_m256d _value;

	#pragma endregion

		public:

	#pragma region CTOR

			__forceinline __fpcall qeh_m256d(__m256d value) noexcept : _value(algo_t_inst(value)) {

				if (!is_init)
					init_qtype_hash();

				set(value);
			}

	#pragma endregion

	#pragma region Accessors

			__forceinline __m256d __cdecl get() const noexcept {
				return algo_t_inst(_value.get());
			}

			__forceinline void __fpcall set(__m256d value) noexcept {
				_value = algo_t_inst(value);
			}

			__forceinline decltype(_value)* get_raw_memory_address() noexcept {
				return &_value;
			}

	#pragma endregion

	#pragma region Operators

	#ifdef __clang__

			__forceinline qeh_m256d __fpcall operator+(const __m256d value) const noexcept {
				return qeh_m256d(get() + value);
			};

			__forceinline qeh_m256d __fpcall operator-(const __m256d value) const noexcept {
				return qeh_m256d(get() - value);
			}

			__forceinline qeh_m256d __fpcall operator/(const __m256d value) const noexcept {
				return qeh_m256d(get() / value);
			}

			__forceinline qeh_m256d __fpcall operator*(const __m256d value) const noexcept {
				return qeh_m256d(get() * value);
			}

			__forceinline qeh_m256d& __fpcall operator+=(const __m256d value) noexcept {
				set(static_cast<__m256d>(get() + value));
				return *this;
			}

			__forceinline qeh_m256d& __fpcall operator-=(const __m256d value) noexcept {
				set(static_cast<__m256d>(get() - value));
				return *this;
			}

			__forceinline qeh_m256d& __fpcall operator*=(const __m256d value) noexcept {
				set(static_cast<__m256d>(get() * value));
				return *this;
			}

			__forceinline qeh_m256d& __fpcall operator/=(const __m256d value) noexcept {
				set(static_cast<__m256d>(get() / value));
				return *this;
			}

	#endif

			__forceinline qeh_m256d& __fpcall operator=(const __m256d value) noexcept {
				set(value);
				return *this;
			}

			__forceinline __cdecl operator __m256d() const noexcept {
				return get();
			}

			__forceinline __cdecl ~qeh_m256d() noexcept { }
	#pragma endregion
		};

	#endif

	#pragma endregion

	#pragma endregion

	#pragma endregion

	#pragma region String

		class qeh_string {
		private:

	#pragma region Encrypted value

			qtype_hash::qh_string _value;

	#pragma endregion

		public:

	#pragma region CTOR

			__forceinline __cdecl qeh_string(const std::string value = "") noexcept {

				_value = algo_str_inst(value);

				if (!is_init)
					init_qtype_hash();

				set(value);
			}

	#pragma endregion

	#pragma region Accessors

			__forceinline std::string __cdecl get() const noexcept {
				return algo_str_inst(_value.get());
			}

			__forceinline void __cdecl set(const std::string value) noexcept {
				_value = algo_str_inst(value);
			}

			__forceinline std::string* __cdecl get_raw_memory_address() noexcept {
				return _value.get_raw_memory_address();
			}

	#pragma endregion

	#pragma region Operators

			__forceinline qeh_string __cdecl operator+(const std::string& value) const noexcept {
				return qeh_string(get() + value);
			}

			__forceinline qeh_string& __cdecl operator+=(const std::string& value) noexcept {
				set(static_cast<std::string>(get() + value));
				return *this;
			}

			__forceinline qeh_string& __cdecl operator=(const std::string value) noexcept {
				set(value);
				return *this;
			}

			__forceinline __cdecl operator std::string() const noexcept {
				return get();
			}

			__forceinline __cdecl ~qeh_string() noexcept { }

	#pragma endregion
		};

	#pragma endregion

	#pragma region Wide String

		class qeh_wstring {

		private:

	#pragma region Encrypted value

			qtype_hash::qh_wstring _value;

	#pragma endregion

		public:

	#pragma region CTOR

			__forceinline __cdecl qeh_wstring(const std::wstring value) noexcept : _value(algo_wstr_inst(value)) {

				if (!is_init)
					init_qtype_hash();

				set(value);
			}

	#pragma endregion

	#pragma region Accessors

			__forceinline std::wstring __cdecl get() const noexcept {
				return algo_wstr_inst(_value.get());
			}

			__forceinline void __cdecl set(const std::wstring& value) noexcept {
				_value = algo_wstr_inst(value);
			}

			__forceinline std::wstring* __cdecl get_raw_memory_address() noexcept {
				return _value.get_raw_memory_address();
			}

	#pragma endregion

	#pragma region Operators

			__forceinline qeh_wstring __cdecl operator+(const std::wstring& value) const noexcept {
				return qeh_wstring(get() + value);
			}

			__forceinline qeh_wstring& __cdecl operator+=(const std::wstring& value) noexcept {
				set(static_cast<std::wstring>(get() + value));
				return *this;
			}

			__forceinline qeh_wstring& __cdecl operator=(const std::wstring& value) noexcept {
				set(value);
				return *this;
			}

			__forceinline __cdecl operator std::wstring() const noexcept {
				return get();
			}

			__forceinline __cdecl ~qeh_wstring() noexcept { }

	#pragma endregion
		};

	#pragma endregion

	#pragma region Heap Allocation

		class qeh_malloc {

		private:

	#pragma region Globals

			qtype_hash::qh_malloc allocation;

	#pragma endregion

	#pragma region Subscript proxy

			// nested class to support subscript assignment
			class index_proxy {

			private:

	#pragma region Globals

				qeh_malloc& parent;
				size_t index;

	#pragma endregion

			public:
	#pragma region Ctor

				index_proxy(size_t index_, qeh_malloc& instance) noexcept : index(index_), parent(instance) { }

	#pragma endregion

	#pragma region Operator overrides

				__forceinline byte& operator=(byte value) noexcept {
					parent.set(index, value);
					return value;   // return the passed assignment value rather than using up absurd resources to decrypt, re-encrypt everything using get()
				}

				__forceinline __fastcall operator byte() const noexcept {
					return parent.get(index);
				}

	#pragma endregion
			};

	#pragma endregion

		public:

	#pragma region Ctor

			__forceinline __fastcall qeh_malloc(size_t size) noexcept : allocation(size) {
				if (!size)
					return;

				if (!is_init)
					init_qtype_hash();

				if (!allocation.get_raw_memory_address())
					throw qexcept::q_badalloc();

			}

	#pragma endregion

	#pragma region Get Accessors

			__forceinline void __fastcall get(uintptr_t source_position, void* destination, size_t length) const noexcept {
				void* dec_alloc = allocation.get();

				algo(dec_alloc, allocation.length());

				memcpy(destination, reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(dec_alloc) + source_position), length);

				free(dec_alloc);
			}

			__forceinline byte __fastcall get(uintptr_t position) const noexcept {
				byte _return = NULL;

				get(position, &_return, sizeof(_return));

				return _return;
			}

			__forceinline void* __fastcall get() const noexcept {

				auto _return = allocation.get();

				algo(_return, allocation.length());

				return _return;
			}

	#pragma endregion

	#pragma region Set Accessors

			__forceinline void __fastcall set(uintptr_t position, void* data, size_t length) noexcept {
				auto dec_alloc = allocation.get();

				algo(dec_alloc, allocation.length());

				memcpy(reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(dec_alloc) + position), data, length);

				algo(dec_alloc, allocation.length());

				allocation.swap(dec_alloc, allocation.length());
			}

			template<typename T>
			__forceinline void __fastcall set(uintptr_t position, T value) noexcept {
				set(position, &value, sizeof(decltype(value)));
			}

	#pragma endregion

	#pragma region Utility functions

			__forceinline void __fastcall reallocate(size_t size) noexcept {
				allocation.reallocate(size);
			}

			__forceinline const bool __fastcall swap(void* allocation_, size_t size, bool free_source = false) noexcept {
				if (!size)
					return false;

				void* enc_alloc = malloc(size);

				if (!enc_alloc)
					return false;

				memcpy(enc_alloc, allocation_, size);

				algo(enc_alloc, size);

				if (free_source)
					free(allocation_);

				allocation.swap(enc_alloc, size);

				return true;
			}

			__forceinline void* get_raw_memory_address() noexcept {
				return allocation.get_raw_memory_address();
			}

	#pragma endregion

	#pragma region Operators

			__forceinline index_proxy __fastcall operator[](size_t index) noexcept {
				return index_proxy(index, *this);
			}

	#pragma endregion

	#pragma region Destructor

			__forceinline ~qeh_malloc() noexcept { }

	#pragma endregion
		};

	#pragma endregion
	} 

#pragma region Static Declarators

	bool qtype_enchash::is_init = false;

#pragma endregion

}

#endif