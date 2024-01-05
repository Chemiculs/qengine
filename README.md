#                                          		qengine 

An easy to use and highly configurable, compiler-independent, fully inlined binary obfuscation toolkit for C++ 17+ Windows applications

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

<details>
<summary>##Features</summary>

* Runtime stack polymorphism (locals will be manipulated directly on the stack and appear differently each execution, not really a big deal as this happens in most applications anyways)

  
* Runtime heap polymorphism (dynamic polymorphic allocations are supported, not a big deal as above)

  
* Thorough control-flow obfuscation (depending on the compiler used and amount of library types used, the IDA control-flow graph will be extremely difficult to read and in many cases fail pseudo-code generation)

  
* Cumbersome conditional branching (extended memory check obfuscation e.g. create indirection for checking valuable information such as product keys etc.)

  
* .text / executable section Polymorphism (.text section dumps will appear different at each runtime which would hypothetically prevent basic static .text dump signature scans by AV's / AC's etc.)

  
* PE header wipe/mutation (headers will be wiped or appear differently at each runtime)

  
* Dynamic / Runtime imports ( hide imports from disk import table )

</details>

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

<details>
<summary>##What is qengine?</summary>

qengine is a polymorphic engine (meaning an engine that takes multiple forms/permutations) for Windows with the end goal of making the reverse engineer's day much more difficult and making the binary appear as unique as possible and unrecognizable at each independent runtime.

i couldn't find a good solution - llvm-obfuscator only supports llvm / clang, vmprotect / themida are proprietary solutions which offer little in terms of control over the process of obfuscation and other options tend to have the same issue - 
i couldn't control the way my binary was obfuscated the ways in which i wanted to.

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

* qengine is fairly well tested (considering I am a one-man team) - I currently am unaware of any bugs for LLVM / CLANG, MSVC, and Intel compiler targets for both x86 and x64 release builds.

* This will NOT prevent static disk signatures of your executables - however, it will make the task of understanding your code from a classic disassembler such as IDA VERY difficult if used properly, and will prevent memory-dump / memory-scan-based signature detections of your binary.

* This library is fully inlined, employing a minimalist design and maximum performance + reliability --

qengine is very lightweight and likewise incurs a ~1.70% average performance loss vs. standard library / primitive types, likewise you will retain ~98.3% of your application's original performance ( on average )

If anyone is able to contribute detailed benchmarks if they have the time, this would be extremely helpful - my hands are tied when it comes to free time for this project at the moment.

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

# Demonstration of control-flow obfuscation:

- "Hello, World!" application before polymorphic type -

![IDA view of hello world C++ program before polymorphic engine](img/crypt2.png)

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

- "Hello, World!" application after polymorphic type -
(The control flow chart might be hard to see, but there are roughly 1,000 sub-routines)

![IDA view of hello world C++ program after polymorphic engine](img/crypt1.png)

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

## Usage

### Option 1: Add to an existing project:

* Download the repository as a zip file, and extract the /src/qengine folder to your project's main / root directory
  
* goto <root_directory>/qengine/extern/ and unzip "asmjit_libs.zip"  - make sure all the files within are extracted to this directory
  
* Include the qengine header file contained in <root_directory>/qengine/engine/
  
* Add <root_directory>/qengine/extern/ to additional library directories (for linking)

### Option 2: Build from source

* Download the repository as a zip file and extract the /vs/ folder
  
* Open the Project in Visual Studio 2022
  
* Change the compiler to whichever you prefer (the project is by default set to LLVM / CLANG), make sure C++ language standard is set to 17 or higher and build for desired architecture (leave build as a static library)
  
* Link against built libraries and include the qengine folder in your project
(you MUST either extract asmjit_libs.zip in /qengine/extern/ as above or build ASMJIT from source for static library target)

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

* All types contained in the qhash_t and qenc_h_t namespace's are hashed using a high-performance 32 or 64-bit hashing algorithm I made for this purpose.

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

### Cumbersome Conditional Branching

