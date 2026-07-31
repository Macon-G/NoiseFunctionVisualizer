#include "noise/noise.hpp"

#include <cmath>

namespace Noise::Functions {
	float Worley(float x, float y, u32 seed) {
		// Grid coordinate
		const int32_t grid_x = Math::FloorToInt(x);
		const int32_t grid_y = Math::FloorToInt(y);

		// Find distance to closest feature point
		// The largest possible distance to the nearest feature point is guaranteed to be sqrt(2)
		// Keep it squared for speed and efficiency: sqrt(2)^2 = 2. Output range = [0, 2]
		float closest_dist_sq = 2.0f;

		// Search all neighboring cells for shorter distances
		for (int32_t offset_y = -2; offset_y <= 2; ++offset_y) {
			for (int32_t offset_x = -2; offset_x <= 2; ++offset_x) {
				// Current cell coords
				const int32_t curr_x = grid_x + offset_x;
				const int32_t curr_y = grid_y + offset_y;

				// Generate one deterministic feature point within this cell
				const float feat_x =
					static_cast<float>(curr_x) +
					Utilities::Rand01(
						Utilities::Hash2D(curr_x, curr_y, seed)
					);
				
				const float feat_y =
					static_cast<float>(curr_y) +
					Utilities::Rand01(
						Utilities::Hash2D(curr_x, curr_y, seed + 1u)
					);

				const float delta_x = feat_x - x;
				const float delta_y = feat_y - y;

				const float dist_sq =
					delta_x * delta_x +
					delta_y * delta_y;

				if (dist_sq < closest_dist_sq) {
					closest_dist_sq = dist_sq;
				}
			}
		}

		// Convert squared distance to Euclidean distance and map
		// from [0, sqrt(2)] to [-1, 1].
		return std::sqrt(closest_dist_sq) * Constants::SQRT_TWO - 1.0f;
	}
}