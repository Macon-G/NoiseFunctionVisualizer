#pragma once

#include "app/noise_editor_state.hpp"
#include "gui/gui_window.hpp"
#include "project/noise_project.hpp"

class SettingsWindow : public GuiWindow {
public:
	explicit SettingsWindow(
		NoiseEditorState& state
	);
	
	void Draw() override;

private:
	bool DrawFunctionTypeCombo();

	bool DrawWorleyDistanceCombo();

	bool DrawWorleyOutputCombo();

private:
	char seed_string_[64] = "My Awesome Seed!";

	NoiseEditorState& state_;
};