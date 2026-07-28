#include "noise_view_window.hpp"
#include "fbm.hpp"

#include <imgui.h>

NoiseViewWindow::NoiseViewWindow(NoiseProject& project)
	: noise_project_(project)
{
	Regenerate();
}

void NoiseViewWindow::Regenerate() {
	Noise::Perlin perlin{ noise_project_.seed };

	Noise::FBM fbm {
		perlin,
		static_cast<uint32_t>(noise_project_.octaves),
		noise_project_.lacunarity,
		noise_project_.gain
	};

	texture_.Generate(
		fbm,
		noise_project_.scale
	);

	generated_seed_ = noise_project_.seed;
	generated_scale_ = noise_project_.scale;
	generated_octaves_ = noise_project_.octaves;
	generated_lacunarity_ = noise_project_.lacunarity;
	generated_gain_ = noise_project_.gain;
}

void NoiseViewWindow::Draw() {
	// Render the 2D noise output
	ImGui::Begin(
		"Output Viewport",
		nullptr,
		ImGuiWindowFlags_NoCollapse
	);

	if (generated_seed_ != noise_project_.seed
		|| generated_scale_ != noise_project_.scale
		|| generated_octaves_ != noise_project_.octaves
		|| generated_gain_ != noise_project_.gain
		|| generated_lacunarity_ != noise_project_.lacunarity
	) {
		Regenerate();
	}

	if (ImGui::Button("Regenerate")) {
		Regenerate();
	}

	texture_.Draw(ImVec2{512.0f, 512.0f});

	ImGui::End();
}