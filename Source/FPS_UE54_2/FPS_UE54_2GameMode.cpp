// Copyright Epic Games, Inc. All Rights Reserved.

#include "FPS_UE54_2GameMode.h"
#include "FPS_UE54_2Character.h"
#include "UObject/ConstructorHelpers.h"

AFPS_UE54_2GameMode::AFPS_UE54_2GameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
