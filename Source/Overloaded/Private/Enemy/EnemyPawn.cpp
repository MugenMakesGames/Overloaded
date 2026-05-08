// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/EnemyPawn.h"
#include "Enemy/EnemySpawningManager.h"
#include "Kismet/GameplayStatics.h"


class ANewOverloadPlayerController;
// Sets default values
AEnemyPawn::AEnemyPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	//Initializing all components 
	EnemyStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("EnemyStaticMesh"));
	EnemyStaticMesh->SetupAttachment(RootComponent);
	
	EnemyCollision = CreateDefaultSubobject<UBoxComponent>("EnemyCollison");
	EnemyCollision->SetGenerateOverlapEvents(true);
	EnemyCollision->SetCollisionResponseToAllChannels(ECR_Overlap);
	EnemyCollision->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AEnemyPawn::BeginPlay()
{
	Super::BeginPlay();
	
	ResetActor();
	
	EnemySpawningManagerClass = Cast<AEnemySpawningManager>(UGameplayStatics::GetActorOfClass(GetWorld(),
	AEnemySpawningManager::StaticClass()));
}

// Called every frame
void AEnemyPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AEnemyPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}


void AEnemyPawn::ResetActor()
{
	CurrentHealth = MaxHealth;
	//Resetting the actor to not hidden in game and collision to enabled to be re-used when needed
	SetActorHiddenInGame(false);
	SetActorEnableCollision(true);
}

void AEnemyPawn::EnemyTakeDamage_Implementation(int32 DamageAmount, AEnemyPawn* CurrentEnemy)
{
	if (!CurrentEnemy) return;
	
	CurrentEnemy->CurrentHealth -= DamageAmount;
	
	if (CurrentEnemy->CurrentHealth <= 0)
	{
		CurrentEnemy->SetActorHiddenInGame(true);
		CurrentEnemy->SetActorEnableCollision(false);
		
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Magenta, CurrentEnemy->GetName());
		
		if (EnemySpawningManagerClass && EnemySpawningManagerClass->Implements<UInteractionInterface>())
		{
			Execute_DestroyEnemy(EnemySpawningManagerClass, CurrentEnemy);
			
			//Resetting the timeline so the enemy start at the beginning of the spline
			//EnemySpawningManagerClass->ResetTimeline();
		}
	}
}
