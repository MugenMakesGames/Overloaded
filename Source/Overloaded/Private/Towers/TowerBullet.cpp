// Fill out your copyright notice in the Description page of Project Settings.


#include "Towers/TowerBullet.h"
#include "Enemy/EnemyPawn.h"
#include "GameFramework/ProjectileMovementComponent.h"


// Sets default values
ATowerBullet::ATowerBullet()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Setting up collision
	BulletCollision = CreateDefaultSubobject<USphereComponent>(FName("BulletCollision"));
	BulletCollision->SetupAttachment(RootComponent);

	BulletCollision->SetGenerateOverlapEvents(true);
	BulletCollision->SetCollisionResponseToChannels(ECollisionResponse::ECR_Overlap);

	BulletCollision->OnComponentBeginOverlap.AddDynamic(this, &ATowerBullet::OnEnemyHit);

	BulletProjectile = CreateDefaultSubobject<UProjectileMovementComponent>(FName("BulletProjectile"));
	
	BulletMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("BulletMesh"));
	BulletMesh->SetupAttachment(RootComponent);
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

void ATowerBullet::OnEnemyHit(class UPrimitiveComponent* ThisComp, class AActor* OtherActor,
                              class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                              const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor == EnemyPawnRef)
	{
		//Binding he OnEnemyDamaged delegate
		OnEnemyDamaged.Broadcast(this, 10);
	}
}

