/*
/**************************************************************************************************************************************************************************
*																											                                                              *
* This class is ONLY intended to prevent plaintext cstring from being output to the binary                                                                               *
* This does not use the polyq algorithm and is NOT hash-checked, it's one and only purpose is the most basic possible encryption to prevent string-searching the binary  *
*                                                                                                                                                                        *
*                                                                                                                                                                        *
* Credit for this class should mostly, if not entirely, go to the original author of skCrypt:                                                                            *
*                                                                                                                                                                        *
* https://github.com/javaloader/Sky-Crypt-C-11-String-Encryptor-                                                                                                          *
*                                                                                                                                                                        *
* Preprocessor / Constexpr is tricky, so i modified the naming convention(s) and a few specificities from his class to fit qengine's                                     *
*																											                                                              *                      
***************************************************************************************************************************************************************************
*/

#pragma region Header Guard

#ifndef QSTR_H
#define QSTR_H

#pragma endregion

#pragma region Imports

#pragma region qengine

#include "qdef.hpp"

#pragma endregion

#pragma endregion

template <class C>
using qclean_type = typename std::remove_const_t<std::remove_reference_t<C>>;

#pragma region Output Macro

#define QSTR(__STR__) []() { \
		constexpr static auto _QSTR_ = qstr_object \
			<sizeof(__STR__) / sizeof(__STR__[0]), qclean_type< decltype( __STR__[0] ) >>((qclean_type<decltype(__STR__[0])>*)__STR__); \
				return _QSTR_; }()

#pragma endregion

#pragma region Compile-time Constants

imut constexpr std::int8_t _QSTR_KEY = (__TIME__[7] | __TIME__[4] | __TIME__[0]) ^ BYTE_SET;

#pragma endregion

template <imut std::int32_t _size, typename T>
class qstr_object
{

private:

    mut T _storage[_size]{};

    __compelled_inline constexpr void qcrypt(imut T *data) noexcept {

        for (int i = 0; i < _size; i++)
            _storage[i] = ( ( data[i] ^ _QSTR_KEY ) ^ ( (__TIME__[0] ^  __TIME__[4] ^ __TIME__[6]) ^ BYTE_SET ) );
    }

public:

#pragma region Ctor

    __compelled_inline constexpr qstr_object(imut T *data) noexcept {

        qcrypt(data);
    }

#pragma endregion

    __compelled_inline imut T* get() imut noexcept {

        return _storage;
    }

    __compelled_inline imut std::int32_t size() imut noexcept {

        return _size;
    }

    __compelled_inline imut bool __stackcall is_crypted() imut noexcept {

        return _storage[_size - 1] != 0;
    }

    __compelled_inline T* crypter_routine() noexcept {

        if (is_crypted())
            qcrypt(_storage);

        return _storage;
    }

    __compelled_inline void __stackcall clear() noexcept {

        RtlZeroMemory(_storage, _size);
    }

    __compelled_inline __stackcall operator T* () noexcept {

        return const_cast<T*>(
            crypter_routine()
        );
    }
};

#pragma region Header Guard

#endif

#pragma endregion