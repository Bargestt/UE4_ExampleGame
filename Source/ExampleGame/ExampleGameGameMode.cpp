// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "ExampleGameGameMode.h"
#include "UObject/ConstructorHelpers.h"

AExampleGameGameMode::AExampleGameGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Character/Blueprints/BasicMarine"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
