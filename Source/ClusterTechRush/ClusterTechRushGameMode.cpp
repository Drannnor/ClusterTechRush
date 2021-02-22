// Copyright Epic Games, Inc. All Rights Reserved.

#include "ClusterTechRushGameMode.h"
#include "ClusterTechRushCharacter.h"
#include "UObject/ConstructorHelpers.h"

AClusterTechRushGameMode::AClusterTechRushGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
