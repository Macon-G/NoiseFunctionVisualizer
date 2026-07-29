#pragma once

#include "noise/generator.hpp"

namespace Noise {
	class FBM final : public Generator {
	public:
		FBM(
			const Generator& source,
			uint32_t octaves,
			float lacunarity,
			float gain
		);

		[[nodiscard]] float Sample(float x, float y) const override;
	private:
		const Generator& source_;
		
		uint32_t octaves_;
		float lacunarity_;
		float gain_;
	};
}