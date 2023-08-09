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

#include "polytypes/qenc_t.hpp"
#include  "hashtypes/qhash_t.hpp"
#include  "polyhashtypes/qenc_h_t.hpp"
#include  "../qutil/qcritical.hpp"
#include "../qimport/qimport.hpp"
#include "../qmorph/qdisasm.hpp"
#include "../qhook/qhook.hpp"

#endif