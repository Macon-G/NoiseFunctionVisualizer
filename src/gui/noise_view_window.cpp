#include "noise_view_window.hpp"

#include <imgui.h>

NoiseViewWindow::NoiseViewWindow(NoiseProject& project)
	: noise_project_(project)
{
	Regenerate();
}

void NoiseViewWindow::Regenerate() {
	Noise::Perlin perlin{ noise_project_.seed };

	texture_.Generate(
		perlin,
		noise_project_.scale
	);

	generated_seed_ = noise_project_.seed;
	generated_scale_ = noise_project_.scale;
}

void NoiseViewWindow::Draw() {
	// Render the 2D noise output
	ImGui::Begin(
		"Output Viewport",
		nullptr,
		ImGuiWindowFlags_NoCollapse
	);

	if (generated_seed_ != noise_project_.seed ||
		generated_scale_ != noise_project_.scale
	) {
		Regenerate();
	}

	if (ImGui::Button("Regenerate")) {
		Regenerate();
	}

	texture_.Draw(ImVec2{512.0f, 512.0f});

	ImGui::End();
}