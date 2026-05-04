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
	TowerClass = Cast<ATowers>(UGameplayStatics::GetActorOfClass(GetWorld(), ATowers::StaticClass()));
	
	if (!TowerClass)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Tower class is not valid"));
		
		return;
	}
	
	Execute_GetCurrentTower(GetOwningPlayer(), TowerClass);
	
	Execute_UpgradeShootingSpeed(TowerClass, 0.1f, 1.f);
}

void UTowerSelectUI::DetectionRadiusUpgraded()
{
	if (!TowerClass)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Tower class is not valid"));
		
		return;
	}
	
	// while (NumberOfUpgrades < 4)
	// {
	// 	NumberOfUpgrades++;
	// 	
	// }
}

void UTowerSelectUI::DamageAmountUpgraded()
{
	if (!TowerClass)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Tower class is not valid"));
		
		return;
	}
	
	// while (NumberOfUpgrades < 4)
	// {
	// 	NumberOfUpgrades++;
	// 	
	// }
}

void UTowerSelectUI::RotationSpeedUpgraded()
{
	if (!TowerClass)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Tower class is not valid"));
		
		return;
	}
	
	// while (NumberOfUpgrades < 4)
	// {
	// 	NumberOfUpgrades++;
	//
	// 	
	// }
}