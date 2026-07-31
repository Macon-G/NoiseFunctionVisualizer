#include "noise/noise.hpp"

#include <array>
#include <cmath>
#include <numbers>
#include <stdexcept>
#include <limits>

namespace Noise::Math {

	constexpr float Abs(float x) {
		return x < 0.0f ? -x : x;
	}

	constexpr float NormalizeAngle(float x) {
		while (x > Constants::PI)
			x -= Constants::TWO_PI;
		while (x < -Constants::PI)
			x += Constants::TWO_PI;
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

	constexpr float Sqrt(float x) {
		// Newton-Raphson method

		if (x < 0.0) {
			// Since throwing an exception is illegal at compile-time,
			// causes compilation to fail if given a negative input.
			// This is 100% intentional, since it is impossible to take
			// the square root of a negative number.
			throw std::invalid_argument("Cannot take the square root of a negative number");
		}
		if (x == 0.0 || x == std::numeric_limits<float>::infinity()) {
			return x;
		}
		
		float result = x;
		float prev = 0.0f;

		// Stabilize the value
		while (result != prev) {
			result = 0.5 * (result + x / result);
			prev = result;
		}

		return result;
	}

	constexpr float Dot(
		float ax,
		float ay,
		float bx,
		float by
	) {
		return ax * bx + ay * by;
	}

	constexpr float Lerp(
		float t,
		float a,
		float b
	) {
		return a + (b - a) * t;
	}

	constexpr float LerpInverse(
		float v,
		float a,
		float b
	) {
		return (v - a) / (b - a);
	}

	constexpr i32 FloorToInt(float x) noexcept {
		return static_cast<i32>(std::floorf(x));
	} 

	constexpr float Clamp(
		float v,
		float min,
		float max
	) {
		return std::max(min, std::min(max, v));
	}

	constexpr float Remap(
		float v,
		float a0,
		float b0,
		float a1,
		float b1
	) {
		float t = LerpInverse(v, a0, b0);
		return Lerp(t, a1, b1);
	}

	constexpr float Smoothstep(float x) {	// Smooths the value
		return x * x * (3 - x * 2);
	}

	constexpr float Smootherstep(float x) {	// Smooths the value
		return x * x * x * (x * (x * 6 - 15) + 10);
	}

}