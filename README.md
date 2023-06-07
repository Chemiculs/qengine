# Polymorphic-Engine

NOTE-- MSVC SUPPORT IS EXPIRIMENTAL - LLVM / CLANG ARE THOROUGHLY TESTED --|

As you can see reading over the source, i have attempted to implement support for MSVC and others however have not succeeded at this yet. 

This is a well tested and while not perfect, an effective polymorphic type engine for C++ applications which will prevent security applications such Antiviruse's and Anticheat's from creating effective runtime signatures of your program, and above all else greatly obstruct reverse-engineers attempting to steal / crack your source.

This class is fully inlined, employing minimalist design and maximum performance and reliability.

HOW-TO:

* Download enc_t.cpp and enc_t.hpp and include both of these in your project  

* Depending on the pathing structure of both your project and the placement of these specific files - you may need to adjust the include pathing in the source file "enc_t.cpp" to adhere to aformentioned pathing.

* in the source file(s) which you wish to include the project, you can simply use the #include directive to import the library and begin using it as such


Example project indicating generalized usage of primitive and extended types included in according folder.


Demonstration of control flow obfuscation:
__-- Basic "Hello, World!" application before polymorphic type --__
![IDA view of hello world C++ program before polymorphic engine](crypt2.png)

__-- Basic "Hello, World!" application after polymorphic type --__
(the control flow chart gets more and more messy, the more instances of polymorphic types are instantiated) 
![IDA view of hello world C++ program after polymorphic engine](crypt1.png)
