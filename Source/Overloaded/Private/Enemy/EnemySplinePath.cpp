// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/EnemySplinePath.h"

// Sets default values
AEnemySplinePath::AEnemySplinePath()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	RootComponent = CreateDefaultSubobject<USceneComponent>("RootComponent");
	
	EnemySplinePath = CreateDefaultSubobject<USplineComponent>(FName("EnemySplinePath"));
	EnemySplinePath->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AEnemySplinePath::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AEnemySplinePath::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

