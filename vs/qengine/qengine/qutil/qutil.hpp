#ifndef QUTIL_H
#define QUTIL_H

#include <iomanip>
#include <sstream>
#include <string>

namespace qengine {

	namespace qutil {
		/*
		/**************************************************************************************************************
		*																											 *
		*  QUtil is a helper library around the windows api and standard C++ library to make life easier             *
		*																											 *
		***************************************************************************************************************
		*/

		__forceinline std::wstring __fastcall get_hex_wstring(const void* data, int length)
		{
			std::wstringstream ss;
			ss << std::hex << std::uppercase;

			for (int i = length - 1; i >= 0; --i)
				ss << std::setw(2) << std::setfill(L'0') << reinterpret_cast<const unsigned char*>(data)[i];

			return ss.str();
		}

		__forceinline std::string __fastcall get_hex_string(const void* data, int length)
		{
			std::stringstream ss;
			ss << std::hex << std::uppercase;

			for (int i = length - 1; i >= 0; --i)
				ss << std::setw(2) << std::setfill('0') << reinterpret_cast<const unsigned char*>(data)[i];

			return ss.str();
		}
	}

}

#endif