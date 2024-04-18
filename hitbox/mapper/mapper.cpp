#include "mapper.h"

bool mapper::initliaze()
{
	searcher* instance = searcher::instance();

	this->uworld = reinterpret_cast<UWorld**>(instance->transform(instance->search(".text", signatures::uworld)));
	if (this->uworld == nullptr) {
		return false;
	}

	this->objs = reinterpret_cast<objects**>(instance->transform(instance->search(".text", signatures::objects)));
	if (this->objs == nullptr) {
		return false;
	}

	this->WorldToScreen = reinterpret_cast<bool(*)(void* Player, const FVector & WorldPosition, FVector2D & ScreenPosition, bool bPlayerViewportRelative)>(instance->search(".text", signatures::screen));
	if (this->WorldToScreen == nullptr) {
		return false;
	}

	return true;
}

//bool mapper::screen(box_helper& r)
//{
//	FVector w1{};
//	w1.X = r.left;
//	w1.Z = r.top;
//	FVector2D s1{};
//	WorldToScreen((*uworld)->OwningGameInstance->LocalPlayers.AllocatorInstance[0]->PlayerController, w1, s1, false);
//
//	FVector w3{};
//	w3.X = r.right;
//	w3.Z = r.bottom;
//	FVector2D s3{};
//	WorldToScreen((*uworld)->OwningGameInstance->LocalPlayers.AllocatorInstance[0]->PlayerController, w3, s3, false);
//
//	ImVec2 rect_min(s1.X, s1.Y);
//	ImVec2 rect_max(s3.X, s3.Y);
//}