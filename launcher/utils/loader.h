#ifndef LOADER_H
#define LOADER_H

#include <memory>
#include <fstream>
#include <iostream>
#include <windows.h>
#include <filesystem>

namespace utils {
#pragma pack(push, 1)
	struct trampline {
		std::uint8_t jmp[0x6] = { 0xff, 0x25, 0, 0, 0, 0 };
		std::uintmax_t address;
	};
#pragma pack(pop)

	class loader
	{
	public:
		bool shadow(const wchar_t* name, unsigned __int8* file, unsigned long size) noexcept(false);
		bool remote_thread(const wchar_t* name, const char* filepath) noexcept(false);
		bool apc(const wchar_t* name, const char* filepath) noexcept(false);
		bool free(const wchar_t* name, const wchar_t* lib) noexcept(false);
	};
}

#endif // LOADER_H
