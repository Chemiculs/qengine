#ifndef QEXCEPT_H
#define QEXCEPT_H

#include "qdef.hpp"

#include <string>

namespace qengine {

	namespace qexcept {
#pragma region Interface Prototype

		struct qexcept_t {

			mut std::string message;

			mut std::uint32_t id;

			mut bool iserror;
		};

#pragma endregion

#pragma region Memory Exceptions

#pragma region Preset Exceptions

		enum qexcept_mem_e {

			BAD_ALLOC,

			BAD_ACCESS,

			BAD_PTR,

			MEMORY_ALTERATION,

			THREAD_VIOLATION,

			ACCESS_VIOLATION,

			HOOK_DETECTED,

			FN_HASH_CORRUPT
		};

		static constexpr imut char* qexcept_mem_str[8]{

			"BAD_ALLOC",

			"BAD_ACCESS",

			"BAD_PTR",

			"MEMORY_ALTERATION",

			"THREAD_VIOLATION",

			"ACCESS_VIOLATION",

			"HOOK_DETECTED",

			"FN_HASH_CORRUPT"
		};

#pragma endregion

#pragma region Memory Exception Prototype

		struct qexcept_mem : qexcept_t {

			__optimized_ctor qexcept_mem(qexcept_mem_e except_t) noexcept {

				message = std::string(qexcept_mem_str[except_t]) ;

				id = except_t;

				// Unnecessary placeholder switch statement, but it's here for future expansion

				switch (except_t) {

					case BAD_ALLOC: {

						iserror = true;
						break;
					}
					case BAD_ACCESS: {

						iserror = true;
						break;
					}
					case ACCESS_VIOLATION: {

						iserror = true;
						break;
					}
					case THREAD_VIOLATION: {

						iserror = true;
						break;
					}
					case HOOK_DETECTED: {

						iserror = true;
						break;
					}
					case FN_HASH_CORRUPT: {

						iserror = true;
						break;
					}
					default: {

						iserror = false;
						break;
					}
				}
			}
		};

#pragma endregion

#pragma region Memory Exception Presets

		struct q_badalloc : qexcept_mem {
			q_badalloc() : qexcept_mem(qexcept_mem_e::BAD_ALLOC) {  }
		};

#define hash_t std::uintptr_t	

		struct q_rogueaccess : qexcept_mem {

			hash_t original_hash;
			hash_t altered_hash;
			q_rogueaccess(hash_t oldhash, hash_t newhash) : qexcept_mem(qexcept_mem_e::MEMORY_ALTERATION) { original_hash = oldhash; altered_hash = newhash; };
		};

#pragma endregion

#pragma endregion
	}
}

#endif