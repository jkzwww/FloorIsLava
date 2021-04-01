// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/World.h"
#include "Math/UnrealMathUtility.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ShootableActor.generated.h"

UCLASS()
class FLOORISLAVA_API AShootableActor : public AActor
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

	FVector InitialPosition;
	int index; //for deciding left right
	float JumpHeight;
	float GroundHeight;
	float beginHeight;

public:	
	// Sets default values for this actor's properties
	AShootableActor();

	void OnBulletHit();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	UPROPERTY(EditAnywhere);
	UStaticMeshComponent* mVisibleComponent;
};
