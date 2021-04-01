// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "MovingOrbitActor.generated.h"

UCLASS()
class FLOORISLAVA_API AMovingOrbitActor : public AActor
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere)
		float RotationSpeed;

	FVector OrbitLocation;

	UPROPERTY(EditAnywhere)
		AActor* OrbitTarget;

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* VisibleComponent;

	UPROPERTY(EditAnywhere)
		float MinimumDistance;
public:	
	// Sets default values for this actor's properties
	AMovingOrbitActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	float RotationDegrees;
	FVector RotationRadius;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
