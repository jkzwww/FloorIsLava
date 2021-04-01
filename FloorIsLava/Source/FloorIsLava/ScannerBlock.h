// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Materials/Material.h"
#include "timedMovingActor.h"
#include "chasingActor.h"
#include "ChasingCones.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "FloorIsLavaCharacter.h"
#include "ScannerBlock.generated.h"

UCLASS()
class FLOORISLAVA_API AScannerBlock : public AActor
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* VisibleComponent;

	UPROPERTY(EditAnywhere)
		UMaterial* OnMaterial;

	UPROPERTY(EditAnywhere)
		UMaterial* OffMaterial;

	UPROPERTY(EditAnywhere)
		AFloorIsLavaCharacter* Target;

	//distance till character is detected
	UPROPERTY(EditAnywhere)
		float MaxDistance;

	//platform and chasing actors that is triggered through scanner block

	UPROPERTY(EditAnywhere)
		AtimedMovingActor* targetPlatform;

	UPROPERTY(EditAnywhere)
		TArray<AchasingActor*> chasingActors;

	UPROPERTY(EditAnywhere)
		TArray<AChasingCones*> chasingCones;
public:	
	// Sets default values for this actor's properties
	AScannerBlock();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


};
