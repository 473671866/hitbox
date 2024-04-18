#ifndef HITBOXES_H
#define HITBOXES_H

#include "../view/control.h"
#include "../service/runable.h"
#include "../context/description.h"

namespace hitboxes {
	class box {
	public:
		float thickness;
		float alpha;

	public:
		bool foreground(range& r, ImColor color);

		virtual bool resolve(object* obj, action_collections actcs, description desc) = 0;
	};

	class attack :public box {
	public:
		bool resolve(object* obj, action_collections actcs, description desc) override;
	};

	class body : public box {
	public:
		bool resolve(object* obj, action_collections actcs, description desc) override;
	};

	class affected : public box {
	public:
		bool resolve(object* obj, action_collections actcs, description desc) override;
	};
};

#endif
