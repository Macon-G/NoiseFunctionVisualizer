#pragma once

#include "noise/functions.hpp"

namespace Noise::Modifiers {
	struct FBMParameters {
		u32 octaves = 1;
		float gain = 0.5f;
		float lacunarity = 2.0f;

		// Enable per-value equality comparison
		constexpr bool operator==(const FBMParameters& other) const = default;
	};
	
	[[nodiscard]]
	float FBM(
		Function source,
		const Functions::NoiseParameters&,
		const FBMParameters& params
	);
}