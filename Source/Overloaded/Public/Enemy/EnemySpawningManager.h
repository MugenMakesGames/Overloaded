// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
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
	UPROPERTY(EditAnywhere, Category = "Enemy")
	class AEnemySplinePath* EnemySplineActorRef;
	
	//Getting the enemy spline path
	UPROPERTY()
	USplineComponent* EnemySpline;
	
	//Getting ref to EnemyPawn
	UPROPERTY(EditAnywhere, Category = "Enemy")
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
	
	//Creating a timeline using tick
	float TimelineAlpha = 0.f;
	
	//Creating variables to controll enemy speed and spacing
	UPROPERTY(EditAnywhere, Category = "Enemy Movement")
	float MoveDuration = 10.f;
	
	UPROPERTY(EditAnywhere, Category = "Enemy Movement")
	int32 EnemySpacing = 200;
	
	UFUNCTION()
	void OnEnemyReturned(AEnemyPawn* Enemy);
	
	void InitializeEnemyPool();
	void SpawnFromEnemyPool();

};
