// Fill out your copyright notice in the Description page of Project Settings.


#include "InGameMenu.h"
#include "Components/Button.h"

bool UInGameMenu::Initialize()
{
	const bool SuperSuccess = Super::Initialize();
	if (!SuperSuccess) { return false; }

	if (!CancelButton) { return false; }
	CancelButton->OnClicked.AddDynamic(this, &UInGameMenu::CancelPressed);

	if (!QuitButton) { return false; }
	QuitButton->OnClicked.AddDynamic(this, &UInGameMenu::QuitPressed);

	return true;
}

void UInGameMenu::CancelPressed()
{
	Hide();
}

void UInGameMenu::QuitPressed()
{
	if (MenuInterface != nullptr)
	{
		Hide();
		MenuInterface->LoadMainMenuMap();
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("MenuInterface not found."));
	}
}
