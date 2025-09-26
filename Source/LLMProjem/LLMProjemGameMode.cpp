// Copyright Epic Games, Inc. All Rights Reserved.

#include "LLMProjemGameMode.h"
#include "LLMProjemCharacter.h"
#include "UObject/ConstructorHelpers.h"

ALLMProjemGameMode::ALLMProjemGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
