#ifndef QCRITICAL_H
#define QCRITICAL_H

#pragma region Imports

#include <tuple>
#include <type_traits>

#include "../qbase/qdef.hpp"
#include "../engine/polyhashtypes/qtype_enchash.hpp"

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

		/* scrambled comparison operation */
		template<typename T, typename T2>
		static __compelled_inline bool __regcall compare_memory(T word1, T2 word2) noexcept {
			bool same = true;

			if (sizeof(decltype(word1)) != sizeof(decltype(word2))) {
				/* align bits of smaller word type to the larger one */
				decltype(sizeof(decltype(word1)) > sizeof(decltype(word2)) ? word1 : word2) word_c = (sizeof(decltype(word1)) > sizeof(decltype(word2)) ? static_cast<decltype(word_c)>(word2) : static_cast<decltype(word_c)>(word1));

				if (sizeof(decltype(word1)) > sizeof(decltype(word2)))
					for (auto i = 0; i < sizeof(decltype(word1)); ++i)
						if (same)
							same = qtype_enchash::qeh_uint8(reinterpret_cast<std::uint8_t*>(&word1)[i]) == qtype_enchash::qeh_uint8(reinterpret_cast<std::uint8_t*>(&word_c)[i]);
						else
							continue;
				else
					for (auto i = 0; i < sizeof(decltype(word2)); ++i)
						if (same)
							same = qtype_enchash::qeh_uint8((reinterpret_cast<std::uint8_t*>(&word2)[i]) == qtype_enchash::qeh_uint8(reinterpret_cast<std::uint8_t*>(&word_c)[i]));
						else
							continue;
			}
			else {
				for (auto i = 0; i < sizeof(decltype(word1)); ++i)
					if (same)
						same = qtype_enchash::qeh_uint8((reinterpret_cast<std::uint8_t*>(&word1)[i]) == qtype_enchash::qeh_uint8(reinterpret_cast<std::uint8_t*>(&word2)[i]));
					else
						continue;
			}

			return same;
		}

		static __compelled_inline bool __regcall fast_compare_string(const std::string string1, const std::string string2) noexcept {

			bool same = true;

			const char* ptr1;
			const char* ptr2;

			if (string1.length() != string2.length()) {
				same = false;
				goto ret;
			}

			ptr1 = string1.c_str();
			ptr2 = string2.c_str();

			for (auto i = 0; i < string1.length(); ++i) {

				if (static_cast<std::uint8_t>(ptr1[i]) != static_cast<std::uint8_t>(ptr2[i])) {
					same = false;
					goto ret;
				}
			}



		ret:

			return same;
		}

		static __compelled_inline bool __regcall fast_compare_wstring(std::wstring string1, std::wstring string2) noexcept {

			bool same = true;

			PWORD ptr1;
			PWORD ptr2;

			PWORD ptr_end;

			if (string1.length() != string2.length()) {
				same = false;
				goto ret;
			}

			ptr1 = reinterpret_cast<PWORD>(const_cast<wchar_t*>(string1.c_str()));
			ptr2 = reinterpret_cast<PWORD>(const_cast<wchar_t*>(string2.c_str()));

			ptr_end = reinterpret_cast<PWORD>(const_cast<wchar_t*>(string1.c_str()) + (string1.length() * sizeof(wchar_t)));

			while (ptr1 < ptr_end) {

				if (*ptr1 != *ptr2) {
					same = false;
					goto ret;
				}

				++ptr1, ++ptr2;
			}


		ret:

			return same;
		}

		template<typename... args, typename... args2, typename T, typename T2>
		__inlineable void __regcall SCRAMBLE_CRITICAL_CONDITION(

			void(*callback)(args...), 
			void(*callback_two)(args2...),
			const std::tuple<args...> args_one,
			const std::tuple<args2...> args_two,
			T condition_one,
			T2 condition_two,
			condition_t condition = EQUALTO
		) {

			bool evaluation = false;

			switch (condition) {

				case condition_t::EQUALTO: {

					if (std::is_same_v<T, std::string> && std::is_same_v<T2, std::string>)
						evaluation = fast_compare_string(*reinterpret_cast<std::string*>(&condition_one), *reinterpret_cast<std::string*>(&condition_two));

					else if (std::is_same_v<T, std::wstring> && std::is_same_v<T2, std::wstring>)
						evaluation = fast_compare_wstring(*reinterpret_cast<std::wstring*>(&condition_one), *reinterpret_cast<std::wstring*>(&condition_two));

					else
						evaluation = compare_memory(condition_one, condition_two); /* arguments are raw / integral */

					break;
				}
				case condition_t::GREATERTHAN: {

					evaluation = condition_one > condition_two;
					break;
				}
				case condition_t::GREATERTHANOREQUALTO: {

					if (std::is_signed<T>::value && !std::is_signed<T2>::value) { // special condition here as a signed int can appear the same as an un signed int for example in memory but hold different values

						evaluation = condition_one >= condition_two;
					}
					else {

						evaluation = compare_memory(condition_one, condition_two); // inlined scrambling

						if (!evaluation) // condition one failed, they are not equal. check if second part of condition is true
							evaluation = condition_one > condition_two;
					}

					break;
				}

				case condition_t::LESSTHAN: {

					evaluation = condition_one < condition_two;
					break;
				}
				case condition_t::LESSTHANOREQUALTO: {

					if (std::is_signed<T>::value && !std::is_signed<T2>::value) { // special condition here as a signed int can appear the same as an un signed int for example in memory but hold different values

						evaluation = condition_one >= condition_two;
					}
					else {

						evaluation = compare_memory(condition_one, condition_two); // inlined scrambling

						if (!evaluation) // condition one failed, they are not equal. check if second part of condition is true
							evaluation = condition_one < condition_two;
					}
					break;
				}
				case condition_t::NOTEQUALTO: {

					if (std::is_same_v<T, std::string> && std::is_same_v<T2, std::string>)
						evaluation = fast_compare_string(*reinterpret_cast<std::string*>(&condition_one), *reinterpret_cast<std::string*>(&condition_two)) ? false : true;

					else if (std::is_same_v<T, std::wstring> && std::is_same_v<T2, std::wstring>)
						evaluation = fast_compare_wstring(*reinterpret_cast<std::wstring*>(&condition_one), *reinterpret_cast<std::wstring*>(&condition_two)) ? false : true;

					else
						evaluation = compare_memory(condition_one, condition_two) ? false : true; /* arguments are raw / integral */

					break;
				}
				default: {
					break;
				}
			}

			if (compare_memory(evaluation, true))
				std::apply(callback, args_one);

			else
				std::apply(callback_two, args_two);
			
		}

#pragma endregion
	}
}

#endif