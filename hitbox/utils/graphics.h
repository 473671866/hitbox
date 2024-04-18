#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <d3d11.h>

#include "singleton.hpp"
#include "../imgui/imgui.h"
#include "../imgui/imgui_impl_win32.h"
#include "../imgui/imgui_impl_dx11.h"

enum class options :int {
	present = 8,
	resize = 13,
};

class graphics : public singleton<graphics>
{
private:
	void** virtual_table;
	IDXGISwapChain* chain;

public:
	bool initialize(HWND hwnd);
	bool hook(void* handler, void* original, options op);
};

#endif // !GRAPHICS_H
