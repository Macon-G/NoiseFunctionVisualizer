#include "noise/functions.hpp"
#include "noise/math.hpp"
#include "noise/utilities.hpp"

#include <algorithm>
#include <cmath>
#include <limits>

namespace Noise::Functions {

	namespace {

		constexpr float SQRT_TWO = Math::SQRT_TWO;
		constexpr float SQRT_FIVE_HALVES = 1.58113883008f;

		struct DistanceMetrics {
			float Euclidean = std::numeric_limits<float>::max();
			float Manhattan = std::numeric_limits<float>::max();
			float Chebyshev = std::numeric_limits<float>::max();
		};

		struct FeatureHashes {
			u32 Euclidean = 0;
			u32 Manhattan = 0;
			u32 Chebyshev = 0;
		};

		struct WorleyDistances {
			DistanceMetrics F1;
			DistanceMetrics F2;
			FeatureHashes F1Hash;
		};

		struct WorleyOutputMaximums {
			float F1;
			float F2;
			float F1AddF2;
			float F2SubF1;
			float F1MulF2;
			float F1DivF2;
		};

		constexpr WorleyOutputMaximums EUCLIDEAN_MAXIMUMS{
			.F1 = SQRT_TWO,
			.F2 = SQRT_FIVE_HALVES,
			.F1AddF2 = 2.0f * SQRT_TWO,
			.F2SubF1 = SQRT_FIVE_HALVES,
			.F1MulF2 = 2.0f,
			.F1DivF2 = 1.0f
		};

		constexpr WorleyOutputMaximums MANHATTAN_MAXIMUMS{
			.F1 = 2.0f,
			.F2 = 2.0f,
			.F1AddF2 = 4.0f,
			.F2SubF1 = 2.0f,
			.F1MulF2 = 4.0f,
			.F1DivF2 = 1.0f
		};

		constexpr WorleyOutputMaximums CHEBYSHEV_MAXIMUMS{
			.F1 = 1.0f,
			.F2 = 1.5f,
			.F1AddF2 = 2.0f,
			.F2SubF1 = 1.5f,
			.F1MulF2 = 1.0f,
			.F1DivF2 = 1.0f
		};

		[[nodiscard]]
		constexpr float NormalizeToSigned(
			float value,
			float maximum
		) noexcept {
			const float normalized = value / maximum;
			return normalized * 2.0f - 1.0f;
		}

		[[nodiscard]]
		WorleyDistances GetWorleyDistances(
			float x,
			float y,
			u32 seed
		) {
			DistanceMetrics f1{};
			DistanceMetrics f2{};

			FeatureHashes f1_hash{};

			const i32 origin_cell_x = Math::FloorToInt(x);
			const i32 origin_cell_y = Math::FloorToInt(y);

			for (i32 offset_y = -2; offset_y <= 2; ++offset_y) {
				for (i32 offset_x = -2; offset_x <= 2; ++offset_x) {

					const i32 cell_x =
						origin_cell_x + offset_x;

					const i32 cell_y =
						origin_cell_y + offset_y;

					const u32 hash = Utilities::Hash2D(
						cell_x,
						cell_y,
						seed
					);

					const float feature_x =
						static_cast<float>(cell_x) +
						Utilities::Rand01FromHigh16(hash);

					const float feature_y =
						static_cast<float>(cell_y) +
						Utilities::Rand01FromLow16(hash);

					const float delta_x =
						feature_x - x;

					const float delta_y =
						feature_y - y;

					const float abs_delta_x =
						std::abs(delta_x);

					const float abs_delta_y =
						std::abs(delta_y);

					const float curr_manhattan =
						abs_delta_x +
						abs_delta_y;

					const float curr_dist_sq =
						delta_x * delta_x +
						delta_y * delta_y;

					const float curr_chebyshev =
						std::max(
							abs_delta_x,
							abs_delta_y
						);

					// Manhattan
					if (curr_manhattan < f1.Manhattan) {
						f2.Manhattan = f1.Manhattan;
						f1.Manhattan = curr_manhattan;

						f1_hash.Manhattan = hash;
					}
					else if (curr_manhattan < f2.Manhattan) {
						f2.Manhattan = curr_manhattan;
					}

					// Euclidean
					if (curr_dist_sq < f1.Euclidean) {
						f2.Euclidean = f1.Euclidean;
						f1.Euclidean = curr_dist_sq;

						f1_hash.Euclidean = hash;
					}
					else if (curr_dist_sq < f2.Euclidean) {
						f2.Euclidean = curr_dist_sq;
					}

					// Chebyshev
					if (curr_chebyshev < f1.Chebyshev) {
						f2.Chebyshev = f1.Chebyshev;
						f1.Chebyshev = curr_chebyshev;

						f1_hash.Chebyshev = hash;
					}
					else if (
						curr_chebyshev <
						f2.Chebyshev
					) {
						f2.Chebyshev =
							curr_chebyshev;
					}
				}
			}

			// Convert squared Euclidean distances
			// into actual Euclidean distances.
			f1.Euclidean =
				std::sqrt(f1.Euclidean);

			f2.Euclidean =
				std::sqrt(f2.Euclidean);

			return {
				.F1 = f1,
				.F2 = f2,
				.F1Hash = f1_hash
			};
		}

	} // anonymous namespace

