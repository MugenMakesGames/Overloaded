// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "InteractionInterface.generated.h"

class AEnemyPawn;

UINTERFACE(BlueprintType)
class OVERLOADED_API UInteractionInterface : public UInterface
{
	GENERATED_BODY()
};

class OVERLOADED_API IInteractionInterface
{
	GENERATED_BODY()

public:
	
	UFUNCTION(BlueprintNativeEvent)
	void ActivateBullet(const FVector& BulletLocation, const FRotator& BulletRotation);
	
	UFUNCTION(BlueprintNativeEvent)
	void EnemyTakeDamage(int32 DamageAmount, AEnemyPawn* CurrentEnemy);
	
	UFUNCTION(BlueprintNativeEvent)
	void DestroyEnemy(AEnemyPawn* CurrentEnemy);
	
	UFUNCTION(BlueprintNativeEvent)
	void CreateEnemyPool(int32 NumberOfEnemiesToSpawn);
	
	UFUNCTION(BlueprintNativeEvent)
	void EnemyCrossedFinishLine(AEnemyPawn* CurrentEnemy, TArray<AEnemyPawn*>& FinishedPool);
	
	UFUNCTION(BlueprintNativeEvent)
	void SpawnTowerAtMouseLocation(class ATowers*& SpawnedTower, const FVector& SpawnLocation);
};
