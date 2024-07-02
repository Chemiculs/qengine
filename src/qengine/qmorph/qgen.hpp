#include <cstdint>
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

				static __inlineable const asmjit::_abi_1_10::x86::Gpq* generate_random_register64() nex {

					srand(std::chrono::high_resolution_clock::now().time_since_epoch().count());

					auto register_o = static_cast<asm_register64>(__RAND__(4, 0));
					// TODO add r8-r15
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
							break;
						}
					}

				}

				static __inlineable const asmjit::_abi_1_10::x86::Gpd* generate_random_register32() nex {

					srand(std::chrono::high_resolution_clock::now().time_since_epoch().count());

					auto register_o = static_cast<asm_register32>(__RAND__(4, 0));

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
							break;
						}
					}

				}

				static __inlineable imut c_void __regcall generate_insn(asm_preamble insn_t) nex {

#pragma region Random Number Generator

					srand(std::chrono::high_resolution_clock::now().time_since_epoch().count());

#pragma endregion

#pragma region AsmJit Objects

					asmjit::JitRuntime jit_r;

					asmjit::CodeHolder code_h{};

					code_h.init(jit_r._environment);

					asmjit::x86::Assembler assembler_o(&code_h);

#pragma endregion

					static c_void alloc_insn = nullptr;

					switch (insn_t) { // could compress the preprocessor directives but this works for now

						case MOV: {

#ifdef _WIN64
							assembler_o.mov(*generate_random_register64(), static_cast<std::uint32_t>(__RAND__(UINT32_MAX, 0)));
#else
							assembler_o.mov(*generate_random_register32(), static_cast<std::uint32_t>(__RAND__(UINT32_MAX, 0)));
#endif
							break;
						}

						case PUSH:{
							assembler_o.push(static_cast<std::uint32_t>(__RAND__(UINT32_MAX, 0)));
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

							assembler_o.call(static_cast<std::uint32_t>(__RAND__(UINT32_MAX, 0))); // call imm64 does not exist so use imm32

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

					static asmjit::Error err;

					if (err = jit_r.add(&alloc_insn, &code_h)) 
						return nullptr;

					c_void alloc_r = malloc(code_h.codeSize());

					memcpy(alloc_r, alloc_insn, code_h.codeSize()); // asmjit compiled code lifetime expires at end of scope, so use a ghetto heap allocation work-around

					// Securely wipe Singletons, skipping some asmjit objects to avoid potential UB
					RtlZeroMemory(static_cast<c_void>(&alloc_insn), sizeof(c_void));
					RtlZeroMemory(&err, sizeof(asmjit::Error));

					return std::move(alloc_r);
				}

			public:

				static __inlineable imut c_void __regcall generate_assembly(imut std::uint32_t length) nex {

					if (!length)
						return nullptr;

					srand(std::chrono::high_resolution_clock::now().time_since_epoch().count());

					c_void shellcode_r;

					if (!(shellcode_r = malloc(length)))
						return nullptr;

					static std::intptr_t last_insn_index = -1;

					static std::size_t bytes_written = static_cast<size_t>(0);

					do {

						static std::size_t remaining = length - bytes_written;

						asm_preamble insn;

						std::pair<char, char> insn_size_data;

						static std::uint16_t word_r = static_cast<std::uint16_t>(__RAND__(9, 0));

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
							
							c_void alloc_nop;

							if (!(alloc_nop = malloc(remaining)))
								return nullptr;

							memset(alloc_nop, static_cast<std::uint8_t>(0x90), remaining);

							memcpy(reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(shellcode_r) + bytes_written), alloc_nop, remaining);

							free(alloc_nop);

							goto do_ret; // this may throw compile-time errors with C++ 20 bcuz gotos r scary

							break;
						}

						insn_size_data = preamble_size_mapping_64.at(insn);

						c_void alloc_insn = generate_insn(std::move(insn));

						memcpy(reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(shellcode_r) + bytes_written), alloc_insn, insn_size_data.first);

						free(alloc_insn);

						bytes_written += std::move( insn_size_data.first );

						// This is a redundant call foreach iteration, but it garauntees secured Singleton(s) after last iteration at slight performance loss
						RtlZeroMemory(&remaining, sizeof(std::size_t));
						RtlZeroMemory(&word_r, sizeof(std::uint16_t));

					} while (bytes_written < length);

				do_ret:

					RtlZeroMemory(&last_insn_index, sizeof(std::intptr_t));
					RtlZeroMemory(&bytes_written, sizeof(std::size_t));

					return std::move( shellcode_r );
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