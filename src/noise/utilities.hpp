#pragma once

#include <bit>
#include <cstdint>
#include <string_view>

namespace Noise::Utilities {
    using u32 = std::uint32_t;
    using i32 = std::int32_t;

    namespace {

        constexpr u32 PRIME_X = 0x1e65c3ef;
        constexpr u32 PRIME_Y = 0x9e3779b9;
        constexpr u32 PRIME_SEED = 0x85ebca6b;
        constexpr u32 AVALANCHE_PRIME = 0x045d9f3b;

        constexpr u32 LOW_16_MASK = 0x0000FFFF;
        constexpr float SCALE_24 = 1.0f / 16'777'216.0f;
        constexpr float SCALE_16 = 1.0f / 65'536.0f;

    }

    [[nodiscard]]
    inline constexpr u32 HashString(std::string_view str) {
        // DJB2 string hashing algorithm

        u32 h = 5381; // Magic number

        for (char c : str) {
            // (h * 33) ^ c
            h = ((h << 5) + h) ^ static_cast<uint8_t>(c);
        }

        return h;
    }

    [[nodiscard]]
    inline constexpr i32 FloatToI32(float x) {
        return std::bit_cast<i32>(x);
    }

    [[nodiscard]]
    inline constexpr u32 Hash2D(i32 x, i32 y, u32 seed) {
        u32 h =
            (static_cast<u32>(x) * PRIME_X) ^
            (static_cast<u32>(y) * PRIME_Y) ^
            (seed * PRIME_SEED);

        h = ((h >> 16) ^ h) * AVALANCHE_PRIME;
        h = ((h >> 16) ^ h) * AVALANCHE_PRIME;
        h = (h >> 16) ^ h;

        return h;
    }

    [[nodiscard]]
    inline constexpr u32 Hash2D(float x, float y, u32 seed) {
        return Hash2D(
            FloatToI32(x),
            FloatToI32(y),
            seed
        );
    }


    // Range: [0, 1)
    [[nodiscard]]
    inline constexpr float Rand01(u32 hash) noexcept {
        // Floats have 24 bit mantissa.
        // Mantissa range: [1.0f, 2.0f)
        // 2^24 = 16,777,216

        // Shift the input hash by 8 bits to get a 24 bit number.
        // Scale by 1 / 16,777,216 to get the result.
        return static_cast<float>(hash >> 8) * SCALE_24;
    }

    // Range: [0, 1)
    [[nodiscard]]
    inline constexpr float Rand01FromLow16(u32 hash) noexcept {
        return static_cast<float>(hash & LOW_16_MASK) * SCALE_16;
    }

    // Range: [0, 1)
    [[nodiscard]]
    inline constexpr float Rand01FromHigh16(u32 hash) noexcept {
        return static_cast<float>(hash >> 16) * SCALE_16;
    }
}