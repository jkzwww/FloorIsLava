// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "zigZagActor.generated.h"

UCLASS()
class FLOORISLAVA_API AzigZagActor : public AActor
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere)
		float TravelDistance;

	UPROPERTY(EditAnywhere)
		float Speed;

	UPROPERTY(EditAnywhere)
		float Direction;

	UPROPERTY(EditAnywhere)
		float Tolerance;

	UPROPERTY(EditAnywhere)
		float Range;

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* VisibleComponent;

	FVector StartingPosition;
	FVector InitialPosition;
	
	//index to choose between which diagonal part of zigzag
	int ZigZagChoice;

public:	
	// Sets default values for this actor's properties
	AzigZagActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
