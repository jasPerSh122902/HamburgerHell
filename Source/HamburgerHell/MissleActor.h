// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MissleActor.generated.h"

class USphereComponent;
class UBoxComponent;
class UProjectileMovementComponent;
class UStaticMeshComponent;
class ABurgerActor;
class ABurgerEnemyCharacter;
//class USoundBase;
//class UParticleSystem;

UCLASS()
class HAMBURGERHELL_API AMissleActor : public AActor
{
	GENERATED_BODY()
public:
	// Sets default values for this actor's properties
	AMissleActor();
	/// <summary>
	/// Called when it hits something
	/// </summary>
/** called when something enters the sphere component */
	UFUNCTION(Category = "Missile")
		void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	//	void OnOverlapBegin_Implementation(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

		/** called when something leaves the sphere component */
	UFUNCTION(Category = "Missile")
		void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	//void OnOverlapEnd_Implementation(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	/// <summary>
	/// Makes the Box collision
	/// </summary>
	void MakeBoxCollision();
	/// <summary>
	/// Makes the movement
	/// </summary>
	void MakeMovement();
	/// <summary>
	/// Makes the Mesh
	/// </summary>
	void MakeMesh();

	/// <summary>
	/// Play the sound
	/// </summary>
	/// <USoundBase="sound"></param>
	UFUNCTION(BlueprintCallable)
	void OnCollisionSound(USoundBase* sound);
//--------------------------------Damage--------------------------------------------------
	/// <summary>
	/// Set the Damage
	/// </summary>
	/// <float="damage">how much health is taken</param>
	UFUNCTION(BlueprintCallable)
	void SetDamage(float damage) { Damage = damage; }
	/// <summary>
	/// Gets the damage
	/// </summary>
	/// <returns>Damage</returns>
	UFUNCTION(BlueprintCallable)
	float getDamage() { return Damage; }
//------------------------Box Collisions Functions-------------------------------
	/// <summary>
	/// Sets the Box collider component
	/// </summary>
	/// <USphereComponent*="sphere">Current Collider</param>
	void setBoxCollision(UBoxComponent* sphere) { BoxCollision = sphere; }
	/// <summary>
	/// Gets the Box collider component
	/// </summary>
	/// <returns>SphereCollision</returns>
	UBoxComponent* getBoxCollision() { return BoxCollision; }
	/// <summary>
	/// Sets Scale
	/// </summary>
	/// <float="scale">Size</param>
	void setBoxScale(FVector scale) { BoxScale = scale; }
	/// <summary>
	/// Gets the scale
	/// </summary>
	/// <returns>BoxScale</returns>
	FVector getBoxScale() { return BoxScale; }
	/// <summary>
	/// Sets position
	/// </summary>
	/// <FVector="posistion"></param>
		void setBoxWorldPosistion(FVector posistion) { collisionBoxWorldLocation = posistion; }
	/// <summary>
	/// Get position
	/// </summary>
	/// <returns>collisionPosistion</returns>
		FVector getBoxWorldPosistion() { return collisionBoxWorldLocation; }


//------------------------MESH Functions-------------------------------------------
	/// <summary>
	/// Set position
	/// </summary>
	/// <FVector="posistion"></param>
	void setMeshPosistion(FVector posistion) { MeshPosistion = posistion; }
	/// <summary>
	/// Get position
	/// </summary>
	/// <returns>MeshPosistion</returns>
	FVector getMeshPosistion() { return MeshPosistion; }
	/// <summary>
	/// Set scale
	/// </summary>
	/// <FVector="posistion"></param>
	void setMeshScale(FVector posistion) { MeshScale = posistion; }
	/// <summary>
	/// Get scale
	/// </summary>
	/// <returns>MeshScale</returns>
	FVector getMeshScale() { return MeshScale; }
	/// <summary>
	/// Set Static mesh component
	/// </summary>
	/// <UStaticMeshComponent*="mesh"></param>
	void setMeshComponent(UStaticMeshComponent* mesh) { MeshA = mesh; }
	/// <summary>
	/// Get the Static mesh component
	/// </summary>
	/// <returns>MeshA</returns>

