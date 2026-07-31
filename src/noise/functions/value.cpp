#include "noise/noise.hpp"

namespace Noise::Functions {
	float Value(float x, float y, u32 seed) {
		// Get cell coords
		const int32_t grid_x = Math::FloorToInt(x);
		const int32_t grid_y = Math::FloorToInt(y);

		// Get local coordinates
		const float local_x = x - static_cast<float>(grid_x);
		const float local_y = y - static_cast<float>(grid_y);

		const float u = Math::Smootherstep(local_x);
		const float v = Math::Smootherstep(local_y);

		const float value_00 =
			Utilities::Rand01(
				Utilities::Hash2D(grid_x, grid_y, seed)
			);
		const float value_01 =
			Utilities::Rand01(
				Utilities::Hash2D(grid_x, grid_y + 1, seed)
			);
		const float value_10 =
			Utilities::Rand01(
				Utilities::Hash2D(grid_x + 1, grid_y, seed)
			);
		const float value_11 =
			Utilities::Rand01(
				Utilities::Hash2D(grid_x + 1, grid_y + 1, seed)
			);

		const float bottom = Math::Lerp(u, value_00, value_10);
		const float top = Math::Lerp(u, value_01, value_11);

		const float value = Math::Lerp(v, bottom, top);

		return value * 2.0f - 1.0f;
	}
}