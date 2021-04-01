// Fill out your copyright notice in the Description page of Project Settings.


#include "RotatingActor.h"

// Sets default values
ARotatingActor::ARotatingActor()
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
}

// Called when the game starts or when spawned
void ARotatingActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARotatingActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//rotator(pitch,yaw,roll)
	FRotator Rotator(0, RotationSpeed * DeltaTime, 0);
	FQuat RotationQuaternion(Rotator);

	AddActorLocalRotation(RotationQuaternion, false, nullptr, ETeleportType::None);
}

