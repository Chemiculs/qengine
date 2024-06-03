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

#pragma region Namespacing

namespace qengine {

	namespace qtype_enchash {

#pragma endregion

	#pragma region Singleton 

		extern bool is_init;

	#pragma endregion

	#pragma region Static Methods

		__compelled_inline void __stackcall init_qtype_hash(qcallback::qmem_exception_rogue_c callback = qtype_hash::violation_callback_d) noexcept {

			if (is_init)
				return;

			qtype_hash::init_hash_t(callback);

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

			__optimized_ctor qeh_int8(imut std::int8_t value = 0) noexcept : _value(qengine::polyc::algo_t_inst(value)) {

				if (!is_init)
					init_qtype_hash();

				set(value);
			}

	#pragma endregion

	#pragma region Accessors

			__compelled_inline std::int8_t __stackcall get() imut noexcept {
				return algo_t_inst(_value.get());
			}

			__compelled_inline void __regcall set(imut std::int8_t value) noexcept {
				_value = algo_t_inst(value);
			}

			__compelled_inline imut void* __stackcall get_raw_memory_address() imut noexcept {
				return _value.get_raw_memory_address();
			}
	#pragma endregion

	#pragma region Operators

			__compelled_inline qeh_int8 __regcall operator+(imut std::int8_t value) imut noexcept {
				return qeh_int8(algo_t_inst(_value.get()) + value);
			};

			__compelled_inline qeh_int8 __regcall operator-(imut std::int8_t value) imut noexcept {
				return qeh_int8(algo_t_inst(_value.get()) - value);
			}

			__compelled_inline qeh_int8 __regcall operator/(imut std::int8_t value) imut noexcept {
				return qeh_int8(algo_t_inst(_value.get()) / value);
			}

			__compelled_inline qeh_int8 __regcall operator*(imut std::int8_t value) imut noexcept {
				return qeh_int8(algo_t_inst(_value.get()) * value);
			}

			__compelled_inline qeh_int8 __regcall operator&(imut std::int8_t value) imut noexcept {
				return qeh_int8(algo_t_inst(_value.get()) & value);
			}

			__compelled_inline qeh_int8 __regcall operator|(imut std::int8_t value) imut noexcept {
				return qeh_int8(algo_t_inst(_value.get()) | value);
			}

			__compelled_inline qeh_int8 __regcall operator%(imut std::int8_t value) imut noexcept {
				return qeh_int8(algo_t_inst(_value.get()) % value);
			}

			__compelled_inline qeh_int8 __regcall operator^(imut std::int8_t value) imut noexcept {
				return qeh_int8(algo_t_inst(_value.get()) ^ value);
			}

			__compelled_inline qeh_int8 __regcall operator<<(imut std::int8_t value) imut noexcept {
				return qeh_int8(algo_t_inst(_value.get()) << value);
			}

			__compelled_inline qeh_int8 __regcall operator>>(imut std::int8_t value) imut noexcept {
				return qeh_int8(algo_t_inst(_value.get()) >> value);
			}

			__compelled_inline qeh_int8& __regcall operator+=(imut std::int8_t value) noexcept {
				this->_value = algo_t_inst(static_cast<std::int8_t>(algo_t_inst(_value.get()) + value));
				return *this;
			}

			__compelled_inline qeh_int8& __regcall operator-=(imut std::int8_t value) noexcept {
				this->_value = algo_t_inst(static_cast<std::int8_t>(algo_t_inst(_value.get()) - value));
				return *this;
			}

			__compelled_inline qeh_int8& __stackcall operator++() noexcept {
				operator+=(1i8);
				return *this;
			}

			__compelled_inline qeh_int8& __stackcall operator--() noexcept {
				operator-=(1i8);
				return *this;
			}

			__compelled_inline qeh_int8& __regcall operator*=(imut std::int8_t value) noexcept {
				this->_value = algo_t_inst(static_cast<std::int8_t>(algo_t_inst(_value.get()) * value));
				return *this;
			}

			__compelled_inline qeh_int8& __regcall operator/=(imut std::int8_t value) noexcept {
				this->_value = algo_t_inst(static_cast<std::int8_t>(algo_t_inst(_value.get()) / value));
				return *this;
			}

			__compelled_inline qeh_int8& __regcall operator%=(imut std::int8_t value) noexcept {
				this->_value = algo_t_inst(static_cast<std::int8_t>(algo_t_inst(_value.get()) % value));
				return *this;
			}

			__compelled_inline qeh_int8& __regcall operator^=(imut std::int8_t value) noexcept {
				this->_value = algo_t_inst(static_cast<std::int8_t>(algo_t_inst(_value.get()) ^ value));
				return *this;
			}

			__compelled_inline qeh_int8& __regcall operator&=(imut std::int8_t value) noexcept {
				this->_value = algo_t_inst(static_cast<std::int8_t>(algo_t_inst(_value.get()) & value));
				return *this;
			}

			__compelled_inline qeh_int8& __regcall operator|=(imut std::int8_t value) noexcept {
				this->_value = algo_t_inst(static_cast<std::int8_t>(algo_t_inst(_value.get()) | value));
				return *this;
			}

			__compelled_inline qeh_int8& __regcall operator<<=(imut std::int8_t value) noexcept {
				this->_value = algo_t_inst(static_cast<std::int8_t>(algo_t_inst(_value.get()) << value));
				return *this;
			}

			__compelled_inline qeh_int8& __regcall operator>>=(imut std::int8_t value) noexcept {
				this->_value = algo_t_inst(static_cast<std::int8_t>(algo_t_inst(_value.get()) >> value));
				return *this;
			}

			__compelled_inline qeh_int8& __regcall operator=(imut std::int8_t value) noexcept {
				_value = algo_t_inst(value);
				return *this;
			}

			__compelled_inline __stackcall operator char() imut noexcept {
				return algo_t_inst(_value.get());
			}

			__compelled_inline __stackcall ~qeh_int8() noexcept { }
	#pragma endregion
		};

		class qeh_uint8 {

		private:

	#pragma region Encrypted value

			qtype_hash::qh_uint8 _value;

	#pragma endregion

		public:

	#pragma region CTOR

			__compelled_inline __regcall qeh_uint8(imut std::uint8_t value = 0) noexcept : _value(algo_t_inst(value)) {

				if (!is_init)
					init_qtype_hash();

				set(value);
			}

	#pragma endregion

	#pragma region Accessors

			__compelled_inline std::uint8_t __stackcall get() imut noexcept {
				return algo_t_inst(_value.get());
			}

			__compelled_inline void __regcall set(imut std::uint8_t value) noexcept {
				_value = algo_t_inst(value);
			}

			__compelled_inline imut void* get_raw_memory_address() imut noexcept {
				return _value.get_raw_memory_address();
			}
	#pragma endregion

	#pragma region Operators

			__compelled_inline qeh_uint8 __regcall operator+(imut std::uint8_t value) imut noexcept {
				return qeh_uint8(algo_t_inst(_value.get()) + value);
			};

			__compelled_inline qeh_uint8 __regcall operator-(imut std::uint8_t value) imut noexcept {
				return qeh_uint8(algo_t_inst(_value.get()) - value);
			}

			__compelled_inline qeh_uint8 __regcall operator/(imut std::uint8_t value) imut noexcept {
				return qeh_uint8(algo_t_inst(_value.get()) / value);
			}

			__compelled_inline qeh_uint8 __regcall operator*(imut std::uint8_t value) imut noexcept {
				return qeh_uint8(algo_t_inst(_value.get()) * value);
			}

			__compelled_inline qeh_uint8 __regcall operator&(imut std::uint8_t value) imut noexcept {
				return qeh_uint8(algo_t_inst(_value.get()) & value);
			}

			__compelled_inline qeh_uint8 __regcall operator|(imut std::uint8_t value) imut noexcept {
				return qeh_uint8(algo_t_inst(_value.get()) | value);
			}

			__compelled_inline qeh_uint8 __regcall operator%(imut std::uint8_t value) imut noexcept {
				return qeh_uint8(algo_t_inst(_value.get()) % value);
			}

			__compelled_inline qeh_uint8 __regcall operator^(imut std::uint8_t value) imut noexcept {
				return qeh_uint8(algo_t_inst(_value.get()) ^ value);
			}

			__compelled_inline qeh_uint8 __regcall operator<<(imut std::uint8_t value) imut noexcept {
				return qeh_uint8(algo_t_inst(_value.get()) << value);
			}

			__compelled_inline qeh_uint8 __regcall operator>>(imut std::uint8_t value) imut noexcept {
				return qeh_uint8(algo_t_inst(_value.get()) >> value);
			}

			__compelled_inline qeh_uint8& __regcall operator+=(imut std::uint8_t value) noexcept {
				this->_value = algo_t_inst(static_cast<std::uint8_t>(algo_t_inst(_value.get()) + value));
				return *this;
			}

