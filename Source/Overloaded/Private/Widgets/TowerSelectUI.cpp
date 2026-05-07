// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/TowerSelectUI.h"
#include "Kismet/GameplayStatics.h"
#include "Player/PlayerMoneyManager.h"

void UTowerSelectUI::NativeConstruct()
{
	Super::NativeConstruct();
	
	UpgradeShootingAndDeactivationSpeed->OnClicked.AddDynamic(this, &UTowerSelectUI::ShootingAndDetectionSpeedUpgraded);
	
	UpgradeDetectionRadius->OnClicked.AddDynamic(this, &UTowerSelectUI::DetectionRadiusUpgraded);
	
	UpgradeRotationSpeed->OnClicked.AddDynamic(this, &UTowerSelectUI::RotationSpeedUpgraded);
	
	MoneyManagerClass = Cast<APlayerMoneyManager>(UGameplayStatics::GetActorOfClass(GetWorld(), 
	APlayerMoneyManager::StaticClass()));
}


void UTowerSelectUI::ShootingAndDetectionSpeedUpgraded()
{
	if (!MoneyManagerClass) return;
	
	//Displaying the budget in the TowerSelectUI
	MoneyManagerClass->SetBudget(TEXT("ShootingUpgrade"));
}

void UTowerSelectUI::DetectionRadiusUpgraded()
{
	if (!MoneyManagerClass) return;
	
	MoneyManagerClass->SetBudget(TEXT("RadiusUpgrade"));
}

void UTowerSelectUI::RotationSpeedUpgraded()
{
	if (!MoneyManagerClass) return;
	
	MoneyManagerClass->SetBudget(TEXT("RotationUpgrade"));
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
		DetectionRadiusText->SetText(NewText);
	}
	else if (WhichUpgradeText.IsEqual(TEXT("RotationSpeedText")))
	{
		RotationSpeedText->SetText(NewText);
	}
}
