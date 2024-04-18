#include "decoration.h"

namespace view {
	bool compoment::ins(const char* tag, std::function<void()> element) {
		elements.push_back(std::make_pair(tag, element));
		return true;
	}

	bool compoment::del(const char* tag) {
		for (auto it = elements.begin(); it != elements.end(); it++) {
			if (it->first.compare(tag) == 0) {
				elements.erase(it);
				return true;
			}
		}
		return false;
	}

	bool decoration::insert(const char* icon, compoment comp) {
		components.push_back(std::make_pair(icon, comp));
		return true;
	}

	bool decoration::remove(const char* name) {
		for (auto it = components.begin(); it != components.end(); it++) {
			if (it->first.compare(name) == 0) {
				components.erase(it);
				return true;
			}
		}
		return false;
	}

	bool decoration::icon(ImFont* font) {
		icons = font;
		return true;
	}

	bool decoration::logo(ImFont* font, const char* icon) {
		logos = font;
		logo_icon = icon;
		return true;
	}

	void decoration::show(const char* name, ImVec2 size) {
		imgui::Begin(name, nullptr, ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_HorizontalScrollbar | ImGuiWindowFlags_NoBringToFrontOnFocus);

		//´°¿Ú´óÐ¡
		imgui::SetWindowSize(size);

		auto draw = imgui::GetWindowDrawList();
		auto pos = imgui::GetWindowPos();
		auto wndsize = imgui::GetWindowSize();

		//±³¾°
		draw->AddRectFilled(pos, { pos.x + wndsize.x, pos.y + wndsize.y }, IM_COL32(36, 40, 49, 255), 2);

		//²à±ßÀ¸
		draw->AddRectFilled(pos, { pos.x + barsize, pos.y + wndsize.y }, IM_COL32(56, 62, 74, 255));

		//²Ëµ¥À¸
		draw->AddRectFilled({ pos.x + barsize, pos.y }, { pos.x + wndsize.x, pos.y + barsize * 0.5f }, IM_COL32(56, 62, 74, 255));

		//logo
		imgui::BeginChild("##LOGO", ImVec2(barsize, 60));
		imgui::PushFont(logos);
		imgui::SetCursorPos({ 10, 20 });
		imgui::Text(logo_icon);
		imgui::PopFont();
		imgui::EndChild();

		//µ¼º½À¸
		static int navs = 0;
		imgui::BeginGroup();
		for (int i = 0; i < components.size(); i++) {
			imgui::PushFont(icons);

			std::string name = components[i].first;
			if (control::navigation(name.c_str(), navs == i)) {
				navs = i;
			}
			imgui::PopFont();
		}
		imgui::EndGroup();

		//·ÖÒ³
		imgui::SetCursorPos({ barsize, 0 });
		imgui::BeginChild("##PAGINATION", { wndsize.x + barsize, barsize * 0.5f });
		imgui::BeginGroup();
		compoment nav = components[navs].second;
		static int paginations = 0;
		for (int i = 0; i < nav.elements.size(); i++) {
			auto [tag, temp] = nav.elements[i];
			if (control::pagination(tag.c_str(), paginations == i)) {
				paginations = i;
			}
			imgui::SameLine();
		}
		imgui::EndGroup();
		imgui::EndChild();

		//Ò³Ãæ
		imgui::SetCursorPos({ barsize + 5, barsize * 0.5f + 5 });
		imgui::BeginChild("##PAGE", { wndsize.x - barsize - 15, wndsize.y - barsize * 0.5f - 10 }, false, ImGuiWindowFlags_Background);
		imgui::SetCursorPos({ 10,10 });
		imgui::BeginGroup();
		nav.elements[paginations].second();
		imgui::EndGroup();
		imgui::EndChild();
		imgui::End();
		return;
	}
}