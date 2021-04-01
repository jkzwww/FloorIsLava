// Fill out your copyright notice in the Description page of Project Settings.


#include "chasingActor.h"

// Sets default values
AchasingActor::AchasingActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
	VisibleComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Visible Component"));
	VisibleComponent->SetupAttachment(RootComponent);

	ConstructorHelpers::FObjectFinder<UStaticMesh> SphereMeshObject(TEXT("/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere"));

	if (SphereMeshObject.Succeeded())
	{
		VisibleComponent->SetStaticMesh(SphereMeshObject.Object);
	}

	Speed = 200;
	MinimumDistance = 80;
	startChase = false;
}

// Called when the game starts or when spawned
void AchasingActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AchasingActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//target exists and scannerblock triggered
	if (FollowTarget && startChase)
	{
		FVector TargetDirection = FollowTarget->GetActorLocation() - GetActorLocation();

		//approach player if distance in between is too far
		if (TargetDirection.Size() > MinimumDistance)
		{
			TargetDirection.Normalize();

			SetActorLocation(GetActorLocation() + TargetDirection * Speed * DeltaTime);
		}
		else if (TargetDirection.Size() <= MinimumDistance) //if player is touched
		{
			//end game
			FollowTarget->GameOver(1);
		}
	}
}

