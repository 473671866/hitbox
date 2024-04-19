#include "control.h"

namespace control {
	bool slider(const char* label, bool* v) {
		bool clicked = false;
		if (imgui::IsItemClicked()) {
			clicked = true;
		}

		ImVec2 p = imgui::GetCursorScreenPos();
		ImDrawList* draw_list = imgui::GetWindowDrawList();

		float height = imgui::GetFrameHeight();
		float width = height * 1.55f;
		float radius = height * 0.50f;

		if (imgui::InvisibleButton(label, ImVec2(width, height))) {
			if (v) {
				*v = !*v;
			}
		}

		ImU32 col_bg;
		if (imgui::IsItemHovered()) {
			imgui::SetMouseCursor(7);
			col_bg = *v ? IM_COL32(145 + 20, 211, 68 + 20, 255) : IM_COL32(218 - 20, 218 - 20, 218 - 20, 255);
		}
		else {
			col_bg = *v ? IM_COL32(145, 211, 68, 255) : IM_COL32(218, 218, 218, 255);
		}

		draw_list->AddRectFilled(p, ImVec2(p.x + width, p.y + height), col_bg, height * 0.5f);
		draw_list->AddCircleFilled(ImVec2(*v ? (p.x + width - radius) : (p.x + radius), p.y + radius), radius - 1.5f, IM_COL32(255, 255, 255, 255));

		return clicked;
	}

	bool trigger(const char* label, bool* v) {
		imgui::Text(label);
		imgui::SameLine();
		imgui::SetCursorPosX(imgui::GetWindowWidth() - 50);
		return control::slider(label, v);
	}

	bool navigation(const char* label, bool selected) {
		ImGuiWindow* window = imgui::GetCurrentWindow();
		if (window->SkipItems)
			return false;

		ImGuiContext& g = *GImGui;
		const ImGuiStyle& style = g.Style;
		const ImGuiID id = window->GetID(label);
		const ImVec2 label_size = imgui::CalcTextSize(label, NULL, true);

		ImVec2 pos = window->DC.CursorPos;
		ImVec2 size = imgui::CalcItemSize(ImVec2(200, 50), label_size.x + style.FramePadding.x * 2.0f, label_size.y + style.FramePadding.y * 2.0f);

		const ImRect rect(pos, pos + size);
		imgui::ItemSize(size, style.FramePadding.y);
		if (!imgui::ItemAdd(rect, id))
			return false;

		bool hovered, held;
		bool pressed = imgui::ButtonBehavior(rect, id, &hovered, &held, NULL);

		if (hovered || held)
			imgui::SetMouseCursor(7);

		if (selected) {
			window->DrawList->AddRectFilled(rect.Min, { rect.Max.x - 150, rect.Max.y }, ImColor(72, 79, 89));
			window->DrawList->AddRectFilled(rect.Min, ImVec2(rect.Min.x + 3, rect.Max.y), ImColor(215, 219, 228));
		}

		window->DrawList->AddLine(ImVec2(rect.Min.x, rect.Max.y), { rect.Max.x - 150, rect.Max.y }, ImColor(46, 52, 64));
		imgui::RenderText(ImVec2(rect.Min.x + 30 - label_size.x / 2 - 5, rect.Min.y + (size.y / 2) - (label_size.y / 2)), label);
		return pressed;
	}

	bool pagination(const char* label, bool selected) {
		ImGuiWindow* window = imgui::GetCurrentWindow();
		if (window->SkipItems)
			return false;

		ImGuiContext& g = *GImGui;
		const ImGuiStyle& style = g.Style;
		const ImGuiID id = window->GetID(label);
		const ImVec2 label_size = imgui::CalcTextSize(label, NULL, true);

		ImVec2 pos = window->DC.CursorPos;
		ImVec2 size = imgui::CalcItemSize(ImVec2(100, 30), label_size.x + style.FramePadding.x * 2.0f, label_size.y + style.FramePadding.y * 2.0f);

		const ImRect rect(pos, pos + size);
		imgui::ItemSize(size, style.FramePadding.y);
		if (!imgui::ItemAdd(rect, id))
			return false;

		bool hovered, held;
		bool pressed = imgui::ButtonBehavior(rect, id, &hovered, &held, NULL);

		if (hovered || held)
			imgui::SetMouseCursor(7);

		if (selected) {
			window->DrawList->AddRectFilled(rect.Min, rect.Max, ImColor(72, 79, 89));
			window->DrawList->AddRectFilled(ImVec2(rect.Min.x, rect.Max.y - 3), ImVec2(rect.Max.x, rect.Max.y), ImColor(215, 219, 228));
		}

		imgui::RenderText(ImVec2(rect.Min.x + size.x / 2 - label_size.x / 2, rect.Min.y + (size.y / 2) - (label_size.y / 2)), label);
		return pressed;
	}

	bool draw_box(ImVec2 rect_min, ImVec2 rect_max, float alpha, float tickness, ImColor color) {
		imgui::GetForegroundDrawList()->AddRect(rect_min, rect_max, imgui::ColorConvertFloat4ToU32(color.Value), 0, 0, tickness);

		color.Value.w = alpha;
		imgui::GetForegroundDrawList()->AddRectFilled(rect_min, rect_max, imgui::ColorConvertFloat4ToU32(color.Value));
		return true;
	}

	bool label(int btn, const char* title, bool* open, bool* selected, ImColor* color) {
		imgui::Text(title); imgui::SameLine();

		imgui::PushID(btn + 10);
		imgui::ColorButton("", color->Value); imgui::SameLine();
		imgui::PopID();

		imgui::PushID(btn);
		if (imgui::Button(u8"ÐÞ¸ÄÑÕÉ«")) {
			*open = !(*open);
		}
		imgui::PopID();

		if (*open) {
			imgui::Begin("color", open, ImGuiWindowFlags_NoResize);
			imgui::SetWindowSize({ 320, 240 });
			imgui::ColorPicker3("picker", (float*)color);
			imgui::End();
		}
		imgui::SameLine();
		imgui::SetCursorPosX(imgui::GetWindowWidth() - 50);
		slider(title, selected);
		return true;
	}
};