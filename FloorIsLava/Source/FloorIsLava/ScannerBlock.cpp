// Fill out your copyright notice in the Description page of Project Settings.


#include "ScannerBlock.h"


// Sets default values
AScannerBlock::AScannerBlock()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
	VisibleComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Visible Component"));
	VisibleComponent->SetupAttachment(RootComponent);

	OnMaterial = CreateDefaultSubobject<UMaterial>(TEXT("On Material"));
	OffMaterial = CreateDefaultSubobject<UMaterial>(TEXT("Off Material"));

	ConstructorHelpers::FObjectFinder<UStaticMesh> CubeMeshObject(TEXT("/Game/Geometry/Meshes/1M_Cube.1M_Cube"));
	ConstructorHelpers::FObjectFinder<UMaterial> OnMaterialObject(TEXT("/Game/StarterContent/Materials/M_Tech_Hex_Tile_Pulse.M_Tech_Hex_Tile_Pulse"));
	ConstructorHelpers::FObjectFinder<UMaterial> OffMaterialObject(TEXT("/Game/StarterContent/Materials/M_Tech_Hex_Tile.M_Tech_Hex_Tile"));


	if (CubeMeshObject.Succeeded())
	{
		VisibleComponent->SetStaticMesh(CubeMeshObject.Object);
	}

	if (OnMaterialObject.Succeeded())
	{
		OnMaterial = OnMaterialObject.Object;
	}

	if (OffMaterialObject.Succeeded())
	{
		OffMaterial = OffMaterialObject.Object;
	}

	MaxDistance = 500;
}

// Called when the game starts or when spawned
void AScannerBlock::BeginPlay()
{
	Super::BeginPlay();
	
	VisibleComponent->SetMaterial(0, OffMaterial);
}

// Called every frame
void AScannerBlock::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//check if target is selected
	if (Target)
	{

		FVector TargetDirection = Target->GetActorLocation() - GetActorLocation();


		if (TargetDirection.Size() <= MaxDistance)
		{
			TargetDirection.Normalize();
			float DotProduct = FVector::DotProduct(GetActorForwardVector(), TargetDirection);


			if (DotProduct > 0.9) //only light up when character is in front
			{
				VisibleComponent->SetMaterial(0, OnMaterial);
				//UE_LOG(LogTemp, Warning, TEXT("detected"));
				
				//character detected, trigger actors
				if (targetPlatform)
				{
					targetPlatform->startAction = true;
				}
				
				if (chasingActors.Num() != 0)
				{
					for (int i = 0; i < chasingActors.Num(); i++)
					{
						chasingActors[i]->FollowTarget = Target;
						chasingActors[i]->startChase = true;
					}
				}

				if (chasingCones.Num() != 0)
				{
					for (int i = 0; i < chasingCones.Num(); i++)
					{
						chasingCones[i]->FollowTarget = Target;
						chasingCones[i]->startChase = true;
					}
				}
			}
			else
			{
				VisibleComponent->SetMaterial(0, OffMaterial);
				
				if (targetPlatform)
				{
					//stop target platform action as target not in front of scanner
					targetPlatform->startAction = false;
				}
			}
		}
		else
		{
			//prevent material not turning off if target goes straight and out of distance
			VisibleComponent->SetMaterial(0, OffMaterial);
		}

	}

}

