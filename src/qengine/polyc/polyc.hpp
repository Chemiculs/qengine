#pragma region Header Guard

#ifndef POLYC_H
#define POLYC_H

#pragma endregion

#pragma region Imports

#pragma region qengine

#include "../qbase/qdef.hpp"

#pragma endregion

#pragma region std

#include <chrono>
#include <random>
#include <string>
#include <vector>

#pragma endregion

#pragma endregion

#pragma region Preprocessor

#pragma runtime_checks("", off)   // Disable runtime checks
#pragma strict_gs_check(off)      // Disable stack protection
#pragma optimize("", on)		  // Force optimization
#pragma inline_depth(255)		  
#pragma inline_recursion(on)

#pragma pack(push, 1)

#pragma endregion

#pragma region Namespacing

namespace qengine {

	namespace polyc {

#pragma endregion

#pragma region Pointer Table Entry Structure

		typedef struct polyc_pointer_t {

			std::uintptr_t abs;
			std::uint8_t mutator;
			bool is_crypted;
			std::size_t pointer_table_index;
			std::size_t length;
		};

#pragma endregion

	#pragma region Algorithm Constants

		static imut constexpr auto QCTIME_SEED = __TIME__[7];

	#define BYTE_SET 0xFFui8

	#ifdef _WIN64

	#define BIT_SCRAMBLE 0x0101010101010101ui64

	#else

	#define BIT_SCRAMBLE 0x01010101ui32

	#endif

	#pragma endregion

	#pragma region Globals

		extern bool _polyc_initialized;

		extern std::vector<polyc_pointer_t>* _polyc_pointer_table;

		extern std::vector<std::uintptr_t>* _polyc_subroutine_safecall_table;	//	This needs to be allocated on the heap at runtime atm, if allocated in .data heap at fixed length, preprocessor corrupts first pointer

		extern std::uint8_t qsub0_mutator;
		extern std::uint8_t qsub1_mutator;
		extern std::uint8_t qsub2_mutator;
		extern std::uint8_t qsub3_mutator;
		extern std::uint8_t qsub4_mutator;
		extern std::uint8_t qsub5_mutator;
		extern std::uint8_t qsub6_mutator;
		extern std::uint8_t qsub7_mutator;
		extern std::uint8_t qsub8_mutator;

		extern std::uint8_t _polyc_pointer_table_key;

	#pragma endregion

	#pragma region Seeding Values

	#pragma region Raw arrays

		extern std::uintptr_t _ciph_x[16];

		extern std::uintptr_t _ciph_y[16];

		extern std::uintptr_t _ciph_z[16];

	#pragma endregion

	#pragma region Used Indice(s)

		extern std::uint8_t _indice_map_x[4];

		extern std::uint8_t _indice_map_y[8];

		extern std::uint8_t _indice_map_z[12];

	#pragma endregion

	#pragma endregion

	#pragma region Polymorphic Subroutine(s)

#pragma region Rolling Addition / Subtraction (Junk Code Generation + WEAK Encryption)

		static __compelled_inline imut std::uint8_t rol_add(imut std::uint8_t base, imut std::uint8_t modifier) noexcept {

			static imut constexpr std::uint8_t maximum = 0xFFui8;

			imut std::uint8_t remaining = maximum - base;

			if (modifier <= remaining)
				return base + modifier;

			return (modifier - remaining) - 1;
		}

		static __compelled_inline imut std::uint8_t rol_sub(imut std::uint8_t base, imut std::uint8_t modifier) noexcept {

			static imut constexpr std::uint8_t maximum = 0xFFui8;

			return modifier > base ? maximum - ((modifier - base) - 1) : base - modifier;
		}

#pragma endregion

