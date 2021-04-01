// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "Engine/World.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "FloorIsLavaCharacter.h"
#include "timedMovingActor.generated.h"

UCLASS()
class FLOORISLAVA_API AtimedMovingActor :public AActor
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* VisibleComponent;

	UPROPERTY(EditAnywhere)
		float TravelDistance;

	UPROPERTY(EditAnywhere)
		float Speed;

	UPROPERTY(EditAnywhere)
		float Tolerance;

	//interval of movement triggered
	UPROPERTY(EditAnywhere)
		float Interval;

	FVector StartingPosition;

	float Direction;
	float startSecond;
	float currentSecond;
	bool actionStarted;
	
public:	
	// Sets default values for this actor's properties
	AtimedMovingActor();
	bool startAction;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
