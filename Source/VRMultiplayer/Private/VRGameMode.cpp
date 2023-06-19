// Fill out your copyright notice in the Description page of Project Settings.


#include "VRGameMode.h"

AVRGameMode::AVRGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Sample/VRTemplate/Blueprints/VRPawn"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

