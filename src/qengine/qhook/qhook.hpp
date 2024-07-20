#include <vector>
#pragma region Header Guard

#ifndef QHOOK_H
#define QHOOK_H

#pragma endregion

#pragma region Imports

#pragma region qengine

#include "../qbase/qpreprocess.hpp"

#pragma endregion 

#pragma region ASMJIT

#define ASMJIT_STATIC
#include "../extern/asmjit/asmjit.h"

#pragma endregion

#pragma endregion

#pragma region Preprocessor

#ifdef NDEBUG

#ifdef _WIN64

#pragma comment(lib, "asmjit64.lib")

#else

#pragma comment(lib, "asmjit32.lib")

#endif

#else

#ifdef _WIN64

#pragma comment(lib, "asmjit_d64.lib")

#else

#pragma comment(lib, "asmjit_d32.lib")

#endif

#endif

#pragma pack(push, 1)

#pragma endregion

#pragma region Namespacing

namespace qengine{

    namespace qhook{

#pragma endregion
        
#pragma region Enumerations

        enum no_operation_t{

            NOP,
            NOTNOT,
            ADDSUB,
            SUBADD,
            PUSHPOP,
            XORXOR,
            SUBXSPMOVPOP,
        };

        enum address_load_t{
            
            // Address will be encoded into the instructions, and pushed / moved onto the stack
            inline_stack,
            // Address will be encoded into a register, i.e { mov GPR, IMM }
            inline_register,
            // Address will be loaded from a memory location on the Heap, or elsewhere on the Stack (pointer must be supplied)
            symbolic
        };

        // call instruction is a macro around jmp / push / pop and will corrupt SP upon return to caller (unless we predict the Alignment changes the compiler may / may not generate) as the compiler will generate that code itself
        enum control_flow_transfer_t{
            
            _JMP,
            _RET
        };

#pragma endregion

#pragma region Data Structures

        struct qhook_t{
            
            imut address_load_t address_load_type;

            imut control_flow_transfer_t control_flow_transfer_type;

            imut std::size_t length;

            imut std::uintptr_t control_flow_transfer_insn_rva;

            std::unique_ptr<std::uint8_t[]> body;
        };

#pragma endregion

class qhook_inline{

    private:

    __inlineable imut std::unique_ptr<std::uint8_t[]> __regcall qhook_gen_jmp_ihook(

        imut std::uintptr_t abs,
        imut bool inline_abs,
        imut bool generate_junk_insns = false
    ) nex {

        if(!abs)
            return nullptr;

#pragma region AsmJit Objects

					asmjit::JitRuntime jit_r;

					asmjit::CodeHolder code_h{};

					code_h.init(jit_r._environment);

					asmjit::x86::Assembler assembler_o(&code_h);

#pragma endregion

        if(inline_abs){

            //assembler_o.mov();
        }else{

        }

        return nullptr;
    }

    public:

        __optimized_ctor qhook_inline (

             imut std::uintptr_t abs,
             imut bool inline_abs,
             control_flow_transfer_t cf_transfer_t,
             imut bool generate_junk_insns = false
        ) nex {

            if(!abs)
                return;

                
        }

};

#pragma region Namespacing

    }

}

#pragma endregion

#pragma region Preprocessor

#pragma pack(pop)

#pragma endregion

#pragma region Header Guard

#endif

#pragma endregion