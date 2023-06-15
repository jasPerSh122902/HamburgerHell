// Fill out your copyright notice in the Description page of Project Settings.


#include "BurgerEnemyCharacter.h"
#include <Components/CapsuleComponent.h>
#include <Components/SphereComponent.h>
#include "HamburgerHellCharacter.h"

// Sets default values
ABurgerEnemyCharacter::ABurgerEnemyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Set the Collider's Scale
	UCapsuleComponent* BurgerCollider = FindComponentByClass<UCapsuleComponent>();
	BurgerCollider->SetWorldScale3D({ 0.55f, 2.0f, 0.55f });
	//Set Mesh Transform
	USkeletalMeshComponent* SkelMesh = FindComponentByClass<USkeletalMeshComponent>();
	SkelMesh->SetRelativeLocation({ 0.0f, 0.0f, -72.727272f });
	SkelMesh->SetRelativeRotation({ 0.0f,-90.000183f, 0.0f });
	SkelMesh->SetRelativeScale3D({ 1.818182f, 0.500000f, 1.818182f });
	//Set Mesh Collision
	SkelMesh->SetGenerateOverlapEvents(true);
	SkelMesh->CanCharacterStepUpOn = ECB_Yes;
	SkelMesh->SetCollisionProfileName(TEXT("Trigger"));
	//Add Sphere Collider
	Hitbox = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Collider"));
	Hitbox->SetupAttachment(RootComponent);
	Hitbox->SetRelativeScale3D({ 4.673640f, 3.486618f, 4.818182f });
	Hitbox->SetSphereRadius(32.0f);

	GetRootComponent()->ComponentTags.Add("EnemyActor");

}

// Called when the game starts or when spawned
void ABurgerEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
}

 //Called every frame
void ABurgerEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABurgerEnemyCharacter::DealDamageTo(AActor* OtherActor)
{
	//Calls the TakeDamage function in the players class
	OtherActor->TakeDamage(m_damage, FDamageEvent(), GetInstigatorController(), this);
}



