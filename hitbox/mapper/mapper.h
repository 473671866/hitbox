#ifndef MAPPER_H
#define MAPPER_H

#include "../utils/searcher.h"
#include "../utils/singleton.hpp"
#include "../entity/objects.h"
#include "../unreal_engine/World.h"

namespace signatures {
	constexpr auto uworld = "48******488B***488BC7488B***48***5EC3";
	constexpr auto screen = "4889***4889***4889***5748******410FB6E9498BD8488BF2488BF94885C90F";
	constexpr auto objects = "48******428B***83**3B88";
}

class mapper : public singleton<mapper> {
public:
	UWorld** uworld;
	objects** objs;
	bool(*WorldToScreen)(void* Player, const FVector& WorldPosition, FVector2D& ScreenPosition, bool bPlayerViewportRelative);

public:
	bool initliaze();
};

#endif // MAPPER_H