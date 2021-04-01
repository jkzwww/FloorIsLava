// Fill out your copyright notice in the Description page of Project Settings.


#include "OrbitActor.h"

// Sets default values
AOrbitActor::AOrbitActor()
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

	RotationSpeed = 20;
	RotationDegrees = 0;

	//default
	OrbitLocation = FVector(0, 0, 0);
}

// Called when the game starts or when spawned
void AOrbitActor::BeginPlay()
{
	Super::BeginPlay();
	
	OrbitLocation.Z = GetActorLocation().Z;
	RotationRadius = GetActorLocation() - OrbitLocation;
	RotationRadius.Z = 0;

	RotationRadius.Normalize();
	RotationRadius *= OrbitRadius;
}

// Called every frame
void AOrbitActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (OrbitTarget)
	{
		OrbitLocation = OrbitTarget->GetActorLocation();
		OrbitLocation.Z = GetActorLocation().Z;
	}

	RotationDegrees += RotationSpeed * DeltaTime;

	if (RotationDegrees >= 360)
	{
		RotationDegrees -= 360;
	}

	//rotated vector using degree(angle) and world forward actor(axis)
	FVector RotateValue = RotationRadius.RotateAngleAxis(RotationDegrees, FVector(0, 0, 1));
	FVector NewPosition = OrbitLocation + RotateValue;
	SetActorLocation(NewPosition);

	FVector TargetDirection = OrbitLocation - GetActorLocation();
	TargetDirection.Z = 0; //rotate horizontally only
	TargetDirection.Normalize();

	FVector Forward = FVector(1, 0, 0);

	float Dot = FVector::DotProduct(Forward, TargetDirection);
	//determinant
	float Det = Forward.X * TargetDirection.Y + Forward.Y * TargetDirection.X;
	float RotRadians = FMath::Atan2(Det, Dot);
	float RotDegree = FMath::RadiansToDegrees(RotRadians);

	FRotator Rotator = FRotator(0, RotDegree, 0);
	FQuat RotationQuaternion = FQuat(Rotator);
	SetActorRotation(RotationQuaternion);
	
}

