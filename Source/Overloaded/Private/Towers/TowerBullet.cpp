// Fill out your copyright notice in the Description page of Project Settings.


#include "Towers/TowerBullet.h"
#include "Enemy/EnemyPawn.h"
#include "GameFramework/ProjectileMovementComponent.h"


// Sets default values
ATowerBullet::ATowerBullet()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	//Setting up the collision
	BulletCollision = CreateDefaultSubobject<USphereComponent>(TEXT("BulletCollision"));
	RootComponent = BulletCollision;
	BulletCollision->SetGenerateOverlapEvents(true);
	BulletCollision->SetCollisionResponseToAllChannels(ECR_Overlap);
	BulletCollision->SetSphereRadius(10.f);
	
	BulletCollision->OnComponentBeginOverlap.AddDynamic(this, &ATowerBullet::OnEnemyHit);
	
	BulletMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BulletMeshComponent"));
	BulletMeshComponent->SetupAttachment(RootComponent);
	
	BulletProjectile = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("BulletProjectile"));
	BulletProjectile->SetUpdatedComponent(RootComponent);
	//Setting up the projectile speed
	BulletProjectile->InitialSpeed = 1500.f;
	BulletProjectile->MaxSpeed = 2000.f;
	BulletProjectile->bRotationFollowsVelocity = true;
}

// Called when the game starts or when spawned
void ATowerBullet::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ATowerBullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATowerBullet::OnEnemyHit(class UPrimitiveComponent* ThisComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//Getting the ref to the enemy pawn
	AEnemyPawn* EnemyPawn = Cast<AEnemyPawn>(OtherActor);
	
	if (EnemyPawn && EnemyPawn->Implements<UInteractionInterface>())
	{
		//Applying damage to the enemy
		Execute_EnemyTakeDamage(EnemyPawn, 10);
		
		//Deactivate the bullet if it hits the enemy
		DeactivateBullet();
	}
}

void ATowerBullet::ActivateBullet_Implementation(const FVector& BulletLocation, const FRotator& BulletRotation)
{ 
	//Setting the shooting point of the bullet actor
	SetActorLocation(BulletLocation);
	SetActorRotation(BulletRotation);
	
	SetActorEnableCollision(true);
	SetActorHiddenInGame(false);
	
	//Shooting the bullet 
	BulletProjectile->SetVelocityInLocalSpace(FVector::ForwardVector * BulletSpeed);
	BulletProjectile->Activate(true);
	
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green,  IsHidden() ? "True" : "False");
}

void ATowerBullet::DeactivateBullet()
{
	//Resetting the bullet actor by setting collision disabled and hiding it in game
	SetActorEnableCollision(false);
	SetActorHiddenInGame(true);
	
	//Stopping bullet's movement 
	BulletProjectile->StopMovementImmediately();
	BulletProjectile->Deactivate();
}


