#include "gui/noise_view_window.hpp"

#include "noise/noise.hpp"

#include <imgui.h>

NoiseViewWindow::NoiseViewWindow(
	NoiseEditorState& state
) : state_(state)
{
	Regenerate();
}

void NoiseViewWindow::Regenerate() {
	texture_.Generate(state_.project);
	state_.preview_dirty = false;
}

void NoiseViewWindow::Draw() {
	// Render the 2D noise output
	ImGui::Begin(
		"Output Viewport",
		nullptr,
		ImGuiWindowFlags_NoCollapse
	);

	if (state_.preview_dirty) {
		Regenerate();
	}

	texture_.Draw(ImVec2{512.0f, 512.0f});

	ImGui::End();
}