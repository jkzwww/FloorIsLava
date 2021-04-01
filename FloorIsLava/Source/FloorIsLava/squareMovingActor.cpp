// Fill out your copyright notice in the Description page of Project Settings.


#include "squareMovingActor.h"


// Sets default values
AsquareMovingActor::AsquareMovingActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
	VisibleComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Visible Component"));
	VisibleComponent->SetupAttachment(RootComponent);

	ConstructorHelpers::FObjectFinder<UStaticMesh> CubeMeshObject(TEXT("/Game/Geometry/Meshes/1M_Cube.1M_Cube"));

	if (CubeMeshObject.Succeeded())
	{
		VisibleComponent->SetStaticMesh(CubeMeshObject.Object);
	}

	//default values
	TravelDistance = 500;
	Speed = 200;
	Tolerance = 10;
	currentSide = 0;
	InitialDirection = 1;
}

// Called when the game starts or when spawned
void AsquareMovingActor::BeginPlay()
{
	Super::BeginPlay();
	
	Direction = InitialDirection;
	StartingPosition = GetActorLocation();

	//start from bottom left
	squareSides[0] = GetActorForwardVector();
	squareSides[1] = GetActorRightVector();
	squareSides[2] = -squareSides[0];
	squareSides[3] = -squareSides[1];
	
}

// Called every frame
void AsquareMovingActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector DirectionVector = squareSides[currentSide] * Direction;
	FVector CurrentPosition = GetActorLocation();


	FVector TargetPosition = StartingPosition + (DirectionVector * TravelDistance);

	CurrentPosition += DirectionVector * Speed * DeltaTime;

	if (FVector::Dist(CurrentPosition, TargetPosition) <= Tolerance)
	{
		CurrentPosition = TargetPosition;
		StartingPosition = CurrentPosition;

		currentSide++;

		if (currentSide == 4)
		{
			currentSide = 0;
		}
	}

	SetActorLocation(CurrentPosition);
}

