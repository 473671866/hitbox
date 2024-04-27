#include "dominator.h"

bool dominator::window()
{
	view::compoment hb;
	hb.ins("settings", [&] {
		control::trigger("p1", &configurs::dp1);

		control::trigger("p2", &configurs::dp2);

		imgui::Text(u8"Í¸Ã÷¶È");
		imgui::SameLine();
		imgui::SetCursorPosX(imgui::GetWindowWidth() - 50);
		imgui::SetNextItemWidth(40);
		imgui::PushID(100);
		imgui::InputFloat(u8"", &configurs::alpha, 0.0f, 0.0f, "%.2f");
		imgui::PopID();

		imgui::Text(u8"´ÖÏ¸");
		imgui::SameLine();
		imgui::SetCursorPosX(imgui::GetWindowWidth() - 50);
		imgui::SetNextItemWidth(40);
		imgui::PushID(101);
		imgui::InputFloat(u8"", &configurs::thickness, 0.0f, 0.0f, "%.2f");
		imgui::PopID();
		});

	hb.ins("hitboxes", [&] {
		for (int i = 0; i < (sizeof(descriptions) / sizeof(description)); i++) {
			description* desc = &descriptions[i];
			control::label(desc->btn, desc->title, &desc->open, &desc->activity, &desc->color);
		}
		});

	view::decoration decor;
	decor.insert(ICON_FA_EXPAND, hb);
	decor.icon(configurs::icon_awesmoe);
	decor.logo(configurs::icon_brands, ICON_FA_GITHUB);
	decor.show("HOTBOX");
	return true;
}