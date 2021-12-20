// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "MovingPlatform.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEPLATFORMS_API AMovingPlatform : public AStaticMeshActor
{
	GENERATED_BODY()

public:
	////////// FUNCTIONS //////////
	AMovingPlatform();

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	void AddCharacterOnTrigger();

	void RemoveCharacterOnTrigger();

private:
	////////// PROPERTIES //////////
	UPROPERTY(Category = Activation, VisibleAnywhere)
	int CharactersOnTrigger = 0;

	UPROPERTY(Category = Activation, EditAnywhere)
	int RequiredCharacters = 0;

	UPROPERTY(Category = Movement, EditAnywhere)
	float Speed = 100;

	UPROPERTY(Category = Movement, VisibleAnywhere)
	FVector GlobalStartLocation;

	UPROPERTY(Category = Movement, VisibleAnywhere)
	FVector GlobalTargetLocation;

	UPROPERTY(Category = Movement, EditAnywhere, Meta = (MakeEditWidget = true))
	FVector TargetLocation;

	// Set to 0 if platform shouldn't hover.
	UPROPERTY(Category = Movement, EditAnywhere)
	float HoverHeight = 10.f;

	float RunningTime = 0.f;
};
