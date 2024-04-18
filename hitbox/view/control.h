#ifndef CONTROL_H
#define CONTROL_H

#include "../imgui/imgui.h"
#include "../imgui/imgui_internal.h"
namespace imgui = ImGui;

namespace control {
	template<typename callable>
	bool button(const char* label, callable&& handler, int id = 0) {
		if (id) {
			imgui::PushID(id);
		}

		bool clicked = false;
		imgui::Button(label);
		if (ImGui::IsItemClicked()) {
			handler();
			clicked = true;
		}

		if (id) {
			imgui::PopID();
		}

		return clicked;
	}

	bool slider(const char* label, bool* v);
	bool trigger(const char* label, bool* v);
	bool navigation(const char* label, bool selected);
	bool pagination(const char* label, bool selected);
	bool draw_box(ImVec2 rect_min, ImVec2 rect_max, float alpha, float tickness, ImColor color);
	bool label(int btn, const char* title, bool* open, bool* selected, ImColor* color);
};

#endif // CONTROL_H
