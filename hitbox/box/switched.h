#pragma once
#include "../imgui/imgui.h"
#include "../structs/object.h"

struct switcher {
	const char* name;
	const char* title;
	ImColor color;
	action_types action;
	wrappers types;
	bool display;
	bool control;
};

extern switcher switches[14];