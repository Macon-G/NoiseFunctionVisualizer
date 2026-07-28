#include "perlin.hpp"
#include "hash.hpp"
#include "noise_utils.hpp"

// #include <cmath>

Noise::Perlin::Perlin(uint32_t seed) : seed_(seed) {}

float Noise::Perlin::Sample(float x, float y) const {
	// Find the four lattice points around the sample.
	const int32_t
		x0{ static_cast<int32_t>(std::floor(x)) },
		x1{ x0 + 1 },
		y0{ static_cast<int32_t>(std::floor(y)) },
		y1{ y0 + 1 };

	// Measure the sample's offset from each lattice column and row.
	const float
		dx0{ x - static_cast<float>(x0) },
		dy0{ y - static_cast<float>(y0) },
		dx1{ dx0 - 1.0f },
		dy1{ dy0 - 1.0f };

	// Get gradient vectors (deterministic)
	const auto& gradients = Noise::Math::GRADIENT_VECTORS;
	const Math::GradientVector
		&g00{ gradients[Hash::Hash2D(x0, y0, seed_) & (Math::GRADIENT_VECTOR_COUNT - 1)] },
		&g01{ gradients[Hash::Hash2D(x0, y1, seed_) & (Math::GRADIENT_VECTOR_COUNT - 1)] },
		&g10{ gradients[Hash::Hash2D(x1, y0, seed_) & (Math::GRADIENT_VECTOR_COUNT - 1)] },
		&g11{ gradients[Hash::Hash2D(x1, y1, seed_) & (Math::GRADIENT_VECTOR_COUNT - 1)] };

	// Calculate each corner's gradient contribution
	const float
		dot00{ Math::Dot(g00.x, g00.y, dx0, dy0) },
		dot01{ Math::Dot(g01.x, g01.y, dx0, dy1) },
		dot10{ Math::Dot(g10.x, g10.y, dx1, dy0) },
		dot11{ Math::Dot(g11.x, g11.y, dx1, dy1) };

	// Smooth the interpolation amount along each axis.
	const float
		tx{ Math::Smootherstep(dx0) },
		ty{ Math::Smootherstep(dy0) };

	// Blend along x first, then blend those results along y.
	const float
		nx0{ Math::Lerp(tx, dot00, dot10) },
		nx1{ Math::Lerp(tx, dot01, dot11) };
	const float value = Math::Lerp(ty, nx0, nx1);

	// Scale output from [-1/sqrt(2), +1/sqrt(2)] to [-1, +1]
	return value * Math::SQRT_TWO;
}