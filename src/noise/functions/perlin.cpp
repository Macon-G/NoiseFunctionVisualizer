#include "noise/functions.hpp"
#include "noise/math.hpp"
#include "noise/utilities.hpp"

namespace Noise::Functions {
	float Perlin(const NoiseParameters& params) {
		// Find the four lattice points around the sample.
		const i32 x0 = Math::FloorToInt(params.x);
		const i32 y0 = Math::FloorToInt(params.y);
		const i32 x1 = x0 + 1;
		const i32 y1 = y0 + 1;

		// Measure the sample's offset from each lattice column and row.
		const float dx0 = params.x - static_cast<float>(x0);
		const float dy0 = params.y - static_cast<float>(y0);
		const float dx1 = dx0 - 1.0f;
		const float dy1 = dy0 - 1.0f;

		// Get gradient vectors (deterministic)
		const auto& gradients = Math::GRADIENT_VECTORS;

		const Math::Vec2& g00 = gradients[
			Utilities::Hash2D(x0, y0, params.seed) &
			(Math::GRADIENT_VECTOR_COUNT - 1)
		];
		const Math::Vec2& g01 = gradients[
			Utilities::Hash2D(x0, y1, params.seed) &
			(Math::GRADIENT_VECTOR_COUNT - 1)
		];
		const Math::Vec2& g10 = gradients[
			Utilities::Hash2D(x1, y0, params.seed) &
			(Math::GRADIENT_VECTOR_COUNT - 1)
		];
		const Math::Vec2& g11 = gradients[
			Utilities::Hash2D(x1, y1, params.seed) &
			(Math::GRADIENT_VECTOR_COUNT - 1)
		];

		// Calculate each corner's gradient contribution
		const float dot00 = Math::Dot(g00.x, g00.y, dx0, dy0);
		const float dot01 = Math::Dot(g01.x, g01.y, dx0, dy1);
		const float dot10 = Math::Dot(g10.x, g10.y, dx1, dy0);
		const float dot11 = Math::Dot(g11.x, g11.y, dx1, dy1);

		// Smooth the interpolation amount along each axis.
		const float tx = Math::Smootherstep(dx0);
		const float ty = Math::Smootherstep(dy0);

		// Blend along x first, then blend those results along y.
		const float nx0 = Math::Lerp(tx, dot00, dot10);
		const float nx1 = Math::Lerp(tx, dot01, dot11);

		const float value = Math::Lerp(ty, nx0, nx1);

		// Scale output from [-1/sqrt(2), +1/sqrt(2)] to [-1, +1]
		return value * Math::SQRT_TWO;
	}
}