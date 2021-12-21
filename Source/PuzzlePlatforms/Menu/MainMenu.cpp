// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenu.h"
#include "Components/Button.h"
#include "Components/EditableTextBox.h"
#include "Components/Widget.h"
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

void UMainMenu::SetMenuInterface(IMenuInterface* Interface)
{
	MenuInterface = Interface;
}

void UMainMenu::Setup()
{
	AddToViewport();

	UWorld* World = GetWorld();
	if (World == nullptr) { return; }
	APlayerController* Controller = World->GetFirstPlayerController();
	if (!Controller) { return; }

	bIsFocusable = true;
	FInputModeUIOnly InputModeData;
	InputModeData.SetWidgetToFocus(TakeWidget());
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::LockInFullscreen);
	Controller->SetInputMode(InputModeData);
	Controller->bShowMouseCursor = true;
}

void UMainMenu::Hide()
{
	UWorld* World = GetWorld();
	if (World == nullptr) { return; }
	APlayerController* Controller = World->GetFirstPlayerController();
	if (!Controller) { return; }

	bIsFocusable = false;
	const FInputModeGameOnly InputModeData;
	Controller->SetInputMode(InputModeData);
	Controller->bShowMouseCursor = false;
	RemoveFromViewport();
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
		// try
		// {
		Hide();
		MenuInterface->Join(Address);
		// }
		// catch (const std::exception& e)
		// {
		// 	UE_LOG(LogTemp, Error, TEXT("%s"), e);
		// 	UE_LOG(LogTemp, Error, TEXT("[%s] is not a valid IP address."), *Address);
		// }
	}
}
