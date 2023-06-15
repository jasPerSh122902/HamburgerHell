// Fill out your copyright notice in the Description page of Project Settings.


#include "BulletActor.h"
#include <Components/SphereComponent.h>
#include <Components/BoxComponent.h>
#include <GameFramework/ProjectileMovementComponent.h>
#include <Engine/Engine.h>
#include <Kismet/GameplayStatics.h>
#include <Engine/World.h>
#include <HamburgerHell/BurgerEnemyCharacter.h>

// Sets default values
ABulletActor::ABulletActor()
{
	// MakeCollision
	MakeBoxCollision();
	// Makes the mesh
	MakeMesh();
	// Make movement
	MakeMovement();
	// Die after 3 seconds
	InitialLifeSpan = 3.0f;
	// Set this actor to call Tick() every frame.You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void ABulletActor::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// get the location of the mesh...
	FVector location = MeshA->GetComponentLocation();
	// ..check if it exits and if its not a bullet.
	if ((OtherActor != this) && (OtherActor->GetFName() != "SelfMadePlayer_0") && (OtherActor != nullptr))
	{
		// If the actor has the name Bullet...
		if (OtherActor->GetRootComponent()->ComponentHasTag(UnWantedCollisionname1))
			return;// Do not continue
		// If the actor has the name enemy actor...
		if (ABurgerEnemyCharacter* charactorCheck = Cast<ABurgerEnemyCharacter>(OtherActor))
		{
			// See if its NULL...
			if (charactorCheck != NULL)
			{
				// Get the health of the enemy...
				float currenthealth = Cast<ABurgerEnemyCharacter>(OtherActor)->getHealth();
				// Deal Damage
				Cast<ABurgerEnemyCharacter>(OtherActor)->setHealth(currenthealth - getDamage());
				// Destroy Self
				Destroy();
			}
		}
	}
}

void ABulletActor::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}

// Called when the game starts or when spawned
void ABulletActor::BeginPlay()
{
	Super::BeginPlay();
	// Set the location to the actors location.
	StartLocation = GetActorLocation();
}

void ABulletActor::MakeBoxCollision()
{
	// Make a default Sub-object
	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Circle"));
	// Set the size
	GetBoxCollision()->SetWorldScale3D(getBoxScale());
	// Set the collision profile
	GetBoxCollision()->BodyInstance.SetCollisionProfileName("Trigger");
	// Makes it so it has collision
	GetBoxCollision()->OnComponentBeginOverlap.AddDynamic(this, &ABulletActor::OnOverlapBegin);
	GetBoxCollision()->OnComponentEndOverlap.AddDynamic(this, &ABulletActor::OnOverlapEnd);
	// Makes player unable to walk on object
	GetBoxCollision()->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	GetBoxCollision()->CanCharacterStepUpOn = ECB_No;
	// Makes the collision not trigger on pawns
	GetBoxCollision()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);
	// Allow triggers to work
	GetBoxCollision()->SetGenerateOverlapEvents(true);
	// Makes the root comp to the collider
	RootComponent = GetBoxCollision();
	// Set a tag name(BulletActor)
	GetBoxCollision()->ComponentTags.Add(Name);
}

void ABulletActor::MakeMovement()
{
	// Makes a default movement
	Movement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Movement"));
	// Updates the movement based on the root-component
	getMovement()->UpdatedComponent = RootComponent;
	// Set the movements speed
	getMovement()->InitialSpeed = getInitialSpeed();
	// Set the maxSpeed to the gotten Max Speed
	getMovement()->MaxSpeed = getMaxSpeed();
	// Allows for rotations
	getMovement()->bRotationFollowsVelocity = true;
	// Allows for bounce
	getMovement()->bShouldBounce = getShouldBounce();
	// Sets the how mush bounce
	getMovement()->Bounciness = getBounceiness();
	// Set velocity
	getMovement()->Velocity = getVeloicty();
	// Set gravity to 0/ NO GRAVITY
	getMovement()->ProjectileGravityScale = 0;
}

void ABulletActor::MakeMesh()
{
	// Make a default sub object of mesh
	MeshA = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	// Allow all to see it
	getMesh()->SetOnlyOwnerSee(false);
	// Attach it to something
	getMesh()->SetupAttachment(RootComponent);
	// Shadows
	getMesh()->bCastDynamicShadow = false;
	// Case a shadow
	getMesh()->CastShadow = false;
	// Set the place it is in
	getMesh()->SetRelativeLocation(RootComponent->GetComponentLocation(), false, nullptr, ETeleportType::None);
	// Sets the world scale of the mesh
	getMesh()->SetWorldScale3D(getMeshScale());
	// Set cancharactersStepUpOn the mesh
	getMesh()->CanCharacterStepUpOn = ECB_No;
	// Set the generateoverlapevents
	getMesh()->SetGenerateOverlapEvents(false);
	// Set the mesh to a preset assets
	ConstructorHelpers::FObjectFinder<UStaticMesh>MeshAsset(TEXT("StaticMesh'/Game/Characters/Weapons/PepperGrinder/pepper_grain.pepper_grain'"));
	// Make the mesh asset in to a pointer of asset
	UStaticMesh* Asset = MeshAsset.Object;
	// Set the staticMesh
	getMesh()->SetStaticMesh(Asset);
}

// Called every frame
void ABulletActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	// gets the positions of the components
	CollisionPosistion = GetBoxCollision()->GetComponentLocation();
	MeshPosistion = getMesh()->GetComponentLocation();
}