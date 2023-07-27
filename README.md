#                                          		qengine 

Easy to use and highly configurable, compiler-independent, fully inlined binary obfuscation for C++ 17+ windows applications

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

## Features

* Runtime stack polymorphism (locals will be manipulated directly on the stack and appear differently each execution, not really a big deal as this happens in most applications anyways)

  
* Runtime heap polymorphism (dynamic polymorphic allocations are supported, not a big deal as above)

  
* Thorough control-flow obfuscation (depending on compiler used and amount of library types used, IDA control-flow graph will be extremely difficult to read and in many cases fail pseudo-code generation)

  
* Cumbersome conditional branching (extended memory check obfuscation e.g create indirection for checking valuable information such as product keys etc.)

  
* .text / executable section Polymorphism (.text section dumps will appear different at each runtime which would hypothetically prevent basic static .text dump signature scans by AV's / AC's etc.)

  
* PE header wipe / mutation (headers will be wiped or appear different at each runtime)

  
* Dynamic / Runtime imports ( hide imports from disk import table )

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

## What is qengine?

qengine is a polymorphic engine (meaning an engine that takes multiple forms / permutations) for windows with the end goal of making the reverse engineers day much more difficult, and making the binary appear as unique as possible and unrecognizable at each independent runtime.

i couldn't find a good solution - llvm-obfuscator only supports llvm / clang, vmprotect / themida are proprietary solutions which offer little in terms of control over the process of obfuscation and other options tend to have the same issue - 
i couldn't control the way my binary was obfuscated the ways in which i wanted to.

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

* qengine is fairly well tested (considering i am a one-man team) - i currently am unaware of any bugs for LLVM / CLANG, MSVC, and Intel compiler targets for both x86 and x64 release builds.

* This will NOT prevent static disk-signatures of your executables - however, it will make the task of understanding your code from a classic disassembler such as IDA VERY difficult if used properly, and will prevent memory-dump / memory-scan based signature detections of your binary.

* This library is fully inlined, employing minimalist design and maximum performance + reliability --

qengine is very lightweight and likewise incurs a ~1.70% average performance loss vs standard library / primitive types, likewise you will retain ~98.3% of your application's original performance ( on average )

If anyone is able to contribute detailed benchmarks if they have the time, this would be extremely helpful - my hands are tied when it comes to free time for this project at the moment.

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

# Demonstration of control-flow obfuscation:

- "Hello, World!" application before polymorphic type -
- 
![IDA view of hello world C++ program before polymorphic engine](crypt2.png)

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

- "Hello, World!" application after polymorphic type -
(the control flow chart might be hard to see, but there are roughly 1000 sub-routines)

![IDA view of hello world C++ program after polymorphic engine](crypt1.png)

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

## Usage

### Option 1: Add to existing project:

* Download the repository as a zip file, and extract the /src/qengine folder to your project's main / root directory
* Include the qengine header file contained in <root_directory>/qengine/engine/
* Add <root_directory>/qengine/extern/ to additional library directories (for linking)

### Option 2: Build from source

* Download the repository as a zip file and extract the /vs/ folder
* Open the Project in visual studio 2022
* Change the compiler to whichever you prefer (the project is by default set to LLVM / CLANG), make sure C++ language standard is set to 17 or higher and build for desired architecture (leave build as a static library)
* Link against built libraries and include the qengine folder in your project

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

### Hello World

Here is the obligatory "Hello World" for qengine:

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

* All types contained in the qenc_t and qenc_h_t namespace's are encrypted using a polymorphic encryption algorithm and decrypted only when accessed, then re-encrypted. 

* All types contained in the qhash_t and qenc_h_t namespace's are hashed using a high-performance 32 or 64-bit hashing algorithm i made for this purpose.

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

### Cumbersome Conditional Branching

Here is an example of creating an obfuscated conditional branch which evaluates two variables for the specified conddition, and executes the callback function corresponding to the outcome:

```cpp
#include <iostream>

#include "qengine/engine/qengine.hpp"

using namespace qengine;

void true_() {

	std::cout << "condition is true" << std::endl;
}

void false_() {

	std::cout << "condition is false" << std::endl;
}


int main() {

	int x = 1;
	int y = 1;

	qcritical::SCRAMBLE_CRITICAL_CONDITION(
		true_,				// callback if condition evaluates to TRUE
		false_,				// callback if condition evaluates to FALSE
		std::tuple<>{},     // arguments (if any) for TRUE evaluated callback (our callback has no arguments)
		std::tuple<>{},		// arguments (if any) for FALSE evaluated callback (our callback has no arguments)
		x, y,				// our condition variables from left -> right order (can be of any primitive type or std::string / std::wstring type for now)
		qcritical::EQUALTO  // evaluation type (less than, greater than, equal to, greaterthanorequalto etc. )
	);

	return 0;
}
```

