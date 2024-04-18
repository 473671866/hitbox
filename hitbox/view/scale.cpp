#include "scale.h"

namespace view {
	void scale::show() {
		RECT rect;
		GetClientRect(hwnd, &rect);

		int width = rect.right - rect.left;
		int height = rect.bottom - rect.top;
		float middle = height * 0.8f;
		float left = width * 0.05f;
		float right = width * 0.95f;

		ImVec2 size = { (float)std::abs(right - left), 20.f };
		ImVec2 head = { left, middle - size.y / 2 };
		ImVec2 tail(head.x + size.x, head.y + size.y);

		int ticks = 100;
		float step = size.x / static_cast<float>(ticks - 1);
		//float step = 12.0f;
		//int ticks = static_cast<int>(size.x / step) + 1;
		auto forceground = ImGui::GetForegroundDrawList();

		ImVec2 shadow_head = { head.x - head.x * 0.01f, head.y - head.y * 0.005f };
		ImVec2 shadow_tail = { tail.x + tail.x * 0.01f, tail.y + tail.y * 0.005f };
		forceground->AddText({ shadow_head.x + 5, shadow_head.y - 15 }, WHITE, "FRAME");
		forceground->AddText({ shadow_tail.x - 50, shadow_tail.y - 40 }, WHITE, "PLAYER1");
		forceground->AddRectFilled(shadow_head, shadow_tail, IM_COL32(0, 0, 0, 255));
		col1.resize(ticks, DIMGRAY);

		shadow_head = { head.x - head.x * 0.01f, head.y - head.y * 0.005f + offsets };
		shadow_tail = { tail.x + tail.x * 0.01f, tail.y + tail.y * 0.005f + offsets };
		forceground->AddText({ shadow_head.x + 5, shadow_head.y + 30 }, WHITE, "FRAME");
		forceground->AddText({ shadow_tail.x - 50, shadow_tail.y + 5 }, WHITE, "PLAYER2");
		forceground->AddRectFilled(shadow_head, shadow_tail, IM_COL32(0, 0, 0, 255));
		col2.resize(ticks, DIMGRAY);

		for (int i = 0; i < ticks; ++i) {
			ImVec2 tick_head(head.x + i * step, head.y);
			ImVec2 tick_tail(tick_head.x, tail.y);
			ImVec2 rect_min(tick_head.x, head.y);
			ImVec2 rect_max(tick_tail.x + step, tail.y);
			ImVec2 text = { rect_min.x + 3, rect_min.y + 5 };
			forceground->AddRectFilled(rect_min, rect_max, col1[i]);
			forceground->AddLine(tick_head, tick_tail, BLACK, 2.0f);
			//forceground->AddText(text, WHITE, "11");

			rect_min = { tick_head.x, head.y + offsets };
			rect_max = { tick_tail.x + step, tail.y + offsets };
			tick_head = { head.x + i * step, head.y + offsets };
			tick_tail = { tick_tail.x, tail.y + offsets };
			text = { rect_min.x + 3, rect_min.y + 5 };
			forceground->AddRectFilled(rect_min, rect_max, col2[i]);
			forceground->AddLine(tick_head, tick_tail, BLACK, 2.0f);
			//forceground->AddText(text, WHITE, "11");
		}
	}

	void scale::win(HWND h) {
		hwnd = h;
	}

	void scale::p1(int index, int size, ImU32 color) {
		if (index < col1.size()) {
			std::fill(col1.begin() + index, col1.begin() + index + size, color);
		}
	}

	void scale::p2(int index, int size, ImU32 color)
	{
		if (index + size < col2.size()) {
			std::fill(col2.begin() + index, col2.begin() + index + size, color);
		}
	}
};