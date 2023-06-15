// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BulletActor.generated.h"

class USphereComponent;
class UBoxComponent;
class UProjectileMovementComponent;
class UStaticMeshComponent;
class ABurgerEnemyCharacter;
UCLASS()
class HAMBURGERHELL_API ABulletActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABulletActor();
	/// <summary>
	/// Called when it hits something
	/// </summary>
	/** called when something enters the sphere component */
	UFUNCTION(Category = "Bullet")
		void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	//	void OnOverlapBegin_Implementation(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

		/** called when something leaves the sphere component */
	UFUNCTION(Category = "Bullet")
		void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	//void OnOverlapEnd_Implementation(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	/// <summary>
	/// Makes the collision
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
//------------------------Collision Functions---------------------------------------
	/// <summary>
	/// Set the current Box collider component
	/// </summary>
	/// <UBoxComponent*="BoxCollider">Collider</param>
	void SetBoxCollision(UBoxComponent* BoxCollider) { BoxCollision = BoxCollider; }
	/// <summary>
	/// Get the Box collider
	/// </summary>
	/// <returns>BoxCollision</returns>
	UBoxComponent* GetBoxCollision() { return BoxCollision; }
	/// <summary>
	/// Set the scale
	/// </summary>
	/// <FVector="scale"></param>
	void SetBoxScale(FVector scale) { BoxScale = scale; }
	/// <summary>
	/// Gets the box's scale
	/// </summary>
	/// <returns>BoxScale</returns>
	FVector getBoxScale() { return BoxScale; }
	/// <summary>
	/// Set the position
	/// </summary>
	/// <FVector="posistion"></param>
	void SetBoxPosistion(FVector posistion) { CollisionPosistion = posistion; }
	/// <summary>
	/// Gets the position
	/// </summary>
	/// <returnscollisionPosistion</returns>
	FVector getBoxPosistion() { return CollisionPosistion; }
//------------------------MESH Functions-------------------------------------------
	/// <summary>
	/// Set the position
	/// </summary>
	/// <FVector="posistion"></param>
	void SetMeshPosistion(FVector posistion) { MeshPosistion = posistion; }
	/// <summary>
	/// Gets the position
	/// made on start
	/// </summary>
	/// <returns>MeshPosistion</returns>
	FVector getMeshPosistion() { return MeshPosistion; }
	/// <summary>
	/// Gets the start position
	/// made on start
	/// </summary>
	/// <returns>startLocation</returns>
	FVector GetStartPosistion() { return StartLocation; }
	/// <summary>
	/// Sets mesh component
	/// </summary>
	/// <UStaticMeshComponents="Mesh"></param>
	void setMesh(UStaticMeshComponent* Mesh) { MeshA = Mesh; }
	/// <summary>
	/// Gets the mesh
	/// </summary>
	/// <returns>MeshA</returns>
	UStaticMeshComponent* getMesh() { return MeshA; }
	/// <summary>
	/// Sets the mesh's scale
	/// </summary>
	/// <FVector="scale"></param>
	void setMeshScale(FVector scale) { MeshScale = scale; }
	/// <summary>
	/// Gets the mesh's scale
	/// </summary>
	/// <returns>MeshScale</returns>
	FVector getMeshScale() { return MeshScale; }
	//------------------------MOVEMENT Functions---------------------------------------
	/// <summary>
	/// Sets the movement component
	/// </summary>
	/// <UProjectileMovementComponent*="movement"></param>
	void setMovement(UProjectileMovementComponent* movement) { Movement = movement; }
	/// <summary>
	/// Gets the movement component
	/// </summary>
	/// <returns>Movement</returns>
	UProjectileMovementComponent* getMovement() { return Movement; }
	/// <summary>
	/// Sets the initialSpeed
	/// </summary>
	/// <float="speed">Needs to be a big number to see results</param>
	void setInitialSpeed(float speed) { InitialSpeed = speed; }
	/// <summary>
	/// Gets the initial Speed
	/// </summary>
	/// <returns>InitialSpeed</returns>
	float getInitialSpeed() {return InitialSpeed;}
	/// <summary>
	/// Sets the max speed
	/// </summary>
	/// <float="speed">Is the cap for initial speed</param>
	void setMaxSpeed(float speed) { MaxSpeed = speed; }
	/// <summary>
	/// Gets the max speed
	/// </summary>
	/// <returns>MaxSpeed</returns>
	float getMaxSpeed() { return MaxSpeed; }
	/// <summary>
	/// Sets the shouldbounce variable
	/// </summary>
	/// <bool="shouldBounce">set to false</param>
	void setShouldBounce(bool shouldBounce) { ShouldBounce = shouldBounce; }
	/// <summary>
	/// Gets the shouldBounce variable
	/// </summary>
	/// <returns>ShouldBounce</returns>
	bool getShouldBounce() { return ShouldBounce; }
	/// <summary>
	/// Set the amount of bounce the bullet has
	/// </summary>
	/// <float="bounceAmount"></param>
	void setBounceiness(float bounceAmount) { Bounceiness = bounceAmount; }
	/// <summary>
	/// Gets the amount of bounce a bullet has
	/// </summary>
	/// <returns>Bounceiness</returns>
	float getBounceiness() { return Bounceiness; }
	/// <summary>
	/// Sets the velocity
	/// </summary>
	/// <FVector="velocity"></param>
	void setVelocity(FVector velocity) { Velocity = velocity; }
	/// <summary>
	/// Gets the current velocity
	/// </summary>
	/// <returns>Velocity</returns>
	FVector getVeloicty() { return Velocity; }

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
private:
//------------------------General Collisions variables------------------------------
	UPROPERTY(VisibleAnywhere, Category = "BulletBoxCollisionsDEVLOG")
	FName Name = "BulletActor";
	UPROPERTY(VisibleAnywhere, Category = "BulletBoxCollisionsDEVLOG")
	FName UnWantedCollisionname1 = "MissleActor";
	UPROPERTY(VisibleAnywhere, Category = "BulletBoxCollisionsDEVLOG")
	FName WantedCollisionname1 = "EnemyActor";
