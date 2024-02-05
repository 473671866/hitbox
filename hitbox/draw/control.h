#pragma once
#include "../imgui/imgui.h"
class control {
public:
	static bool label(const char* checkbox, bool* box, const char* selector, bool* open, ImColor* color);
};
