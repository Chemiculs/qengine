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

#pragma region Namespacing

namespace qengine {

	namespace qtype_enchash {

#pragma endregion

#pragma region Singleton 

		extern bool is_init;

#pragma endregion

#pragma region Static Methods

		__compelled_inline void __stackcall init_qtype_hash(qcallback::qmem_exception_rogue_c callback = qtype_hash::violation_callback_d) nex {

			if (is_init || qtype_hash::is_init)
				return;

			qtype_hash::init_hash_t(callback);

			is_init = true;
		}

#pragma endregion

#pragma region Types

#pragma region Template / User Defined

template<typename T>
class qeh_struct {

		private:

#pragma region Encrypted value

			qtype_hash::qh_struct<T> _value;

#pragma endregion

		public:

#pragma region Ctor / Dtor

			__optimized_ctor qeh_struct(imut T value = T{}) nex {

				if (!is_init)
					init_qtype_hash();

				set(value);
			}

			__compelled_inline __stackcall ~qeh_struct() nex {

				// Dtor for qh_xxx will inline RtlZeroMemory() macro
				polyc::unregister_polyc_pointer(_value.open_data_ptr());
			}

#pragma endregion

#pragma region Accessors

			__compelled_inline imut T __stackcall get() imut nex {

				// Invoke get() accessor to memcmp checksums, as checksums are for ciphertext, this must happen before open_data_ptr() is called
				auto value = _value.get();

				qengine::polyc::algo(_value.open_data_ptr(), sizeof(T));

				value = *_value.open_data_ptr();

				qengine::polyc::algo(_value.open_data_ptr(), sizeof(T));

				_value.close_data_ptr();

				return value;
			}

			template<typename _T>
			__compelled_inline imut _T __regcall get(imut _T T::* member) imut nex {

				imut auto decrypted = get();

				return decrypted.*member;
			}

			__compelled_inline imut bool __regcall set(imut T value) nex {
				
				*_value.open_data_ptr() = value;

				qengine::polyc::algo(_value.open_data_ptr(), sizeof(T));

				return _value.close_data_ptr();
			}

			template<typename _T>
			__compelled_inline imut bool __regcall set(_T T::* member, imut _T value) nex{

				auto decrypted = get();

				decrypted.*member = value;

				return set( std::move(decrypted) );
			}

			__compelled_inline imut c_void __stackcall open_data_ptr() imut nex {
				return _value.open_data_ptr();
			}

			__compelled_inline imut c_void __stackcall get_raw_memory_address() imut nex {
				return imut_cast<T*>(_value.get_raw_memory_address());
			}

#pragma endregion

#pragma region Operators

