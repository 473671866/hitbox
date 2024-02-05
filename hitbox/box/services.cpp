#include "services.h"

bool services::initliaze(mappers* mapping)
{
	searcher* instance = searcher::instance();
	this->screen_ptr = instance->search<bool(*)(void* Player, const FVector & WorldPosition, FVector2D & ScreenPosition, bool bPlayerViewportRelative)>(".text", signatures::screen);
	if (screen_ptr == nullptr) {
		return false;
	}

	this->mapping = mapping;
	this->uworld = *mapping->uworld;
	if (this->uworld == nullptr) {
		return false;
	}

	return true;
}

bool services::screen(const FVector& WorldPosition, FVector2D& ScreenPosition)
{
	this->uworld = *mapping->uworld;
	if (this->uworld == nullptr) {
		return false;
	}
	return screen_ptr(uworld->OwningGameInstance->LocalPlayers.AllocatorInstance[0]->PlayerController, WorldPosition, ScreenPosition, false);
}