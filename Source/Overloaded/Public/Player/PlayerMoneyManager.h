// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interface/TowerUpgradesInterface.h"
#include "PlayerMoneyManager.generated.h"

class ATowers;
class anewOverloadPlayerController;

UCLASS()
class OVERLOADED_API APlayerMoneyManager : public AActor, public ITowerUpgradesInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APlayerMoneyManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	const int32 BudgetMaxPerRound = 3000;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UPROPERTY()
	int32 PlayerCurrentBudget = 0;
	
	void AddToBudgetOnRoundWin();
	
	//Upgrade functions and variables
	UFUNCTION()
	void UpgradeShootingFrequency();
	
	UFUNCTION()
	void UpgradeRadius();
	
	UFUNCTION()
	void UpgradeRotation();
	
	UPROPERTY()
	float ShootingSpeed;
	
	UPROPERTY()
	float DeactivationSpeed;
	
	UPROPERTY()
	float DetectionRadius;
	
	UPROPERTY()
	float RotationSpeed;
	
	UFUNCTION()
	void SetBudget(FName PurchaseType);
	
	UPROPERTY(editAnywhere, BlueprintReadWrite, Category = "Audio")
	USoundBase* UpgradeSoldOutSound;
	
	UPROPERTY()
	UAudioComponent* UpgradeSoldOutAudioComp;
	
	UPROPERTY(editAnywhere, BlueprintReadWrite, Category = "Audio")
	USoundBase* ClickSound;
	
	UPROPERTY()
	UAudioComponent* ClickSoundAudioComp;
	
	UPROPERTY(editAnywhere, BlueprintReadWrite, Category = "Audio")
	USoundBase* UpgradePurchaseSound;
	
	UPROPERTY()
	UAudioComponent* UpgradePurchaseSoundAudioComp;
	
	void PlayPurchaseSound();
	
	void PlayClickSound();
	
	void PlaySoldOutSound();
	
};
