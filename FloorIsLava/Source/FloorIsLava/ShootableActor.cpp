// Fill out your copyright notice in the Description page of Project Settings.


#include "ShootableActor.h"

// Sets default values
AShootableActor::AShootableActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	mVisibleComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VisibleComponent"));
	mVisibleComponent->SetupAttachment(RootComponent);

	TravelDistance = 100;
	Speed = 250;
	Tolerance = 10;
	JumpHeight = 3;
	GroundHeight = 40;
}

// Called when the game starts or when spawned
void AShootableActor::BeginPlay()
{
	Super::BeginPlay();
	
	InitialPosition = GetActorLocation();
	index = FMath::RandRange(0, 1);
	beginHeight = GetActorLocation().Z;
}

// Called every frame
void AShootableActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	//get direction to the actor side 
	FVector RightVector = GetActorRightVector();
	FVector LeftVector = RightVector * -1;
	FVector LorR[] = { LeftVector,RightVector };

	//get current position
	FVector CurrentPosition = GetActorLocation();

	//check borders
	float leftBorder = 2200;
	float rightBorder = -2200;

	if (CurrentPosition.Y < rightBorder)
	{
		index = 0; //move left back to centre
	}
	else if (CurrentPosition.Y > leftBorder)
	{
		index = 1; //move right back to center
	}

	//get directions and move
	FVector DirectionVector = LorR[index];

	FVector TargetPosition = InitialPosition + (DirectionVector * TravelDistance);

	CurrentPosition += DirectionVector * Speed * DeltaTime;

	if (FVector::Dist(CurrentPosition, TargetPosition) <= Tolerance)
	{
		CurrentPosition = TargetPosition;
		InitialPosition = CurrentPosition;

		//random left or right
		index = FMath::RandRange(0, 1);

	}

	//get world seconds
	int seconds = GetWorld()->UWorld::GetRealTimeSeconds();

	//for every 3 seconds
	if (seconds % 3 == 0)
	{
		//jump
		CurrentPosition.Z += JumpHeight;
	}
	else
	{
		//to ground
		if (CurrentPosition.Z > beginHeight)
		{
			CurrentPosition.Z -= JumpHeight;
		}
	}

	SetActorLocation(CurrentPosition);

}

void AShootableActor::OnBulletHit()
{
	Destroy();
}