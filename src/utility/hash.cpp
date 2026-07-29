#include "utility/hash.hpp"

namespace Noise::Hash {

    namespace {

        constexpr uint32_t PRIME_X = 0x1e65c3ef;
        constexpr uint32_t PRIME_Y = 0x9e3779b9;
        constexpr uint32_t PRIME_SEED = 0x85ebca6b;
        constexpr uint32_t AVALANCHE_PRIME = 0x045d9f3b;

        float ToFloat01(uint32_t hash) {
            return static_cast<float>(hash >> 8)
                 * (1.0f / 16777216.0f);
        }

    }

    uint32_t Hash2D(int32_t x, int32_t y, uint32_t seed) {
        uint32_t h =
            (static_cast<uint32_t>(x) * PRIME_X) ^
            (static_cast<uint32_t>(y) * PRIME_Y) ^
            (seed * PRIME_SEED);

        h = ((h >> 16) ^ h) * AVALANCHE_PRIME;
        h = ((h >> 16) ^ h) * AVALANCHE_PRIME;
        h = (h >> 16) ^ h;

        return h;
    }

    uint32_t HashString(std::string_view str) {
        // DJB2 string hashing algorithm

        uint32_t h = 5381; // Magic number

        for (char c : str) {
            // (h * 33) ^ c
            h = ((h << 5) + h) ^ static_cast<uint8_t>(c);
        }

        return h;
    }

    float Rand01(int32_t x, int32_t y, uint32_t seed) {
        return ToFloat01(Hash2D(x, y, seed));
    }

    float RandMax(
        int32_t x,
        int32_t y,
        uint32_t seed,
        float max
    ) {
        return Rand01(x, y, seed) * max;
    }

    float RandRange(
        int32_t x,
        int32_t y,
        uint32_t seed,
        float min,
        float max
    ) {
        return min + Rand01(x, y, seed) * (max - min);
    }

}