			__compelled_inline qeh_uint8& __regcall operator-=(imut std::uint8_t value) noexcept {
				this->_value = algo_t_inst(static_cast<std::uint8_t>(algo_t_inst(_value.get()) - value));
				return *this;
			}

			__compelled_inline qeh_uint8& __stackcall operator++() noexcept {
				operator+=(1ui8);
				return *this;
			}

			__compelled_inline qeh_uint8& __stackcall operator--() noexcept {
				operator-=(1ui8);
				return *this;
			}

			__compelled_inline qeh_uint8& __regcall operator*=(imut std::uint8_t value) noexcept {
				this->_value = algo_t_inst(static_cast<std::uint8_t>(algo_t_inst(_value.get()) * value));
				return *this;
			}

			__compelled_inline qeh_uint8& __regcall operator/=(imut std::uint8_t value) noexcept {
				this->_value = algo_t_inst(static_cast<std::uint8_t>(algo_t_inst(_value.get()) / value));
				return *this;
			}

			__compelled_inline qeh_uint8& __regcall operator%=(imut std::uint8_t value) noexcept {
				this->_value = algo_t_inst(static_cast<std::uint8_t>(algo_t_inst(_value.get()) % value));
				return *this;
			}

			__compelled_inline qeh_uint8& __regcall operator^=(imut std::uint8_t value) noexcept {
				this->_value = algo_t_inst(static_cast<std::uint8_t>(algo_t_inst(_value.get()) ^ value));
				return *this;
			}

			__compelled_inline qeh_uint8& __regcall operator&=(imut std::uint8_t value) noexcept {
				this->_value = algo_t_inst(static_cast<std::uint8_t>(algo_t_inst(_value.get()) & value));
				return *this;
			}

			__compelled_inline qeh_uint8& __regcall operator|=(imut std::uint8_t value) noexcept {
				this->_value = algo_t_inst(static_cast<std::uint8_t>(algo_t_inst(_value.get()) | value));
				return *this;
			}

			__compelled_inline qeh_uint8& __regcall operator<<=(imut std::uint8_t value) noexcept {
				this->_value = algo_t_inst(static_cast<std::uint8_t>(algo_t_inst(_value.get()) << value));
				return *this;
			}

			__compelled_inline qeh_uint8& __regcall operator>>=(imut std::uint8_t value) noexcept {
				this->_value = algo_t_inst(static_cast<std::uint8_t>(algo_t_inst(_value.get()) >> value));
				return *this;
			}

			__compelled_inline qeh_uint8& __regcall operator=(imut std::uint8_t value) noexcept {
				_value = algo_t_inst(value);
				return *this;
			}

			__compelled_inline __stackcall operator std::uint8_t() imut noexcept {
				return algo_t_inst(_value.get());
			}

			__compelled_inline __stackcall ~qeh_uint8() noexcept { }
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

			__optimized_ctor qeh_int16(imut std::int16_t value = 0) noexcept : _value(algo_t_inst(value)) {

				if (!is_init)
					init_qtype_hash();

				set(value);
			}

	#pragma endregion

	#pragma region Accessors

			__compelled_inline short __stackcall get() imut noexcept {
				return algo_t_inst(_value.get());
			}

			__compelled_inline void __regcall set(imut std::int16_t value) noexcept {
				_value = algo_t_inst(value);
			}

			__compelled_inline imut void* __stackcall get_raw_memory_address() noexcept {
				return _value.get_raw_memory_address();
			}
	#pragma endregion

	#pragma region Operators

			__compelled_inline qeh_int16 __regcall operator+(imut std::int16_t value) imut noexcept {
				return qeh_int16(algo_t_inst(_value.get()) + value);
			};

			__compelled_inline qeh_int16 __regcall operator-(imut std::int16_t value) imut noexcept {
				return qeh_int16(algo_t_inst(_value.get()) - value);
			}

			__compelled_inline qeh_int16 __regcall operator/(imut std::int16_t value) imut noexcept {
				return qeh_int16(algo_t_inst(_value.get()) / value);
			}

			__compelled_inline qeh_int16 __regcall operator*(imut std::int16_t value) imut noexcept {
				return qeh_int16(algo_t_inst(_value.get()) * value);
			}

			__compelled_inline qeh_int16 __regcall operator&(imut std::int16_t value) imut noexcept {
				return qeh_int16(algo_t_inst(_value.get()) & value);
			}

			__compelled_inline qeh_int16 __regcall operator|(imut std::int16_t value) imut noexcept {
				return qeh_int16(algo_t_inst(_value.get()) | value);
			}

			__compelled_inline qeh_int16 __regcall operator%(imut std::int16_t value) imut noexcept {
				return qeh_int16(algo_t_inst(_value.get()) % value);
			}

			__compelled_inline qeh_int16 __regcall operator^(imut std::int16_t value) imut noexcept {
				return qeh_int16(algo_t_inst(_value.get()) ^ value);
			}

			__compelled_inline qeh_int16 __regcall operator<<(imut std::int16_t value) imut noexcept {
				return qeh_int16(algo_t_inst(_value.get()) << value);
			}

			__compelled_inline qeh_int16 __regcall operator>>(imut std::int16_t value) imut noexcept {
				return qeh_int16(algo_t_inst(_value.get()) >> value);
			}

			__compelled_inline qeh_int16& __regcall operator+=(imut std::int16_t value) noexcept {
				this->_value = algo_t_inst(static_cast<std::int16_t>(algo_t_inst(_value.get()) + value));
				return *this;
			}

			__compelled_inline qeh_int16& __regcall operator-=(imut std::int16_t value) noexcept {
				this->_value = algo_t_inst(static_cast<std::int16_t>(algo_t_inst(_value.get()) - value));
				return *this;
			}

			__compelled_inline qeh_int16& __stackcall operator++() noexcept {
				operator+=(1i16);
				return *this;
			}

			__compelled_inline qeh_int16& __stackcall operator--() noexcept {
				operator-=(1i16);
				return *this;
			}

			__compelled_inline qeh_int16& __regcall operator*=(imut short value) noexcept {
				this->_value = algo_t_inst(static_cast<short>(algo_t_inst(_value.get()) * value));
				return *this;
			}

			__compelled_inline qeh_int16& __regcall operator/=(imut short value) noexcept {
				this->_value = algo_t_inst(static_cast<short>(algo_t_inst(_value.get()) / value));
				return *this;
			}

			__compelled_inline qeh_int16& __regcall operator%=(imut std::int16_t value) noexcept {
				this->_value = algo_t_inst(static_cast<std::int16_t>(algo_t_inst(_value.get()) % value));
				return *this;
			}

			__compelled_inline qeh_int16& __regcall operator^=(imut std::int16_t value) noexcept {
				this->_value = algo_t_inst(static_cast<std::int16_t>(algo_t_inst(_value.get()) ^ value));
				return *this;
			}

			__compelled_inline qeh_int16& __regcall operator&=(imut std::int16_t value) noexcept {
				this->_value = algo_t_inst(static_cast<std::int16_t>(algo_t_inst(_value.get()) & value));
				return *this;
			}

			__compelled_inline qeh_int16& __regcall operator|=(imut std::int16_t value) noexcept {
				this->_value = algo_t_inst(static_cast<std::int16_t>(algo_t_inst(_value.get()) | value));
				return *this;
			}

			__compelled_inline qeh_int16& __regcall operator<<=(imut std::int16_t value) noexcept {
				this->_value = algo_t_inst(static_cast<std::int16_t>(algo_t_inst(_value.get()) << value));
				return *this;
			}

			__compelled_inline qeh_int16& __regcall operator>>=(imut std::int16_t value) noexcept {
				this->_value = algo_t_inst(static_cast<std::int16_t>(algo_t_inst(_value.get()) >> value));
				return *this;
			}

			__compelled_inline qeh_int16& __regcall operator=(imut std::int16_t value) noexcept {
				_value = algo_t_inst(value);
				return *this;
			}

			__compelled_inline __stackcall operator std::int16_t() imut noexcept {
				return algo_t_inst(_value.get());
			}

			__compelled_inline __stackcall ~qeh_int16() noexcept { }
	#pragma endregion
		};

		class qeh_uint16 {

		private:

	#pragma region Encrypted value

			qtype_hash::qh_uint16 _value;

	#pragma endregion

		public:

	#pragma region CTOR

			__compelled_inline __regcall qeh_uint16(imut std::uint16_t value = 0) noexcept : _value(algo_t_inst(value)) {

				if (!is_init)
					init_qtype_hash();

				set(value);
			}

	#pragma endregion

	#pragma region Accessors

			__compelled_inline std::uint16_t __stackcall get() imut noexcept {
				return algo_t_inst(_value.get());
			}

			__compelled_inline void __regcall set(imut std::uint16_t value) noexcept {
				_value = algo_t_inst(value);
			}

