#pragma once

#include "generator.hpp"
#include "noise_utils.hpp"

#include <cstdint>

namespace Noise {
	class OpenSimplex : public Generator {
	public:
		explicit OpenSimplex(uint32_t seed);

		[[nodiscard]] float Sample(float x, float y) const override;

	private:
		[[nodiscard]] float EvaluateLattice(
			int32_t lattice_x,
			int32_t lattice_y,
			float local_x,
			float local_y
		) const;

		[[nodiscard]] float Contribution(
			int32_t lattice_x,
			int32_t lattice_y,
			float dx,
			float dy
		) const;

		[[nodiscard]] const Math::GradientVector& GetGradient(
			int32_t lattice_x,
			int32_t lattice_y
		) const;

		// (sqrt(3) - 1) / 2
		static constexpr float SKEW_2D_ =
			(Math::Detail::Sqrt(3.0f) - 1.0f) / 2.0f;

		// (1 - sqrt(3)) / 6
		static constexpr float UNSKEW_2D_ =
			(1.0f - Math::Detail::Sqrt(3.0f)) / 6.0f;

		// Radius squared of each lattice vertex's influence.
		static constexpr float RSQUARED_2D_ = 0.5f;

		// Reference OpenSimplex2 2D gradients are scaled by
		// 1 / 0.01001634121365712.
		//
		// This applies the equivalent scaling after summing when
		// Math::GRADIENT_VECTORS contains unit-length gradients.
		static constexpr float NORMALIZATION_2D_ =
			1.0f / 0.01001634121365712f;

		uint32_t seed_;
	};
}