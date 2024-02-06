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

#pragma endregion

namespace qengine {

	namespace qutil {

		__forceinline std::wstring __fastcall get_hex_wstring(const void* data, const std::size_t length) noexcept {
			std::wstringstream ss;
			ss << std::hex << std::uppercase;

			for (int i = length - 1; i >= 0; --i)
				ss << std::setw(2) << std::setfill(L'0') << reinterpret_cast<const unsigned char*>(data)[i];

			return ss.str();
		}

		__forceinline std::string __fastcall get_hex_string(const void* data, const int length) noexcept {
			std::stringstream ss;
			ss << std::hex << std::uppercase;

			for (int i = length - 1; i >= 0; --i)
				ss << std::setw(2) << std::setfill('0') << reinterpret_cast<const unsigned char*>(data)[i];

			return ss.str();
		}
	}

}

#endif