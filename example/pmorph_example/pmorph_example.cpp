// pmorph_example.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <cstdlib>
#include "enc_t.hpp"

using namespace crypto;
using namespace std;

int main()
{
    //call our initializer: we need this for the polymorphic seed we will use to encrypt data. this changes at each runtime based on environment variables
    crypto::init_constants();
#pragma region Integral Types

    
    
    e_uint8 test_byte(0xFF);// instantiate encrypted byte with max value

    test_byte = 0xFF; // test assignment operator towards our object by reassigning max byte value

    uint8_t value = test_byte; // operator = etc.. overload will automatially call e_uint8_t.get(), so value will be 0xFF

    cout << "e_uint8_t 0xFF value: " << endl << std::to_string(value) << endl << endl;

    crypto::init_constants();

    e_uint32 test_int(0xFFFFFFFF);// instantiate encrypted byte with max uint value

    test_int = 0xFFFFFFFF; // test assignment operator towards our object by reassigning max uint value

    uint32_t value_int = test_int; // operator = etc.. overload will automatially call e_uint32_t.get(), so value will be 0xFF

    cout << "e_uint32_t 0xFFFFFFFF value: " << endl << std::to_string(value_int) << endl << endl; // should output 4,294,967,295

    // all operators of any kind can be used on the instantiated polymorphic objects as you would with a usual base type integeral T
#pragma endregion

#pragma region Floating Point

    e_double test_double(0.00125); // assign the object a value of 0.00125f

    test_double = 0.00125; // reassign same value to verify functionality

    test_double ^= 1; // perform xor-assignment operation twice to return original value and to test the addition of xor compatibility to some floating point types
    test_double ^= 1;

    double value_double = 0.00125; // retrieve the assigned value

    cout << "e_double 0.00125 value: " << endl << std::to_string(value_double) << endl << endl;


#pragma endregion

#pragma region String Types
    
    e_string test_string("i am polymorphic!");

    test_string += " - and modified!";

    cout << "e_string i am polymorphic! value + test_string: " << endl << test_string.get() << endl << endl;

#pragma endregion

#pragma region Extended vector types

    e_m128 test_vec4(_mm_set_ps(1.f, 2.f, 3.f, 4.f));
    
    cout << "vector4 (__m128) (4, 3, 2, 1) values: " << endl << endl;
    float values[4];
    _mm_store_ps(values, test_vec4);
    for (auto i = 0; i < 4; ++i)
        cout << values[i] << endl << endl;

#pragma endregion

#pragma region Heap allocations

    e_malloc test_heap(5); // declare new heap allocation of size 5 bytes

    test_heap[0] = 0xFF; // use subscript operator to assign each byte a unique value
    test_heap[1] = 0xFE;
    test_heap[2] = 0xFD;
    test_heap[3] = 0xFC;
    test_heap[4] = 0xFB;

    auto data = UNIQUE(test_heap.get()); // use UNIQUE macro to get a unique_ptr object that will dispose when it goes out of scope 
    // if you want you can simply retrieve a pointer to the data 
    // - however you must call free() explicitly when done using it, as it will be a COPY of the actual data stored int the class 

    cout << "e_malloc(5){255, 254, 253, 252, 251} values: " << endl << endl;
    for (auto i = 0; i < 5; ++i)
        cout << std::to_string(data[i]) << endl << endl;

#pragma endregion

    getchar();
}