#ifndef QCALLBACK_H
#define QCALLBACK_H

#include "qexcept.hpp"

namespace qengine {

	namespace qcallback {

#pragma region Callback FN Prototypes

		typedef void(__regcall* qmem_exception_rogue_c)(qengine::qexcept::q_rogueaccess violation, c_void data);

#pragma endregion

	}
}

#endif