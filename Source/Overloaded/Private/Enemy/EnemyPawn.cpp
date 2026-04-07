// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/EnemyPawn.h"
#include "Towers/TowerBullet.h"


// Sets default values
AEnemyPawn::AEnemyPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	//Initializing all components 
	EnemyStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("EnemyStaticMesh"));
	EnemyStaticMesh->SetupAttachment(RootComponent);
	
	EnemyCollision = CreateDefaultSubobject<UBoxComponent>("EnemyCollison");
	EnemyCollision->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void AEnemyPawn::BeginPlay()
{
	Super::BeginPlay();
	
	ResetActor();
	
	//Assigning the delegate function to TakeDamage
	if (TowerBulletRef != nullptr)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, "Update func is working");
		TowerBulletRef->OnEnemyDamaged.AddDynamic(this, &AEnemyPawn::TakeDamage);
	}
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


void AEnemyPawn::TakeDamage(AActor* DamagedActor, float DamageAmount)
{
	CurrentHealth -= DamageAmount;
	
	if (CurrentHealth <= 0.f)
	{
		SetActorHiddenInGame(true);
		SetActorEnableCollision(false);
		
		//Binding the on enemy destroyed delegate to this function
		OnEnemyDestoryed.Broadcast(this);
	}
}

void AEnemyPawn::ResetActor()
{
	CurrentHealth = MaxHealth;
	//Resetting the actor to not hidden in game and collision to enabled to be re-used when needed
	SetActorHiddenInGame(false);
	SetActorEnableCollision(true);
}
