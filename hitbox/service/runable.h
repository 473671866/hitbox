#ifndef RUNABLE_H
#define RUNABLE_H

#include "../utils/singleton.hpp"
#include "../entity/objects.h"
#include "../unreal_engine/World.h"

class runable : public singleton<runable>
{
private:
	using WorldToSrceenProc = bool(*)(void* Player, const FVector& WorldPosition, FVector2D& ScreenPosition, bool bPlayerViewportRelative);
	UWorld** world;
	WorldToSrceenProc func;

public:
	bool initialize(UWorld** uworld, void* p);
	bool screen(const FVector& WorldPosition, FVector2D& ScreenPosition);
};

#endif // RUNABLE_H
