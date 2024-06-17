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

#pragma region Ctor / Dtor

			__optimized_ctor qeh_int8(imut std::int8_t value = 0) noexcept : _value(qengine::polyc::algo_t_inst(value)) {

				if (!is_init)
					init_qtype_hash();

				set(value);
			}

			__compelled_inline __stackcall ~qeh_int8() noexcept {
				polyc::unregister_polyc_pointer(_value.open_data_ptr());
			}

#pragma endregion

#pragma region Accessors

			__compelled_inline std::int8_t __stackcall get() imut noexcept {

				polyc::algo(_value.open_data_ptr(), sizeof(std::int8_t));

				auto value = _value.get();

				polyc::algo(_value.open_data_ptr(), sizeof(std::int8_t));

				_value.close_data_ptr();

				return value;
			}

			__compelled_inline bool __regcall set(imut std::int8_t value) noexcept {
				
				*_value.open_data_ptr() = value;

				polyc::algo(_value.open_data_ptr(), sizeof(std::int8_t));

				return _value.close_data_ptr();
			}

			__compelled_inline imut void* __stackcall open_data_ptr() imut noexcept {
				return _value.open_data_ptr();
			}

			__compelled_inline imut void* __stackcall get_raw_memory_address() imut noexcept {
				return _value.get_raw_memory_address();
			}

#pragma endregion

#pragma region Operators

			__compelled_inline qeh_int8 __regcall operator+(imut std::int8_t value) imut noexcept {
				return qeh_int8(get() + value);
			};

			__compelled_inline qeh_int8 __regcall operator-(imut std::int8_t value) imut noexcept {
				return qeh_int8(get() - value);
			}

			__compelled_inline qeh_int8 __regcall operator/(imut std::int8_t value) imut noexcept {
				return qeh_int8(get() / value);
			}

			__compelled_inline qeh_int8 __regcall operator*(imut std::int8_t value) imut noexcept {
				return qeh_int8(get() * value);
			}

			__compelled_inline qeh_int8 __regcall operator&(imut std::int8_t value) imut noexcept {
				return qeh_int8(get() & value);
			}

			__compelled_inline qeh_int8 __regcall operator|(imut std::int8_t value) imut noexcept {
				return qeh_int8(get() | value);
			}

			__compelled_inline qeh_int8 __regcall operator%(imut std::int8_t value) imut noexcept {
				return qeh_int8(get() % value);
			}

			__compelled_inline qeh_int8 __regcall operator^(imut std::int8_t value) imut noexcept {
				return qeh_int8(get() ^ value);
			}

			__compelled_inline qeh_int8 __regcall operator<<(imut std::int8_t value) imut noexcept {
				return qeh_int8(get() << value);
			}

			__compelled_inline qeh_int8 __regcall operator>>(imut std::int8_t value) imut noexcept {
				return qeh_int8(get() >> value);
			}

			__compelled_inline qeh_int8& __regcall operator+=(imut std::int8_t value) noexcept {
				set(static_cast<std::int8_t>(get() + value));
				return *this;
			}

			__compelled_inline qeh_int8& __regcall operator-=(imut std::int8_t value) noexcept {
				set(static_cast<std::int8_t>(get() - value));
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
				set(static_cast<std::int8_t>(get() * value));
				return *this;
			}

			__compelled_inline qeh_int8& __regcall operator/=(imut std::int8_t value) noexcept {
				set(static_cast<std::int8_t>(get() / value));
				return *this;
			}

			__compelled_inline qeh_int8& __regcall operator%=(imut std::int8_t value) noexcept {
				set(static_cast<std::int8_t>(get() % value));
				return *this;
			}

			__compelled_inline qeh_int8& __regcall operator^=(imut std::int8_t value) noexcept {
				set(static_cast<std::int8_t>(get() ^ value));
				return *this;
			}

			__compelled_inline qeh_int8& __regcall operator&=(imut std::int8_t value) noexcept {
				set(static_cast<std::int8_t>(get() & value));
				return *this;
			}

			__compelled_inline qeh_int8& __regcall operator|=(imut std::int8_t value) noexcept {
				set(static_cast<std::int8_t>(get() | value));
				return *this;
			}

			__compelled_inline qeh_int8& __regcall operator<<=(imut std::int8_t value) noexcept {
				set(static_cast<std::int8_t>(get() << value));
				return *this;
			}

			__compelled_inline qeh_int8& __regcall operator>>=(imut std::int8_t value) noexcept {
				set(static_cast<std::int8_t>(get() >> value));
				return *this;
			}

			__compelled_inline qeh_int8& __regcall operator=(imut std::int8_t value) noexcept {
				set(value);
				return *this;
			}

			__compelled_inline __stackcall operator std::int8_t() imut noexcept {
				return get();
			}

