// Fill out your copyright notice in the Description page of Project Settings.


#include "InGameMenu.h"
#include "Components/Button.h"

bool UInGameMenu::Initialize()
{
	const bool SuperSuccess = Super::Initialize();
	if (!SuperSuccess) { return false; }

	if (!CancelButton) { return false; }
	CancelButton->OnClicked.AddDynamic(this, &UInGameMenu::CloseMenu);

	if (!QuitButton) { return false; }
	QuitButton->OnClicked.AddDynamic(this, &UInGameMenu::OpenMainMenuMap);

	return true;
}

void UInGameMenu::CloseMenu()
{
}

void UInGameMenu::OpenMainMenuMap()
{
}
