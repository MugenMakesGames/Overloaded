// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/EnemyPawn.h"

// Sets default values
AEnemyPawn::AEnemyPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	//Initializing all components 
	EnemyStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("EnemyStaticMesh"));
	EnemyStaticMesh->SetupAttachment(RootComponent);
	
	MoveEnemyTimelineComp = CreateDefaultSubobject<UTimelineComponent>(FName("MoveToSplineEnd"));
	

}

// Called when the game starts or when spawned
void AEnemyPawn::BeginPlay()
{
	Super::BeginPlay();
	
	//Binding timeline functions
	MoveEnemyTimelineFinished.BindUFunction(this, FName("MoveEnemyEnd"));
	MoveEnemyTimelineUpdate.BindUFunction(this, FName("MoveEnemyUpdate"));
	
	MoveEnemyTimelineComp->SetTimelinePostUpdateFunc(MoveEnemyTimelineUpdate);
	MoveEnemyTimelineComp->SetTimelineFinishedFunc(MoveEnemyTimelineFinished);
	
	EnemySplineActorRef->
	
}

void AEnemyPawn::MoveEnemyEnd()
{
	
}

void AEnemyPawn::MoveEnemyUpdate()
{
	
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





