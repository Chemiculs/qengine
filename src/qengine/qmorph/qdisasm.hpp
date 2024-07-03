#include <winnt.h>
#pragma region Header Guard

#ifndef DISASM_H
#define DISASM_H

#pragma endregion

#pragma region Imports

#pragma region Windows

#include <windows.h>

#pragma endregion

#pragma region std

#include <random>
#include <chrono>
#include <string>
#include <vector>

#pragma endregion

#pragma region qengine

#include "qgen.hpp"

#pragma endregion

#pragma region Capstone

#include "../extern/capstone/include/capstone/capstone.h"

#pragma endregion

#pragma region Preprocessor

#ifdef _WIN64

#pragma comment(lib, "capstone64.lib")

#elif defined(_WIN32)

#pragma comment(lib, "capstone32.lib")

#endif

#pragma endregion

#pragma endregion

#pragma region Namespacing

/* utilizing this class may render VM-based protection solutions un-usable */
namespace qengine {

	namespace qmorph{

		namespace qdisasm {

#pragma endregion

			class qsection_assembler {

#pragma region Constants

#define STATE_NULL 0xFFui8

#pragma endregion

#pragma region Enumerations / Structures

				enum instruction_permutations {

					INT1 = 0xF1,
					INT3 = 0xCC,
					NOP = 0x90
				};

				typedef struct interrupt_permutator { // instruction length is always going to be 1 std::uint8_t so no need for additional field

					c_void instruction_address;
					std::uint8_t iterator_seed;
				};

				typedef struct interrupt_region {

					c_void region_address;
					std::uint32_t region_length;
					std::uint32_t region_parent_section; // index of parent inside executable_sections vector
					std::vector<interrupt_permutator> region_instructions{};
				};

				typedef struct executable_text_section {
					
					PIMAGE_SECTION_HEADER section_header;
					std::vector<interrupt_region> interrupt_mapping{};
				};

#pragma endregion

			private:

#pragma region Globals

#ifdef _WIN64

				mut cs_mode mode = CS_MODE_64;

#else

				mut cs_mode mode = CS_MODE_32;

#endif

				mut cs_arch arch = cs_arch::CS_ARCH_X86;
				mut csh handle;
				mut std::uintptr_t base_address;

				mut std::vector<executable_text_section> executable_sections{};
				mut std::vector<PIMAGE_SECTION_HEADER> pe_other_sections{};
				mut std::vector<interrupt_region> pe_interrupt_regions{};

#pragma endregion

			public:

				/* specify __regcall should the compiler choose to optimize the argument as a pointer (to fit register) */
				__singleton imut bool __regcall instruction_permutation(interrupt_region& region) nex {

					static DWORD protection = NULL;

					if (!VirtualProtect(region.region_address, region.region_length, PAGE_EXECUTE_READWRITE, &protection))
						return false;

					c_void alloc_gen;
					
					if ( (alloc_gen = qgen::asm_generator::generate_assembly(region.region_length)) ) { // generate junk instructions to replace the padding
					
						memcpy(region.region_address, alloc_gen, region.region_length);

						free( alloc_gen );
					}
					
					if (!VirtualProtect(region.region_address, region.region_length, protection, &protection))
						return false;

					// Securely Wipe Singleton
					RtlZeroMemory(&protection, sizeof(DWORD));

					return true;
				}

