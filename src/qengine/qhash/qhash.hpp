/*
/**************************************************************************************************************
*																											 *
*  QHash is made to be a fast and performative 32 / 64-bit hashing algorithm for runtime data integrity      *
*																											 *
***************************************************************************************************************
*/

#pragma region Header Guard

#ifndef QHASH_H
#define QHASH_H

#pragma endregion

#pragma region Imports

#pragma region qengine

#include "../qbase/qdef.hpp"

#pragma endregion

#pragma region std

#include <cstdint>

#pragma endregion

#pragma endregion

#pragma region Preprocessor

#pragma optimize("", on)
#pragma inline_depth(255)
#pragma inline_recursion(on) 

#pragma pack(push, 1)

#pragma endregion

namespace qengine {

	namespace qhash {

#pragma region Type Definitions

#pragma region Hash Structure\

		typedef struct qhash32_t {

			std::uint32_t hash;

			__compelled_inline bool __regcall operator==(const qhash32_t other) const noexcept {

				return (this->hash == other.hash);
			}

			__compelled_inline bool __regcall operator!=(const qhash32_t other) const noexcept {

				return this->operator==(other) ? false : true;
			}
		};

		typedef struct qhash64_t {

			std::uint64_t hash;

			__compelled_inline bool __regcall operator==(const qhash64_t other) const {

				return (this->hash == other.hash);
			}

			__compelled_inline bool __regcall operator!=(const qhash64_t other) const {

				return this->operator==(other) ? false : true;
			}
		};

		typedef struct qhash_cpu_t {

#ifdef _WIN64

			mutable qhash64_t hash_obj;

#else

			mutable qhash32_t hash_obj;

#endif

			__compelled_inline bool __regcall operator==(const qhash_cpu_t other) const noexcept {

				return this->hash_obj == other.hash_obj;
			}

			__compelled_inline bool __regcall operator!=(const qhash_cpu_t other) const noexcept {

				return this->operator==(other) ? false : true;
			}
		};

#pragma endregion

#pragma endregion

#pragma region Hash Constants

#define MOST_SIGNIFICANT_DEFAULT 0xAEui8

#pragma region 32-bit

#define QHBASE32 0xFAE9E8D7ui32

#define QHEPILOGUE32 0xAEBDCCDBui32

		extern bool initialized32;

		extern std::uint32_t qtable32[];

#pragma endregion

#pragma region 64-bit

#ifdef _WIN64

#define QHBASE64 0xFAE9E8D7C6B5A493ui64

#define QHEPILOGUE64 0xAEBDCCDB0A192837ui64

		extern bool initialized64;

		extern std::uint64_t qtable64[];

#endif

#pragma endregion

#pragma endregion

#pragma region Table Generation

		__compelled_inline static void qtable32_gen() noexcept {
			static std::int32_t seed = 0xFEEDDCCBui32;

			static const constexpr std::uint16_t decrementor = 0xFFFFui16;

			for (auto i = 0; i < 255; ++i) {
				qtable32[i] = (((seed ^ QHBASE32) ^ QHEPILOGUE32) ^ 0xFFFFFFFFul);

				seed -= decrementor;
			}
		}

#ifdef _WIN64

		__compelled_inline static void __stackcall qtable64_gen() noexcept {

			static std::uint64_t seed = 0xFEEDDCCBBAA99887ui64;

			static const constexpr std::uint32_t decrementor = 0xFFFFFFFFui32;

			for (auto i = 0; i < 255; ++i) {

				qtable64[i] = (((seed ^ QHBASE64) ^ QHEPILOGUE64) ^ 0xFFFFFFFFFFFFFFFFull);

				seed -= decrementor;
			}
		}

#endif

#pragma endregion

#pragma region Hashing

