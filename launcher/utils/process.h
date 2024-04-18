#ifndef PROCESS_H
#define PROCESS_H

#include <iostream>
#include <cstring>
#include <vector>
#include <windows.h>
#include <TlHelp32.h>

namespace utils {
	class process {
	private:
		std::uint32_t pid;
		HANDLE hprocess;
		std::vector<void*> records;

	public:
		process() = default;

		~process();

		bool initialize(std::uint32_t pid, const wchar_t* name);

		std::uintmax_t model(const wchar_t* name) noexcept(false);

		std::uint32_t thread_id();

		void* allocate(std::size_t size);

		bool release(void* address);

		template<typename parameter>
		bool reader(parameter address, void* buffer, std::size_t size) {
			return ReadProcessMemory(hprocess, (void*)address, buffer, size, nullptr);
		}

		template<typename parameter>
		bool writer(parameter address, const void* buffer, std::size_t size) {
			return WriteProcessMemory(hprocess, (void*)address, buffer, size, nullptr);
		}

		template<typename parameter>
		bool modify(parameter address, const void* buffer, std::size_t size) {
			unsigned long original = 0;
			VirtualProtect((void*)address, 0x1000, PAGE_EXECUTE_READWRITE, &original);
			bool success = WriteProcessMemory(hprocess, (void*)address, buffer, size, nullptr);
			VirtualProtect((void*)address, 0x1000, original, &original);
			return success;
		}

		template<typename callable, typename parameter>
		HANDLE remote_thread(callable routine, parameter param) {
			return CreateRemoteThread(hprocess, nullptr, 0, (LPTHREAD_START_ROUTINE)routine, (LPVOID)param, 0, nullptr);
		}
	};
}

#endif
