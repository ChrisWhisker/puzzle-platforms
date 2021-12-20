// Fill out your copyright notice in the Description page of Project Settings.


#include "PuzzlePlatformsGameInstance.h"

#include "Blueprint/UserWidget.h"


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
		UUserWidget* Menu = CreateWidget<UUserWidget>(this, MenuClass);
		if (!Menu) { return; }
		Menu->AddToViewport();
		
		APlayerController* Controller = GetFirstLocalPlayerController();
		if (!Controller) { return; }
		
		FInputModeUIOnly InputModeData;
		InputModeData.SetWidgetToFocus(Menu->TakeWidget());
		InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::LockInFullscreen);
		Controller->SetInputMode(InputModeData);
		Controller->bShowMouseCursor = true;
	}
}

void UPuzzlePlatformsGameInstance::Host()
{
	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Hosting..."));

	UWorld* World = GetWorld();
	if (World)
		World->ServerTravel("/Game/PuzzlePlatforms/Maps/ThirdPersonExampleMap?listen");
}

void UPuzzlePlatformsGameInstance::Join(const FString& Address)
{
	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Joining %s"), *Address));

	APlayerController* Controller = GetFirstLocalPlayerController();
	if (Controller)
	{
		Controller->ClientTravel(Address, ETravelType::TRAVEL_Absolute);
	}
}
