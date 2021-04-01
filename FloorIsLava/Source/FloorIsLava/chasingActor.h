// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FloorIsLavaCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "chasingActor.generated.h"

UCLASS()
class FLOORISLAVA_API AchasingActor : public AActor
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* VisibleComponent;

	UPROPERTY(EditAnywhere)
		float Speed;

	//minimum distance between it and target
	UPROPERTY(EditAnywhere)
		float MinimumDistance;

public:	
	// Sets default values for this actor's properties
	AchasingActor();

	AFloorIsLavaCharacter* FollowTarget;

	//to trigger chasing
	bool startChase;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
