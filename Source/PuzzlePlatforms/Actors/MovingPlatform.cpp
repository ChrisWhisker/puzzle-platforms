// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"

AMovingPlatform::AMovingPlatform()
{
	PrimaryActorTick.bCanEverTick = true;

	SetMobility(EComponentMobility::Movable);
}

void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();

	if (HasAuthority())
	{
		SetReplicates(true);
		SetReplicateMovement(true);
	}

	GlobalStartLocation = GetActorLocation();
	GlobalTargetLocation = GetTransform().TransformPosition(TargetLocation);

	RunningTime = FMath::FRandRange(0, HoverHeight); // Allows for distribution of platforms' height
}

void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// sine of the times
	const float DeltaHeight = FMath::Sin(RunningTime + DeltaTime) - FMath::Sin(RunningTime);
	FVector Location = GetActorLocation();

	if (CharactersOnTrigger >= RequiredCharacters)
	{
		if (HasAuthority())
		{
			const float JourneyLength = (GlobalTargetLocation - GlobalStartLocation).Size();
			const float JourneyTraveled = (Location - GlobalStartLocation).Size();

			if (JourneyTraveled >= JourneyLength)
			{
				const FVector Swap = GlobalStartLocation;
				GlobalStartLocation = GlobalTargetLocation;
				GlobalTargetLocation = Swap;
			}
			const FVector Direction = (GlobalTargetLocation - GlobalStartLocation).GetSafeNormal();
			Location += Speed * DeltaTime * Direction;
		}
	}

	Location.Z += DeltaHeight * HoverHeight;
	SetActorLocation(Location);
	RunningTime += DeltaTime;
}

void AMovingPlatform::AddCharacterOnTrigger()
{
	CharactersOnTrigger++;
}

void AMovingPlatform::RemoveCharacterOnTrigger()
{
	if (CharactersOnTrigger > 0)
	{
		CharactersOnTrigger--;
	}
}
