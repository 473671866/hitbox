#pragma once
#include "services.h"
#include "../imgui/imgui.h"
#include "../structs/object.h"

struct switched {
	const char* name;
	const char* title;
	ImColor color;
	action_types action;
	wrappers types;
	bool display;
	bool control;
};

extern switched switches[14];

namespace hitboxs {
	class boxs {
	public:
		services* service;
		float alpha;

	protected:
		bool foreground(rect& r, ImColor color);

	public:
		virtual bool box(object* obj, action_collections actcs, switched swch) = 0;
	};

	class attack :public boxs {
	public:
		bool box(object* obj, action_collections actcs, switched swch) override;
	};

	class body : public boxs {
	public:
		bool box(object* obj, action_collections actcs, switched swch)override;
	};

	class affected : public boxs {
	public:
		bool box(object* obj, action_collections actcs, switched swch)override;
	};
};
