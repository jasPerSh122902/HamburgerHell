// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BurgerEnemyCharacter.generated.h"

class AHamburgerHellCharacter;

UCLASS()
class HAMBURGERHELL_API ABurgerEnemyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABurgerEnemyCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/// <summary>
	/// Returns the enemey's health
	/// </summary>
	UFUNCTION(BlueprintCallable)
	float getHealth() { return m_health; }

	/// <summary>
	/// Sets the enemey's health to a given value 
	/// </summary>
	/// <param name="health">The vealue to set health to</param>
	UFUNCTION(BlueprintCallable)
	void setHealth(float health) { m_health = health; }

	/// <summary>
	/// 
	/// </summary>
	/// <returns></returns>
	UFUNCTION(BlueprintCallable)
	float getDamage() { return m_damage; }

	/// <summary>
	/// 
	/// </summary>
	/// <param name="damage"></param>
	UFUNCTION(BlueprintCallable)
	void setDamage(float damage) { m_damage = damage; }

	/// <summary>
	/// Damages the Player
	/// </summary>
	/// <param name="other">The Player</param>
	void DealDamageTo(AActor* OtherActor);

private:
	//The player's damage hitbox
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Collision", meta = (AllowPrivateAccess = "true"))
		class USphereComponent* Hitbox;
	//Enemy's health
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stats", meta = (AllowPrivateAccess = "true"))
	float m_health = 0;
	//Enemy's damage
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stats", meta = (AllowPrivateAccess = "true"))
	float m_damage = 0;

	/// <summary>
	/// Reference to the first person character
	/// </summary>
	AHamburgerHellCharacter* m_player;
};
