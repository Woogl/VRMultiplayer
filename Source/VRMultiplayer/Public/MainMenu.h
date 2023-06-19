// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenu.generated.h"

USTRUCT()
struct FServerData 
{
	GENERATED_BODY()

	FString Name;
	uint16 CurrentPlayers;
	uint16 MaxPlayers;
	FString HostUsername;
};
/**
 * 
 */
UCLASS()
class VRMULTIPLAYER_API UMainMenu : public UUserWidget
{
	GENERATED_BODY()

public:
	UMainMenu(const FObjectInitializer& ObjectInitializer);

	void SetServerList(TArray<FServerData> ServerNames);;

private:
	UPROPERTY(meta = (BindWidget))
	class UButton* MultiPlayButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* CounselingButton;

	UPROPERTY(meta = (BindWidget), BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UPanelWidget* ServerList;

	TSubclassOf<class UUserWidget> ServerRowClass;
};
