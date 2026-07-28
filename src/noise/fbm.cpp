#include "fbm.hpp"

Noise::FBM::FBM(
	const Generator& source,
	uint32_t octaves,
	float lacunarity,
	float gain
) : source_(source),
	octaves_(octaves),
	lacunarity_(lacunarity),
	gain_(gain)
{}


[[nodiscard]] float Noise::FBM::Sample(float x, float y) {
	float sum = source_.Sample(x, y);
	float max_amplitude = 1;

	for (size_t i = 1; i <= octaves_; ++i) {
		// Frequency doubles with each octave
		float sx = x * i * 2;
		float sy = y * i * 2;

		float value = source_.Sample(sx, sy);

		// Amplitude decreases with each octave
		sum += value / i * 2;

		// Accumulate maximum amplitude
		max_amplitude += 1 / (i * 2);
	}
	return sum / max_amplitude;
}