		static __singleton imut bool __regcall internal_do_algo_subroutine_0(void* data, imut std::size_t length, imut bool crypted) noexcept {

			if (crypted)
				for (auto i = 0; i < length; ++i)
					reinterpret_cast<std::uint8_t*>(data)[i] = rol_add(reinterpret_cast<std::uint8_t*>(data)[i], qsub0_mutator);
			else
				for (auto i = 0; i < length; ++i)
					reinterpret_cast<std::uint8_t*>(data)[i] = rol_sub(reinterpret_cast<std::uint8_t*>(data)[i], qsub0_mutator);

			return true;
		}

		static __singleton imut bool __regcall internal_do_algo_subroutine_1(void* data, imut std::size_t length, imut bool crypted) noexcept {

			internal_do_algo_subroutine_0(data, length, crypted);

			if (crypted)
				for (auto i = 0; i < length; ++i)
					reinterpret_cast<std::uint8_t*>(data)[i] = rol_sub(reinterpret_cast<std::uint8_t*>(data)[i], qsub1_mutator);
			else
				for (auto i = 0; i < length; ++i)
					reinterpret_cast<std::uint8_t*>(data)[i] = rol_add(reinterpret_cast<std::uint8_t*>(data)[i], qsub1_mutator);

			return true;
		}

		static __singleton imut bool __regcall internal_do_algo_subroutine_2(void* data, imut std::size_t length, imut bool crypted) noexcept {

			internal_do_algo_subroutine_0(data, length, crypted);
			internal_do_algo_subroutine_1(data, length, crypted);

			if (crypted)
				for (auto i = 0; i < length; ++i)
					reinterpret_cast<std::uint8_t*>(data)[i] = rol_add(reinterpret_cast<std::uint8_t*>(data)[i], qsub2_mutator);
			else
				for (auto i = 0; i < length; ++i)
					reinterpret_cast<std::uint8_t*>(data)[i] = rol_sub(reinterpret_cast<std::uint8_t*>(data)[i], qsub2_mutator);

			return true;
		}

		static __singleton imut bool __regcall internal_do_algo_subroutine_3(void* data, imut std::size_t length, imut bool crypted) noexcept {

			internal_do_algo_subroutine_0(data, length, crypted);
			internal_do_algo_subroutine_1(data, length, crypted);
			internal_do_algo_subroutine_2(data, length, crypted);

			if (crypted)
				for (auto i = 0; i < length; ++i)
					reinterpret_cast<std::uint8_t*>(data)[i] = rol_sub(reinterpret_cast<std::uint8_t*>(data)[i], qsub3_mutator);
			else
				for (auto i = 0; i < length; ++i)
					reinterpret_cast<std::uint8_t*>(data)[i] = rol_add(reinterpret_cast<std::uint8_t*>(data)[i], qsub3_mutator);

			return true;
		}

		static __singleton imut bool __regcall internal_do_algo_subroutine_4(void* data, imut std::size_t length, imut bool crypted) noexcept {

			internal_do_algo_subroutine_0(data, length, crypted);
			internal_do_algo_subroutine_1(data, length, crypted);
			internal_do_algo_subroutine_2(data, length, crypted);
			internal_do_algo_subroutine_3(data, length, crypted);

			if (crypted)
				for (auto i = 0; i < length; ++i)
					reinterpret_cast<std::uint8_t*>(data)[i] = rol_add(reinterpret_cast<std::uint8_t*>(data)[i], qsub4_mutator);
			else
				for (auto i = 0; i < length; ++i)
					reinterpret_cast<std::uint8_t*>(data)[i] = rol_sub(reinterpret_cast<std::uint8_t*>(data)[i], qsub4_mutator);

			return true;
		}

		static __singleton imut bool __regcall internal_do_algo_subroutine_5(void* data, imut std::size_t length, imut bool crypted) noexcept {

			internal_do_algo_subroutine_0(data, length, crypted);
			internal_do_algo_subroutine_1(data, length, crypted);
			internal_do_algo_subroutine_2(data, length, crypted);
			internal_do_algo_subroutine_3(data, length, crypted);
			internal_do_algo_subroutine_4(data, length, crypted);

			if (crypted)
				for (auto i = 0; i < length; ++i)
					reinterpret_cast<std::uint8_t*>(data)[i] = rol_sub(reinterpret_cast<std::uint8_t*>(data)[i], qsub5_mutator);
			else
				for (auto i = 0; i < length; ++i)
					reinterpret_cast<std::uint8_t*>(data)[i] = rol_add(reinterpret_cast<std::uint8_t*>(data)[i], qsub5_mutator);

			return true;
		}

