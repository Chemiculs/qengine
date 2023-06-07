# Polymorphic-Engine

NOTE: __-- MSVC SUPPORT IS EXPIRIMENTAL - LLVM / CLANG ARE THOROUGHLY TESTED --__ :

--------------------------------------------------------------------------------------

__-- FEATURES --__

* Runtime stack polymorphism (locals will be manipulated directly on the stack)
* Runtime heap polymorphism (dynamic polymorphic allocations are supported)

--------------------------------------------------------------------------------------

As you can see reading over the source, i have attempted to implement support for MSVC and others however have a ways to go with this, it was originally only written for LLVM / clang compiler. 

This is a well tested (in LLVM / clang) and while not perfect, is an effective, basic polymorphic type engine for C++ applications which will prevent security applications such Antiviruse's and Anticheat's from creating effective runtime signatures of your program, and above all else greatly obstruct reverse-engineers attempting to steal / crack your source.

This class is fully inlined, employing minimalist design and maximum performance + reliability.

--------------------------------------------------------------------------------------

__--HOW-TO--__

* Download enc_t.cpp and enc_t.hpp and include both of these in your project  

* Depending on the pathing structure of both your project and the placement of these specific files - you may need to adjust the include pathing in the source file "enc_t.cpp" to adhere to aformentioned pathing.

* in the source file(s) which you wish to include the project, you can simply use the #include directive to import the library and begin using it as such

--------------------------------------------------------------------------------------

__--EXAMPLES--__

Example project indicating generalized usage of primitive and extended types included in according folder.

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

* at the startup of your application, you must instantiate the global variables used by the classes by calling the static init_constants() function in the namespace:

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

