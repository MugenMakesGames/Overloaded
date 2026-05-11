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
	
	if (!EnemySpline) return;

	float SplineLength = EnemySpline->GetSplineLength();
	
	for (int32 i = ActiveEnemyPawns.Num() - 1; i >= 0; --i)
	{
		AEnemyPawn* CurrentEnemy = ActiveEnemyPawns[i];
		
		//Removing any invalid enemy pawn from the pool
		if (!IsValid(CurrentEnemy))
		{
			ActiveEnemyPawns.RemoveAt(i);
			//Starting at the beginning of the loop again so we get the same amount of enemies
			--i;
			continue;
		}

		//Getting the enemy forward and having the DistanceAlongSpline reach the EnemyMoveSpeed number of units along the spline in a second by multiplying it by delta time
		CurrentEnemy->DistanceAlongSpline += EnemyMoveSpeed * DeltaTime;
		
		//Make sure DistanceAlongSpline don't exceed the spline length
		float Distance = FMath::Fmod(CurrentEnemy->DistanceAlongSpline,SplineLength);

		FVector Location = EnemySpline->GetLocationAtDistanceAlongSpline(Distance, ESplineCoordinateSpace::World);

		CurrentEnemy->SetActorLocation(Location);
	}
	
	//Checking if the round has started before spawning
	if (bRoundActive && EnemiesRemainingToSpawn > 0)
	{
		if (!ActiveEnemyPawns.IsEmpty())
		{
			//Getting the most recently spawn enemy
			AEnemyPawn* LastEnemy = ActiveEnemyPawns.Last();
			
			//Checking if the last spawned enemy's distance along the spline is higher than the spawn 
			if (LastEnemy && LastEnemy->DistanceAlongSpline >= EnemySpawnSpacing)
			{
				SpawnFromEnemyPool();
				
				//Decrementing the enemies to spawn so we know how many times we need to get the enemy spawn spacing
				EnemiesRemainingToSpawn--;
			}
		}
	}
}

void AEnemySpawningManager::SpawnFromEnemyPool()
{
	if (EnemyPawnPool.IsEmpty()) return;

	AEnemyPawn* CurrentEnemy = EnemyPawnPool[0];
	EnemyPawnPool.RemoveAt(0);

	if (!CurrentEnemy) return;

	CurrentEnemy->ResetActor();

	//Start enemy at beginning of spline
	CurrentEnemy->DistanceAlongSpline = 0.f;

	FVector Location = EnemySpline->GetLocationAtDistanceAlongSpline(
		0.f,
		ESplineCoordinateSpace::World
	);

	CurrentEnemy->SetActorLocation(Location);

	ActiveEnemyPawns.Add(CurrentEnemy);
}

void AEnemySpawningManager::StartRound(int32 NumberOfEnemies)
{
	//Setting the number of enemies to spawn on starting of the round
	EnemiesRemainingToSpawn = NumberOfEnemies;
	
	bRoundActive = true;

	//Spawning the first enemy to get the distance along the spline
	SpawnFromEnemyPool();
	
	//Decrementing the enemies to spawn so we know how many times we need to get the enemy spawn spacing
	EnemiesRemainingToSpawn--;
}

void AEnemySpawningManager::DestroyEnemy_Implementation(AEnemyPawn* CurrentEnemy)
{
	if (!CurrentEnemy) return;
	
	ActiveEnemyPawns.Remove(CurrentEnemy);
	
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Purple,FString::FromInt(ActiveEnemyPawns.Num()));

	if (!EnemyPawnPool.Contains(CurrentEnemy))
	{
		CurrentEnemy->SetActorHiddenInGame(true);
		CurrentEnemy->SetActorEnableCollision(false);
		
		EnemyPawnPool.Add(CurrentEnemy);
	}
	
	//Resetting the round
	if (ActiveEnemyPawns.Num() <= 0 && EnemiesRemainingToSpawn <= 0)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Purple, TEXT("ALL ENEMIES ARE DESTROYED"));
		
		ResetRound();
	}
}

void AEnemySpawningManager::CreateEnemyPool_Implementation(int32 NumberOfEnemiesToSpawn)
{
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

		if (!EnemyPawnPool.Contains(CurrentEnemy))
		{
			EnemyPawnPool.Add(CurrentEnemy);
		}

		if (ActiveEnemyPawns.Num() <= 0 && EnemiesRemainingToSpawn <= 0)
		{
			ResetRound();
		}
	}
}

void AEnemySpawningManager::ResetRound()
{
	EnemiesRemainingToSpawn = 0;

	ANewOverloadPlayerController* PC = Cast<ANewOverloadPlayerController>(GetWorld()->GetFirstPlayerController());

	Execute_IsRoundOver(PC->CameraSwitchingUI, true);
}