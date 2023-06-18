// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "VRGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class VRMULTIPLAYER_API UVRGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	virtual void Init();

	UFUNCTION(BlueprintCallable)
	void CreateSession();

private:
	TSharedPtr<class IOnlineSession, ESPMode::ThreadSafe> SessionInterface;

	void OnCreateSessionComplete(FName SessionName, bool Success);
	void OnDestroySessionComplete(FName SessionName, bool Success);
};
