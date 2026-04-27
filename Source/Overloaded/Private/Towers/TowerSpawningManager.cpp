// Fill out your copyright notice in the Description page of Project Settings.


#include "Towers/TowerSpawningManager.h"
#include "Towers.h"
#include "Towers/TowerBullet.h"

// Sets default values
ATowerSpawningManager::ATowerSpawningManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ATowerSpawningManager::BeginPlay()
{
	Super::BeginPlay();
	
	CreateBulletPool();
}

// Called every frame
void ATowerSpawningManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATowerSpawningManager::CreateBulletPool()
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
			//CurrentBullet->DeactivateBullet();
			BulletPool.Add(CurrentBullet);
		}
	}
}

void ATowerSpawningManager::GetBullet(ATowerBullet*& GetBullet)
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

void ATowerSpawningManager::ReturnBullet(ATowerBullet* CurrentBullet)
{
	CurrentBullet->DeactivateBullet();
	
	ActiveBulletPool.Remove(CurrentBullet);
	BulletPool.Add(CurrentBullet);
}


void ATowerSpawningManager::SpawnTowerAtMouseLocation_Implementation(APlayerController* PC, ATowers*& TowerToDrag)
{
	if (PC)
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
		
		//Spawning the tower at the hit location
		TowerToDrag = GetWorld()->SpawnActor<ATowers>(TowerClass,FVector::ZeroVector,FRotator::ZeroRotator,
		SpawnParams);
			
		if (TowerToDrag)
		{
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green,  TowerToDrag->GetName());
		}
	}
}