			__compelled_inline imut void* __stackcall get_raw_memory_address() imut noexcept {
				return _value.get_raw_memory_address();
			}
	#pragma endregion

	#pragma region Operators

			__compelled_inline qeh_uint16 __regcall operator+(imut std::uint16_t value) imut noexcept {
				return qeh_uint16(algo_t_inst(_value.get()) + value);
			};

			__compelled_inline qeh_uint16 __regcall operator-(imut std::uint16_t value) imut noexcept {
				return qeh_uint16(algo_t_inst(_value.get()) - value);
			}

			__compelled_inline qeh_uint16 __regcall operator/(imut std::uint16_t value) imut noexcept {
				return qeh_uint16(algo_t_inst(_value.get()) / value);
			}

			__compelled_inline qeh_uint16 __regcall operator*(imut std::uint16_t value) imut noexcept {
				return qeh_uint16(algo_t_inst(_value.get()) * value);
			}

			__compelled_inline qeh_uint16 __regcall operator&(imut std::uint16_t value) imut noexcept {
				return qeh_uint16(algo_t_inst(_value.get()) & value);
			}

			__compelled_inline qeh_uint16 __regcall operator|(imut std::uint16_t value) imut noexcept {
				return qeh_uint16(algo_t_inst(_value.get()) | value);
			}

			__compelled_inline qeh_uint16 __regcall operator%(imut std::uint16_t value) imut noexcept {
				return qeh_uint16(algo_t_inst(_value.get()) % value);
			}

			__compelled_inline qeh_uint16 __regcall operator^(imut std::uint16_t value) imut noexcept {
				return qeh_uint16(algo_t_inst(_value.get()) ^ value);
			}

			__compelled_inline qeh_uint16 __regcall operator<<(imut std::uint16_t value) imut noexcept {
				return qeh_uint16(algo_t_inst(_value.get()) << value);
			}

			__compelled_inline qeh_uint16 __regcall operator>>(imut std::uint16_t value) imut noexcept {
				return qeh_uint16(algo_t_inst(_value.get()) >> value);
			}

			__compelled_inline qeh_uint16& __regcall operator+=(imut std::uint16_t value) noexcept {
				this->_value = algo_t_inst(static_cast<std::uint16_t>(algo_t_inst(_value.get()) + value));
				return *this;
			}

			__compelled_inline qeh_uint16& __regcall operator-=(imut std::uint16_t value) noexcept {
				this->_value = algo_t_inst(static_cast<std::uint16_t>(algo_t_inst(_value.get()) - value));
				return *this;
			}

			__compelled_inline qeh_uint16& __stackcall operator++() noexcept {
				operator+=(1ui16);
				return *this;
			}

			__compelled_inline qeh_uint16& __stackcall operator--() noexcept {
				operator-=(1ui16);
				return *this;
			}

			__compelled_inline qeh_uint16& __regcall operator*=(imut std::uint16_t value) noexcept {
				this->_value = algo_t_inst(static_cast<std::uint16_t>(algo_t_inst(_value.get()) * value));
				return *this;
			}

			__compelled_inline qeh_uint16& __regcall operator/=(imut std::uint16_t value) noexcept {
				this->_value = algo_t_inst(static_cast<std::uint16_t>(algo_t_inst(_value.get()) / value));
				return *this;
			}

			__compelled_inline qeh_uint16& __regcall operator%=(imut std::uint16_t value) noexcept {
				this->_value = algo_t_inst(static_cast<std::uint16_t>(algo_t_inst(_value.get()) % value));
				return *this;
			}

			__compelled_inline qeh_uint16& __regcall operator^=(imut std::uint16_t value) noexcept {
				this->_value = algo_t_inst(static_cast<std::uint16_t>(algo_t_inst(_value.get()) ^ value));
				return *this;
			}

			__compelled_inline qeh_uint16& __regcall operator&=(imut std::uint16_t value) noexcept {
				this->_value = algo_t_inst(static_cast<std::uint16_t>(algo_t_inst(_value.get()) & value));
				return *this;
			}

			__compelled_inline qeh_uint16& __regcall operator|=(imut std::uint16_t value) noexcept {
				this->_value = algo_t_inst(static_cast<std::uint16_t>(algo_t_inst(_value.get()) | value));
				return *this;
			}

			__compelled_inline qeh_uint16& __regcall operator<<=(imut std::uint16_t value) noexcept {
				this->_value = algo_t_inst(static_cast<std::uint16_t>(algo_t_inst(_value.get()) << value));
				return *this;
			}

			__compelled_inline qeh_uint16& __regcall operator>>=(imut std::uint16_t value) noexcept {
				this->_value = algo_t_inst(static_cast<std::uint16_t>(algo_t_inst(_value.get()) >> value));
				return *this;
			}

			__compelled_inline qeh_uint16& __regcall operator=(imut std::uint16_t value) noexcept {
				_value = algo_t_inst(value);
				return *this;
			}

			__compelled_inline __stackcall operator std::uint16_t() imut noexcept {
				return algo_t_inst(_value.get());
			}

			__compelled_inline __stackcall ~qeh_uint16() noexcept { }
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

			__compelled_inline __regcall qeh_int32(imut std::int32_t value = 0) noexcept : _value(algo_t_inst(value)) {

				if (!is_init)
					init_qtype_hash();

				set(value);
			}

	#pragma endregion

	#pragma region Accessors

			__compelled_inline int __stackcall get() imut noexcept {
				return algo_t_inst(_value.get());
			}

			__compelled_inline void __regcall set(imut std::int32_t value) noexcept {
				_value = algo_t_inst(value);
			}

			__compelled_inline imut void* __stackcall get_raw_memory_address() imut noexcept {
				return _value.get_raw_memory_address();
			}
	#pragma endregion

	#pragma region Operators

			__compelled_inline qeh_int32 __regcall operator+(imut std::int32_t value) imut noexcept {
				return qeh_int32(algo_t_inst(_value.get()) + value);
			};

			__compelled_inline qeh_int32 __regcall operator-(imut std::int32_t value) imut noexcept {
				return qeh_int32(algo_t_inst(_value.get()) - value);
			}

			__compelled_inline qeh_int32 __regcall operator/(imut std::int32_t value) imut noexcept {
				return qeh_int32(algo_t_inst(_value.get()) / value);
			}

			__compelled_inline qeh_int32 __regcall operator*(imut std::int32_t value) imut noexcept {
				return qeh_int32(algo_t_inst(_value.get()) * value);
			}

			__compelled_inline qeh_int32 __regcall operator&(imut std::int32_t value) imut noexcept {
				return qeh_int32(algo_t_inst(_value.get()) & value);
			}

			__compelled_inline qeh_int32 __regcall operator|(imut std::int32_t value) imut noexcept {
				return qeh_int32(algo_t_inst(_value.get()) | value);
			}

			__compelled_inline qeh_int32 __regcall operator%(imut std::int32_t value) imut noexcept {
				return qeh_int32(algo_t_inst(_value.get()) % value);
			}

			__compelled_inline qeh_int32 __regcall operator^(imut std::int32_t value) imut noexcept {
				return qeh_int32(algo_t_inst(_value.get()) ^ value);
			}

			__compelled_inline qeh_int32 __regcall operator<<(imut std::int32_t value) imut noexcept {
				return qeh_int32(algo_t_inst(_value.get()) << value);
			}

			__compelled_inline qeh_int32 __regcall operator>>(imut std::int32_t value) imut noexcept {
				return qeh_int32(algo_t_inst(_value.get()) >> value);
			}

			__compelled_inline qeh_int32& __regcall operator+=(imut std::int32_t value) noexcept {
				this->_value = algo_t_inst(static_cast<std::int32_t>(algo_t_inst(_value.get()) + value));
				return *this;
			}

			__compelled_inline qeh_int32& __regcall operator-=(imut std::int32_t value) noexcept {
				this->_value = algo_t_inst(static_cast<std::int32_t>(algo_t_inst(_value.get()) - value));
				return *this;
			}

			__compelled_inline qeh_int32& __stackcall operator++() noexcept {
				operator+=(1i32);
				return *this;
			}

			__compelled_inline qeh_int32& __stackcall operator--() noexcept {
				operator-=(1i32);
				return *this;
			}

			__compelled_inline qeh_int32& __regcall operator*=(imut std::int32_t value) noexcept {

				this->_value = algo_t_inst(static_cast<std::int32_t>(algo_t_inst(_value.get()) * value));
				return *this;
			}

			__compelled_inline qeh_int32& __regcall operator/=(imut std::int32_t value) noexcept {

				this->_value = algo_t_inst(static_cast<std::int32_t>(algo_t_inst(_value.get()) / value));
				return *this;
			}

			__compelled_inline qeh_int32& __regcall operator%=(imut std::int32_t value) noexcept {

				this->_value = algo_t_inst(static_cast<std::int32_t>(algo_t_inst(_value.get()) % value));
				return *this;
			}