		static __singleton imut bool __regcall internal_do_algo_subroutine_6(void* data, imut std::size_t length, imut bool crypted) noexcept {

			internal_do_algo_subroutine_0(data, length, crypted);
			internal_do_algo_subroutine_1(data, length, crypted);
			internal_do_algo_subroutine_2(data, length, crypted);
			internal_do_algo_subroutine_3(data, length, crypted);
			internal_do_algo_subroutine_4(data, length, crypted);
			internal_do_algo_subroutine_5(data, length, crypted);

			if (crypted)
				for (auto i = 0; i < length; ++i)
					reinterpret_cast<std::uint8_t*>(data)[i] = rol_add(reinterpret_cast<std::uint8_t*>(data)[i], qsub6_mutator);
			else
				for (auto i = 0; i < length; ++i)
					reinterpret_cast<std::uint8_t*>(data)[i] = rol_sub(reinterpret_cast<std::uint8_t*>(data)[i], qsub6_mutator);

			return true;
		}

		static __singleton imut bool __regcall internal_do_algo_subroutine_7(void* data, imut std::size_t length, imut bool crypted) noexcept {

			internal_do_algo_subroutine_0(data, length, crypted);
			internal_do_algo_subroutine_1(data, length, crypted);
			internal_do_algo_subroutine_2(data, length, crypted);
			internal_do_algo_subroutine_3(data, length, crypted);
			internal_do_algo_subroutine_4(data, length, crypted);
			internal_do_algo_subroutine_5(data, length, crypted);
			internal_do_algo_subroutine_6(data, length, crypted);

			if (crypted)
				for (auto i = 0; i < length; ++i)
					reinterpret_cast<std::uint8_t*>(data)[i] = rol_sub(reinterpret_cast<std::uint8_t*>(data)[i], qsub7_mutator);
			else
				for (auto i = 0; i < length; ++i)
					reinterpret_cast<std::uint8_t*>(data)[i] = rol_add(reinterpret_cast<std::uint8_t*>(data)[i], qsub7_mutator);

			return true;
		}

		static __singleton imut bool __regcall internal_do_algo_subroutine_8(void* data, imut std::size_t length, imut bool crypted) noexcept {

			internal_do_algo_subroutine_0(data, length, crypted);
			internal_do_algo_subroutine_1(data, length, crypted);
			internal_do_algo_subroutine_2(data, length, crypted);
			internal_do_algo_subroutine_3(data, length, crypted);
			internal_do_algo_subroutine_4(data, length, crypted);
			internal_do_algo_subroutine_5(data, length, crypted);
			internal_do_algo_subroutine_6(data, length, crypted);
			internal_do_algo_subroutine_7(data, length, crypted);

			if (crypted)
				for (auto i = 0; i < length; ++i)
					reinterpret_cast<std::uint8_t*>(data)[i] = rol_add(reinterpret_cast<std::uint8_t*>(data)[i], qsub8_mutator);
			else
				for (auto i = 0; i < length; ++i)
					reinterpret_cast<std::uint8_t*>(data)[i] = rol_sub(reinterpret_cast<std::uint8_t*>(data)[i], qsub8_mutator);

			return true;
		}

#pragma region Subroutine FN Prototype

		typedef bool(__regcall* _algo_subroutine_prototype)(void*, imut std::size_t, imut bool);

#pragma endregion