Here is an example of creating an obfuscated conditional branch that evaluates two variables for the specified condition, and executes the callback function corresponding to the outcome:

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

The above program outputs "condition is true" to the screen - the above example is optimized in the release build, and if you want to see the real-world results on control flow this will have, you should use non-const comparison values e.g. time_since_epoch etc.

Let's do that below to give a better example of what is exactly happening with a non-const example:

![source files](img/originalcode.png)

Both programs above serve the same mathematical function and produce the same output, the one on the left built with qengine and the one on the right built using C++ standard operators/function calls.

Let's take a look at both of the above applications in IDA pseudo-code view (both are built Release x64, optimizations on, MSVC )

[Left = qengine, Right = std]
![entrypoints](img/criticalmain.png)

At first glance the entrypoint of both applications appear to be almost identical, with key differences I will highlight from the pseudo-code view and others from the raw assembly view -

* The conditional arithmetic in the std application all occurs within the entrypoint function, this will be highlighted in the next screenshot precisely using assembly-code view
  
* The conditional arithmetic in the qengine application is detoured to another subroutine, namely sub_140001810 which is compiled by taking callback arguments to the functions 'true_' and 'false_'

Below is the relevant region of machine code from both entry-point functions, which should reveal a JLE instruction (jump if lesser than or equal to), as this is the condition under which this program determines its functionality:

![entrypoints](img/critical_asm_jle.png)

The std-compiled binary on the right, as expected, contains a JLE instruction plain as day. this, or the previous cmp instruction can be altered by a reverse engineer easily in a number of ways to manipulate the control flow of the application, or 'crack' it.

The qengine-compiled binary on the left, however, contains no such instruction. the instruction is detoured to sub_140001810, and inside of that subroutine, split into dozens of varying, complex comparison operators scattered amongst thousands of lines of obfuscated code.

A quick peak below at the pseudo-code view of both subroutines called from the std-compiled application (sub_140001240) (Right) and the qengine-compiled application(sub_140001810) (Left) :

![subroutines](img/criticalsubroutine.png)

The std subroutine is easily identifiable as a standard output stream and is anything but complex in its appearance to a skilled reverse engineer.

The qengine-generated subroutine is (almost) incomprehensible - IDA generated 4726 lines of pseudo-code for the sub-routine, and attempted to allocate 1127 local variables on the stack - i wouldn't be having fun if i opened this application in IDA  looking to crack it.

Let's not be naive however - a thoroughly determined and highly skilled reverse engineer could theoretically spend hours/days or perhaps weeks/months reversing the subroutine and eventually find the critical cmp / test instructions, patch them out, and produce a working crack or modification of the application. 

There is no perfect fix for the issue of reversing - It boils down to a battle of which side can annoy the other the most.

## But couldn't I just NOP the call to sub_140001810 and bypass the security?

![entrypoints](img/callsub.png)

You could absolutely replace the call to sub_140001810 with an NOP or any other instruction, however with the above program, the consequences of doing so would be -

* Ceasing of further functionality ( if this was a product key input, for example, the program would fail to properly execute moving forward )
  
* You would have to go inside of sub_140001810 and patch the appropriate cmp / test / jmp instructions (all of which are hash-checked on the stack as well), in order to truly 'crack' the application in a manner which would preserve functionality, this is not a crackme but could easily be converted to one and would appear similar enough.

To demonstrate a basic cracking attempt by preventing the call to the subroutine, I opened up the binary in IDA and patched the call to sub_140001810

![track](img/patchview.png)

Now all that is left to do is run the patched binary and see if it produces usable output like the original -

![track](img/patchedrun.png)

The 'patched' binary (which now fails to call the subroutine handling conditional callbacks), produces zero output. the program is in a broken and unusable state.

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

### Memory Hash-Check Violation Handling

This library allows you to handle the event where a debugger or external tool attempts to illicitly write data to the stack/heap which corrupts/changes any of your variables. 

