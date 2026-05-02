// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/EnemyPawn.h"
#include "Enemy/EnemySpawningManager.h"


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

void AEnemyPawn::EnemyTakeDamage_Implementation(int32 DamageAmount)
{
	
	CurrentHealth -= DamageAmount;
	
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Purple, FString::Printf(TEXT("DamageDone: %i"), CurrentHealth));
	
	if (CurrentHealth <= 0.f)
	{
		SetActorHiddenInGame(true);
		SetActorEnableCollision(false);
		
		if (EnemySpawningManagerClass && EnemySpawningManagerClass->Implements<UInteractionInterface>())
		{
			Execute_DestroyEnemy(EnemySpawningManagerClass, this);
		}
	}
}
