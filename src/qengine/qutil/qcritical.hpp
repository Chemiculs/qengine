#ifndef QCRITICAL_H
#define QCRITICAL_H

#pragma region Imports

#include <tuple>
#include <type_traits>

#include "../qbase/qdef.hpp"

#pragma endregion

namespace qengine {

	namespace qcritical {

		enum condition_t {
			GREATERTHAN,
			GREATERTHANOREQUALTO,
			LESSTHAN,
			LESSTHANOREQUALTO,
			NOTEQUALTO,
			EQUALTO
		};

#pragma region Generic Definitions

		template<typename... args, typename... args2, typename T, typename T2>
		__forceinline void __fastcall SCRAMBLE_CRITICAL_CONDITION(
			void(*callback)(args...), void(*callback_two)(args2...),
			const std::tuple<args...> args_one, const std::tuple<args2...> args_two,
			T condition_one, T2 condition_two,
			condition_t condition = EQUALTO) {

			bool evaluation = false;

			switch (condition) {
			case condition_t::EQUALTO: {
				if (std::is_same_v<T, std::string> && std::is_same_v<T2, std::string>)
					evaluation = compare_string(*reinterpret_cast<std::string*>(&condition_one), *reinterpret_cast<std::string*>(&condition_two));
				else if (std::is_same_v<T, std::wstring> && std::is_same_v<T2, std::wstring>)
					evaluation = compare_wstring(*reinterpret_cast<std::wstring*>(&condition_one), *reinterpret_cast<std::wstring*>(&condition_two));
				else
					evaluation = compare_memory(condition_one, condition_two); /* arguments are raw / integral */

				break;
			}
			case condition_t::GREATERTHAN: {
				evaluation = condition_one > condition_two;
				break;
			}
			case condition_t::GREATERTHANOREQUALTO: {
				evaluation = condition_one >= condition_two;
				break;
			}
			case condition_t::LESSTHAN: {
				evaluation = condition_one < condition_two;
				break;
			}
			case condition_t::LESSTHANOREQUALTO: {
				evaluation = condition_one <= condition_two;
				break;
			}
			case condition_t::NOTEQUALTO: {
				if (std::is_same_v<T, std::string> && std::is_same_v<T2, std::string>)
					evaluation = compare_string(*reinterpret_cast<std::string*>(&condition_one), *reinterpret_cast<std::string*>(&condition_two)) ? false : true;
				else if (std::is_same_v<T, std::wstring> && std::is_same_v<T2, std::wstring>)
					evaluation = compare_wstring(*reinterpret_cast<std::wstring*>(&condition_one), *reinterpret_cast<std::wstring*>(&condition_two)) ? false : true;
				else
					evaluation = compare_memory(condition_one, condition_two) ? false : true; /* arguments are raw / integral */

				break;
			}
			default: {
				break;
			}
			}

			if (compare_memory(evaluation, true)) {
				std::apply(callback, args_one);
			}
			else {
				std::apply(callback_two, args_two);
			}
		}

#pragma endregion
	}
}

#endif