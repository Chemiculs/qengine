#pragma region Header Guard

#ifndef QUTIL_H
#define QUTIL_H

#pragma endregion

#pragma region Imports

#pragma region std

#include <iomanip>
#include <sstream>
#include <string>
#include <cstdint>

#pragma endregion

#pragma region qengine

#include "../qbase/qdef.hpp"

#pragma endregion

#pragma endregion

#pragma region Namespacing

namespace qengine {

	namespace qutil {

#pragma endregion

#pragma region (UNUSED) Binary -> Hex String Conversion

		static __compelled_inline imut std::wstring __regcall get_hex_wstring(imut c_void data, imut std::size_t length) nex {
			std::wstringstream ss;
			ss << std::hex << std::uppercase;

			for (int i = length - 1; i >= 0; --i)
				ss << std::setw(2) << std::setfill(L'0') << reinterpret_cast<imut std::uint8_t*>(data)[i];

			return ss.str();
		}

		static __compelled_inline imut std::string __regcall get_hex_string(imut c_void data, imut std::uint32_t length) nex {

			std::stringstream ss;
			ss << std::hex << std::uppercase;

			for (int i = length - 1; i >= 0; --i)
				ss << std::setw(2) << std::setfill('0') << reinterpret_cast<imut std::uint8_t*>(data)[i];

			return ss.str();
		}

#pragma endregion

#pragma region Safe Integer Inversion

		template <typename T>
		static __compelled_inline T inverse_integral_t(imut T value) nex {

			static_assert(std::is_integral<T>::value && std::is_signed<T>::value, "T must be a signed integral type");

			return -value;
		}

#pragma endregion

#pragma region Namespacing

	}
}

#pragma endregion

#pragma region Header Guard

#endif

#pragma endregion