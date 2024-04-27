#include <iostream>
#include <windows.h>
#include "utils/loader.h"
#pragma comment(linker, "/subsystem:windows /entry:mainCRTStartup")

#ifdef _DEBUG
constexpr auto path = "..\\x64\\Debug\\hitbox.dll";
#else
constexpr auto path = ".\\hitbox.dll";
#endif

int main() {
	try {
		utils::loader load;
		load.remote_thread(L"KOFXV-Win64-Shipping.exe", path);
	}
	catch (std::exception& e) {
		MessageBoxA(0, e.what(), "warning", MB_OK);
	}
	return 0;
}