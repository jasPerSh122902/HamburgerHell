// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "HamburgerHellCharacter.generated.h"

class UInputComponent;
class USkeletalMeshComponent;
class USceneComponent;
class UCameraComponent;
class UMotionControllerComponent;
class UAnimMontage;
class USoundBase;
class UCharacterMovementComponent;
class ABurgerEnemyCharacter;
class AMissleActor;
class ABulletActor;
class UUserWidget;

UCLASS(config=Game)
class AHamburgerHellCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Pawn mesh: 1st person view (arms; seen only by self) */
	UPROPERTY(VisibleDefaultsOnly, Category=Mesh)
	USkeletalMeshComponent* Mesh1P;

	/** Gun mesh: 1st person view (seen only by self) */
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	USkeletalMeshComponent* FP_Gun;

	/** Location on gun mesh where projectiles should spawn. */
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	USceneComponent* FP_MuzzleLocation;

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FirstPersonCameraComponent;

	/** How fast the player can walk*/
	UPROPERTY(EditAnywhere)
	float PlayerSpeed = 600.0f;

	/** Default player health*/
	UPROPERTY(EditAnywhere)
	float Health = 100.0f;

	/// <summary>
	/// A camera offset for when the player dies
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera, meta = (AllowPrivateAccess = "true"))
	FVector CameraOffset;

	/// <summary>
	/// Time that has passed since players death
	/// </summary>
	UPROPERTY(EditAnywhere)
	float ElapsedTime = 0.0f;

public:
	/// <summary>
	/// The Players Movement Component
	/// </summary>
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	UCharacterMovementComponent* MovementComponent;

	/// <summary>
	/// Boolean for if player is dead or not
	/// </summary>
	UPROPERTY(BlueprintReadOnly)
	bool PlayerDead = false;

public:
	AHamburgerHellCharacter();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/// <summary>
	/// The players current health
	/// </summary>
	UPROPERTY(BlueprintReadOnly)
	float CurrentHealth;
	
	/// <summary>
	/// Returns the players current health
	/// </summary>
	UFUNCTION(BlueprintCallable)
	float GetCurrentHealth() { return CurrentHealth; }

	/// <summary>
	/// Sets the players current health to a new health
	/// </summary>
	UFUNCTION(BlueprintCallable)
	void SetCurrentHealth(float NewHealth){CurrentHealth = NewHealth;}

	/// <summary>
	/// Funtion is called when players health reaches zero
	/// When called players movement and shooting are disabled and camera is lerped into
	/// a position to for a death like scene.
	/// </summary>
	UFUNCTION(BlueprintCallable)
	void OnDeath(float Time);

	//--------------------------------Bullet Functions--------------------------------------------------
	/// <summary>
	/// Gets the current time to shoot the Bullet
	/// </summary>
	/// <returns>BulletcurrentTimeToShoot</returns>
	UFUNCTION(BlueprintCallable)
		float GetBulletcurrentTimeToShoot() { return BulletcurrentTimeToShoot; }
	/// <summary>
	/// Set the current time to shoot the Bullet
	/// </summary>
	/// <float="time"></param>
	UFUNCTION(BlueprintCallable)
		void SetBulletcurrentTimeToShoot(float time) {BulletcurrentTimeToShoot = time;}
	/// <summary>
	/// Gets the final time to shoot
	/// </summary>
	/// <returns>BulletFinalTimeToShoot</returns>
	UFUNCTION(BlueprintCallable)
		float GetBulletFinalTimeToShoot() { return BulletFinalTimeToShoot; }
	/// <summary>
	/// Set the final time to shoot
	/// </summary>
	/// <float="time"></param>
	UFUNCTION(BlueprintCallable)
	void SetBulletFinalTimeToShoot(float time) { BulletFinalTimeToShoot = time; }
	/// <summary>
	/// Get the animation active
	/// </summary>
	/// <returns>BulletReloadAnimationActive</returns>
	UFUNCTION(BlueprintCallable)
		bool GetBulletReloadAnimationActive() { return BulletReloadAnimationActive; }
	/// <summary>
	/// Set the animation active
	/// </summary>
	/// <bool="active"></param>
	UFUNCTION(BlueprintCallable)
	void SetBulletReloadAnimationActive(bool active) { BulletReloadAnimationActive = active; }
	//--------------------------------Missile Functions--------------------------------------------------
	/// <summary>
	/// Get the current time to shoot
	/// </summary>
	/// <returns>MissilecurrentTimeToShoot</returns>
	UFUNCTION(BlueprintCallable)
		float GetMissilecurrentTimeToShoot() { return MissilecurrentTimeToShoot; }
	/// <summary>
	/// Set the current time to shoot
	/// </summary>
	/// <float="time"></param>
	UFUNCTION(BlueprintCallable)
	void SetMissilecurrentTimeToShoot(float time) { MissilecurrentTimeToShoot = time; }
	/// <summary>
	/// Get final time to shoot
	/// </summary>
	/// <returns>MissileFinalTimeToShoot</returns>
	UFUNCTION(BlueprintCallable)
		float GetMissileFinalTimeToShoot() { return MissileFinalTimeToShoot; }
	/// <summary>
	/// Set final time to shoot
	/// </summary>
	/// <float="time"></param>
	UFUNCTION(BlueprintCallable)
	void SetMissileFinalTimeToShoot(float time) { MissileFinalTimeToShoot = time; }
	/// <summary>
	/// Get the animation active
	/// </summary>
	/// <returns>MissleReloadAnimationActive</returns>
	UFUNCTION(BlueprintCallable)
		bool GetMissileReloadAnimationActive() { return MissileReloadAnimationActive; }
	/// <summary>
	/// Set the animation active
	/// </summary>
	/// <bool="active"></param>
	UFUNCTION(BlueprintCallable)
	void SetMissileReloadAnimationActive(bool active) { MissileReloadAnimationActive = active; }

