#include "noise/noise.hpp"


namespace Noise::Functions {
	float White(float x, float y, u32 seed) {
		return Utilities::Rand01(Utilities::Hash2D(
			Math::FloorToInt(x),
			Math::FloorToInt(y),
			seed
		)) * 2.0f - 1.0f;
	}
}