// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Interface/TowerUpgradesInterface.h"
#include "TowerSelectUI.generated.h"

/**
 * 
 */
UCLASS()
class OVERLOADED_API UTowerSelectUI : public UUserWidget, public ITowerUpgradesInterface
{
	GENERATED_BODY()
	
	virtual void NativeConstruct() override;
	
public:
	
	//Tower Upgrades
	UPROPERTY(meta = (BindWidget), BlueprintReadOnly)
	UButton* UpgradeShootingAndDeactivationSpeed;
	
	UPROPERTY(meta = (BindWidget), BlueprintReadOnly)
	UButton* UpgradeDetectionRadius;
	
	UPROPERTY(meta = (BindWidget), BlueprintReadOnly)
	UButton* UpgradeDamageAmount;
	
	UPROPERTY(meta = (BindWidget), BlueprintReadOnly)
	UButton* UpgradeRotationSpeed;
	
	UFUNCTION(BlueprintCallable)
	void ShootingAndDetectionSpeedUpgraded();
	
	UFUNCTION(blueprintCallable)
	void DetectionRadiusUpgraded();
	
	UFUNCTION(BlueprintCallable)
	void DamageAmountUpgraded();
	
	UFUNCTION(BlueprintCallable)
	void RotationSpeedUpgraded();
};
