#pragma once

class GuiWindow {
public:
	virtual ~GuiWindow() = default;
	virtual void Draw() = 0;
};