#pragma endregion

		};

		class qeh_uint8 {

		private:

#pragma region Encrypted value

			qtype_hash::qh_uint8 _value;

#pragma endregion

		public:

#pragma region Ctor / Dtor

			__compelled_inline __regcall qeh_uint8(imut std::uint8_t value = 0) noexcept : _value(algo_t_inst(value)) {

				if (!is_init)
					init_qtype_hash();

				set(value);
			}

			__optimized_dtor ~qeh_uint8() noexcept {
				polyc::unregister_polyc_pointer(_value.open_data_ptr());
			}

#pragma endregion

#pragma region Accessors

			__compelled_inline std::uint8_t __stackcall get() imut noexcept {

				polyc::algo(_value.open_data_ptr(), sizeof(std::uint8_t));

				auto value = _value.get();

				polyc::algo(_value.open_data_ptr(), sizeof(std::uint8_t));

				_value.close_data_ptr();

				return value;
			}

			__compelled_inline bool __regcall set(imut std::uint8_t value) noexcept {

				*_value.open_data_ptr() = value;

				polyc::algo(_value.open_data_ptr(), sizeof(std::uint8_t));

				return _value.close_data_ptr();
			}

			__compelled_inline imut void* __stackcall open_data_ptr() imut noexcept {
				return _value.open_data_ptr();
			}

			__compelled_inline imut void* __stackcall get_raw_memory_address() imut noexcept {
				return _value.get_raw_memory_address();
			}

#pragma endregion

#pragma region Operators

			__compelled_inline qeh_uint8 __regcall operator+(imut std::uint8_t value) imut noexcept {
				return qeh_uint8(get() + value);
			};

			__compelled_inline qeh_uint8 __regcall operator-(imut std::uint8_t value) imut noexcept {
				return qeh_uint8(get() - value);
			}

			__compelled_inline qeh_uint8 __regcall operator/(imut std::uint8_t value) imut noexcept {
				return qeh_uint8(get() / value);
			}

			__compelled_inline qeh_uint8 __regcall operator*(imut std::uint8_t value) imut noexcept {
				return qeh_uint8(get() * value);
			}

			__compelled_inline qeh_uint8 __regcall operator&(imut std::uint8_t value) imut noexcept {
				return qeh_uint8(get() & value);
			}

			__compelled_inline qeh_uint8 __regcall operator|(imut std::uint8_t value) imut noexcept {
				return qeh_uint8(get() | value);
			}

			__compelled_inline qeh_uint8 __regcall operator%(imut std::uint8_t value) imut noexcept {
				return qeh_uint8(get() % value);
			}

			__compelled_inline qeh_uint8 __regcall operator^(imut std::uint8_t value) imut noexcept {
				return qeh_uint8(get() ^ value);
			}

			__compelled_inline qeh_uint8 __regcall operator<<(imut std::uint8_t value) imut noexcept {
				return qeh_uint8(get() << value);
			}

			__compelled_inline qeh_uint8 __regcall operator>>(imut std::uint8_t value) imut noexcept {
				return qeh_uint8(get() >> value);
			}

			__compelled_inline qeh_uint8& __regcall operator+=(imut std::uint8_t value) noexcept {
				set(static_cast<std::uint8_t>(get() + value));
				return *this;
			}

			__compelled_inline qeh_uint8& __regcall operator-=(imut std::uint8_t value) noexcept {
				set(static_cast<std::uint8_t>(get() - value));
				return *this;
			}

			__compelled_inline qeh_uint8& __stackcall operator++() noexcept {
				operator+=(1i8);
				return *this;
			}

			__compelled_inline qeh_uint8& __stackcall operator--() noexcept {
				operator-=(1i8);
				return *this;
			}

			__compelled_inline qeh_uint8& __regcall operator*=(imut std::uint8_t value) noexcept {
				set(static_cast<std::uint8_t>(get() * value));
				return *this;
			}

			__compelled_inline qeh_uint8& __regcall operator/=(imut std::uint8_t value) noexcept {
				set(static_cast<std::uint8_t>(get() / value));
				return *this;
			}

			__compelled_inline qeh_uint8& __regcall operator%=(imut std::uint8_t value) noexcept {
				set(static_cast<std::uint8_t>(get() % value));
				return *this;
			}

			__compelled_inline qeh_uint8& __regcall operator^=(imut std::uint8_t value) noexcept {
				set(static_cast<std::uint8_t>(get() ^ value));
				return *this;
			}

			__compelled_inline qeh_uint8& __regcall operator&=(imut std::uint8_t value) noexcept {
				set(static_cast<std::uint8_t>(get() & value));
				return *this;
			}

			__compelled_inline qeh_uint8& __regcall operator|=(imut std::uint8_t value) noexcept {
				set(static_cast<std::uint8_t>(get() | value));
				return *this;
			}

			__compelled_inline qeh_uint8& __regcall operator<<=(imut std::uint8_t value) noexcept {
				set(static_cast<std::uint8_t>(get() << value));
				return *this;
			}

			__compelled_inline qeh_uint8& __regcall operator>>=(imut std::uint8_t value) noexcept {
				set(static_cast<std::uint8_t>(get() >> value));
				return *this;
			}

			__compelled_inline qeh_uint8& __regcall operator=(imut std::uint8_t value) noexcept {
				set(value);
				return *this;
			}

			__compelled_inline __stackcall operator std::uint8_t() imut noexcept {
				return get();
			}

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

#pragma region Ctor / Dtor

			__optimized_ctor qeh_int16(imut std::int16_t value = 0) noexcept : _value(algo_t_inst(value)) {

				if (!is_init)
					init_qtype_hash();

				set(value);
			}

			__optimized_dtor ~qeh_int16() noexcept {
				polyc::unregister_polyc_pointer(_value.open_data_ptr());
			}

#pragma endregion

#pragma region Accessors

			__compelled_inline std::int16_t __stackcall get() imut noexcept {

				polyc::algo(_value.open_data_ptr(), sizeof(std::int16_t));

				auto value = _value.get();

				polyc::algo(_value.open_data_ptr(), sizeof(std::int16_t));

				_value.close_data_ptr();

				return value;
			}

			__compelled_inline bool __regcall set(imut std::int16_t value) noexcept {

				*_value.open_data_ptr() = value;

				polyc::algo(_value.open_data_ptr(), sizeof(std::int16_t));

				return _value.close_data_ptr();
			}

			__compelled_inline imut void* __stackcall open_data_ptr() imut noexcept {
				return _value.open_data_ptr();
			}

			__compelled_inline imut void* __stackcall get_raw_memory_address() imut noexcept {
				return _value.get_raw_memory_address();
			}

#pragma endregion

#pragma region Operators

			__compelled_inline qeh_int16 __regcall operator+(imut std::int16_t value) imut noexcept {
				return qeh_int16(get() + value);
			};

			__compelled_inline qeh_int16 __regcall operator-(imut std::int16_t value) imut noexcept {
				return qeh_int16(get() - value);
			}

			__compelled_inline qeh_int16 __regcall operator/(imut std::int16_t value) imut noexcept {
				return qeh_int16(get() / value);
			}

			__compelled_inline qeh_int16 __regcall operator*(imut std::int16_t value) imut noexcept {
				return qeh_int16(get() * value);
			}

			__compelled_inline qeh_int16 __regcall operator&(imut std::int16_t value) imut noexcept {
				return qeh_int16(get() & value);
			}

			__compelled_inline qeh_int16 __regcall operator|(imut std::int16_t value) imut noexcept {
				return qeh_int16(get() | value);
			}

			__compelled_inline qeh_int16 __regcall operator%(imut std::int16_t value) imut noexcept {
				return qeh_int16(get() % value);
			}

			__compelled_inline qeh_int16 __regcall operator^(imut std::int16_t value) imut noexcept {
				return qeh_int16(get() ^ value);
			}

			__compelled_inline qeh_int16 __regcall operator<<(imut std::int16_t value) imut noexcept {
				return qeh_int16(get() << value);
			}

			__compelled_inline qeh_int16 __regcall operator>>(imut std::int16_t value) imut noexcept {
				return qeh_int16(get() >> value);
			}

			__compelled_inline qeh_int16& __regcall operator+=(imut std::int16_t value) noexcept {
				set(static_cast<std::int16_t>(get() + value));
				return *this;
			}

			__compelled_inline qeh_int16& __regcall operator-=(imut std::int16_t value) noexcept {
				set(static_cast<std::int16_t>(get() - value));
				return *this;
			}

			__compelled_inline qeh_int16& __stackcall operator++() noexcept {
				operator+=(1i8);
				return *this;
			}

			__compelled_inline qeh_int16& __stackcall operator--() noexcept {
				operator-=(1i8);
				return *this;
			}

			__compelled_inline qeh_int16& __regcall operator*=(imut std::int16_t value) noexcept {
				set(static_cast<std::int16_t>(get() * value));
				return *this;
			}

			__compelled_inline qeh_int16& __regcall operator/=(imut std::int16_t value) noexcept {
				set(static_cast<std::int16_t>(get() / value));
				return *this;
			}

			__compelled_inline qeh_int16& __regcall operator%=(imut std::int16_t value) noexcept {
				set(static_cast<std::int16_t>(get() % value));
				return *this;
			}

			__compelled_inline qeh_int16& __regcall operator^=(imut std::int16_t value) noexcept {
				set(static_cast<std::int16_t>(get() ^ value));
				return *this;
			}

			__compelled_inline qeh_int16& __regcall operator&=(imut std::int16_t value) noexcept {
				set(static_cast<std::int16_t>(get() & value));
				return *this;
			}

			__compelled_inline qeh_int16& __regcall operator|=(imut std::int16_t value) noexcept {
				set(static_cast<std::int16_t>(get() | value));
				return *this;
			}

			__compelled_inline qeh_int16& __regcall operator<<=(imut std::int16_t value) noexcept {
				set(static_cast<std::int16_t>(get() << value));
				return *this;
			}

			__compelled_inline qeh_int16& __regcall operator>>=(imut std::int16_t value) noexcept {
				set(static_cast<std::int16_t>(get() >> value));
				return *this;
			}

			__compelled_inline qeh_int16& __regcall operator=(imut std::int16_t value) noexcept {
				set(value);
				return *this;
			}

			__compelled_inline __stackcall operator std::int16_t() imut noexcept {
				return get();
			}

#pragma endregion

		};

		class qeh_uint16 {

		private:

#pragma region Encrypted value

			qtype_hash::qh_uint16 _value;

#pragma endregion

		public:

#pragma region Ctor / Dtor

			__compelled_inline __regcall qeh_uint16(imut std::uint16_t value = 0) noexcept : _value(algo_t_inst(value)) {

				if (!is_init)
					init_qtype_hash();

				set(value);
			}
			__optimized_dtor ~qeh_uint16() noexcept {
				polyc::unregister_polyc_pointer(_value.open_data_ptr());
			}

#pragma endregion

#pragma region Accessors

			__compelled_inline std::uint16_t __stackcall get() imut noexcept {

				polyc::algo(_value.open_data_ptr(), sizeof(std::uint16_t));

				auto value = _value.get();

				polyc::algo(_value.open_data_ptr(), sizeof(std::uint16_t));

				_value.close_data_ptr();

				return value;
			}

			__compelled_inline bool __regcall set(imut std::uint16_t value) noexcept {

				*_value.open_data_ptr() = value;

				polyc::algo(_value.open_data_ptr(), sizeof(std::uint16_t));

				return _value.close_data_ptr();
			}

			__compelled_inline imut void* __stackcall open_data_ptr() imut noexcept {
				return _value.open_data_ptr();
			}

			__compelled_inline imut void* __stackcall get_raw_memory_address() imut noexcept {
				return _value.get_raw_memory_address();
			}

#pragma endregion

#pragma region Operators

			__compelled_inline qeh_uint16 __regcall operator+(imut std::uint16_t value) imut noexcept {
				return qeh_uint16(get() + value);
			};

			__compelled_inline qeh_uint16 __regcall operator-(imut std::uint16_t value) imut noexcept {
				return qeh_uint16(get() - value);
			}

			__compelled_inline qeh_uint16 __regcall operator/(imut std::uint16_t value) imut noexcept {
				return qeh_uint16(get() / value);
			}

			__compelled_inline qeh_uint16 __regcall operator*(imut std::uint16_t value) imut noexcept {
				return qeh_uint16(get() * value);
			}

			__compelled_inline qeh_uint16 __regcall operator&(imut std::uint16_t value) imut noexcept {
				return qeh_uint16(get() & value);
			}

			__compelled_inline qeh_uint16 __regcall operator|(imut std::uint16_t value) imut noexcept {
				return qeh_uint16(get() | value);
			}

			__compelled_inline qeh_uint16 __regcall operator%(imut std::uint16_t value) imut noexcept {
				return qeh_uint16(get() % value);
			}

			__compelled_inline qeh_uint16 __regcall operator^(imut std::uint16_t value) imut noexcept {
				return qeh_uint16(get() ^ value);
			}

			__compelled_inline qeh_uint16 __regcall operator<<(imut std::uint16_t value) imut noexcept {
				return qeh_uint16(get() << value);
			}

			__compelled_inline qeh_uint16 __regcall operator>>(imut std::uint16_t value) imut noexcept {
				return qeh_uint16(get() >> value);
			}

			__compelled_inline qeh_uint16& __regcall operator+=(imut std::uint16_t value) noexcept {
				set(static_cast<std::uint16_t>(get() + value));
				return *this;
			}

			__compelled_inline qeh_uint16& __regcall operator-=(imut std::uint16_t value) noexcept {
				set(static_cast<std::uint16_t>(get() - value));
				return *this;
			}

			__compelled_inline qeh_uint16& __stackcall operator++() noexcept {
				operator+=(1i8);
				return *this;
			}

			__compelled_inline qeh_uint16& __stackcall operator--() noexcept {
				operator-=(1i8);
				return *this;
			}

			__compelled_inline qeh_uint16& __regcall operator*=(imut std::uint16_t value) noexcept {
				set(static_cast<std::uint16_t>(get() * value));
				return *this;
			}

			__compelled_inline qeh_uint16& __regcall operator/=(imut std::uint16_t value) noexcept {
				set(static_cast<std::uint16_t>(get() / value));
				return *this;
			}

			__compelled_inline qeh_uint16& __regcall operator%=(imut std::uint16_t value) noexcept {
				set(static_cast<std::uint16_t>(get() % value));
				return *this;
			}

			__compelled_inline qeh_uint16& __regcall operator^=(imut std::uint16_t value) noexcept {
				set(static_cast<std::uint16_t>(get() ^ value));
				return *this;
			}

			__compelled_inline qeh_uint16& __regcall operator&=(imut std::uint16_t value) noexcept {
				set(static_cast<std::uint16_t>(get() & value));
				return *this;
			}

			__compelled_inline qeh_uint16& __regcall operator|=(imut std::uint16_t value) noexcept {
				set(static_cast<std::uint16_t>(get() | value));
				return *this;
			}

			__compelled_inline qeh_uint16& __regcall operator<<=(imut std::uint16_t value) noexcept {
				set(static_cast<std::uint16_t>(get() << value));
				return *this;
			}

			__compelled_inline qeh_uint16& __regcall operator>>=(imut std::uint16_t value) noexcept {
				set(static_cast<std::uint16_t>(get() >> value));
				return *this;
			}

			__compelled_inline qeh_uint16& __regcall operator=(imut std::uint16_t value) noexcept {
				set(value);
				return *this;
			}

			__compelled_inline __stackcall operator std::uint16_t() imut noexcept {
				return get();
			}

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

#pragma region Ctor / Dtor

			__compelled_inline __regcall qeh_int32(imut std::int32_t value = 0) noexcept : _value(algo_t_inst(value)) {

				if (!is_init)
					init_qtype_hash();

				set(value);
			}
			__optimized_dtor ~qeh_int32() noexcept {
				polyc::unregister_polyc_pointer(_value.open_data_ptr());
			}

#pragma endregion

#pragma region Accessors

			__compelled_inline std::int32_t __stackcall get() imut noexcept {

				polyc::algo(_value.open_data_ptr(), sizeof(std::int32_t));

				auto value = _value.get();

				polyc::algo(_value.open_data_ptr(), sizeof(std::int32_t));

				_value.close_data_ptr();

				return value;
			}

			__compelled_inline bool __regcall set(imut std::int32_t value) noexcept {

				*_value.open_data_ptr() = value;

				polyc::algo(_value.open_data_ptr(), sizeof(std::int32_t));

				return _value.close_data_ptr();
			}

			__compelled_inline imut void* __stackcall open_data_ptr() imut noexcept {
				return _value.open_data_ptr();
			}

			__compelled_inline imut void* __stackcall get_raw_memory_address() imut noexcept {
				return _value.get_raw_memory_address();
			}

#pragma endregion

#pragma region Operators

			__compelled_inline qeh_int32 __regcall operator+(imut std::int32_t value) imut noexcept {
				return qeh_int32(get() + value);
			};

			__compelled_inline qeh_int32 __regcall operator-(imut std::int32_t value) imut noexcept {
				return qeh_int32(get() - value);
			}

			__compelled_inline qeh_int32 __regcall operator/(imut std::int32_t value) imut noexcept {
				return qeh_int32(get() / value);
			}

			__compelled_inline qeh_int32 __regcall operator*(imut std::int32_t value) imut noexcept {
				return qeh_int32(get() * value);
			}

			__compelled_inline qeh_int32 __regcall operator&(imut std::int32_t value) imut noexcept {
				return qeh_int32(get() & value);
			}

			__compelled_inline qeh_int32 __regcall operator|(imut std::int32_t value) imut noexcept {
				return qeh_int32(get() | value);
			}

			__compelled_inline qeh_int32 __regcall operator%(imut std::int32_t value) imut noexcept {
				return qeh_int32(get() % value);
			}

			__compelled_inline qeh_int32 __regcall operator^(imut std::int32_t value) imut noexcept {
				return qeh_int32(get() ^ value);
			}

			__compelled_inline qeh_int32 __regcall operator<<(imut std::int32_t value) imut noexcept {
				return qeh_int32(get() << value);
			}

			__compelled_inline qeh_int32 __regcall operator>>(imut std::int32_t value) imut noexcept {
				return qeh_int32(get() >> value);
			}

			__compelled_inline qeh_int32& __regcall operator+=(imut std::int32_t value) noexcept {
				set(static_cast<std::int32_t>(get() + value));
				return *this;
			}

			__compelled_inline qeh_int32& __regcall operator-=(imut std::int32_t value) noexcept {
				set(static_cast<std::int32_t>(get() - value));
				return *this;
			}

			__compelled_inline qeh_int32& __stackcall operator++() noexcept {
				operator+=(1i8);
				return *this;
			}

			__compelled_inline qeh_int32& __stackcall operator--() noexcept {
				operator-=(1i8);
				return *this;
			}

			__compelled_inline qeh_int32& __regcall operator*=(imut std::int32_t value) noexcept {
				set(static_cast<std::int32_t>(get() * value));
				return *this;
			}

			__compelled_inline qeh_int32& __regcall operator/=(imut std::int32_t value) noexcept {
				set(static_cast<std::int32_t>(get() / value));
				return *this;
			}

			__compelled_inline qeh_int32& __regcall operator%=(imut std::int32_t value) noexcept {
				set(static_cast<std::int32_t>(get() % value));
				return *this;
			}

			__compelled_inline qeh_int32& __regcall operator^=(imut std::int32_t value) noexcept {
				set(static_cast<std::int32_t>(get() ^ value));
				return *this;
			}

			__compelled_inline qeh_int32& __regcall operator&=(imut std::int32_t value) noexcept {
				set(static_cast<std::int32_t>(get() & value));
				return *this;
			}

			__compelled_inline qeh_int32& __regcall operator|=(imut std::int32_t value) noexcept {
				set(static_cast<std::int32_t>(get() | value));
				return *this;
			}

			__compelled_inline qeh_int32& __regcall operator<<=(imut std::int32_t value) noexcept {
				set(static_cast<std::int32_t>(get() << value));
				return *this;
			}

			__compelled_inline qeh_int32& __regcall operator>>=(imut std::int32_t value) noexcept {
				set(static_cast<std::int32_t>(get() >> value));
				return *this;
			}

			__compelled_inline qeh_int32& __regcall operator=(imut std::int32_t value) noexcept {
				set(value);
				return *this;
			}

			__compelled_inline __stackcall operator std::int32_t() imut noexcept {
				return get();
			}

#pragma endregion
		};

		class qeh_uint32 {

		private:

#pragma region Encrypted value

			qtype_hash::qh_uint32 _value;

#pragma endregion

		public:

#pragma region Ctor / Dtor

			__compelled_inline __regcall qeh_uint32(imut std::uint32_t value = 0) noexcept : _value(algo_t_inst(value)) {

				if (!is_init)
					init_qtype_hash();

				set(value);
			}
			__optimized_dtor ~qeh_uint32() noexcept {
				polyc::unregister_polyc_pointer(_value.open_data_ptr());
			}

#pragma endregion

#pragma region Accessors

			__compelled_inline std::uint32_t __stackcall get() imut noexcept {

				polyc::algo(_value.open_data_ptr(), sizeof(std::uint32_t));

				auto value = _value.get();

				polyc::algo(_value.open_data_ptr(), sizeof(std::uint32_t));

				_value.close_data_ptr();

				return value;
			}

			__compelled_inline bool __regcall set(imut std::uint32_t value) noexcept {

				*_value.open_data_ptr() = value;

				polyc::algo(_value.open_data_ptr(), sizeof(std::uint32_t));

				return _value.close_data_ptr();
			}

			__compelled_inline imut void* __stackcall open_data_ptr() imut noexcept {
				return _value.open_data_ptr();
			}

			__compelled_inline imut void* __stackcall get_raw_memory_address() imut noexcept {
				return _value.get_raw_memory_address();
			}

#pragma endregion

#pragma region Operators

			__compelled_inline qeh_uint32 __regcall operator+(imut std::uint32_t value) imut noexcept {
				return qeh_uint32(get() + value);
			};

			__compelled_inline qeh_uint32 __regcall operator-(imut std::uint32_t value) imut noexcept {
				return qeh_uint32(get() - value);
			}

			__compelled_inline qeh_uint32 __regcall operator/(imut std::uint32_t value) imut noexcept {
				return qeh_uint32(get() / value);
			}

			__compelled_inline qeh_uint32 __regcall operator*(imut std::uint32_t value) imut noexcept {
				return qeh_uint32(get() * value);
			}

			__compelled_inline qeh_uint32 __regcall operator&(imut std::uint32_t value) imut noexcept {
				return qeh_uint32(get() & value);
			}

			__compelled_inline qeh_uint32 __regcall operator|(imut std::uint32_t value) imut noexcept {
				return qeh_uint32(get() | value);
			}

			__compelled_inline qeh_uint32 __regcall operator%(imut std::uint32_t value) imut noexcept {
				return qeh_uint32(get() % value);
			}

			__compelled_inline qeh_uint32 __regcall operator^(imut std::uint32_t value) imut noexcept {
				return qeh_uint32(get() ^ value);
			}

			__compelled_inline qeh_uint32 __regcall operator<<(imut std::uint32_t value) imut noexcept {
				return qeh_uint32(get() << value);
			}

			__compelled_inline qeh_uint32 __regcall operator>>(imut std::uint32_t value) imut noexcept {
				return qeh_uint32(get() >> value);
			}

			__compelled_inline qeh_uint32& __regcall operator+=(imut std::uint32_t value) noexcept {
				set(static_cast<std::uint32_t>(get() + value));
				return *this;
			}

			__compelled_inline qeh_uint32& __regcall operator-=(imut std::uint32_t value) noexcept {
				set(static_cast<std::uint32_t>(get() - value));
				return *this;
			}

			__compelled_inline qeh_uint32& __stackcall operator++() noexcept {
				operator+=(1i8);
				return *this;
			}

			__compelled_inline qeh_uint32& __stackcall operator--() noexcept {
				operator-=(1i8);
				return *this;
			}

			__compelled_inline qeh_uint32& __regcall operator*=(imut std::uint32_t value) noexcept {
				set(static_cast<std::uint32_t>(get() * value));
				return *this;
			}

			__compelled_inline qeh_uint32& __regcall operator/=(imut std::uint32_t value) noexcept {
				set(static_cast<std::uint32_t>(get() / value));
				return *this;
			}

			__compelled_inline qeh_uint32& __regcall operator%=(imut std::uint32_t value) noexcept {
				set(static_cast<std::uint32_t>(get() % value));
				return *this;
			}

			__compelled_inline qeh_uint32& __regcall operator^=(imut std::uint32_t value) noexcept {
				set(static_cast<std::uint32_t>(get() ^ value));
				return *this;
			}

			__compelled_inline qeh_uint32& __regcall operator&=(imut std::uint32_t value) noexcept {
				set(static_cast<std::uint32_t>(get() & value));
				return *this;
			}

			__compelled_inline qeh_uint32& __regcall operator|=(imut std::uint32_t value) noexcept {
				set(static_cast<std::uint32_t>(get() | value));
				return *this;
			}

			__compelled_inline qeh_uint32& __regcall operator<<=(imut std::uint32_t value) noexcept {
				set(static_cast<std::uint32_t>(get() << value));
				return *this;
			}

			__compelled_inline qeh_uint32& __regcall operator>>=(imut std::uint32_t value) noexcept {
				set(static_cast<std::uint32_t>(get() >> value));
				return *this;
			}

			__compelled_inline qeh_uint32& __regcall operator=(imut std::uint32_t value) noexcept {
				set(value);
				return *this;
			}

			__compelled_inline __stackcall operator std::uint32_t() imut noexcept {
				return get();
			}

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

#pragma region Ctor / Dtor

			__compelled_inline __regcall qeh_int64(imut std::int64_t value = 0) noexcept : _value(algo_t_inst(value)) {

				if (!is_init)
					init_qtype_hash();

				set(value);
			}

			__optimized_dtor ~qeh_int64() noexcept {
				polyc::unregister_polyc_pointer(_value.open_data_ptr());
			}

#pragma endregion

#pragma region Accessors

			__compelled_inline std::int64_t __stackcall get() imut noexcept {

				polyc::algo(_value.open_data_ptr(), sizeof(std::int64_t));

				auto value = _value.get();

				polyc::algo(_value.open_data_ptr(), sizeof(std::int64_t));

				_value.close_data_ptr();

				return value;
			}

			__compelled_inline bool __regcall set(imut std::int64_t value) noexcept {

				*_value.open_data_ptr() = value;

				polyc::algo(_value.open_data_ptr(), sizeof(std::int64_t));

				return _value.close_data_ptr();
			}

			__compelled_inline imut void* __stackcall open_data_ptr() imut noexcept {
				return _value.open_data_ptr();
			}

			__compelled_inline imut void* __stackcall get_raw_memory_address() imut noexcept {
				return _value.get_raw_memory_address();
			}

#pragma endregion

#pragma region Operators

			__compelled_inline qeh_int64 __regcall operator+(imut std::int64_t value) imut noexcept {
				return qeh_int64(get() + value);
			};

			__compelled_inline qeh_int64 __regcall operator-(imut std::int64_t value) imut noexcept {
				return qeh_int64(get() - value);
			}

			__compelled_inline qeh_int64 __regcall operator/(imut std::int64_t value) imut noexcept {
				return qeh_int64(get() / value);
			}

			__compelled_inline qeh_int64 __regcall operator*(imut std::int64_t value) imut noexcept {
				return qeh_int64(get() * value);
			}

			__compelled_inline qeh_int64 __regcall operator&(imut std::int64_t value) imut noexcept {
				return qeh_int64(get() & value);
			}

			__compelled_inline qeh_int64 __regcall operator|(imut std::int64_t value) imut noexcept {
				return qeh_int64(get() | value);
			}

			__compelled_inline qeh_int64 __regcall operator%(imut std::int64_t value) imut noexcept {
				return qeh_int64(get() % value);
			}

			__compelled_inline qeh_int64 __regcall operator^(imut std::int64_t value) imut noexcept {
				return qeh_int64(get() ^ value);
			}

			__compelled_inline qeh_int64 __regcall operator<<(imut std::int64_t value) imut noexcept {
				return qeh_int64(get() << value);
			}

			__compelled_inline qeh_int64 __regcall operator>>(imut std::int64_t value) imut noexcept {
				return qeh_int64(get() >> value);
			}

			__compelled_inline qeh_int64& __regcall operator+=(imut std::int64_t value) noexcept {
				set(static_cast<std::int64_t>(get() + value));
				return *this;
			}

			__compelled_inline qeh_int64& __regcall operator-=(imut std::int64_t value) noexcept {
				set(static_cast<std::int64_t>(get() - value));
				return *this;
			}

			__compelled_inline qeh_int64& __stackcall operator++() noexcept {
				operator+=(1i8);
				return *this;
			}

			__compelled_inline qeh_int64& __stackcall operator--() noexcept {
				operator-=(1i8);
				return *this;
			}

			__compelled_inline qeh_int64& __regcall operator*=(imut std::int64_t value) noexcept {
				set(static_cast<std::int64_t>(get() * value));
				return *this;
			}

			__compelled_inline qeh_int64& __regcall operator/=(imut std::int64_t value) noexcept {
				set(static_cast<std::int64_t>(get() / value));
				return *this;
			}

			__compelled_inline qeh_int64& __regcall operator%=(imut std::int64_t value) noexcept {
				set(static_cast<std::int64_t>(get() % value));
				return *this;
			}

			__compelled_inline qeh_int64& __regcall operator^=(imut std::int64_t value) noexcept {
				set(static_cast<std::int64_t>(get() ^ value));
				return *this;
			}

			__compelled_inline qeh_int64& __regcall operator&=(imut std::int64_t value) noexcept {
				set(static_cast<std::int64_t>(get() & value));
				return *this;
			}

			__compelled_inline qeh_int64& __regcall operator|=(imut std::int64_t value) noexcept {
				set(static_cast<std::int64_t>(get() | value));
				return *this;
			}

			__compelled_inline qeh_int64& __regcall operator<<=(imut std::int64_t value) noexcept {
				set(static_cast<std::int64_t>(get() << value));
				return *this;
			}

			__compelled_inline qeh_int64& __regcall operator>>=(imut std::int64_t value) noexcept {
				set(static_cast<std::int64_t>(get() >> value));
				return *this;
			}

			__compelled_inline qeh_int64& __regcall operator=(imut std::int64_t value) noexcept {
				set(value);
				return *this;
			}

			__compelled_inline __stackcall operator std::int64_t() imut noexcept {
				return get();
			}

#pragma endregion
		};

		class qeh_uint64 {
		private:

#pragma region Encrypted value

			qtype_hash::qh_uint64 _value;

#pragma endregion

		public:

#pragma region Ctor / Dtor

			__compelled_inline __regcall qeh_uint64(imut std::uint64_t value = 0) noexcept : _value(algo_t_inst(value)) {

				if (!is_init)
					init_qtype_hash();

				set(value);
			}

			__optimized_dtor ~qeh_uint64() noexcept {
				polyc::unregister_polyc_pointer(_value.open_data_ptr());
			}

#pragma endregion

#pragma region Accessors

			__compelled_inline std::uint64_t __stackcall get() imut noexcept {

				polyc::algo(_value.open_data_ptr(), sizeof(std::uint64_t));

				auto value = _value.get();

				polyc::algo(_value.open_data_ptr(), sizeof(std::uint64_t));

				_value.close_data_ptr();

				return value;
			}

			__compelled_inline bool __regcall set(imut std::uint64_t value) noexcept {

				*_value.open_data_ptr() = value;

				polyc::algo(_value.open_data_ptr(), sizeof(std::uint64_t));

				return _value.close_data_ptr();
			}

			__compelled_inline imut void* __stackcall open_data_ptr() imut noexcept {
				return _value.open_data_ptr();
			}

			__compelled_inline imut void* __stackcall get_raw_memory_address() imut noexcept {
				return _value.get_raw_memory_address();
			}

#pragma endregion

#pragma region Operators

			__compelled_inline qeh_uint64 __regcall operator+(imut std::uint64_t value) imut noexcept {
				return qeh_uint64(get() + value);
			};

			__compelled_inline qeh_uint64 __regcall operator-(imut std::uint64_t value) imut noexcept {
				return qeh_uint64(get() - value);
			}

			__compelled_inline qeh_uint64 __regcall operator/(imut std::uint64_t value) imut noexcept {
				return qeh_uint64(get() / value);
			}

			__compelled_inline qeh_uint64 __regcall operator*(imut std::uint64_t value) imut noexcept {
				return qeh_uint64(get() * value);
			}

			__compelled_inline qeh_uint64 __regcall operator&(imut std::uint64_t value) imut noexcept {
				return qeh_uint64(get() & value);
			}

			__compelled_inline qeh_uint64 __regcall operator|(imut std::uint64_t value) imut noexcept {
				return qeh_uint64(get() | value);
			}

			__compelled_inline qeh_uint64 __regcall operator%(imut std::uint64_t value) imut noexcept {
				return qeh_uint64(get() % value);
			}

			__compelled_inline qeh_uint64 __regcall operator^(imut std::uint64_t value) imut noexcept {
				return qeh_uint64(get() ^ value);
			}

			__compelled_inline qeh_uint64 __regcall operator<<(imut std::uint64_t value) imut noexcept {
				return qeh_uint64(get() << value);
			}

			__compelled_inline qeh_uint64 __regcall operator>>(imut std::uint64_t value) imut noexcept {
				return qeh_uint64(get() >> value);
			}

			__compelled_inline qeh_uint64& __regcall operator+=(imut std::uint64_t value) noexcept {
				set(static_cast<std::uint64_t>(get() + value));
				return *this;
			}

			__compelled_inline qeh_uint64& __regcall operator-=(imut std::uint64_t value) noexcept {
				set(static_cast<std::uint64_t>(get() - value));
				return *this;
			}

			__compelled_inline qeh_uint64& __stackcall operator++() noexcept {
				operator+=(1i8);
				return *this;
			}

			__compelled_inline qeh_uint64& __stackcall operator--() noexcept {
				operator-=(1i8);
				return *this;
			}

			__compelled_inline qeh_uint64& __regcall operator*=(imut std::uint64_t value) noexcept {
				set(static_cast<std::uint64_t>(get() * value));
				return *this;
			}

			__compelled_inline qeh_uint64& __regcall operator/=(imut std::uint64_t value) noexcept {
				set(static_cast<std::uint64_t>(get() / value));
				return *this;
			}

			__compelled_inline qeh_uint64& __regcall operator%=(imut std::uint64_t value) noexcept {
				set(static_cast<std::uint64_t>(get() % value));
				return *this;
			}

			__compelled_inline qeh_uint64& __regcall operator^=(imut std::uint64_t value) noexcept {
				set(static_cast<std::uint64_t>(get() ^ value));
				return *this;
			}

			__compelled_inline qeh_uint64& __regcall operator&=(imut std::uint64_t value) noexcept {
				set(static_cast<std::uint64_t>(get() & value));
				return *this;
			}

			__compelled_inline qeh_uint64& __regcall operator|=(imut std::uint64_t value) noexcept {
				set(static_cast<std::uint64_t>(get() | value));
				return *this;
			}

			__compelled_inline qeh_uint64& __regcall operator<<=(imut std::uint64_t value) noexcept {
				set(static_cast<std::uint64_t>(get() << value));
				return *this;
			}

			__compelled_inline qeh_uint64& __regcall operator>>=(imut std::uint64_t value) noexcept {
				set(static_cast<std::uint64_t>(get() >> value));
				return *this;
			}

			__compelled_inline qeh_uint64& __regcall operator=(imut std::uint64_t value) noexcept {
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

		class qeh_float {

		private:

#pragma region Encrypted value

			qtype_hash::qh_float _value;

#pragma endregion

		public:

#pragma region Ctor / Dtor

			__compelled_inline __fpcall qeh_float(imut float value = 0.f) noexcept : _value(algo_t_inst(value)) {

				if (!is_init)
					init_qtype_hash();

				set(value);
			}
			__optimized_dtor ~qeh_float() noexcept {
				polyc::unregister_polyc_pointer(_value.open_data_ptr());
			}

#pragma endregion

#pragma region Accessors

			__compelled_inline float __stackcall get() imut noexcept {

				polyc::algo(_value.open_data_ptr(), sizeof(float));

				auto value = _value.get();

				polyc::algo(_value.open_data_ptr(), sizeof(float));

				_value.close_data_ptr();

				return value;
			}

			__compelled_inline bool __regcall set(imut float value) noexcept {

				*_value.open_data_ptr() = value;

				polyc::algo(_value.open_data_ptr(), sizeof(float));

				return _value.close_data_ptr();
			}

			__compelled_inline imut void* __stackcall open_data_ptr() imut noexcept {
				return _value.open_data_ptr();
			}

			__compelled_inline imut void* __stackcall get_raw_memory_address() imut noexcept {
				return _value.get_raw_memory_address();
			}

#pragma endregion

#pragma region Operators

			__compelled_inline qeh_float __regcall operator+(imut float value) imut noexcept {
				return qeh_float(get() + value);
			};

			__compelled_inline qeh_float __regcall operator-(imut float value) imut noexcept {
				return qeh_float(get() - value);
			}

			__compelled_inline qeh_float __regcall operator/(imut float value) imut noexcept {
				return qeh_float(get() / value);
			}

			__compelled_inline qeh_float __regcall operator*(imut float value) imut noexcept {
				return qeh_float(get() * value);
			}

			__compelled_inline qeh_float& __regcall operator+=(imut float value) noexcept {
				set(static_cast<float>(get() + value));
				return *this;
			}

			__compelled_inline qeh_float& __regcall operator-=(imut float value) noexcept {
				set(static_cast<float>(get() - value));
				return *this;
			}

			__compelled_inline qeh_float& __stackcall operator++() noexcept {
				operator+=(1i8);
				return *this;
			}

			__compelled_inline qeh_float& __stackcall operator--() noexcept {
				operator-=(1i8);
				return *this;
			}

			__compelled_inline qeh_float& __regcall operator*=(imut float value) noexcept {
				set(static_cast<float>(get() * value));
				return *this;
			}

			__compelled_inline qeh_float& __regcall operator/=(imut float value) noexcept {
				set(static_cast<float>(get() / value));
				return *this;
			}

			__compelled_inline qeh_float& __regcall operator=(imut float value) noexcept {
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

		class qeh_double {

		private:

#pragma region Encrypted value

			qtype_hash::qh_double _value;

#pragma endregion

		public:

#pragma region Ctor / Dtor

			__compelled_inline __fpcall qeh_double(double value = static_cast<double>(0.f)) noexcept : _value(algo_t_inst(value)) {

				if (!is_init)
					init_qtype_hash();

				set(value);
			}

			__optimized_dtor ~qeh_double() noexcept {
				polyc::unregister_polyc_pointer(_value.open_data_ptr());
			}

#pragma endregion

#pragma endregion

#pragma region Accessors

			__compelled_inline double __stackcall get() imut noexcept {

				polyc::algo(_value.open_data_ptr(), sizeof(double));

				auto value = _value.get();

				polyc::algo(_value.open_data_ptr(), sizeof(double));

				_value.close_data_ptr();

				return value;
			}

			__compelled_inline bool __regcall set(imut double value) noexcept {

				*_value.open_data_ptr() = value;

				polyc::algo(_value.open_data_ptr(), sizeof(double));

				return _value.close_data_ptr();
			}

			__compelled_inline imut void* __stackcall open_data_ptr() imut noexcept {
				return _value.open_data_ptr();
			}

			__compelled_inline imut void* __stackcall get_raw_memory_address() imut noexcept {
				return _value.get_raw_memory_address();
			}

#pragma endregion

#pragma region Operators

			__compelled_inline qeh_double __regcall operator+(imut double value) imut noexcept {
				return qeh_double(get() + value);
			};

			__compelled_inline qeh_double __regcall operator-(imut double value) imut noexcept {
				return qeh_double(get() - value);
			}

			__compelled_inline qeh_double __regcall operator/(imut double value) imut noexcept {
				return qeh_double(get() / value);
			}

			__compelled_inline qeh_double __regcall operator*(imut double value) imut noexcept {
				return qeh_double(get() * value);
			}

			__compelled_inline qeh_double& __regcall operator+=(imut double value) noexcept {
				set(static_cast<double>(get() + value));
				return *this;
			}

			__compelled_inline qeh_double& __regcall operator-=(imut double value) noexcept {
				set(static_cast<double>(get() - value));
				return *this;
			}

			__compelled_inline qeh_double& __stackcall operator++() noexcept {
				operator+=(1i8);
				return *this;
			}

			__compelled_inline qeh_double& __stackcall operator--() noexcept {
				operator-=(1i8);
				return *this;
			}

			__compelled_inline qeh_double& __regcall operator*=(imut double value) noexcept {
				set(static_cast<double>(get() * value));
				return *this;
			}

			__compelled_inline qeh_double& __regcall operator/=(imut double value) noexcept {
				set(static_cast<double>(get() / value));
				return *this;
			}

			__compelled_inline qeh_double& __regcall operator=(imut double value) noexcept {
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

#pragma region Extended Types

#pragma region SSE

	#ifdef __SSE__

		class qeh_m128 {

		private:

#pragma region Globals

			qtype_hash::qh_m128 _value;

#pragma endregion

		public:

#pragma region Ctor / Dtor

			__compelled_inline __fpcall qeh_m128(imut __m128 value) noexcept : _value(algo_t_inst(value)) {

				if (!is_init)
					init_qtype_hash();

				set(value);
			}

			__optimized_dtor ~qeh_m128() noexcept {
				polyc::unregister_polyc_pointer(_value.open_data_ptr());
			}

#pragma endregion

#pragma region Accessors

			__compelled_inline __m128 __stackcall get() imut noexcept {

				polyc::algo(_value.open_data_ptr(), sizeof(__m128));

				auto value = _value.get();

				polyc::algo(_value.open_data_ptr(), sizeof(__m128));

				_value.close_data_ptr();

				return value;
			}

			__compelled_inline bool __regcall set(imut __m128 value) noexcept {

				*_value.open_data_ptr() = value;

				polyc::algo(_value.open_data_ptr(), sizeof(__m128));

				return _value.close_data_ptr();
			}

			__compelled_inline imut void* __stackcall open_data_ptr() imut noexcept {
				return _value.open_data_ptr();
			}

			__compelled_inline imut void* __stackcall get_raw_memory_address() imut noexcept {
				return _value.get_raw_memory_address();
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

#pragma endregion

		};

	#ifdef __SSE2__

		class qeh_m128i {

		private:

#pragma region Globals

			qtype_hash::qh_m128i _value;

#pragma endregion

		public:

#pragma region Ctor / Dtor

			__compelled_inline __fpcall qeh_m128i(imut __m128i value) noexcept : _value(algo_t_inst(value)) {

				if (!is_init)
					init_qtype_hash();

				set(value);
			}

			__optimized_dtor ~qeh_m128i() noexcept {
				polyc::unregister_polyc_pointer(_value.open_data_ptr());
			}

#pragma endregion

#pragma region Accessors

			__compelled_inline __m128i __stackcall get() imut noexcept {

				polyc::algo(_value.open_data_ptr(), sizeof(__m128i));

				auto value = _value.get();

				polyc::algo(_value.open_data_ptr(), sizeof(__m128i));

				_value.close_data_ptr();

				return value;
			}

			__compelled_inline bool __regcall set(imut __m128i value) noexcept {

				*_value.open_data_ptr() = value;

				polyc::algo(_value.open_data_ptr(), sizeof(__m128i));

				return _value.close_data_ptr();
			}

			__compelled_inline imut void* __stackcall open_data_ptr() imut noexcept {
				return _value.open_data_ptr();
			}

			__compelled_inline imut void* __stackcall get_raw_memory_address() imut noexcept {
				return _value.get_raw_memory_address();
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

#pragma endregion

		};

		class qeh_m128d {

		private:

#pragma region Globals

			qtype_hash::qh_m128d _value;

#pragma endregion

		public:

#pragma region Ctor / Dtor

			__compelled_inline __fpcall qeh_m128d(imut __m128d value) noexcept : _value(algo_t_inst(value)) {

				if (!is_init)
					init_qtype_hash();

				set(value);
			}
			__optimized_dtor ~qeh_m128d() noexcept {
				polyc::unregister_polyc_pointer(_value.open_data_ptr());
			}

#pragma endregion

#pragma region Accessors

			__compelled_inline __m128d __stackcall get() imut noexcept {

				polyc::algo(_value.open_data_ptr(), sizeof(__m128d));

				auto value = _value.get();

				polyc::algo(_value.open_data_ptr(), sizeof(__m128d));

				_value.close_data_ptr();

				return value;
			}

			__compelled_inline bool __regcall set(imut __m128d value) noexcept {

				*_value.open_data_ptr() = value;

				polyc::algo(_value.open_data_ptr(), sizeof(__m128d));

				return _value.close_data_ptr();
			}

			__compelled_inline imut void* __stackcall open_data_ptr() imut noexcept {
				return _value.open_data_ptr();
			}

			__compelled_inline imut void* __stackcall get_raw_memory_address() imut noexcept {
				return _value.get_raw_memory_address();
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

#pragma region Ctor / Dtor

			__compelled_inline __fpcall qeh_m256(imut __m256 value) noexcept : _value(algo_t_inst(value)) {

				if (!is_init)
					init_qtype_hash();

				set(value);
			}

			__optimized_dtor ~qeh_m256() noexcept {
				polyc::unregister_polyc_pointer(_value.open_data_ptr());
			}

#pragma endregion

#pragma region Accessors

			__compelled_inline __m256 __stackcall get() imut noexcept {

				polyc::algo(_value.open_data_ptr(), sizeof(__m256));

				auto value = _value.get();

				polyc::algo(_value.open_data_ptr(), sizeof(__m256));

				_value.close_data_ptr();

				return value;
			}

			__compelled_inline bool __regcall set(imut __m256 value) noexcept {

				*_value.open_data_ptr() = value;

				polyc::algo(_value.open_data_ptr(), sizeof(__m256));

				return _value.close_data_ptr();
			}

			__compelled_inline imut void* __stackcall open_data_ptr() imut noexcept {
				return _value.open_data_ptr();
			}

			__compelled_inline imut void* __stackcall get_raw_memory_address() imut noexcept {
				return _value.get_raw_memory_address();
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
#pragma endregion
		};

		class qeh_m256i {
		private:

#pragma region Globals

			qtype_hash::qh_m256i _value;

#pragma endregion

		public:

#pragma region Ctor / Dtor

			__compelled_inline __fpcall qeh_m256i(imut __m256i value) noexcept : _value(algo_t_inst(value)) {

				if (!is_init)
					init_qtype_hash();

				set(value);
			}

			__optimized_dtor ~qeh_m256i() noexcept {
				polyc::unregister_polyc_pointer(_value.open_data_ptr());
			}

#pragma endregion

#pragma region Accessors

			__compelled_inline __m256i __stackcall get() imut noexcept {

				polyc::algo(_value.open_data_ptr(), sizeof(__m256i));

				auto value = _value.get();

				polyc::algo(_value.open_data_ptr(), sizeof(__m256i));

				_value.close_data_ptr();

				return value;
			}

			__compelled_inline bool __regcall set(imut __m256i value) noexcept {

				*_value.open_data_ptr() = value;

				polyc::algo(_value.open_data_ptr(), sizeof(__m256i));

				return _value.close_data_ptr();
			}

			__compelled_inline imut void* __stackcall open_data_ptr() imut noexcept {
				return _value.open_data_ptr();
			}

			__compelled_inline imut void* __stackcall get_raw_memory_address() imut noexcept {
				return _value.get_raw_memory_address();
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

#pragma endregion
		};

		class qeh_m256d {

		private:

#pragma region Globals

			qtype_hash::qh_m256d _value;

#pragma endregion

		public:

#pragma region Ctor / Dtor

			__compelled_inline __fpcall qeh_m256d(imut __m256d value) noexcept : _value(algo_t_inst(value)) {

				if (!is_init)
					init_qtype_hash();

				set(value);
			}
			__optimized_dtor ~qeh_m256d() noexcept {
				polyc::unregister_polyc_pointer(_value.open_data_ptr());
			}

#pragma endregion

#pragma region Accessors

			__compelled_inline __m256d __stackcall get() imut noexcept {

				polyc::algo(_value.open_data_ptr(), sizeof(__m256d));

				auto value = _value.get();

				polyc::algo(_value.open_data_ptr(), sizeof(__m256d));

				_value.close_data_ptr();

				return value;
			}

			__compelled_inline bool __regcall set(imut __m256d value) noexcept {

				*_value.open_data_ptr() = value;

				polyc::algo(_value.open_data_ptr(), sizeof(__m256d));

				return _value.close_data_ptr();
			}

			__compelled_inline imut void* __stackcall open_data_ptr() imut noexcept {
				return _value.open_data_ptr();
			}

			__compelled_inline imut void* __stackcall get_raw_memory_address() imut noexcept {
				return _value.get_raw_memory_address();
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

#pragma region Ctor / Dtor

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

			__compelled_inline __stackcall ~qeh_string() noexcept { 
				
				polyc::unregister_polyc_pointer((c_void)_value.open_data_ptr());
			}

#pragma endregion

#pragma region Accessors

			__compelled_inline std::string __stackcall get() imut noexcept {
				
				polyc::algo(const_cast<char*>(_value.open_data_ptr()), _value.get().length());

				auto value = _value.get();

				polyc::algo(const_cast<char*>(_value.open_data_ptr()), _value.get().length());

				_value.close_data_ptr();

				return value;
			}

			__compelled_inline bool __stackcall set(imut std::string value) noexcept {
				
				*_value.open_str_ptr() = value;

				return polyc::algo(const_cast<char*>(_value.open_data_ptr()), _value.get().length());

				return _value.close_data_ptr();
			}

			__compelled_inline imut void* __stackcall open_data_ptr() noexcept {
				return _value.open_data_ptr();
			}

			__compelled_inline imut void* __stackcall get_raw_memory_address() imut noexcept {
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

#pragma region Ctor / Dtor

			__compelled_inline __stackcall qeh_wstring(imut std::wstring value) noexcept : _value(algo_wstr_inst(value)) {

				if (!is_init)
					init_qtype_hash();

				set(value);
			}

			__compelled_inline __stackcall ~qeh_wstring() noexcept {
				
				polyc::unregister_polyc_pointer((imut c_void)_value.open_data_ptr());
			}

#pragma endregion

#pragma region Accessors

			__compelled_inline std::wstring __stackcall get() imut noexcept {

				polyc::algo(const_cast<wchar_t*>(_value.open_data_ptr()), _value.get().length() * sizeof(wchar_t));

				auto value = _value.get();

				polyc::algo(const_cast<wchar_t*>(_value.open_data_ptr()), _value.get().length() * sizeof(wchar_t));

				_value.close_data_ptr();

				return value;
			}

			__compelled_inline bool __stackcall set(imut std::wstring value) noexcept {

				*_value.open_wstr_ptr() = value;

				return polyc::algo(const_cast<wchar_t*>(_value.open_data_ptr()), _value.get().length() * sizeof(wchar_t));

				return _value.close_data_ptr();
			}


			__compelled_inline imut void* __stackcall open_data_ptr() noexcept {
				return _value.open_data_ptr();
			}

			__compelled_inline imut void* __stackcall get_raw_memory_address() imut noexcept {
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

				mut size_t index;

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

			__compelled_inline __regcall qeh_malloc( imut std::size_t size ) noexcept : allocation(size) {
				if (!size)
					return;

				if (!is_init)
					init_qtype_hash();

				if (!allocation.open_data_ptr())
					return;

			}

#pragma endregion

#pragma region Get Accessors

			__compelled_inline imut bool __regcall get(imut std::uintptr_t source_position, void* destination, imut std::size_t length) imut noexcept {

				if (!destination || !length)
					return false;

				polyc::algo(const_cast<void*>(allocation.open_data_ptr()), allocation.length(), false);

				memcpy(destination, (void*)(reinterpret_cast<std::uintptr_t>(allocation.open_data_ptr()) + source_position), length);

				polyc::algo(const_cast<void*>(allocation.open_data_ptr()), allocation.length(), false);

				allocation.close_data_ptr();

				return true;
			}

			__compelled_inline void* __regcall get( imut std::uintptr_t position, imut std::uintptr_t length ) noexcept {

				if (!length)
					return nullptr;

				auto* result = malloc(length);

				if (!result)
					return nullptr;

				get(position, result, length);
			}

			__compelled_inline std::uint8_t __regcall get( imut std::uintptr_t position ) imut noexcept {

				std::uint8_t _return = NULL;

				get(position, &_return, sizeof(_return));

				return _return;
			}

			__compelled_inline void* __regcall get() imut noexcept {

				auto* result = malloc( allocation.length() );

				if (!result)
					return nullptr;

				if (!get(0, result, allocation.length()))
					return nullptr;

				return result;
			}

			__compelled_inline imut void* __stackcall get_raw_memory_address() imut noexcept {
				return allocation.get_raw_memory_address();
			}

#pragma endregion

#pragma region Set Accessors

			__compelled_inline imut bool __regcall set( imut std::uintptr_t position, void* data, imut std::size_t length) noexcept {

				if (!data || !length)
					return false;

				polyc::algo(const_cast<void*>(allocation.open_data_ptr()), allocation.length(), false);

				memcpy((void*)(reinterpret_cast<std::uintptr_t>(allocation.open_data_ptr()) + position), data, length);

				polyc::algo(const_cast<void*>(allocation.open_data_ptr()), allocation.length(), false);

				allocation.close_data_ptr();

				return true;
			}

			template<typename T>
			__compelled_inline void __regcall set( imut std::uintptr_t position, T value ) noexcept {
				set(position, &value, sizeof(decltype(value)));
			}

#pragma endregion

#pragma region Utility functions

			__compelled_inline void __regcall reallocate( imut std::size_t size ) noexcept {

				allocation.reallocate(size);
			}

			__compelled_inline imut bool __regcall swap(void* allocation_, imut std::size_t size, imut bool free_source = false) noexcept {
				if (!size)
					return false;

				void* enc_alloc = malloc(size);

				if (!enc_alloc)
					return false;

				memcpy(enc_alloc, allocation_, size);

				algo(enc_alloc, size, false);

				if (free_source)
					free(allocation_);

				allocation.swap(enc_alloc, size);

				return true;
			}

			__compelled_inline imut void* open_data_ptr() noexcept {

				return allocation.open_data_ptr();
			}

#pragma endregion

#pragma region Operators

			__compelled_inline index_proxy __regcall operator[]( imut std::size_t index ) noexcept {
				return index_proxy(index, *this);
			}

#pragma endregion

#pragma region Destructor

			__compelled_inline ~qeh_malloc() noexcept {
				
				polyc::unregister_polyc_pointer( (imut c_void)allocation.open_data_ptr() );
			}

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