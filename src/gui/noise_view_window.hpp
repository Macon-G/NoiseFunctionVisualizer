#pragma once

#include "app/noise_editor_state.hpp"
#include "gui/gui_window.hpp"
#include "noise/noise.hpp"
#include "project/noise_project.hpp"
#include "rendering/noise_texture.hpp"

#include <vector>

class NoiseViewWindow : public GuiWindow {
public:
	explicit NoiseViewWindow(
		NoiseEditorState& state
	);
	
	void Draw() override;

private:
	void Regenerate();

	NoiseEditorState& state_;
	
	NoiseTexture texture_{512, 512}; 
};