				/* if you erase / randomize headers before calling this the function will fail and your program will crash */
				__singleton imut bool __stackcall analyze_executable_sections() noexcept {
					
					if (cs_open(arch, mode, &handle) != CS_ERR_OK) // initialize capstone with our target architecture using our handle
						return false;

					static DWORD protection = NULL; // used to set / get virtualprotect permissions for applicable memory pages

					for (auto& section : executable_sections) {

						auto offset = reinterpret_cast<PBYTE>(base_address + section.section_header->VirtualAddress);
						auto& maximum = section.section_header->SizeOfRawData;

						if (!VirtualProtect(static_cast<c_void>(offset), maximum, PAGE_EXECUTE_READWRITE, &protection))
							return false;

						cs_insn* instructions;

						std::size_t instruction_count = cs_disasm(handle, offset, maximum, reinterpret_cast<std::uintptr_t>(offset), maximum, &instructions);

						for (std::size_t i = 0; i < instruction_count; ++i) {

							const auto& instruction = instructions[i]; 

							if (instruction.id == X86_INS_INT1 || instruction.id == X86_INS_INT3) {

								interrupt_region region{};
								region.region_address = reinterpret_cast<c_void>(instruction.address);
								region.region_parent_section = i;
								region.region_length = NULL;

								bool region_continuation = true;
								PBYTE region_iterator = reinterpret_cast<PBYTE>(instruction.address);
								std::uint8_t region_iteration_instruction;

								do {

									region_iteration_instruction = *reinterpret_cast<PBYTE>(region_iterator);

									if (region_iteration_instruction == instruction_permutations::INT3 || region_iteration_instruction == instruction_permutations::INT1) {

										interrupt_permutator interrupt_instruction;
										interrupt_instruction.instruction_address = static_cast<c_void>(region_iterator); // address / pointer to instruction
										region.region_instructions.push_back(interrupt_instruction);

										++region.region_length;

									}
									else {

										region_continuation = false;
									}

									++region_iterator;

								} while (region_continuation);

								if (region.region_length > 1)
									pe_interrupt_regions.push_back(region);
							}

						}

						cs_free(instructions, instruction_count);

						if (!VirtualProtect(static_cast<c_void>(offset), maximum, protection, &protection))
							return false;// this should not occur when rstoring page perms even if mid-execution, something is not right

					}

					// Securely Wipe Singleton
					RtlZeroMemory(&protection, sizeof(DWORD));

					return true;
				}

				__singleton imut bool __regcall morph_executable_sections(imut bool free_memory = true) noexcept {

					if (!pe_interrupt_regions.size())
						return false;

					for (auto& region : pe_interrupt_regions)
						instruction_permutation(region);

					if (free_memory) {

						for (auto& interrupt_mapping : pe_interrupt_regions) {

							for (auto& _interrupt_permutator : interrupt_mapping.region_instructions)
								RtlZeroMemory(&_interrupt_permutator, sizeof(interrupt_permutator));

							RtlZeroMemory(&interrupt_mapping, sizeof(interrupt_region));
						}

						pe_interrupt_regions.clear();
					}

					return true;
				}

#pragma region PE Header Manipulation

