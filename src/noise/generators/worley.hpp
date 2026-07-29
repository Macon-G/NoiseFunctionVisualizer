#pragma once

#include "noise/generator.hpp"

namespace Noise {
	class Worley : public Generator {
	public:
		explicit Worley(uint32_t seed);

		[[nodiscard]] float Sample(float x, float y) const override;
	private:
		uint32_t seed_;
	};
}