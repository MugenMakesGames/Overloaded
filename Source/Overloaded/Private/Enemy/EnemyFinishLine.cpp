// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/EnemyFinishLine.h"

#include "Enemy/EnemyPawn.h"
#include "Enemy/EnemySpawningManager.h"


// Sets default values
AEnemyFinishLine::AEnemyFinishLine()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	//Setting up collision
	EnemyFinishPoint = CreateDefaultSubobject<UBoxComponent>("Enemy Finish Line");
	EnemyFinishPoint->SetupAttachment(RootComponent);
	EnemyFinishPoint->SetGenerateOverlapEvents(true);
	EnemyFinishPoint->SetCollisionResponseToAllChannels(ECR_Overlap);
	EnemyFinishPoint->OnComponentEndOverlap.AddDynamic(this, &AEnemyFinishLine::OnEnemyCrossedLine);
	

}

// Called when the game starts or when spawned
void AEnemyFinishLine::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemyFinishLine::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEnemyFinishLine::OnEnemyCrossedLine(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	AEnemyPawn* EnemyPawn = Cast<AEnemyPawn>(OtherActor);

	if (EnemyPawn && EnemySpawnerClass)
	{
		//CLEAR POOL?
		//EnemySpawnerClass->EnemyPawnPool.Empty();
	}
}
