#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <iostream>
#include <windows.h>

#ifdef _DEBUG
#define logger(message, ...) loggers::information(__FUNCTION__, __LINE__, message, __VA_ARGS__)
#else
#define logger(message, ...)
#endif

class loggers {
public:
	static void initialize() {
#ifdef _DEBUG
		AllocConsole();
		freopen("CONOUT$", "w+t", stdout);
		freopen("CONIN$", "r+t", stdin);
#endif
		return;
	}

	// 支持格式化字符串的日志记录函数
	template<typename... args>
	static void information(const char* func, int line, const char* message, args&&... params) {
		char buffer[512]{};
		sprintf(buffer, message, params...);
		printf("%s | %d | %s\n", func, line, buffer);
		return;
	}
};

#endif // LOGGER_HPP