#pragma region Header Guard

#ifndef QGEN_H
#define QGEN_H

#pragma endregion

#pragma region Imports

#include <random>
#include <chrono>
#include <climits>
#include <unordered_map>

#pragma region qengine

#include "../qimport/qimport.hpp"

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

#pragma endregion

namespace qengine {

	namespace qmorph{

		namespace qgen {

	#pragma region Opcode Descriptor(s)

			enum asm_register64 {

				RAX,
				RBX,
				RCX,
				RDX,
				RSI
			};

			enum asm_register32 {
				
				EAX,
				EBX,
				ECX,
				EDX,
				ESI
			};

			enum asm_preamble {

				MOV,
				PUSH,
				POP,
				CALL,
				OR,
				XOR,
				AND,
				SUB,
				INC,
				DEC,
				JMP
			};
			/* in order of PREAMBLE_TYPE, IMM / IMMEDIATE_TO_REG_OPERATION_SIZE, REG / REG_TO_REG_SIZE */
			static std::unordered_map<asm_preamble, std::pair<char, char>> preamble_size_mapping_64{
				{ MOV, { 7 , 3 } }, // we are using imm32 values regardless of platform to simplify this process atm
				{ PUSH, { 5, 1 } },
				{ POP, { 1, 1 } },
				{ CALL, { 6, 2 } }, // 0 will be a flag for not supported operation
				{ OR, { 0, 3 } },  // we won't use imm->reg for below insn's so value of zero
				{ XOR, { 0, 3 } },
				{ AND, { 0, 3 } },
				{ SUB, { 0, 3 } },
				{ INC, { 0, 3 } },
				{ DEC, { 0, 3 } },
				{ JMP, { 0, 2 } }
			};

#pragma endregion

			class asm_generator {

			private:

				static __inlineable const asmjit::_abi_1_10::x86::Gpq* generate_random_register64() noexcept {

#pragma region RNG Locals

					auto epoch_t = std::chrono::high_resolution_clock::now().time_since_epoch().count();

					std::default_random_engine engine_r(epoch_t);

					std::uniform_int_distribution<short> distributor_o(0, 4);

#pragma endregion

					auto register_o = static_cast<asm_register64>(distributor_o(engine_r));

					switch (register_o) {
						case RAX: {
							return &asmjit::x86::rax;
							break;
						}
						case RBX: {
							return &asmjit::x86::rbx;
							break;
						}
						case RCX: {
							return &asmjit::x86::rcx;
							break;
						}
						case RDX: {
							return &asmjit::x86::rdx;
							break;
						}
						case RSI: {
							return &asmjit::x86::rsi;
							break;
						}
						default: {
							return nullptr;
						}
					}

				}

				static __inlineable const asmjit::_abi_1_10::x86::Gpd* generate_random_register32() noexcept {

#pragma region RNG locals

					auto epoch_t = std::chrono::high_resolution_clock::now().time_since_epoch().count();

					std::default_random_engine engine_r(epoch_t);

					std::uniform_int_distribution<short> distributor_o(0, 4);

#pragma endregion

					auto register_o = static_cast<asm_register32>(distributor_o(engine_r));

					switch (register_o) {
						case EAX: {
							return &asmjit::x86::eax;
							break;
						}
						case EBX: {
							return &asmjit::x86::ebx;
							break;
						}
						case ECX: {
							return &asmjit::x86::ecx;
							break;
						}
						case EDX: {
							return &asmjit::x86::edx;
							break;
						}
						case ESI: {
							return &asmjit::x86::esi;
							break;
						}
						default: {
							return nullptr;
						}
					}

				}

