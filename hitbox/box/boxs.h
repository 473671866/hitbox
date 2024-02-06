#pragma once
#include "services.h"
#include "switched.h"

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
