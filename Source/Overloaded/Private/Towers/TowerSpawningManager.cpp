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
	
}

// Called every frame
void ATowerSpawningManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATowerSpawningManager::SpawnTowerAtMouseLocation_Implementation(APlayerController* PC, ATowers*& TowerToDrag)
{
	// if (PC)
	// {
	// 	FHitResult HitResult;
	// 	
	// 	//Getting the HisResult for whatever is under the mouse cursor and putting it in an if statement to see if the line trace was successful
	// 	if (PC->GetHitResultUnderCursorByChannel(UEngineTypes::ConvertToTraceType(ECC_Visibility), true,  HitResult))
	// 	{
	// 		FActorSpawnParameters SpawnParams;
	// 		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	// 	
	// 		//Getting the surface contact of the mouse cursor and adding an FVector to avoid clipping
	// 		FVector SpawnLocation = HitResult.ImpactPoint + FVector(0, 0, 30.f);
	// 	
	// 		//Spawning the tower at the hit location
	// 		TowerToDrag = GetWorld()->SpawnActor<ATowers>(TowerClass, SpawnLocation, FRotator::ZeroRotator, SpawnParams);
	// 		
	// 		if (TowerToDrag)
	// 		{
	// 			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green,  TowerToDrag->GetName());
	// 		}
	// 	}
	// }
}



