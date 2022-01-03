// Fill out your copyright notice in the Description page of Project Settings.


#include "PuzzlePlatformsGameInstance.h"
#include "Blueprint/UserWidget.h"
#include "Menu/MainMenu.h"
#include "Menu/MenuWidget.h"
#include "OnlineSessionSettings.h"
#include "OnlineSubsystem.h"

const static FName SESSION_NAME = TEXT("My Session");

UPuzzlePlatformsGameInstance::UPuzzlePlatformsGameInstance()
{
	const ConstructorHelpers::FClassFinder<UUserWidget> MenuBPClass(TEXT("/Game/PuzzlePlatforms/Menu/WBP_MainMenu"));
	MainMenuClass = MenuBPClass.Class;

	const ConstructorHelpers::FClassFinder<UUserWidget> InGameMenuBPClass(
		TEXT("/Game/PuzzlePlatforms/Menu/WBP_InGameMenu"));
	InGameMenuClass = InGameMenuBPClass.Class;
}

void UPuzzlePlatformsGameInstance::Init()
{
	Super::Init();

	IOnlineSubsystem* Subsystem = IOnlineSubsystem::Get();

	if (Subsystem != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Subsystem found: %s"), *Subsystem->GetSubsystemName().ToString());
		SessionInterface = Subsystem->GetSessionInterface();
		if (SessionInterface.IsValid())
		{
			// Bind session delegates
			SessionInterface->OnCreateSessionCompleteDelegates.AddUObject(
				this, &UPuzzlePlatformsGameInstance::OnCreateSessionComplete);
			SessionInterface->OnDestroySessionCompleteDelegates.AddUObject(
				this, &UPuzzlePlatformsGameInstance::OnDestroySessionComplete);
			SessionInterface->OnFindSessionsCompleteDelegates.AddUObject(
				this, &UPuzzlePlatformsGameInstance::OnFindSessionsComplete);

			// Make TSharedPtr
			SessionSearch = MakeShareable(new FOnlineSessionSearch());

			if (SessionSearch.IsValid())
			{
				SessionSearch->bIsLanQuery = true;
				SessionInterface->FindSessions(0, SessionSearch.ToSharedRef());
				UE_LOG(LogTemp, Warning, TEXT("Finding sessions..."));
			}
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("IOnlineSubsystem is not found."));
	}
}

void UPuzzlePlatformsGameInstance::LoadMainMenu()
{
	if (!MainMenuClass) { return; }

	MainMenu = CreateWidget<UMainMenu>(this, MainMenuClass);
	if (!MainMenu) { return; }

	MainMenu->Setup();
	MainMenu->SetMenuInterface(this);
}

void UPuzzlePlatformsGameInstance::LoadInGameMenu()
{
	if (!InGameMenuClass) { return; }

	UMenuWidget* InGameMenu = CreateWidget<UMenuWidget>(this, InGameMenuClass);
	if (!InGameMenu) { return; }

	InGameMenu->Setup();
	InGameMenu->SetMenuInterface(this);
}

void UPuzzlePlatformsGameInstance::OnCreateSessionComplete(FName SessionName, bool bSuccess)
{
	if (!bSuccess)
	{
		UE_LOG(LogTemp, Error, TEXT("Could not create session."));
		return;
	}

	UWorld* World = GetWorld();
	if (World)
	{
		World->ServerTravel("/Game/PuzzlePlatforms/Maps/ThirdPersonExampleMap?listen");
	}
}


void UPuzzlePlatformsGameInstance::OnFindSessionsComplete(const bool bSuccess) const
{
	if (bSuccess && SessionSearch.IsValid())
	{
		UE_LOG(LogTemp, Warning, TEXT("OnFindSessionsComplete() was a success."));

		// Print all session IDs
		for (FOnlineSessionSearchResult& Result : SessionSearch->SearchResults)
		{
			UE_LOG(LogTemp, Warning, TEXT("Session found: %s"), *Result.Session.GetSessionIdStr());
		}
	}
}

void UPuzzlePlatformsGameInstance::OnDestroySessionComplete(FName SessionName, bool bSuccess) const
{
	if (bSuccess)
	{
		CreateSession();
	}
}

void UPuzzlePlatformsGameInstance::CreateSession() const
{
	if (SessionInterface.IsValid())
	{
		// Configure and create session
		FOnlineSessionSettings SessionSettings;
		SessionSettings.bIsLANMatch = true;
		SessionSettings.NumPublicConnections = 2;
		SessionSettings.bShouldAdvertise = true;
		SessionInterface->CreateSession(0, SESSION_NAME, SessionSettings);
	}
}

void UPuzzlePlatformsGameInstance::Host()
{
	if (SessionInterface.IsValid())
	{
		const FNamedOnlineSession* ExistingSession = SessionInterface->GetNamedSession(SESSION_NAME);

		if (ExistingSession != nullptr)
		{
			SessionInterface->DestroySession(SESSION_NAME);
		}
		else
		{
			CreateSession();
		}
	}
}

void UPuzzlePlatformsGameInstance::Join(const FString& Address)
{
	APlayerController* Controller = GetFirstLocalPlayerController();
	if (Controller)
	{
		Controller->ClientTravel(Address, ETravelType::TRAVEL_Absolute);
	}
}

void UPuzzlePlatformsGameInstance::LoadMainMenuMap()
{
	APlayerController* Controller = GetFirstLocalPlayerController();
	if (Controller)
	{
		Controller->ClientTravel("/Game/PuzzlePlatforms/Menu/MainMenu", ETravelType::TRAVEL_Absolute);
	}
}
