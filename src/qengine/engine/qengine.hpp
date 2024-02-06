#ifndef QENGINE_H
#define QENGINE_H

#define ASMJIT_STATIC

#ifdef NDEBUG

#ifdef _WIN64

#pragma comment(lib, "qengine64.lib")
#pragma comment(lib, "asmjit64.lib")

#else

#pragma comment(lib, "qengine32.lib")
#pragma comment(lib, "asmjit32.lib")

#endif

#else

#ifdef _WIN64

#pragma comment(lib, "qengine_d64.lib")
#pragma comment(lib, "asmjit_d64.lib")

#else

#pragma comment(lib, "qengine_d32.lib")
#pragma comment(lib, "asmjit_d32.lib")

#endif

#endif

#include "polytypes/qtype_enc.hpp"
#include  "hashtypes/qtype_hash.hpp"
#include  "polyhashtypes/qtype_enchash.hpp"
#include  "../qutil/qcritical.hpp"
#include "../qimport/qimport.hpp"
#include "../qmorph/qdisasm.hpp"
#include "../qhook/qhook.hpp"

#endif