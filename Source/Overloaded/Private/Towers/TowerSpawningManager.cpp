// Fill out your copyright notice in the Description page of Project Settings.


#include "Towers/TowerSpawningManager.h"
#include "Towers.h"

// Sets default values
ATowerSpawningManager::ATowerSpawningManager()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	SpawnerMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SpawnerMesh"));
	RootComponent = SpawnerMesh;
	
	TowerSpawningArea = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawningArea"));
	TowerSpawningArea->SetupAttachment(RootComponent);
	
	TowerSpawnLocation = CreateDefaultSubobject<UArrowComponent>(FName("TowerSpawnLocation"));
	TowerSpawnLocation->SetupAttachment(RootComponent);
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

void ATowerSpawningManager::SpawnTowerAtMouseLocation_Implementation(ATowers*& SpawnedTower, const FVector& SpawnLocation)
{
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	
	if (!TowerSpawnLocation) return;
	
	SpawnedTower = GetWorld()->SpawnActor<ATowers>(TowerClass, SpawnLocation, FRotator::ZeroRotator, SpawnParams);
	
	if (SpawnedTower)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, TEXT("TOWER SPAWNED"));
	}
}



