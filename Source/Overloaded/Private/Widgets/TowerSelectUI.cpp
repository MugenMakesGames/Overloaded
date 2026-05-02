// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/TowerSelectUI.h"

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