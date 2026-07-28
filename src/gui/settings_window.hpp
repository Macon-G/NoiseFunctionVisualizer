#pragma once

#include "gui_window.hpp"
#include "noise_project.hpp"

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