				__singleton imut bool __stackcall scramble_dos_header( imut bool null_header = false, imut bool erase_stub = true) noexcept {

#pragma region Locals Setup

					static DWORD protection_old = NULL;

					static noregister auto header_dos_ptr = reinterpret_cast<PIMAGE_DOS_HEADER>(base_address);

#pragma endregion

					if (!VirtualProtect(reinterpret_cast<c_void>(base_address), header_dos_ptr->e_lfanew, PAGE_READWRITE, &protection_old))
						return false;

					if(null_header){

								/* preserve e_lfanew && e_magic so that the exit() call will not throw an exception, for some reason windows checks both of these past it's RunPE exeution */
						auto e_lfanew = reinterpret_cast<PIMAGE_DOS_HEADER>(base_address)->e_lfanew;
						auto e_magic = reinterpret_cast<PIMAGE_DOS_HEADER>(base_address)->e_magic;

						RtlZeroMemory(reinterpret_cast<c_void>(base_address + sizeof(IMAGE_DOS_HEADER)), e_lfanew - sizeof(IMAGE_DOS_HEADER)); // e_lfanew - 1 will also erase the dos stub (debatable how useful this will generally be as it is generally unused / same across any modern executable)

						reinterpret_cast<PIMAGE_DOS_HEADER>(base_address)->e_lfanew = e_lfanew;
						reinterpret_cast<PIMAGE_DOS_HEADER>(base_address)->e_magic = e_magic;
					}
					else{
						
						srand(static_cast<std::uint32_t>(std::chrono::high_resolution_clock().now().time_since_epoch().count()));

						/* e_magic and e_lfanew shall be preserved as altering these can cause crashes in certain situations, the below fields are not used pass RunPE execution  */
						header_dos_ptr->e_cblp = static_cast<WORD>(__RAND__(UINT16_MAX, 0));
						header_dos_ptr->e_cparhdr = static_cast<WORD>(__RAND__(UINT16_MAX, 0));
						header_dos_ptr->e_crlc = static_cast<WORD>(__RAND__(UINT16_MAX, 0));
						header_dos_ptr->e_cs = static_cast<WORD>(__RAND__(UINT16_MAX, 0));
						header_dos_ptr->e_csum = static_cast<WORD>(__RAND__(UINT16_MAX, 0));
						header_dos_ptr->e_ip = static_cast<WORD>(__RAND__(UINT16_MAX, 0));
						header_dos_ptr->e_lfarlc = static_cast<WORD>(__RAND__(UINT16_MAX, 0));
						header_dos_ptr->e_maxalloc = static_cast<WORD>(__RAND__(UINT16_MAX, 0));
						header_dos_ptr->e_minalloc = static_cast<WORD>(__RAND__(UINT16_MAX, 0));
						header_dos_ptr->e_oemid = static_cast<WORD>(__RAND__(UINT16_MAX, 0));
						header_dos_ptr->e_oeminfo = static_cast<WORD>(__RAND__(UINT16_MAX, 0));
						header_dos_ptr->e_ovno = static_cast<WORD>(__RAND__(UINT16_MAX, 0));
						header_dos_ptr->e_sp = static_cast<WORD>(__RAND__(UINT16_MAX, 0));
						header_dos_ptr->e_ss = static_cast<WORD>(__RAND__(UINT16_MAX, 0));
					}

					if (erase_stub)
						RtlZeroMemory(reinterpret_cast<c_void>(base_address + sizeof(IMAGE_DOS_HEADER)), (header_dos_ptr->e_lfanew - sizeof(IMAGE_DOS_HEADER))); /* remove the DOS stub */

					if (!VirtualProtect(reinterpret_cast<c_void>(base_address), header_dos_ptr->e_lfanew, PAGE_READONLY, &protection_old))
						return false; // this shouldn't happen when restoring perms and if it does something is terribly wrong

					return true;
				}

