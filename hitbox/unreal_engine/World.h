#pragma once
#include "UObject.h"
#include "Level.h"
#include "GameInstance.h"

_declspec(align(8))
struct UWorld : public UObject
{
	ULevel* PersistentLevel;				//0x30
	char Unknown[0x148];					//0x38
	UGameInstance* OwningGameInstance;		//0x180
};
