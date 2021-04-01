// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Components/InputComponent.h"
#include "Camera/CameraComponent.h"
#include "CollisionQueryParams.h"
#include "CharacterPawn.generated.h"

UCLASS()
class FLOORISLAVA_API ACharacterPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ACharacterPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void MoveForward(float axisValue);
	void MoveRight(float axisValue);
	void Shoot();

	UPROPERTY(EditAnywhere, Category = "My speed value")
		float speed = 500.0f;
	FVector mMovementInput;
	UCameraComponent* mCamera;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
