#pragma once
#include "../imgui/imgui.h"
#include "../entity/object.h"

struct description {
	int btn;
	const char* title;
	bool activity;
	bool open;
	ImColor color;
	action_types action;
	warpper types;
};

extern description descriptions[14];