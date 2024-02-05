#include "memory.h"
#include <windows.h>

bool memory::probe(void* address, unsigned long long size, unsigned __int32 alignment)
{
	if (address == nullptr) {
		return false;
	}

	if (size == 0) {
		return false;
	}

	unsigned long long current = (unsigned long long)address;
	if (((unsigned long long)address & (alignment - 1)) != 0) {
		return false;
	}

	unsigned long long last = current + size - 1;
	if (last < current) {
		return false;
	}

	return true;
}

bool memory::hook(void** vtbl, void* handler, void* original, int index)
{
	if (vtbl != nullptr && handler != nullptr) {
		if (original != nullptr) {
			*reinterpret_cast<void**>(original) = vtbl[index];
		}

		unsigned long protect = 0;
		if (VirtualProtect(&vtbl[index], 0x1000, PAGE_EXECUTE_READWRITE, &protect)) {
			vtbl[index] = handler;
			VirtualProtect(&vtbl[index], 0x1000, protect, &protect);
			return true;
		}
	}
	return false;
}