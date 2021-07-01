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

protected:
	////////// FUNCTIONS //////////
	UPROPERTY(Category = "Movement", EditAnywhere)
	float Speed = 100;

	UPROPERTY(Category = "Movement", VisibleAnywhere)
	FVector GlobalStartLocation;

	UPROPERTY(Category = "Movement", VisibleAnywhere)
	FVector GlobalTargetLocation;
	
	UPROPERTY(Category = "Movement", EditAnywhere, Meta = (MakeEditWidget = true))
	FVector TargetLocation;
};
