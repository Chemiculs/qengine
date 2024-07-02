#pragma region Header Guard

#ifndef QMAP_H
#define QMAP_H

#pragma endregion

#pragma region Imports

#pragma region qengine

#include "../qbase/qdef.hpp"

#pragma endregion

#pragma region std

#include <fstream>
#include <string>

#pragma endregion

#pragma endregion

#pragma region Namespacing

namespace qengine{

    namespace import{

#pragma endregion

        class qmap{
            
            private:

                // For DLL's manually loaded from disk
                imut char* _dll_path;
                // For manual load DLL's embedded in the executable as byte array etc. only
                imut c_void _dll_memory_map;
                // Size of above allocation ( if applicable )
                imut std::size_t _dll_memory_map_sz;
                // PE header / section reference pointers, while unnecessary these are subject to change and are marked volatile likewise
                mut volatile PIMAGE_DOS_HEADER _pdos_header;
                mut volatile PIMAGE_NT_HEADERS _pnt_headers;
                mut volatile PIMAGE_SECTION_HEADER _psection_headers;

                static __inlineable imut std::unique_ptr<std::uint8_t[]> __regcall get_file_memory_map(imut char* dll_path) nex {

                    if(!dll_path) 
                        return nullptr;

                    std::fstream stream(dll_path, std::ios::in | std::ios::binary);
                    if(!stream.is_open())
                        return nullptr;
                    //  Get file size
                    stream.seekg(0, std::ios::end);

                    imut std::size_t dll_sz = stream.tellg();

                    // Allocate memory for DLL
                    auto dll_alloc = new std::uint8_t[ std::move(dll_sz) ];
                    if(!dll_alloc)
                        return nullptr;

                    // Reset stream position
                    stream.seekg(0, std::ios::beg); 
                    // Read file into memory
                    stream.read((char*)dll_alloc, dll_sz);

                    stream.close();

                    return std::unique_ptr<std::uint8_t[]>(dll_alloc);   
                }

