#pragma once

#include "gui/gui_window.hpp"
#include "noise/noise_project.hpp"

#include <imgui.h>

class SettingsWindow : public GuiWindow {
public:
	SettingsWindow(NoiseProject& project);
	void Draw() override;
private:
	char seed_string_[64] = "My Awesome Seed!";
	NoiseProject& project_;
	ImVec2 window_size_;
	ImVec2 window_pos_;
};