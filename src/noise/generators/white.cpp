#include "noise/generators/white.hpp"

#include "utility/hash.hpp"
#include "noise/noise_utils.hpp"

Noise::White::White(uint32_t seed) : seed_(seed) {}

float Noise::White::Sample(float x, float y) const {
	int gx = Math::FloorToInt(x);
	int gy = Math::FloorToInt(y);

	return Hash::Rand01(gx, gy, seed_) * 2.0f - 1.0f;
}