private:
	/// <summary>
	/// When an enemy burger hits the player the health is depleted by how much the enemy burgers damage is.
	/// </summary>
	UFUNCTION(BlueprintCallable)
	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

protected:
	virtual void BeginPlay();

public:
	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;
//----------------------------------Gun Off sets--------------------------------
	/** Gun muzzle's offset from the characters location */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category= "Bullet offset")
		FVector GunOffset;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Bullet offset")
		FVector GunOffset2;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Bullet offset")
		FVector GunOffset3;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Bullet offset")
		FVector GunOffset4;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Bullet offset")
		FVector GunOffset5;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Bullet offset")
		FVector GunOffset6;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Bullet offset")
		FVector GunOffset7;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Bullet offset")
		FVector GunOffset8;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Bullet offset")
		FVector GunOffset9;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Bullet offset")
		FVector GunOffset10;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Bullet offset")
		FVector GunOffset11;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Bullet offset")
		TArray<FVector> Offsets;
	/** Gun muzzle's offset from the characters location */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Bullet Spread")
		FVector BulletSpread;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Bullet Spread")
		FVector BulletSpread2;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Bullet Spread")
		FVector BulletSpread3;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Bullet Spread")
		FVector BulletSpread4;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Bullet Spread")
		FVector BulletSpread5;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Bullet Spread")
		FVector BulletSpread6;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Bullet Spread")
		FVector BulletSpread7;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Bullet Spread")
		FVector BulletSpread8;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Bullet Spread")
		FVector BulletSpread9;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Bullet Spread")
		FVector BulletSpread10;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Bullet Spread")
		FVector BulletSpread11;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Bullet Spread")
		TArray<FVector> BulletSpreads;
	/** Projectile class to spawn */
	UPROPERTY(EditDefaultsOnly, Category=Projectile)
		TSubclassOf<class ABulletActor> ProjectileClass;
	/** Projectile class to spawn */
	UPROPERTY(EditDefaultsOnly, Category = Projectile)
		TSubclassOf<class AMissleActor> ProjectileClass2;
	//--------------------------------Bullet variables--------------------------------------------------
	// Current time for Bullet
	UPROPERTY(EditAnywhere, Category = "Bullet")
		float BulletcurrentTimeToShoot = 0.0f;
	// Final time for Bullet
	UPROPERTY(EditAnywhere, Category = "Bullet")
		float BulletFinalTimeToShoot = 35.0f;
	// Is the animation active
	UPROPERTY(EditAnywhere, Category = "Bullet")
		bool BulletReloadAnimationActive = false;
	//--------------------------------Missile variables--------------------------------------------------
	//Current time for Missile
	UPROPERTY(EditAnywhere, Category = "Missile")
		float MissilecurrentTimeToShoot = 0.0f;
	// Final time for Bullet
	UPROPERTY(EditAnywhere, Category = "Missile")
		float MissileFinalTimeToShoot = 100.0f;
	// Is the animation active
	UPROPERTY(EditAnywhere, Category = "Missile")
		bool MissileReloadAnimationActive = false;
	/** Whether to use motion controller location for aiming. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	uint8 bUsingMotionControllers : 1;

public:
//----------------------------------Bullet animation and sound functions---------------
	/** Fires a projectile. */
	UFUNCTION(BlueprintCallable)
		void OnFire(FVector location, FRotator Spread);
	UFUNCTION(BlueprintCallable)
		void OnBulletFireSound(USoundBase* sound);
	UFUNCTION(BlueprintCallable)
		void OnBulletReloadSound(USoundBase* sound);
//----------------------------------Missile animation and sound functions---------------
	/** Fires a Missile. */
	UFUNCTION(BlueprintCallable)
		void OnFireMissle(FVector location, FRotator Rotration);
	UFUNCTION(BlueprintCallable)
		void OnMissleFireSound(USoundBase* sound);
	UFUNCTION(BlueprintCallable)
		void OnMissleReloadSound(USoundBase* sound);
	/** Handles moving forward/backward */
	void MoveForward(float Val);

	/** Handles stafing movement, left and right */
	void MoveRight(float Val);

	/**
	 * Called via input to turn at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);
	
protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;
	// End of APawn interface

public:
	/** Returns Mesh1P sub-object **/
	USkeletalMeshComponent* GetMesh1P() const { return Mesh1P; }
	/** Returns FirstPersonCameraComponent sub-object **/
	UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }

};

