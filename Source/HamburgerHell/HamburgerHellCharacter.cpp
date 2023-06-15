// Copyright Epic Games, Inc. All Rights Reserved.

#include "HamburgerHellCharacter.h"
#include <HamburgerHell/BulletActor.h>
#include <HamburgerHell/MissleActor.h>
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/InputSettings.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "MotionControllerComponent.h"
#include <GameFramework/CharacterMovementComponent.h>
#include "BurgerEnemyCharacter.h"
#include <Components/TimelineComponent.h>


DEFINE_LOG_CATEGORY_STATIC(LogFPChar, Warning, All);

//////////////////////////////////////////////////////////////////////////
// AHamburgerHellCharacter

AHamburgerHellCharacter::AHamburgerHellCharacter()
{
	//Set CurrentHealth to be Health which is 100.0f
	CurrentHealth = Health;

	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);

	// Set the movement component to be this characters movement component
	MovementComponent = GetCharacterMovement();

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-39.56f, 1.75f, 64.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	Mesh1P->SetRelativeRotation(FRotator(1.9f, -19.19f, 5.2f));
	Mesh1P->SetRelativeLocation(FVector(-0.5f, -4.4f, -155.7f));

	// Create a gun mesh component
	FP_Gun = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FP_Gun"));
	FP_Gun->SetOnlyOwnerSee(false);			// otherwise won't be visible in the multilayer
	FP_Gun->bCastDynamicShadow = false;
	FP_Gun->CastShadow = false;
	FP_Gun->SetupAttachment(Mesh1P, TEXT("GripPoint"));
	FP_Gun->SetupAttachment(RootComponent);

	FP_MuzzleLocation = CreateDefaultSubobject<USceneComponent>(TEXT("MuzzleLocation"));
	FP_MuzzleLocation->SetupAttachment(FP_Gun);
	FP_MuzzleLocation->SetRelativeLocation(FVector(0.2f, 48.4f, -10.6f));

	// Default offset from the character location for projectiles to spawn
	GunOffset  = FVector(102.0f, 0.0f, 20.0f);
	GunOffset2 = FVector(101.0f, 0.0f, 20.0f);
	GunOffset3 = FVector(100.0f, 0.0f, 20.0f);
	GunOffset4 = FVector(99.0f, 0.0f, 20.0f);
	GunOffset5 = FVector(98.0f, 0.0f, 20.0f);
	GunOffset6 = FVector(103.0f, 0.0f, 20.0f);

	BulletSpread = FVector(100.5f, 0.0f, 0.0f);
	BulletSpread2 = FVector(0.0f, 0.0f, 0.0f);
	BulletSpread3 = FVector(-1000.5f, 0.0f, 0.0);
	BulletSpread4 = FVector(0.5f, 0.0f, 0.0f);
	BulletSpread5 = FVector(0.0f, 0.0f, 0.0f);
	BulletSpread6 = FVector(-0.5f, 0.0f, 0.0);


	Offsets.Add(GunOffset);
	Offsets.Add(GunOffset2);
	Offsets.Add(GunOffset3);
	Offsets.Add(GunOffset4);
	Offsets.Add(GunOffset5);
	Offsets.Add(GunOffset6);

	BulletSpreads.Add(BulletSpread);
	BulletSpreads.Add(BulletSpread2);
	BulletSpreads.Add(BulletSpread3);
	BulletSpreads.Add(BulletSpread4);
	BulletSpreads.Add(BulletSpread5);
	BulletSpreads.Add(BulletSpread6);
	// Note: The ProjectileClass and the skeletal mesh/animation blueprints for Mesh1P, FP_Gun, and VR_Gun 
	// are set in the derived blueprint asset named MyCharacter to avoid direct content references in C++.
}

void AHamburgerHellCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//Check if the health is less than or equal to 0...
	if (GetCurrentHealth() <= 0)
	{
		ElapsedTime += DeltaTime;
		OnDeath(ElapsedTime);
		CurrentHealth = 0.0f;
	}

	//GEngine->AddOnScreenDebugMessage(1, 10.0f, FColor::Cyan,"" +FString::SanitizeFloat(GetCurrentHealth(),5), true);
	// If the animation is active...
		// Increase time
		SetBulletcurrentTimeToShoot(GetBulletcurrentTimeToShoot() + 1);
	// If the animation is active...
		// Increase time 
		SetMissilecurrentTimeToShoot(GetMissilecurrentTimeToShoot() + 1);
}

void AHamburgerHellCharacter::OnDeath(float Time)
{
	//Disable player movements
	MovementComponent->Deactivate();
	FirstPersonCameraComponent->bUsePawnControlRotation = false;
	bUseControllerRotationYaw = false;

	//How long it will take for the camera to lerp
	float TimeTransition = 5.0f;
	//The time between the starting position and the target position
	float Alpha = FMath::Clamp(Time / TimeTransition, 0.0f, 1.0f);
	//The new position the camera will be in after the lerp
	FVector NewPosition = FMath::Lerp(FirstPersonCameraComponent->GetRelativeLocation(), FVector(0.0f, -150.0f, -80.0f), Alpha);
	FirstPersonCameraComponent->SetRelativeLocation(NewPosition);

	//The new rotation the camera will be in after the lerp
	FRotator NewRotation = FMath::Lerp(FirstPersonCameraComponent->GetRelativeRotation(), FRotator(0.0f, 0.0f, -60.0f), Alpha);
	FirstPersonCameraComponent->SetRelativeRotation(NewRotation);

	//Disable the gun
	FP_Gun->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	//Set the player dead to true
	PlayerDead = true;
}

float AHamburgerHellCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	//subtract the amount of damage the burgers do from the current health
	CurrentHealth -= DamageAmount;

	//if (CurrentHealth <= 0)
	//{
	//	//Disable Collision
	//	this->SetActorEnableCollision(false);
	//	//Re-spawn the player
	//	this->SetActorRelativeLocation(FVector(2860.0f, 29570.0f, 362.0f));
	//	//Rein-able the collision
	//	this->SetActorEnableCollision(true);
	//	//Set the current health back to the default
	//	
	//}
	return DamageAmount;
}

void AHamburgerHellCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	//GetOwner()->OnTakeAnyDamage.AddDynamic(this, &AHamburgerHellCharacter::OnTakeRadialDamage);

	//Attach gun mesh component to Skeleton, doing it here because the skeleton is not yet created in the constructor
	FP_Gun->AttachToComponent(Mesh1P, FAttachmentTransformRules(EAttachmentRule::KeepRelative, true), TEXT("GripPoint"));

	// Show or hide the two versions of the gun based on whether or not we're using motion controllers.
	if (bUsingMotionControllers)
	{
		/*VR_Gun->SetHiddenInGame(false, true);*/
		Mesh1P->SetHiddenInGame(true, true);
	}
	else
	{
		/*VR_Gun->SetHiddenInGame(true, true);*/
		Mesh1P->SetHiddenInGame(false, true);
	}
	CurrentHealth = Health;
}

//////////////////////////////////////////////////////////////////////////
// Input

void AHamburgerHellCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// set up game-play key bindings
	check(PlayerInputComponent);

	// Bind jump events
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	// Bind fire event
	//PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AHamburgerHellCharacter::OnFire);
	//PlayerInputComponent->BindAction("FireM", IE_Pressed, this, &AHamburgerHellCharacter::OnFireMissle);

	// Bind movement events
	PlayerInputComponent->BindAxis("MoveForward", this, &AHamburgerHellCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AHamburgerHellCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turn-rate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &AHamburgerHellCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AHamburgerHellCharacter::LookUpAtRate);
}

void AHamburgerHellCharacter::OnFire(FVector location, FRotator Spread)
{
	// Check if the current time to shoot is more or equal to the final time...
		// try and fire a projectile
	UWorld* const World = GetWorld();
	if (World != nullptr)
	{
		SetBulletReloadAnimationActive(false);
		SetBulletcurrentTimeToShoot(0);
		const FRotator SpawnRotation = GetControlRotation();
		// MuzzleOffset is in camera space, so transform it to world space before offsetting from the character location to find the final muzzle position
		const FVector SpawnLocation = location + SpawnRotation.RotateVector(GunOffset);

		//Set Spawn Collision Handling Override
		FActorSpawnParameters ActorSpawnParams;
		ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		// spawn the projectile at the muzzle
		World->SpawnActor<ABulletActor>(SpawnLocation, Spread, ActorSpawnParams);

	}
}

void AHamburgerHellCharacter::OnBulletFireSound(USoundBase* sound)
{
	// try and play the sound if specified
	if (sound != nullptr)
	{
		UGameplayStatics::PlaySoundAtLocation(this, sound, GetActorLocation());
	}
}

void AHamburgerHellCharacter::OnBulletReloadSound(USoundBase* sound)
{
	// Set bool true...
	SetBulletReloadAnimationActive(true);
	// Check if animation exist...
	if (sound != nullptr)
	{
		// Do sound
		UGameplayStatics::PlaySoundAtLocation(this, sound, GetActorLocation());
	}
}

void AHamburgerHellCharacter::OnFireMissle(FVector location, FRotator Rotration)
{
	// Check if the current time to shoot is more or equal to the final time...

		// try and fire a projectile
	UWorld* const World = GetWorld();
	if (World != nullptr)
	{
		SetMissileReloadAnimationActive(false);
		SetMissilecurrentTimeToShoot(0);
		const FRotator SpawnRotation = GetControlRotation();
		// MuzzleOffset is in camera space, so transform it to world space before offsetting from the character location to find the final muzzle position
		const FVector SpawnLocation = location + SpawnRotation.RotateVector(GunOffset);

		//Set Spawn Collision Handling Override
		FActorSpawnParameters ActorSpawnParams;
		ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		// spawn the projectile at the muzzle
		World->SpawnActor<AMissleActor>(SpawnLocation, Rotration, ActorSpawnParams);

	}
}

void AHamburgerHellCharacter::OnMissleFireSound(USoundBase* sound)
{
	// try and play the sound if specified
	if (sound != nullptr)
	{
		UGameplayStatics::PlaySoundAtLocation(this, sound, GetActorLocation());
	}
}

void AHamburgerHellCharacter::OnMissleReloadSound(USoundBase* sound)
{
	// Set bool true...
	SetBulletReloadAnimationActive(true);
	// Check if animation exist...
	if (sound != nullptr)
	{
		// Do sound
		UGameplayStatics::PlaySoundAtLocation(this, sound, GetActorLocation());
	}
}


void AHamburgerHellCharacter::MoveForward(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorForwardVector(), Value);
	}
}

void AHamburgerHellCharacter::MoveRight(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorRightVector(), Value);
	}
}

void AHamburgerHellCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AHamburgerHellCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}
