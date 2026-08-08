#include "noise/modifiers/fbm.hpp"

#include <stdexcept>

namespace Noise::Modifiers {
	float FBM(
		Function source,
		const Functions::NoiseParameters& source_params,
		const FBMParameters& fbm_params
	) {
		if (source == nullptr) {
			throw std::runtime_error("FBM missing noise function source");
		}
		
		if (fbm_params.octaves < 1) {
			throw std::runtime_error("FBM must have at least one octave");
		}

		float value = 0.0f;
		float amplitude = 1.0f;
		float frequency = 1.0f;
		float amplitude_sum = 0.0f;

		Functions::NoiseParameters octave_params = source_params;

		for (u32 octave = 0; octave < fbm_params.octaves; ++octave) {
			octave_params.x = source_params.x * frequency;
			octave_params.y = source_params.y * frequency;

			value += source(octave_params) * amplitude;
			amplitude_sum += amplitude;
			
			frequency *= fbm_params.lacunarity;
			amplitude *= fbm_params.gain;
		}

		return amplitude_sum > 0.0f
			? value / amplitude_sum
			: 0.0f;
	}
}