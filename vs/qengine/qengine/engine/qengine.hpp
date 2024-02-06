#ifndef QENGINE_H
#define QENGINE_H

// commented section below is for including direct from source
/*
#ifdef NDEBUG
#pragma comment(lib, "qengine.lib")
#else
#pragma comment(lib, "qengine_d.lib")
#endif
*/

#pragma region Imports

#pragma region qengine

#include "polytypes/qtype_enc.hpp"
#include  "hashtypes/qtype_hash.hpp"
#include  "polyhashtypes/qtype_enchash.hpp"
#include  "../qutil/qcritical.hpp"
#include "../qimport/qimport.hpp"
#include "../qmorph/qdisasm.hpp"
#include "../qbase/qcallback.hpp"
#include "../qbase/qexcept.hpp"

#pragma endregion

#pragma endregion

#endif