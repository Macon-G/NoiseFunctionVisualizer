#pragma once

#include <imgui.h>

class GuiWindow {
public:
	virtual ~GuiWindow() = default;
	virtual void Draw() = 0;
};