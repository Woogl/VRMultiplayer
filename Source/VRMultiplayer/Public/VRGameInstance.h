// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Interfaces/OnlineSessionInterface.h"
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

	UFUNCTION(BlueprintCallable)
	void RefreshServerList();

private:
	TSharedPtr<class IOnlineSession, ESPMode::ThreadSafe> SessionInterface;
	TSharedPtr<class FOnlineSessionSearch> SessionSearch;

	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UUserWidget* MainUI;

	void OnCreateSessionComplete(FName SessionName, bool Success);
	void OnDestroySessionComplete(FName SessionName, bool Success);
	void OnFindSessionComplete(bool Success);
	void OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result);
};
