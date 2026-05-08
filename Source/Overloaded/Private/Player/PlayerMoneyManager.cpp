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
	
	//Setting the current budget to max budget on begin play
	PlayerCurrentBudget = BudgetMaxPerRound;
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
	if (NumberOfUpgrades == 1) return;
	
	NumberOfUpgrades--;
	
	Execute_UpgradeShootingSpeed(CurrentTower, ShootingSpeed, DeactivationSpeed, CurrentTower);
}

void APlayerMoneyManager::UpgradeRadius()
{
	ATowers* CurrentTower = nullptr;
	
	ANewOverloadPlayerController* PC = Cast<ANewOverloadPlayerController>(GetWorld()->GetFirstPlayerController());
	
	Execute_GetCurrentTower(PC, CurrentTower);
	
	if (!CurrentTower) return;
	
	CurrentTower->TrackingUpgrades(CurrentTower, TEXT("DetectionRadiusUpgrades"));
	
	int32& NumberOfUpgrades = CurrentTower->NumberOfUpgrades;
	
	//When max number of upgrades to hit
	if (NumberOfUpgrades == 1) return;
	
	NumberOfUpgrades--;
	
	Execute_UpgradeDetectionRadius(CurrentTower, DetectionRadius, CurrentTower);
}

void APlayerMoneyManager::UpgradeRotation()
{
	ATowers* CurrentTower = nullptr;
	
	ANewOverloadPlayerController* PC = Cast<ANewOverloadPlayerController>(GetWorld()->GetFirstPlayerController());
	
	Execute_GetCurrentTower(PC, CurrentTower);
	
	if (!CurrentTower) return;
	
	CurrentTower->TrackingUpgrades(CurrentTower, TEXT("RotationSpeedUpgrades"));
	
	int32& NumberOfUpgrades = CurrentTower->NumberOfUpgrades;
	
	//When max number of upgrades to hit
	if (NumberOfUpgrades == 1) return;
	
	NumberOfUpgrades--;
	
	Execute_UpgradeRotationSpeed(CurrentTower, RotationSpeed, CurrentTower);
}

void APlayerMoneyManager::SetBudget(FName PurchaseType)
{
	ANewOverloadPlayerController* PC = Cast<ANewOverloadPlayerController>(GetWorld()->GetFirstPlayerController());
	
	if (PurchaseType.IsEqual(TEXT("Tower")))
	{
		if (PlayerCurrentBudget >= 200)
		{
			//PLAYER BUY SOUND EFFECT
			
			//Towers cost 200 to buy and Upgrades cost 50
			PlayerCurrentBudget -= 200;
		
			FText NewBudgetText = FText::FromString(FString::Printf(TEXT("Your Budget: %d"), PlayerCurrentBudget));
		
			Execute_SetBudgetText(PC->PlayerBudgetUI, NewBudgetText);
		}
	}
	else if (PurchaseType.IsEqual(TEXT("ShootingUpgrade")))
	{
		if (PlayerCurrentBudget >= 50)
		{
			//PLAYER BUY SOUND EFFECT
			
			PlayerCurrentBudget -= 50;
			
			FText NewBudgetText = FText::FromString(FString::Printf(TEXT("Your Budget: %d"), PlayerCurrentBudget));
	
			Execute_SetBudgetText(PC->PlayerBudgetUI, NewBudgetText);
			
			UpgradeShootingFrequency();
		}
	}
	else if (PurchaseType.IsEqual(TEXT("RadiusUpgrade")))
	{
		if (PlayerCurrentBudget >= 50)
		{
			//PLAYER BUY SOUND EFFECT
			
			PlayerCurrentBudget -= 50;
			
			FText NewBudgetText = FText::FromString(FString::Printf(TEXT("Your Budget: %d"), PlayerCurrentBudget));
	
			Execute_SetBudgetText(PC->PlayerBudgetUI, NewBudgetText);
		
			UpgradeRadius();
		}
	}
	else if (PurchaseType.IsEqual(TEXT("RotationUpgrade")))
	{
		if (PlayerCurrentBudget >= 50)
		{
			//PLAYER BUY SOUND EFFECT
			
			PlayerCurrentBudget -= 50;
			
			FText NewBudgetText = FText::FromString(FString::Printf(TEXT("Your Budget: %d"), PlayerCurrentBudget));
	
			Execute_SetBudgetText(PC->PlayerBudgetUI, NewBudgetText);
			
			UpgradeRotation();
		}
	}
}

void APlayerMoneyManager::AddToBudgetOnRoundWin()
{
	ANewOverloadPlayerController* PC = Cast<ANewOverloadPlayerController>(GetWorld()->GetFirstPlayerController());
	
	//Adding money to buy towers and upgrades
	PlayerCurrentBudget += 600;
	
	FText NewBudgetText = FText::FromString(FString::Printf(TEXT("Your Budget: %d"), PlayerCurrentBudget));
		
	Execute_SetBudgetText(PC->PlayerBudgetUI, NewBudgetText);
}


