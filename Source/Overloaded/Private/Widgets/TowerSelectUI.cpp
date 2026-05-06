// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/TowerSelectUI.h"
#include "Kismet/GameplayStatics.h"
#include "Player/PlayerMoneyManager.h"

void UTowerSelectUI::NativeConstruct()
{
	Super::NativeConstruct();
	
	UpgradeShootingAndDeactivationSpeed->OnClicked.AddDynamic(this, &UTowerSelectUI::ShootingAndDetectionSpeedUpgraded);
	
	UpgradeDetectionRadius->OnClicked.AddDynamic(this, &UTowerSelectUI::DetectionRadiusUpgraded);
	
	UpgradeDamageAmount->OnClicked.AddDynamic(this, &UTowerSelectUI::DamageAmountUpgraded);
	
	UpgradeRotationSpeed->OnClicked.AddDynamic(this, &UTowerSelectUI::RotationSpeedUpgraded);
	
	MoneyManagerClass = Cast<APlayerMoneyManager>(UGameplayStatics::GetActorOfClass(GetWorld(), 
	APlayerMoneyManager::StaticClass()));
}


void UTowerSelectUI::ShootingAndDetectionSpeedUpgraded()
{
	if (!MoneyManagerClass) return;
	
	MoneyManagerClass->UpgradeShootingFrequency();
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

void UTowerSelectUI::SetSoldOutTextBlock_Implementation(const FText& NewText, FName WhichUpgradeText)
{
	//Updating the text based on the which upgrade button is being pressed
	if (WhichUpgradeText.IsEqual(TEXT("ShootingSpeedText")))
	{
		ShootingSpeedText->SetText(NewText);
	}
	else if (WhichUpgradeText.IsEqual(TEXT("DetectionRadiusText")))
	{
		
	}
	else if (WhichUpgradeText.IsEqual(TEXT("RotationSpeedText")))
	{
		
	}
	else
	{
		
	}
	
}
