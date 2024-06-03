/*
/********************************************************************
*                                                                  *
*  Polyc 3-dimensional Polymorphic Encryption Algorithm Prototype  *
*                                                                  *
*********************************************************************
*/

#pragma region Header Guard

#ifndef POLYC_H
#define POLYC_H

#pragma endregion

#pragma region Imports

#pragma region std

#include <chrono>
#include <random>
#include <string>

#pragma endregion 

#pragma region qengine

#include "../qbase/qdef.hpp"

#pragma endregion 

#pragma endregion

#pragma region Preprocessor

#pragma optimize("", on)
#pragma inline_depth(255)
#pragma inline_recursion(on)

#pragma endregion 

#pragma region Namespacing

namespace qengine {

	namespace polyc {

#pragma endregion

#pragma region Other Globals

		extern bool _polyc_initialized;

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

#pragma region Pseudo-Ctor

		static __compelled_inline void __stackcall polyc_init() noexcept {

			/* provide a proper pseudo-random seed to rand()  */

			srand(
				std::chrono::high_resolution_clock().now().time_since_epoch().count() ^ BYTE_SET ^ QCTIME_SEED // inverse the bits, then xor by compile-time constant
			);

			/* Determine algorithm key value(s) */

			for (auto i = 0; i < 16; ++i) {

				_ciph_x[i] = ((static_cast<uintptr_t>(std::chrono::high_resolution_clock::now().time_since_epoch().count() % __RAND__(16, 1)) ^ 16ui64) * 1024) | BIT_SCRAMBLE;

				_ciph_y[i] = ((static_cast<uintptr_t>(std::chrono::high_resolution_clock::now().time_since_epoch().count() % __RAND__(32, 1)) ^ 32ui64) * 2048) | BIT_SCRAMBLE;

				_ciph_z[i] = ((static_cast<uintptr_t>(std::chrono::high_resolution_clock::now().time_since_epoch().count() % __RAND__(64, 1)) ^ 64ui64) * 4096) | BIT_SCRAMBLE;
			}
			/* determine indices in x vector to use */

			for (auto x = 0; x < sizeof(_indice_map_x); ++x)
				_indice_map_x[x] = static_cast<char>(std::chrono::high_resolution_clock::now().time_since_epoch().count() % static_cast<char>(__RAND__(16, 1)));

			for (auto y = 0; y < sizeof(_indice_map_y); ++y)
				_indice_map_y[y] = static_cast<char>(std::chrono::high_resolution_clock::now().time_since_epoch().count() % static_cast<char>(__RAND__(16, 1)));

			for (auto z = 0; z < sizeof(_indice_map_z); ++z)
				_indice_map_z[z] = static_cast<char>(std::chrono::high_resolution_clock::now().time_since_epoch().count() % static_cast<char>(__RAND__(16, 1)));

			_polyc_initialized = true;
		}

#pragma endregion

#pragma region Algorithm

		static __singleton void __regcall algo(void* data, imut size_t length) noexcept {

			if (!_polyc_initialized)
				polyc_init();

			/* obvious */
			if (!length)
				return;

			auto data_c = reinterpret_cast<std::uint8_t*>( data );

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
					__XORBYTE__(data_c[i], _ciph_x[_indice_map_z[z]]);

			}
		}

		static __compelled_inline void* __regcall algo_inst(void* data, imut std::size_t length) noexcept {

			if (!data || !length)
				return nullptr;

			auto* copy_d = reinterpret_cast<std::uint8_t*>(malloc(length));

			if (!copy_d)
				return nullptr;

			memcpy(copy_d, data, length);

			algo(copy_d, length);

			return copy_d;
		}

		template<typename T>
		static __compelled_inline void __regcall algo_t(T& data) noexcept {

			algo(&data, sizeof(decltype(data)));
		}

		template<typename T>
		static __compelled_inline T __regcall algo_t_inst(T data) noexcept {

			T copy_t = data;

			algo_t(copy_t);

			return copy_t;
		}

		static __compelled_inline void __stackcall algo_str(imut std::string& data) noexcept {

			algo(const_cast<char*>(data.c_str()), data.length());
		}

		static __compelled_inline std::string __stackcall algo_str_inst(imut std::string& data) noexcept {

			std::string copy_str = data;

			algo_str(copy_str);

			return copy_str;
		}

		static __compelled_inline void __stackcall algo_wstr(imut std::wstring& data) noexcept {

			algo(const_cast<wchar_t*>(data.c_str()), data.size() * sizeof(wchar_t));
		}

		static __compelled_inline std::wstring __stackcall algo_wstr_inst(imut std::wstring& data) noexcept {

			std::wstring copy_wstr = data;

			algo_wstr(copy_wstr);

			return copy_wstr;
		}

#pragma endregion

#pragma region Namespacing

	}

}

#pragma endregion

#pragma region Static Declarators

	/* have our globals been _polyc_initialized? */
	bool qengine::polyc::_polyc_initialized = false;
	/*Singleton instance(s) of seeding values*/
	std::uintptr_t qengine::polyc::_ciph_x[16]{};

	std::uintptr_t qengine::polyc::_ciph_y[16]{};

	std::uintptr_t qengine::polyc::_ciph_z[16]{};

	std::uint8_t qengine::polyc::_indice_map_x[4]{};

	std::uint8_t qengine::polyc::_indice_map_y[8]{};

	std::uint8_t qengine::polyc::_indice_map_z[12]{};

#pragma endregion

#pragma region Header Guard

#endif

#pragma endregion