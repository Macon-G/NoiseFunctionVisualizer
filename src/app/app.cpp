#include "app.hpp"
#include "test_window.hpp"
#include "settings_window.hpp"
#include "noise_view_window.hpp"

#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include <stdexcept>

App::App() {
	try {
		InitializeGlfw();
		InitializeWindow();
		InitializeImGui();
	}
	catch (...) {
		Shutdown();
		throw;
	}

	window_manager_.AddWindow<TestWindow>(show_demo_window_);
	window_manager_.AddWindow<SettingsWindow>(project_);
	window_manager_.AddWindow<NoiseViewWindow>(project_);
}

App::~App() {
	Shutdown();
}

void App::Run() {
	while (!glfwWindowShouldClose(window_)) {
		glfwPollEvents();

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		DrawGui();

		ImGui::Render();

		RenderFrame();

		glfwSwapBuffers(window_);
	}
}

void App::InitializeGlfw() {
	if (!glfwInit()) {
		throw std::runtime_error("Failed to initialize GLFW");
	}

	glfw_initialized_ = true;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(
		GLFW_OPENGL_PROFILE,
		GLFW_OPENGL_CORE_PROFILE
	);

#ifdef __APPLE__
	glfwWindowHint(
		GLFW_OPENGL_FORWARD_COMPAT,
		GL_TRUE
	);
#endif
}

void App::InitializeWindow() {
	window_ = glfwCreateWindow(
		1280,
		720,
		"Noise Generator",
		nullptr,
		nullptr
	);

	if (!window_) {
		throw std::runtime_error("Failed to create GLFW window");
	}

	glfwMakeContextCurrent(window_);
	
	if (!gladLoadGL(glfwGetProcAddress)) {
		throw std::runtime_error("Failed to initialize GLAD");
	}
	
	glfwSwapInterval(1);
}

void App::InitializeImGui() {
	IMGUI_CHECKVERSION();
	
	ImGui::CreateContext();
	imgui_context_created_ = true;
	
	ImGuiIO& io = ImGui::GetIO();

	io.ConfigFlags |=
		ImGuiConfigFlags_NavEnableKeyboard;

	ImGui::StyleColorsDark();

	if (!ImGui_ImplGlfw_InitForOpenGL(window_, true)) {
		throw std::runtime_error("Failed to initialize GLFW for OpenGL backend");
	}

	imgui_glfw_initialized_ = true;
	
	if (!ImGui_ImplOpenGL3_Init("#version 130")) {
		throw std::runtime_error("Failed to initialize ImGui OpenGL backend");
	}

	imgui_opengl_initialized_ = true;
}

void App::Shutdown() noexcept {
	if (imgui_opengl_initialized_) {
		ImGui_ImplOpenGL3_Shutdown();
		imgui_opengl_initialized_ = false;
	}
	if (imgui_glfw_initialized_) {
		ImGui_ImplGlfw_Shutdown();
		imgui_glfw_initialized_ = false;
	}
	if (imgui_context_created_) {
		ImGui::DestroyContext();
		imgui_context_created_ = false;
	}
	if (window_) {
		glfwDestroyWindow(window_);
		window_ = nullptr;
	}
	if (glfw_initialized_) {
		glfwTerminate();
		glfw_initialized_ = false;
	}
}

void App::DrawGui() {
	window_manager_.Draw();

	if (show_demo_window_) {
		ImGui::ShowDemoWindow(&show_demo_window_);
	}
}

void App::RenderFrame() {
	int display_width;
	int display_height;

	glfwGetFramebufferSize(
		window_,
		&display_width,
		&display_height
	);

	glViewport(
		0,
		0,
		display_width,
		display_height
	);

	glClearColor(
		clear_color_[0] * clear_color_[3],
		clear_color_[1] * clear_color_[3],
		clear_color_[2] * clear_color_[3],
		clear_color_[3]
	);

	glClear(GL_COLOR_BUFFER_BIT);

	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
