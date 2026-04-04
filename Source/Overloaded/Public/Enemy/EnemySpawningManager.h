// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemySplinePath.h"
#include "Components/SplineComponent.h"
#include "GameFramework/Actor.h"
#include "EnemySpawningManager.generated.h"

UCLASS()
class OVERLOADED_API AEnemySpawningManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemySpawningManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	//Getting ref the spline actor / spline variables
	UPROPERTY(EditInstanceOnly, Category = "Enemy Spline Path")
	class AEnemySplinePath* EnemySpineActorRef;
	
	//Getting the enemy spline path
	UPROPERTY()
	USplineComponent* EnemySpline;
	
	//Getting ref to EnemyPawn
	UPROPERTY(EditAnywhere)
	TSubclassOf<class AEnemyPawn> EnemyPawnClass;
	
	//Creating a pool of enemy pawns 
	UPROPERTY()
	TArray<AEnemyPawn*> EnemyPawnPool;
	
	//Getting all active enemy pawns
	UPROPERTY()
	TArray<AEnemyPawn*> ActiveEnemyPawns;
	
	//Creating max enemy pool size
	UPROPERTY(EditAnywhere)
	int32 EnemyPoolSize = 10;
	
	//Creating a timeline with the component
	float TimelineAlpha = 0.f;
	
	UPROPERTY(EditAnywhere)
	float MoveDuration = 0.f;
	
	UFUNCTION()
	void OnEnemyReturned(AEnemyPawn* Enemy);
	
	void InitializeEnemyPool();
	void SpawnFromEnemyPool();

};
