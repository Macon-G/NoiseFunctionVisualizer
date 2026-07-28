#include "test_window.hpp"

TestWindow::TestWindow(bool &show_demo_window)
	: show_demo_window_(show_demo_window) {}
	
void TestWindow::Draw() {
	ImGui::Begin("Test Window", nullptr, ImGuiWindowFlags_NoCollapse);
	ImGui::Text("Big man Blastoise");
	ImGui::Checkbox("Show demo window", &show_demo_window_);
	ImGui::End();
}