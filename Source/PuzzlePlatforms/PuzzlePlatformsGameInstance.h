// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "Menu/MenuInterface.h"
#include "PuzzlePlatformsGameInstance.generated.h"

UCLASS()
class PUZZLEPLATFORMS_API UPuzzlePlatformsGameInstance : public UGameInstance, public IMenuInterface
{
	GENERATED_BODY()

public:
	UPuzzlePlatformsGameInstance();

	virtual void Init() override;

	UFUNCTION(Exec, BlueprintCallable)
	void LoadMainMenu();

	UFUNCTION(Exec, BlueprintCallable)
	void LoadInGameMenu();

	UFUNCTION(Exec)
	virtual void Host() override;

	UFUNCTION(Exec)
	virtual void Join(uint32 Index) override;

	virtual void LoadMainMenuMap() override;

	virtual void RefreshServerList() override;

private:
	TSubclassOf<class UUserWidget> MainMenuClass;

	TSubclassOf<class UUserWidget> InGameMenuClass;

	UPROPERTY()
	class UMainMenu* MainMenu;

	TSharedPtr<class FOnlineSessionSearch> SessionSearch;

	IOnlineSessionPtr SessionInterface;

	void OnCreateSessionComplete(FName SessionName, bool bSuccess);

	void OnDestroySessionComplete(FName SessionName, bool bSuccess) const;

	void OnFindSessionsComplete(const bool bSuccess) const;

	void OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result);

	void CreateSession() const;
};
