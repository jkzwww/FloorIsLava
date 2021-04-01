// Copyright Epic Games, Inc. All Rights Reserved.


#include "FloorIsLavaCharacter.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"

//////////////////////////////////////////////////////////////////////////
// AFloorIsLavaCharacter

AFloorIsLavaCharacter::AFloorIsLavaCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)

	//default minDistFromLava
	minDistFromLava = 98.2; //experimental value

	//set start sec to check if end game countdown have started
	startSec = 0;

	//default delay between triggering and actually quitting
	endGameDelay = 0.2;
}

//////////////////////////////////////////////////////////////////////////
// Input

void AFloorIsLavaCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAxis("MoveForward", this, &AFloorIsLavaCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AFloorIsLavaCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &AFloorIsLavaCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AFloorIsLavaCharacter::LookUpAtRate);

	// handle touch devices
	PlayerInputComponent->BindTouch(IE_Pressed, this, &AFloorIsLavaCharacter::TouchStarted);
	PlayerInputComponent->BindTouch(IE_Released, this, &AFloorIsLavaCharacter::TouchStopped);

	// VR headset functionality
	PlayerInputComponent->BindAction("ResetVR", IE_Pressed, this, &AFloorIsLavaCharacter::OnResetVR);
}


void AFloorIsLavaCharacter::OnResetVR()
{
	// If FloorIsLava is added to a project via 'Add Feature' in the Unreal Editor the dependency on HeadMountedDisplay in FloorIsLava.Build.cs is not automatically propagated
	// and a linker error will result.
	// You will need to either:
	//		Add "HeadMountedDisplay" to [YourProject].Build.cs PublicDependencyModuleNames in order to build successfully (appropriate if supporting VR).
	// or:
	//		Comment or delete the call to ResetOrientationAndPosition below (appropriate if not supporting VR)
	UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();
}

void AFloorIsLavaCharacter::TouchStarted(ETouchIndex::Type FingerIndex, FVector Location)
{
		Jump();
}

void AFloorIsLavaCharacter::TouchStopped(ETouchIndex::Type FingerIndex, FVector Location)
{
		StopJumping();
}

void AFloorIsLavaCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AFloorIsLavaCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void AFloorIsLavaCharacter::MoveForward(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void AFloorIsLavaCharacter::MoveRight(float Value)
{
	if ( (Controller != nullptr) && (Value != 0.0f) )
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
	
		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}


void AFloorIsLavaCharacter::GameOver(int status)
{
	//status 0, player fell into lava
	if(status == 0)
	{
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, TEXT("Ahh your parts are damaged !!!! ( X - X)/"));
	}
	else if (status == 1) //status 1, player get touched by the chasing actors
	{
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("Poisoned by unknown creatures... O A O)/"));
	}
	else  //status 2, player reach the platform and won the game
	{
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Stage cleared >w<)/ Hurray~!!"));
	}

	UKismetSystemLibrary::QuitGame(GetWorld(), nullptr, EQuitPreference::Background, true);
}


void AFloorIsLavaCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//get current seconds
	float currentSec = GetWorld()->UWorld::GetRealTimeSeconds();

	//actor vector
	FVector actorLoc = GetActorLocation();

	//floor vector
	FVector floor = FVector(actorLoc.X, actorLoc.Y, 130.277); //z from floor object

	//get vector between floor and actor
	FVector TargetDirection = actorLoc - floor;

	//get vector btwn end platform and actor
	FVector PlatformDirection = actorLoc - EndPlatform->GetActorLocation();

	//if the magnitude is smaller than the min distance(where player looks like on ground from editor)
	if (TargetDirection.Size() <= minDistFromLava)
	{
		//call gameover to end game and display message

		if (startSec == 0)
		{
			startSec = GetWorld()->UWorld::GetRealTimeSeconds();
		}
	
		if (currentSec - startSec > endGameDelay)
		{
			GameOver(0);
		}
	}

	//trigger only when player stand on platform
	float maxDistFromPlatform = 200;
	if (PlatformDirection.Size() <= maxDistFromPlatform)
	{
		//if actor is on end platform, win
		PlatformDirection.Normalize();
		float DotProduct = FVector::DotProduct(EndPlatform->GetActorForwardVector(), PlatformDirection);
		if (DotProduct > 0.85)
		{

			if (startSec == 0)
			{
				startSec = GetWorld()->UWorld::GetRealTimeSeconds();
			}

			if (currentSec - startSec > endGameDelay)
			{
				GameOver(2);
			}
		}
	}
	

	

}