#include "process.h"

namespace utils {
	bool process::initialize(std::uint32_t pid, const wchar_t* name) {
		HANDLE snapshot_handle = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
		if (snapshot_handle == INVALID_HANDLE_VALUE || snapshot_handle == nullptr) {
			return false;
		}

		bool survival = false;
		HANDLE hprocess = INVALID_HANDLE_VALUE;
		PROCESSENTRY32 process_entry = { .dwSize = sizeof(PROCESSENTRY32) };
		bool success = Process32First(snapshot_handle, &process_entry);
		while (success) {
			if (pid) {
				if (pid == process_entry.th32ProcessID) {
					this->pid = process_entry.th32ProcessID;
					this->hprocess = OpenProcess(PROCESS_ALL_ACCESS, false, process_entry.th32ProcessID);
					survival = true;
					break;
				}
			}

			if (name) {
				if (_wcsicmp(process_entry.szExeFile, name) == 0) {
					this->pid = process_entry.th32ProcessID;
					this->hprocess = OpenProcess(PROCESS_ALL_ACCESS, false, process_entry.th32ProcessID);
					survival = true;
					break;
				}
			}
			success = Process32Next(snapshot_handle, &process_entry);
		}
		CloseHandle(snapshot_handle);
		return survival;
	}

	process::~process() {
		for (auto address : records) {
			VirtualFreeEx(hprocess, address, 0, MEM_RELEASE);
		}
		CloseHandle(hprocess);
		hprocess = nullptr;
	}

	std::uintmax_t process::model(const wchar_t* name) {
		HMODULE hmodule = nullptr;
		HANDLE snapshot_handle = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, pid);
		if (snapshot_handle == nullptr || snapshot_handle == INVALID_HANDLE_VALUE) {
			throw std::exception("failed to create snapshot");
		}

		MODULEENTRY32 module_entry{ .dwSize = sizeof(MODULEENTRY32) };
		bool success = Module32First(snapshot_handle, &module_entry);
		if (success) {
			do {
				if (_wcsicmp(module_entry.szModule, name) == 0) {
					hmodule = module_entry.hModule;
					break;
				}
			} while (Module32Next(snapshot_handle, &module_entry));
		}

		CloseHandle(snapshot_handle);
		return reinterpret_cast<std::uintmax_t>(hmodule);
	}

	std::uint32_t process::thread_id() {
		HANDLE snapshot_handle = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, pid);
		if (snapshot_handle == INVALID_HANDLE_VALUE)
			throw std::exception("failed to create snapshot");

		THREADENTRY32 thread_entry = { };
		thread_entry.dwSize = sizeof(THREADENTRY32);
		std::uint32_t tid = 0;
		bool success = Thread32First(snapshot_handle, &thread_entry);
		if (success) {
			do {
				if (thread_entry.th32OwnerProcessID == pid) {
					tid = thread_entry.th32ThreadID;
					break;
				}
			} while (Thread32Next(snapshot_handle, &thread_entry));
		}

		CloseHandle(snapshot_handle);
		return tid;
	}

	void* process::allocate(std::size_t size) {
		void* address = VirtualAllocEx(hprocess, nullptr, size, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
		records.push_back(address);
		return address;
	}

	bool process::release(void* address) {
		return VirtualFreeEx(hprocess, address, 0, MEM_RELEASE);
	}
}