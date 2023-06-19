// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyGameMode.h"
#include "VRGameInstance.h"

void ALobbyGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	WG_FUNC();
	NumberOfPlayers++;
	if (GEngine) { GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Number of Players : %d"), NumberOfPlayers)); }
}

void ALobbyGameMode::Logout(AController* Exiting)
{
	Super::Logout(Exiting);

	WG_FUNC();
	NumberOfPlayers--;
	if (GEngine) { GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Number of Players : %d"), NumberOfPlayers)); }
}
