// Fill out your copyright notice in the Description page of Project Settings.


#include "movingLocalActor.h"

// Sets default values
AmovingLocalActor::AmovingLocalActor()
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
	InitialDirection = 1;
	InitialDelay = 0;
	MoveDiagonal = false;
}

// Called when the game starts or when spawned
void AmovingLocalActor::BeginPlay()
{
	Super::BeginPlay();

	StartingPosition = GetActorLocation();
	Direction = InitialDirection;

	StartSecond = GetWorld()->UWorld::GetRealTimeSeconds();

}

// Called every frame
void AmovingLocalActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CurrentSecond = GetWorld()->UWorld::GetRealTimeSeconds();

	//check whether initial delay time has passed 
	if (CurrentSecond - StartSecond > InitialDelay )
	{
		FVector DirectionVector = GetActorForwardVector() * Direction;

		if (MoveDiagonal)
		{
			DirectionVector = (GetActorForwardVector() + GetActorRightVector()) *Direction;
		}

		FVector CurrentPosition = GetActorLocation();

		FVector TargetPosition = StartingPosition + (DirectionVector * TravelDistance);

		CurrentPosition += DirectionVector * Speed * DeltaTime;

		if (FVector::Dist(CurrentPosition, TargetPosition) <= Tolerance)
		{
			CurrentPosition = TargetPosition;
			StartingPosition = CurrentPosition;

			Direction *= -1;
		}

		SetActorLocation(CurrentPosition);

	}
	

}

