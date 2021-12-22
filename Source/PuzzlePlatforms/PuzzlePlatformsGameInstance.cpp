// Fill out your copyright notice in the Description page of Project Settings.


#include "PuzzlePlatformsGameInstance.h"
#include "Blueprint/UserWidget.h"
#include "Menu/MainMenu.h"
#include "Menu/MenuWidget.h"
#include "Menu/InGameMenu.h"

UPuzzlePlatformsGameInstance::UPuzzlePlatformsGameInstance()
{
	const ConstructorHelpers::FClassFinder<UUserWidget> MenuBPClass(
		TEXT("/Game/PuzzlePlatforms/Menu/WBP_MainMenu"));
	MainMenuClass = MenuBPClass.Class;

	const ConstructorHelpers::FClassFinder<UUserWidget> InGameMenuBPClass(
		TEXT("/Game/PuzzlePlatforms/Menu/WBP_InGameMenu"));
	InGameMenuClass = InGameMenuBPClass.Class;
}

void UPuzzlePlatformsGameInstance::Init()
{
	Super::Init();
}

void UPuzzlePlatformsGameInstance::LoadMenu()
{
	if (MainMenuClass)
	{
		Menu = CreateWidget<UMainMenu>(this, MainMenuClass);
		if (!Menu) { return; }
		Menu->Setup();
		Menu->SetMenuInterface(this);
	}
}

void UPuzzlePlatformsGameInstance::LoadInGameMenu()
{
	if (InGameMenuClass)
	{
		UInGameMenu* InGameMenu = CreateWidget<UInGameMenu>(this, InGameMenuClass);
		if (!InGameMenu) { return; }
		InGameMenu->Setup();
		InGameMenu->SetMenuInterface(this);
	}
}

void UPuzzlePlatformsGameInstance::Host()
{
	UWorld* World = GetWorld();
	if (World)
		World->ServerTravel("/Game/PuzzlePlatforms/Maps/ThirdPersonExampleMap?listen");
}

void UPuzzlePlatformsGameInstance::Join(const FString& Address)
{
	APlayerController* Controller = GetFirstLocalPlayerController();
	if (Controller)
	{
		Controller->ClientTravel(Address, ETravelType::TRAVEL_Absolute);
	}
}