				__singleton bool __stackcall scramble_nt_header(bool null_headers = false) noexcept {

#pragma region Locals Setup

					static DWORD protection = NULL;

					static noregister auto header_dos_ptr = reinterpret_cast<PIMAGE_DOS_HEADER>(base_address);
					static noregister auto header_nt_ptr = reinterpret_cast<PIMAGE_NT_HEADERS>(base_address + header_dos_ptr->e_lfanew);

#pragma endregion

					if (!VirtualProtect(reinterpret_cast<c_void>(base_address + header_dos_ptr->e_lfanew), sizeof(IMAGE_NT_HEADERS), PAGE_READWRITE, &protection))
						return false;

					if(null_headers){

						/* Windows PE Loader fails for many executables when these fields are modified, we save them and write them back after wiping the rest of the header */
						auto signature = header_nt_ptr->Signature;
						auto magic = header_nt_ptr->OptionalHeader.Magic;

						RtlZeroMemory(reinterpret_cast<c_void>(base_address + header_dos_ptr->e_lfanew), sizeof(IMAGE_NT_HEADERS));

						/* restore Signature + Magic fields */
						header_nt_ptr->Signature = std::move(signature);
						header_nt_ptr->OptionalHeader.Magic = std::move(magic);
					}
					else{

						/* signature shall be preserved as overwriting this can cause runtime exceptions w/ windows default PE Loader */

#pragma region PE32 Header

						/* override PE32 header */
						header_nt_ptr->FileHeader.Characteristics = static_cast<WORD>   ( __RAND__(UINT16_MAX, 0) );
						header_nt_ptr->FileHeader.Machine = static_cast<WORD>   (__RAND__(UINT16_MAX, 0));
						header_nt_ptr->FileHeader.NumberOfSymbols = static_cast<DWORD>  (__RAND__(UINT32_MAX, 0));
						header_nt_ptr->FileHeader.PointerToSymbolTable = static_cast<DWORD>  (__RAND__(UINT32_MAX, 0));
						header_nt_ptr->FileHeader.NumberOfSections = static_cast<WORD>	(__RAND__(UINT16_MAX, 0));
						header_nt_ptr->FileHeader.SizeOfOptionalHeader = static_cast<WORD>   (__RAND__(UINT16_MAX, 0));
						header_nt_ptr->FileHeader.TimeDateStamp = static_cast<DWORD>  (__RAND__(UINT32_MAX, 0));

#pragma endregion

#pragma region Optional Header
						/* MODIYFYING STACK RESERVE / COMMIT FIELDS CAN CAUSE RUNTIME CRASHES WHEN USING WINDOWS API */

						/* override optional header */
						header_nt_ptr->OptionalHeader.AddressOfEntryPoint = static_cast<DWORD>  (__RAND__(UINT32_MAX, 0));
						header_nt_ptr->OptionalHeader.BaseOfCode = static_cast<DWORD>  (__RAND__(UINT32_MAX, 0));
						header_nt_ptr->OptionalHeader.CheckSum = static_cast<DWORD>  (__RAND__(UINT32_MAX, 0));
						header_nt_ptr->OptionalHeader.DllCharacteristics = static_cast<WORD>   (__RAND__(UINT16_MAX, 0));
						header_nt_ptr->OptionalHeader.FileAlignment = static_cast<DWORD>  (__RAND__(UINT32_MAX, 0));

#ifdef _WIN64

						header_nt_ptr->OptionalHeader.ImageBase = static_cast<DWORD64>(__RAND__(UINT64_MAX, 0));
						header_nt_ptr->OptionalHeader.SizeOfHeapCommit = static_cast<DWORD64>(__RAND__(UINT64_MAX, 0));
						header_nt_ptr->OptionalHeader.SizeOfHeapReserve = static_cast<DWORD64>(__RAND__(UINT64_MAX, 0));

#else

						header_nt_ptr->OptionalHeader.ImageBase = static_cast<DWORD>  (__RAND__(UINT32_MAX, 0));
						header_nt_ptr->OptionalHeader.SizeOfHeapCommit = static_cast<DWORD>  (__RAND__(UINT32_MAX, 0));
						header_nt_ptr->OptionalHeader.SizeOfHeapReserve = static_cast<DWORD>  (__RAND__(UINT32_MAX, 0));

#endif

						header_nt_ptr->OptionalHeader.LoaderFlags = static_cast<DWORD>  (__RAND__(UINT32_MAX, 0));
						header_nt_ptr->OptionalHeader.MajorImageVersion = static_cast<WORD>   (__RAND__(UINT16_MAX, 0));
						header_nt_ptr->OptionalHeader.MinorImageVersion = static_cast<WORD>   (__RAND__(UINT16_MAX, 0));
						header_nt_ptr->OptionalHeader.MajorLinkerVersion = static_cast<BYTE>   (__RAND__(UINT8_MAX, 0));
						header_nt_ptr->OptionalHeader.MinorLinkerVersion = static_cast<BYTE>   (__RAND__(UINT8_MAX, 0));
						header_nt_ptr->OptionalHeader.MajorOperatingSystemVersion = static_cast<WORD>   (__RAND__(UINT16_MAX, 0));
						header_nt_ptr->OptionalHeader.MinorOperatingSystemVersion = static_cast<WORD>   (__RAND__(UINT16_MAX, 0));
						header_nt_ptr->OptionalHeader.MajorSubsystemVersion = static_cast<WORD>   (__RAND__(UINT16_MAX, 0));
						header_nt_ptr->OptionalHeader.MinorSubsystemVersion = static_cast<WORD>   (__RAND__(UINT16_MAX, 0));
						header_nt_ptr->OptionalHeader.NumberOfRvaAndSizes = static_cast<DWORD>  (__RAND__(UINT32_MAX, 0));
						header_nt_ptr->OptionalHeader.SectionAlignment = static_cast<DWORD>  (__RAND__(UINT32_MAX, 0));
						header_nt_ptr->OptionalHeader.SizeOfCode = static_cast<DWORD>  (__RAND__(UINT32_MAX, 0));
						header_nt_ptr->OptionalHeader.SizeOfHeaders = static_cast<DWORD>  (__RAND__(UINT32_MAX, 0));
						header_nt_ptr->OptionalHeader.SizeOfImage = static_cast<DWORD>  (__RAND__(UINT32_MAX, 0));
						header_nt_ptr->OptionalHeader.SizeOfInitializedData = static_cast<DWORD>  (__RAND__(UINT32_MAX, 0));
						header_nt_ptr->OptionalHeader.SizeOfUninitializedData = static_cast<DWORD>  (__RAND__(UINT32_MAX, 0));
						header_nt_ptr->OptionalHeader.Subsystem = static_cast<WORD>   (__RAND__(UINT16_MAX, 0));
						header_nt_ptr->OptionalHeader.Win32VersionValue = static_cast<DWORD>  (__RAND__(UINT32_MAX, 0));

#pragma endregion
					}

					if (!VirtualProtect(reinterpret_cast<c_void>(base_address + header_dos_ptr->e_lfanew), sizeof(IMAGE_NT_HEADERS), PAGE_READONLY, &protection))
						return false;

					// Securely Wipe Singletons
					RtlZeroMemory(&protection, sizeof(DWORD));
					RtlZeroMemory(static_cast<c_void>(volatile_cast<PIMAGE_DOS_HEADER*>(&header_dos_ptr)), sizeof(c_void));
					RtlZeroMemory(static_cast<c_void>(volatile_cast<PIMAGE_NT_HEADERS*>(&header_nt_ptr)), sizeof(c_void));

					return true;
				}