		static __compelled_inline imut bool __regcall internal_do_algo_subroutine_byref(polyc_pointer_t* pointer_entry) noexcept {

			if (!pointer_entry || !_polyc_pointer_table || !_polyc_subroutine_safecall_table)
				return false;

			__XORWORD__(pointer_entry->abs, _polyc_pointer_table_key);								//	Decrypt pointer to data before calling subroutine

			static bool result =  false;

			auto subroutine_addr_cpy = (*_polyc_subroutine_safecall_table)[pointer_entry->mutator];	//	Copy heap allocated encrypted pointer to the stack

			__XORWORD__(subroutine_addr_cpy, _polyc_pointer_table_key);								//	Decrypt pointer ONLY on the stack

			result = reinterpret_cast<_algo_subroutine_prototype>(subroutine_addr_cpy)(reinterpret_cast<void*>(pointer_entry->abs), pointer_entry->length, pointer_entry->is_crypted);

			RtlZeroMemory(&subroutine_addr_cpy, sizeof(void*));										//	Ensure stack pointer is wiped

			pointer_entry->is_crypted = pointer_entry->is_crypted ? false : true;					//	Toggle Encryption state indicator

			__XORWORD__(pointer_entry->abs, _polyc_pointer_table_key);								//	Re-Encrypt pointer before exiting routine

			return result;
		}

#pragma endregion

#pragma region Pseudo-Ctor

