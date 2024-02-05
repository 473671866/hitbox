#pragma once
#include "signatures.hpp"
#include "../utils/searcher.h"
#include "../utils/singleton.hpp"
#include "../structs/objects.h"
#include "../unreal_engine/World.h"

class mappers : public singleton<mappers>
{
public:
	UWorld** uworld;
	objects** objs;

public:
	bool initliaze();
};
