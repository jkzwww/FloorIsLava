// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "squareMovingActor.generated.h"

UCLASS()
class FLOORISLAVA_API AsquareMovingActor : public AActor
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere)
		float TravelDistance;

	UPROPERTY(EditAnywhere)
		float Speed;

	UPROPERTY(EditAnywhere)
		float Tolerance;

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* VisibleComponent;

	UPROPERTY(EditAnywhere)
		float InitialDirection;

	FVector StartingPosition;

	//current side of the square path
	int currentSide;

	float Direction;
	
	//array to store vector paths of square
	FVector squareSides[4];

public:	
	// Sets default values for this actor's properties
	AsquareMovingActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
