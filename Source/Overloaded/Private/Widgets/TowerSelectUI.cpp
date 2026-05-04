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
	ATowers* CurrentTower = nullptr;
	
	Execute_GetCurrentTower(GetOwningPlayer(), CurrentTower);
	
	if (!CurrentTower) return;
	
	CurrentTower->TrackingUpgrades(CurrentTower, TEXT("ShootingUpgrades"));
	
	Execute_UpgradeShootingSpeed(CurrentTower, 0.1f, 1.f);
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