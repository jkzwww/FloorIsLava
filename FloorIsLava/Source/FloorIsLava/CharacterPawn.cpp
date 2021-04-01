// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterPawn.h"
#include "ShootableActor.h"
// Sets default values
ACharacterPawn::ACharacterPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AutoPossessPlayer = EAutoReceiveInput::Player0;
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	mCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));

	mCamera->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ACharacterPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACharacterPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	if (!mMovementInput.IsZero())
	{
		mMovementInput.Normalize();

		SetActorLocation(GetActorLocation() + (mMovementInput * speed * DeltaTime));
	}
}

// Called to bind functionality to input
void ACharacterPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveX", this, &ACharacterPawn::MoveForward);
	PlayerInputComponent->BindAxis("MoveY", this, &ACharacterPawn::MoveRight);
	PlayerInputComponent->BindAction("Shoot", IE_Pressed, this, &ACharacterPawn::Shoot);
}


void ACharacterPawn::MoveForward(float axisValue)
{
	//due to map orientation
	mMovementInput.X = -axisValue;
}


void ACharacterPawn::MoveRight(float axisValue)
{
	//due to map orientation
	mMovementInput.Y = -axisValue;
}

void ACharacterPawn::Shoot()
{
	
	// Print a message to the output log
	UE_LOG(LogTemp, Warning, TEXT("Bang"));
	// Set up a trace to see if we can hit something
	FHitResult linetraceResult;
	// Stat position of check
	FVector startTrace = GetActorLocation();
	startTrace.X += 200;
	// End position of check
	FVector endTrace = (GetActorForwardVector() * 7500.0f) + startTrace;
	FCollisionQueryParams params;
	// Attempt to check
	bool isHit = GetWorld()->LineTraceSingleByChannel(linetraceResult, startTrace, endTrace, ECC_WorldStatic, params);
	// If something was hit
	if (isHit) {
		// Attempt to cast to our shootable object
		AShootableActor* shootTarget = Cast<AShootableActor>(linetraceResult.GetActor());
		if (shootTarget) {
			// If successful case then display hit message and call OnBulletHit
			UE_LOG(LogTemp, Warning, TEXT("Hit Shoot Target"));
			shootTarget->OnBulletHit();
		}
	}
	
}