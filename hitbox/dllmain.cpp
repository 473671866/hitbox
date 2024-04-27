#include <windows.h>
#include <thread>
#include "entry/entry.h"

PRUNTIME_FUNCTION rebuild_exception(
	_In_ DWORD64 ControlPc,
	_In_opt_ PVOID Context
)
{
	auto header = reinterpret_cast<unsigned long long>(Context);
	auto dos_header = reinterpret_cast<IMAGE_DOS_HEADER*>(header);
	auto nt_header = reinterpret_cast<IMAGE_NT_HEADERS*>(header + dos_header->e_lfanew);
	auto dircetory = &nt_header->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXCEPTION];
	auto routine = reinterpret_cast<PRUNTIME_FUNCTION>(header + dircetory->VirtualAddress);

	PRUNTIME_FUNCTION result = nullptr;
	for (int i = 0; i < dircetory->Size / sizeof(RUNTIME_FUNCTION); i++) {
		unsigned long long start = (header + routine[i].BeginAddress);
		unsigned long long end = (header + routine[i].EndAddress);
		if (ControlPc >= start && ControlPc <= end) {
			result = &routine[i];
			break;
		}
	}
	return result;
}

BOOL APIENTRY DllMain(HMODULE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH: {
		try {
			std::thread(entry, hModule).detach();
		}
		catch (std::exception& e) {
			MessageBoxA(NULL, e.what(), "warning", MB_OK);
			TerminateProcess(GetCurrentProcess(), 0);
		}
		//auto header = reinterpret_cast<unsigned long long>(hModule);
		//auto dos_header = reinterpret_cast<IMAGE_DOS_HEADER*>(header);
		//auto nt_header = reinterpret_cast<IMAGE_NT_HEADERS*>(header + dos_header->e_lfanew);
		//RtlInstallFunctionTableCallback(header | 3, header, nt_header->OptionalHeader.SizeOfImage, rebuild_exception, hModule, NULL);
		break;
	}
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}