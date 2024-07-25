#include <chrono>
#include <vector>
#include <winnt.h>
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

        enum address_load_t{

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
            
            bool is_valid;

            address_load_t address_load_type;

            control_flow_transfer_t control_flow_transfer_type;

            std::size_t length;

            std::unique_ptr<std::uint8_t[]> body;
        };

#pragma endregion

class qhook_inline{

    private:

#pragma region Globals

        const std::uintptr_t _abs_real_fn;

        // We will get this address manually dependent on whether interrupt codecaves are used, or imported WINAPI functions
        const std::uintptr_t _abs_false_call;

        qhook_t _hook;

        std::unique_ptr<std::uint8_t[]> _original_shellcode;

#pragma endregion
        
        __inlineable qhook_t __regcall qhook_gen_ret_ihook(

            imut std::uintptr_t abs,
            imut bool inline_abs = true,
            imut asmjit::x86::Gpq* override_x64_gpr = nullptr
        ) nex {

            if(!abs)
                return {false};

#pragma region AsmJit Objects

            asmjit::JitRuntime jit_r;

            asmjit::CodeHolder code_h{};

            code_h.init(jit_r._environment);

            asmjit::x86::Assembler assembler_o(&code_h);

#pragma endregion

            if(inline_abs){
#ifdef _WIN64

                assembler_o.mov(
                    override_x64_gpr ? *override_x64_gpr : asmjit::x86::rax,
                    abs
                );

                assembler_o.push(override_x64_gpr ? *override_x64_gpr : asmjit::x86::rax);
#else
                // PUSH IMM32
                assembler_o.push(abs);
#endif
            }else{

                assembler_o.push(asmjit::x86::Mem((std::uintptr_t)&abs));
            }

            assembler_o.ret();

            asmjit::Error err;

            void* alloc_insn;

            if ((err = jit_r.add(&alloc_insn, &code_h))) 
                return {false};

            std::unique_ptr<std::uint8_t[]> alloc_r = std::make_unique<std::uint8_t[]>(code_h.codeSize());

            memcpy(alloc_r.get(), alloc_insn, code_h.codeSize()); // asmjit compiled code lifetime expires at end of scope, so use a ghetto heap allocation work-around

            return {

                true,
                inline_abs ? address_load_t::inline_register : address_load_t::symbolic,
                control_flow_transfer_t::_RET,
                code_h.codeSize(),
                std::move(alloc_r)
            };
        }

        __inlineable qhook_t __regcall qhook_gen_jmp_ihook(

            imut std::uintptr_t abs,
            imut bool inline_abs,
            // This argument does nothing on x32 as no register needed for inlined jmp
            imut asmjit::x86::Gpq* override_x64_gpr = nullptr

        ) nex {

            if(!abs)
                return {false};

#pragma region AsmJit Objects

            asmjit::JitRuntime jit_r;

            asmjit::CodeHolder code_h{};

            code_h.init(jit_r._environment);

            asmjit::x86::Assembler assembler_o(&code_h);

#pragma endregion

            if(inline_abs){
                
#ifdef _WIN64

                assembler_o.mov(
                override_x64_gpr ? *override_x64_gpr : asmjit::x86::rax,
                abs
                );

                assembler_o.jmp( override_x64_gpr ? *override_x64_gpr : asmjit::x86::rax );

#else

                assembler_o.jmp(abs));

#endif

            }
            else{
                
                assembler_o.jmp(asmjit::x86::Mem((std::uintptr_t)&abs));
            }

            asmjit::Error err;

            void* alloc_insn;

            if ((err = jit_r.add(&alloc_insn, &code_h))) 
                return {false};

            std::unique_ptr<std::uint8_t[]> alloc_r = std::make_unique<std::uint8_t[]>(code_h.codeSize());

            if(!alloc_r)
                return {false};

            memcpy(alloc_r.get(), alloc_insn, code_h.codeSize()); // asmjit compiled code lifetime expires at end of scope, so use a ghetto heap allocation work-around

            return {

                true,
                inline_abs ? address_load_t::inline_register : address_load_t::symbolic,
                control_flow_transfer_t::_JMP,
                code_h.codeSize(),
                std::move(alloc_r)
            };
        }

        // POC dummy function test, just return and use MessageBoxA() for now
        __inlineable imut std::uintptr_t get_falsecall_address_WINAPI() nex {

            // When fully implemented this will contain list ofn generally unused WINAPI functions which will be randomly selected, for now just return &MessageBoxA();
            return (std::uintptr_t)&MessageBoxA;
        }



    public:

        template<typename T, typename... args>
        __inlineable imut T __regcall qstdcall( 
            
            args... arguments
        ) nex {
             
            if (!_abs_false_call || !_abs_real_fn || !_hook.is_valid)
                return (T)NULL;

            return reinterpret_cast<T(__stdcall*)(args...)>(reinterpret_cast<void*>(_abs_false_call))(arguments...);
        }

        __optimized_ctor qhook_inline (

             imut std::uintptr_t abs,
             control_flow_transfer_t cf_transfer_t,
             imut bool inline_abs = true,
             imut asmjit::x86::Gpq* override_x64_gpr = nullptr
        ) nex : 
        _abs_real_fn(abs),
        _abs_false_call(get_falsecall_address_WINAPI()) {

            if(!abs)
                return;

            if(cf_transfer_t == _JMP)
                _hook = qhook_gen_jmp_ihook(abs, inline_abs, override_x64_gpr);
            else
                _hook = qhook_gen_ret_ihook(abs, inline_abs, override_x64_gpr);

            if(!_hook.is_valid)
                return;

            auto alloc_backup = std::make_unique<std::uint8_t[]>(_hook.length);

            memcpy(

                alloc_backup.get(),
                reinterpret_cast<void*>(_abs_false_call),
                _hook.length
            );

            _original_shellcode = std::move(alloc_backup);

            DWORD protection = NULL;

            if(!VirtualProtect(reinterpret_cast<void*>(_abs_false_call), _hook.length, PAGE_EXECUTE_READWRITE, &protection))
                return;

            memcpy(

                reinterpret_cast<void*>(_abs_false_call),
                _hook.body.get(),
                _hook.length
            );

            if(!VirtualProtect(reinterpret_cast<void*>(_abs_false_call), _hook.length, protection, &protection))
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