				__inlineable imut bool __stackcall wipe_basereloc() nex {

					static DWORD protection = NULL;

					static volatile PIMAGE_DOS_HEADER header_dos = static_cast<PIMAGE_DOS_HEADER>(reinterpret_cast<c_void>(base_address));
					static volatile PIMAGE_NT_HEADERS header_nt = static_cast<PIMAGE_NT_HEADERS>(reinterpret_cast<c_void>(base_address + header_dos->e_lfanew));

					static volatile PIMAGE_DATA_DIRECTORY basereloc_section = &header_nt->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_BASERELOC];

					static MODULEINFO main_module_information{};

					if (!GetModuleInformation(GetCurrentProcess(), NULL, &main_module_information, sizeof(MODULEINFO)))
						return false;

					// Check if the PE has relocation table generated, and if it was loaded into memory
					// ( If windows PE loader allocates at preffered base, relocations shouldn't be loaded into mapped image )
					if (basereloc_section->Size && (header_nt->OptionalHeader.ImageBase != reinterpret_cast<std::uintptr_t>(main_module_information.lpBaseOfDll)) ) {

						if (!VirtualProtect(reinterpret_cast<c_void>(base_address + basereloc_section->VirtualAddress), basereloc_section->Size, PAGE_READWRITE, &protection))
							return false;

						RtlZeroMemory(reinterpret_cast<c_void>(base_address + basereloc_section->VirtualAddress), basereloc_section->Size);

						if (!VirtualProtect(reinterpret_cast<c_void>(base_address + basereloc_section->VirtualAddress), basereloc_section->Size, protection, &protection))
							return false;
					}

