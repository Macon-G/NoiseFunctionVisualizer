#pragma once

#include "noise/functions.hpp"

#include <array>
#include <string_view>

namespace Noise::Registry {

	// Distance Options
	struct WorleyDistanceOption {
		std::string_view name;
		Functions::WorleyDistanceMetric value;
	};

	inline constexpr auto WORLEY_DISTANCE_OPTIONS = std::array{
		WorleyDistanceOption{
			"Euclidean",
			Functions::WorleyDistanceMetric::EUCLIDEAN
		},
		WorleyDistanceOption{
			"Manhattan",
			Functions::WorleyDistanceMetric::MANHATTAN
		},
		WorleyDistanceOption{
			"Chebyshev",
			Functions::WorleyDistanceMetric::CHEBYSHEV
		},
	};

	[[nodiscard]]
	inline const char* GetWorleyDistanceOptionName(
		Functions::WorleyDistanceMetric value
	) {
		switch (value) {
		case Functions::WorleyDistanceMetric::CHEBYSHEV:
			return "Chebyshev";

		case Functions::WorleyDistanceMetric::EUCLIDEAN:
			return "Euclidean";

		case Functions::WorleyDistanceMetric::MANHATTAN:
			return "Manhattan";
		}

		return "Unknown";
	}

	// Output mode options

	struct WorleyOutputOption {
		std::string_view name;
		Functions::WorleyOutputMode value;
	};

	inline constexpr auto WORLEY_OUTPUT_OPTIONS = std::array{
		WorleyOutputOption{
			"F1",
			Functions::WorleyOutputMode::F1
		},
		WorleyOutputOption{
			"F2",
			Functions::WorleyOutputMode::F2
		},
		WorleyOutputOption{
			"F1 + F2",
			Functions::WorleyOutputMode::F1_ADD_F2
		},
		WorleyOutputOption{
			"F2 - F1",
			Functions::WorleyOutputMode::F2_SUB_F1
		},
		WorleyOutputOption{
			"F1 * F2",
			Functions::WorleyOutputMode::F1_MUL_F2
		},
		WorleyOutputOption{
			"F1 / F2",
			Functions::WorleyOutputMode::F1_DIV_F2
		},
		WorleyOutputOption{
			"Cell Value",
			Functions::WorleyOutputMode::CELL_VALUE
		}
	};

	[[nodiscard]]
	inline const char* GetWorleyOutputOptionName(
		Functions::WorleyOutputMode value
	) {
		switch(value) {
		case Functions::WorleyOutputMode::F1:
			return "F1";

		case Functions::WorleyOutputMode::F2:
			return "F2";

		case Functions::WorleyOutputMode::F1_ADD_F2:
			return "F1 + F2";

		case Functions::WorleyOutputMode::F2_SUB_F1:
			return "F2 - F1";

		case Functions::WorleyOutputMode::F1_MUL_F2:
			return "F1 * F2";

		case Functions::WorleyOutputMode::F1_DIV_F2:
			return "F1 / F2";
		
		case Functions::WorleyOutputMode::CELL_VALUE:
			return "Cell Value";
		}

		return "Unknown";
	}
}