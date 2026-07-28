#include "fbm.hpp"

Noise::FBM::FBM(
	const Generator& source,
	uint32_t octaves,
	float lacunarity,
	float gain
) : source_(source),
	octaves_(octaves),
	lacunarity_(lacunarity),
	gain_(gain)
{}


float Noise::FBM::Sample(float x, float y) const {
	float value = 0.0f;
	float amplitude = 1.0f;
	float frequency = 1.0f;
	float max_amplitude = 0.0f;

	for (uint32_t i = 0; i < octaves_; ++i) {
		value += source_.Sample(
			static_cast<float>(x) * frequency,
			static_cast<float>(y) * frequency
		) * amplitude;

		max_amplitude += amplitude;
		frequency *= lacunarity_;
		amplitude *= gain_;
	}

	return max_amplitude > 0 ? value / max_amplitude : 0;
}