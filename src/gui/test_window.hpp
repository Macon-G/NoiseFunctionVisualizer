#pragma once

#include "gui/gui_window.hpp"

class TestWindow final : public GuiWindow {
public:
	TestWindow(bool &show_demo_window);
	void Draw() override;
private:
	bool& show_demo_window_;
};
