// Fill out your copyright notice in the Description page of Project Settings.


#include "MissleActor.h"
#include <Components/SphereComponent.h>
#include <Components/BoxComponent.h>
#include <GameFramework/ProjectileMovementComponent.h>
#include <HamburgerHell/BurgerEnemyCharacter.h>
#include <Engine/Engine.h>
#include <Kismet/GameplayStatics.h>
// Sets default values
AMissleActor::AMissleActor()
{
	// MakeCollision
	MakeBoxCollision();
	// Makes the mesh
	MakeMesh();
	// Make movement
	MakeMovement();
	// Die after 3 seconds
	InitialLifeSpan = 20.0f;

	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}
void AMissleActor::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// ..check if it exits and if its not a bullet.
	if ((OtherActor != this) && (OtherActor->GetFName() != "SelfMadePlayer_0") && (OtherActor != nullptr))
	{
		// If the actor has the name Bullet...
		if (OtherActor->GetRootComponent()->ComponentHasTag(UnWantedCollisionName1))
			return;// Do not continue
		// Make mesh not visible
		MeshA->SetVisibility(false);
		// Make the box collision BIG
		BoxCollision->SetWorldScale3D(FVector(30, 30, 30));
		// Turn off movement
		getMovementComponent()->SetActive(false);
		// Try to cast the other actor as a burger enemy character...
		if (ABurgerEnemyCharacter* charactorCheck = Cast<ABurgerEnemyCharacter>(OtherActor))
		{
			// See if its NULL...
			if (charactorCheck != NULL)
			{
				// Get the health of the enemy...
				float currenthealth = charactorCheck->getHealth();
				// Deal Damage
				charactorCheck->setHealth((int)currenthealth - getDamage());
			}
		}
		// Set the collision happened bool to true
		DidCollisionHappen = true;
	}
}
void AMissleActor::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}
void AMissleActor::OnCollisionSound(USoundBase* sound)
{
	// try and play the sound if specified...
	if (sound != nullptr)
	{
		// Play the sound
		UGameplayStatics::PlaySoundAtLocation(this, sound, GetActorLocation());
	}
}
// Called when the game starts or when spawned
void AMissleActor::BeginPlay()
{
	Super::BeginPlay();
}
void AMissleActor::MakeBoxCollision()
{
	// Create the box
	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	// Set root component to the box
	RootComponent = BoxCollision;
	// Set the place it is in
	BoxCollision->SetRelativeLocation(RootComponent->GetComponentLocation(), false, nullptr, ETeleportType::None);
	// Set the world location 
	BoxCollision->SetWorldLocation(getBoxWorldPosistion());
	// Set the relativeScale
	BoxCollision->SetRelativeScale3D(FVector(5.0f, 5.0f, 5.0f));
	// Set the profile name
	BoxCollision->BodyInstance.SetCollisionProfileName("Trigger");
	// Add dynamics
	BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &AMissleActor::OnOverlapBegin);
	BoxCollision->OnComponentEndOverlap.AddDynamic(this, &AMissleActor::OnOverlapEnd);
	// Set the collision response channels
	BoxCollision->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);
	BoxCollision->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);
	BoxCollision->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldStatic, ECollisionResponse::ECR_Ignore);
	// Set generate overlap events to true
	BoxCollision->SetGenerateOverlapEvents(true);
	// Add the tag to the collision
	BoxCollision->ComponentTags.Add(Name);

}
void AMissleActor::MakeMovement()
{
	// Makes a default movement
	Movement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Movement"));
	getMovementComponent()->UpdatedComponent = RootComponent;
	// Set the movements speed
	getMovementComponent()->InitialSpeed = getInitialSpeed();
	getMovementComponent()->MaxSpeed = getMaxSpeed();
	// Allows for rotations
	getMovementComponent()->bRotationFollowsVelocity = true;
	// Allows for bounce
	getMovementComponent()->bShouldBounce = getShouldBounce();
	// Set the bounce
	getMovementComponent()->Bounciness = getBounceiness();
	// Set velocity
	getMovementComponent()->Velocity = getVelocity();
	// Set the gravity off and on with a float
	getMovementComponent()->ProjectileGravityScale = 0.0f;
}
void AMissleActor::MakeMesh()
{
	// Make a default sub object of mesh
	MeshA = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	// Allow all to see it
	getMeshComponent()->SetupAttachment(RootComponent);
	// Shadows
	getMeshComponent()->bCastDynamicShadow = false;
	// Case a shadow
	getMeshComponent()->CastShadow = false;
	// Set the place it is in
	getMeshComponent()->SetRelativeLocation(RootComponent->GetComponentLocation(), false, nullptr, ETeleportType::None);
	// Set the relativeScale
	getMeshComponent()->SetRelativeScale3D(getMeshScale());
	// Set the relative location
	getMeshComponent()->SetRelativeLocation(getMeshPosistion());
	// Set the mesh to a preset assets
	ConstructorHelpers::FObjectFinder<UStaticMesh>MeshAsset(TEXT("StaticMesh'/Game/Geometry/Meshes/SM_Missile.SM_Missile'"));
	// Make the mesh asset in to a pointer of asset
	UStaticMesh* Asset = MeshAsset.Object;
	// Set the staticMesh
	getMeshComponent()->SetStaticMesh(Asset);
}
// Called every frame
void AMissleActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	// Rotate the rocket
	MeshA->AddLocalRotation(FRotator(0,0,10));
	// Check if collisoin happed...
	if (DidCollisionHappen == true)
	{
		// If current time is greater than time...
		if (currentTime >= Time)
			this->Destroy();// Then destroy self
		else
			currentTime++;// Increase currentTime
	}
}