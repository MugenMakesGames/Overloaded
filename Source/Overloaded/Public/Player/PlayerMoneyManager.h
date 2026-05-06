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
	
	const int32 BudgetMaxPerRound = 1000;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UPROPERTY()
	int32 PlayerCurrentBudget = 0;
	
	UFUNCTION()
	void UpgradeShootingFrequency();
	
	UPROPERTY()
	float ShootingSpeed;
	
	UPROPERTY()
	float DeactivationSpeed;
	
	UFUNCTION()
	void GetBudget();
	
	//Interface Functions
	
};
