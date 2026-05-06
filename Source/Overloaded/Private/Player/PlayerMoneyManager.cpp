// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/PlayerMoneyManager.h"

#include "NewOverloadPlayerController.h"
#include "Towers.h"

// Sets default values
APlayerMoneyManager::APlayerMoneyManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APlayerMoneyManager::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayerMoneyManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APlayerMoneyManager::UpgradeShootingFrequency()
{
	ATowers* CurrentTower = nullptr;
	
	ANewOverloadPlayerController* PC = Cast<ANewOverloadPlayerController>(GetWorld()->GetFirstPlayerController());
	
	Execute_GetCurrentTower(PC, CurrentTower);
	
	if (!CurrentTower) return;
	
	CurrentTower->TrackingUpgrades(CurrentTower, TEXT("ShootingUpgrades"));
	
	int32& NumberOfUpgrades = CurrentTower->NumberOfUpgrades;
	
	//When max number of upgrades to hit
	if (NumberOfUpgrades == 0)
	{
		return;
	}
	
	NumberOfUpgrades--;
	
	Execute_UpgradeShootingSpeed(CurrentTower, ShootingSpeed, DeativationSpeed, CurrentTower);
	
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, FString::Printf(TEXT("Shooting Speed: %f"), ShootingSpeed));
}
