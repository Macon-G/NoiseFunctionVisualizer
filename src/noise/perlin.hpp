#pragma once

#include "generator.hpp"

#include <array>

namespace Noise {
	class Perlin final : public Generator {
	public:
		explicit Perlin(uint32_t seed);

		[[nodiscard]] float Sample(float x) const override;
		[[nodiscard]] float Sample(float x, float y) const override;
	
	private:
		uint32_t seed_;
	};
	
}