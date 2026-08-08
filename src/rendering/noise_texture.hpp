#pragma once

#include "project/noise_project.hpp"

#include <glad/gl.h>
#include <imgui.h>

#include <cstdint>
#include <vector>

class NoiseTexture {
public:
	NoiseTexture(int width, int height);
	~NoiseTexture();

	// Make NoiseTexture non-copiable and non-movable, to ensure double deletions are prevented.
	NoiseTexture(const NoiseTexture&) = delete;
	NoiseTexture& operator=(const NoiseTexture&) = delete;
	NoiseTexture(NoiseTexture&&) = delete;
	NoiseTexture& operator=(NoiseTexture&&) = delete;

	void Generate(
		const NoiseProject& project
	);

	void Draw(ImVec2 size) const;

private:
	GLuint texture_id_ = 0;
	int width_ = 0;
	int height_ = 0;
	std::vector<unsigned char> pixels_;
};