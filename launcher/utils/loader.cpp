#include "loader.h"
#include "MemLoadDll.h"
#include "scope_exit.hpp"
#include "process.h"

namespace utils {
	bool loader::shadow(const wchar_t* name, unsigned __int8* file, unsigned long size) {
		std::unique_ptr<unsigned __int8[]> filebuffer(new unsigned __int8[size]);
		std::memcpy(filebuffer.get(), file, size);

		auto dos_header = reinterpret_cast<IMAGE_DOS_HEADER*>(filebuffer.get());
		if (dos_header->e_magic != IMAGE_DOS_SIGNATURE) {
			throw std::exception("library invalid");
			return false;
		}

		auto nt_headers = reinterpret_cast<IMAGE_NT_HEADERS*>(filebuffer.get() + dos_header->e_lfanew);
		if (nt_headers->Signature != IMAGE_NT_SIGNATURE || nt_headers->FileHeader.Machine != IMAGE_FILE_MACHINE_AMD64) {
			throw std::exception("library invalid");
			return false;
		}

		process proc;
		bool success = proc.initialize(0, name);
		if (!success) {
			throw std::exception("process invalid");
			return false;
		}

		void* library = proc.allocate(size); ;
		void* shellcode = proc.allocate(sizeof(MemLoadShellcode_x64));

		success = proc.writer(library, filebuffer.get(), size);
		if (!success) {
			throw std::exception("permission denied");
			return false;
		}

		success = proc.writer(shellcode, MemLoadShellcode_x64, sizeof(MemLoadShellcode_x64));
		if (!success) {
			throw std::exception("permission denied");
			return false;
		}

		HANDLE remote_thread = proc.remote_thread(shellcode, library);
		if (remote_thread == INVALID_HANDLE_VALUE || remote_thread == 0) {
			throw std::exception("permission denied");
			return false;
		}

		WaitForSingleObject(remote_thread, INFINITE);
		CloseHandle(remote_thread);
		return true;
	}

	bool loader::remote_thread(const wchar_t* name, const char* filepath)
	{
		process proc;
		bool success = proc.initialize(0, name);
		if (!success) {
			throw std::exception("process invalid");
			return false;
		}

		bool exists = std::filesystem::exists(filepath);
		if (!exists) {
			throw std::exception("path invliad");
			return false;
		}

		std::string fullpath = std::filesystem::absolute(filepath).string();

		void* address = proc.allocate(0x1000);
		if (address == nullptr) {
			return false;
		}

		success = proc.writer(address, fullpath.c_str(), fullpath.length());
		if (!success) {
			throw std::exception("permission denied");
			return false;
		}

		HMODULE hmodule = GetModuleHandleA("kernel32.dll");
		if (hmodule == INVALID_HANDLE_VALUE || hmodule == 0) {
			throw std::exception("library invalid");
			return false;
		}

		auto loadlibrary = (void**)GetProcAddress(hmodule, "LoadLibraryA");

		char source[14] = { };
		std::memcpy(source, loadlibrary, sizeof(source));

		char backups[14] = { };
		success = proc.reader(loadlibrary, (void*)backups, sizeof(backups));
		if (!success) {
			throw std::exception("permission denied");
			return false;
		}

		success = proc.modify(loadlibrary, source, sizeof(source));
		if (!success) {
			throw std::exception("permission denied");
			return false;
		}

		HANDLE hthread = proc.remote_thread(loadlibrary, address);
		if (hthread == INVALID_HANDLE_VALUE || hthread == 0) {
			proc.modify(loadlibrary, backups, sizeof(backups));
			throw std::exception("permission denied");
			return false;
		}

		WaitForSingleObject(hthread, INFINITE);
		CloseHandle(hthread);
		proc.modify(loadlibrary, backups, sizeof(backups));
		return true;
	}

	bool loader::apc(const wchar_t* name, const char* filepath) {
		process proc;
		bool success = proc.initialize(0, name);
		if (!success) {
			throw std::exception("process invalid");
			return false;
		}

		bool exists = std::filesystem::exists(filepath);
		if (!exists) {
			throw std::exception("path invliad");
			return false;
		}

		std::string fullpath = std::filesystem::absolute(filepath).string();

		void* address = proc.allocate(0x1000);
		if (address == nullptr) {
			throw std::exception("permission denied");
			return false;
		}

		success = proc.writer(address, fullpath.c_str(), fullpath.length());
		if (!success) {
			throw std::exception("permission denied");
			return false;
		}

		HMODULE hmodule = GetModuleHandleA("kernel32.dll");
		if (hmodule == INVALID_HANDLE_VALUE || hmodule == 0) {
			throw std::exception("library invalid");
			return false;
		}

		auto loadlibrary = (void**)GetProcAddress(hmodule, "LoadLibraryA");

		char source[14] = { };
		std::memcpy(source, loadlibrary, sizeof(source));

		char backups[14] = { };
		proc.reader(loadlibrary, (void*)backups, sizeof(backups));

		success = proc.modify(loadlibrary, source, sizeof(source));
		if (!success) {
			throw std::exception("permission denied");
			return false;
		}

		auto tid = proc.thread_id();
		HANDLE hthread = OpenThread(THREAD_ALL_ACCESS, false, tid);
		if (hthread == INVALID_HANDLE_VALUE || hthread == 0) {
			proc.modify(loadlibrary, backups, sizeof(backups));
			throw std::exception("permission denied");
			return false;
		}

		QueueUserAPC((PAPCFUNC)loadlibrary, hthread, (ULONG_PTR)address);
		WaitForSingleObject(hthread, INFINITE);
		CloseHandle(hthread);
		return true;
	}

	bool loader::free(const wchar_t* name, const wchar_t* lib)
	{
		process proc;
		bool success = proc.initialize(0, name);
		if (!success) {
			throw std::exception("process invalid");
			return false;
		}

		auto handle = proc.model(lib);
		if (handle == 0) {
			throw std::exception("library invalid");
			return false;
		}

		HMODULE hmodule = GetModuleHandleA("kernel32.dll");
		if (hmodule == INVALID_HANDLE_VALUE || hmodule == 0) {
			throw std::exception("library invalid");
			return false;
		}

		auto freelibrary = (void**)GetProcAddress(hmodule, "FreeLibrary");

		char source[14] = { };
		std::memcpy(source, freelibrary, sizeof(source));

		char backups[14] = { };
		proc.reader(freelibrary, (void*)backups, sizeof(backups));

		if (!success) {
			throw std::exception("permission denied");
			return false;
		}

		success = proc.modify(freelibrary, source, sizeof(source));
		if (!success) {
			throw std::exception("permission denied");
			return false;
		}

		HANDLE hthread = proc.remote_thread(freelibrary, handle);
		if (hthread == INVALID_HANDLE_VALUE || hthread == 0) {
			proc.modify(freelibrary, backups, sizeof(backups));
			throw std::exception("permission denied");
			return false;
		}

		WaitForSingleObject(hthread, INFINITE);
		CloseHandle(hthread);
		proc.modify(freelibrary, backups, sizeof(backups));

		return true;
	}
}