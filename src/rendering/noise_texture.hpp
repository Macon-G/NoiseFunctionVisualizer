#pragma once

#include "noise/generator.hpp"

#include <imgui.h>
#include <glad/gl.h>
#include <vector>
#include <cstdint>

class NoiseTexture {
public:
	NoiseTexture(int width, int height);
	~NoiseTexture();

	void Generate(
		const Noise::Generator& generator,
		float scale
	);
	void Draw(ImVec2 size) const;
private:
	GLuint texture_id_ = 0;
	int width_ = 0;
	int height_ = 0;
	std::vector<unsigned char> pixels_;
};