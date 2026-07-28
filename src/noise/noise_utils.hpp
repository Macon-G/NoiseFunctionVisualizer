#pragma once

#include <array>
#include <cmath>
#include <algorithm>
#include <numbers>
#include <cstdint>

namespace Noise::Math {
	struct GradientVector {
		float x;
		float y;
	};

	inline constexpr float PI = std::numbers::pi_v<float>;

	inline constexpr float TWO_PI = 2 * PI;
	
	inline constexpr float SQRT_TWO = std::numbers::sqrt2_v<float>;
	
	inline constexpr std::size_t GRADIENT_VECTOR_COUNT = 1024;

	namespace Detail{
		constexpr float abs(float x) {
			return x < 0.0f ? -x : x;
		}

		constexpr float NormalizeAngle(float x) {
			while (x > PI)
				x -= TWO_PI;
			while (x < -PI)
				x += TWO_PI;
			return x;
		}

		constexpr float Sin(float x) {
			x = NormalizeAngle(x);
			float term = x;
			float sum = x;
			float x_sq = x * x;

			for (int i = 1; i <= 6; ++i) {
				term *= -x_sq / ((2 * i) * (2 * i + 1));
				sum += term;
			}

			return sum;
		}

		constexpr float Cos(float x) {
			x = NormalizeAngle(x);
			float term = 1.0f;
			float sum = 1.0f;
			float x_sq = x * x;

			for (int i = 1; i <= 6; ++i) {
				term *= -x_sq / ((2 * i) * (2 * i - 1));
				sum += term;
			}

			return sum;
		}
	}

	inline constexpr auto GRADIENT_VECTORS = []{
		std::array<GradientVector, GRADIENT_VECTOR_COUNT> vectors{};
		for (size_t i = 0; i < GRADIENT_VECTOR_COUNT; ++i) {
			float angle = 
				TWO_PI * static_cast<float>(i)
				/ static_cast<float>(GRADIENT_VECTOR_COUNT);
			vectors[i] = {Detail::Cos(angle), Detail::Sin(angle)};
		}
		return vectors;
	}();

	inline constexpr float Dot(	// Dot product of two vectors
		float ax,
		float ay,
		float bx,
		float by
	) {
		return ax * bx + ay * by;
	}

	inline constexpr float Lerp(
		float t,
		float a,
		float b
	) {
		return a + (b - a) * t;
	}

	inline constexpr float LerpInverse(
		float v,
		float a,
		float b
	) {
		return (v - a) / (b - a);
	}

	inline constexpr int32_t FloorToInt(float x) noexcept {
		return static_cast<int32_t>(std::floorf(x));
	} 

	inline constexpr float Clamp(
		float v,
		float min,
		float max
	) {
		return std::max(min, std::min(max, v));
	}
	
	inline constexpr float Remap(
		float v,
		float a0,
		float b0,
		float a1,
		float b1
	) {
		float t = LerpInverse(v, a0, b0);
		return Lerp(t, a1, b1);
	}

	inline constexpr float Smoothstep(float x) {	// Smooths the value
		return x * x * (3 - x * 2);
	}

	inline constexpr float Smootherstep(float x) {	// Smooths the value
		return x * x * x * (x * (x * 6 - 15) + 10);
	}
}