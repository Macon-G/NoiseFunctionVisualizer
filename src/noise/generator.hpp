#pragma once

#include <cstdint>

namespace Noise {

	class Generator {
	public:
		virtual ~Generator() = default;

		[[nodiscard]] virtual float Sample(float x) const = 0;
		[[nodiscard]] virtual float Sample(float x, float y) const = 0;
	};

}