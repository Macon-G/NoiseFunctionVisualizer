#pragma once
#include "noise_project.hpp"
#include "window_manager.hpp"
#include <glad/gl.h>
#include <GLFW/glfw3.h>

class App {
public:
	App();
	~App();

	void Run();

private:
	void InitializeGlfw();
	void InitializeWindow();
	void InitializeImGui();
	void Shutdown() noexcept;

	void DrawGui();
	void RenderFrame();

private:
	NoiseProject project_;
	WindowManager window_manager_;

	// bool show_demo_window_ = true;

	float clear_color_[4] = { 0.15f, 0.15f, 0.18f, 1.0f };

	GLFWwindow* window_ = nullptr;
	bool glfw_initialized_ = false;
	bool imgui_context_created_ = false;
	bool imgui_glfw_initialized_ = false;
	bool imgui_opengl_initialized_ = false;
};