					// Wipe basereloc DataDirectory entry 
					if (!VirtualProtect(basereloc_section, sizeof(IMAGE_DATA_DIRECTORY), PAGE_READWRITE, &protection))
						return false;

					RtlZeroMemory(basereloc_section, sizeof(IMAGE_DATA_DIRECTORY));

					if (!VirtualProtect(basereloc_section, sizeof(IMAGE_DATA_DIRECTORY), protection, &protection))
						return false;

					// Securely Wipe Singletons
					RtlZeroMemory(&protection, sizeof(DWORD));
					RtlZeroMemory(static_cast<c_void>(volatile_cast<PIMAGE_DOS_HEADER*>(&header_dos)), sizeof(c_void));
					RtlZeroMemory(static_cast<c_void>(volatile_cast<PIMAGE_NT_HEADERS*>(&header_nt)), sizeof(c_void));
					RtlZeroMemory(static_cast<c_void>(volatile_cast<PIMAGE_DATA_DIRECTORY*>(&basereloc_section)), sizeof(c_void));
					RtlZeroMemory(&main_module_information, sizeof(MODULEINFO));

					return true;
				}

				__inlineable imut bool __stackcall wipe_idata_ilt() nex {

					static DWORD protection = NULL;

					static volatile PIMAGE_DOS_HEADER header_dos = reinterpret_cast<PIMAGE_DOS_HEADER>(reinterpret_cast<c_void>(base_address));
					static volatile PIMAGE_NT_HEADERS header_nt = reinterpret_cast<PIMAGE_NT_HEADERS>(reinterpret_cast<c_void>(base_address + header_dos->e_lfanew));

					static volatile PIMAGE_DATA_DIRECTORY import_directory = &header_nt->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT];

					if(import_directory->Size) {

						if (!VirtualProtect(reinterpret_cast<c_void>(base_address + import_directory->VirtualAddress),import_directory->Size, PAGE_READWRITE, &protection))
							return false;

						static volatile PIMAGE_THUNK_DATA ilt_pointer = reinterpret_cast<PIMAGE_THUNK_DATA>(
							base_address + reinterpret_cast<PIMAGE_IMPORT_DESCRIPTOR>(base_address + import_directory->VirtualAddress)->OriginalFirstThunk
						);

						// Wipe all ILT entries
						for (; ilt_pointer->u1.Function; ++ilt_pointer)
							RtlZeroMemory(ilt_pointer, sizeof(IMAGE_THUNK_DATA));

						// Backup contents of the IAT before wiping .idata as this is the only important information post-mapping in this section
						std::vector<IMAGE_THUNK_DATA> iat_backup;

						static volatile PIMAGE_THUNK_DATA iat_pointer = reinterpret_cast<PIMAGE_THUNK_DATA>(
							base_address + reinterpret_cast<PIMAGE_IMPORT_DESCRIPTOR>(base_address + import_directory->VirtualAddress)->FirstThunk
						);

						DWORD import_protection = protection;

						for (; iat_pointer->u1.Function; ++iat_pointer) {

							iat_backup.push_back(*iat_pointer);

							// The IAT should be inside of the import section, but write access errors seem to occur here even after the initial VirtualProtect() call to the entire .idata section
							// So we call virtual protect per each write to ensure proper memory access
							if (!VirtualProtect(iat_pointer, sizeof(IMAGE_THUNK_DATA), PAGE_READWRITE, &protection))
								return false;

							RtlZeroMemory(iat_pointer, sizeof(IMAGE_THUNK_DATA));
						}

						// Reset IAT pointer to beginning
						iat_pointer = reinterpret_cast<PIMAGE_THUNK_DATA>(
							base_address + reinterpret_cast<PIMAGE_IMPORT_DESCRIPTOR>(base_address + import_directory->VirtualAddress)->FirstThunk
						);

						// Wipe the entire import(.idata) section itself 
						RtlZeroMemory(
							reinterpret_cast<c_void>(base_address + import_directory->VirtualAddress),
							import_directory->Size
						);

						// Restore the IAT to it's patched state
						for (std::size_t i = 0; i < iat_backup.size(); ++i, ++iat_pointer)
							*iat_pointer = iat_backup[i];

						// Restore memory permissions for imort section
						if (!VirtualProtect(reinterpret_cast<c_void>(base_address + import_directory->VirtualAddress), import_directory->Size, std::move(import_protection), &protection))
							return false;

						// Securely wipe nested Singletons / Locals
						RtlZeroMemory(static_cast<c_void>(volatile_cast<PIMAGE_THUNK_DATA*>(&iat_pointer)), sizeof(c_void));
						RtlZeroMemory(static_cast<c_void>(&import_protection), sizeof(DWORD));

						for (auto& iat_entry : iat_backup)
							RtlZeroMemory(&iat_entry, sizeof(IMAGE_THUNK_DATA));

						iat_backup.clear();
					}

