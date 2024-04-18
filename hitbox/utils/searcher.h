#ifndef SEARCHER_H
#define SEARCHER_H

#include <windows.h>
#include "singleton.hpp"

class searcher : public singleton<searcher>
{
private:
	unsigned char hex(unsigned char* ch);
	int initialize(unsigned char* hex, unsigned char* ch);
	unsigned __int64 compare(unsigned char* hex, unsigned __int64 length, unsigned __int64 start, unsigned __int64 end);

public:
	template<typename parameter, typename returned = unsigned __int64>
	returned search(parameter address, unsigned __int64 size, const char* signature)
	{
		unsigned char hex[0x200]{ NULL };
		int length = this->initialize(hex, (unsigned char*)signature);
		return (returned)this->compare(hex, (unsigned __int64)address, (unsigned __int64)address + size, length);
	}

	template<typename returned = unsigned __int64>
	returned search(const char* section, const char* signature)
	{
		auto hmodule = reinterpret_cast<unsigned __int64>(GetModuleHandleA(nullptr));
		auto dos_header = reinterpret_cast<IMAGE_DOS_HEADER*>(hmodule);
		auto nt_headers = reinterpret_cast<IMAGE_NT_HEADERS*>(hmodule + dos_header->e_lfanew);
		PIMAGE_SECTION_HEADER section_header = IMAGE_FIRST_SECTION(nt_headers);

		for (int i = 0; i < nt_headers->FileHeader.NumberOfSections; i++) {
			char buffer[9]{};
			memcpy(buffer, section_header->Name, 8);
			if (_stricmp(buffer, section) == 0) {
				break;
			}
			section_header++;
		}

		unsigned char hex[0x200]{ NULL };
		int length = this->initialize(hex, (unsigned char*)signature);
		auto start = hmodule + section_header->VirtualAddress;
		auto end = start + section_header->SizeOfRawData;
		return (returned)this->compare(hex, length, start, end);
	}

	template<typename parameter, typename returned = unsigned __int64>
	returned transform(parameter address) {
		LARGE_INTEGER result{};
		if (address != 0) {
			result.QuadPart = (unsigned long long)((unsigned long long)address + 7);
			result.LowPart += *(unsigned __int32*)((unsigned long long)address + 3);
		}
		return (returned)result.QuadPart;
	}
};

#endif // SEARCHER_H
