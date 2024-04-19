#include <iostream>
#include <windows.h>
#include <TlHelp32.h>
#include "utils/loader.h"
//#include "process.h"
//#include "hitbox.hpp"

//#pragma comment(linker, "/subsystem:windows /entry:mainCRTStartup")

int main() {
	//HMODULE hmodule = GetModuleHandleA("kernel32.dll");
	//auto loadlibrary = (void**)GetProcAddress(hmodule, "LoadLibraryA");
	//auto freelibrary = (void**)GetProcAddress(hmodule, "FreeLibrary");

	//utils::process proc;
	//proc.initialize(0, L"KOFXV-Win64-Shipping.exe");

	//char source[14] = { };
	//std::memcpy(source, loadlibrary, sizeof(source));
	//proc.modify(loadlibrary, source, sizeof(source));

	//char original[14] = { };
	//std::memcpy(original, freelibrary, sizeof(original));
	//proc.modify(freelibrary, original, sizeof(original));
	try {
		utils::loader load;
		//load.shadow(L"KOFXV-Win64-Shipping.exe", hitbox, sizeof(hitbox));
#ifdef _DEBUG
		load.remote_thread(L"KOFXV-Win64-Shipping.exe", "..\\x64\\Debug\\hitbox.dll");
#else
		load.remote_thread(L"KOFXV-Win64-Shipping.exe", "..\\x64\\Release\\hitbox.dll");
#endif
	}
	catch (std::exception& e) {
		MessageBoxA(0, e.what(), "warning", MB_OK);
	}
	return 0;
}