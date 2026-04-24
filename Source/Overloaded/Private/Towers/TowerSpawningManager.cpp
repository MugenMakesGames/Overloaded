// Fill out your copyright notice in the Description page of Project Settings.


#include "Towers/TowerSpawningManager.h"

#include "Towers.h"
#include "Components/BoxComponent.h"

// Sets default values
ATowerSpawningManager::ATowerSpawningManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	TowerSpawningArea = CreateDefaultSubobject<UBoxComponent>(TEXT("Tower Placement Area"));
	TowerSpawningArea->SetupAttachment(RootComponent);
	
	TowerSpawningArea->SetGenerateOverlapEvents(true);
	TowerSpawningArea->SetCollisionResponseToAllChannels(ECR_Overlap);
	TowerSpawningArea->OnComponentBeginOverlap.AddDynamic(this, &ATowerSpawningManager::OnTowerInPlacementRadius);
	TowerSpawningArea->OnComponentEndOverlap.AddDynamic(this, &ATowerSpawningManager::OnTowerOutOfPlacementRadius);
	

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

void ATowerSpawningManager::OnTowerInPlacementRadius(class UPrimitiveComponent* ThisComp, class AActor* OtherActor,class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,const FHitResult& SweepResult)
{
	if (Cast<ATowers>(OtherActor))
	{
		IsTowerInPlacementRadius = true;
	}
}

void ATowerSpawningManager::OnTowerOutOfPlacementRadius(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (Cast<ATowers>(OtherActor))
	{
		IsTowerInPlacementRadius = false;
	}
}
