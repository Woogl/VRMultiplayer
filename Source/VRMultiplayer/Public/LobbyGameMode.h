// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "VRGameMode.h"
#include "LobbyGameMode.generated.h"

/**
 * 
 */
UCLASS()
class VRMULTIPLAYER_API ALobbyGameMode : public AVRGameMode
{
	GENERATED_BODY()

public:
	virtual void PostLogin(APlayerController* NewPlayer) override;

	virtual void Logout(AController* Exiting) override;

private:
	uint32 NumberOfPlayers = 0;

	FTimerHandle GameStartTimer;
};