			__compelled_inline qeh_struct<T>& __regcall operator=(imut T value) nex {
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

class qeh_bool {

		private:

#pragma region Encrypted value

			qtype_hash::qh_bool _value;

#pragma endregion

		public:

#pragma region Ctor / Dtor

			__optimized_ctor qeh_bool(imut bool value = false) nex  {

				if (!is_init)
					init_qtype_hash();

				set(value);
			}

			__compelled_inline __stackcall ~qeh_bool() nex {

				polyc::unregister_polyc_pointer(_value.open_data_ptr());
			}

#pragma endregion

#pragma region Accessors

			__compelled_inline bool __stackcall get() imut nex {

				// Invoke get() accessor to memcmp checksums, as checksums are for ciphertext, this must happen before open_data_ptr() is called
				auto value = _value.get();

				qengine::polyc::algo(_value.open_data_ptr(), sizeof(bool));

				value = *_value.open_data_ptr();

				qengine::polyc::algo(_value.open_data_ptr(), sizeof(bool));

				_value.close_data_ptr();

				return value;
			}

			__compelled_inline bool __regcall set(imut bool value) nex {
				
				*_value.open_data_ptr() = value;

				qengine::polyc::algo(_value.open_data_ptr(), sizeof(bool));

				return _value.close_data_ptr();
			}

			__compelled_inline imut c_void __stackcall open_data_ptr() imut nex {
				return _value.open_data_ptr();
			}

			__compelled_inline imut c_void __stackcall get_raw_memory_address() imut nex {
				return imut_cast<bool*>(_value.get_raw_memory_address());
			}

#pragma endregion

#pragma region Operators

			__compelled_inline qeh_bool& __regcall operator=(imut bool value) nex {
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

		class qeh_int8 {

		private:

#pragma region Encrypted value

			qtype_hash::qh_int8 _value;

#pragma endregion

		public:

#pragma region Ctor / Dtor

			__optimized_ctor qeh_int8(imut std::int8_t value = 0) nex  {

				if (!is_init)
					init_qtype_hash();

				set(value);
			}

			__compelled_inline __stackcall ~qeh_int8() nex {
				polyc::unregister_polyc_pointer(_value.open_data_ptr());
			}

#pragma endregion

#pragma region Accessors

			__compelled_inline std::int8_t __stackcall get() imut nex {

				// Invoke get() accessor to memcmp checksums, as checksums are for ciphertext, this must happen before open_data_ptr() is called
				auto value = _value.get();

				qengine::polyc::algo(_value.open_data_ptr(), sizeof(std::int8_t));

				value = *_value.open_data_ptr();

				qengine::polyc::algo(_value.open_data_ptr(), sizeof(std::int8_t));

				_value.close_data_ptr();

				return value;
			}

			__compelled_inline bool __regcall set(imut std::int8_t value) nex {
				
				*_value.open_data_ptr() = value;

				qengine::polyc::algo(_value.open_data_ptr(), sizeof(std::int8_t));

				return _value.close_data_ptr();
			}

			__compelled_inline imut c_void __stackcall open_data_ptr() imut nex {
				return _value.open_data_ptr();
			}

			__compelled_inline imut c_void __stackcall get_raw_memory_address() imut nex {
				return imut_cast<std::int8_t*>(_value.get_raw_memory_address());
			}

#pragma endregion

#pragma region Operators

			__compelled_inline qeh_int8 __regcall operator+(imut std::int8_t value) imut nex {
				return qeh_int8(get() + value);
			};

			__compelled_inline qeh_int8 __regcall operator-(imut std::int8_t value) imut nex {
				return qeh_int8(get() - value);
			}

			__compelled_inline qeh_int8 __regcall operator/(imut std::int8_t value) imut nex {
				return qeh_int8(get() / value);
			}

			__compelled_inline qeh_int8 __regcall operator*(imut std::int8_t value) imut nex {
				return qeh_int8(get() * value);
			}

			__compelled_inline qeh_int8 __regcall operator&(imut std::int8_t value) imut nex {
				return qeh_int8(get() & value);
			}

			__compelled_inline qeh_int8 __regcall operator|(imut std::int8_t value) imut nex {
				return qeh_int8(get() | value);
			}

			__compelled_inline qeh_int8 __regcall operator%(imut std::int8_t value) imut nex {
				return qeh_int8(get() % value);
			}

			__compelled_inline qeh_int8 __regcall operator^(imut std::int8_t value) imut nex {
				return qeh_int8(get() ^ value);
			}

			__compelled_inline qeh_int8 __regcall operator<<(imut std::int8_t value) imut nex {
				return qeh_int8(get() << value);
			}

			__compelled_inline qeh_int8 __regcall operator>>(imut std::int8_t value) imut nex {
				return qeh_int8(get() >> value);
			}

			__compelled_inline qeh_int8& __regcall operator+=(imut std::int8_t value) nex {
				set(get() + value);
				return *this;
			}

			__compelled_inline qeh_int8& __regcall operator-=(imut std::int8_t value) nex {
				set(get() - value);
				return *this;
			}

			__compelled_inline qeh_int8& __stackcall operator++() nex {
				operator+=(1i8);
				return *this;
			}

			__compelled_inline qeh_int8& __stackcall operator--() nex {
				operator-=(1i8);
				return *this;
			}

			__compelled_inline qeh_int8& __regcall operator*=(imut std::int8_t value) nex {
				set(get() * value);
				return *this;
			}

			__compelled_inline qeh_int8& __regcall operator/=(imut std::int8_t value) nex {
				set(get() / value);
				return *this;
			}

			__compelled_inline qeh_int8& __regcall operator%=(imut std::int8_t value) nex {
				set(get() % value);
				return *this;
			}

			__compelled_inline qeh_int8& __regcall operator^=(imut std::int8_t value) nex {
				set(get() ^ value);
				return *this;
			}

			__compelled_inline qeh_int8& __regcall operator&=(imut std::int8_t value) nex {
				set(get() & value);
				return *this;
			}

			__compelled_inline qeh_int8& __regcall operator|=(imut std::int8_t value) nex {
				set(get() | value);
				return *this;
			}

			__compelled_inline qeh_int8& __regcall operator<<=(imut std::int8_t value) nex {
				set(get() << value);
				return *this;
			}

			__compelled_inline qeh_int8& __regcall operator>>=(imut std::int8_t value) nex {
				set(get() >> value);
				return *this;
			}

			__compelled_inline qeh_int8& __regcall operator=(imut std::int8_t value) nex {
				set(value);
				return *this;
			}

			__compelled_inline __stackcall operator std::int8_t() imut nex {
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

			__compelled_inline __regcall qeh_uint8(imut std::uint8_t value = 0) nex  {

				if (!is_init)
					init_qtype_hash();

				set(value);
			}

			__optimized_dtor ~qeh_uint8() nex {
				polyc::unregister_polyc_pointer(_value.open_data_ptr());
			}

#pragma endregion

#pragma region Accessors

			__compelled_inline std::uint8_t __stackcall get() imut nex {

				// Invoke get() accessor to memcmp checksums, as checksums are for ciphertext, this must happen before open_data_ptr() is called
				auto value = _value.get();

				qengine::polyc::algo(_value.open_data_ptr(), sizeof(std::uint8_t));

				value = *_value.open_data_ptr();

				qengine::polyc::algo(_value.open_data_ptr(), sizeof(std::uint8_t));

				_value.close_data_ptr();

				return value;
			}

			__compelled_inline bool __regcall set(imut std::uint8_t value) nex {

				*_value.open_data_ptr() = value;

				qengine::polyc::algo(_value.open_data_ptr(), sizeof(std::uint8_t));

				return _value.close_data_ptr();
			}

			__compelled_inline imut c_void __stackcall open_data_ptr() imut nex {
				return _value.open_data_ptr();
			}

			__compelled_inline imut c_void __stackcall get_raw_memory_address() imut nex {
				return imut_cast<std::uint8_t*>(_value.get_raw_memory_address());
			}

#pragma endregion

#pragma region Operators

			__compelled_inline qeh_uint8 __regcall operator+(imut std::uint8_t value) imut nex {
				return qeh_uint8(get() + value);
			};

			__compelled_inline qeh_uint8 __regcall operator-(imut std::uint8_t value) imut nex {
				return qeh_uint8(get() - value);
			}

			__compelled_inline qeh_uint8 __regcall operator/(imut std::uint8_t value) imut nex {
				return qeh_uint8(get() / value);
			}

			__compelled_inline qeh_uint8 __regcall operator*(imut std::uint8_t value) imut nex {
				return qeh_uint8(get() * value);
			}

			__compelled_inline qeh_uint8 __regcall operator&(imut std::uint8_t value) imut nex {
				return qeh_uint8(get() & value);
			}

			__compelled_inline qeh_uint8 __regcall operator|(imut std::uint8_t value) imut nex {
				return qeh_uint8(get() | value);
			}

			__compelled_inline qeh_uint8 __regcall operator%(imut std::uint8_t value) imut nex {
				return qeh_uint8(get() % value);
			}

			__compelled_inline qeh_uint8 __regcall operator^(imut std::uint8_t value) imut nex {
				return qeh_uint8(get() ^ value);
			}

			__compelled_inline qeh_uint8 __regcall operator<<(imut std::uint8_t value) imut nex {
				return qeh_uint8(get() << value);
			}

			__compelled_inline qeh_uint8 __regcall operator>>(imut std::uint8_t value) imut nex {
				return qeh_uint8(get() >> value);
			}

			__compelled_inline qeh_uint8& __regcall operator+=(imut std::uint8_t value) nex {
				set(get() + value);
				return *this;
			}

			__compelled_inline qeh_uint8& __regcall operator-=(imut std::uint8_t value) nex {
				set(get() - value);
				return *this;
			}

			__compelled_inline qeh_uint8& __stackcall operator++() nex {
				operator+=(1i8);
				return *this;
			}

			__compelled_inline qeh_uint8& __stackcall operator--() nex {
				operator-=(1i8);
				return *this;
			}

			__compelled_inline qeh_uint8& __regcall operator*=(imut std::uint8_t value) nex {
				set(get() * value);
				return *this;
			}

			__compelled_inline qeh_uint8& __regcall operator/=(imut std::uint8_t value) nex {
				set(get() / value);
				return *this;
			}

			__compelled_inline qeh_uint8& __regcall operator%=(imut std::uint8_t value) nex {
				set(get() % value);
				return *this;
			}

			__compelled_inline qeh_uint8& __regcall operator^=(imut std::uint8_t value) nex {
				set(get() ^ value);
				return *this;
			}

			__compelled_inline qeh_uint8& __regcall operator&=(imut std::uint8_t value) nex {
				set(get() & value);
				return *this;
			}

			__compelled_inline qeh_uint8& __regcall operator|=(imut std::uint8_t value) nex {
				set(get() | value);
				return *this;
			}

			__compelled_inline qeh_uint8& __regcall operator<<=(imut std::uint8_t value) nex {
				set(get() << value);
				return *this;
			}

			__compelled_inline qeh_uint8& __regcall operator>>=(imut std::uint8_t value) nex {
				set(get() >> value);
				return *this;
			}

			__compelled_inline qeh_uint8& __regcall operator=(imut std::uint8_t value) nex {
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

		class qeh_int16 {

		private:

#pragma region Encrypted value

			qtype_hash::qh_int16 _value;

#pragma endregion

		public:

#pragma region Ctor / Dtor

			__optimized_ctor qeh_int16(imut std::int16_t value = 0) nex  {

				if (!is_init)
					init_qtype_hash();

				set(value);
			}

			__optimized_dtor ~qeh_int16() nex {
				polyc::unregister_polyc_pointer(_value.open_data_ptr());
			}

#pragma endregion

#pragma region Accessors

			__compelled_inline std::int16_t __stackcall get() imut nex {

				// Invoke get() accessor to memcmp checksums, as checksums are for ciphertext, this must happen before open_data_ptr() is called
				auto value = _value.get();

				qengine::polyc::algo(_value.open_data_ptr(), sizeof(std::int16_t));

				value = *_value.open_data_ptr();

				qengine::polyc::algo(_value.open_data_ptr(), sizeof(std::int16_t));

				_value.close_data_ptr();

				return value;
			}

			__compelled_inline bool __regcall set(imut std::int16_t value) nex {

				*_value.open_data_ptr() = value;

				qengine::polyc::algo(_value.open_data_ptr(), sizeof(std::int16_t));

				return _value.close_data_ptr();
			}

			__compelled_inline imut c_void __stackcall open_data_ptr() imut nex {
				return _value.open_data_ptr();
			}

			__compelled_inline imut c_void __stackcall get_raw_memory_address() imut nex {
				return imut_cast<std::int16_t*>(_value.get_raw_memory_address());
			}

#pragma endregion

#pragma region Operators

			__compelled_inline qeh_int16 __regcall operator+(imut std::int16_t value) imut nex {
				return qeh_int16(get() + value);
			};

			__compelled_inline qeh_int16 __regcall operator-(imut std::int16_t value) imut nex {
				return qeh_int16(get() - value);
			}

			__compelled_inline qeh_int16 __regcall operator/(imut std::int16_t value) imut nex {
				return qeh_int16(get() / value);
			}

			__compelled_inline qeh_int16 __regcall operator*(imut std::int16_t value) imut nex {
				return qeh_int16(get() * value);
			}

			__compelled_inline qeh_int16 __regcall operator&(imut std::int16_t value) imut nex {
				return qeh_int16(get() & value);
			}

			__compelled_inline qeh_int16 __regcall operator|(imut std::int16_t value) imut nex {
				return qeh_int16(get() | value);
			}

			__compelled_inline qeh_int16 __regcall operator%(imut std::int16_t value) imut nex {
				return qeh_int16(get() % value);
			}

			__compelled_inline qeh_int16 __regcall operator^(imut std::int16_t value) imut nex {
				return qeh_int16(get() ^ value);
			}

			__compelled_inline qeh_int16 __regcall operator<<(imut std::int16_t value) imut nex {
				return qeh_int16(get() << value);
			}

			__compelled_inline qeh_int16 __regcall operator>>(imut std::int16_t value) imut nex {
				return qeh_int16(get() >> value);
			}

			__compelled_inline qeh_int16& __regcall operator+=(imut std::int16_t value) nex {
				set(get() + value);
				return *this;
			}

			__compelled_inline qeh_int16& __regcall operator-=(imut std::int16_t value) nex {
				set(get() - value);
				return *this;
			}

			__compelled_inline qeh_int16& __stackcall operator++() nex {
				operator+=(1i8);
				return *this;
			}

			__compelled_inline qeh_int16& __stackcall operator--() nex {
				operator-=(1i8);
				return *this;
			}

			__compelled_inline qeh_int16& __regcall operator*=(imut std::int16_t value) nex {
				set(get() * value);
				return *this;
			}

			__compelled_inline qeh_int16& __regcall operator/=(imut std::int16_t value) nex {
				set(get() / value);
				return *this;
			}

			__compelled_inline qeh_int16& __regcall operator%=(imut std::int16_t value) nex {
				set(get() % value);
				return *this;
			}

			__compelled_inline qeh_int16& __regcall operator^=(imut std::int16_t value) nex {
				set(get() ^ value);
				return *this;
			}

			__compelled_inline qeh_int16& __regcall operator&=(imut std::int16_t value) nex {
				set(get() & value);
				return *this;
			}

			__compelled_inline qeh_int16& __regcall operator|=(imut std::int16_t value) nex {
				set(get() | value);
				return *this;
			}

			__compelled_inline qeh_int16& __regcall operator<<=(imut std::int16_t value) nex {
				set(get() << value);
				return *this;
			}

			__compelled_inline qeh_int16& __regcall operator>>=(imut std::int16_t value) nex {
				set(get() >> value);
				return *this;
			}

			__compelled_inline qeh_int16& __regcall operator=(imut std::int16_t value) nex {
				set(value);
				return *this;
			}

			__compelled_inline __stackcall operator std::int16_t() imut nex {
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

			__compelled_inline __regcall qeh_uint16(imut std::uint16_t value = 0) nex  {

				if (!is_init)
					init_qtype_hash();

				set(value);
			}
			__optimized_dtor ~qeh_uint16() nex {

				polyc::unregister_polyc_pointer(_value.open_data_ptr());
			}

#pragma endregion

#pragma region Accessors

			__compelled_inline std::uint16_t __stackcall get() imut nex {

				// Invoke get() accessor to memcmp checksums, as checksums are for ciphertext, this must happen before open_data_ptr() is called
				auto value = _value.get();

				qengine::polyc::algo(_value.open_data_ptr(), sizeof(std::uint16_t));

				value = *_value.open_data_ptr();

				qengine::polyc::algo(_value.open_data_ptr(), sizeof(std::uint16_t));

				_value.close_data_ptr();

				return value;
			}

			__compelled_inline bool __regcall set(imut std::uint16_t value) nex {

				*_value.open_data_ptr() = value;

				qengine::polyc::algo(_value.open_data_ptr(), sizeof(std::uint16_t));

				return _value.close_data_ptr();
			}

			__compelled_inline imut c_void __stackcall open_data_ptr() imut nex {
				return _value.open_data_ptr();
			}

			__compelled_inline imut c_void __stackcall get_raw_memory_address() imut nex {
				return imut_cast<std::uint16_t*>(_value.get_raw_memory_address());
			}

#pragma endregion

#pragma region Operators

			__compelled_inline qeh_uint16 __regcall operator+(imut std::uint16_t value) imut nex {
				return qeh_uint16(get() + value);
			};

			__compelled_inline qeh_uint16 __regcall operator-(imut std::uint16_t value) imut nex {
				return qeh_uint16(get() - value);
			}

			__compelled_inline qeh_uint16 __regcall operator/(imut std::uint16_t value) imut nex {
				return qeh_uint16(get() / value);
			}

			__compelled_inline qeh_uint16 __regcall operator*(imut std::uint16_t value) imut nex {
				return qeh_uint16(get() * value);
			}

			__compelled_inline qeh_uint16 __regcall operator&(imut std::uint16_t value) imut nex {
				return qeh_uint16(get() & value);
			}

			__compelled_inline qeh_uint16 __regcall operator|(imut std::uint16_t value) imut nex {
				return qeh_uint16(get() | value);
			}

			__compelled_inline qeh_uint16 __regcall operator%(imut std::uint16_t value) imut nex {
				return qeh_uint16(get() % value);
			}

			__compelled_inline qeh_uint16 __regcall operator^(imut std::uint16_t value) imut nex {
				return qeh_uint16(get() ^ value);
			}

			__compelled_inline qeh_uint16 __regcall operator<<(imut std::uint16_t value) imut nex {
				return qeh_uint16(get() << value);
			}

			__compelled_inline qeh_uint16 __regcall operator>>(imut std::uint16_t value) imut nex {
				return qeh_uint16(get() >> value);
			}

			__compelled_inline qeh_uint16& __regcall operator+=(imut std::uint16_t value) nex {
				set(get() + value);
				return *this;
			}

			__compelled_inline qeh_uint16& __regcall operator-=(imut std::uint16_t value) nex {
				set(get() - value);
				return *this;
			}

			__compelled_inline qeh_uint16& __stackcall operator++() nex {
				operator+=(1i8);
				return *this;
			}

			__compelled_inline qeh_uint16& __stackcall operator--() nex {
				operator-=(1i8);
				return *this;
			}

			__compelled_inline qeh_uint16& __regcall operator*=(imut std::uint16_t value) nex {
				set(get() * value);
				return *this;
			}

			__compelled_inline qeh_uint16& __regcall operator/=(imut std::uint16_t value) nex {
				set(get() / value);
				return *this;
			}

			__compelled_inline qeh_uint16& __regcall operator%=(imut std::uint16_t value) nex {
				set(get() % value);
				return *this;
			}

			__compelled_inline qeh_uint16& __regcall operator^=(imut std::uint16_t value) nex {
				set(get() ^ value);
				return *this;
			}

			__compelled_inline qeh_uint16& __regcall operator&=(imut std::uint16_t value) nex {
				set(get() & value);
				return *this;
			}

			__compelled_inline qeh_uint16& __regcall operator|=(imut std::uint16_t value) nex {
				set(get() | value);
				return *this;
			}

			__compelled_inline qeh_uint16& __regcall operator<<=(imut std::uint16_t value) nex {
				set(get() << value);
				return *this;
			}

			__compelled_inline qeh_uint16& __regcall operator>>=(imut std::uint16_t value) nex {
				set(get() >> value);
				return *this;
			}

			__compelled_inline qeh_uint16& __regcall operator=(imut std::uint16_t value) nex {
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

		class qeh_int32 {

		private:

#pragma region Encrypted value

			qtype_hash::qh_int32 _value;

#pragma endregion

		public:

#pragma region Ctor / Dtor

			__compelled_inline __regcall qeh_int32(imut std::int32_t value = 0) nex {

				if (!is_init)
					init_qtype_hash();

				set(value);
			}
			__optimized_dtor ~qeh_int32() nex {
				polyc::unregister_polyc_pointer(_value.open_data_ptr());
			}

#pragma endregion

#pragma region Accessors

			__singleton std::int32_t __stackcall get() imut nex {

				// Invoke get() accessor to memcmp checksums, as checksums are for ciphertext, this must happen before open_data_ptr() is called
				auto value = _value.get();
				
				qengine::polyc::algo(_value.open_data_ptr(), sizeof(std::int32_t));

				value = *_value.open_data_ptr();

				qengine::polyc::algo(_value.open_data_ptr(), sizeof(std::int32_t));

				_value.close_data_ptr();

				return value;
			}

			__compelled_inline imut bool __regcall set(imut std::int32_t value) nex {

				*_value.open_data_ptr() = value;

				qengine::polyc::algo(_value.open_data_ptr(), sizeof(std::int32_t));

				return _value.close_data_ptr();
			}

			__compelled_inline imut c_void __stackcall open_data_ptr() imut nex {
				return _value.open_data_ptr();
			}

			__compelled_inline imut c_void __stackcall get_raw_memory_address() imut nex {
				return imut_cast<std::int32_t*>(_value.get_raw_memory_address());
			}

#pragma endregion

#pragma region Operators

			__compelled_inline qeh_int32 __regcall operator+(imut std::int32_t value) imut nex {
				return qeh_int32(get() + value);
			};

			__compelled_inline qeh_int32 __regcall operator-(imut std::int32_t value) imut nex {
				return qeh_int32(get() - value);
			}

			__compelled_inline qeh_int32 __regcall operator/(imut std::int32_t value) imut nex {
				return qeh_int32(get() / value);
			}

			__compelled_inline qeh_int32 __regcall operator*(imut std::int32_t value) imut nex {
				return qeh_int32(get() * value);
			}

			__compelled_inline qeh_int32 __regcall operator&(imut std::int32_t value) imut nex {
				return qeh_int32(get() & value);
			}

			__compelled_inline qeh_int32 __regcall operator|(imut std::int32_t value) imut nex {
				return qeh_int32(get() | value);
			}

			__compelled_inline qeh_int32 __regcall operator%(imut std::int32_t value) imut nex {
				return qeh_int32(get() % value);
			}

			__compelled_inline qeh_int32 __regcall operator^(imut std::int32_t value) imut nex {
				return qeh_int32(get() ^ value);
			}

			__compelled_inline qeh_int32 __regcall operator<<(imut std::int32_t value) imut nex {
				return qeh_int32(get() << value);
			}

			__compelled_inline qeh_int32 __regcall operator>>(imut std::int32_t value) imut nex {
				return qeh_int32(get() >> value);
			}

			__compelled_inline qeh_int32& __regcall operator+=(imut std::int32_t value) nex {
				set(get() + value);
				return *this;
			}

			__compelled_inline qeh_int32& __regcall operator-=(imut std::int32_t value) nex {
				set(get() - value);
				return *this;
			}

			__compelled_inline qeh_int32& __stackcall operator++() nex {
				operator+=(1i8);
				return *this;
			}

			__compelled_inline qeh_int32& __stackcall operator--() nex {
				operator-=(1i8);
				return *this;
			}

			__compelled_inline qeh_int32& __regcall operator*=(imut std::int32_t value) nex {
				set(get() * value);
				return *this;
			}

			__compelled_inline qeh_int32& __regcall operator/=(imut std::int32_t value) nex {
				set(get() / value);
				return *this;
			}

			__compelled_inline qeh_int32& __regcall operator%=(imut std::int32_t value) nex {
				set(get() % value);
				return *this;
			}

			__compelled_inline qeh_int32& __regcall operator^=(imut std::int32_t value) nex {
				set(get() ^ value);
				return *this;
			}

			__compelled_inline qeh_int32& __regcall operator&=(imut std::int32_t value) nex {
				set(get() & value);
				return *this;
			}

			__compelled_inline qeh_int32& __regcall operator|=(imut std::int32_t value) nex {
				set(get() | value);
				return *this;
			}

			__compelled_inline qeh_int32& __regcall operator<<=(imut std::int32_t value) nex {
				set(get() << value);
				return *this;
			}

			__compelled_inline qeh_int32& __regcall operator>>=(imut std::int32_t value) nex {
				set(get() >> value);
				return *this;
			}

			__compelled_inline qeh_int32& __regcall operator=(imut std::int32_t value) nex {
				set(value);
				return *this;
			}

			__compelled_inline __stackcall operator std::int32_t() imut nex {
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

			__compelled_inline __regcall qeh_uint32(imut std::uint32_t value = 0) nex  {

				if (!is_init)
					init_qtype_hash();

				set(value);
			}
			__optimized_dtor ~qeh_uint32() nex {
				polyc::unregister_polyc_pointer(_value.open_data_ptr());
			}

#pragma endregion

#pragma region Accessors

			__compelled_inline std::uint32_t __stackcall get() imut nex {

				// Invoke get() accessor to memcmp checksums, as checksums are for ciphertext, this must happen before open_data_ptr() is called
				auto value = _value.get();

				qengine::polyc::algo(_value.open_data_ptr(), sizeof(std::uint32_t));

				value = *_value.open_data_ptr();

				qengine::polyc::algo(_value.open_data_ptr(), sizeof(std::uint32_t));

				_value.close_data_ptr();

				return value;
			}

			__compelled_inline bool __regcall set(imut std::uint32_t value) nex {

				*_value.open_data_ptr() = value;

				qengine::polyc::algo(_value.open_data_ptr(), sizeof(std::uint32_t));

				return _value.close_data_ptr();
			}

			__compelled_inline imut c_void __stackcall open_data_ptr() imut nex {
				return _value.open_data_ptr();
			}

			__compelled_inline imut c_void __stackcall get_raw_memory_address() imut nex {
				return imut_cast<std::uint32_t*>(_value.get_raw_memory_address());
			}

#pragma endregion

#pragma region Operators

			__compelled_inline qeh_uint32 __regcall operator+(imut std::uint32_t value) imut nex {
				return qeh_uint32(get() + value);
			};

			__compelled_inline qeh_uint32 __regcall operator-(imut std::uint32_t value) imut nex {
				return qeh_uint32(get() - value);
			}

			__compelled_inline qeh_uint32 __regcall operator/(imut std::uint32_t value) imut nex {
				return qeh_uint32(get() / value);
			}

			__compelled_inline qeh_uint32 __regcall operator*(imut std::uint32_t value) imut nex {
				return qeh_uint32(get() * value);
			}

			__compelled_inline qeh_uint32 __regcall operator&(imut std::uint32_t value) imut nex {
				return qeh_uint32(get() & value);
			}

			__compelled_inline qeh_uint32 __regcall operator|(imut std::uint32_t value) imut nex {
				return qeh_uint32(get() | value);
			}

			__compelled_inline qeh_uint32 __regcall operator%(imut std::uint32_t value) imut nex {
				return qeh_uint32(get() % value);
			}

			__compelled_inline qeh_uint32 __regcall operator^(imut std::uint32_t value) imut nex {
				return qeh_uint32(get() ^ value);
			}

			__compelled_inline qeh_uint32 __regcall operator<<(imut std::uint32_t value) imut nex {
				return qeh_uint32(get() << value);
			}

			__compelled_inline qeh_uint32 __regcall operator>>(imut std::uint32_t value) imut nex {
				return qeh_uint32(get() >> value);
			}

			__compelled_inline qeh_uint32& __regcall operator+=(imut std::uint32_t value) nex {
				set(get() + value);
				return *this;
			}

			__compelled_inline qeh_uint32& __regcall operator-=(imut std::uint32_t value) nex {
				set(get() - value);
				return *this;
			}

			__compelled_inline qeh_uint32& __stackcall operator++() nex {
				operator+=(1i8);
				return *this;
			}

			__compelled_inline qeh_uint32& __stackcall operator--() nex {
				operator-=(1i8);
				return *this;
			}

			__compelled_inline qeh_uint32& __regcall operator*=(imut std::uint32_t value) nex {
				set(get() * value);
				return *this;
			}

			__compelled_inline qeh_uint32& __regcall operator/=(imut std::uint32_t value) nex {
				set(get() / value);
				return *this;
			}

			__compelled_inline qeh_uint32& __regcall operator%=(imut std::uint32_t value) nex {
				set(get() % value);
				return *this;
			}

			__compelled_inline qeh_uint32& __regcall operator^=(imut std::uint32_t value) nex {
				set(get() ^ value);
				return *this;
			}

			__compelled_inline qeh_uint32& __regcall operator&=(imut std::uint32_t value) nex {
				set(get() & value);
				return *this;
			}

			__compelled_inline qeh_uint32& __regcall operator|=(imut std::uint32_t value) nex {
				set(get() | value);
				return *this;
			}

			__compelled_inline qeh_uint32& __regcall operator<<=(imut std::uint32_t value) nex {
				set(get() << value);
				return *this;
			}

			__compelled_inline qeh_uint32& __regcall operator>>=(imut std::uint32_t value) nex {
				set(get() >> value);
				return *this;
			}

			__compelled_inline qeh_uint32& __regcall operator=(imut std::uint32_t value) nex {
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

		class qeh_int64 {

		private:

#pragma region Encrypted value

			qtype_hash::qh_int64 _value;

#pragma endregion

		public:

#pragma region Ctor / Dtor

			__compelled_inline __regcall qeh_int64(imut std::int64_t value = 0) nex  {

				if (!is_init)
					init_qtype_hash();

				set(value);
			}

			__optimized_dtor ~qeh_int64() nex {
				polyc::unregister_polyc_pointer(_value.open_data_ptr());
			}

#pragma endregion

#pragma region Accessors

			__compelled_inline std::int64_t __stackcall get() imut nex {

				// Invoke get() accessor to memcmp checksums, as checksums are for ciphertext, this must happen before open_data_ptr() is called
				auto value = _value.get();

				qengine::polyc::algo(_value.open_data_ptr(), sizeof(std::int64_t));

				value = *_value.open_data_ptr();

				qengine::polyc::algo(_value.open_data_ptr(), sizeof(std::int64_t));

				_value.close_data_ptr();

				return value;
			}

			__compelled_inline bool __regcall set(imut std::int64_t value) nex {

				*_value.open_data_ptr() = value;

				qengine::polyc::algo(_value.open_data_ptr(), sizeof(std::int64_t));

				return _value.close_data_ptr();
			}

			__compelled_inline imut c_void __stackcall open_data_ptr() imut nex {
				return _value.open_data_ptr();
			}

			__compelled_inline imut c_void __stackcall get_raw_memory_address() imut nex {
				return imut_cast<std::int64_t*>(_value.get_raw_memory_address());
			}

#pragma endregion

#pragma region Operators

			__compelled_inline qeh_int64 __regcall operator+(imut std::int64_t value) imut nex {
				return qeh_int64(get() + value);
			};

			__compelled_inline qeh_int64 __regcall operator-(imut std::int64_t value) imut nex {
				return qeh_int64(get() - value);
			}

			__compelled_inline qeh_int64 __regcall operator/(imut std::int64_t value) imut nex {
				return qeh_int64(get() / value);
			}

			__compelled_inline qeh_int64 __regcall operator*(imut std::int64_t value) imut nex {
				return qeh_int64(get() * value);
			}

			__compelled_inline qeh_int64 __regcall operator&(imut std::int64_t value) imut nex {
				return qeh_int64(get() & value);
			}

			__compelled_inline qeh_int64 __regcall operator|(imut std::int64_t value) imut nex {
				return qeh_int64(get() | value);
			}

			__compelled_inline qeh_int64 __regcall operator%(imut std::int64_t value) imut nex {
				return qeh_int64(get() % value);
			}

			__compelled_inline qeh_int64 __regcall operator^(imut std::int64_t value) imut nex {
				return qeh_int64(get() ^ value);
			}

			__compelled_inline qeh_int64 __regcall operator<<(imut std::int64_t value) imut nex {
				return qeh_int64(get() << value);
			}

			__compelled_inline qeh_int64 __regcall operator>>(imut std::int64_t value) imut nex {
				return qeh_int64(get() >> value);
			}

			__compelled_inline qeh_int64& __regcall operator+=(imut std::int64_t value) nex {
				set(get() + value);
				return *this;
			}

			__compelled_inline qeh_int64& __regcall operator-=(imut std::int64_t value) nex {
				set(get() - value);
				return *this;
			}

			__compelled_inline qeh_int64& __stackcall operator++() nex {
				operator+=(1i8);
				return *this;
			}

			__compelled_inline qeh_int64& __stackcall operator--() nex {
				operator-=(1i8);
				return *this;
			}

			__compelled_inline qeh_int64& __regcall operator*=(imut std::int64_t value) nex {
				set(get() * value);
				return *this;
			}

			__compelled_inline qeh_int64& __regcall operator/=(imut std::int64_t value) nex {
				set(get() / value);
				return *this;
			}

			__compelled_inline qeh_int64& __regcall operator%=(imut std::int64_t value) nex {
				set(get() % value);
				return *this;
			}

			__compelled_inline qeh_int64& __regcall operator^=(imut std::int64_t value) nex {
				set(get() ^ value);
				return *this;
			}

			__compelled_inline qeh_int64& __regcall operator&=(imut std::int64_t value) nex {
				set(get() & value);
				return *this;
			}

			__compelled_inline qeh_int64& __regcall operator|=(imut std::int64_t value) nex {
				set(get() | value);
				return *this;
			}

			__compelled_inline qeh_int64& __regcall operator<<=(imut std::int64_t value) nex {
				set(get() << value);
				return *this;
			}

			__compelled_inline qeh_int64& __regcall operator>>=(imut std::int64_t value) nex {
				set(get() >> value);
				return *this;
			}

			__compelled_inline qeh_int64& __regcall operator=(imut std::int64_t value) nex {
				set(value);
				return *this;
			}

			__compelled_inline __stackcall operator std::int64_t() imut nex {
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

			__compelled_inline __regcall qeh_uint64(imut std::uint64_t value = 0) nex  {

				if (!is_init)
					init_qtype_hash();

				set(value);
			}

			__optimized_dtor ~qeh_uint64() nex {
				polyc::unregister_polyc_pointer(_value.open_data_ptr());
			}

#pragma endregion

#pragma region Accessors

			__compelled_inline std::uint64_t __stackcall get() imut nex {

				// Invoke get() accessor to memcmp checksums, as checksums are for ciphertext, this must happen before open_data_ptr() is called
				auto value = _value.get();

				qengine::polyc::algo(_value.open_data_ptr(), sizeof(std::uint64_t));

				value = *_value.open_data_ptr();

				qengine::polyc::algo(_value.open_data_ptr(), sizeof(std::uint64_t));

				_value.close_data_ptr();

				return value;
			}

			__compelled_inline bool __regcall set(imut std::uint64_t value) nex {

				*_value.open_data_ptr() = value;

				qengine::polyc::algo(_value.open_data_ptr(), sizeof(std::uint64_t));

				return _value.close_data_ptr();
			}

			__compelled_inline imut c_void __stackcall open_data_ptr() imut nex {
				return _value.open_data_ptr();
			}

			__compelled_inline imut c_void __stackcall get_raw_memory_address() imut nex {
				return imut_cast<std::uint64_t*>(_value.get_raw_memory_address());
			}

#pragma endregion

#pragma region Operators

			__compelled_inline qeh_uint64 __regcall operator+(imut std::uint64_t value) imut nex {
				return qeh_uint64(get() + value);
			};

			__compelled_inline qeh_uint64 __regcall operator-(imut std::uint64_t value) imut nex {
				return qeh_uint64(get() - value);
			}

			__compelled_inline qeh_uint64 __regcall operator/(imut std::uint64_t value) imut nex {
				return qeh_uint64(get() / value);
			}

			__compelled_inline qeh_uint64 __regcall operator*(imut std::uint64_t value) imut nex {
				return qeh_uint64(get() * value);
			}

			__compelled_inline qeh_uint64 __regcall operator&(imut std::uint64_t value) imut nex {
				return qeh_uint64(get() & value);
			}

			__compelled_inline qeh_uint64 __regcall operator|(imut std::uint64_t value) imut nex {
				return qeh_uint64(get() | value);
			}

			__compelled_inline qeh_uint64 __regcall operator%(imut std::uint64_t value) imut nex {
				return qeh_uint64(get() % value);
			}

			__compelled_inline qeh_uint64 __regcall operator^(imut std::uint64_t value) imut nex {
				return qeh_uint64(get() ^ value);
			}

			__compelled_inline qeh_uint64 __regcall operator<<(imut std::uint64_t value) imut nex {
				return qeh_uint64(get() << value);
			}

			__compelled_inline qeh_uint64 __regcall operator>>(imut std::uint64_t value) imut nex {
				return qeh_uint64(get() >> value);
			}

			__compelled_inline qeh_uint64& __regcall operator+=(imut std::uint64_t value) nex {
				set(get() + value);
				return *this;
			}

			__compelled_inline qeh_uint64& __regcall operator-=(imut std::uint64_t value) nex {
				set(get() - value);
				return *this;
			}

			__compelled_inline qeh_uint64& __stackcall operator++() nex {
				operator+=(1i8);
				return *this;
			}

			__compelled_inline qeh_uint64& __stackcall operator--() nex {
				operator-=(1i8);
				return *this;
			}

			__compelled_inline qeh_uint64& __regcall operator*=(imut std::uint64_t value) nex {
				set(get() * value);
				return *this;
			}

			__compelled_inline qeh_uint64& __regcall operator/=(imut std::uint64_t value) nex {
				set(get() / value);
				return *this;
			}

			__compelled_inline qeh_uint64& __regcall operator%=(imut std::uint64_t value) nex {
				set(get() % value);
				return *this;
			}

			__compelled_inline qeh_uint64& __regcall operator^=(imut std::uint64_t value) nex {
				set(get() ^ value);
				return *this;
			}

			__compelled_inline qeh_uint64& __regcall operator&=(imut std::uint64_t value) nex {
				set(get() & value);
				return *this;
			}

			__compelled_inline qeh_uint64& __regcall operator|=(imut std::uint64_t value) nex {
				set(get() | value);
				return *this;
			}

			__compelled_inline qeh_uint64& __regcall operator<<=(imut std::uint64_t value) nex {
				set(get() << value);
				return *this;
			}

			__compelled_inline qeh_uint64& __regcall operator>>=(imut std::uint64_t value) nex {
				set(get() >> value);
				return *this;
			}

			__compelled_inline qeh_uint64& __regcall operator=(imut std::uint64_t value) nex {
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

		class qeh_float {

		private:

#pragma region Encrypted value

			qtype_hash::qh_float _value;

#pragma endregion

		public:

#pragma region Ctor / Dtor

			__compelled_inline __fpcall qeh_float(imut float value = 0.f) nex  {

				if (!is_init)
					init_qtype_hash();

				set(value);
			}
			__optimized_dtor ~qeh_float() nex {
				polyc::unregister_polyc_pointer(_value.open_data_ptr());
			}

#pragma endregion

#pragma region Accessors

			__compelled_inline float __stackcall get() imut nex {

				// Invoke get() accessor to memcmp checksums, as checksums are for ciphertext, this must happen before open_data_ptr() is called
				auto value = _value.get();

				qengine::polyc::algo(_value.open_data_ptr(), sizeof(float));

				value = *_value.open_data_ptr();

				qengine::polyc::algo(_value.open_data_ptr(), sizeof(float));

				_value.close_data_ptr();

				return value;
			}

			__compelled_inline bool __regcall set(imut float value) nex {

				*_value.open_data_ptr() = value;

				qengine::polyc::algo(_value.open_data_ptr(), sizeof(float));

				return _value.close_data_ptr();
			}

			__compelled_inline imut c_void __stackcall open_data_ptr() imut nex {
				return _value.open_data_ptr();
			}

			__compelled_inline imut c_void __stackcall get_raw_memory_address() imut nex {
				return imut_cast<float*>(_value.get_raw_memory_address());
			}

#pragma endregion

#pragma region Operators

			__compelled_inline qeh_float __regcall operator+(imut float value) imut nex {
				return qeh_float(get() + value);
			};

			__compelled_inline qeh_float __regcall operator-(imut float value) imut nex {
				return qeh_float(get() - value);
			}

			__compelled_inline qeh_float __regcall operator/(imut float value) imut nex {
				return qeh_float(get() / value);
			}

			__compelled_inline qeh_float __regcall operator*(imut float value) imut nex {
				return qeh_float(get() * value);
			}

			__compelled_inline qeh_float& __regcall operator+=(imut float value) nex {
				set(get() + value);
				return *this;
			}

			__compelled_inline qeh_float& __regcall operator-=(imut float value) nex {
				set(get() - value);
				return *this;
			}

			__compelled_inline qeh_float& __stackcall operator++() nex {
				operator+=(1i8);
				return *this;
			}

			__compelled_inline qeh_float& __stackcall operator--() nex {
				operator-=(1i8);
				return *this;
			}

			__compelled_inline qeh_float& __regcall operator*=(imut float value) nex {
				set(get() * value);
				return *this;
			}

			__compelled_inline qeh_float& __regcall operator/=(imut float value) nex {
				set(get() / value);
				return *this;
			}

			__compelled_inline qeh_float& __regcall operator=(imut float value) nex {
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

		class qeh_double {

		private:

#pragma region Encrypted value

			qtype_hash::qh_double _value;

#pragma endregion

		public:

#pragma region Ctor / Dtor

			__compelled_inline __fpcall qeh_double(double value = static_cast<double>(0.f)) nex  {

				if (!is_init)
					init_qtype_hash();

				set(value);
			}

			__optimized_dtor ~qeh_double() nex {
				polyc::unregister_polyc_pointer(_value.open_data_ptr());
			}

#pragma endregion

#pragma endregion

#pragma region Accessors

			__compelled_inline double __stackcall get() imut nex {

				// Invoke get() accessor to memcmp checksums, as checksums are for ciphertext, this must happen before open_data_ptr() is called
				auto value = _value.get();

				qengine::polyc::algo(_value.open_data_ptr(), sizeof(double));

				value = *_value.open_data_ptr();

				qengine::polyc::algo(_value.open_data_ptr(), sizeof(double));

				_value.close_data_ptr();

				return value;
			}

			__compelled_inline bool __regcall set(imut double value) nex {

				*_value.open_data_ptr() = value;

				qengine::polyc::algo(_value.open_data_ptr(), sizeof(double));

				return _value.close_data_ptr();
			}

			__compelled_inline imut c_void __stackcall open_data_ptr() imut nex {
				return _value.open_data_ptr();
			}

			__compelled_inline imut c_void __stackcall get_raw_memory_address() imut nex {
				return imut_cast<double*>(_value.get_raw_memory_address());
			}

#pragma endregion

#pragma region Operators

			__compelled_inline qeh_double __regcall operator+(imut double value) imut nex {
				return qeh_double(get() + value);
			};

			__compelled_inline qeh_double __regcall operator-(imut double value) imut nex {
				return qeh_double(get() - value);
			}

			__compelled_inline qeh_double __regcall operator/(imut double value) imut nex {
				return qeh_double(get() / value);
			}

			__compelled_inline qeh_double __regcall operator*(imut double value) imut nex {
				return qeh_double(get() * value);
			}

			__compelled_inline qeh_double& __regcall operator+=(imut double value) nex {
				set(get() + value);
				return *this;
			}

			__compelled_inline qeh_double& __regcall operator-=(imut double value) nex {
				set(get() - value);
				return *this;
			}

			__compelled_inline qeh_double& __stackcall operator++() nex {
				operator+=(1i8);
				return *this;
			}

			__compelled_inline qeh_double& __stackcall operator--() nex {
				operator-=(1i8);
				return *this;
			}

			__compelled_inline qeh_double& __regcall operator*=(imut double value) nex {
				set(get() * value);
				return *this;
			}

			__compelled_inline qeh_double& __regcall operator/=(imut double value) nex {
				set(get() / value);
				return *this;
			}

			__compelled_inline qeh_double& __regcall operator=(imut double value) nex {
				set(value);
				return *this;
			}

			__compelled_inline __stackcall operator double() imut nex {
				return get();
			}

#pragma endregion
		};

class qeh_longdouble {

		private:

#pragma region Encrypted value

			qtype_hash::qh_longdouble _value;

#pragma endregion

		public:

#pragma region Ctor / Dtor

			__compelled_inline __fpcall qeh_longdouble(long double value = static_cast<long double>(0.f)) nex  {

				if (!is_init)
					init_qtype_hash();

				set(value);
			}

			__optimized_dtor ~qeh_longdouble() nex {
				polyc::unregister_polyc_pointer(_value.open_data_ptr());
			}

#pragma endregion

#pragma endregion

#pragma region Accessors

			__compelled_inline long double __stackcall get() imut nex {

				// Invoke get() accessor to memcmp checksums, as checksums are for ciphertext, this must happen before open_data_ptr() is called
				auto value = _value.get();

				qengine::polyc::algo(_value.open_data_ptr(), sizeof(long double));

				value = *_value.open_data_ptr();

				qengine::polyc::algo(_value.open_data_ptr(), sizeof(long double));

				_value.close_data_ptr();

				return value;
			}

			__compelled_inline bool __regcall set(imut long double value) nex {

				*_value.open_data_ptr() = value;

				qengine::polyc::algo(_value.open_data_ptr(), sizeof(long double));

				return _value.close_data_ptr();
			}

			__compelled_inline imut c_void __stackcall open_data_ptr() imut nex {
				return _value.open_data_ptr();
			}

			__compelled_inline imut c_void __stackcall get_raw_memory_address() imut nex {
				return imut_cast<long double*>(_value.get_raw_memory_address());
			}

#pragma endregion

#pragma region Operators

			__compelled_inline qeh_longdouble __regcall operator+(imut long double value) imut nex {
				return qeh_longdouble(get() + value);
			};

			__compelled_inline qeh_longdouble __regcall operator-(imut long double value) imut nex {
				return qeh_longdouble(get() - value);
			}

			__compelled_inline qeh_longdouble __regcall operator/(imut long double value) imut nex {
				return qeh_longdouble(get() / value);
			}

			__compelled_inline qeh_longdouble __regcall operator*(imut long double value) imut nex {
				return qeh_longdouble(get() * value);
			}

			__compelled_inline qeh_longdouble& __regcall operator+=(imut long double value) nex {
				set(static_cast<double>(get() + value));
				return *this;
			}

			__compelled_inline qeh_longdouble& __regcall operator-=(imut long double value) nex {
				set(static_cast<double>(get() - value));
				return *this;
			}

			__compelled_inline qeh_longdouble& __stackcall operator++() nex {
				operator+=(1i8);
				return *this;
			}

			__compelled_inline qeh_longdouble& __stackcall operator--() nex {
				operator-=(1i8);
				return *this;
			}

			__compelled_inline qeh_longdouble& __regcall operator*=(imut long double value) nex {
				set(get() * value);
				return *this;
			}

			__compelled_inline qeh_longdouble& __regcall operator/=(imut long double value) nex {
				set(get() / value);
				return *this;
			}

			__compelled_inline qeh_longdouble& __regcall operator=(imut long double value) nex {
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

		class qeh_m128 {

		private:

#pragma region Globals

			qtype_hash::qh_m128 _value;

#pragma endregion

		public:

#pragma region Ctor / Dtor

			__compelled_inline __fpcall qeh_m128(imut __m128 value) nex  {

				if (!is_init)
					init_qtype_hash();

				set(value);
			}

			__optimized_dtor ~qeh_m128() nex {
				polyc::unregister_polyc_pointer(_value.open_data_ptr());
			}

#pragma endregion

#pragma region Accessors

			__compelled_inline __m128 __stackcall get() imut nex {

				// Invoke get() accessor to memcmp checksums, as checksums are for ciphertext, this must happen before open_data_ptr() is called
				auto value = _value.get();

				qengine::polyc::algo(_value.open_data_ptr(), sizeof(__m128));

				value = *_value.open_data_ptr();

				qengine::polyc::algo(_value.open_data_ptr(), sizeof(__m128));

				_value.close_data_ptr();

				return value;
			}

			__compelled_inline bool __regcall set(imut __m128 value) nex {

				*_value.open_data_ptr() = value;

				qengine::polyc::algo(_value.open_data_ptr(), sizeof(__m128));

				return _value.close_data_ptr();
			}

			__compelled_inline imut c_void __stackcall open_data_ptr() imut nex {
				return _value.open_data_ptr();
			}

			__compelled_inline imut c_void __stackcall get_raw_memory_address() imut nex {
				return imut_cast<__m128*>(_value.get_raw_memory_address());
			}

#pragma endregion

#pragma region Operators

	#ifdef __clang__

			__compelled_inline qeh_m128 __fpcall operator+(imut __m128 value) imut nex {
				return qeh_m128(get() + value);
			};

			__compelled_inline qeh_m128 __fpcall operator-(imut __m128 value) imut nex {
				return qeh_m128(get() - value);
			}

			__compelled_inline qeh_m128 __fpcall operator/(imut __m128 value) imut nex {
				return qeh_m128(get() / value);
			}

			__compelled_inline qeh_m128 __fpcall operator*(imut __m128 value) imut nex {
				return qeh_m128(get() * value);
			}

			__compelled_inline qeh_m128& __fpcall operator+=(imut __m128 value) nex {
				set(get() + value);
				return *this;
			}

			__compelled_inline qeh_m128& __fpcall operator-=(imut __m128 value) nex {
				set(get() - value);
				return *this;
			}

			__compelled_inline qeh_m128& __fpcall operator*=(imut __m128 value) nex {
				set(get() * value);
				return *this;
			}

			__compelled_inline qeh_m128& __fpcall operator/=(imut __m128 value) nex {
				set(get() / value);
				return *this;
			}

	#endif

			__compelled_inline qeh_m128& __fpcall operator=(imut __m128 value) nex {
				set(value);
				return *this;
			}

			__compelled_inline __stackcall operator __m128() imut nex {
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

			__compelled_inline __fpcall qeh_m128i(imut __m128i value) nex  {

				if (!is_init)
					init_qtype_hash();

				set(value);
			}

			__optimized_dtor ~qeh_m128i() nex {
				polyc::unregister_polyc_pointer(_value.open_data_ptr());
			}

#pragma endregion

#pragma region Accessors

			__compelled_inline __m128i __stackcall get() imut nex {

				// Invoke get() accessor to memcmp checksums, as checksums are for ciphertext, this must happen before open_data_ptr() is called
				auto value = _value.get();

				qengine::polyc::algo(_value.open_data_ptr(), sizeof(__m128i));

				value = *_value.open_data_ptr();

				qengine::polyc::algo(_value.open_data_ptr(), sizeof(__m128i));

				_value.close_data_ptr();

				return value;
			}

			__compelled_inline bool __regcall set(imut __m128i value) nex {

				*_value.open_data_ptr() = value;

				qengine::polyc::algo(_value.open_data_ptr(), sizeof(__m128i));

				return _value.close_data_ptr();
			}

			__compelled_inline imut c_void __stackcall open_data_ptr() imut nex {
				return _value.open_data_ptr();
			}

			__compelled_inline imut c_void __stackcall get_raw_memory_address() imut nex {
				return imut_cast<__m128i*>(_value.get_raw_memory_address());
			}

#pragma endregion

#pragma region Operators

#ifdef __clang__

			__compelled_inline qeh_m128i __fpcall operator+(imut __m128i value) imut nex {
				return qeh_m128i(get() + value);
			};

			__compelled_inline qeh_m128i __fpcall operator-(imut __m128i value) imut nex {
				return qeh_m128i(get() - value);
			}

			__compelled_inline qeh_m128i __fpcall operator/(imut __m128i value) imut nex {
				return qeh_m128i(get() / value);
			}

			__compelled_inline qeh_m128i __fpcall operator*(imut __m128i value) imut nex {
				return qeh_m128i(get() * value);
			}

			__compelled_inline qeh_m128i& __fpcall operator+=(imut __m128i value) nex {
				set(get() + value);
				return *this;
			}

			__compelled_inline qeh_m128i& __fpcall operator-=(imut __m128i value) nex {
				set(get() - value);
				return *this;
			}

			__compelled_inline qeh_m128i& __fpcall operator*=(imut __m128i value) nex {
				set(get() * value);
				return *this;
			}

			__compelled_inline qeh_m128i& __fpcall operator/=(imut __m128i value) nex {
				set(get() / value);
				return *this;
			}

#endif

			__compelled_inline qeh_m128i& __fpcall operator=(imut __m128i value) nex {
				set(value);
				return *this;
			}

			__compelled_inline __stackcall operator __m128i() imut nex {
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

			__compelled_inline __fpcall qeh_m128d(imut __m128d value) nex  {

				if (!is_init)
					init_qtype_hash();

				set(value);
			}
			__optimized_dtor ~qeh_m128d() nex {
				polyc::unregister_polyc_pointer(_value.open_data_ptr());
			}

#pragma endregion

#pragma region Accessors

			__compelled_inline __m128d __stackcall get() imut nex {

				// Invoke get() accessor to memcmp checksums, as checksums are for ciphertext, this must happen before open_data_ptr() is called
				auto value = _value.get();

				qengine::polyc::algo(_value.open_data_ptr(), sizeof(__m128d));

				value = *_value.open_data_ptr();

				qengine::polyc::algo(_value.open_data_ptr(), sizeof(__m128d));

				_value.close_data_ptr();

				return value;
			}

			__compelled_inline bool __regcall set(imut __m128d value) nex {

				*_value.open_data_ptr() = value;

				qengine::polyc::algo(_value.open_data_ptr(), sizeof(__m128d));

				return _value.close_data_ptr();
			}

			__compelled_inline imut c_void __stackcall open_data_ptr() imut nex {
				return _value.open_data_ptr();
			}

			__compelled_inline imut c_void __stackcall get_raw_memory_address() imut nex {
				return imut_cast<__m128d*>(_value.get_raw_memory_address());
			}

#pragma endregion

#pragma region Operators

#ifdef __clang__

			__compelled_inline qeh_m128d __fpcall operator+(imut __m128d value) imut nex {
				return qeh_m128d(get() + value);
			};

			__compelled_inline qeh_m128d __fpcall operator-(imut __m128d value) imut nex {
				return qeh_m128d(get() - value);
			}

			__compelled_inline qeh_m128d __fpcall operator/(imut __m128d value) imut nex {
				return qeh_m128d(get() / value);
			}

			__compelled_inline qeh_m128d __fpcall operator*(imut __m128d value) imut nex {
				return qeh_m128d(get() * value);
			}

			__compelled_inline qeh_m128d& __fpcall operator+=(imut __m128d value) nex {
				set(get() + value);
				return *this;
			}

			__compelled_inline qeh_m128d& __fpcall operator-=(imut __m128d value) nex {
				set(get() - value);
				return *this;
			}

			__compelled_inline qeh_m128d& __fpcall operator*=(imut __m128d value) nex {
				set(get() * value);
				return *this;
			}

			__compelled_inline qeh_m128d& __fpcall operator/=(imut __m128d value) nex {
				set(get() / value);
				return *this;
			}

#endif

			__compelled_inline qeh_m128d& __fpcall operator=(imut __m128d value) nex {
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

#pragma region AVX

	#ifdef __AVX__

		class qeh_m256 {

		private:

#pragma region Globals

			qtype_hash::qh_m256 _value;

#pragma endregion

		public:

#pragma region Ctor / Dtor

			__compelled_inline __fpcall qeh_m256(imut __m256 value) nex  {

				if (!is_init)
					init_qtype_hash();

				set(value);
			}

			__optimized_dtor ~qeh_m256() nex {
				polyc::unregister_polyc_pointer(_value.open_data_ptr());
			}

#pragma endregion

#pragma region Accessors

			__compelled_inline __m256 __stackcall get() imut nex {

				// Invoke get() accessor to memcmp checksums, as checksums are for ciphertext, this must happen before open_data_ptr() is called
				auto value = _value.get();

				qengine::polyc::algo(_value.open_data_ptr(), sizeof(__m256));

				value = *_value.open_data_ptr();

				qengine::polyc::algo(_value.open_data_ptr(), sizeof(__m256));

				_value.close_data_ptr();

				return value;
			}

			__compelled_inline bool __regcall set(imut __m256 value) nex {

				*_value.open_data_ptr() = value;

				qengine::polyc::algo(_value.open_data_ptr(), sizeof(__m256));

				return _value.close_data_ptr();
			}

			__compelled_inline imut c_void __stackcall open_data_ptr() imut nex {
				return _value.open_data_ptr();
			}

			__compelled_inline imut c_void __stackcall get_raw_memory_address() imut nex {
				return imut_cast<__m256*>(_value.get_raw_memory_address());
			}

#pragma endregion

#pragma region Operators

#ifdef __clang__

			__compelled_inline qeh_m256 __fpcall operator+(imut __m256 value) imut nex {
				return qeh_m256(get() + value);
			};

			__compelled_inline qeh_m256 __fpcall operator-(imut __m256 value) imut nex {
				return qeh_m256(get() - value);
			}

			__compelled_inline qeh_m256 __fpcall operator/(imut __m256 value) imut nex {
				return qeh_m256(get() / value);
			}

			__compelled_inline qeh_m256 __fpcall operator*(imut __m256 value) imut nex {
				return qeh_m256(get() * value);
			}

			__compelled_inline qeh_m256& __fpcall operator+=(imut __m256 value) nex {
				set(get() + value);
				return *this;
			}

			__compelled_inline qeh_m256& __fpcall operator-=(imut __m256 value) nex {
				set(get() - value);
				return *this;
			}

			__compelled_inline qeh_m256& __fpcall operator*=(imut __m256 value) nex {
				set(get() * value);
				return *this;
			}

			__compelled_inline qeh_m256& __fpcall operator/=(imut __m256 value) nex {
				set(get() / value);
				return *this;
			}

#endif

			__compelled_inline qeh_m256& __fpcall operator=(imut __m256 value) nex {
				set(value);
				return *this;
			}

			__compelled_inline __stackcall operator __m256() imut nex {
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

			__compelled_inline __fpcall qeh_m256i(imut __m256i value) nex  {

				if (!is_init)
					init_qtype_hash();

				set(value);
			}

			__optimized_dtor ~qeh_m256i() nex {
				polyc::unregister_polyc_pointer(_value.open_data_ptr());
			}

#pragma endregion

#pragma region Accessors

			__compelled_inline __m256i __stackcall get() imut nex {

				// Invoke get() accessor to memcmp checksums, as checksums are for ciphertext, this must happen before open_data_ptr() is called
				auto value = _value.get();

				qengine::polyc::algo(_value.open_data_ptr(), sizeof(__m256i));

				value = *_value.open_data_ptr();

				qengine::polyc::algo(_value.open_data_ptr(), sizeof(__m256i));

				_value.close_data_ptr();

				return value;
			}

			__compelled_inline bool __regcall set(imut __m256i value) nex {

				*_value.open_data_ptr() = value;

				qengine::polyc::algo(_value.open_data_ptr(), sizeof(__m256i));

				return _value.close_data_ptr();
			}

			__compelled_inline imut c_void __stackcall open_data_ptr() imut nex {
				return _value.open_data_ptr();
			}

			__compelled_inline imut c_void __stackcall get_raw_memory_address() imut nex {
				return imut_cast<__m256i*>(_value.get_raw_memory_address());
			}

#pragma endregion

#pragma region Operators

#ifdef __clang__

			__compelled_inline qeh_m256i __fpcall operator+(imut __m256i value) imut nex {
				return qeh_m256i(get() + value);
			};

			__compelled_inline qeh_m256i __fpcall operator-(imut __m256i value) imut nex {
				return qeh_m256i(get() - value);
			}

			__compelled_inline qeh_m256i __fpcall operator/(imut __m256i value) imut nex {
				return qeh_m256i(get() / value);
			}

			__compelled_inline qeh_m256i __fpcall operator*(imut __m256i value) imut nex {
				return qeh_m256i(get() * value);
			}

			__compelled_inline qeh_m256i& __fpcall operator+=(imut __m256i value) nex {
				set(get() + value);
				return *this;
			}

			__compelled_inline qeh_m256i& __fpcall operator-=(imut __m256i value) nex {
				set(get() - value);
				return *this;
			}

			__compelled_inline qeh_m256i& __fpcall operator*=(imut __m256i value) nex {
				set(get() * value);
				return *this;
			}

			__compelled_inline qeh_m256i& __fpcall operator/=(imut __m256i value) nex {
				set(get() / value);
				return *this;
			}

#endif

			__compelled_inline qeh_m256i& __fpcall operator=(imut __m256i value) nex {
				set(value);
				return *this;
			}

			__compelled_inline __stackcall operator __m256i() imut nex {
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

			__compelled_inline __fpcall qeh_m256d(imut __m256d value) nex  {

				if (!is_init)
					init_qtype_hash();

				set(value);
			}
			__optimized_dtor ~qeh_m256d() nex {
				polyc::unregister_polyc_pointer(_value.open_data_ptr());
			}

#pragma endregion

#pragma region Accessors

			__compelled_inline __m256d __stackcall get() imut nex {

				// Invoke get() accessor to memcmp checksums, as checksums are for ciphertext, this must happen before open_data_ptr() is called
				auto value = _value.get();

				qengine::polyc::algo(_value.open_data_ptr(), sizeof(__m256d));

				value = *_value.open_data_ptr();

				qengine::polyc::algo(_value.open_data_ptr(), sizeof(__m256d));

				_value.close_data_ptr();

				return value;
			}

			__compelled_inline bool __regcall set(imut __m256d value) nex {

				*_value.open_data_ptr() = value;

				qengine::polyc::algo(_value.open_data_ptr(), sizeof(__m256d));

				return _value.close_data_ptr();
			}

			__compelled_inline imut c_void __stackcall open_data_ptr() imut nex {
				return _value.open_data_ptr();
			}

			__compelled_inline imut c_void __stackcall get_raw_memory_address() imut nex {
				return imut_cast<__m256d*>(_value.get_raw_memory_address());
			}

#pragma endregion

#pragma region Operators

#ifdef __clang__

			__compelled_inline qeh_m256d __fpcall operator+(imut __m256d value) imut nex {
				return qeh_m256d(get() + value);
			};

			__compelled_inline qeh_m256d __fpcall operator-(imut __m256d value) imut nex {
				return qeh_m256d(get() - value);
			}

			__compelled_inline qeh_m256d __fpcall operator/(imut __m256d value) imut nex {
				return qeh_m256d(get() / value);
			}

			__compelled_inline qeh_m256d __fpcall operator*(imut __m256d value) imut nex {
				return qeh_m256d(get() * value);
			}

			__compelled_inline qeh_m256d& __fpcall operator+=(imut __m256d value) nex {
				set(get() + value);
				return *this;
			}

			__compelled_inline qeh_m256d& __fpcall operator-=(imut __m256d value) nex {
				set(get() - value);
				return *this;
			}

			__compelled_inline qeh_m256d& __fpcall operator*=(imut __m256d value) nex {
				set(get() * value);
				return *this;
			}

			__compelled_inline qeh_m256d& __fpcall operator/=(imut __m256d value) nex {
				set(get() / value);
				return *this;
			}

#endif

			__compelled_inline qeh_m256d& __fpcall operator=(imut __m256d value) nex {
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

#pragma endregion

#pragma region String

		class qeh_string {

		private:

#pragma region Encrypted value

			qtype_hash::qh_string _value;

#pragma endregion

		public:

#pragma region Ctor / Dtor

			__compelled_inline __stackcall qeh_string(imut std::string value) nex {

				if (!is_init)
					init_qtype_hash();

				set(value);
			}

			__optimized_ctor qeh_string(imut char* value = "") {

				if (!is_init)
					init_qtype_hash();

				set(value);
			}

			__compelled_inline __stackcall ~qeh_string() nex { 
				
				polyc::unregister_polyc_pointer(reinterpret_cast<c_void>( imut_cast<char*>(_value.open_data_ptr()) ));
			}

#pragma endregion

#pragma region Accessors

			__compelled_inline std::string __stackcall get() imut nex {
				
				auto value = _value.get();

				qengine::polyc::algo(imut_cast<char*>(_value.open_data_ptr()), _value.get().length());

				value = *_value.open_str_ptr();

				qengine::polyc::algo(imut_cast<char*>(_value.open_data_ptr()), _value.get().length());

				_value.close_data_ptr();

				return value;
			}

			__compelled_inline bool __stackcall set(imut std::string value) nex {
				
				*_value.open_str_ptr() = value;

				return qengine::polyc::algo(imut_cast<char*>(_value.open_data_ptr()), _value.get().length());

				return _value.close_data_ptr();
			}

			__compelled_inline imut c_void __stackcall open_data_ptr() nex {
				return imut_cast<char*>(_value.open_data_ptr());
			}

			__compelled_inline imut c_void __stackcall get_raw_memory_address() imut nex {
				return imut_cast<char*>(_value.get_raw_memory_address());
			}

#pragma endregion

#pragma region Operators

			__compelled_inline qeh_string __stackcall operator+(imut std::string& value) imut nex {
				return qeh_string(get() + value);
			}

			__compelled_inline qeh_string& __stackcall operator+=(imut std::string& value) nex {
				set(get() + value);
				return *this;
			}

			__compelled_inline qeh_string& __stackcall operator=(imut std::string value) nex {
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

		class qeh_wstring {

		private:

#pragma region Encrypted value

			qtype_hash::qh_wstring _value;

#pragma endregion

		public:

#pragma region Ctor / Dtor

			__compelled_inline __stackcall qeh_wstring(imut std::wstring value) nex {

				if (!is_init)
					init_qtype_hash();

				set(value);
			}

			__compelled_inline __stackcall ~qeh_wstring() nex {
				
				polyc::unregister_polyc_pointer(reinterpret_cast<c_void>( imut_cast<wchar_t*>(_value.open_data_ptr()) ));
			}

#pragma endregion

#pragma region Accessors

			__compelled_inline std::wstring __stackcall get() imut nex {

				auto value = _value.get();

				qengine::polyc::algo(imut_cast<wchar_t*>(_value.open_data_ptr()), _value.get().length() * sizeof(wchar_t));

				value = *_value.open_wstr_ptr();

				qengine::polyc::algo(imut_cast<wchar_t*>(_value.open_data_ptr()), _value.get().length() * sizeof(wchar_t));

				_value.close_data_ptr();

				return value;
			}

			__compelled_inline bool __stackcall set(imut std::wstring value) nex {

				*_value.open_wstr_ptr() = value;

				return qengine::polyc::algo(imut_cast<wchar_t*>(_value.open_data_ptr()), _value.get().length() * sizeof(wchar_t));

				return _value.close_data_ptr();
			}


			__compelled_inline imut c_void __stackcall open_data_ptr() nex {
				return imut_cast<wchar_t*>(_value.open_data_ptr());
			}

			__compelled_inline imut c_void __stackcall get_raw_memory_address() imut nex {
				return imut_cast<wchar_t*>(_value.get_raw_memory_address());
			}

#pragma endregion

#pragma region Operators

			__compelled_inline qeh_wstring __stackcall operator+(imut std::wstring& value) imut nex {
				return qeh_wstring(get() + value);
			}

			__compelled_inline qeh_wstring& __stackcall operator+=(imut std::wstring& value) nex {
				set(get() + value);
				return *this;
			}

			__compelled_inline qeh_wstring& __stackcall operator=(imut std::wstring& value) nex {
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

				index_proxy(std::size_t index_, qeh_malloc& instance) nex : index(index_), parent(instance) { }

#pragma endregion

#pragma region Operator overrides

				__compelled_inline std::uint8_t& operator=(std::uint8_t value) nex {

					parent.set(index, value);
					return value;   // return the passed assignment value rather than using up absurd resources to decrypt, re-encrypt everything using get()
				}

				__compelled_inline __regcall operator std::uint8_t() imut nex {

					return parent.get(index);
				}

#pragma endregion
			};

#pragma endregion

		public:

#pragma region Ctor

			__compelled_inline __regcall qeh_malloc( imut std::size_t size ) nex : allocation(size) {
				if (!size)
					return;

				if (!is_init)
					init_qtype_hash();

				if (!allocation.open_data_ptr())
					return;

			}

#pragma endregion

#pragma region Get Accessors

			__compelled_inline imut bool __regcall get(imut std::uintptr_t source_position, c_void destination, imut std::size_t length) imut nex {

				if (!destination || !length)
					return false;

				qengine::polyc::algo(imut_cast<c_void>(allocation.open_data_ptr()), allocation.length(), false);

				allocation.get(destination, source_position, length);

				qengine::polyc::algo(imut_cast<c_void>(allocation.open_data_ptr()), allocation.length(), false);

				allocation.close_data_ptr();

				return true;
			}

			__compelled_inline c_void __regcall get( imut std::uintptr_t position, imut std::uintptr_t length ) nex {

				if (!length)
					return nullptr;

				auto* result = malloc(length);

				if (!result)
					return nullptr;

				get(position, result, length);
			}

			__compelled_inline std::uint8_t __regcall get( imut std::uintptr_t position ) imut nex {

				std::uint8_t _return = NULL;

				get(position, &_return, sizeof(_return));

				return _return;
			}

			__compelled_inline c_void __regcall get() imut nex {

				auto* result = malloc( allocation.length() );

				if (!result)
					return nullptr;

				if (!get(0, result, allocation.length()))
					return nullptr;

				return result;
			}

			__compelled_inline imut c_void __stackcall get_raw_memory_address() imut nex {
				return allocation.get_raw_memory_address();
			}

#pragma endregion

#pragma region Set Accessors

			__compelled_inline imut bool __regcall set( imut std::uintptr_t position, c_void data, imut std::size_t length) nex {

				if (!data || !length)
					return false;

				qengine::polyc::algo(imut_cast<c_void>(allocation.open_data_ptr()), allocation.length(), false);

				memcpy((c_void)(reinterpret_cast<std::uintptr_t>(allocation.open_data_ptr()) + position), data, length);

				qengine::polyc::algo(imut_cast<c_void>(allocation.open_data_ptr()), allocation.length(), false);

				allocation.close_data_ptr();

				return true;
			}

			template<typename T>
			__compelled_inline void __regcall set( imut std::uintptr_t position, T value ) nex {
				set(position, &value, sizeof(decltype(value)));
			}

#pragma endregion

#pragma region Utility functions

			__compelled_inline void __regcall reallocate( imut std::size_t size ) nex {

				allocation.reallocate(size);
			}

			__compelled_inline imut bool __regcall swap(c_void allocation_, imut std::size_t size, imut bool free_source = false) nex {
				if (!size)
					return false;

				c_void enc_alloc = malloc(size);

				if (!enc_alloc)
					return false;

				memcpy(enc_alloc, allocation_, size);

				qengine::polyc::algo(enc_alloc, size, false);

				if (free_source)
					free(allocation_);

				allocation.swap(enc_alloc, size);

				return true;
			}

			__compelled_inline imut c_void open_data_ptr() nex {

				return allocation.open_data_ptr();
			}

#pragma endregion

#pragma region Operators

			__compelled_inline index_proxy __regcall operator[]( imut std::size_t index ) nex {
				return index_proxy(index, *this);
			}

#pragma endregion

#pragma region Destructor

			__compelled_inline ~qeh_malloc() nex {
				
				polyc::unregister_polyc_pointer(allocation.open_data_ptr());
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