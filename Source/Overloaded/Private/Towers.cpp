// Fill out your copyright notice in the Description page of Project Settings.


#include "Towers.h"
#include "Towers/TowerBullet.h"

// Sets default values
ATowers::ATowers()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	TowerMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TowerMeshComponent"));
	TowerMeshComponent->SetupAttachment(RootComponent);
	
	//Creating an arrow component create a point in which the bullet can shoot from
	TowerShootingPoint = CreateDefaultSubobject<UArrowComponent>(TEXT("ShootingPoint"));
	TowerShootingPoint->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ATowers::BeginPlay()
{
	Super::BeginPlay();
	
	CreateBulletPool();
	
	//ShootBullet();
}

// Called every frame
void ATowers::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATowers::ShootBullet()
{
	for (int i = 0; i < BulletPool.Num(); ++i)
	{
		ATowerBullet* Bullet = BulletPool[i];
		
		//Adding the bullets to the active bullet pool when they need to be shot
		ActiveBulletPool.Add(Bullet);
	}
}

void ATowers::CreateBulletPool()
{
	for (int i = 0; i < BulletPoolAmount; ++i)
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
		
		ATowerBullet* CurrentBullet = GetWorld()->SpawnActor<ATowerBullet>(BulletClass, SpawnParams);
		
		if (CurrentBullet)
		{
			CurrentBullet->SetActorEnableCollision(false);
			CurrentBullet->SetActorHiddenInGame(true);
			
			BulletPool.Add(CurrentBullet);
		}
	}
}

void ATowers::RefillBulletPool_Implementation(TArray<ATowerBullet*> ActiveBulletPoolRef, TArray<ATowerBullet*> BulletPoolRef)
{
	
}
