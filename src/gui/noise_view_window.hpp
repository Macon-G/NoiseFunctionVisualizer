#pragma once

#include "gui_window.hpp"
#include "noise_project.hpp"
#include "noise_texture.hpp"
#include "perlin.hpp"

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
	float generated_scale_ = 0;
};