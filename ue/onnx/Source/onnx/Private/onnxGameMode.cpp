// Copyright Epic Games, Inc. All Rights Reserved.

#include "onnxGameMode.h"
#include "onnxCharacter.h"
#include "UObject/ConstructorHelpers.h"

AonnxGameMode::AonnxGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
