// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/EnemySpawningManager.h"
#include "Enemy/EnemyPawn.h"
#include "Enemy/EnemySplinePath.h"

// Sets default values
AEnemySpawningManager::AEnemySpawningManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AEnemySpawningManager::BeginPlay()
{
	Super::BeginPlay();
	
	//Getting the enemy spline path
	if (EnemySplineActorRef)
	{
		EnemySpline = EnemySplineActorRef->FindComponentByClass<USplineComponent>();
	}
	
	InitializeEnemyPool();
	SpawnFromEnemyPool();
}

// Called every frame
void AEnemySpawningManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (EnemySpline)
	{
		//Checking if the enemy pawn pool is populated
		if (!ActiveEnemyPawns.IsEmpty())
		{
			//Getting the amount of time pasted every frame 
			//Dividing by move duration (5) so that it takes 5 seconds for the timeline alpha to get from 0 to 1.0 instead of 1
			TimelineAlpha += DeltaTime / MoveDuration;
		}
	
		//Looping the timeline 
		if (TimelineAlpha >= 1.0f)
		{
			TimelineAlpha -= 1.0f;
		}
	
		float SplineLength  = EnemySpline->GetSplineLength();
		
		for (int i = 0; i < ActiveEnemyPawns.Num(); ++i)
		{
			AEnemyPawn* CurrentEnemy = ActiveEnemyPawns[i];
		
			//Checking if the current enemy variable is null and continuing if it is
			if (!CurrentEnemy) continue;
		
			//Getting the distance the new next enemy pawn should spawn after the other
			float SpawnOffset =  EnemySpacing * i;
		
			//Fmod is used for if the distance exceeds the spline length
			float Distance = FMath::Fmod((TimelineAlpha * SplineLength) + SpawnOffset, SplineLength);
			
			FVector Location = EnemySpline->GetLocationAtDistanceAlongSpline(
				Distance, 
				ESplineCoordinateSpace::World
				);
		
			CurrentEnemy->SetActorLocation(Location);
		}
	}
}

void AEnemySpawningManager::InitializeEnemyPool()
{
	 //Adding enemy pawns to the pool until the enemypoolsize is reached
	for (int i = 0; i < EnemyPoolSize; ++i)
	{
		if (EnemyPawnClass)
		{
			//Making sure collision doesn't block the enemy spawning
			FActorSpawnParameters Params;
			Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

			AEnemyPawn* SpawnedEnemy = GetWorld()->SpawnActor<AEnemyPawn>(EnemyPawnClass, Params);

			if (SpawnedEnemy)
			{
				SpawnedEnemy->SetActorHiddenInGame(true);
				SpawnedEnemy->SetActorEnableCollision(false);
				
				EnemyPawnPool.Add(SpawnedEnemy);
			}
		}
	}
}

void AEnemySpawningManager::SpawnFromEnemyPool()
{
	float SplineLength = EnemySpline->GetSplineLength();
	
	//Tracking the spawn index 
	int SpawnIndex = 0;
	//Making sure the enemy pool size and enemy pawn pool values don't desync
	int TargetCount = FMath::Min(EnemyPoolSize, EnemyPawnPool.Num());
	
	//Looping until active all enemies in enemy pawn are in active enemy pawns
	while (ActiveEnemyPawns.Num() < EnemyPoolSize && EnemyPawnPool.Num() > 0)
	{
		
		AEnemyPawn* CurrentEnemy = EnemyPawnPool[0];
		EnemyPawnPool.RemoveAt(0);
		

		if (!CurrentEnemy) continue;

		float Distance = (SplineLength / TargetCount) * SpawnIndex;

		FVector Location = EnemySpline->GetLocationAtDistanceAlongSpline(
			Distance,
			ESplineCoordinateSpace::World
		);

		CurrentEnemy->SetActorHiddenInGame(false);
		CurrentEnemy->SetActorEnableCollision(true);
		
		CurrentEnemy->SetActorLocation(Location);

		ActiveEnemyPawns.Add(CurrentEnemy);
		
		//Incrementing index
		SpawnIndex++;
	}
}


void AEnemySpawningManager::DestroyEnemy_Implementation(AEnemyPawn* CurrentEnemy)
{
	if (!CurrentEnemy) return;
	
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("ITS RUNNING"));
	
	//Removing the current enemy pawn from the active pawns 
	if (ActiveEnemyPawns.Contains(CurrentEnemy))
	{
		ActiveEnemyPawns.Remove(CurrentEnemy);
	}
	
	//Adding it back to the enemy pawn pool
	if (!EnemyPawnPool.Contains(CurrentEnemy))
	{
		EnemyPawnPool.Add(CurrentEnemy);
	}
}