			__compelled_inline qeh_int32& __regcall operator^=(imut std::int32_t value) noexcept {

				this->_value = algo_t_inst(static_cast<std::int32_t>(algo_t_inst(_value.get()) ^ value));
				return *this;
			}

			__compelled_inline qeh_int32& __regcall operator&=(imut std::int32_t value) noexcept {

				this->_value = algo_t_inst(static_cast<std::int32_t>(algo_t_inst(_value.get()) & value));
				return *this;
			}

			__compelled_inline qeh_int32& __regcall operator|=(imut std::int32_t value) noexcept {

				this->_value = algo_t_inst(static_cast<std::int32_t>(algo_t_inst(_value.get()) | value));
				return *this;
			}

			__compelled_inline qeh_int32& __regcall operator<<=(imut std::int32_t value) noexcept {

				this->_value = algo_t_inst(static_cast<std::int32_t>(algo_t_inst(_value.get()) << value));
				return *this;
			}

			__compelled_inline qeh_int32& __regcall operator>>=(imut std::int32_t value) noexcept {
				this->_value = algo_t_inst(static_cast<std::int32_t>(algo_t_inst(_value.get()) >> value));
				return *this;
			}

			__compelled_inline qeh_int32& __regcall operator=(imut std::int32_t value) noexcept {
				_value = algo_t_inst(value);
				return *this;
			}

			__compelled_inline __stackcall operator std::int32_t() imut noexcept {
				return get();
			}

			__compelled_inline __stackcall ~qeh_int32() noexcept { }
	#pragma endregion
		};

		class qeh_uint32 {

		private:

	#pragma region Encrypted value

			qtype_hash::qh_uint32 _value;

	#pragma endregion

		public:

	#pragma region CTOR

			__compelled_inline __regcall qeh_uint32(imut std::uint32_t value = 0) noexcept : _value(algo_t_inst(value)) {

				if (!is_init)
					init_qtype_hash();

				set(value);
			}

	#pragma endregion

	#pragma region Accessors

			__compelled_inline std::uint32_t __stackcall get() imut noexcept {
				return algo_t_inst(_value.get());
			}

			__compelled_inline void __regcall set(imut std::uint32_t value) noexcept {
				_value = algo_t_inst(value);
			}

			__compelled_inline imut void* __stackcall get_raw_memory_address() imut noexcept {
				return _value.get_raw_memory_address();
			}
	#pragma endregion

	#pragma region Operators

			__compelled_inline qeh_uint32 __regcall operator+(imut std::uint32_t value) imut noexcept {
				return qeh_uint32(algo_t_inst(_value.get()) + value);
			};

			__compelled_inline qeh_uint32 __regcall operator-(imut std::uint32_t value) imut noexcept {
				return qeh_uint32(algo_t_inst(_value.get()) - value);
			}

			__compelled_inline qeh_uint32 __regcall operator/(imut std::uint32_t value) imut noexcept {
				return qeh_uint32(algo_t_inst(_value.get()) / value);
			}

			__compelled_inline qeh_uint32 __regcall operator*(imut std::uint32_t value) imut noexcept {
				return qeh_uint32(algo_t_inst(_value.get()) * value);
			}

			__compelled_inline qeh_uint32 __regcall operator&(imut std::uint32_t value) imut noexcept {
				return qeh_uint32(algo_t_inst(_value.get()) & value);
			}

			__compelled_inline qeh_uint32 __regcall operator|(imut std::uint32_t value) imut noexcept {
				return qeh_uint32(algo_t_inst(_value.get()) | value);
			}

			__compelled_inline qeh_uint32 __regcall operator%(imut std::uint32_t value) imut noexcept {
				return qeh_uint32(algo_t_inst(_value.get()) % value);
			}

			__compelled_inline qeh_uint32 __regcall operator^(imut std::uint32_t value) imut noexcept {
				return qeh_uint32(algo_t_inst(_value.get()) ^ value);
			}

			__compelled_inline qeh_uint32 __regcall operator<<(imut std::uint32_t value) imut noexcept {
				return qeh_uint32(algo_t_inst(_value.get()) << value);
			}

			__compelled_inline qeh_uint32 __regcall operator>>(imut std::uint32_t value) imut noexcept {
				return qeh_uint32(algo_t_inst(_value.get()) >> value);
			}

			__compelled_inline qeh_uint32& __regcall operator+=(imut std::uint32_t value) noexcept {
				this->_value = algo_t_inst(static_cast<int>(algo_t_inst(_value.get()) + value));
				return *this;
			}

			__compelled_inline qeh_uint32& __regcall operator-=(imut std::uint32_t value) noexcept {
				this->_value = algo_t_inst(static_cast<int>(algo_t_inst(_value.get()) - value));
				return *this;
			}

			__compelled_inline qeh_uint32& __stackcall operator++() noexcept {
				operator+=(1ui32);
				return *this;
			}

			__compelled_inline qeh_uint32& __stackcall operator--() noexcept {
				operator-=(1ui32);
				return *this;
			}

			__compelled_inline qeh_uint32& __regcall operator*=(imut std::uint32_t value) noexcept {
				this->_value = algo_t_inst(static_cast<std::uint32_t>(algo_t_inst(_value.get()) * value));
				return *this;
			}

			__compelled_inline qeh_uint32& __regcall operator/=(imut std::uint32_t value) noexcept {
				this->_value = algo_t_inst(static_cast<std::uint32_t>(algo_t_inst(_value.get()) / value));
				return *this;
			}

			__compelled_inline qeh_uint32& __regcall operator%=(imut std::uint32_t value) noexcept {
				this->_value = algo_t_inst(static_cast<std::uint32_t>(algo_t_inst(_value.get()) % value));
				return *this;
			}

			__compelled_inline qeh_uint32& __regcall operator^=(imut std::uint32_t value) noexcept {
				this->_value = algo_t_inst(static_cast<std::uint32_t>(algo_t_inst(_value.get()) ^ value));
				return *this;
			}

			__compelled_inline qeh_uint32& __regcall operator&=(imut std::uint32_t value) noexcept {
				this->_value = algo_t_inst(static_cast<std::uint32_t>(algo_t_inst(_value.get()) & value));
				return *this;
			}

			__compelled_inline qeh_uint32& __regcall operator|=(imut std::uint32_t value) noexcept {
				this->_value = algo_t_inst(static_cast<std::uint32_t>(algo_t_inst(_value.get()) | value));
				return *this;
			}

			__compelled_inline qeh_uint32& __regcall operator<<=(imut std::uint32_t value) noexcept {
				this->_value = algo_t_inst(static_cast<std::uint32_t>(algo_t_inst(_value.get()) << value));
				return *this;
			}

			__compelled_inline qeh_uint32& __regcall operator>>=(imut std::uint32_t value) noexcept {
				this->_value = algo_t_inst(static_cast<std::uint32_t>(algo_t_inst(_value.get()) >> value));
				return *this;
			}

			__compelled_inline qeh_uint32& __regcall operator=(imut std::uint32_t value) noexcept {
				_value = algo_t_inst(value);
				return *this;
			}

			__compelled_inline __stackcall operator std::uint32_t() imut noexcept {
				return algo_t_inst(_value.get());
			}

			__compelled_inline __stackcall ~qeh_uint32() noexcept { }

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

			__compelled_inline __regcall qeh_int64(imut std::int64_t value = 0) noexcept : _value(algo_t_inst(value)) {

				if (!is_init)
					init_qtype_hash();

				set(value);
			}

	#pragma endregion

	#pragma region Accessors

			__compelled_inline std::int64_t __stackcall get() imut noexcept {
				return algo_t_inst(_value.get());
			}

			__compelled_inline void __regcall set(imut std::int64_t value) noexcept {
				_value = algo_t_inst(value);
			}

			__compelled_inline imut void* __stackcall get_raw_memory_address() imut noexcept {
				return _value.get_raw_memory_address();
			}
	#pragma endregion

	#pragma region Operators

			__compelled_inline qeh_int64 __regcall operator+(imut std::int64_t value) imut noexcept {
				return qeh_int64(algo_t_inst(_value.get()) + value);
			};

			__compelled_inline qeh_int64 __regcall operator-(imut std::int64_t value) imut noexcept {
				return qeh_int64(algo_t_inst(_value.get()) - value);
			}

			__compelled_inline qeh_int64 __regcall operator/(imut std::int64_t value) imut noexcept {
				return qeh_int64(algo_t_inst(_value.get()) / value);
			}

			__compelled_inline qeh_int64 __regcall operator*(imut std::int64_t value) imut noexcept {
				return qeh_int64(algo_t_inst(_value.get()) * value);
			}

			__compelled_inline qeh_int64 __regcall operator&(imut std::int64_t value) imut noexcept {
				return qeh_int64(algo_t_inst(_value.get()) & value);
			}

