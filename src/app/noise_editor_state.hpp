#pragma once

#include "project/noise_project.hpp"

struct NoiseEditorState{
	NoiseProject project;
	bool preview_dirty = true;
};