// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "EnemyFinishLine.generated.h"

class AEnemyPawn;

UCLASS()
class OVERLOADED_API AEnemyFinishLine : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemyFinishLine();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UPROPERTY(EditAnywhere, Category = "Finish Line")
	UBoxComponent* EnemyFinishPoint;
	
	UPROPERTY(EditInstanceOnly, Category = "Enemy Spawner")
	class AEnemySpawningManager* EnemySpawnerClass;
	
	UFUNCTION()
	void OnEnemyCrossedLine(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

};
