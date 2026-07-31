// #include "noise/modifiers/fbm.hpp"

// Noise::FBM::FBM(
// 	const Generator& source,
// 	uint32_t octaves,
// 	float lacunarity,
// 	float gain
// ) : source_(source),
// 	octaves_(octaves),
// 	lacunarity_(lacunarity),
// 	gain_(gain)
// {}

#include "noise/noise.hpp"

namespace Noise::Modifiers {
	constexpr float FBM(
		Function source,
		float x,
		float y,
		u32 seed,
		const FBMParameters& params
	) {
		float value = 0.0f;
		float amplitude = 1.0f;
		float frequency = 1.0f;
		float max_amplitude = 0.0f;

		for (uint32_t i = 0; i < params.octaves; ++i) {
			value += source(
				x * frequency,
				y * frequency,
				seed
			) * amplitude;

			max_amplitude += amplitude;
			frequency *= params.lacunarity;
			amplitude *= params.gain;
		}

		if (max_amplitude > 0) {
			return value / max_amplitude;
		} else {
			return 0.0f;
		}
	}
}