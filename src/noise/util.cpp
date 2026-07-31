#include "noise/noise.hpp"

#include <cstdint>

namespace Utilities {
    using u32 = std::uint32_t;
    using i32 = std::int32_t;

    namespace {

        constexpr u32 PRIME_X = 0x1e65c3ef;
        constexpr u32 PRIME_Y = 0x9e3779b9;
        constexpr u32 PRIME_SEED = 0x85ebca6b;
        constexpr u32 AVALANCHE_PRIME = 0x045d9f3b;

        [[nodiscard]]
        inline constexpr float ToFloat01(u32 hash) {
            return static_cast<float>(hash >> 8)
                 * (1.0f / 16777216.0f);
        }

    }

    constexpr u32 Hash2D(i32 x, i32 y, u32 seed) {
        u32 h =
            (static_cast<u32>(x) * PRIME_X) ^
            (static_cast<u32>(y) * PRIME_Y) ^
            (seed * PRIME_SEED);

        h = ((h >> 16) ^ h) * AVALANCHE_PRIME;
        h = ((h >> 16) ^ h) * AVALANCHE_PRIME;
        h = (h >> 16) ^ h;

        return h;
    }

    constexpr u32 HashString(std::string_view str) {
        // DJB2 string hashing algorithm

        u32 h = 5381; // Magic number

        for (char c : str) {
            // (h * 33) ^ c
            h = ((h << 5) + h) ^ static_cast<uint8_t>(c);
        }

        return h;
    }

    constexpr float Rand01(u32 hash) {
        return ToFloat01(hash);
    }

    constexpr float RandMax(u32 hash, float upper) {
        return Rand01(hash) * upper;
    }

    constexpr float RandRange(u32 hash, float min, float max) {
        return min + Rand01(hash) * (max - min);
    }

}