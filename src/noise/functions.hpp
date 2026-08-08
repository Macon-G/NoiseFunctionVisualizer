#pragma once

#include <cstdint>

namespace Noise {
	using u32 = std::uint32_t;
	using i32 = std::int32_t;

	namespace Functions {
		enum class WorleyDistanceMetric {
			EUCLIDEAN,
			MANHATTAN,
			CHEBYSHEV
		};

		enum class WorleyOutputMode {
			F1,
			F2,
			F1_ADD_F2,
			F2_SUB_F1,
			F1_MUL_F2,
			F1_DIV_F2,
			CELL_VALUE
		};

		struct NoiseParameters {
			// Generic
			float x = 0.0f;
			float y = 0.0f;
			u32 seed = 0;

			// Worley-specific
			WorleyDistanceMetric worley_distance_type =
				WorleyDistanceMetric::EUCLIDEAN;
			WorleyOutputMode worley_output_mode =
				WorleyOutputMode::F1;
		};
	}

	using Function = float (*)(const Functions::NoiseParameters&);

	namespace Functions {
		[[nodiscard]]
		float OpenSimplex(const NoiseParameters& params);
		
		[[nodiscard]]
		float Perlin(const NoiseParameters& params);
		
		[[nodiscard]]
		float Value(const NoiseParameters& params);
		
		[[nodiscard]]
		float White(const NoiseParameters& params);

		[[nodiscard]]
		float Worley(const NoiseParameters& params);
	}
}