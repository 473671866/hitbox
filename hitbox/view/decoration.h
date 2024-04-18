#ifndef INTERFACE_H
#define INTERFACE_H

#include <iostream>
#include <functional>
#include <vector>

#include "control.h"

namespace view {
	class compoment {
	public:
		std::vector<std::pair<std::string, std::function<void()>>> elements;

	public:
		bool ins(const char* tag, std::function<void()> element);
		bool del(const char* tag);
	};

	class decoration {
	private:
		std::vector <std::pair<std::string, compoment>> components;
		float barsize = 60.f;
		ImFont* icons = nullptr;
		ImFont* logos = nullptr;
		const char* logo_icon;

	public:
		void show(const char* name, ImVec2 size = { 720 - 720 * 0.1f, 480 - 480 * 0.1f });

		bool insert(const char* icon, compoment comp);
		bool remove(const char* name);
		bool icon(ImFont* font);
		bool logo(ImFont* font, const char* icon);
	};
};

#endif // INTERFACE_H