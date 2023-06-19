// Fill out your copyright notice in the Description page of Project Settings.


#include "VRGameInstance.h"
#include "OnlineSubSystem.h"
#include "OnlineSessionSettings.h"
#include "MainMenu.h"

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
			SessionInterface->OnFindSessionsCompleteDelegates.AddUObject(this, &UVRGameInstance::OnFindSessionComplete);
			SessionInterface->OnJoinSessionCompleteDelegates.AddUObject(this, &UVRGameInstance::OnJoinSessionComplete);
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

void UVRGameInstance::RefreshServerList()
{
	SessionSearch = MakeShareable(new FOnlineSessionSearch());
	if (SessionSearch.IsValid())
	{
		SessionSearch->MaxSearchResults = 100;
		SessionSearch->QuerySettings.Set(SEARCH_PRESENCE, true, EOnlineComparisonOp::Equals);
		WG_TEXT("Starting Find Session");
		SessionInterface->FindSessions(0, SessionSearch.ToSharedRef());
	}
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

void UVRGameInstance::OnFindSessionComplete(bool Success)
{
	if (Success && SessionSearch.IsValid())
	{
		WG_TEXT("Finished Find Session");
		TArray<FServerData> ServerNames;
		for (const FOnlineSessionSearchResult& SearchResult : SessionSearch->SearchResults)
		{
			WG_STRING(*SearchResult.GetSessionIdStr());
			FServerData Data;
			Data.Name = SearchResult.GetSessionIdStr();
			Data.MaxPlayers = SearchResult.Session.SessionSettings.NumPublicConnections;
			Data.CurrentPlayers = Data.MaxPlayers - SearchResult.Session.NumOpenPublicConnections;
			Data.HostUsername = SearchResult.Session.OwningUserName;
			FString ServerName;
			if (SearchResult.Session.SessionSettings.Get(TEXT("ServerName"), ServerName))
			{
				Data.Name = ServerName;
			}
			else
			{
				Data.Name = TEXT("Could not find server name.");
			}
			ServerNames.Add(Data);
		}

		//Menu->SetServerList(ServerNames);
	}
}

void UVRGameInstance::OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result)
{

}
