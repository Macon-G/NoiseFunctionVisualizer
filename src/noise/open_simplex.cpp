#include "open_simplex.hpp"

#include "hash.hpp"
#include "noise_utils.hpp"

#include <cstddef>
#include <cstdint>

namespace Noise {
	OpenSimplex::OpenSimplex(uint32_t seed)
		: seed_(seed) {}

	float OpenSimplex::Sample(float x, float y) const {
		// Transform the square coordinate space into the triangular
		// lattice coordinate space used by OpenSimplex2.
		const float skew = SKEW_2D_ * (x + y);

		const float x_skewed = x + skew;
		const float y_skewed = y + skew;

		// Find the base lattice coordinates.
		const int32_t lattice_x = Math::FloorToInt(x_skewed);
		const int32_t lattice_y = Math::FloorToInt(y_skewed);

		// Position within the skewed lattice cell.
		const float local_x =
			x_skewed - static_cast<float>(lattice_x);

		const float local_y =
			y_skewed - static_cast<float>(lattice_y);

		return EvaluateLattice(
			lattice_x,
			lattice_y,
			local_x,
			local_y
		);
	}

	float OpenSimplex::EvaluateLattice(
		int32_t lattice_x,
		int32_t lattice_y,
		float local_x,
		float local_y
	) const {
		// Transform the local coordinates back into the unskewed
		// triangular lattice space.
		const float unskew =
			UNSKEW_2D_ * (local_x + local_y);

		const float dx0 = local_x + unskew;
		const float dy0 = local_y + unskew;

		float value = 0.0f;

		// First vertex: base lattice point.
		value += Contribution(
			lattice_x,
			lattice_y,
			dx0,
			dy0
		);

		// Second vertex: diagonally opposite lattice point.
		constexpr float diagonal_offset =
			1.0f + 2.0f * UNSKEW_2D_;

		const float dx1 = dx0 - diagonal_offset;
		const float dy1 = dy0 - diagonal_offset;

		value += Contribution(
			lattice_x + 1,
			lattice_y + 1,
			dx1,
			dy1
		);

		// Third vertex depends on which triangular half of the
		// skewed cell contains the sample.
		if (dy0 > dx0) {
			const float dx2 =
				dx0 - UNSKEW_2D_;

			const float dy2 =
				dy0 - (UNSKEW_2D_ + 1.0f);

			value += Contribution(
				lattice_x,
				lattice_y + 1,
				dx2,
				dy2
			);
		}
		else {
			const float dx2 =
				dx0 - (UNSKEW_2D_ + 1.0f);

			const float dy2 =
				dy0 - UNSKEW_2D_;

			value += Contribution(
				lattice_x + 1,
				lattice_y,
				dx2,
				dy2
			);
		}

		return value * NORMALIZATION_2D_;
	}

	float OpenSimplex::Contribution(
		int32_t lattice_x,
		int32_t lattice_y,
		float dx,
		float dy
	) const {
		// Vertices outside the influence radius contribute nothing.
		float attenuation =
			RSQUARED_2D_ -
			dx * dx -
			dy * dy;

		if (attenuation <= 0.0f) {
			return 0.0f;
		}

		const Math::GradientVector& gradient =
			GetGradient(lattice_x, lattice_y);

		const float extrapolation =
			gradient.x * dx +
			gradient.y * dy;

		// attenuation^4 creates a smooth radial falloff.
		const float attenuation_sq =
			attenuation * attenuation;

		return attenuation_sq *
			   attenuation_sq *
			   extrapolation;
	}

	const Math::GradientVector& OpenSimplex::GetGradient(
		int32_t lattice_x,
		int32_t lattice_y
	) const {
		const uint32_t hash =
			Hash::Hash2D(lattice_x, lattice_y, seed_);

		const std::size_t index =
			static_cast<std::size_t>(hash) %
			Math::GRADIENT_VECTORS.size();

		return Math::GRADIENT_VECTORS[index];
	}
}