The above program outputs "condition is true" to the screen - the above example is optimized in release build, and if you want to see the real-world results on control flow this will have, you should use non-const comparison values e.g time_since_epoch etc.

When i get time i will upload a more in-depth analysis including screen-shots of the way which the cumbersome conditional branching obfuscates control-flow, but to summarize - 

* Multiple complex sub-routines are generated by the compiler as opposed to two basic ones for true / false evaluations
  
AND

* Each sub-routine contains multiple iterations of cmp / test instructions rather than a single cmp / test instruction as the compiler would normally generate and is beyond trivial to crack using a debugger.

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

### Memory Hash-Check Violation Handling

This library allows you to handle the event where a debugger or external tool attempts to illicitly write data to the stack / heap which corrupts / change any of your variables. 

Below i will give an example of how to create a callback function to handle this event, assign it to the library, and trigger it yourself to test it -

```cpp
#include <iostream>

#include "qengine/engine/qengine.hpp"

using namespace qengine;

 __declspec(noinline) void __fastcall violation_callback(qexcept::q_rogueaccess except, void* data) {

	if (except.id != qexcept::MEMORY_ALTERATION) // ensure this callback has been raised due to memory alteration
		return;

	std::cout << "Memory access violation occured, original hash: " << std::hex << except.original_hash << std::endl; // display the original hash of the data when it was valid

	std::cout << "Altered hash: " << std::hex << except.altered_hash << std::endl; // display the hash of the data which was altered

	std::cout << "Memory address: " << std::hex << reinterpret_cast<uintptr_t>(data) << std::endl; //display the memory address of the data which was altered 

	//here you would normally flag the user for a ban / violation or force-quit the application
}


int main() {

	qhash_t::init_hash_t(violation_callback); // assign our callback function to the namespace - all instances will refer to this callback if they detect a violation

	qhash_t::h_int32 MyInteger(999); // instance a hash-checked integer and set it's value to 999

	(*MyInteger.get_raw_memory_address()) = 998; // use the built in illegal-accessor for this example to modify the value of the data and trigger our callback

	int32_t value = MyInteger; // store the value held within MyInteger in a normal primitive variable to invoke get() (get() is when the check will occur)

	std::cout << "Hacked value: " << value << std::endl; // print the new / hacked value to the screen (998)

	std::cin.get();

	return 0;
}
```

Below is a screenshot of the resulting output from the above code:

![Output from hash check violation](callback_h.png)

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

### Header Manipulation / Executable Section Polymorphism / Permutations

This library can disrupt the ability to signature scan the executable sections of the PE file f=in memory / from memory dumps, and corrupt / wipe the header information (it would need to be rebuilt to properly parse through PE-bear / CFF explorer etc.)

Below is an example of how to mutate the executable sections of the PE and scramble the header information:

```cpp
#include <iostream>

#include "qengine/engine/qengine.hpp"

using namespace qengine;


int main() {

	// You do not have to use all of the below functions, however analyze_executable_sections() must be called before morph_executable_sections(), and this must be called before manipulating headers as it depends on information from the headers to perform analyzation

	qdisasm::qsection_assembler sec{ };

	sec.analyze_executable_sections();

	if (sec.morph_executable_sections(true)) // NOW we morph our stored sections and pass true to flag for memory clearance 
		std::cout << "Interrupt Padding morphed successfully! " << std::endl;
	else
		std::cout << "Interrupt Padding failed to be morphed! " << std::endl;

	if (sec.zero_information_sections())
		std::cout << "Garbage sections nulled" << std::endl;
	else
		std::cout << "Garbage section wipe failed" << std::endl;

	if (sec.scramble_dos_header(true))
		std::cout << "DOS headers wiped" << std::endl;
	else
		std::cout << "DOS headers not wiped" << std::endl;

	if (sec.scramble_nt_header())
		std::cout << "NT headers wiped" << std::endl;
	else
		std::cout << "NT headers not wiped" << std::endl;
	
	std::cout << ".text / header permutations complete!" << std::endl;

	std::cin.get();
}
```

