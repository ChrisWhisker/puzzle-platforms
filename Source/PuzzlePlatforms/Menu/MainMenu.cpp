// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenu.h"
#include "Components/Button.h"
#include "Components/EditableTextBox.h"
#include "Components/WidgetSwitcher.h"
#include "PuzzlePlatforms/PuzzlePlatformsGameInstance.h"

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
	JoinGameButton->OnClicked.AddDynamic(this, &UMainMenu::JoinGame);

	return true;
}

void UMainMenu::OpenJoinMenu()
{
	if (MenuSwitcher != nullptr && JoinMenu != nullptr)
	{
		MenuSwitcher->SetActiveWidget(JoinMenu);
	}
}

void UMainMenu::OpenMainMenu()
{
	if (IPAddressBox != nullptr)
	{
		IPAddressBox->SetText(FText());
	}

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

void UMainMenu::JoinGame()
{
	if (IPAddressBox == nullptr) { return; }
	const FString Address = IPAddressBox->GetText().ToString();

	if (MenuInterface != nullptr)
	{
		Hide();
		MenuInterface->Join(Address);
	}
}
