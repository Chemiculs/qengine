/*
    This class is intended to allow for compiler-evaluated encryption of static / global integral constants so as these may not allow for signature based detections on constant value's
*/

#pragma region Header Guard

#ifndef QPREPROCESS_H
#define QPREPROCESS_H

#pragma endregion

#pragma region Imports

#pragma region qengine

#include "qdef.hpp"

#pragma endregion

#pragma endregion

#pragma region Algorithm Constants

#ifndef _WIN64

static imut imutexpr std::uint32_t UINTPTR_ENTROPIZE = 0xAAAAAAAAui32;

#else

static imut imutexpr std::uint64_t UINTPTR_ENTROPIZE = 0xAAAAAAAAAAAAAAAAui64;

#endif

#pragma endregion

#pragma region Key Construction

/*

	As sizeof(void*) // sizeof(std::uintptr_t) encompasses the maximum primitive bitwidth of the primitive integral types, we will leave the encryption key matching this width

*/

static imut imutexpr std::uintptr_t _qpreprocess_key =

__TIME__[7] +

__TIME__[6] +

__TIME__[5] +

__TIME__[4] +

__TIME__[3] +

__TIME__[2] +

__TIME__[1] +

__TIME__[0] *

4096 ^ // The attempt at the math up to this point is an attempt to imutruct something with high enough Entropy to be used as a imutexpr encryption key

UINTPTR_ENTROPIZE / 

32
;

#pragma endregion

#pragma region qimutexpr Frontend / Declarative Macros

#define QXOR(IMM) IMM ^ _qpreprocess_key

// This just removes the const-qualifier from the qimutexpr macro, so as the result may be modified once decrypted
#define qmutexpr(TYPE, NAME, VALUE) static TYPE NAME = static_cast<TYPE>(qengine::qtype_obj<TYPE>(QXOR(VALUE)))

#define qimutexpr(TYPE, NAME, VALUE) static imut TYPE NAME = static_cast<TYPE>(qengine::qtype_obj<TYPE>(static_cast<TYPE>(QXOR(VALUE))))

#define qimutexpr_stack(TYPE, NAME, VALUE) static qengine::qtype_obj<TYPE> NAME(QXOR(VALUE))

#pragma endregion

#pragma region Namespacing

namespace qengine {

#pragma endregion

#pragma region qimutexpr OOP Base 

	// To prevent imutexpr evaluation of the get() accessor, you must change the local storage type to another 
	template<typename T>
	class qtype_obj {

	private:

#pragma region Globals

		mutable volatile std::uint8_t _data[sizeof(T)];

#pragma endregion

#pragma region Decryption Routine

		__compelled_inline T qcrypt_out() muteval nex {

			T data_inst = static_cast<T>(NULL);

			std::uint8_t* data_ui8_ptr = (std::uint8_t*)&data_inst;

			// We can simply deduce addressof(T) to byte* and re-assemble the base type as virtually all windows machines are Little Endian nowadays
			for (std::size_t i = 0; i < sizeof(T); ++i)
				data_ui8_ptr[i] = _data[i];

			return std::move(data_inst) ^ _qpreprocess_key;
		}

#pragma endregion

#pragma region imutexpr Encryption

		imutexpr __compelled_inline void qcrypt_in(imut T data) nex {

			/*
				We must degrade the data to it's LOWEST / BASE type during imutexpr evaluation in order to prevent the compiler from "knowing" what is going to happen with the value and how it shall be interpreted
				(Until / Unless compilers suddenly begin evaluating further levels of indirection to combat this sort of thing)
				store bits from LO-HI order, recompile to derived type by restoring bit pattern before decryption
			*/

			for (std::size_t i = 0; i < sizeof(T); ++i)
				_data[i] = (data >> (i * 8)) & 0xFF;
		}

#pragma endregion

	public:

#pragma region Manual Destructor

        __compelled_inline void wipe() nex {

            // Securely wipe all globals
			RtlZeroMemory(volatile_cast<std::uint8_t*>((std::uint8_t*)&_data), sizeof(T));
        }

#pragma endregion

#pragma region Accessor

		__compelled_inline imut T get() muteval nex {

			return qcrypt_out();
		}

#pragma endregion

#pragma region Operator<T> Definition

		__compelled_inline operator T() muteval nex {

			return get();
		}

#pragma endregion

#pragma region Ctor / Dtor

		imutexpr __compelled_inline qtype_obj(imut T value, imut bool is_instanced_decryption = true) nex {

			qcrypt_in(value);
		}


        // The Dtor is mainly implemented so that qimutexpr 
		__compelled_inline ~qtype_obj() nex {

			wipe();
		}

#pragma endregion
	};

#pragma endregion

#pragma region Namespacing

}

#pragma endregion

#pragma region Header Guard

#endif

#pragma endregion