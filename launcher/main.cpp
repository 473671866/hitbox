#include <iostream>
#include <windows.h>
#include "utils/loader.h"
#include "hitbox.h"
#pragma comment(linker, "/subsystem:windows /entry:mainCRTStartup")

#ifndef _WIN64
#error errors requires x64 environment
#endif

int main() {
	try {
		utils::loader load;
		load.shadow(L"KOFXV-Win64-Shipping.exe", hitbox, sizeof(hitbox));
	}
	catch (std::exception& e) {
		MessageBoxA(0, e.what(), "warning", MB_OK);
	}
	return 0;
}