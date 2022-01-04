// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenu.h"

#include "ServerRow.h"
#include "Components/Button.h"
#include "Components/EditableTextBox.h"
#include "Components/TextBlock.h"
#include "Components/WidgetSwitcher.h"
#include "PuzzlePlatforms/PuzzlePlatformsGameInstance.h"

UMainMenu::UMainMenu(const FObjectInitializer& ObjectInitializer)
{
	const ConstructorHelpers::FClassFinder<UUserWidget> ServerRowBPClass(
		TEXT("/Game/PuzzlePlatforms/Menu/WBP_ServerRow"));
	ServerRowClass = ServerRowBPClass.Class;
}

bool UMainMenu::Initialize()
{
	const bool SuperSuccess = Super::Initialize();
	if (!SuperSuccess) { return false; }

	if (!HostButton) { return false; }
	HostButton->OnClicked.AddDynamic(this, &UMainMenu::HostServer);

	if (!JoinMenuButton) { return false; }
	JoinMenuButton->OnClicked.AddDynamic(this, &UMainMenu::OpenJoinMenu);

	if (!CancelButton) { return false; }
	CancelButton->OnClicked.AddDynamic(this, &UMainMenu::OpenMainMenu);

	if (!JoinGameButton) { return false; }
	JoinGameButton->OnClicked.AddDynamic(this, &UMainMenu::JoinServer);

	if (!QuitGameButton) { return false; }
	QuitGameButton->OnClicked.AddDynamic(this, &UMainMenu::QuitToDesktop);

	return true;
}

void UMainMenu::OpenJoinMenu()
{
	if (MenuSwitcher != nullptr && JoinMenu != nullptr)
	{
		MenuSwitcher->SetActiveWidget(JoinMenu);
	}

	if (MenuInterface != nullptr)
	{
		MenuInterface->RefreshServerList();
	}
}

void UMainMenu::OpenMainMenu()
{
	// if (IPAddressBox != nullptr)
	// {
	// 	IPAddressBox->SetText(FText());
	// }

	if (MenuSwitcher != nullptr && MainMenu != nullptr)
	{
		MenuSwitcher->SetActiveWidget(MainMenu);
	}
}

void UMainMenu::HostServer()
{
	if (MenuInterface != nullptr)
	{
		Hide();
		MenuInterface->Host();
	}
}

void UMainMenu::SetServerList(TArray<FString> ServerNames)
{
	UWorld* World = GetWorld();
	if (World == nullptr) { return; }

	ServerList->ClearChildren();
	uint32 i = 0;

	for (const FString& ServerName : ServerNames)
	{
		UServerRow* ServerRow = CreateWidget<UServerRow>(World, ServerRowClass);
		if (ServerRow == nullptr) { return; }

		ServerRow->ServerName->SetText(FText::FromString(ServerName));
		ServerRow->Setup(this, i);
		++i;
		ServerList->AddChild(ServerRow);
	}
}

void UMainMenu::SelectIndex(uint32 Index)
{
	SelectedIndex = Index;
}

void UMainMenu::JoinServer()
{
	if (SelectedIndex.IsSet())
	{
		UE_LOG(LogTemp, Warning, TEXT("Selected index is %d"), SelectedIndex.GetValue());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Selected index is not set"));
	}

	if (MenuInterface != nullptr)
	{
		// FString& Address =
		MenuInterface->Join("");
	}


	// if (IPAddressBox == nullptr) { return; }
	// const FString Address = IPAddressBox->GetText().ToString();
	//
	// if (MenuInterface != nullptr)
	// {
	// 	Hide();
	// 	MenuInterface->Join(Address);
	// }
}

void UMainMenu::QuitToDesktop()
{
	GetOwningPlayer()->ConsoleCommand("Quit");
}
