// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "RotatingActor.generated.h"

UCLASS()
class FLOORISLAVA_API ARotatingActor : public AActor
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere)
		float RotationSpeed;

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* VisibleComponent;
public:	
	// Sets default values for this actor's properties
	ARotatingActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
