// Fill out your copyright notice in the Description page of Project Settings.


#include "Towers/TowerBulletHandler.h"
#include "Towers/TowerBullet.h"

// Sets default values
ATowerBulletHandler::ATowerBulletHandler()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ATowerBulletHandler::BeginPlay()
{
	Super::BeginPlay();
	
	CreateBulletPool();
}

// Called every frame
void ATowerBulletHandler::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATowerBulletHandler::CreateBulletPool()
{
	if (!BulletClass)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("BULLET CLASS IS NULL"));
	}

	for (int i = 0; i < BulletPoolSize; ++i)
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

		ATowerBullet* CurrentBullet = GetWorld()->SpawnActor<ATowerBullet>(BulletClass, SpawnParams);

		if (CurrentBullet)
		{
			CurrentBullet->DeactivateBullet();
			BulletPool.Add(CurrentBullet);
		}
	}
}

void ATowerBulletHandler::GetBullet(ATowerBullet*& GetBullet)
{
	GetBullet = nullptr;

	if (BulletPool.Num() == 0) return;

	GetBullet = BulletPool[0];

	if (!GetBullet)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("BULLET IS NOT VALID"));
		return;
	}

	BulletPool.RemoveAt(0);
	ActiveBulletPool.Add(GetBullet);
}

void ATowerBulletHandler::ReturnBullet(ATowerBullet* CurrentBullet)
{
	CurrentBullet->DeactivateBullet();

	ActiveBulletPool.Remove(CurrentBullet);
	BulletPool.Add(CurrentBullet);
}
