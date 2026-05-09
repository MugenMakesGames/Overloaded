// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "Interface/InteractionInterface.h"
#include "Interface/TowerUpgradesInterface.h"
#include "Enemy/EnemyPawn.h"
#include "EnemyFinishLine.generated.h"


UCLASS()
class OVERLOADED_API AEnemyFinishLine : public AActor, public IInteractionInterface, public ITowerUpgradesInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemyFinishLine();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UPROPERTY(EditAnywhere, Category = "Finish Line")
	UBoxComponent* EnemyFinishPoint;
	
	UPROPERTY(EditInstanceOnly, Category = "Enemy Spawner")
	class AEnemySpawningManager* EnemySpawnerClass;
	
	UPROPERTY()
	TArray<AEnemyPawn*> FinishedEnemyPool;
	
	UPROPERTY()
	int32 EnemiesSpawned;
	
	
	const int32 MaxEnemiesCrossedLineTillLoss = 10;
	
	UFUNCTION()
	void OnEnemyCrossedLine(class UPrimitiveComponent* ThisComp, class AActor* OtherActor,
					class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
					const FHitResult& SweepResult);
	
	UFUNCTION()
	void UpdateEnemiesCrossed();
	
	UFUNCTION()
	void SetFinishedPool(TArray<AEnemyPawn*>& FinishedPool);
	

};
