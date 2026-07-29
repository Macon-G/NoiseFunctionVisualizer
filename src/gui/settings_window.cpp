#include "gui/settings_window.hpp"

#include "noise/noise_project.hpp"
#include "utility/hash.hpp"

#include <string>

SettingsWindow::SettingsWindow(NoiseProject& project)
	: project_(project), window_pos_(0, 0)
{
	// Set initial window size to half of the main window size on startup
	ImVec2 s = ImGui::GetMainViewport()->Size;
	window_size_ = {s.x * 0.5f, s.y * 0.5f};

	project_.seed = Noise::Hash::HashString(seed_string_);
}

void SettingsWindow::Draw() {
	ImGui::Begin(
		"Noise Parameters",
		nullptr,
		ImGuiWindowFlags_NoCollapse
			| ImGuiWindowFlags_AlwaysAutoResize
	);

	if (ImGui::InputText(
		"Seed",
		seed_string_,
		IM_ARRAYSIZE(seed_string_)
	)) {
		project_.seed = Noise::Hash::HashString(seed_string_);
	}
	
	std::string seed_numeric_view_text = "Seed (integer): ";
	seed_numeric_view_text += std::to_string(project_.seed);

	ImGui::Text(seed_numeric_view_text.c_str());

	const uint32_t octaves_min = 1;
	const uint32_t octaves_max = 6;
	ImGui::SliderScalar(
		"Octaves",
		ImGuiDataType_U32,
		&project_.octaves,
		&octaves_min,
		&octaves_max,
		"%u"
	);

	ImGui::SliderFloat(
		"Scale",
		&project_.scale,
		0.001f,
		0.100f,
		"%.4f"
	);

	ImGui::SliderFloat(
		"Gain",
		&project_.gain,
		0.01f,
		2.00f,
		"%.2f"
	);

	ImGui::SliderFloat(
		"Lacunarity",
		&project_.lacunarity,
		0.01f,
		2.00f,
		"%.2f"
	);

	ImGui::End();
}