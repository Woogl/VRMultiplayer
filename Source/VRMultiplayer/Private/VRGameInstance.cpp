// Fill out your copyright notice in the Description page of Project Settings.


#include "VRGameInstance.h"
#include "OnlineSubSystem.h"
#include <OnlineSessionSettings.h>
#include "Interfaces/OnlineSessionInterface.h"

void UVRGameInstance::Init()
{
	Super::Init();

	IOnlineSubsystem* OnlineSubSystem = IOnlineSubsystem::Get();
    if (OnlineSubSystem)
    {
        WG_STRING(*OnlineSubSystem->GetSubsystemName().ToString());
		SessionInterface = OnlineSubSystem->GetSessionInterface();
		if (SessionInterface.IsValid())
		{
			SessionInterface->OnCreateSessionCompleteDelegates.AddUObject(this, &UVRGameInstance::OnCreateSessionComplete);
			SessionInterface->OnDestroySessionCompleteDelegates.AddUObject(this, &UVRGameInstance::OnDestroySessionComplete);
		}
    }
}

void UVRGameInstance::CreateSession()
{
	if (!SessionInterface.IsValid()) return;

	FOnlineSessionSettings SessionSettings;
	if (IOnlineSubsystem::Get()->GetSubsystemName() == "NULL")
	{
		SessionSettings.bIsLANMatch = true;
	}
	else
	{
		SessionSettings.bIsLANMatch = false;
	}
	SessionSettings.NumPublicConnections = 4;
	SessionSettings.bShouldAdvertise = true;
	SessionSettings.bUsesPresence = true;
	SessionSettings.bUseLobbiesIfAvailable = true;

	SessionInterface->CreateSession(0, NAME_GameSession, SessionSettings);
}

void UVRGameInstance::OnCreateSessionComplete(FName SessionName, bool Success)
{
	if (Success)
	{
		WG_TEXT("Create Session Success!");
		UWorld* World = GetWorld();
		if (World)
		{
			World->ServerTravel("/Game/Sample/VRTemplate/Maps/VRTemplateMap?listen");
		}
	}
	else
	{
		WG_TEXT("Create Session Failed!");
	}
}

void UVRGameInstance::OnDestroySessionComplete(FName SessionName, bool Success)
{
	if (Success)
	{
		CreateSession();
	}
}