Below I will give an example of how to create a callback function to handle this event, assign it to the library, and trigger it yourself to test it -

```cpp
#include <iostream>

#include "qengine/engine/qengine.hpp"

using namespace qengine;

 __declspec(noinline) void __fastcall violation_callback(qexcept::q_rogueaccess except, void* data) {

	if (except.id != qexcept::MEMORY_ALTERATION) // ensure this callback has been raised due to memory alteration
		return;

	std::cout << "Memory access violation occurred, original hash: " << std::hex << except.original_hash << std::endl; // display the original hash of the data when it was valid

	std::cout << "Altered hash: " << std::hex << except.altered_hash << std::endl; // display the hash of the data which was altered

	std::cout << "Memory address: " << std::hex << reinterpret_cast<uintptr_t>(data) << std::endl; //display the memory address of the data which was altered 

	//Here you would normally flag the user for a ban/violation or force-quit the application
}


int main() {

	qhash_t::init_hash_t(violation_callback); // assign our callback function to the namespace - all instances will refer to this callback if they detect a violation

	qhash_t::h_int32 MyInteger(999); // instance a hash-checked integer and set its value to 999

	(*MyInteger.get_raw_memory_address()) = 998; // use the built-in illegal-accessor for this example to modify the value of the data and trigger our callback

	int32_t value = MyInteger; // store the value held within MyInteger in a normal primitive variable to invoke get() (get() is when the check will occur)

	std::cout << "Hacked value: " << value << std::endl; // print the new / hacked value to the screen (998)

	std::cin.get();

	return 0;
}
```

Below is a screenshot of the resulting output from the above code:

![Output from hash check violation](img/callback_h.png)

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

