#include "boxs.h"

switched switches[] = {
	{u8"普通攻击框",		u8"普通攻击框颜色",		{ 200, 100, 100 },	action_types::attack,	attack_types::normal,		false,	false},
	{u8"投技框",			u8"投技框颜色",			{ 127, 191, 191 },	action_types::attack,	attack_types::grasp,		false,	false},
	{u8"飞行道具攻击框",	u8"飞行道具攻击框颜色",	{ 127, 255, 127 },	action_types::attack,	attack_types::projectile,	false,	false},
	{u8"引发防御框",		u8"引发防御框颜色",		{ 127, 255, 127 },	action_types::attack,	attack_types::guard,		false,	false},
	{u8"身位框",			u8"身位框颜色",			{ 255, 165, 0  },	action_types::body,		body_types::none,			false,	false},
	{u8"受击框",			u8"受击框颜色",			{ 255, 255, 0 },	action_types::affected, affected_types::normal,		false,	false},
	{u8"被投框",			u8"被投框颜色",			{ 127, 255, 255 },	action_types::affected, affected_types::capture,	false,	false},
	{u8"防御框",			u8"防御框颜色",			{ 0, 255, 0 },		action_types::affected, affected_types::guard,		false,	false},
	{u8"追加框",			u8"追加框颜色",			{ 0, 255, 0 },		action_types::affected, affected_types::ground,		false,	false},
	{u8"抵消飞行道具框",	u8"抵消飞行道具框颜色", { 128, 128, 255 },	action_types::affected, affected_types::negative,	false,	false},
	{u8"反弹飞行道具框",	u8"反弹飞行道具框颜色", { 255, 127, 255 },	action_types::affected, affected_types::reflects,	false,	false},
	{u8"霸体框",			u8"霸体框颜色",			{ 64, 127, 127 },	action_types::affected, affected_types::invulnerability, false, false},
	{u8"当身框",			u8"当身框颜色",			{ 0, 0, 255 },		action_types::affected, affected_types::parries,	false, false},
	{u8"对投当身框",		u8"对投当身框颜色",		{ 139, 0, 255 },	action_types::affected, affected_types::parriesex,	false, false},
};

namespace hitboxs {
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

	bool attack::box(object* obj, action_collections actcs, switched swch) {
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

	bool body::box(object* obj, action_collections actcs, switched swch) {
		for (unsigned int i = 0; i < actcs.capacity; i++) {
			body_boxs box = actcs.body[i];
			if (box.frame != obj->now)
				continue;

			rect r(obj, box, obj->left());
			foreground(r, swch.color);
		}
		return false;
	}

	bool affected::box(object* obj, action_collections actcs, switched swch) {
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