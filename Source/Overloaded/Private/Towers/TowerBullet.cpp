// Fill out your copyright notice in the Description page of Project Settings.


#include "Towers/TowerBullet.h"

#include "Towers.h"
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
	
	BulletCollision->OnComponentBeginOverlap.AddDynamic(this, &ATowerBullet::OnEnemyHit);
	
	BulletMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BulletMeshComponent"));
	BulletMeshComponent->SetupAttachment(RootComponent);
	
	BulletProjectile = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("BulletProjectile"));
	//Setting up the projectile speed
	BulletProjectile->InitialSpeed = 1500.f;
	BulletProjectile->MaxSpeed = 2000.f;
	BulletProjectile->bRotationFollowsVelocity = true;
}

// Called when the game starts or when spawned
void ATowerBullet::BeginPlay()
{
	Super::BeginPlay();

	if (TowerClass)
	{
		TowerClass->OnBulletDestroyed.AddDynamic(this, &ATowerBullet::BulletDestoryed);
	}
}

// Called every frame
void ATowerBullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

void ATowerBullet::OnEnemyHit(class UPrimitiveComponent* ThisComp, class AActor* OtherActor,
                              class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                              const FHitResult& SweepResult)
{
	//Getting the ref to the enemy pawn
	AEnemyPawn* EnemyPawn = Cast<AEnemyPawn>(OtherActor);
	
	if (EnemyPawn)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("BulletDestroyed"));
		
		//Binding he OnEnemyDamaged delegate
		OnEnemyDamaged.Broadcast(this, 10);
		
		//Tracking if the bullet has hit the enemy
	}
}

void ATowerBullet::BulletDestoryed(ATowerBullet* CurrentBullet)
{
	if (bHasBulletHitEnemy == true)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("BulletDestroyed"));
		
		//Setting the actor hidden in game and disabling collision instead of destroying for performance
		CurrentBullet->SetActorHiddenInGame(true);
		CurrentBullet->SetActorEnableCollision(false);
		
		bHasBulletHitEnemy = false;
	}
}