	float Worley(const NoiseParameters& params) {

		const WorleyDistances distances =
			GetWorleyDistances(
				params.x,
				params.y,
				params.seed
			);

		float f1 = 0.0f;
		float f2 = 0.0f;

		u32 f1_hash = 0;

		const WorleyOutputMaximums* maximums = nullptr;

		switch (params.worley_distance_type) {

		case WorleyDistanceMetric::EUCLIDEAN:
			f1 = distances.F1.Euclidean;
			f2 = distances.F2.Euclidean;

			f1_hash =
				distances.F1Hash.Euclidean;

			maximums =
				&EUCLIDEAN_MAXIMUMS;

			break;

		case WorleyDistanceMetric::MANHATTAN:
			f1 = distances.F1.Manhattan;
			f2 = distances.F2.Manhattan;

			f1_hash =
				distances.F1Hash.Manhattan;

			maximums =
				&MANHATTAN_MAXIMUMS;

			break;

		case WorleyDistanceMetric::CHEBYSHEV:
			f1 = distances.F1.Chebyshev;
			f2 = distances.F2.Chebyshev;

			f1_hash =
				distances.F1Hash.Chebyshev;

			maximums =
				&CHEBYSHEV_MAXIMUMS;

			break;
		}

		float result = 0.0f;
		float result_max = 1.0f;

		switch (params.worley_output_mode) {

		case WorleyOutputMode::F1:
			result = f1;
			result_max = maximums->F1;
			break;

		case WorleyOutputMode::F2:
			result = f2;
			result_max = maximums->F2;
			break;

		case WorleyOutputMode::F1_ADD_F2:
			result = f1 + f2;
			result_max =
				maximums->F1AddF2;
			break;

		case WorleyOutputMode::F2_SUB_F1:
			result = f2 - f1;
			result_max =
				maximums->F2SubF1;
			break;

		case WorleyOutputMode::F1_MUL_F2:
			result = f1 * f2;
			result_max =
				maximums->F1MulF2;
			break;

		case WorleyOutputMode::F1_DIV_F2:
			result =
				(f2 > 0.0f)
				? (f1 / f2)
				: 0.0f;

			result_max =
				maximums->F1DivF2;

			break;

		case WorleyOutputMode::CELL_VALUE:
			/*
			 * The hash already uniquely identifies the
			 * feature point's source cell.
			 *
			 * Using it directly ensures that every pixel
			 * owned by the same nearest feature point
			 * receives exactly the same value.
			 */
			result =
				Utilities::Rand01(f1_hash);

			result_max = 1.0f;

			break;
		}

		return std::clamp(
			NormalizeToSigned(
				result,
				result_max
			),
			-1.0f,
			1.0f
		);
	}

}