			__compelled_inline qeh_int64 __regcall operator|(imut std::int64_t value) imut noexcept {
				return qeh_int64(algo_t_inst(_value.get()) | value);
			}

			__compelled_inline qeh_int64 __regcall operator%(imut std::int64_t value) imut noexcept {
				return qeh_int64(algo_t_inst(_value.get()) % value);
			}

			__compelled_inline qeh_int64 __regcall operator^(imut std::int64_t value) imut noexcept {
				return qeh_int64(algo_t_inst(_value.get()) ^ value);
			}

			__compelled_inline qeh_int64 __regcall operator<<(imut std::int64_t value) imut noexcept {
				return qeh_int64(algo_t_inst(_value.get()) << value);
			}

			__compelled_inline qeh_int64 __regcall operator>>(imut std::int64_t value) imut noexcept {
				return qeh_int64(algo_t_inst(_value.get()) >> value);
			}

			__compelled_inline qeh_int64& __regcall operator+=(imut std::int64_t value) noexcept {
				this->_value = algo_t_inst(static_cast<std::int64_t>(algo_t_inst(_value.get()) + value));
				return *this;
			}

			__compelled_inline qeh_int64& __regcall operator-=(imut std::int64_t value) noexcept {
				this->_value = algo_t_inst(static_cast<std::int64_t>(algo_t_inst(_value.get()) - value));
				return *this;
			}

			__compelled_inline qeh_int64& __stackcall operator++() noexcept {
				operator+=(1i64);
				return *this;
			}

			__compelled_inline qeh_int64& __stackcall operator--() noexcept {
				operator-=(1i64);
				return *this;
			}

			__compelled_inline qeh_int64& __regcall operator*=(imut std::int64_t value) noexcept {
				this->_value = algo_t_inst(static_cast<std::int64_t>(algo_t_inst(_value.get()) * value));
				return *this;
			}

			__compelled_inline qeh_int64& __regcall operator/=(imut std::int64_t value) noexcept {
				this->_value = algo_t_inst(static_cast<std::int64_t>(algo_t_inst(_value.get()) / value));
				return *this;
			}

			__compelled_inline qeh_int64& __regcall operator%=(imut std::int64_t value) noexcept {
				this->_value = algo_t_inst(static_cast<std::int64_t>(algo_t_inst(_value.get()) % value));
				return *this;
			}

			__compelled_inline qeh_int64& __regcall operator^=(imut std::int64_t value) noexcept {
				this->_value = algo_t_inst(static_cast<std::int64_t>(algo_t_inst(_value.get()) ^ value));
				return *this;
			}

			__compelled_inline qeh_int64& __regcall operator&=(imut std::int64_t value) noexcept {
				this->_value = algo_t_inst(static_cast<std::int64_t>(algo_t_inst(_value.get()) & value));
				return *this;
			}

			__compelled_inline qeh_int64& __regcall operator|=(imut std::int64_t value) noexcept {
				this->_value = algo_t_inst(static_cast<std::int64_t>(algo_t_inst(_value.get()) | value));
				return *this;
			}

			__compelled_inline qeh_int64& __regcall operator<<=(imut std::int64_t value) noexcept {
				this->_value = algo_t_inst(static_cast<std::int64_t>(algo_t_inst(_value.get()) << value));
				return *this;
			}

			__compelled_inline qeh_int64& __regcall operator>>=(imut std::int64_t value) noexcept {
				this->_value = algo_t_inst(static_cast<std::int64_t>(algo_t_inst(_value.get()) >> value));
				return *this;
			}

			__compelled_inline qeh_int64& __regcall operator=(imut std::int64_t value) noexcept {
				_value = algo_t_inst(value);
				return *this;
			}

			__compelled_inline __stackcall operator std::int64_t() imut noexcept {
				return algo_t_inst(_value.get());
			}

			__compelled_inline __stackcall ~qeh_int64() noexcept { }
	#pragma endregion
		};

		class qeh_uint64 {
		private:

	#pragma region Encrypted value

			qtype_hash::qh_uint64 _value;

	#pragma endregion

		public:

	#pragma region CTOR

			__compelled_inline __regcall qeh_uint64(imut std::uint64_t value = 0) noexcept : _value(algo_t_inst(value)) {

				if (!is_init)
					init_qtype_hash();

				set(value);
			}

	#pragma endregion

	#pragma region Accessors

			__compelled_inline std::uint64_t __stackcall get() imut noexcept {
				return algo_t_inst(_value.get());
			}

			__compelled_inline void __regcall set(imut std::uint64_t value) noexcept {
				_value = algo_t_inst(value);
			}

			__compelled_inline imut void* __stackcall get_raw_memory_address() imut noexcept {
				return _value.get_raw_memory_address();
			}
	#pragma endregion

	#pragma region Operators

			__compelled_inline qeh_uint64 __regcall operator+(imut std::uint64_t value) imut noexcept {
				return qeh_uint64(algo_t_inst(_value.get()) + value);
			};

			__compelled_inline qeh_uint64 __regcall operator-(imut std::uint64_t value) imut noexcept {
				return qeh_uint64(algo_t_inst(_value.get()) - value);
			}

			__compelled_inline qeh_uint64 __regcall operator/(imut std::uint64_t value) imut noexcept {
				return qeh_uint64(algo_t_inst(_value.get()) / value);
			}

			__compelled_inline qeh_uint64 __regcall operator*(imut std::uint64_t value) imut noexcept {
				return qeh_uint64(algo_t_inst(_value.get()) * value);
			}

			__compelled_inline qeh_uint64 __regcall operator&(imut std::uint64_t value) imut noexcept {
				return qeh_uint64(algo_t_inst(_value.get()) & value);
			}

			__compelled_inline qeh_uint64 __regcall operator|(imut std::uint64_t value) imut noexcept {
				return qeh_uint64(algo_t_inst(_value.get()) | value);
			}

			__compelled_inline qeh_uint64 __regcall operator%(imut std::uint64_t value) imut noexcept {
				return qeh_uint64(algo_t_inst(_value.get()) % value);
			}

			__compelled_inline qeh_uint64 __regcall operator^(imut std::uint64_t value) imut noexcept {
				return qeh_uint64(algo_t_inst(_value.get()) ^ value);
			}

			__compelled_inline qeh_uint64 __regcall operator<<(imut std::uint64_t value) imut noexcept {
				return qeh_uint64(algo_t_inst(_value.get()) << value);
			}

			__compelled_inline qeh_uint64 __regcall operator>>(imut std::uint64_t value) imut noexcept {
				return qeh_uint64(algo_t_inst(_value.get()) >> value);
			}

			__compelled_inline qeh_uint64& __regcall operator+=(imut std::uint64_t value) noexcept {
				this->_value = algo_t_inst(static_cast<std::uint64_t>(algo_t_inst(_value.get()) + value));
				return *this;
			}

			__compelled_inline qeh_uint64& __regcall operator-=(imut std::uint64_t value) noexcept {
				this->_value = algo_t_inst(static_cast<std::uint64_t>(algo_t_inst(_value.get()) - value));
				return *this;
			}

			__compelled_inline qeh_uint64& __stackcall operator++() noexcept {
				operator+=(1ui64);
				return *this;
			}

			__compelled_inline qeh_uint64& __stackcall operator--() noexcept {
				operator-=(1ui64);
				return *this;
			}

			__compelled_inline qeh_uint64& __regcall operator*=(imut std::uint64_t value) noexcept {
				this->_value = algo_t_inst(static_cast<std::uint64_t>(algo_t_inst(_value.get()) * value));
				return *this;
			}

			__compelled_inline qeh_uint64& __regcall operator/=(imut std::uint64_t value) noexcept {
				this->_value = algo_t_inst(static_cast<std::uint64_t>(algo_t_inst(_value.get()) / value));
				return *this;
			}

			__compelled_inline qeh_uint64& __regcall operator%=(imut std::uint64_t value) noexcept {
				this->_value = algo_t_inst(static_cast<std::uint64_t>(algo_t_inst(_value.get()) % value));
				return *this;
			}

			__compelled_inline qeh_uint64& __regcall operator^=(imut std::uint64_t value) noexcept {
				this->_value = algo_t_inst(static_cast<std::uint64_t>(algo_t_inst(_value.get()) ^ value));
				return *this;
			}

			__compelled_inline qeh_uint64& __regcall operator&=(imut std::uint64_t value) noexcept {
				this->_value = algo_t_inst(static_cast<std::uint64_t>(algo_t_inst(_value.get()) & value));
				return *this;
			}

			__compelled_inline qeh_uint64& __regcall operator|=(imut std::uint64_t value) noexcept {
				this->_value = algo_t_inst(static_cast<std::uint64_t>(algo_t_inst(_value.get()) | value));
				return *this;
			}

