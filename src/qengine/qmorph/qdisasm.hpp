#ifndef DISASM_H
#define DISASM_H

#pragma region Imports

#include <Windows.h>

#include <random>
#include <chrono>
#include <string>
#include <memory>
#include <vector>
#include <climits>

#include "qgen.hpp"

#include "../extern/capstone/include/capstone/capstone.h"

#pragma region Preprocessor

#ifdef _WIN64

#pragma comment(lib, "capstone64.lib")

#elif defined(_WIN32)

#pragma comment(lib, "capstone32.lib")

#endif

#pragma endregion

#pragma endregion

/* utilizing this class may render VM-based protection solutions un-usable */
namespace qengine {

	namespace qdisasm {

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

			typedef struct interrupt_permutator { // instruction length is always going to be 1 byte so no need for additional field
				void* instruction_address;
				byte iterator_seed;
			};

			typedef struct interrupt_region {
				void* region_address;
				uint32_t region_length;
				uint32_t region_parent_section; // index of parent inside executable_sections vector
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

			cs_mode mode = CS_MODE_64;

#else

			cs_mode mode = CS_MODE_32;

#endif

			cs_arch arch = cs_arch::CS_ARCH_X86;
			csh handle;
			uintptr_t base_address;

			std::vector<executable_text_section> executable_sections{};
			std::vector<PIMAGE_SECTION_HEADER> pe_other_sections{};
			std::vector<interrupt_region> pe_interrupt_regions{};

#pragma endregion

#pragma region Permutation Functions

			__inlineable std::int32_t __regcall get_permutation_index(std::uint8_t original_instruction) noexcept {
				switch (original_instruction) {
					case (BYTE)instruction_permutations::INT1: {
						return 0;
						break;
					}
					case (BYTE)instruction_permutations::INT3: {
						return 1;
						break;
					}
					case (BYTE)instruction_permutations::NOP: {
						return 2;
						break;
					}
				}

				return NULL;
			}

			__inlineable instruction_permutations __regcall get_permutation_instruction(std::uint32_t index) noexcept {

				instruction_permutations _return{};

				switch (index) {
					case 0: {
						_return = INT1;
						break;
					}
					case 1: {
						_return = INT3;
						break;
					}
					case 2: {
						_return = NOP;
						break;
					}
				}

				return _return;
			}

		public:

			/* specify __regcall should the compiler choose to optimize the argument as a pointer (to fit register) */
			__inlineable void __regcall instruction_permutation(interrupt_region& region) noexcept {
				DWORD protection{};

				if (!VirtualProtect(region.region_address, region.region_length, PAGE_EXECUTE_READWRITE, &protection))
					throw std::bad_variant_access();

				void* alloc_gen;
				
				if ( (alloc_gen = qgen::asm_generator::generate_assembly(region.region_length)) ) { // generate junk instructions to replace the padding
				
					memcpy(region.region_address, alloc_gen, region.region_length);

					free(alloc_gen);

				}
				
				if (!VirtualProtect(region.region_address, region.region_length, protection, &protection))
					throw std::bad_alloc();
			}

			/* if you erase / randomize headers before calling this the function will fail and your program will crash */
			__inlineable bool __stackcall analyze_executable_sections() noexcept {
				if (cs_open(arch, mode, &handle) != CS_ERR_OK) // initialize capstone with our target architecture using our handle
					throw std::bad_alloc();

				// VirtualProtect Shit
				DWORD original_protect = PAGE_EXECUTE_READ, modified_protect = PAGE_EXECUTE_READWRITE, temporary_protect{}; // used to set / get virtualprotect permissions for applicable memory pages



				// Seeded random number generation 
				auto permutation_seed = static_cast<uintptr_t>(std::chrono::high_resolution_clock::now().time_since_epoch().count());
				std::default_random_engine generator(permutation_seed);
				std::uniform_int_distribution<WORD> distribution(0, 2); // random indices 0-2 as we have three usable permutations

				for (auto& section : executable_sections) {

					auto offset = reinterpret_cast<PBYTE>(base_address + section.section_header->VirtualAddress);
					auto& maximum = section.section_header->SizeOfRawData;

					if (!VirtualProtect(reinterpret_cast<void*>(offset), maximum, modified_protect, &temporary_protect))
						return false;

					cs_insn* instructions;

					size_t instruction_count = cs_disasm(handle, offset, maximum, reinterpret_cast<uintptr_t>(offset), maximum, &instructions);

					for (size_t i = 0; i < instruction_count; ++i) {
						const auto& instruction = instructions[i]; // forward subscript to speed up
						if (instruction.id == X86_INS_INT1 || instruction.id == X86_INS_INT3) {

							interrupt_region region{};
							region.region_address = reinterpret_cast<void*>(instruction.address);
							region.region_parent_section = i;
							region.region_length = static_cast<uint32_t>(0x00);

							bool region_continuation = true;
							PBYTE region_iterator = reinterpret_cast<PBYTE>(instruction.address);
							BYTE region_iteration_instruction;

							do {
								region_iteration_instruction = *reinterpret_cast<PBYTE>(region_iterator);

								if (region_iteration_instruction == instruction_permutations::INT3 || region_iteration_instruction == instruction_permutations::INT1) {

									interrupt_permutator interrupt_instruction;
									interrupt_instruction.instruction_address = reinterpret_cast<void*>(region_iterator); // address / pointer to instruction
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

					if (!VirtualProtect(reinterpret_cast<void*>(offset), maximum, original_protect, &temporary_protect))
						throw std::bad_alloc(); // this should not occur when rstoring page perms even if mid-execution, something is not right

				}
				return true;
			}

			__inlineable bool __regcall morph_executable_sections(bool free_memory = true) noexcept {

				if (!pe_interrupt_regions.size())
					return false;

				for (auto& region : pe_interrupt_regions)
					instruction_permutation(region);

				if (free_memory)
					pe_interrupt_regions.clear();

				return true;
			}

#pragma endregion

#pragma region PE Header Manipulation

			__inlineable bool __stackcall zero_dos_header(bool erase_stub = true) noexcept {

				DWORD protection_old{};

				if (!VirtualProtect(reinterpret_cast<void*>(base_address), sizeof(IMAGE_DOS_HEADER), PAGE_READWRITE, &protection_old))
					return false;

				/* preserve e_lfanew && e_magic so that the exit() call will not throw an exception, for some reason windows checks both of these past it's RunPE exeution */
				auto e_lfanew = reinterpret_cast<PIMAGE_DOS_HEADER>(base_address)->e_lfanew;
				auto e_magic = reinterpret_cast<PIMAGE_DOS_HEADER>(base_address)->e_magic;

				RtlZeroMemory(reinterpret_cast<void*>(base_address + sizeof(IMAGE_DOS_HEADER)), e_lfanew - sizeof(IMAGE_DOS_HEADER)); // e_lfanew - 1 will also erase the dos stub (debatable how useful this will generally be as it is generally unused / same across any modern executable)

				reinterpret_cast<PIMAGE_DOS_HEADER>(base_address)->e_lfanew = e_lfanew;
				reinterpret_cast<PIMAGE_DOS_HEADER>(base_address)->e_magic = e_magic;

				if (!VirtualProtect(reinterpret_cast<void*>(base_address), sizeof(IMAGE_DOS_HEADER), PAGE_READONLY, &protection_old))
					throw std::bad_alloc(); // this shouldn't happen when restoring perms and if it does something is terribly wrong so throw badalloc()

				return true;
			}

			__inlineable bool __stackcall scramble_dos_header(bool erase_stub = true) noexcept {

#pragma region Locals Setup

				DWORD protection_old{};

				// Seeded random number generation 
				auto integer_seed = static_cast<uintptr_t>(std::chrono::high_resolution_clock::now().time_since_epoch().count());

				std::default_random_engine generator(integer_seed);
				std::uniform_int_distribution<WORD> word_distribution(0, UINT16_MAX); // WORD / UINT16 generation for our header

				auto header_dos_ptr = reinterpret_cast<PIMAGE_DOS_HEADER>(base_address);

#pragma endregion

				if (!VirtualProtect(reinterpret_cast<void*>(base_address), header_dos_ptr->e_lfanew, PAGE_READWRITE, &protection_old))
					return false;

				/* e_magic and e_lfanew shall be preserved as altering these can cause crashes in certain situations, the below fields are not used pass RunPE execution  */
				header_dos_ptr->e_cblp = static_cast<WORD>(word_distribution(generator));
				header_dos_ptr->e_cparhdr = static_cast<WORD>(word_distribution(generator));
				header_dos_ptr->e_crlc = static_cast<WORD>(word_distribution(generator));
				header_dos_ptr->e_cs = static_cast<WORD>(word_distribution(generator));
				header_dos_ptr->e_csum = static_cast<WORD>(word_distribution(generator));
				header_dos_ptr->e_ip = static_cast<WORD>(word_distribution(generator));
				header_dos_ptr->e_lfarlc = static_cast<WORD>(word_distribution(generator));
				header_dos_ptr->e_maxalloc = static_cast<WORD>(word_distribution(generator));
				header_dos_ptr->e_minalloc = static_cast<WORD>(word_distribution(generator));
				header_dos_ptr->e_oemid = static_cast<WORD>(word_distribution(generator));
				header_dos_ptr->e_oeminfo = static_cast<WORD>(word_distribution(generator));
				header_dos_ptr->e_ovno = static_cast<WORD>(word_distribution(generator));
				header_dos_ptr->e_sp = static_cast<WORD>(word_distribution(generator));
				header_dos_ptr->e_ss = static_cast<WORD>(word_distribution(generator));


				//scylla is reconstructing headers from disk image
				if (erase_stub)
					RtlZeroMemory(reinterpret_cast<void*>(base_address + sizeof(IMAGE_DOS_HEADER)), (header_dos_ptr->e_lfanew - sizeof(IMAGE_DOS_HEADER))); /* remove the DOS stub */

				if (!VirtualProtect(reinterpret_cast<void*>(base_address), header_dos_ptr->e_lfanew, PAGE_READONLY, &protection_old))
					throw std::bad_alloc(); // this shouldn't happen when restoring perms and if it does something is terribly wrong so throw badalloc()

				return true;
			}

			__inlineable bool __stackcall zero_nt_header() noexcept {

				DWORD protection_old{};

				auto header_dos_ptr = reinterpret_cast<PIMAGE_DOS_HEADER>(base_address);
				auto header_nt_ptr = reinterpret_cast<PIMAGE_NT_HEADERS>(base_address + header_dos_ptr->e_lfanew);

				if (!VirtualProtect(reinterpret_cast<void*>(base_address + header_dos_ptr->e_lfanew), sizeof(IMAGE_NT_HEADERS), PAGE_READWRITE, &protection_old))
					return false;

				/* preserve these values to write them back after zeroing memory */
				auto signature = header_nt_ptr->Signature;
				auto magic = header_nt_ptr->OptionalHeader.Magic;

				RtlZeroMemory(reinterpret_cast<void*>(base_address + header_dos_ptr->e_lfanew), sizeof(IMAGE_NT_HEADERS));
				/* restore signature + magic fields */
				header_nt_ptr->Signature = signature;
				header_nt_ptr->OptionalHeader.Magic = magic;

				if (!VirtualProtect(reinterpret_cast<void*>(base_address + header_dos_ptr->e_lfanew), sizeof(IMAGE_NT_HEADERS), PAGE_READONLY, &protection_old))
					throw std::bad_alloc();

				return true;

			}

			__inlineable bool __stackcall scramble_nt_header() noexcept {

#pragma region Locals Setup

				DWORD protection_old{};

				auto integer_seed = static_cast<uintptr_t>(std::chrono::high_resolution_clock::now().time_since_epoch().count());

				std::default_random_engine generator(integer_seed);
				std::uniform_int_distribution<WORD> word_distribution(0, UINT16_MAX); // WORD / UINT16 generation for our header
				std::uniform_int_distribution<DWORD> dword_distribution(0, UINT32_MAX); // DWORD / UINT32 generation for our header

#ifdef _WIN64

				std::uniform_int_distribution<DWORD64> dword64_distribution(0, UINT64_MAX);

#endif

				auto header_dos_ptr = reinterpret_cast<PIMAGE_DOS_HEADER>(base_address);
				auto header_nt_ptr = reinterpret_cast<PIMAGE_NT_HEADERS>(base_address + header_dos_ptr->e_lfanew);

#pragma endregion

				if (!VirtualProtect(reinterpret_cast<void*>(base_address + header_dos_ptr->e_lfanew), sizeof(IMAGE_NT_HEADERS), PAGE_READWRITE, &protection_old))
					return false;

				/* signature shall be preserved as overwriting this can cause runtime exceptions */

#pragma region PE32 Header

				/* override PE32 header */
				header_nt_ptr->FileHeader.Characteristics = static_cast<WORD>   (word_distribution(generator));
				header_nt_ptr->FileHeader.Machine = static_cast<WORD>   (word_distribution(generator));
				header_nt_ptr->FileHeader.NumberOfSymbols = static_cast<DWORD>  (dword_distribution(generator));
				header_nt_ptr->FileHeader.PointerToSymbolTable = static_cast<DWORD>  (dword_distribution(generator));
				header_nt_ptr->FileHeader.NumberOfSections = static_cast<WORD>	(word_distribution(generator));
				header_nt_ptr->FileHeader.SizeOfOptionalHeader = static_cast<WORD>   (word_distribution(generator));
				header_nt_ptr->FileHeader.TimeDateStamp = static_cast<DWORD>  (dword_distribution(generator));

#pragma endregion

#pragma region Optional Header
				/* MODIYFYING STACK RESERVE / COMMIT FIELDS CAN CAUSE RUNTIME CRASHES WHEN USING WINDOWS API */

				/* override optional header */
				header_nt_ptr->OptionalHeader.AddressOfEntryPoint = static_cast<DWORD>  (dword_distribution(generator));
				header_nt_ptr->OptionalHeader.BaseOfCode = static_cast<DWORD>  (dword_distribution(generator));
				header_nt_ptr->OptionalHeader.CheckSum = static_cast<DWORD>  (dword_distribution(generator));
				header_nt_ptr->OptionalHeader.DllCharacteristics = static_cast<WORD>   (word_distribution(generator));
				header_nt_ptr->OptionalHeader.FileAlignment = static_cast<DWORD>  (dword_distribution(generator));

#ifdef _WIN64

				header_nt_ptr->OptionalHeader.ImageBase = static_cast<DWORD64>(dword64_distribution(generator));
				header_nt_ptr->OptionalHeader.SizeOfHeapCommit = static_cast<DWORD64>(dword64_distribution(generator));
				header_nt_ptr->OptionalHeader.SizeOfHeapReserve = static_cast<DWORD64>(dword64_distribution(generator));

#else

				header_nt_ptr->OptionalHeader.ImageBase = static_cast<DWORD>  (dword_distribution(generator));
				header_nt_ptr->OptionalHeader.SizeOfHeapCommit = static_cast<DWORD>  (dword_distribution(generator));
				header_nt_ptr->OptionalHeader.SizeOfHeapReserve = static_cast<DWORD>  (dword_distribution(generator));

#endif

				header_nt_ptr->OptionalHeader.LoaderFlags = static_cast<DWORD>  (dword_distribution(generator));
				header_nt_ptr->OptionalHeader.MajorImageVersion = static_cast<WORD>   (word_distribution(generator));
				header_nt_ptr->OptionalHeader.MinorImageVersion = static_cast<WORD>   (word_distribution(generator));
				header_nt_ptr->OptionalHeader.MajorLinkerVersion = static_cast<BYTE>   (LOBYTE(word_distribution(generator)));
				header_nt_ptr->OptionalHeader.MinorLinkerVersion = static_cast<BYTE>   (LOBYTE(word_distribution(generator)));
				header_nt_ptr->OptionalHeader.MajorOperatingSystemVersion = static_cast<WORD>   (word_distribution(generator));
				header_nt_ptr->OptionalHeader.MinorOperatingSystemVersion = static_cast<WORD>   (word_distribution(generator));
				header_nt_ptr->OptionalHeader.MajorSubsystemVersion = static_cast<WORD>   (word_distribution(generator));
				header_nt_ptr->OptionalHeader.MinorSubsystemVersion = static_cast<WORD>   (word_distribution(generator));
				header_nt_ptr->OptionalHeader.NumberOfRvaAndSizes = static_cast<DWORD>  (dword_distribution(generator));
				header_nt_ptr->OptionalHeader.SectionAlignment = static_cast<DWORD>  (dword_distribution(generator));
				header_nt_ptr->OptionalHeader.SizeOfCode = static_cast<DWORD>  (dword_distribution(generator));
				header_nt_ptr->OptionalHeader.SizeOfHeaders = static_cast<DWORD>  (dword_distribution(generator));
				header_nt_ptr->OptionalHeader.SizeOfImage = static_cast<DWORD>  (dword_distribution(generator));
				header_nt_ptr->OptionalHeader.SizeOfInitializedData = static_cast<DWORD>  (dword_distribution(generator));
				header_nt_ptr->OptionalHeader.SizeOfUninitializedData = static_cast<DWORD>  (dword_distribution(generator));
				header_nt_ptr->OptionalHeader.Subsystem = static_cast<WORD>   (word_distribution(generator));
				header_nt_ptr->OptionalHeader.Win32VersionValue = static_cast<DWORD>  (dword_distribution(generator));

#pragma endregion

				if (!VirtualProtect(reinterpret_cast<void*>(base_address + header_dos_ptr->e_lfanew), sizeof(IMAGE_NT_HEADERS), PAGE_READONLY, &protection_old))
					throw std::bad_alloc(); // We should not encounter an issue here restoring permissions, if so something is terribly wrong

				return true;
			}

			__inlineable bool __stackcall zero_information_sections() noexcept {

#pragma region Locals Setup

				DWORD protection_old{};

				PIMAGE_DOS_HEADER header_dos = reinterpret_cast<PIMAGE_DOS_HEADER>(reinterpret_cast<void*>(base_address));
				PIMAGE_NT_HEADERS header_nt = reinterpret_cast<PIMAGE_NT_HEADERS>(reinterpret_cast<void*>(base_address + header_dos->e_lfanew));

				auto& import_directory = header_nt->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT];
				auto& iat_directory = header_nt->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IAT];

#pragma endregion

#pragma region IAT Descriptor Wipe

				if (!VirtualProtect(reinterpret_cast<void*>(&header_nt->OptionalHeader.DataDirectory[0]), sizeof(IMAGE_DATA_DIRECTORY) * 16, PAGE_READWRITE, &protection_old))
					return false;

				void* iat_descriptor_ptr = &iat_directory;

				RtlZeroMemory(iat_descriptor_ptr, sizeof(IMAGE_DATA_DIRECTORY));

#pragma endregion

#pragma region Import Table Data Wipe

				if (import_directory.VirtualAddress) {

					if (!VirtualProtect(reinterpret_cast<void*>(base_address + import_directory.VirtualAddress), import_directory.Size, PAGE_READWRITE, &protection_old))
						return false;

					RtlZeroMemory(reinterpret_cast<void*>(base_address + import_directory.VirtualAddress), import_directory.Size);

					if (!VirtualProtect(reinterpret_cast<void*>(base_address + import_directory.VirtualAddress), import_directory.Size, PAGE_READONLY, &protection_old))
						throw std::bad_alloc();

				}

#pragma endregion

#pragma region Import Table Descriptor Wipe

				/* import_directory was instanced by reference for performance so we wait till done using it to wipe the pointers directly */
				void* import_descriptor_ptr = &import_directory;

				RtlZeroMemory(import_descriptor_ptr, sizeof(IMAGE_DATA_DIRECTORY));

				/* Restore perms to the data directory as we are done writing to it */
				if (!VirtualProtect(reinterpret_cast<void*>(import_descriptor_ptr), sizeof(IMAGE_DATA_DIRECTORY) * 16, PAGE_READONLY, &protection_old))
					throw std::bad_alloc();

#pragma endregion

#pragma region Relocation Section Wipe

				/* wipe relocations */
				for (auto& section : pe_other_sections) {
					std::string section_name_str(reinterpret_cast<char*>(&section->Name)); // we only want to modify .text and (if applicable) twin regions

					if ((section_name_str.find(".reloc") != std::string::npos))
					{
						if (!VirtualProtect(reinterpret_cast<void*>(base_address + section->VirtualAddress), section->SizeOfRawData, PAGE_READWRITE, &protection_old))
							return false;

						RtlZeroMemory(reinterpret_cast<void*>(base_address + section->VirtualAddress), section->SizeOfRawData);

						if (!VirtualProtect(reinterpret_cast<void*>(base_address + section->VirtualAddress), section->SizeOfRawData, PAGE_READONLY, &protection_old))
							throw std::bad_alloc();
					}
				}

#pragma endregion

#pragma region Wipe Section Descriptors

				auto section_ptr = IMAGE_FIRST_SECTION(header_nt);

				for (auto i = 0; i < header_nt->FileHeader.NumberOfSections; ++i, ++section_ptr) {

					if (!VirtualProtect(reinterpret_cast<void*>(section_ptr), sizeof(IMAGE_SECTION_HEADER), PAGE_READWRITE, &protection_old))
						return false;

					RtlZeroMemory(reinterpret_cast<void*>(section_ptr), sizeof(IMAGE_SECTION_HEADER));

					if (!VirtualProtect(reinterpret_cast<void*>(section_ptr), sizeof(IMAGE_SECTION_HEADER), PAGE_READONLY, &protection_old))
						throw std::bad_alloc();

				}

#pragma endregion

				return true;
			}

			__inlineable void __stackcall parse_main_module_headers() noexcept {

				base_address = reinterpret_cast<uintptr_t>(GetModuleHandle(NULL));

				PIMAGE_DOS_HEADER header_dos = reinterpret_cast<PIMAGE_DOS_HEADER>(reinterpret_cast<void*>(base_address));

				PIMAGE_NT_HEADERS headers_nt = reinterpret_cast<PIMAGE_NT_HEADERS>(reinterpret_cast<void*>(base_address + header_dos->e_lfanew));

				auto section_ptr = IMAGE_FIRST_SECTION(headers_nt);

				for (auto i = 0; i < headers_nt->FileHeader.NumberOfSections; ++i, ++section_ptr) {

					if ((section_ptr->Characteristics & IMAGE_SCN_CNT_CODE) == IMAGE_SCN_CNT_CODE) { // section contains executable code ?

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
						pe_other_sections.push_back(section_ptr);
					}
				}
			}

#pragma endregion


#pragma region Ctor / Dtor

			__inlineable __stackcall qsection_assembler() noexcept {
				parse_main_module_headers();
			}

			__inlineable __stackcall ~qsection_assembler() noexcept {

				if (handle)
					cs_close(&handle);
			}

#pragma endregion

		};
	}
}

#endif
