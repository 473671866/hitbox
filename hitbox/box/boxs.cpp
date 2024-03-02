#include "boxs.h"

namespace hitboxes {
	bool boxs::foreground(rect& r, ImColor color)
	{
		FVector w1{};
		w1.X = r.x1;
		w1.Z = r.y1;
		FVector2D s1{};
		service->screen(w1, s1);

		FVector w3{};
		w3.X = r.x2;
		w3.Z = r.y2;
		FVector2D s3{};
		service->screen(w3, s3);

		ImVec2 rect_min(s1.X, s1.Y);
		ImVec2 rect_max(s3.X, s3.Y);
		ImGui::GetForegroundDrawList()->AddRect(rect_min, rect_max, ImGui::ColorConvertFloat4ToU32(color.Value));

		color.Value.w = alpha;
		ImGui::GetForegroundDrawList()->AddRectFilled(rect_min, rect_max, ImGui::ColorConvertFloat4ToU32(color.Value));

		return true;
	}

	bool attack::box(object* obj, action_collections actcs, switcher swch) {
		for (unsigned int i = 0; i < actcs.capacity; i++) {
			attack_boxs box = actcs.attack[i];
			if (box.frame != obj->now)
				continue;

			attack_collections atccs = obj->atcs->atccs[box.number];
			if (swch.types.attack != atccs.types)
				continue;

			rect r(obj, box, obj->left());
			foreground(r, swch.color);
		}
		return true;
	}

	bool body::box(object* obj, action_collections actcs, switcher swch) {
		for (unsigned int i = 0; i < actcs.capacity; i++) {
			body_boxs box = actcs.body[i];
			if (box.frame != obj->now)
				continue;

			rect r(obj, box, obj->left());
			foreground(r, swch.color);
		}
		return false;
	}

	bool affected::box(object* obj, action_collections actcs, switcher swch) {
		for (unsigned int i = 0; i < actcs.capacity; i++) {
			affected_boxs box = actcs.affected[i];
			if (box.frame != obj->now)
				continue;

			if (swch.types.affected != box.types)
				continue;

			rect r(obj, box, obj->left());
			foreground(r, swch.color);
		}
		return false;
	}
};