			__compelled_inline qeh_uint64& __regcall operator<<=(imut std::uint64_t value) noexcept {
				this->_value = algo_t_inst(static_cast<std::uint64_t>(algo_t_inst(_value.get()) << value));
				return *this;
			}

			__compelled_inline qeh_uint64& __regcall operator>>=(imut std::uint64_t value) noexcept {
				this->_value = algo_t_inst(static_cast<std::uint64_t>(algo_t_inst(_value.get()) >> value));
				return *this;
			}

			__compelled_inline qeh_uint64& __regcall operator=(imut std::uint64_t value) noexcept {
				_value = algo_t_inst(value);
				return *this;
			}

			__compelled_inline __stackcall operator std::uint64_t() imut noexcept {
				return algo_t_inst(_value.get());
			}

			__compelled_inline __stackcall ~qeh_uint64() noexcept { }
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

			__compelled_inline __fpcall qeh_float(imut float value = 0.f) noexcept : _value(algo_t_inst(value)) {

				if (!is_init)
					init_qtype_hash();

				set(value);
			}

	#pragma endregion

	#pragma region Accessors

			__compelled_inline float __stackcall get() imut noexcept {
				return algo_t_inst(_value.get());
			}

			__compelled_inline void __fpcall set(imut float value) noexcept {
				_value = algo_t_inst(value);
			}

			__compelled_inline imut void* __stackcall get_raw_memory_address() imut noexcept {
				return _value.get_raw_memory_address();
			}
	#pragma endregion

	#pragma region Operators

			__compelled_inline qeh_float __fpcall operator+(imut float value) imut noexcept {
				return qeh_float(algo_t_inst(_value.get()) + value);
			};

			__compelled_inline qeh_float __fpcall operator-(imut float value) imut noexcept {
				return qeh_float(algo_t_inst(_value.get()) - value);
			}

			__compelled_inline qeh_float __fpcall operator/(imut float value) imut noexcept {
				return qeh_float(algo_t_inst(_value.get()) / value);
			}

			__compelled_inline qeh_float __fpcall operator*(imut float value) imut noexcept {
				return qeh_float(algo_t_inst(_value.get()) * value);
			}

			__compelled_inline qeh_float& __fpcall operator+=(imut float value) noexcept {
				this->_value = algo_t_inst(static_cast<float>(algo_t_inst(_value.get()) + value));
				return *this;
			}

			__compelled_inline qeh_float& __fpcall operator-=(imut float value) noexcept {
				this->_value = algo_t_inst(static_cast<float>(algo_t_inst(_value.get()) - value));
				return *this;
			}

			__compelled_inline qeh_float& __stackcall operator++() noexcept {
				auto local_inst = 0.f;
				++local_inst;
				operator+=(local_inst);
				return *this;
			}

			__compelled_inline qeh_float& __stackcall operator--() noexcept {
				auto local_inst = 0.f;
				--local_inst;
				operator+=(local_inst);
				return *this;
			}

			__compelled_inline qeh_float& __fpcall operator*=(imut float value) noexcept {
				this->_value = algo_t_inst(static_cast<float>(algo_t_inst(_value.get()) * value));
				return *this;
			}

			__compelled_inline qeh_float& __fpcall operator/=(imut float value) noexcept {
				this->_value = algo_t_inst(static_cast<float>(algo_t_inst(_value.get()) / value));
				return *this;
			}

			__compelled_inline qeh_float& __fpcall operator=(imut float value) noexcept {
				_value = algo_t_inst(value);
				return *this;
			}

			__compelled_inline __stackcall operator float() imut noexcept {
				return algo_t_inst(_value.get());
			}

			__compelled_inline __stackcall ~qeh_float() noexcept { }

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

			__compelled_inline __fpcall qeh_double(double value = static_cast<double>(0.f)) noexcept : _value(algo_t_inst(value)) {

				if (!is_init)
					init_qtype_hash();

				set(value);
			}

	#pragma endregion

	#pragma region Accessors

			__compelled_inline double __stackcall get() imut noexcept {
				return algo_t_inst(_value.get());
			}

			__compelled_inline void __fpcall set(double value) noexcept {
				_value = algo_t_inst(value);
			}

			__compelled_inline imut void* __stackcall get_raw_memory_address() imut noexcept {
				return _value.get_raw_memory_address();
			}
	#pragma endregion

	#pragma region Operators

			__compelled_inline qeh_double __fpcall operator+(imut double value) imut noexcept {
				return qeh_double(algo_t_inst(_value.get()) + value);
			};

			__compelled_inline qeh_double __fpcall operator-(imut double value) imut noexcept {
				return qeh_double(algo_t_inst(_value.get()) - value);
			}

			__compelled_inline qeh_double __fpcall operator/(imut double value) imut noexcept {
				return qeh_double(algo_t_inst(_value.get()) / value);
			}

			__compelled_inline qeh_double __fpcall operator*(imut double value) imut noexcept {
				return qeh_double(algo_t_inst(_value.get()) * value);
			}

			__compelled_inline qeh_double& __fpcall operator+=(imut double value) noexcept {
				this->_value = algo_t_inst(static_cast<double>(algo_t_inst(_value.get()) + value));
				return *this;
			}

			__compelled_inline qeh_double& __fpcall operator-=(imut double value) noexcept {
				this->_value = algo_t_inst(static_cast<double>(algo_t_inst(_value.get()) - value));
				return *this;
			}

			__compelled_inline qeh_double& __stackcall operator++() noexcept {
				auto local_inst = static_cast<double>(0.f);
				++local_inst;
				operator+=(local_inst);
				return *this;
			}

			__compelled_inline qeh_double& __stackcall operator--() noexcept {
				auto local_inst = static_cast<double>(0.f);
				--local_inst;
				operator+=(local_inst);
				return *this;
			}

			__compelled_inline qeh_double& __fpcall operator*=(imut double value) noexcept {
				this->_value = algo_t_inst(static_cast<double>(algo_t_inst(_value.get()) * value));
				return *this;
			}

			__compelled_inline qeh_double& __fpcall operator/=(imut double value) noexcept {
				this->_value = algo_t_inst(static_cast<double>(algo_t_inst(_value.get()) / value));
				return *this;
			}

			__compelled_inline qeh_double& __fpcall operator=(imut double value) noexcept {
				_value = algo_t_inst(value);
				return *this;
			}

			__compelled_inline __stackcall operator double() imut noexcept {
				return algo_t_inst(_value.get());
			}

			__compelled_inline __stackcall ~qeh_double() noexcept { }
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

			__compelled_inline __fpcall qeh_m128(imut __m128 value) noexcept : _value(algo_t_inst(value)) {

				if (!is_init)
					init_qtype_hash();

				set(value);
			}

	#pragma endregion

	#pragma region Accessors

			__compelled_inline __m128 __stackcall get() imut noexcept {
				return algo_t_inst(_value.get());
			}

			__compelled_inline void __fpcall set(__m128 value) noexcept {
				_value = algo_t_inst(value);
			}

			__compelled_inline decltype(_value)* get_raw_memory_address() noexcept {
				return &_value;
			}

	#pragma endregion

	#pragma region Operators

	#ifdef __clang__

			__compelled_inline qeh_m128 __fpcall operator+(imut __m128 value) imut noexcept {
				return qeh_m128(get() + value);
			};

			__compelled_inline qeh_m128 __fpcall operator-(imut __m128 value) imut noexcept {
				return qeh_m128(get() - value);
			}

			__compelled_inline qeh_m128 __fpcall operator/(imut __m128 value) imut noexcept {
				return qeh_m128(get() / value);
			}

			__compelled_inline qeh_m128 __fpcall operator*(imut __m128 value) imut noexcept {
				return qeh_m128(get() * value);
			}

			__compelled_inline qeh_m128& __fpcall operator+=(imut __m128 value) noexcept {
				set(static_cast<__m128>(get() + value));
				return *this;
			}

			__compelled_inline qeh_m128& __fpcall operator-=(imut __m128 value) noexcept {
				set(static_cast<__m128>(get() - value));
				return *this;
			}

			__compelled_inline qeh_m128& __fpcall operator*=(imut __m128 value) noexcept {
				set(static_cast<__m128>(get() * value));
				return *this;
			}

			__compelled_inline qeh_m128& __fpcall operator/=(imut __m128 value) noexcept {
				set(static_cast<__m128>(get() / value));
				return *this;
			}

	#endif

			__compelled_inline qeh_m128& __fpcall operator=(imut __m128 value) noexcept {
				set(value);
				return *this;
			}

			__compelled_inline __stackcall operator __m128() imut noexcept {
				return get();
			}

			__compelled_inline __stackcall ~qeh_m128() noexcept {  }
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

			__compelled_inline __fpcall qeh_m128i(imut __m128i value) noexcept : _value(algo_t_inst(value)) {

				if (!is_init)
					init_qtype_hash();

				set(value);
			}

	#pragma endregion

