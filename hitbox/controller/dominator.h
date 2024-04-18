#ifndef DOMINATOR_H
#define DOMINATOR_H
#include <windows.h>

#include "../context/context.h"
#include "../mapper/mapper.h"
#include "../view/decoration.h"
#include "../view/scale.h"
#include "../service/runable.h"
#include "../utils/singleton.hpp"
#include "../context/description.h"
#include "../font/msyh.h"
#include "../font/FontAewsome6.h"
#include "../font/IconsFontAwesome6.inl"
#include "../font/FontAwesome6Brands.h"
#include "../font/IconsFontAwesome6Brands.inl"

class dominator :public singleton<dominator> {
public:
	HWND hwnd;
	ImFont* font_mshy = nullptr;
	ImFont* icon_awesmoe = nullptr;
	ImFont* icon_brands = nullptr;
	bool dp1 = false;
	bool dp2 = false;
	bool fps = false;
	bool async = true;
	float alpha = 0.2f;
	float thickness = 1.0f;

public:
	dominator();
	bool run();
	bool draw();
	bool window(HWND h);
	bool test();
};

#endif // DOMINATOR_H
