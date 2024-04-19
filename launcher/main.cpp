#include <iostream>
#include <windows.h>
#include "utils/loader.h"

#ifdef _DEBUG
constexpr auto path = "..\\x64\\Debug\\hitbox.dll";
#else
#pragma comment(linker, "/subsystem:windows /entry:mainCRTStartup")
constexpr auto path = "..\\x64\\Release\\hitbox.dll";
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