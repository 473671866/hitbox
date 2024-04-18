#pragma once
#include "UObject.h"
#include "Array.h"
#include "Player.h"

_declspec(align(8))
struct UGameInstance : public UObject
{
	void* UnKnown;					//0x30
	TArray<UPlayer*> LocalPlayers;	//0x38
};
