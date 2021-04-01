// Fill out your copyright notice in the Description page of Project Settings.


#include "zigZagActor.h"

// Sets default values
AzigZagActor::AzigZagActor()
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

	TravelDistance = 300;
	Speed = 200;
	Tolerance = 10;
	Direction = 1;
	ZigZagChoice = 0;
	Range = 700;
}

// Called when the game starts or when spawned
void AzigZagActor::BeginPlay()
{
	Super::BeginPlay();
	
	InitialPosition = GetActorLocation();
	StartingPosition = GetActorLocation();
}

// Called every frame
void AzigZagActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	FVector forwardRight = GetActorForwardVector() + GetActorRightVector();
	FVector forwardLeft = GetActorForwardVector() - GetActorRightVector();

	FVector ZigOrZag[] = { forwardRight,forwardLeft };

	FVector CurrentPosition = GetActorLocation();

	FVector DirectionVector;
	FVector TargetPosition;

	DirectionVector = ZigOrZag[ZigZagChoice] * Direction;
	TargetPosition = StartingPosition + (DirectionVector * TravelDistance);
	CurrentPosition += DirectionVector * Speed * DeltaTime;

	if (FVector::Dist(CurrentPosition, TargetPosition) <= Tolerance)
	{
		CurrentPosition = TargetPosition;
		StartingPosition = CurrentPosition;

		//out of range , zig zag back in opp direction
		if (FVector::Dist(CurrentPosition, InitialPosition) > Range)
		{
			Direction *= -1;
		}
		else if (ZigZagChoice == 1) //change between 0 and 1 for zig zag movement
		{
			ZigZagChoice = 0;
		}
		else
		{
			ZigZagChoice++;
		}
		
	}

	SetActorLocation(CurrentPosition);

}

