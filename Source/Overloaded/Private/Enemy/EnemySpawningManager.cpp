// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/EnemySpawningManager.h"

#include "NewOverloadPlayerController.h"
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
		
			//Fmod is used for if the distance exceeds the spline length and if it does reset it original enemy offset
			float Distance = FMath::Fmod((TimelineAlpha * SplineLength) + CurrentEnemy->EnemyOffset, SplineLength);
			
			FVector Location = EnemySpline->GetLocationAtDistanceAlongSpline(
				Distance, 
				ESplineCoordinateSpace::World
				);
		
			CurrentEnemy->SetActorLocation(Location);
		}
	}
}

void AEnemySpawningManager::SpawnFromEnemyPool()
{
	float SplineLength = EnemySpline->GetSplineLength();
	
	//Engine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("ITS RUNNING"));
	
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
		
		//Giving each spawned enemy their own permanent spacing
		CurrentEnemy->EnemyOffset = EnemySpacing * SpawnIndex;
		
		//Making sure the enemies offset doesn't exceed the spline's length
		float Distance = FMath::Fmod(CurrentEnemy->EnemyOffset, SplineLength);
		
		FVector Location = EnemySpline->GetLocationAtDistanceAlongSpline(
			Distance,
			ESplineCoordinateSpace::World
		);

		CurrentEnemy->ResetActor();
		CurrentEnemy->SetActorLocation(Location);

		ActiveEnemyPawns.Add(CurrentEnemy);
		
		//Incrementing index
		SpawnIndex++;
	}
}

void AEnemySpawningManager::DestroyEnemy_Implementation(AEnemyPawn* CurrentEnemy)
{
	if (!CurrentEnemy) return;

	ActiveEnemyPawns.Remove(CurrentEnemy);

	if (!EnemyPawnPool.Contains(CurrentEnemy))
	{
		EnemyPawnPool.Add(CurrentEnemy);
	}

	//Reset the timeline if all enemies are destroyed
	if (ActiveEnemyPawns.Num() <= 0)
	{
		ResetTimeline();
	}
}

void AEnemySpawningManager::CreateEnemyPool_Implementation(int32 NumberOfEnemiesToSpawn)
{
	EnemyPoolSize = NumberOfEnemiesToSpawn;
	
	//Adding enemy pawns to the pool until the enemypoolsize is reached
	for (int i = 0; i < NumberOfEnemiesToSpawn; ++i)
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

void AEnemySpawningManager::EnemyCrossedFinishLine_Implementation(class AEnemyPawn* CurrentEnemy, TArray<AEnemyPawn*>& FinishedPool)
{
	//Removing the current enemy pawn from the active pawns when they cross the finish line
	if (ActiveEnemyPawns.Contains(CurrentEnemy))
	{
		ActiveEnemyPawns.Remove(CurrentEnemy);
		
		CurrentEnemy->SetActorEnableCollision(false);
		CurrentEnemy->SetActorHiddenInGame(true);
		
		//Adding it to the finish pool
		FinishedPool.Add(CurrentEnemy);
	}
}

void AEnemySpawningManager::ResetTimeline()
{
	if (ActiveEnemyPawns.Num() <= 0)
	{
		TimelineAlpha = 1.f;
		
		ANewOverloadPlayerController* PC = Cast<ANewOverloadPlayerController>(GetWorld()->GetFirstPlayerController());
		
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("ROUND IS OVER"));
			
		Execute_IsRoundOver(PC->CameraSwitchingUI, true);
	}
}