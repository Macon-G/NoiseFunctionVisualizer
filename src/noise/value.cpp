#include "value.hpp"

#include "hash.hpp"
#include "noise_utils.hpp"

Noise::Value::Value(uint32_t seed) : seed_(seed) {}

float Noise::Value::Sample(float x, float y) const {
	// Get cell coords
	const int32_t grid_x = Math::FloorToInt(x);
	const int32_t grid_y = Math::FloorToInt(y);

	// Get local coordinates
	const float local_x = x - static_cast<float>(grid_x);
	const float local_y = y - static_cast<float>(grid_y);

	const float u = Math::Smootherstep(local_x);
	const float v = Math::Smootherstep(local_y);

	const float value_00 = Hash::Rand01(grid_x, grid_y, seed_);
	const float value_01 = Hash::Rand01(grid_x, grid_y + 1, seed_);
	const float value_10 = Hash::Rand01(grid_x + 1, grid_y, seed_);
	const float value_11 = Hash::Rand01(grid_x + 1, grid_y + 1, seed_);

	const float bottom = Math::Lerp(u, value_00, value_10);
	const float top = Math::Lerp(u, value_01, value_11);

	const float value = Math::Lerp(v, bottom, top);

	return value * 2.0f - 1.0f;
}