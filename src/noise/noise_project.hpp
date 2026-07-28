#pragma once
#include "cstdint"

struct NoiseProject {
	uint32_t seed = 0;
	float scale = 0.02f;
	uint32_t octaves = 6;
	float gain = 0.5f;
	float lacunarity = 2.0f;
};