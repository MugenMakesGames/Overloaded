// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Interface/TowerUpgradesInterface.h"
#include "TowerSelectUI.generated.h"

class APlayerMoneyManager;
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
	UButton* UpgradeRotationSpeed;
	
	UPROPERTY(meta = (BindWidget), BlueprintReadOnly)
	UTextBlock* ShootingSpeedText;
	
	UPROPERTY(meta = (BindWidget), BlueprintReadOnly)
	UTextBlock* DetectionRadiusText;
	
	UPROPERTY(meta = (BindWidget), BlueprintReadOnly)
	UTextBlock* RotationSpeedText;
	
	UFUNCTION(BlueprintCallable)
	void ShootingAndDetectionSpeedUpgraded();
	
	UFUNCTION(blueprintCallable)
	void DetectionRadiusUpgraded();
	
	UFUNCTION(BlueprintCallable)
	void RotationSpeedUpgraded();
	
	UPROPERTY()
	APlayerMoneyManager* MoneyManagerClass;
	
	//Interface functions
	virtual void SetSoldOutTextBlock_Implementation(const FText& NewText, FName WhichUpgradeText) override;
};
