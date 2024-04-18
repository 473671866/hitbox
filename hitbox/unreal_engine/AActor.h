#pragma once
#include "UObject.h"
#include "SceneComponent.h"
struct AActor : public UObject
{
	char Unknown[0x100];
	USceneComponent* RootComponent;	//0x130
};
