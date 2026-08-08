#include "noise/functions.hpp"
#include "noise/math.hpp"
#include "noise/utilities.hpp"

namespace Noise::Functions {
	float White(const NoiseParameters& params) {
		return Utilities::Rand01(Utilities::Hash2D(
			Math::FloorToInt(params.x),
			Math::FloorToInt(params.y),
			params.seed
		)) * 2.0f - 1.0f;
	}
}