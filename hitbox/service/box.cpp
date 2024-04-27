#include "box.h"

namespace hitboxes {
	bool box::foreground(range& r, ImColor color)
	{
		runable* invoke = runable::instance();

		FVector w1{};
		w1.X = r.left;
		w1.Z = r.top;
		FVector2D s1{};
		invoke->screen(w1, s1);

		FVector w3{};
		w3.X = r.right;
		w3.Z = r.bottom;
		FVector2D s3{};
		invoke->screen(w3, s3);

		ImVec2 rect_min(s1.X, s1.Y);
		ImVec2 rect_max(s3.X, s3.Y);

		control::draw_box(rect_min, rect_max, alpha, thickness, color);
		return true;
	}

	bool  attack::resolve(object* obj, action_collections actcs, description desc) {
		for (unsigned int i = 0; i < actcs.capacity; i++) {
			attack_boxs box = actcs.attack[i];
			if (box.frame != obj->now)
				continue;

			attack_collections atccs = obj->atcs->atccs[box.number];
			if (desc.types.attack != atccs.types)
				continue;

			range r(obj, box, obj->left());
			foreground(r, desc.color);
		}
		return true;
	}

	bool body::resolve(object* obj, action_collections actcs, description desc) {
		for (unsigned int i = 0; i < actcs.capacity; i++) {
			body_boxs box = actcs.body[i];
			if (box.frame != obj->now)
				continue;

			range r(obj, box, obj->left());
			foreground(r, desc.color);
		}
		return true;
	}

	bool affected::resolve(object* obj, action_collections actcs, description desc) {
		for (unsigned int i = 0; i < actcs.capacity; i++) {
			affected_boxs box = actcs.affected[i];
			if (box.frame != obj->now)
				continue;

			if (desc.types.affected != box.types)
				continue;

			range r(obj, box, obj->left());
			foreground(r, desc.color);
		}
		return true;
	}
};