		static __singleton imut bool __stackcall polyc_init() noexcept {

			if (_polyc_initialized)
				return false;

			/* provide a proper pseudo-random seed to rand()  */
			srand(
				std::chrono::high_resolution_clock().now().time_since_epoch().count() ^ BYTE_SET ^ QCTIME_SEED // inverse the bits, then xor by compile-time constant
			);

			/* Determine algorithm key value(s) */
			for (auto i = 0; i < 16; ++i) {

				_ciph_x[i] = ((static_cast<uintptr_t>(std::chrono::high_resolution_clock::now().time_since_epoch().count() % __RAND__(0x10000ui32, 0x1ui32)) ^ 16ui64) * 1024) | BIT_SCRAMBLE;

				_ciph_y[i] = ((static_cast<uintptr_t>(std::chrono::high_resolution_clock::now().time_since_epoch().count() % __RAND__(0x20000ui32, 0x1ui32)) ^ 32ui64) * 2048) | BIT_SCRAMBLE;

				_ciph_z[i] = ((static_cast<uintptr_t>(std::chrono::high_resolution_clock::now().time_since_epoch().count() % __RAND__(0x30000ui32, 0x1ui32)) ^ 64ui64) * 4096) | BIT_SCRAMBLE;
			}

			/* determine indices in x vector to use */
			for (auto x = 0; x < sizeof(_indice_map_x); ++x)
				_indice_map_x[x] = static_cast<char>(std::chrono::high_resolution_clock::now().time_since_epoch().count() % static_cast<std::uint8_t>(__RAND__(16, 1)));

			for (auto y = 0; y < sizeof(_indice_map_y); ++y)
				_indice_map_y[y] = static_cast<char>(std::chrono::high_resolution_clock::now().time_since_epoch().count() % static_cast<std::uint8_t>(__RAND__(16, 1)));

			for (auto z = 0; z < sizeof(_indice_map_z); ++z)
				_indice_map_z[z] = static_cast<char>(std::chrono::high_resolution_clock::now().time_since_epoch().count() % static_cast<std::uint8_t>(__RAND__(16, 1)));

			qsub0_mutator ^= static_cast<std::uint8_t>(__RAND__(255, 0));
			qsub1_mutator ^= static_cast<std::uint8_t>(__RAND__(255, 0));
			qsub2_mutator ^= static_cast<std::uint8_t>(__RAND__(255, 0));
			qsub3_mutator ^= static_cast<std::uint8_t>(__RAND__(255, 0));
			qsub4_mutator ^= static_cast<std::uint8_t>(__RAND__(255, 0));
			qsub5_mutator ^= static_cast<std::uint8_t>(__RAND__(255, 0));
			qsub6_mutator ^= static_cast<std::uint8_t>(__RAND__(255, 0));
			qsub7_mutator ^= static_cast<std::uint8_t>(__RAND__(255, 0));
			qsub8_mutator ^= static_cast<std::uint8_t>(__RAND__(255, 0));

			_polyc_pointer_table = new std::vector<polyc_pointer_t>(0);

			_polyc_subroutine_safecall_table = new std::vector<std::uintptr_t>(0);

			if (!_polyc_pointer_table || !_polyc_subroutine_safecall_table)
				return false;

			_polyc_pointer_table_key ^= static_cast<std::uint8_t>(std::chrono::high_resolution_clock().now().time_since_epoch().count());

			auto subroutine0_addr = reinterpret_cast<std::uintptr_t>(&internal_do_algo_subroutine_0);
			auto subroutine1_addr = reinterpret_cast<std::uintptr_t>(&internal_do_algo_subroutine_1);
			auto subroutine2_addr = reinterpret_cast<std::uintptr_t>(&internal_do_algo_subroutine_2);
			auto subroutine3_addr = reinterpret_cast<std::uintptr_t>(&internal_do_algo_subroutine_3);
			auto subroutine4_addr = reinterpret_cast<std::uintptr_t>(&internal_do_algo_subroutine_4);
			auto subroutine5_addr = reinterpret_cast<std::uintptr_t>(&internal_do_algo_subroutine_5);
			auto subroutine6_addr = reinterpret_cast<std::uintptr_t>(&internal_do_algo_subroutine_6);
			auto subroutine7_addr = reinterpret_cast<std::uintptr_t>(&internal_do_algo_subroutine_7);
			auto subroutine8_addr = reinterpret_cast<std::uintptr_t>(&internal_do_algo_subroutine_8);

			__XORWORD__(subroutine0_addr, _polyc_pointer_table_key);
			__XORWORD__(subroutine1_addr, _polyc_pointer_table_key);
			__XORWORD__(subroutine2_addr, _polyc_pointer_table_key);
			__XORWORD__(subroutine3_addr, _polyc_pointer_table_key);
			__XORWORD__(subroutine4_addr, _polyc_pointer_table_key);
			__XORWORD__(subroutine5_addr, _polyc_pointer_table_key);
			__XORWORD__(subroutine6_addr, _polyc_pointer_table_key);
			__XORWORD__(subroutine7_addr, _polyc_pointer_table_key);
			__XORWORD__(subroutine8_addr, _polyc_pointer_table_key);

			_polyc_subroutine_safecall_table->push_back(subroutine0_addr);
			_polyc_subroutine_safecall_table->push_back(subroutine1_addr);
			_polyc_subroutine_safecall_table->push_back(subroutine2_addr);
			_polyc_subroutine_safecall_table->push_back(subroutine3_addr);
			_polyc_subroutine_safecall_table->push_back(subroutine4_addr);
			_polyc_subroutine_safecall_table->push_back(subroutine5_addr);
			_polyc_subroutine_safecall_table->push_back(subroutine6_addr);
			_polyc_subroutine_safecall_table->push_back(subroutine7_addr);
			_polyc_subroutine_safecall_table->push_back(subroutine8_addr);

			return (_polyc_initialized = true);
		}

#pragma endregion

#pragma region Pointer Table Search

		static __compelled_inline polyc_pointer_t* __regcall get_pointer_table_entry_by_abs(imut void* abs) noexcept {

			if (!abs || !_polyc_pointer_table)
				return nullptr;

			for (auto& pointer_entry : *_polyc_pointer_table) {

				__XORWORD__(pointer_entry.abs, _polyc_pointer_table_key);		//	Decrypt pointer to allow for memcmp

				if (reinterpret_cast<void*>(pointer_entry.abs) == abs) {

					__XORWORD__(pointer_entry.abs, _polyc_pointer_table_key);	//	Re-Encrypt pointer before returning

					return &pointer_entry;
				}
				else {

					__XORWORD__(pointer_entry.abs, _polyc_pointer_table_key);	//	Re-Encrypt pointer before continuing iteration
				}
			}
		

			return nullptr;
		}

#pragma endregion

#pragma region Pointer Table Manipulation

