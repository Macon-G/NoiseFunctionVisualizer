#pragma once

#include "noise/functions.hpp"

#include <array>
#include <cstddef>
#include <string_view>

namespace Noise::Registry {
	enum class FunctionType {
		Perlin,
		OpenSimplex,
		Value,
		White,
		Worley
	};

	struct FunctionInfo {
		FunctionType type;
		std::string_view name;
		Function function;
	};

	inline constexpr auto FUNCTION_REGISTRY = std::array{
		FunctionInfo{
			.type = FunctionType::Perlin,
			.name = "Perlin",
			.function = Functions::Perlin
		},
		FunctionInfo{
			FunctionType::OpenSimplex,
			"OpenSimplex",
			Functions::OpenSimplex
		},
		FunctionInfo{
			FunctionType::Value,
			"Value",
			Functions::Value
		},
		FunctionInfo{
			FunctionType::White,
			"White",
			Functions::White
		},
		FunctionInfo{
			FunctionType::Worley,
			"Worley",
			Functions::Worley
		},
	};

	[[nodiscard]]
	constexpr const FunctionInfo& GetFunctionInfo(
		FunctionType type
	) {
		for (const FunctionInfo& info : FUNCTION_REGISTRY) {
			if (info.type == type) {
				return info;
			}
		}

		// Every valid FunctionType should be registered
		return FUNCTION_REGISTRY.front();
	}

	[[nodiscard]]
	constexpr std::size_t GetFunctionIndex(
		FunctionType type
	) {
		for (
			std::size_t i = 0;
			i < FUNCTION_REGISTRY.size();
			++i
		) {
			if (FUNCTION_REGISTRY[i].type == type) {
				return i;
			}
		}

		return 0;
	}

	[[nodiscard]]
	constexpr Function GetFunction(FunctionType type) {
		return GetFunctionInfo(type).function;
	}
}