#pragma once

#include <cstdint>
#include <string_view>

namespace Noise::Hash {

	// --=== Basic hashing functions ===--

	[[nodiscard]] uint32_t Hash2D(
		int32_t x,
		int32_t y,
		uint32_t seed
	);

	[[nodiscard]] uint32_t HashString(
		std::string_view str
	);


	// --=== Deterministic coordinate-based RNG functions ===--
	float Rand01(
		int32_t x,
		int32_t y,
		uint32_t seed
	); // Returns [0.0f, 1.0f)

	float RandMax(
		int32_t x,
		int32_t y,
		uint32_t seed,
		float max
	); // Returns [0.0f, max)

	float RandRange(
		int32_t x,
		int32_t y,
		uint32_t seed,
		float min,
		float max
	); // Returns [min, max)

} // namespace Noise::Hash