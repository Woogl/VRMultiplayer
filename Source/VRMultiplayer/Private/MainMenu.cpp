// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenu.h"
#include "ServerRow.h"
#include <UMG/Public/Components/Button.h>
#include <UMG/Public/Components/TextBlock.h>

UMainMenu::UMainMenu(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	ConstructorHelpers::FClassFinder<UUserWidget> ServerRowBPClass(TEXT("/Game/Woogle/Blueprints/UI/WBP_ServerRow"));
	if (ServerRowBPClass.Succeeded())
	{
		ServerRowClass = ServerRowBPClass.Class;
	}
}

void UMainMenu::SetServerList(TArray<FServerData> ServerNames)
{
	ServerList->ClearChildren();

	uint32 i = 0;
	for (const FServerData& ServerData : ServerNames)
	{
		UServerRow* Row = CreateWidget<UServerRow>(this, ServerRowClass);
		if (!ensure(Row != nullptr)) return;

		Row->ServerName->SetText(FText::FromString(ServerData.Name));
		Row->HostUser->SetText(FText::FromString(ServerData.HostUsername));
		FString FractionText = FString::Printf(TEXT("%d/%d"), ServerData.CurrentPlayers, ServerData.MaxPlayers);
		Row->ConnectionFraction->SetText(FText::FromString(FractionText));

		ServerList->AddChild(Row);
	}
}
