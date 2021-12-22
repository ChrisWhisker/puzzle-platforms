// Fill out your copyright notice in the Description page of Project Settings.


#include "PauseMenu.h"
#include "Components/Button.h"

bool UPauseMenu::Initialize()
{
	const bool SuperSuccess = Super::Initialize();
	if (!SuperSuccess) { return false; }

	if (!CancelButton) { return false; }
	CancelButton->OnClicked.AddDynamic(this, &UPauseMenu::CloseMenu);

	if (!QuitButton) { return false; }
	QuitButton->OnClicked.AddDynamic(this, &UPauseMenu::OpenMainMenuMap);

	return true;
}

void UPauseMenu::CloseMenu()
{
}

void UPauseMenu::OpenMainMenuMap()
{
}