		static __singleton imut bool __regcall unregister_polyc_pointer( imut void* abs ) noexcept {

			if ( !abs || !_polyc_pointer_table || !_polyc_pointer_table->size() )
				return false;

			static polyc_pointer_t* existing_entry = nullptr;

			if ((existing_entry = get_pointer_table_entry_by_abs(abs)) == nullptr)
				return false;

			if (_polyc_pointer_table->size() - 1 > existing_entry->pointer_table_index)								// Perform table relocations if necessary
				for (auto i = (existing_entry->pointer_table_index + 1); i < _polyc_pointer_table->size(); ++i)
					--(*_polyc_pointer_table)[i].pointer_table_index;

			RtlZeroMemory(existing_entry, sizeof(polyc_pointer_t));	//	Wipe pointer table data for this entry before removal

			_polyc_pointer_table->erase(_polyc_pointer_table->begin() + existing_entry->pointer_table_index);

			return true;
		}

		static __singleton polyc_pointer_t* __regcall register_polyc_pointer( void* abs, imut std::size_t length ) noexcept {

			if (!abs || !_polyc_pointer_table)
				return nullptr;

			static polyc_pointer_t* existing_entry = nullptr;

			if (( existing_entry = get_pointer_table_entry_by_abs(abs)) != nullptr)
				return existing_entry;

			polyc_pointer_t pointer_entry{

				reinterpret_cast<std::uintptr_t>(abs),
				// Below is an annoying ternary expression with the sole intention of including a chance of subroutine0 and subroutine8 mutators both being selected given a roughly equivalent chance
				std::chrono::high_resolution_clock::now().time_since_epoch().count() % 2 ? ( (std::chrono::high_resolution_clock::now().time_since_epoch().count() % 9) - 1 ) : (std::chrono::high_resolution_clock::now().time_since_epoch().count() % 9),
				false,
				_polyc_pointer_table->size(),
				length
			};

			__XORWORD__(pointer_entry.abs, _polyc_pointer_table_key);

			_polyc_pointer_table->push_back(pointer_entry);

			RtlZeroMemory( &pointer_entry, sizeof(polyc_pointer_t) );	//	Secure pointer memory remaining on the stack

			return &(*_polyc_pointer_table)[_polyc_pointer_table->size() - 1];
		}

#pragma endregion

#pragma region Algorithm

		static __compelled_inline imut bool __regcall algo(void* abs, imut size_t length, imut bool execute_subroutine = true ) noexcept {

			if (!_polyc_initialized)
				polyc_init();

			if (!abs || !length)
				return false;

			polyc_pointer_t* algo_pointer_entry = nullptr;

			if (execute_subroutine) {

				algo_pointer_entry = register_polyc_pointer(abs, length);	//	This fn allocated a pointer table entry, or returns the existing one (if applicable)

				if (!algo_pointer_entry->is_crypted)
					if (!internal_do_algo_subroutine_byref(algo_pointer_entry))	//	We have to manually dictate the execution of this subroutine as it doesn't utilize a rolling algorithm.
						return false;

			}

			auto data_c = reinterpret_cast<std::uint8_t*>(abs);

			/* iterate each individual byte of data in the source */
			for (auto i = 0; i < length; ++i) {
				
				/* run our first pass on the data */
				for (auto x = 0; x < sizeof(_indice_map_x); ++x)
					__XORBYTE__(data_c[i], _ciph_x[_indice_map_x[x]]);

				/* run our second pass on the data */
				for (auto y = 0; y < sizeof(_indice_map_y); ++y)
					__XORBYTE__(data_c[i], _ciph_y[_indice_map_y[y]]);

				/* run our third pass on the data */
				for (auto z = 0; z < sizeof(_indice_map_z); ++z)
					__XORBYTE__(data_c[i], _ciph_z[_indice_map_z[z]]);

			}

			if(execute_subroutine)
				if (algo_pointer_entry->is_crypted)
					if (!internal_do_algo_subroutine_byref(algo_pointer_entry))
						return false;

			return true;
		}

