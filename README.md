# - qengine - 

Easy to use and highly configurable, compiler-independent, fully inlined binary obfuscation for C++ windows applications

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

## Features

* Runtime stack polymorphism (locals will be manipulated directly on the stack and appear differently each execution, not really a big deal as this happens in most applications anyways)
* Runtime heap polymorphism (dynamic polymorphic allocations are supported, not a big deal as above)
* Thorough control-flow obfuscation (depending on compiler used and amount of library types used, IDA control-flow graph will be extremely difficult to read and in many cases fail pseudo-code generation)
* Cumbersome conditional branching (extended memory check obfuscation e.g create indirection for checking valuable information such as product keys etc.)
* .text / executable section Polymorphism (.text section dumps will appear different at each runtime which would hypothetically prevent basic static .text dump signature scans by AV's / AC's etc.)
* PE header wipe / mutation (headers will be wiped or appear different at each runtime)

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

## What is qengine?

qengine is a polymorphic engine (meaning an engine that takes multiple forms / permutations) for windows with the end goal of making the reverse engineers day much more difficult, and making the binary appear as unique as possible and unrecognizable at each independent runtime.

i couldn't find a good solution - llvm-obfuscator only supports llvm / clang, vmprotect / themida are proprietary solutions which offer little in terms of control over the process of obfuscation and other options tend to have the same issue - 

i couldn't control the way my binary was obfuscated the ways in which i wanted to.

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

This library is fairly well tested (considering i am a one-man team) - i currently am unaware of any bugs for LLVM / CLANG, MSVC, and Intel compiler targets for both x86 and x64 release builds.

This will NOT prevent static disk-signatures of your executables - however, it will make the task of understanding your code from a classic disassembler such as IDA nearly impossible if used properly, and will prevent memory-dump / memory-scan based signature detections of your binary.

This class is fully inlined, employing minimalist design and maximum performance + reliability -

Obfuscation and polymorphism can be heavy in terms of performance cost, howver on 

~1.70% average performance loss vs standard library / primitive types, likewise you will retain ~98.3% of your programs original performance ( on average )

If anyone is able to contribute detailed benchmarks if they have the time, this would be extremely helpful - my hands are tied when it comes to free time for this project at the moment.

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

## Usage

* Download the repository as a zip file, and extract the qengine folder to your project's main / root directory
* Include the qengine header file contained in <root_directory>/qengine/engine/

### Hello World

here is the obligatory "Hello World" for qengine:

```cpp
#include <iostream>

#include "qengine/engine/qengine.hpp"

using namespace qengine;

int main() {
	std::cout << qenc_t::e_string("Hello World!").get() << std::endl; // dynamically encrypted type(s)

	std::cout << qhash_t::h_string("Hello World!").get() << std::endl; // secured / hash-checked type(s)

	std::cout << qenc_h_t::q_string("Hello World!").get() << std::endl; // dynamically encrypted AND hash-checked type(s)

	std::cin.get();

	return 0;
}
```

--------------------------------------------------------------------------------------

Demonstration of control flow obfuscation:
__-- Basic "Hello, World!" application before polymorphic type --__
![IDA view of hello world C++ program before polymorphic engine](crypt2.png)

--------------------------------------------------------------------------------------

__-- Basic "Hello, World!" application after polymorphic type --__
(the control flow chart gets more and more messy, the more instances of polymorphic types are instantiated) 
![IDA view of hello world C++ program after polymorphic engine](crypt1.png)

--------------------------------------------------------------------------------------

__--NOTES--__

* at the startup of your application, you MUST instantiate the global variables used by the classes by calling the static init_constants() function in the namespace:

```cpp
#include "enc_t.hpp"

int main(){
  crypto::init_constants(); // initialize the namespace
  
  // use the namespace throughout application now
  return 0;
}
```

* Extended types (SSE / AVX) must be enabled in your project settings if you wish to use the derived polymorphic versions of them.

* When using the e_malloc class to allocate dynamic blocks of memory, i suggest using the UNIQUE macro as such, unless you wish to manually call free() subsequently for every get() call:
```cpp
e_malloc e_malloc_instance(insert_allocation_size); // instantiate polymorphic memory block

auto unique_block_pointer = UNIQUE(e_malloc_instance.get()); // get unique_ptr to memory block (macro will apply custom Decommission object for malloc / free)

// use unique_block_pointer - it will prevent memory leaks on it's own when it goes out of scope
```


--------------------------------------------------------------------------------------

__--TO-DO / GOALS--__

* optimize the e_malloc class - it is the one class here that is terrible performance heavy during runtime and currently, unless used with the UNIQUE macro, prone to memory leaks
* strengthen XOR encryption algorithm and further randomize seeding method, to make this harder than it currently is to reverse.

