#ifndef QCALLBACK_H
#define QCALLBACK_H

#include "qexcept.hpp"

namespace qengine {

	namespace qcallback {
#pragma region Callback Prototypes

		typedef void(__fastcall* qmem_exception_rogue_c)(qexcept::q_rogueaccess violation, void* data);

#pragma endregion
	}
}

#endif