					// Grant write access to the headers pointing to the IAT / Import Section / ILT etc. 
					if (!VirtualProtect(reinterpret_cast<c_void>(&header_nt->OptionalHeader.DataDirectory[0]), sizeof(IMAGE_DATA_DIRECTORY) * 16, PAGE_READWRITE, &protection))
						return false;

					// Wipe import section descriptor
					RtlZeroMemory(&header_nt->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT], sizeof(IMAGE_DATA_DIRECTORY));
					// Wipe IAT descriptor
					RtlZeroMemory(&header_nt->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IAT], sizeof(IMAGE_DATA_DIRECTORY));

					if (!VirtualProtect(reinterpret_cast<c_void>(&header_nt->OptionalHeader.DataDirectory[0]), sizeof(IMAGE_DATA_DIRECTORY) * 16, protection, &protection))
						return false;

					// Securely wipe Locals / Singletons
					RtlZeroMemory(&protection, sizeof(DWORD));
					RtlZeroMemory(static_cast<c_void>(volatile_cast<PIMAGE_DOS_HEADER*>(&header_dos)), sizeof(c_void));
					RtlZeroMemory(static_cast<c_void>(volatile_cast<PIMAGE_NT_HEADERS*>(&header_nt)), sizeof(c_void));
					RtlZeroMemory(static_cast<c_void>(volatile_cast<PIMAGE_DATA_DIRECTORY*>(&import_directory)), sizeof(c_void));

