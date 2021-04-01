// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/World.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Math/UnrealMathUtility.h"
#include "Containers/UnrealString.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "movingLocalActor.generated.h"

UCLASS()
class FLOORISLAVA_API AmovingLocalActor : public AActor
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

	UPROPERTY(EditAnywhere)
		float InitialDirection;

	//delay of movement from game begin
	UPROPERTY(EditAnywhere)
		float InitialDelay;

	UPROPERTY(EditAnywhere)
		bool MoveDiagonal;

	FVector StartingPosition;

	float Direction;
	float StartSecond;
	float CurrentSecond;

public:	
	// Sets default values for this actor's properties
	AmovingLocalActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
