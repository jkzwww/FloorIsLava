// Fill out your copyright notice in the Description page of Project Settings.


#include "ChasingCones.h"

// Sets default values
AChasingCones::AChasingCones()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
	VisibleComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Visible Component"));
	VisibleComponent->SetupAttachment(RootComponent);

	ConstructorHelpers::FObjectFinder<UStaticMesh> ConeMeshObject(TEXT("/Game/StarterContent/Shapes/Shape_Cone.Shape_Cone"));

	if (ConeMeshObject.Succeeded())
	{
		VisibleComponent->SetStaticMesh(ConeMeshObject.Object);
	}

	Speed = 200;
	MinimumDistance = 80;
	startChase = false;
}

// Called when the game starts or when spawned
void AChasingCones::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AChasingCones::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	//target exists and scannerblock triggered
	if (FollowTarget && startChase)
	{

		//moving direction
		FVector TargetDirection = FollowTarget->GetActorLocation() - GetActorLocation();
		
		//forward vector
		FVector Forward = FVector(1, 0, 0);

		//up vector
		FVector Up = FVector(0, 0, 1);

		//rotate direction
		FVector RotateDirection = TargetDirection;
		RotateDirection.Z = 0;
		RotateDirection.Normalize();

		//actor direction
		FVector actorFront = FollowTarget->GetActorForwardVector();

		if (TargetDirection.Size() > MinimumDistance)
		{
			TargetDirection.Normalize();

			//get pitch degree
			float Dot = FVector::DotProduct(Up, actorFront);
			float Det = Up.X * actorFront.Y + Up.Y * actorFront.X;
			float Rad = FMath::Atan2(Det, Dot);
			float Degrees = FMath::RadiansToDegrees(Rad);

			//get yaw degree
			float Dot2 = FVector::DotProduct(Forward, RotateDirection);
			float Det2 = Forward.X * RotateDirection.Y + Forward.Y * RotateDirection.X;
			float Rad2 = FMath::Atan2(Det2, Dot2);
			float Degrees2 = FMath::RadiansToDegrees(Rad2);


			FRotator Rotator(Degrees-90, Degrees2, 0);
			FQuat RotationQuaternion = FQuat(Rotator);
			SetActorRotation(RotationQuaternion);

			SetActorLocation(GetActorLocation() + TargetDirection * Speed * DeltaTime);
		}
		else if (TargetDirection.Size() <= MinimumDistance) //if player is touched
		{
			//end game
			FollowTarget->GameOver(1);
		}
	}
	
}

