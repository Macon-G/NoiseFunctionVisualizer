#pragma once

#include "gui_window.hpp"

#include <memory>
#include <vector>

class WindowManager {
public:
	WindowManager() = default;

	template <typename T, typename ... Args>
	T& AddWindow(Args&&... args) {
		auto window = std::make_unique<T>(
			std::forward<Args>(args)...
		);

		T& reference = *window;

		windows_.push_back(std::move(window));

		return reference;
	}

	void Draw() {
		for (auto& window : windows_) {
			window->Draw();
		}
	}
private:
	std::vector<std::unique_ptr<GuiWindow>> windows_;
};