#ifndef SALE_H
#define SALE_H

#include <iostream>
#include <vector>
#include <windows.h>

#include "../imgui/imgui.h"
#include "../utils/singleton.hpp"

#define WHITE IM_COL32(255, 255, 255, 255)
#define BLACK IM_COL32(0, 0, 0, 255)
#define YELLOW IM_COL32(255, 255, 0, 255)
#define RED IM_COL32(255, 0, 0, 255)
#define DIMGRAY IM_COL32(50 ,50, 50, 255)

namespace view {
	class scale :public singleton<scale> {
	private:
		HWND hwnd;
		std::vector<ImU32> col1;
		std::vector<ImU32> col2;
		float offsets = 30.0f;

	public:
		void show();
		void win(HWND h);
		void p1(int counter, ImU32 color);
		void p2(int index, int size, ImU32 color);
	};
}

#endif // SALE_H
