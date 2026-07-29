#pragma once

#include "noise/generator.hpp"

#include <cstdint>

namespace Noise {
	
	class White : public Generator {
	public:
		explicit White(uint32_t seed);

		[[nodiscard]] float Sample(float x, float y) const override;
	private:
		uint32_t seed_;
	};

}