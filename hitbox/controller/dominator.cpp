#include "dominator.h"

dominator::dominator() {
	ImGuiIO& io = imgui::GetIO();
	float font_size = 16.0f;
	float icon_size = font_size * 2.0f / 3.0f;
	font_mshy = io.Fonts->AddFontFromMemoryTTF(msyh, sizeof(msyh), 17.0f, nullptr, io.Fonts->GetGlyphRangesChineseFull());
	static const ImWchar icons_ranges[] = { ICON_MIN_FA, ICON_MAX_16_FA,0 };
	ImFontConfig icons_config;
	icons_config.MergeMode = true;
	icons_config.PixelSnapH = true;
	icons_config.GlyphMinAdvanceX = icon_size;
	icon_awesmoe = io.Fonts->AddFontFromMemoryTTF(FontAewsome6, sizeof(FontAewsome6), icon_size, &icons_config, icons_ranges);
	icon_brands = io.Fonts->AddFontFromMemoryTTF(FontAwesome6Brands, sizeof(FontAwesome6Brands), 30.0f, &icons_config, icons_ranges);
	sc = view::scale::instance();
}

bool dominator::principal()
{
	view::compoment hb;
	hb.ins("settings", [&] {
		control::trigger("p1", &dp1);

		control::trigger("p2", &dp2);

		imgui::Text(u8"透明度");
		imgui::SameLine();
		imgui::SetCursorPosX(imgui::GetWindowWidth() - 50);
		imgui::SetNextItemWidth(40);
		imgui::PushID(100);
		imgui::InputFloat(u8"", &alpha, 0.0f, 0.0f, "%.2f");
		imgui::PopID();

		imgui::Text(u8"粗细");
		imgui::SameLine();
		imgui::SetCursorPosX(imgui::GetWindowWidth() - 50);
		imgui::SetNextItemWidth(40);
		imgui::PushID(101);
		imgui::InputFloat(u8"", &thickness, 0.0f, 0.0f, "%.2f");
		imgui::PopID();
		});

	hb.ins("hitboxes", [&] {
		for (int i = 0; i < (sizeof(descriptions) / sizeof(description)); i++) {
			description* desc = &descriptions[i];
			control::label(desc->btn, desc->title, &desc->open, &desc->activity, &desc->color);
		}
		});

	view::compoment rule;
	rule.ins("scale", [&] {
		control::trigger("FPS", &fps);
		control::trigger(u8"帧数表", &frame_rule);

		imgui::PushID(200);
		imgui::InputInt("", &p1_index);
		imgui::PopID();
		imgui::SameLine();
		control::button("p1", [&] { {
				sc->p1(1, YELLOW);
			}});
		});

	view::decoration decor;
	decor.insert(ICON_FA_EXPAND, hb);
	decor.insert(ICON_FA_BARS_PROGRESS, rule);
	decor.icon(icon_awesmoe);
	decor.logo(icon_brands, ICON_FA_GITHUB);
	decor.show("Example");
	return true;
}

bool dominator::draw()
{
	auto mapping = mapper::instance();

	auto objs = *mapping->objs;
	if (objs == nullptr)
		return false;

	auto p1 = objs->p1;
	if (p1 == nullptr)
		return false;

	auto p2 = objs->p2;
	if (p2 == nullptr)
		return false;

	for (description& desc : descriptions) {
		if (!desc.activity)
			continue;

		if (dp1) {
			actions_entry entry = p1->acts->entry[p1->number];
			for (int i = 0; i < entry.capacity && entry.actcs != nullptr && IsBadReadPtr(&entry.actcs[i], sizeof(actions_entry)) == 0; i++) {
				action_collections actcs = entry.actcs[i];
				if (actcs.types != desc.action)
					continue;

				int index = (int)actcs.types - 3;
				if (index < 0 or index > 3)
					continue;

				hitboxes::box* b = contexts[index].instance;
				b->alpha = alpha;
				b->thickness = thickness;
				b->resolve(p1, actcs, desc);
			}
		}

		if (dp2) {
			actions_entry entry = p2->acts->entry[p2->number];
			for (int i = 0; i < entry.capacity && entry.actcs != nullptr && IsBadReadPtr(&entry.actcs[i], sizeof(actions_entry)) == 0; i++) {
				action_collections actcs = entry.actcs[i];
				if (actcs.types != desc.action)
					continue;

				int index = (int)actcs.types - 3;
				if (index < 0 or index > 3)
					continue;

				hitboxes::box* b = contexts[index].instance;
				b->alpha = alpha;
				b->thickness = thickness;
				b->resolve(p2, actcs, desc);
			}
		}

		if (desc.types != attack_types::projectile)
			continue;

		auto list = objs->props_list->list;
		for (; list != nullptr; list = list->next) {
			auto props = list->props;
			auto props_entry = props->acts->entry[props->number];
			for (int i = 0; i < props_entry.capacity; i++) {
				action_collections actcs = props_entry.actcs[i];
				if (actcs.types != desc.action)
					continue;

				int index = (int)actcs.types - 3;
				if (index < 0 or index > 3)
					continue;

				if (dp1) {
					hitboxes::box* b = contexts[index].instance;
					b->alpha = alpha;
					b->thickness = thickness;
					b->resolve((object*)props, actcs, desc);
				}

				if (dp2) {
					hitboxes::box* b = contexts[index].instance;
					b->alpha = alpha;
					b->thickness = thickness;
					b->resolve((object*)props, actcs, desc);
				}
			}
		}
	}
	return true;
}

bool dominator::ruler() {
	if (!frame_rule) {
		return false;
	}

	auto mapping = mapper::instance();

	int frame_count = 0;
	auto objs = *mapping->objs;
	if (objs == nullptr)
		return false;

	auto p1 = objs->p1;
	if (p1 == nullptr)
		return false;

	actions_entry entry = p1->acts->entry[p1->number];
	for (int i = 0; i < entry.capacity && entry.actcs != nullptr && IsBadReadPtr(&entry.actcs[i], sizeof(actions_entry)) == 0; i++) {
		action_collections actcs = entry.actcs[i];
		if (actcs.types != action_types::attack)
			continue;

		for (unsigned int j = 0; j < actcs.capacity; j++) {
			auto box = actcs.attack[j];
			if (p1->atcs->atccs[box.number].types != attack_types::normal)
				continue;

			frame_count = actcs.attack[0].frame;
		}
	}

	sc->p1(frame_count, RED);
	sc->win(hwnd);
	sc->show();

	return frame_rule;
}

bool dominator::frame()
{
	if (fps) {
		ImGuiIO& io = imgui::GetIO();
		char buffer[256] = {};
		sprintf_s(buffer, "FPS: %.0f", io.Framerate);
		imgui::GetForegroundDrawList()->AddText({ 10,10 }, IM_COL32_WHITE, buffer);
	}
	return fps;
}