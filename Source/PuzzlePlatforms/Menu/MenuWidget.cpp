// Fill out your copyright notice in the Description page of Project Settings.


#include "MenuWidget.h"

void UMenuWidget::Setup()
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

void UMenuWidget::Hide()
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

void UMenuWidget::SetMenuInterface(IMenuInterface* Interface)
{
	MenuInterface = Interface;
}