//------------------------Collision-------------------------------------
	UPROPERTY(VisibleAnywhere, Category = "BulletBoxCollision")
		UBoxComponent* BoxCollision;
	UPROPERTY(EditAnywhere, Category = "BulletBoxCollision")
		FVector BoxScale = FVector(1.0f, 1.0f, 1.0f);
	UPROPERTY(EditAnywhere, Category = "BulletBoxCollision")
		FVector CollisionPosistion;
	UPROPERTY(VisibleAnywhere, Category = "BulletBoxCollision")
		FVector MeshPosistion;
	UPROPERTY(VisibleAnywhere, Category = "BulletBoxCollision")
		FVector StartLocation;

//------------------------Damage-----------------------------------------
	ABurgerEnemyCharacter* EnemyCharatro;
	UPROPERTY(EditAnywhere, Category = "BulletDamage")
		float Damage = 1;
//------------------------MESH-------------------------------------------
	UPROPERTY(VisibleAnywhere, Category = "BulletMesh")
		UStaticMeshComponent* MeshA;
	UPROPERTY(EditAnywhere, Category = "BulletMesh")
		FVector MeshScale = FVector(1.0f, 1.0f, 1.0f);
//------------------------MOVEMENT---------------------------------------
	UPROPERTY(VisibleAnywhere, Category = "BulletMovement")
		UProjectileMovementComponent* Movement;
	UPROPERTY(EditAnywhere, Category = "BulletMovement")
		float InitialSpeed = 3000.f;
	UPROPERTY(EditAnywhere, Category = "BulletMovement")
		float MaxSpeed = 3000.f;
	UPROPERTY(EditAnywhere, Category = "BulletMovement")
		bool  ShouldBounce = false;
	UPROPERTY(EditAnywhere, Category = "BulletMovement")
		float Bounceiness = 0.2;
	UPROPERTY(VisibleAnywhere, Category = "BulletMovement")
		FVector Velocity = FVector(1.0f, 0, 0);

};