The above code will complete successfully and without errors, there are instances where the section header manipulation will, however, cause the Visual Studio debugger to trigger exceptions if is attempting to read data from any of the altered sections (this does not matter as you won't be publishing a debug build of your application anyways if you are concerned about security)

Below are examples, before and after the above functions are called, of the PE headers and .text section of an executable

#### Headers before scramble:

![Headers before scramble](img/headerbeforescramble.png)

#### Headers after scramble:

![Headers after scramble](img/headerafterscramble.png)

Some fields such as e_magic in the DOS header and SizeOfStackCommit / SizeOfStackReserve fields in the optional header must be preserved as the application will crash otherwise.

#### .text section before scramble:

![.text before scramble](img/beforescramblenew.png)

#### .text section after scramble:

![.text before scramble](img/afterscramblenew.png)

I cannot show the whole .text section in one screenshot, so I tracked down a section above from a memory dump that was mutated (note that there are generally hundreds or thousands of these regions which will be mutated depending on the symbol count/complexity of the binary).

The interrupt padding (0xCC / INT3 on x86 PE files) between symbols is being tracked and permutated to change the appearance of the executable section in memory.

The INT3 paddings (0xCC arrays) are regions that the instruction pointer never hits, so they are (almost) safely mutable to any form, the engine now mutates these regions to random executable machine code which will make it extremely hard to determine where a function/subroutine ends, and which code is valid and executed.

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

### Runtime imports

This library allows you to manually load API libraries at runtime and invoke them from their imported address - This prevents the names of the libraries and functions you are using in your application from being included on the import table of your PE.

Below is an example of importing a Windows API function using the import tool -

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

![import protection](img/importer.png)

If you do not want the overhead of GetProcAddress() being called repeatedly, I have added the ability to store the imported function bound to its prototype as a local or global object which can be directly invoked for a small performance gain 
(I have not checked myself, but I doubt the compiler will know precisely what we are doing and will perform an Export Table lookup at every GetProcAddress() call).

This is useful if you are calling the imported function in a loop or by any other means calling it repeatedly, below is an example specific to this use case :

```cpp

#include <iostream>

#include "qengine/engine/qengine.hpp"

using namespace qengine;

/* First template argument specifies return type, subsequent template arguments specify argument type list in Left -> Right order for the fn being imported */
static auto imp_MessageBoxA = qimport::qimp::get_fn_import_object<NTSTATUS, unsigned int, const char*, const char*, unsigned int>(L"user32.dll", "MessageBoxA");

int main() {

	auto status = imp_MessageBoxA(NULL, "Hello World!", "Hello World!", NULL); // call MessageBoxA and assign it's status return to a local 

	std::cout << status << std::endl; // output the return status to the console 

	std::cin.get(); 
}

```

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

## Hashing -

To address the reliability of the hashing algorithm(s), I made a collision testing application that tests for collisions amongst all possible permutations of a 2-byte / 16-bit data set using both algorithms, the results are:

* qhash32 algorithm (32-bit) - 0.0000000233% collision rate amongst 65535 unique 16-bit datasets (1 collision), which is the same rate as crc32

* qhash64 algorithm (64-bit) - 0.0% collision rate amongst 65535 unique 16-bit datasets (0 collisions)

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
## Experimental Hook Scanning

People developing certain applications, namely Video Games, struggle with internal game cheats (DLL injection). These cheats (internal) and sometimes external cheats, will hook / detour certain important functions inside of the game/application in order to manipulate output and obtain an advantage or 'crack' certain features of the application.

Detours are generally speaking, simple blocks of machine code 12+ bytes in length which are placed at a functions pointer in memory, in order to redirect control flow of the function outside of the main module, and into the malicious module.

here is an example of a most basic detour function in X86 assembly 

```asm
mov rax, 0xDETOUR_ADDRESS    ; move an immediate value ( address of the function we want to execute instead of the original ) into the RAX register
jmp rax                      ; move the instruction pointer to the address held in the RAX register
```

Detecting these hooks can be a non-trivial task depending on the complexity of the hook -

I have implemented a rather basic implementation of a hook scanning class inside of qengine in the latest update, the class uses a separate thread to efficiently scan methods in memory for the placement of hooks inside of the method's body.

The thread searches for flow transfer instructions (ret, jmp, call namely), and when these are found, it checks if the address to which flow is being transferred is within the module's address space.
If not, this likely means a hook has been placed on the method.

Below is an example application that initializes the hook-detection library, and references the designated callback function to it. After this, an example hook is placed at the functions address in memory to demonstrate detection by our library :

```cpp
#include <iostream>

#include "qengine/engine/qengine.hpp"

using namespace qengine;

__declspec(noinline) void __fastcall myimportantmethod(long long val) { // add junk code to our dummy method to increase it's size in memory to be viable for hook placement

	auto j = std::chrono::high_resolution_clock::now().time_since_epoch().count();

	auto k = j % val;

	std::cout << k << std::endl;
}

__declspec(noinline) void __cdecl callback(qexcept::q_fn_alteration alteration) {

	if (alteration.id != qexcept::HOOK_DETECTED)
		return;

	auto casted_arg = reinterpret_cast<qhook::qhook_detection_t*>(alteration.violation_object_);

	std::cout << "Function hook detected, address: " << std::hex << casted_arg->hook_address << "\n";
	std::cout << "Hook size: " << casted_arg->hook_length << "\n";
	std::cout << "Hook data: " << std::endl;

	for (auto i = 0; i < casted_arg->hook_length; ++i)
		std::cout << std::hex << (int)casted_arg->hook_data[i] << "\n";

	delete casted_arg; // thi was allocated with new, must be deleted inside callback to avoid memory leak
}

int main() {

	std::cout << "initializing hook scanner..." << std::endl;

	qhook::qhook_t::set_client_callback_fn(&callback);

	qhook::qhook_t((void*)&myimportantmethod);

	// any of the below hooks will be detected - you could change the registers used etc. if you wanted to

	unsigned char hook1[12] = {
		0x48, 0xB8, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0xFF, 0xE0 // mov rax, 0x1111111111111111 ; jmp rax
	};

	unsigned char hook2[14] = { // this is a trash hook used to test features of the detection, push rax, pop rax is a NOP essentially
		0x48, 0xB8, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x50, 0x58, // mov rax, 0x1111111111111111 ; push rax ; pop rax ; jmp rax
		0xFF, 0xE0
	};

	unsigned char hook3[12] = {
		0x48, 0xB8, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x50, 0xC3 // mov rax, 0x1111111111111111 ; push rax ; ret
	};

	myimportantmethod(4);

	std::cout << "emplacing hook..." << std::endl;

	auto* ptr = (void*)&myimportantmethod;

	DWORD tmp{};

	VirtualProtect(ptr, sizeof(hook2), PAGE_EXECUTE_READWRITE, &tmp);

	memcpy(ptr, &hook2, sizeof(hook2));

	VirtualProtect(ptr, sizeof(hook2), tmp, &tmp);

	std::cin.get();

	return 0;
}
```

Here is the output when we execute the above application :

![import protection](img/main_withhook.png)

I have with the rather brief testing period I have subjected this to, been unable to cause false-positive detections. Anyone willing to test this library to a greater extent to see if they can break it, would be beyond helpful.

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

## Notes

* You must target C++ 17 or higher as your language standard for the library to compile properly

* Manipulating header info and morphing executable section will likely break virtualization tools such as VMProtect and Themida - I have not thoroughly tested this


* Extended types (SSE / AVX) must be enabled in your project settings if you wish to use the derived polymorphic versions of them.


* All heap-allocated types such as e_malloc, q_malloc, and h_malloc will automatically free their own memory when they go out of scope, however keep in mind that reading variable length memory with their according get() accessor will return new memory allocated with malloc() which you must free yourself.


* While this library works for all of the compilers I will mention, MSVC produces the least complex control-flow graphing as a compiler -
  
LLVM / CLANG and Intel Compiler always produce the best obfuscated output files and skewed control-flow graphs - Here are some examples all from the same basic application with only a main function (~20 lines of code using polymorphic types) :

### CLANG
  ![CFG_clang](img/clang.png)

### INTEL
  ![CFG_intel](img/intel.png)

### MSVC
  ![CFG_msvc](img/MSVC.png)


I am unsure as to exactly why this occurs when I use the same compiler settings for all of the above compilers, my experience would say that MSVC likely does not like to inline functions when you 
instruct it to, while CLANG / Intel compilers are more likely to listen to user commands/suggestions


* Proper compiler settings play a massive role in the output this library will produce.
- Make sure the binary is built for Release mode
- Here are the most important settings to use for maximum security (In VS 2022):

    ![VS2022 Config](img/optimization.png)
  
--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

## Credits

* Huge thank you to the [Capstone Project](https://github.com/capstone-engine/capstone) for making many parts of this library feasible and providing an excellent disassembly library in general

* Another huge thank you to the [ASMJIT Project](https://github.com/asmjit/asmjit) for making machine code generation at runtime a feasible prospect for this project

* [HadockKali](https://github.com/HadockKali) ( For helping with this Readme ) 

Licenses for both respective libraries are included in the repo and must be upheld.

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

## Donations

I am extremely limited in my ability to have time to work on this project - I work a restaurant job at the moment to make ends meet as I have had no luck finding a software job as of the time writing, However, I absolutely do not expect anyone to give me money for this software, please do not feel obligated to. 

If you do however, wish to support this project at the current time you can feel free to donate using CashApp (haven't been able to get a presentable PayPal donation link yet)

[CashApp](https://cash.app/$0xH4X0R)
[Paypal](https://paypal.me/CoDTroll?country.x=US&locale.x=en_US)

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
## How you can help

I don't have much time on my hands at the moment. I am passionate about this project and can see it has a very bright future, however due to these aforementioned reasons I have limited ideas coming to mind as to what the next move will be, how to improve this, etc...

Please submit any bugs with the library you find, and I encourage you to contribute to the project if you enjoy it or find any use for it.

#### If you have any questions/inquiries, feel free to contact me on Discord:
### 0xH4X0R#0390
