// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/TowerSelectUI.h"

#include "Towers.h"
#include "Kismet/GameplayStatics.h"

void UTowerSelectUI::NativeConstruct()
{
	Super::NativeConstruct();
	
	UpgradeShootingAndDeactivationSpeed->OnClicked.AddDynamic(this, &UTowerSelectUI::ShootingAndDetectionSpeedUpgraded);
	
	UpgradeDetectionRadius->OnClicked.AddDynamic(this, &UTowerSelectUI::DetectionRadiusUpgraded);
	
	UpgradeDamageAmount->OnClicked.AddDynamic(this, &UTowerSelectUI::DamageAmountUpgraded);
	
	UpgradeRotationSpeed->OnClicked.AddDynamic(this, &UTowerSelectUI::RotationSpeedUpgraded);
	
}


void UTowerSelectUI::ShootingAndDetectionSpeedUpgraded()
{
	float ShootingSpeed = 2;
	float DetectionSpeed = 3;
	
	ATowers* CurrentTower = nullptr;
	
	Execute_GetCurrentTower(GetOwningPlayer(), CurrentTower);
	
	if (!CurrentTower) return;
	
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, CurrentTower->GetName());
	
	CurrentTower->TrackingUpgrades(CurrentTower, TEXT("ShootingUpgrades"));
	
	//Decreasing the delay between each fired bullet
	ShootingSpeed -= 0.5;
	DetectionSpeed -= 0.5;
	
	Execute_UpgradeShootingSpeed(CurrentTower, ShootingSpeed, DetectionSpeed);
}

void UTowerSelectUI::DetectionRadiusUpgraded()
{
	
}

void UTowerSelectUI::DamageAmountUpgraded()
{
	
}

void UTowerSelectUI::RotationSpeedUpgraded()
{
	
}