	#pragma region Accessors

			__compelled_inline __m128i __stackcall get() imut noexcept {
				return algo_t_inst(_value.get());
			}

			__compelled_inline void __fpcall set(__m128i value) noexcept {
				_value = algo_t_inst(value);
			}

			__compelled_inline decltype(_value)* get_raw_memory_address() noexcept {
				return &_value;
			}

	#pragma endregion

	#pragma region Operators

	#ifdef __clang__

			__compelled_inline qeh_m128i __fpcall operator+(imut __m128i value) imut noexcept {
				return qeh_m128i(get() + value);
			};

			__compelled_inline qeh_m128i __fpcall operator-(imut __m128i value) imut noexcept {
				return qeh_m128i(get() - value);
			}

			__compelled_inline qeh_m128i __fpcall operator/(imut __m128i value) imut noexcept {
				return qeh_m128i(get() / value);
			}

			__compelled_inline qeh_m128i __fpcall operator*(imut __m128i value) imut noexcept {
				return qeh_m128i(get() * value);
			}

			__compelled_inline qeh_m128i& __fpcall operator+=(imut __m128i value) noexcept {
				set(static_cast<__m128i>(get() + value));
				return *this;
			}

			__compelled_inline qeh_m128i& __fpcall operator-=(imut __m128i value) noexcept {
				set(static_cast<__m128i>(get() - value));
				return *this;
			}

			__compelled_inline qeh_m128i& __fpcall operator*=(imut __m128i value) noexcept {
				set(static_cast<__m128i>(get() * value));
				return *this;
			}

			__compelled_inline qeh_m128i& __fpcall operator/=(imut __m128i value) noexcept {
				set(static_cast<__m128i>(get() / value));
				return *this;
			}

	#endif

			__compelled_inline qeh_m128i& __fpcall operator=(imut __m128i value) noexcept {
				set(value);
				return *this;
			}

			__compelled_inline __stackcall operator __m128i() imut noexcept {
				return get();
			}

			__compelled_inline __stackcall ~qeh_m128i() noexcept { }
	#pragma endregion
		};

		class qeh_m128d {

		private:

	#pragma region Globals

			qtype_hash::qh_m128d _value;

	#pragma endregion

		public:

	#pragma region CTOR

			__compelled_inline __fpcall qeh_m128d(imut __m128d value) noexcept : _value(algo_t_inst(value)) {

				if (!is_init)
					init_qtype_hash();

				set(value);
			}

	#pragma endregion

	#pragma region Accessors

			__compelled_inline __m128d __stackcall get() imut noexcept {
				return algo_t_inst(_value.get());
			}

			__compelled_inline void __fpcall set(__m128d value) noexcept {
				_value = algo_t_inst(value);
			}

			__compelled_inline decltype(_value)* get_raw_memory_address() noexcept {
				return &_value;
			}

	#pragma endregion

	#pragma region Operators

	#ifdef __clang__

			__compelled_inline qeh_m128d __fpcall operator+(imut __m128d value) imut noexcept {
				return qeh_m128d(get() + value);
			};

			__compelled_inline qeh_m128d __fpcall operator-(imut __m128d value) imut noexcept {
				return qeh_m128d(get() - value);
			}

			__compelled_inline qeh_m128d __fpcall operator/(imut __m128d value) imut noexcept {
				return qeh_m128d(get() / value);
			}

			__compelled_inline qeh_m128d __fpcall operator*(imut __m128d value) imut noexcept {
				return qeh_m128d(get() * value);
			}

			__compelled_inline qeh_m128d& __fpcall operator+=(imut __m128d value) noexcept {
				set(static_cast<__m128d>(get() + value));
				return *this;
			}

			__compelled_inline qeh_m128d& __fpcall operator-=(imut __m128d value) noexcept {
				set(static_cast<__m128d>(get() - value));
				return *this;
			}

			__compelled_inline qeh_m128d& __fpcall operator*=(imut __m128d value) noexcept {
				set(static_cast<__m128d>(get() * value));
				return *this;
			}

			__compelled_inline qeh_m128d& __fpcall operator/=(imut __m128d value) noexcept {
				set(static_cast<__m128d>(get() / value));
				return *this;
			}

	#endif

			__compelled_inline qeh_m128d& __fpcall operator=(imut __m128d value) noexcept {
				set(value);
				return *this;
			}

			__compelled_inline __stackcall operator __m128d() imut noexcept {
				return get();
			}

			__compelled_inline __stackcall ~qeh_m128d() noexcept { }
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

			__compelled_inline __fpcall qeh_m256(imut __m256 value) noexcept : _value(algo_t_inst(value)) {

				if (!is_init)
					init_qtype_hash();

				set(value);
			}

	#pragma endregion

	#pragma region Accessors

			__compelled_inline __m256 __stackcall get() imut noexcept {
				return algo_t_inst(_value.get());
			}

			__compelled_inline void __fpcall set(__m256 value) noexcept {
				_value = algo_t_inst(value);
			}

			__compelled_inline decltype(_value)* get_raw_memory_address() noexcept {
				return &_value;
			}

	#pragma endregion

	#pragma region Operators

	#ifdef __clang__

			__compelled_inline qeh_m256 __fpcall operator+(imut __m256 value) imut noexcept {
				return qeh_m256(get() + value);
			};

			__compelled_inline qeh_m256 __fpcall operator-(imut __m256 value) imut noexcept {
				return qeh_m256(get() - value);
			}

			__compelled_inline qeh_m256 __fpcall operator/(imut __m256 value) imut noexcept {
				return qeh_m256(get() / value);
			}

			__compelled_inline qeh_m256 __fpcall operator*(imut __m256 value) imut noexcept {
				return qeh_m256(get() * value);
			}

			__compelled_inline qeh_m256& __fpcall operator+=(imut __m256 value) noexcept {
				set(static_cast<__m256>(get() + value));
				return *this;
			}

			__compelled_inline qeh_m256& __fpcall operator-=(imut __m256 value) noexcept {
				set(static_cast<__m256>(get() - value));
				return *this;
			}

			__compelled_inline qeh_m256& __fpcall operator*=(imut __m256 value) noexcept {
				set(static_cast<__m256>(get() * value));
				return *this;
			}

			__compelled_inline qeh_m256& __fpcall operator/=(imut __m256 value) noexcept {
				set(static_cast<__m256>(get() / value));
				return *this;
			}

	#endif

			__compelled_inline qeh_m256& __fpcall operator=(imut __m256 value) noexcept {
				set(value);
				return *this;
			}

			__compelled_inline __stackcall operator __m256() imut noexcept {
				return get();
			}

			__compelled_inline __stackcall ~qeh_m256() noexcept { }
	#pragma endregion
		};

		class qeh_m256i {
		private:

	#pragma region Globals

			qtype_hash::qh_m256i _value;

	#pragma endregion

		public:

	#pragma region CTOR

			__compelled_inline __fpcall qeh_m256i(imut __m256i value) noexcept : _value(algo_t_inst(value)) {

				if (!is_init)
					init_qtype_hash();

				set(value);
			}

	#pragma endregion

	#pragma region Accessors

			__compelled_inline __m256i __stackcall get() imut noexcept {
				return algo_t_inst(_value.get());
			}

			__compelled_inline void __fpcall set(__m256i value) noexcept {
				_value = algo_t_inst(value);
			}

			__compelled_inline decltype(_value)* get_raw_memory_address() noexcept {
				return &_value;
			}

	#pragma endregion

	#pragma region Operators

	#ifdef __clang__

			__compelled_inline qeh_m256i __fpcall operator+(imut __m256i value) imut noexcept {
				return qeh_m256i(get() + value);
			};

			__compelled_inline qeh_m256i __fpcall operator-(imut __m256i value) imut noexcept {
				return qeh_m256i(get() - value);
			}

			__compelled_inline qeh_m256i __fpcall operator/(imut __m256i value) imut noexcept {
				return qeh_m256i(get() / value);
			}

			__compelled_inline qeh_m256i __fpcall operator*(imut __m256i value) imut noexcept {
				return qeh_m256i(get() * value);
			}

			__compelled_inline qeh_m256i& __fpcall operator+=(imut __m256i value) noexcept {
				set(static_cast<__m256i>(get() + value));
				return *this;
			}

			__compelled_inline qeh_m256i& __fpcall operator-=(imut __m256i value) noexcept {
				set(static_cast<__m256i>(get() - value));
				return *this;
			}

			__compelled_inline qeh_m256i& __fpcall operator*=(imut __m256i value) noexcept {
				set(static_cast<__m256i>(get() * value));
				return *this;
			}

			__compelled_inline qeh_m256i& __fpcall operator/=(imut __m256i value) noexcept {
				set(static_cast<__m256i>(get() / value));
				return *this;
			}

	#endif

			__compelled_inline qeh_m256i& __fpcall operator=(imut __m256i value) noexcept {
				set(value);
				return *this;
			}

