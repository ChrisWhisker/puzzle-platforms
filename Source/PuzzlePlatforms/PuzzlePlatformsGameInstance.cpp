// Fill out your copyright notice in the Description page of Project Settings.


#include "PuzzlePlatformsGameInstance.h"
#include "Blueprint/UserWidget.h"
#include "Menu/MainMenu.h"

UPuzzlePlatformsGameInstance::UPuzzlePlatformsGameInstance()
{
	const ConstructorHelpers::FClassFinder<UUserWidget> MenuBPClass(
		TEXT("/Game/PuzzlePlatforms/Menu/WBP_MainMenu"));

	MenuClass = MenuBPClass.Class;
}

void UPuzzlePlatformsGameInstance::Init()
{
	Super::Init();
}

void UPuzzlePlatformsGameInstance::LoadMenu()
{
	if (MenuClass)
	{
		Menu = CreateWidget<UMainMenu>(this, MenuClass);
		if (!Menu) { return; }
		Menu->Setup();
		Menu->SetMenuInterface(this);
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
