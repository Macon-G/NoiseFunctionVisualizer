#pragma once

#include "generator.hpp"

#include <cstdint>

namespace Noise {
	class Value : public Generator {
	public:
		explicit Value(uint32_t seed);

		[[nodiscard]] float Sample(float x, float y) const override;
	private:
		uint32_t seed_;
	};
}