				static __inlineable void* __regcall generate_insn(asm_preamble insn_t) noexcept {

#pragma region Random Number Generator

					auto epoch_t = std::chrono::high_resolution_clock::now().time_since_epoch().count();

					std::default_random_engine engine_r(epoch_t);

					std::uniform_int_distribution<uint32_t> distributor_o(0, UINT32_MAX);

#pragma endregion

#pragma region AsmJit Objects

					asmjit::JitRuntime jit_r;

					asmjit::CodeHolder code_h{};

					code_h.init(jit_r._environment);

					asmjit::x86::Assembler assembler_o(&code_h);

#pragma endregion

					void* alloc_insn = nullptr;

					switch (insn_t) { // could compress the preprocessor directives but this works for now

						case MOV: {

#ifdef _WIN64
							assembler_o.mov(*generate_random_register64(), static_cast<uint32_t>(distributor_o(engine_r)));
#else
							assembler_o.mov(*generate_random_register32(), static_cast<uint32_t>(distributor_o(engine_r)));
#endif
							break;
						}

						case PUSH:{
							assembler_o.push(static_cast<uint32_t>(distributor_o(engine_r)));
							break;
						}
						case POP: {

#ifdef _WIN64
							assembler_o.pop(*generate_random_register64());
#else
							assembler_o.pop(*generate_random_register32());
#endif
							break;
						}
						case CALL: {

							assembler_o.call(static_cast<uint32_t>(distributor_o(engine_r))); // call imm64 does not exist so use imm32

							break;
						}
						case OR: {

#ifdef _WIN64
							assembler_o.or_(*generate_random_register64(), *generate_random_register64());
#else
							assembler_o.or_(*generate_random_register32(), *generate_random_register32());
#endif

							break;
						}
						case XOR: {

#ifdef _WIN64
							assembler_o.xor_(*generate_random_register64(), *generate_random_register64());
#else
							assembler_o.xor_(*generate_random_register32(), *generate_random_register32());
#endif
							break;
						}
						case AND: {

#ifdef _WIN64
							assembler_o.and_(*generate_random_register64(), *generate_random_register64());
#else
							assembler_o.and_(*generate_random_register32(), *generate_random_register32());
#endif
							break;
						}
						case SUB: {

#ifdef _WIN64
							assembler_o.sub(*generate_random_register64(), *generate_random_register64());
#else
							assembler_o.sub(*generate_random_register32(), *generate_random_register32());
#endif
							break;
						}
						case JMP: {

#ifdef _WIN64
							assembler_o.jmp(*generate_random_register64());
#else
							assembler_o.jmp(*generate_random_register32());
#endif
							break;
						}
					}

					asmjit::Error err;

					if (err = jit_r.add(&alloc_insn, &code_h)) 
						return nullptr;

					auto* alloc_r = malloc(code_h.codeSize());

					memcpy(alloc_r, alloc_insn, code_h.codeSize()); // asmjit compiled code lifetime expires at end of scope, so use a ghetto heap allocation work-around

					return alloc_r;
				}

			public:

				static __inlineable void* __regcall generate_assembly(uint32_t length) noexcept {

					if (!length)
						return nullptr;

#pragma region RNG Locals

					auto epoch_t = std::chrono::high_resolution_clock::now().time_since_epoch().count();

					std::default_random_engine engine_r(epoch_t);

					std::uniform_int_distribution<short> distributor_o(0, 9);

#pragma endregion

					void* shellcode_r;

					if (!(shellcode_r = malloc(length)))
						throw std::bad_alloc();

					intptr_t last_insn_index = -1;

					size_t bytes_written = static_cast<size_t>(0);

					do {

						auto remaining = length - bytes_written;

						asm_preamble insn;

						std::pair<char, char> insn_size_data;

						auto word_r = distributor_o(engine_r);

						if (remaining >= 7) {

							if (word_r >= 7)
								insn = MOV;
							else if (word_r >= 3)
								insn = PUSH;
							else if (word_r >= 0)
								insn = CALL;
						}
						else if (remaining >= 3) {

							if (word_r >= 6)
								insn = POP;
							else if (word_r == 5) // can't be bothered to make this a switch
								insn = XOR;
							else if (word_r == 4)
								insn = AND;
							else if (word_r == 3)
								insn = SUB;
							else if (word_r == 2)
								insn = INC;
							else if (word_r == 1)
								insn = DEC;
							else if (!word_r)
								insn = JMP;
						}
						else { // Fill remaining padding with NOP instructions
							
							void* alloc_nop;

							if (!(alloc_nop = malloc(remaining)))
								throw std::bad_alloc();

							memset(alloc_nop, static_cast<std::uint8_t>(0x90), remaining);

							memcpy(reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(shellcode_r) + bytes_written), alloc_nop, remaining);

							free(alloc_nop);

							goto do_ret; // this may throw compile-time errors with C++ 20 bcuz gotos r scary

							break;
						}

						insn_size_data = preamble_size_mapping_64.at(insn);

						auto* alloc_insn = generate_insn(insn);

						memcpy(reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(shellcode_r) + bytes_written), alloc_insn, insn_size_data.first);

						free(alloc_insn);

						bytes_written += insn_size_data.first;

					} while (bytes_written < length);

				do_ret:

					return shellcode_r;
				}

			};

#pragma region Namespacing

		}
	}
}

#pragma endregion

#pragma region Header Guard

#endif

#pragma endregion