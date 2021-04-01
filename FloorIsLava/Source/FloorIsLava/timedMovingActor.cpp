// Fill out your copyright notice in the Description page of Project Settings.


#include "timedMovingActor.h"



// Sets default values
AtimedMovingActor::AtimedMovingActor()
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
	Direction = 1;
	TravelDistance = 500;
	Speed = 200;
	Tolerance = 10;
	Interval = 5;
}

// Called when the game starts or when spawned
void AtimedMovingActor::BeginPlay()
{
	Super::BeginPlay(); 
	StartingPosition = GetActorLocation();
	startAction = false;
	actionStarted = false;
}

// Called every frame
void AtimedMovingActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector DirectionVector = GetActorForwardVector() * Direction;
	FVector CurrentPosition = GetActorLocation();

	FVector TargetPosition = StartingPosition + (DirectionVector * TravelDistance);

	//if no action have been started yet, initialise startsecond when triggered
	if (!actionStarted && startAction)
	{
		startSecond = GetWorld()->UWorld::GetRealTimeSeconds();
		actionStarted = true;
		//UE_LOG(LogTemp, Warning, TEXT("Start"));
	}
	
	//after started
	if (actionStarted)
	{
		currentSecond = GetWorld()->UWorld::GetRealTimeSeconds();

		//move within the interval time
		if (currentSecond - startSecond < Interval)
		{
			CurrentPosition += DirectionVector * Speed * DeltaTime;

			if (FVector::Dist(CurrentPosition, TargetPosition) <= Tolerance)
			{
				CurrentPosition = TargetPosition;
				StartingPosition = CurrentPosition;

				Direction *= -1;
			}

			SetActorLocation(CurrentPosition);
		}
		else
		{
			//wait another interval to be able to trigger the platform again
			if (currentSecond - startSecond > Interval * 2)
			{
				actionStarted = false;
			}

		}
	}


}

