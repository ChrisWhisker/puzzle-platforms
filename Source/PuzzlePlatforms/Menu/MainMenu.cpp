// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenu.h"
#include "Components/Button.h"
#include "PuzzlePlatforms/PuzzlePlatformsGameInstance.h"

bool UMainMenu::Initialize()
{
	const bool SuperSuccess = Super::Initialize();
	if (!SuperSuccess) { return false; }

	if (!HostButton) { return false; }
	HostButton->OnClicked.AddDynamic(this, &UMainMenu::HostServer);

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

void UMainMenu::HostServer()
{
	if (MenuInterface != nullptr)
	{
		MenuInterface->Host();
	}
}
