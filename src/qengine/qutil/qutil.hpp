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

		static __compelled_inline std::wstring __regcall get_hex_wstring(const void* data, const std::size_t length) noexcept {
			std::wstringstream ss;
			ss << std::hex << std::uppercase;

			for (int i = length - 1; i >= 0; --i)
				ss << std::setw(2) << std::setfill(L'0') << reinterpret_cast<const unsigned char*>(data)[i];

			return ss.str();
		}

		static __compelled_inline std::string __regcall get_hex_string(const void* data, const int length) noexcept {
			std::stringstream ss;
			ss << std::hex << std::uppercase;

			for (int i = length - 1; i >= 0; --i)
				ss << std::setw(2) << std::setfill('0') << reinterpret_cast<const unsigned char*>(data)[i];

			return ss.str();
		}

#pragma endregion

#pragma region Safe Integer Inversion

		template <typename T>
		static __compelled_inline T inverse_integral_t(T value) noexcept {

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