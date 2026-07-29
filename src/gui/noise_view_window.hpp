#pragma once

#include "gui/gui_window.hpp"
#include "noise/noise_project.hpp"
#include "rendering/noise_texture.hpp"
#include "noise/generators/perlin.hpp"

#include <vector>

class NoiseViewWindow : public GuiWindow {
public:
	explicit NoiseViewWindow(NoiseProject& project);
	void Draw() override;
private:
	void Regenerate();
	NoiseProject& noise_project_;
	NoiseTexture texture_{512, 512};
	uint32_t generated_seed_ = 0;
	float generated_scale_ = 0.0f;
	uint32_t generated_octaves_ = 0;
	float generated_lacunarity_ = 0.0f;
	float generated_gain_ = 0.0f;
};