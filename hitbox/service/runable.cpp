#include "runable.h"

bool runable::initialize(UWorld** uworld, void* p)
{
	world = uworld;
	func = reinterpret_cast<WorldToSrceenProc>(p);
	return true;
}

bool runable::screen(const FVector& WorldPosition, FVector2D& ScreenPosition)
{
	return func((*world)->OwningGameInstance->LocalPlayers.AllocatorInstance[0]->PlayerController, WorldPosition, ScreenPosition, false);
}