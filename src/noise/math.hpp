#pragma once

#include <array>
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <numbers>
#include <stdexcept>
#include <limits>

namespace Noise::Math {
	using u32 = std::uint32_t;
	using i32 = std::int32_t;
	using std::size_t;

	inline constexpr float PI =
        std::numbers::pi_v<float>;

    inline constexpr float TWO_PI =
        2.0f * PI;

    inline constexpr float SQRT_TWO =
        std::numbers::sqrt2_v<float>;

    struct Vec2 {
        float x;
        float y;
    };

	[[nodiscard]]
	inline constexpr float Abs(float x) {
		return x < 0.0f ? -x : x;
	}

	[[nodiscard]]
	inline constexpr float NormalizeAngle(float x) {
		while (x > PI)
			x -= TWO_PI;
		while (x < -PI)
			x += TWO_PI;
		return x;
	}

	[[nodiscard]]
	inline constexpr float Sin(float x) {
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

	[[nodiscard]]
	inline constexpr float Cos(float x) {
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

	[[nodiscard]]
	inline constexpr float Sqrt(float x) {
		if (x < 0.0) {
			throw std::invalid_argument("Cannot take the square root of a negative number");
		}
		if (x == 0.0 || x == std::numeric_limits<float>::infinity()) {
			return x;
		}
		
		float result = x;
		
		for (int iteration = 0; iteration < 32; ++iteration) {	// Limit to 32 iterations
			const float previous = result;

			result = 0.5 * (
				result +
				x / result
			);

			if (result == previous) {	// Exit early if value stabilizes
				break;
			}
		}

		return result;
	}

	[[nodiscard]]
	inline constexpr float Dot(
		float ax,
		float ay,
		float bx,
		float by
	) {
		return ax * bx + ay * by;
	}

	[[nodiscard]]
	inline constexpr float Lerp(
		float t,
		float a,
		float b
	) {
		return a + (b - a) * t;
	}

	[[nodiscard]]
	inline constexpr float LerpInverse(
		float v,
		float a,
		float b
	) {
		return (v - a) / (b - a);
	}

	[[nodiscard]]
	inline i32 FloorToInt(float x) noexcept {
		return static_cast<i32>(std::floorf(x));
	} 

	[[nodiscard]]
	inline constexpr float Clamp(
		float v,
		float min,
		float max
	) {
		return std::max(min, std::min(max, v));
	}

	[[nodiscard]]
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

	[[nodiscard]]
	inline constexpr float Smoothstep(float x) {	// Smooths the value
		return x * x * (3 - x * 2);
	}

	[[nodiscard]]
	inline constexpr float Smootherstep(float x) {	// Smooths the value
		return x * x * x * (x * (x * 6 - 15) + 10);
	}

	inline constexpr std::size_t
        GRADIENT_VECTOR_COUNT = 1024;

    inline constexpr auto GRADIENT_VECTORS = [] {
        std::array<Vec2, GRADIENT_VECTOR_COUNT> vectors{};

        for (
            std::size_t i = 0;
            i < GRADIENT_VECTOR_COUNT;
            ++i
        ) {
            const float angle =
                TWO_PI * static_cast<float>(i) /
                static_cast<float>(
                    GRADIENT_VECTOR_COUNT
                );

            vectors[i] = {
                Cos(angle),
                Sin(angle)
            };
        }

        return vectors;
    }();
}