// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "TowerUpgradesInterface.generated.h"

class AEnemyPawn;
class USphereComponent;
class ATowerBullet;

// This class does not need to be modified.
UINTERFACE(BlueprintType)
class OVERLOADED_API UTowerUpgradesInterface : public UInterface
{
	GENERATED_BODY()
};

class OVERLOADED_API ITowerUpgradesInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	
	UFUNCTION(BlueprintNativeEvent)
	void UpgradeShootingSpeed(float& NewShootingSpeed, float& NewDeactivationSpeed, class ATowers* CurrentTower);
	
	UFUNCTION(blueprintNativeEvent)
	void UpgradeDetectionRadius(float& NewDetectionRadius, ATowers* CurrentTower);
	
	UFUNCTION(BlueprintNativeEvent)
	void UpgradeRotationSpeed(float& NewRotationSpeed, ATowers* CurrentTower);
	
	UFUNCTION(BlueprintNativeEvent)
	void GetCurrentTower(class ATowers*& CurrentTower);
	
	UFUNCTION(BlueprintNativeEvent)
	void SetBudgetText(const FText& NewText);
	
	UFUNCTION(BlueprintNativeEvent)
	void SetEnemyCrossedLineText(const FText& NewText);
	
	UFUNCTION(BlueprintNativeEvent)
	void SetSoldOutTextBlock(const FText& NewText, FName WhichUpgradeText);
	
	UFUNCTION(blueprintNativeEvent)
	void IsRoundOver(bool bIsRoundOver);
	
  };