		static __compelled_inline void* __regcall algo_inst(void* abs, imut std::size_t length, imut bool execute_subroutine = true) noexcept {

			if (!abs || !length)
				return nullptr;

			auto* copy_d = reinterpret_cast<std::uint8_t*>(malloc(length));

			if (!copy_d)
				return nullptr;

			memcpy(copy_d, abs, length);

			algo( copy_d, length, execute_subroutine );

			return copy_d;
		}

		template<typename T>
		static __compelled_inline imut bool __regcall algo_t(T& data, imut bool execute_subroutine = true) noexcept {

			return algo(&data, sizeof(decltype(data)), execute_subroutine);
		}

		template<typename T>
		static __compelled_inline T __regcall algo_t_inst(T data, imut bool execute_subroutine = true) noexcept {

			T copy_t = data;

			algo_t(copy_t, execute_subroutine);

			return copy_t;
		}

		static __compelled_inline imut bool __stackcall algo_str(imut std::string& data) noexcept {

			return algo(const_cast<char*>(data.c_str()), data.length());
		}

		static __compelled_inline std::string __cdecl algo_str_inst(imut std::string& data) noexcept {

			std::string copy_str = data;

			algo_str(copy_str);

			return copy_str;
		}

		static __compelled_inline imut bool __stackcall algo_wstr(imut std::wstring& data) noexcept {

			return algo(const_cast<wchar_t*>(data.c_str()), data.size() * sizeof(wchar_t));
		}

		static __compelled_inline std::wstring __stackcall algo_wstr_inst(const std::wstring& data) noexcept {

			std::wstring copy_wstr = data;

			algo_wstr(copy_wstr);

			return copy_wstr;
		}

#pragma endregion

#pragma region Decommission

		static __singleton imut bool __stackcall decommit_polyc_resources() noexcept {
			if (!_polyc_initialized)
					return false;

			if(!_polyc_pointer_table || !_polyc_subroutine_safecall_table)
				return false;

			delete _polyc_pointer_table;
			delete _polyc_subroutine_safecall_table;
		}

#pragma endregion

	}

#pragma region Static Instancing

	bool polyc::_polyc_initialized = false;
	
	std::vector<polyc::polyc_pointer_t>* polyc::_polyc_pointer_table{};

	std::vector<std::uintptr_t>* polyc::_polyc_subroutine_safecall_table{};

	std::uint8_t polyc::qsub0_mutator = __TIME__[7];
	std::uint8_t polyc::qsub1_mutator = __TIME__[6];
	std::uint8_t polyc::qsub2_mutator = __TIME__[5];
	std::uint8_t polyc::qsub3_mutator = __TIME__[4];
	std::uint8_t polyc::qsub4_mutator = __TIME__[3];
	std::uint8_t polyc::qsub5_mutator = __TIME__[2];
	std::uint8_t polyc::qsub6_mutator = __TIME__[1];
	std::uint8_t polyc::qsub7_mutator = __TIME__[0];
	std::uint8_t polyc::qsub8_mutator = __TIME__[7] ^ 0xFF;

	std::uint8_t polyc::_polyc_pointer_table_key = __TIME__[7];

	std::uintptr_t polyc::_ciph_x[16]{};

	std::uintptr_t polyc::_ciph_y[16]{};

	std::uintptr_t polyc::_ciph_z[16]{};

	std::uint8_t polyc::_indice_map_x[4]{};

	std::uint8_t polyc::_indice_map_y[8]{};

	std::uint8_t polyc::_indice_map_z[12]{};

#pragma endregion

#pragma endregion

#pragma region Namespacing

}

#pragma endregion

#pragma region Preprocessor

#pragma pack(pop)

#pragma endregion

#pragma region Header Guard

#endif

#pragma endregion