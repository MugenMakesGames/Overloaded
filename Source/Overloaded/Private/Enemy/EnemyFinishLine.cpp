// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/EnemyFinishLine.h"
#include "NewOverloadPlayerController.h"
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
	EnemyFinishPoint->OnComponentBeginOverlap.AddDynamic(this, &AEnemyFinishLine::OnEnemyCrossedLine);
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

void AEnemyFinishLine::OnEnemyCrossedLine(UPrimitiveComponent* ThisComp, class AActor* OtherActor,
					class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
					const FHitResult& SweepResult)
{
	AEnemyPawn* ActiveEnemyPawn = Cast<AEnemyPawn>(OtherActor);

	if (ActiveEnemyPawn && EnemySpawnerClass)
	{
		ANewOverloadPlayerController* PC = Cast<ANewOverloadPlayerController>(GetWorld()->GetFirstPlayerController());
		
		Execute_EnemyCrossedFinishLine(EnemySpawnerClass, ActiveEnemyPawn, FinishedEnemyPool);
		
		UpdateEnemiesCrossed();
		
		FText NewText = FText::FromString(FString::Printf(TEXT("Enemies Crossed: %d/%d"), FinishedEnemyPool.Num(), EnemiesSpawned));
			
		Execute_SetEnemyCrossedLineText(PC->PlayerBudgetUI, NewText);
	}
}

void AEnemyFinishLine::UpdateEnemiesCrossed()
{
	ANewOverloadPlayerController* PC = Cast<ANewOverloadPlayerController>(GetWorld()->GetFirstPlayerController());
	
	//Setting the correct number of enemies that have crossed the line
	Execute_GetNumberOfEnemiesSpawned(PC->CameraSwitchingUI, EnemiesSpawned);
	
	//You lose
	if (FinishedEnemyPool.Num() == EnemiesSpawned)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Magenta, FString::Printf(TEXT("Enemies Crossed: %d/%d"), FinishedEnemyPool.Num(), EnemiesSpawned));
		
		//Display loss widget
		if (PC->LossScreenUI)
		{
			PC->LossScreenUI->AddToViewport();
		};
	}
}

void AEnemyFinishLine::SetFinishedPool(TArray<AEnemyPawn*> FinishedPool)
{
	FinishedEnemyPool = FinishedPool;
}




