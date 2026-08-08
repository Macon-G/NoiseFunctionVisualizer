#include "gui/settings_window.hpp"

#include "project/noise_project.hpp"
#include "noise/function_registry.hpp"
#include "noise/noise.hpp"
#include "noise/worley_registry.hpp"

#include <imgui.h>
#include <format>

SettingsWindow::SettingsWindow(
	NoiseEditorState& state
) : state_(state)
{
	state_.project.seed = Noise::Utilities::HashString(seed_string_);
}

void SettingsWindow::Draw() {
	bool changed = false;	// Tracks input state changes
	
	ImGui::Begin(
		"Noise Parameters",
		nullptr,
		ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_AlwaysAutoResize
	);

	changed |= DrawFunctionTypeCombo();

	if (state_.project.function_type == Noise::Registry::FunctionType::Worley) {
		changed |= DrawWorleyDistanceCombo();
		changed |= DrawWorleyOutputCombo();
	}

	changed |= ImGui::InputText(
		"Seed",
		seed_string_,
		IM_ARRAYSIZE(seed_string_)
	);

	ImGui::Text(
		std::format(
			"Numeric Seed: {}",
			state_.project.seed
		).c_str()
	);

	ImGui::Text(
		"Setting octaves to a value greater than\n"
		"one enables Fractal Brownian Motion."
	);

	const uint32_t octaves_min = 1;
	const uint32_t octaves_max = 6;
	changed |= ImGui::SliderScalar(
		"Octaves",
		ImGuiDataType_U32,
		&state_.project.fbm_params.octaves,
		&octaves_min,
		&octaves_max,
		"%u"
	);

	ImGui::Text(
		state_.project.fbm_params.octaves > 1
			? "FBM is enabled."
			: "FBM is disabled."
	);

	changed |= ImGui::SliderFloat(
		"Scale",
		&state_.project.scale,
		0.001f,
		0.100f,
		"%.3f"
	);

	changed |= ImGui::SliderFloat(
		"Gain",
		&state_.project.fbm_params.gain,
		0.00f,
		1.00f,
		"%.2f"
	);

	changed |= ImGui::SliderFloat(
		"Lacunarity",
		&state_.project.fbm_params.lacunarity,
		1.00f,
		4.00f,
		"%.2f"
	);

	ImGui::End();

	if (changed) {
		state_.project.seed = Noise::Utilities::HashString(seed_string_);
		state_.preview_dirty = true;
	}
}

bool SettingsWindow::DrawFunctionTypeCombo() {
	bool combo_changed = false;

	const Noise::Registry::FunctionInfo& current = Noise::Registry::GetFunctionInfo(
		state_.project.function_type
	);

	if (ImGui::BeginCombo(
		"Noise Function",
		current.name.data()
	)) {
		for (const Noise::Registry::FunctionInfo& option : Noise::Registry::FUNCTION_REGISTRY) {
			const bool is_selected = (option.type == state_.project.function_type);

			if (ImGui::Selectable(option.name.data(), is_selected)) {
				state_.project.function_type = option.type;
				combo_changed = true;
			}

			if (is_selected) {
				ImGui::SetItemDefaultFocus();
			}
		}

		ImGui::EndCombo();
	}

	return combo_changed;
}

bool SettingsWindow::DrawWorleyDistanceCombo() {
	bool combo_changed = false;

	const Noise::Functions::WorleyDistanceMetric& current = state_.project.worley_distance;

	if (ImGui::BeginCombo(
		"Distance Metric Options",
		Noise::Registry::GetWorleyDistanceOptionName(current)
	)) {
		for (const auto& option : Noise::Registry::WORLEY_DISTANCE_OPTIONS) {
			const bool is_selected = (state_.project.worley_distance == option.value);

			if (ImGui::Selectable(option.name.data(), is_selected)) {
				state_.project.worley_distance = option.value;
				combo_changed = true;
			}

			if (is_selected) {
				ImGui::SetItemDefaultFocus();
			}
		}

		ImGui::EndCombo();
	}

	return combo_changed;
}

bool SettingsWindow::DrawWorleyOutputCombo() {
	bool combo_changed = false;

	const Noise::Functions::WorleyOutputMode& current = state_.project.worley_output;

	if (ImGui::BeginCombo(
		"Output Options",
		Noise::Registry::GetWorleyOutputOptionName(current)
	)) {
		for (const auto& option : Noise::Registry::WORLEY_OUTPUT_OPTIONS) {
			const bool is_selected = (state_.project.worley_output == option.value);

			if (ImGui::Selectable(option.name.data(), is_selected)) {
				state_.project.worley_output = option.value;
				combo_changed = true;
			}

			if (is_selected) {
				ImGui::SetItemDefaultFocus();
			}
		}

		ImGui::EndCombo();
	}

	return combo_changed;
}