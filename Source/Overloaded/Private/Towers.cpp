// Fill out your copyright notice in the Description page of Project Settings.


#include "Towers.h"

#include "Towers/TowerBullet.h"

// Sets default values
ATowers::ATowers()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATowers::BeginPlay()
{
	Super::BeginPlay();
	
	InitializeBulletPool();
	
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("SPLINE IS WORKING AT BEGINNING"));
	
}

// Called every frame
void ATowers::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

void ATowers::InitializeBulletPool()
{
	if (BulletClass) 
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Bullet Pool Spawned"));
		
		for (int i = 0; i < BulletPoolAmount; ++i)
		{
			FActorSpawnParameters SpawnParams;
			SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
		
			ATowerBullet* CurrentBullet = GetWorld()->SpawnActor<ATowerBullet>(BulletClass, SpawnParams);
		
			if (CurrentBullet != nullptr)
			{
				BulletPool.Add(CurrentBullet);
			
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Bullet Pool Spawned"));
			}
		}
	};
}