		// 0.0000000233% collision rate among 65535 unique 2-byte data sets ( 1 out of 4,294,770,690 possible collisions )
		__compelled_inline static qhash32_t __regcall qhash32(void* data, uint32_t length) noexcept {
			/* check if our global variables have been initialized */
			if (!initialized32) {
				qtable32_gen();

				initialized32 = true;
			}

			/* initialize base hash32 value constant within structure */
			qhash32_t hash_r{

				QHBASE32
			};

			for (auto i = 0; i < length; ++i) {
				for (auto x = 0; x < sizeof(decltype(hash_r.hash)); ++x)
					reinterpret_cast<std::uint8_t*>(&hash_r.hash)[x] ^= reinterpret_cast<std::uint8_t*>(data)[i];

				hash_r.hash ^= qtable32[reinterpret_cast<std::uint8_t*>(data)[i] ^ 0xFF];
			}

			auto preamble_result = hash_r.hash;

			/* initialize epilogue with base epilogue constant */
			auto epilogue = QHEPILOGUE32;

			std::uint8_t least_significant = reinterpret_cast<std::uint8_t*>(data)[0];
			std::uint8_t most_significant = (length > 1 ? reinterpret_cast<std::uint8_t*>(data)[length - 1] : MOST_SIGNIFICANT_DEFAULT);

			std::uint32_t least_significant_length = length;
			std::uint32_t most_significant_length = length;

			for (auto i = 0; i < sizeof(decltype(length)); ++i) {

				*reinterpret_cast<std::uint8_t*>(&least_significant_length) ^= least_significant;
				*reinterpret_cast<std::uint8_t*>(&most_significant_length) ^= most_significant;
			}

			bool significance_switch = false;

			for (auto i = 0; i < sizeof(hash_r.hash); ++i) {

				/* inverse significance flag */
				significance_switch = (significance_switch ? false : true);

				/* incrementally shift the bits left to ensure the entire output word has been marked by the sizeof(data) (this is more important for smaller datasets to reduce collision rates) */
				epilogue ^= static_cast<uint32_t>((QHEPILOGUE32 ^ (length << ((length * 8) % (((i == 0 ? 1 : i) * 8))))));
				reinterpret_cast<byte*>(&hash_r.hash)[i] ^= reinterpret_cast<std::uint8_t*>(&epilogue)[i];

				/* shift length left i * (sizeof( byte in bits ), xor hash by results to make the result more unique */
				hash_r.hash ^= (((significance_switch ? most_significant_length : least_significant_length) << (32 - ((i * 8) > 0 ? (i * 8) : 8))));
			}

			auto epilogue_result = hash_r.hash;

			hash_r.hash = (preamble_result & epilogue_result) ^ ((0xFFFFFFFF - (most_significant * 255) - (least_significant * 128)));

			return hash_r;
		}

#ifdef _WIN64
		//  0.00% collision rate among every possible 2-byte data set ( 0 out of 4,294,770,690 possible collisions )
		__compelled_inline static qhash64_t __regcall qhash64(void* data, size_t length) noexcept {
			/* check if our global variables have been initialized */
			if (!initialized64) {

				qtable64_gen();

				initialized64 = true;
			}

			/* initialize base hash64 value constant within structure */
			qhash64_t hash_r{
				QHBASE64
			};

			for (auto i = 0; i < length; ++i) {

				for (auto x = 0; x < sizeof(decltype(hash_r.hash)); ++x)
					reinterpret_cast<std::uint8_t*>(&hash_r.hash)[x] ^= reinterpret_cast<std::uint8_t*>(data)[i];

				hash_r.hash ^= qtable64[reinterpret_cast<std::uint8_t*>(data)[i] ^ 0xFF];
			}
			auto preamble_result = hash_r.hash;

			/* initialize epilogue with base epilogue constant */
			auto epilogue = QHEPILOGUE64;

			std::uint8_t least_significant = reinterpret_cast<std::uint8_t*>(data)[0];
			std::uint8_t most_significant = (length > 1 ? reinterpret_cast<std::uint8_t*>(data)[length - 1] : MOST_SIGNIFICANT_DEFAULT);

			std::uint64_t least_significant_length = length;
			std::uint64_t most_significant_length = length;

			for (auto i = 0; i < sizeof(decltype(length)); ++i) {

				*reinterpret_cast<std::uint8_t*>(&least_significant_length) ^= least_significant;
				*reinterpret_cast<std::uint8_t*>(&most_significant_length) ^= most_significant;
			}

			bool significance_switch = false;

			for (auto i = 0; i < sizeof(hash_r.hash); ++i) {
				/* inverse significance flag */
				significance_switch = (significance_switch ? false : true);

				/* incrementally shift the bits left to ensure the entire output word has been marked by the sizeof(data) (this is more important for smaller datasets) */
				epilogue ^= static_cast<uint64_t>((QHEPILOGUE64 ^ (length << ((length * 8) % (((i == 0 ? 1 : i) * 8))))));
				reinterpret_cast<byte*>(&hash_r.hash)[i] ^= reinterpret_cast<std::uint8_t*>(&epilogue)[i];

				/* shift length left i * (sizeof( byte in bits ), xor hash by results to make the result more unique */
				hash_r.hash ^= (((significance_switch ? most_significant_length : least_significant_length) << (64 - ((i * 8) > 0 ? (i * 8) : 8))));
			}

			auto epilogue_result = hash_r.hash;

			hash_r.hash = (preamble_result & epilogue_result) ^ ((0xFFFFFFFFFFFFFFFF - (most_significant * 255) - (least_significant * 128)));

			return hash_r;
		}

#endif

#pragma endregion

#pragma region CPU-Safe Template Accessor

		static __compelled_inline qhash_cpu_t __regcall qhash_cpu(void* data, size_t length) noexcept {

#ifdef _WIN64

			return qhash_cpu_t{ qhash64(data, length) };

#else

			return qhash_cpu_t{ qhash32(data, length) };

#endif

		}

#pragma endregion

	}

	bool qhash::initialized32 = false;

#ifdef _WIN64

	bool qhash::initialized64 = false;

#endif
	std::uint32_t qhash::qtable32[255] { };

#ifdef _WIN64

	std::uint64_t qhash::qtable64[255] { };

}

#endif

#pragma pack(pop)

#endif