The above code will complete successfully and without errors, there are instances where the section header manipulation will, however, cause the visual studio debugger to trigger exceptions if is attempting to read data from any of the altered sections (this does not matter as you won't be publishing a debug build of your application anyways if you are concerned about security)

Below are examples, before and after the above functions are called, of the PE headers and .text section of an executable

#### Headers before scramble:

![Headers before scramble](headerbeforescramble.png)

#### Headers after scramble:

![Headers after scramble](headerafterscramble.png)

Some fields such as e_magic in the DOS header and SizeOfStackCommit / SizeOfStackReserve fields in the optional header must be preserved as the application will crash elsewise.

#### .text section before scramble:

![.text before scramble](beforescramble.png)

#### .text section after scramble:

![.text before scramble](afterscramble.png)

I cannot show the whole .text section in one screenshot, so i tracked down a section above from a memory dump which was mutated (note that there are generaally hundreds or thousands of these regions which will be mutated depending on the symbol count / complexity of the binary) .

The interrupt padding (0xCC / INT3 on x86 PE files) between symbols is being tracked and permutated to change the appearance of the executable section in memory, which is a big thing , for me at least, as it is very hard to change machine code in a stable / reliable fashion during runtime.

The interrupt3 paddings (0xCC arrays) are regions that the instruction pointer never hits, so they are (almost) safely mutable to any form, the engine permutates them between { INT1, INT3, NOP } for the time being with random seed to accomplish this.

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

### Runtime imports

This library allows you to manually load api libraries at runtime and invoke them from their imported address - This prevents the names of the libraries and functions you are using in your application from being included on the import table of your PE.

Below is an example of importing a windows API function using the import tool -

```cpp
#include <iostream>

#include "qengine/engine/qengine.hpp"

using namespace qengine;


int main() {
	// Return type is NTSTATUS (template parameter)
	// Argument 1 is the library name (wide / ansi char depend on charset)
	// Argument 2 is name of function or ordinal number
	// all following arguments correspond to the API functions args themselves

	auto status = qimport::qimp::invoke<NTSTATUS>(L"user32.dll", "MessageBoxA", NULL, "Hello World", "Hello World", NULL);

	std::cin.get();
}
```

As you can see below, this yields the expected result from calling MessageBoxA with the according arguments:

![import protection](importer.png)

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

## - Hashing -

To address the reliability of the hashing algorithm(s), i made a collision testing application which tests for collisions amongst all possible permatations of a 2-byte / 16-bit data set using both algorithm's, the results are:

* qhash32 algorithm (32-bit) - 0.0000000233% collision rate amongst 65535 unique 16-bit datasets (1 collision), which is the same rate as crc32

* qhash64 algorithm (64-bit) - 0.0% collision rate amongst 65535 unique 16-bit datasets (0 collisions)

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

## Notes

* You must target C++ 17 or higher as your language standard for the library to compile properly

* Manipulating header info and morphing executable section will likely break virtualization tools such as VMProtect and Themida - I have not thoroughly tested this


* Extended types (SSE / AVX) must be enabled in your project settings if you wish to use the derived polymorphic versions of them.


* All heap-allocated types such as e_malloc, q_malloc, and h_malloc will automatically free their own memory when they go out of scope, however keep in mind that reading variable length memory with their according get() accessor will return new memory allocated with malloc() which you mut free yourself.


* While this library works for all of the compilers i will mention, MSVC produces the least complex control-flow graphing as a compiler - LLVM / CLANG and Intel Compiler always produce the best obfuscated output files and skewed control-flow graphs - here are some examples all from the same basic application with only a main function :

#### CLANG
  ![CFG_clang](clang.png)

#### INTEL
  ![CFG_intel](intel.png)

#### MSVC
  ![CFG_msvc](MSVC.png)


I am unsure as to exactly why this occurs when i use the same compiler settings for all of the above compilers, my experience would say that MSVC likely does not like to inline functions when you 
instruct it to, while CLANG / Intel com[pilers are more likely to listen to user commands


* Proper compiler settings play a massive role in the output this library will produce.
- Make sure the binary is built for Release mode
- Here are the most important settings to use for maximum security (In VS 2022):

    ![VS2022 Config](optimization.png)
  
--------------------------------------------------------------------------------------

## How you can help

I don't have much time on my hands at the moment. I am passionate about this project and can see it having a very bright future, however due to these aformentioned reasons i have limited ideas coming to mind as to what the next move will be, how to improve this etc...

Please submit any bugs with the library you find, and i encourage you to contribute to the project if you enjoy it or find any use from it.

#### If you have any questions / inquiries, feel free to contact me on discord:
### 0xH4X0R#0390