					return true;
				} 

				__inlineable bool __stackcall wipe_section_headers() noexcept {

#pragma region Locals Setup

					static DWORD protection = NULL;

					static volatile PIMAGE_DOS_HEADER header_dos = reinterpret_cast<PIMAGE_DOS_HEADER>(reinterpret_cast<c_void>(base_address));
					static volatile PIMAGE_NT_HEADERS header_nt = reinterpret_cast<PIMAGE_NT_HEADERS>(reinterpret_cast<c_void>(base_address + header_dos->e_lfanew));

#pragma endregion

#pragma region Wipe Section Descriptors

					static noregister PIMAGE_SECTION_HEADER section_ptr = IMAGE_FIRST_SECTION(header_nt);

					for (std::size_t i = 0; i < header_nt->FileHeader.NumberOfSections; ++i, ++section_ptr) {

						if (!VirtualProtect(static_cast<c_void>(section_ptr), sizeof(IMAGE_SECTION_HEADER), PAGE_READWRITE, &protection))
							return false;

						RtlZeroMemory(static_cast<c_void>(section_ptr), sizeof(IMAGE_SECTION_HEADER));

						if (!VirtualProtect(static_cast<c_void>(section_ptr), sizeof(IMAGE_SECTION_HEADER), protection, &protection))
							return false;

					}

#pragma endregion

					// Securely Wipe Singletons
					RtlZeroMemory(&protection, sizeof(DWORD));
					RtlZeroMemory(static_cast<c_void>(volatile_cast<PIMAGE_DOS_HEADER*>(&header_dos)), sizeof(c_void));
					RtlZeroMemory(static_cast<c_void>(volatile_cast<PIMAGE_NT_HEADERS*>(&header_nt)), sizeof(c_void));
					RtlZeroMemory(static_cast<c_void>(volatile_cast<PIMAGE_SECTION_HEADER*>(&section_ptr)), sizeof(c_void));

					return true;
				}

				__singleton void __stackcall parse_main_module_headers() noexcept {

					base_address = reinterpret_cast<std::uintptr_t>(GetModuleHandle(NULL));

					static noregister PIMAGE_DOS_HEADER header_dos = reinterpret_cast<PIMAGE_DOS_HEADER>(reinterpret_cast<c_void>(base_address));

					static noregister PIMAGE_NT_HEADERS headers_nt = reinterpret_cast<PIMAGE_NT_HEADERS>(reinterpret_cast<c_void>(base_address + header_dos->e_lfanew));

					static noregister auto section_ptr = IMAGE_FIRST_SECTION(headers_nt);

					for (std::size_t i = 0; i < headers_nt->FileHeader.NumberOfSections; ++i, ++section_ptr) {

						if (section_ptr->Characteristics & IMAGE_SCN_CNT_CODE) { // section contains executable code ?

							std::string section_name_str(reinterpret_cast<char*>(&section_ptr->Name)); // we only want to modify .text and (if applicable) twin regions

							if (section_name_str.find(".text") != std::string::npos) {

								if (section_ptr->SizeOfRawData) { // some compilers (e.g clang) will generate extensions of .text and sometimes these are flagged for executable code yet have size of 0x0, check

									executable_sections.push_back(
										executable_text_section{ section_ptr } // add the section to our vector as it contains valid executable machine code
									);

								}
							}
						}
						else {
							pe_other_sections.push_back(volatile_cast<IMAGE_SECTION_HEADER*>(section_ptr));
						}
					}
				}

#pragma endregion


#pragma region Ctor / Dtor

				__inlineable __stackcall qsection_assembler() noexcept {

					parse_main_module_headers();
				}

				/*
				mut std::vector<PIMAGE_SECTION_HEADER> pe_other_sections{};
				mut std::vector<interrupt_region> pe_interrupt_regions{};
				*/

				__inlineable __stackcall ~qsection_assembler() noexcept {

					if (handle)
						cs_close(&handle);

					RtlZeroMemory(&mode, sizeof(cs_mode));
					RtlZeroMemory(&arch, sizeof(cs_arch));
					RtlZeroMemory(&base_address, sizeof(std::uintptr_t));

					for (auto& executable_section : executable_sections) {

						for (auto& interrupt_mapping : executable_section.interrupt_mapping) {

							for (auto& _interrupt_permutator : interrupt_mapping.region_instructions)
								RtlZeroMemory(&_interrupt_permutator, sizeof(interrupt_permutator));

							RtlZeroMemory(&interrupt_mapping, sizeof(interrupt_region));
						}

						RtlZeroMemory(&executable_section, sizeof(executable_text_section));
					}

					for (auto& pscn_header : pe_other_sections)
						RtlZeroMemory(static_cast<c_void>(&pscn_header), sizeof(c_void));

					for (auto& interrupt_mapping : pe_interrupt_regions) {

						for (auto& _interrupt_permutator : interrupt_mapping.region_instructions)
							RtlZeroMemory(&_interrupt_permutator, sizeof(interrupt_permutator));

						RtlZeroMemory(&interrupt_mapping, sizeof(interrupt_region));
					}
				}

#pragma endregion

			};
		}
	}
}

#endif
