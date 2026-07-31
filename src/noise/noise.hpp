#pragma once

#include <array>
#include <cstddef>
#include <cstdint>
#include <numbers>
#include <string_view>

namespace Noise {
	using std::size_t;
	
	using u32 = std::uint32_t;
	using i32 = std::int32_t;
	using Function = float (*)(float, float, u32);	// Type alias for noise function pointer

	namespace Constants { // Public Constants

		inline constexpr float PI = std::numbers::pi_v<float>;

		inline constexpr float TWO_PI = 2.0f * PI;

		inline constexpr float SQRT_TWO = std::numbers::sqrt2_v<float>;

		inline constexpr size_t GRADIENT_VECTOR_COUNT = 1024;

		inline constexpr auto GRADIENT_VECTORS = []{
			std::array<Math::GradientVector, Constants::GRADIENT_VECTOR_COUNT> vectors{};
			for (size_t i = 0; i < Constants::GRADIENT_VECTOR_COUNT; ++i) {
				float angle = 
					Constants::TWO_PI * static_cast<float>(i)
					/ static_cast<float>(Constants::GRADIENT_VECTOR_COUNT);
				vectors[i] = {Math::Cos(angle), Math::Sin(angle)};
			}
			return vectors;
		}();
	}

	namespace Functions {	// Noise Algorithms
		
		[[nodiscard]]
		float OpenSimplex(float x, float y, u32 seed);
		
		[[nodiscard]]
		float Perlin(float x, float y, u32 seed);
		
		[[nodiscard]]
		float Value(float x, float y, u32 seed);
		
		[[nodiscard]]
		float White(float x, float y, u32 seed);
		
		[[nodiscard]]
		float Worley(float x, float y, u32 seed);

	}

	namespace Modifiers {	// Noise function modifiers
		struct FBMParameters {
			u32 octaves;
			float gain;
			float lacunarity;
		};

		[[nodiscard]]
		constexpr float FBM(
			Function source,
			float x,
			float y,
			u32 seed,
			const FBMParameters& params
		);
	}
	
	namespace Math {

		// ==============================
		// Vector Operations
		// ==============================

		struct GradientVector {
			float x;
			float y;
		};

		constexpr float Dot(
			float ax,
			float ay,
			float bx,
			float by
		);

		// ==============================
		// Compile-time Math
		// ==============================
		
		// Absolute value of input value
		[[nodiscard]]
		inline constexpr float Abs(float x);
		
		// Normalize input angle to [0, 2*pi) (in radians)
		[[nodiscard]]
		inline constexpr float NormalizeAngle(float x);
		
		// Sine of input angle (in radians)
		[[nodiscard]]
		inline constexpr float Sin(float x);
		
		// Cosine of input angle (in radians)
		[[nodiscard]]
		inline constexpr float Cos(float x);
		
		// Square root of input value
		[[nodiscard]]
		inline constexpr float Sqrt(float x);
		
		// Clamp value to range
		[[nodiscard]]
		inline constexpr float Clamp(
			float v,
			float min,
			float max
		);
		
		// Floors float value and returns as 32-bit signed int
		[[nodiscard]]
		inline constexpr i32 FloorToInt(float x);
		
		// ==============================
		// Interpolation
		// ==============================
		
		// Linear interpolation
		[[nodiscard]]
		inline constexpr float Lerp(
			float t,
			float a,
			float b
		);

		// Inverse of linear interpolation
		[[nodiscard]]
		inline constexpr float LerpInverse(
			float v,
			float a,
			float b
		);

		// Returns the value of the percentage distance from a1 to b1
		// that matches the percentange distance of v from a0 to b0.
		[[nodiscard]]
		inline constexpr float Remap(
			float v,
			float a0,
			float b0,
			float a1,
			float b1
		);

		// Returns a smooth cubic interpolation between 0 and 1 when edge0 < x < edge1.
		[[nodiscard]]
		inline constexpr float Smoothstep(float x);

		// Returns an even smoother quintic interpolation with zero 1st and 2nd derivatives at edges.
		[[nodiscard]]
		inline constexpr float Smootherstep(float x);

	}

	namespace Utilities {
		
		// ==============================
		// Hashing
		// ==============================
		
		[[nodiscard]]
		constexpr u32 Hash2D(i32 x, i32 y, u32 seed);
		
		[[nodiscard]]
		constexpr u32 HashStr(std::string_view);
		
		// ==============================
		// Deterministic RNG
		// ==============================

		// Outputs in range [0, 1)
		[[nodiscard]]
		constexpr float Rand01(u32 hash);

		// Outputs in range [0, upper)
		[[nodiscard]]
		constexpr float RandMax(u32 hash, float upper);

		// Outputs in range [lower, upper)
		[[nodiscard]]
		constexpr float RandRange(u32 hash, float lower, float upper);

	}

}