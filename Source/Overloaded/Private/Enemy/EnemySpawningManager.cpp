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
	
	InitializeEnemyPool();
	SpawnFromEnemyPool();
	
	//Getting the enemy spline path
	if (EnemySpineActorRef)
	{
		EnemySpline = EnemySpineActorRef->FindComponentByClass<USplineComponent>();
	}
}

// Called every frame
void AEnemySpawningManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	//Checking if the enemy pawn pool is populated
	if (EnemyPawnPool.Num() != 0)
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
		float SpawnOffset = (SplineLength / EnemyPoolSize) * i;
		
		//Fmod is used for if the distance exceeds the spline length
		float Distance = FMath::Fmod((TimelineAlpha * SplineLength) + SpawnOffset, SplineLength);
			
		FVector Location = EnemySpline->GetLocationAtDistanceAlongSpline(
			Distance, 
			ESplineCoordinateSpace::World
			);
		
		CurrentEnemy->SetActorLocation(Location);
		
	}
}

void AEnemySpawningManager::InitializeEnemyPool()
{
	 //Adding enemy pawns to the pool until the enemypoolsize is reached
	for (int i = 0; i < EnemyPoolSize; ++i)
	{
		AEnemyPawn* SpawnedEnemy = GetWorld()->SpawnActor<AEnemyPawn>(EnemyPawnClass);
		SpawnedEnemy->SetActorHiddenInGame(true);
		SpawnedEnemy->SetActorEnableCollision(false);
		
		SpawnedEnemy->OnEnemyDestoryed.AddDynamic(this, &AEnemySpawningManager::OnEnemyReturned);
		EnemyPawnPool.Add(SpawnedEnemy);
	}
}

void AEnemySpawningManager::SpawnFromEnemyPool()
{
	float SplineLength = EnemySpline->GetSplineLength();

	for (int i = 0; i < EnemyPoolSize; ++i)
	{
		//Getting access to the current enemy being index in the enemy pool
		AEnemyPawn* CurrentEnemy = EnemyPawnPool[i];
		
		float Distance = (SplineLength / EnemyPoolSize) * i;
		
		FVector Location = EnemySpline->GetLocationAtDistanceAlongSpline(Distance, 
			ESplineCoordinateSpace::World
			);
		
		CurrentEnemy->SetActorLocation(Location);
		CurrentEnemy->ResetActor();
		
		//Adding the current enemy pawn to the pool of active enemy pawns
		ActiveEnemyPawns.Add(CurrentEnemy);
	}
}

void AEnemySpawningManager::OnEnemyReturned(AEnemyPawn* Enemy)
{
	
}
