#pragma once
#include <iostream>
#include <windows.h>

#include "control.h"
#include "../box/context.h"
#include "../utils/macro.hpp"
#include "../utils/singleton.hpp"

class draws : public singleton<draws>
{
private:
	services* serivce;
	mappers* mapper;
	bool dp1;
	bool dp2;
	float alpha;

public:
	bool initialize(services* service, mappers* mapper);
	void menus();
	bool draw();
};