			__compelled_inline __stackcall operator __m256i() imut noexcept {
				return get();
			}

			__compelled_inline __stackcall ~qeh_m256i() noexcept { }
	#pragma endregion
		};

		class qeh_m256d {

		private:

	#pragma region Globals

			qtype_hash::qh_m256d _value;

	#pragma endregion

		public:

	#pragma region CTOR

			__compelled_inline __fpcall qeh_m256d(imut __m256d value) noexcept : _value(algo_t_inst(value)) {

				if (!is_init)
					init_qtype_hash();

				set(value);
			}

	#pragma endregion

	#pragma region Accessors

			__compelled_inline __m256d __stackcall get() imut noexcept {
				return algo_t_inst(_value.get());
			}

			__compelled_inline void __fpcall set(__m256d value) noexcept {
				_value = algo_t_inst(value);
			}

			__compelled_inline decltype(_value)* get_raw_memory_address() noexcept {
				return &_value;
			}

	#pragma endregion

	#pragma region Operators

	#ifdef __clang__

			__compelled_inline qeh_m256d __fpcall operator+(imut __m256d value) imut noexcept {
				return qeh_m256d(get() + value);
			};

			__compelled_inline qeh_m256d __fpcall operator-(imut __m256d value) imut noexcept {
				return qeh_m256d(get() - value);
			}

			__compelled_inline qeh_m256d __fpcall operator/(imut __m256d value) imut noexcept {
				return qeh_m256d(get() / value);
			}

			__compelled_inline qeh_m256d __fpcall operator*(imut __m256d value) imut noexcept {
				return qeh_m256d(get() * value);
			}

			__compelled_inline qeh_m256d& __fpcall operator+=(imut __m256d value) noexcept {
				set(static_cast<__m256d>(get() + value));
				return *this;
			}

			__compelled_inline qeh_m256d& __fpcall operator-=(imut __m256d value) noexcept {
				set(static_cast<__m256d>(get() - value));
				return *this;
			}

			__compelled_inline qeh_m256d& __fpcall operator*=(imut __m256d value) noexcept {
				set(static_cast<__m256d>(get() * value));
				return *this;
			}

			__compelled_inline qeh_m256d& __fpcall operator/=(imut __m256d value) noexcept {
				set(static_cast<__m256d>(get() / value));
				return *this;
			}

	#endif

			__compelled_inline qeh_m256d& __fpcall operator=(imut __m256d value) noexcept {
				set(value);
				return *this;
			}

			__compelled_inline __stackcall operator __m256d() imut noexcept {
				return get();
			}

			__compelled_inline __stackcall ~qeh_m256d() noexcept { }
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

			__compelled_inline __stackcall qeh_string(imut std::string value) noexcept {

				//_value = algo_str_inst(value);

				if (!is_init)
					init_qtype_hash();

				set(value);
			}

			__optimized_ctor qeh_string(imut char* value = "") {
				
				//_value = algo_str_inst(std::string(value));

				if (!is_init)
					init_qtype_hash();

				set(value);
			}

	#pragma endregion

	#pragma region Accessors

			__compelled_inline std::string __stackcall get() imut noexcept {
				return algo_str_inst(_value.get());
			}

			__compelled_inline void __stackcall set(imut std::string value) noexcept {
				_value = algo_str_inst(value);
			}

			__compelled_inline imut void* __stackcall get_raw_memory_address() noexcept {
				return _value.get_raw_memory_address();
			}

	#pragma endregion

	#pragma region Operators

			__compelled_inline qeh_string __stackcall operator+(imut std::string& value) imut noexcept {
				return qeh_string(get() + value);
			}

			__compelled_inline qeh_string& __stackcall operator+=(imut std::string& value) noexcept {
				set(static_cast<std::string>(get() + value));
				return *this;
			}

			__compelled_inline qeh_string& __stackcall operator=(imut std::string value) noexcept {
				set(value);
				return *this;
			}

			__compelled_inline __stackcall operator std::string() imut noexcept {
				return get();
			}

			__compelled_inline __stackcall ~qeh_string() noexcept { }

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

			__compelled_inline __stackcall qeh_wstring(imut std::wstring value) noexcept : _value(algo_wstr_inst(value)) {

				if (!is_init)
					init_qtype_hash();

				set(value);
			}

	#pragma endregion

	#pragma region Accessors

			__compelled_inline std::wstring __stackcall get() imut noexcept {
				return algo_wstr_inst(_value.get());
			}

			__compelled_inline void __stackcall set(imut std::wstring& value) noexcept {
				_value = algo_wstr_inst(value);
			}

			__compelled_inline imut void* __stackcall get_raw_memory_address() noexcept {
				return _value.get_raw_memory_address();
			}

	#pragma endregion

	#pragma region Operators

			__compelled_inline qeh_wstring __stackcall operator+(imut std::wstring& value) imut noexcept {
				return qeh_wstring(get() + value);
			}

			__compelled_inline qeh_wstring& __stackcall operator+=(imut std::wstring& value) noexcept {
				set(static_cast<std::wstring>(get() + value));
				return *this;
			}

			__compelled_inline qeh_wstring& __stackcall operator=(imut std::wstring& value) noexcept {
				set(value);
				return *this;
			}

			__compelled_inline __stackcall operator std::wstring() imut noexcept {
				return get();
			}

			__compelled_inline __stackcall ~qeh_wstring() noexcept { }

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

				index_proxy(std::size_t index_, qeh_malloc& instance) noexcept : index(index_), parent(instance) { }

	#pragma endregion

	#pragma region Operator overrides

				__compelled_inline std::uint8_t& operator=(std::uint8_t value) noexcept {

					parent.set(index, value);
					return value;   // return the passed assignment value rather than using up absurd resources to decrypt, re-encrypt everything using get()
				}

				__compelled_inline __regcall operator std::uint8_t() imut noexcept {

					return parent.get(index);
				}

	#pragma endregion
			};

	#pragma endregion

		public:

	#pragma region Ctor

			__compelled_inline __regcall qeh_malloc(std::size_t size) noexcept : allocation(size) {
				if (!size)
					return;

				if (!is_init)
					init_qtype_hash();

				if (!allocation.get_raw_memory_address())
					throw qexcept::q_badalloc();

			}

	#pragma endregion

	#pragma region Get Accessors

			__compelled_inline void __regcall get(std::uintptr_t source_position, void* destination, std::size_t length) imut noexcept {
				void* dec_alloc = allocation.get();

				algo(dec_alloc, allocation.length());

				memcpy(destination, reinterpret_cast<void*>(reinterpret_cast<std::uintptr_t>(dec_alloc) + source_position), length);

				free(dec_alloc);
			}

			__compelled_inline std::uint8_t __regcall get(std::uintptr_t position) imut noexcept {
				std::uint8_t _return = NULL;

				get(position, &_return, sizeof(_return));

				return _return;
			}

			__compelled_inline void* __regcall get() imut noexcept {

				auto _return = allocation.get();

				algo(_return, allocation.length());

				return _return;
			}

	#pragma endregion

	#pragma region Set Accessors

			__compelled_inline void __regcall set(std::uintptr_t position, void* data, std::size_t length) noexcept {
				auto dec_alloc = allocation.get();

				algo(dec_alloc, allocation.length());

				memcpy(reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(dec_alloc) + position), data, length);

				algo(dec_alloc, allocation.length());

				allocation.swap(dec_alloc, allocation.length());
			}

			template<typename T>
			__compelled_inline void __regcall set(std::uintptr_t position, T value) noexcept {
				set(position, &value, sizeof(decltype(value)));
			}

	#pragma endregion

	#pragma region Utility functions

			__compelled_inline void __regcall reallocate(std::size_t size) noexcept {
				allocation.reallocate(size);
			}

			__compelled_inline imut bool __regcall swap(void* allocation_, std::size_t size, bool free_source = false) noexcept {
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

			__compelled_inline void* get_raw_memory_address() noexcept {
				return allocation.get_raw_memory_address();
			}

	#pragma endregion

	#pragma region Operators

			__compelled_inline index_proxy __regcall operator[](std::size_t index) noexcept {
				return index_proxy(index, *this);
			}

	#pragma endregion

	#pragma region Destructor

			__compelled_inline ~qeh_malloc() noexcept { }

	#pragma endregion
		};

	#pragma endregion

	#pragma region Extended Typedefs

	#ifdef _WIN64

			typedef qeh_uint64 qeh_uintptr_t;
			typedef qeh_uint64 qeh_size_t;

	#else

			typedef qeh_uint32 qeh_uintptr_t;
			typedef qeh_uint32 qeh_size_t;

	#endif

	#pragma endregion

#pragma region Namespacing

	} 

}

#pragma endregion

#pragma region Static Declarators

	bool qengine::qtype_enchash::is_init = false;

#pragma endregion

#endif