                static __inlineable volatile c_void __regcall get_dll_relocated_map( 

                        imut c_void dll_abs, 
                        imut std::size_t dll_sz, 
                        std::size_t* dll_sz_mapped = nullptr,
                        PIMAGE_DOS_HEADER __pdos_header = nullptr, 
                        PIMAGE_NT_HEADERS __nt_headers = nullptr, 
                        PIMAGE_SECTION_HEADER __section_headers = nullptr
                    ) nex {

                    if(!dll_abs || !dll_sz)
                        return nullptr;
                    // Parse DOS header
                    imut PIMAGE_DOS_HEADER pdos_header = reinterpret_cast<PIMAGE_DOS_HEADER>(dll_abs);
                    if(pdos_header->e_magic!= IMAGE_DOS_SIGNATURE)
                        return nullptr;

                    if(__pdos_header)
                        __pdos_header = pdos_header;
                    //Parse NT headers
                    imut PIMAGE_NT_HEADERS pnt_headers = reinterpret_cast<volatile PIMAGE_NT_HEADERS>(reinterpret_cast<std::uintptr_t>(dll_abs) + pdos_header->e_lfanew);
                    if(pnt_headers->Signature!= IMAGE_NT_SIGNATURE)
                        return nullptr;

                    if(__nt_headers)
                        __nt_headers = pnt_headers;
                    // Attempt allocation at preferred base address
                    volatile c_void mapped_dll_alloc = static_cast<volatile c_void>(
                        VirtualAlloc( (volatile c_void)pnt_headers->OptionalHeader.ImageBase, pnt_headers->OptionalHeader.SizeOfImage, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE)
                    );
                    if(!mapped_dll_alloc)
                        if(!(mapped_dll_alloc = static_cast<volatile c_void>(
                                VirtualAlloc( nullptr, pnt_headers->OptionalHeader.SizeOfImage, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE)
                            ))) // Allocate at rendomized base address if the preferred is unavailable
                                return nullptr;

                    if(dll_sz_mapped)
                        *dll_sz_mapped = pnt_headers->OptionalHeader.SizeOfImage;

                    // Copy PE + Section headers
                    memcpy(const_cast<c_void>(mapped_dll_alloc), dll_abs, pdos_header->e_lfanew + sizeof(IMAGE_NT_HEADERS) + sizeof(IMAGE_SECTION_HEADER) * pnt_headers->FileHeader.NumberOfSections);

                    PIMAGE_SECTION_HEADER scn_iterator = static_cast<PIMAGE_SECTION_HEADER>(
                        IMAGE_FIRST_SECTION(pnt_headers)
                    );
                    // Copy sections
                    for(int i = 0 ; i < pnt_headers->FileHeader.NumberOfSections; ++i, ++scn_iterator)
                        if(!scn_iterator->SizeOfRawData)
                            continue;
                        else
                            memcpy(
                                reinterpret_cast<c_void>(
                                    reinterpret_cast<std::uintptr_t>(mapped_dll_alloc) + scn_iterator->VirtualAddress),
                                reinterpret_cast<c_void>(
                                    reinterpret_cast<std::uintptr_t>(dll_abs) + scn_iterator->PointerToRawData),
                                scn_iterator->SizeOfRawData
                            );
                    // Check if relocations are necessary
                    if(reinterpret_cast<std::uintptr_t>(mapped_dll_alloc) != pnt_headers->OptionalHeader.ImageBase) {
                        
                        imut std::intptr_t delta = static_cast<std::intptr_t>(pnt_headers->OptionalHeader.ImageBase - reinterpret_cast<std::uintptr_t>(mapped_dll_alloc));
                        // Check if the PE has a relocation section, and apply relocations
                        if(pnt_headers->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_BASERELOC].Size){

                            PIMAGE_BASE_RELOCATION preloc_table = reinterpret_cast<PIMAGE_BASE_RELOCATION>( 
                                reinterpret_cast<std::uintptr_t>(mapped_dll_alloc) + pnt_headers->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_BASERELOC].VirtualAddress
                            );

                            do{

                                PWORD block_iter = reinterpret_cast<PWORD>(  reinterpret_cast<std::uintptr_t>(preloc_table) + sizeof(IMAGE_BASE_RELOCATION) );

                                for(auto i = 0; i < preloc_table->SizeOfBlock / sizeof(WORD); ++i, ++block_iter){
                                    
                                    imut std::uint16_t type = (*block_iter & 0xF000ui16) >> 12;
                                    imut std::uint16_t offset = *block_iter & 0x0FFFui16;

                                    if(type == IMAGE_REL_BASED_HIGHLOW)
                                        *reinterpret_cast<PDWORD>(reinterpret_cast<std::uintptr_t>(mapped_dll_alloc) + preloc_table->VirtualAddress + offset) += delta;
                                    if(type == IMAGE_REL_BASED_DIR64)
                                        *reinterpret_cast<PDWORD64>(reinterpret_cast<std::uintptr_t>(mapped_dll_alloc) + preloc_table->VirtualAddress + offset) += delta;
                                    if(type == IMAGE_REL_BASED_HIGH)
                                        *reinterpret_cast<PWORD>(reinterpret_cast<std::uintptr_t>(mapped_dll_alloc) + preloc_table->VirtualAddress + offset) += static_cast<WORD>(delta & 0xFFFF0000);
                                    if(type == IMAGE_REL_BASED_LOW)
                                        *reinterpret_cast<PWORD>(reinterpret_cast<std::uintptr_t>(mapped_dll_alloc) + preloc_table->VirtualAddress + offset) += static_cast<WORD>(delta & 0x0000FFFF);
                                }

                                preloc_table += preloc_table->SizeOfBlock;   

                            } while(preloc_table->SizeOfBlock) ;
                        }
                    }

#ifdef _WIN64

                    static imut constexpr char* api_base_dir64 = "C:\\Windows\\System32\\";
                    static imut constexpr char* api_base_dir32 = "C:\\Windows\\SysWOW64\\";

#else

                    static imut constexpr char* api_base_dir32 = "C:\\Windows\\System32\\";

#endif

                    // Load imported DLL's into process address space
                    if(pnt_headers->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].Size) {

                        
                    }


                    return mapped_dll_alloc;
                }

                static __inlineable imut bool __regcall resolve_iat() noexcept {


                }

            public:

#pragma region Ctor / Dtor

                __optimized_ctor qmap(imut char* dll_path) 
                nex  : _dll_path(dll_path), _dll_memory_map(nullptr), _dll_memory_map_sz(NULL) {


                }

                __optimized_ctor qmap(imut c_void dll_abs, imut std::size_t dll_sz)
                 nex : _dll_memory_map(dll_abs), _dll_path(nullptr), _dll_memory_map_sz(dll_sz) {


                }

                ~qmap();

#pragma endregion 

        };

#pragma region Namespacing

    }
}

#pragma endregion

#pragma region Header Guard

#endif

#pragma endregion