	UStaticMeshComponent* getMeshComponent() { return MeshA; }
//------------------------Movement Functions-------------------------------------------
	/// <summary>
	/// Set the movement component
	/// </summary>
	/// <UProjectileMovementComponent*="movement"></param>
	void setMovementComponent(UProjectileMovementComponent* movement) { Movement = movement; }
	/// <summary>
	/// Get the movement component
	/// </summary>
	/// <returns>Movement</returns>
	UProjectileMovementComponent* getMovementComponent() { return Movement; }
	/// <summary>
	/// Set the initialSpeed
	/// </summary>
	/// <float="speed">How fast the object moves</param>
	void setInitialSpeed(float speed) { InitialSpeed = speed; }
	/// <summary>
	/// Get the initailSpeed
	/// </summary>
	/// <returns>InitialSpeed</returns>
	float getInitialSpeed() { return InitialSpeed; }
	/// <summary>
	/// Set the MaxSpeed
	/// </summary>
	/// <float="speed">How fast the object moves</param>
	void SetMaxSpeed(float speed) { MaxSpeed = speed; }
	/// <summary>
	/// Get the Max Speed
	/// </summary>
	/// <returns>MaxSpeed</returns>
	float getMaxSpeed() { return MaxSpeed; }
	/// <summary>
	/// Set the should bounce
	/// </summary>
	/// <bool="shouldbounce">If you want bounce or not</param>
	void setShouldBounce(bool shouldbounce) { ShouldBounce = shouldbounce; }
	/// <summary>
	/// Get the should bounce
	/// </summary>
	/// <returns>ShouldBounce</returns>
	bool getShouldBounce() { return ShouldBounce; }
	/// <summary>
	/// Set Bounciness
	/// </summary>
	/// <float="bounceAmount">How much bounce there is</param>
	void setBounceiness(float bounceAmount) { bounceiness = bounceAmount; }
	/// <summary>
	/// Get BOunceiness
	/// </summary>
	/// <returns>bounciness</returns>
	float getBounceiness() { return bounceiness; }
	/// <summary>
	/// Set Velocity
	/// </summary>
	/// <FVector="velocity">Increase the ability to move in multiple directions</param>
	void setVelocity(FVector velocity) { Velocity = velocity; }
	/// <summary>
	/// Get Velocity
	/// </summary>
	/// <returns>Velocity</returns>
	FVector getVelocity() { return Velocity; }
private:
//------------------------General Collisions variables------------------------------
	UPROPERTY(VisibleAnywhere, Category = "MissleCollisionsDEVLOG")
		FName Name = "MissleActor";
	UPROPERTY(VisibleAnywhere, Category = "MissleCollisionsDEVLOG")
		FName UnWantedCollisionName1 = "BulletActor";
	UPROPERTY(VisibleAnywhere, Category = "MissleCollisionsDEVLOG")
		FName WantedCollisionName1 = "EnemyActor";
	private:
	UPROPERTY(VisibleAnywhere, Category = "MissleCollisionsDEVLOG")
		bool DidCollisionHappen = false;
	UPROPERTY(VisibleAnywhere, Category = "MissleCollisionsDEVLOG")
		float currentTime = 0.0f;
	UPROPERTY(VisibleAnywhere, Category = "MissleCollisionsDEVLOG")
		float Time = 25.0f;
//------------------------Box Collisions variables------------------------------
	UPROPERTY(VisibleAnywhere, Category = "MissleBoxCollisions")
		UBoxComponent* BoxCollision;
	private:
	UPROPERTY(EditAnywhere, Category = "MissleBoxCollisions")
		FVector BoxScale = FVector(10.f, 10.f, 10.f);
	UPROPERTY(VisibleAnywhere, Category = "MissleBoxCollisions")
	FVector collisionBoxWorldLocation = FVector(0.0f, 0.0f, 0.0f);
//------------------------Damage-----------------------------------------
	ABurgerEnemyCharacter* currentEnemy;
	UPROPERTY(EditAnywhere, Category = "MissleDamage")
	float Damage = 100;
//------------------------Mesh variables-------------------------------------------
	UPROPERTY(VisibleAnywhere, Category = "MissleMesh")
		FVector MeshPosistion;
	UPROPERTY(VisibleAnywhere, Category = "MissleMesh")
		UStaticMeshComponent* MeshA;
	UPROPERTY(EditAnywhere, Category = "MissleMesh")
		FVector MeshScale = FVector(.02f, .02f, .02f);
//------------------------Movement/Location variables---------------------------------
	UPROPERTY(VisibleAnywhere, Category = "MissleMovement")
		UProjectileMovementComponent* Movement;
	UPROPERTY(EditAnywhere, Category = "MissleMovement")
		float InitialSpeed = 1500.f;
	UPROPERTY(EditAnywhere, Category = "MissleMovement")
		float MaxSpeed = 3000.f;
	UPROPERTY(VisibleAnywhere, Category = "MissleMovement")
		bool  ShouldBounce = false;
	UPROPERTY(VisibleAnywhere, Category = "MissleMovement")
		float bounceiness = 4.0f;
	UPROPERTY(VisibleAnywhere, Category = "MissleMovement")
		FVector Velocity = FVector(1.0f, 0.0f, 0.0f);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};