// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "Interface/InteractionInterface.h"
#include "EnemyFinishLine.generated.h"

class AEnemyPawn;

UCLASS()
class OVERLOADED_API AEnemyFinishLine : public AActor, public IInteractionInterface
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
	
	UPROPERTY()
	TArray<AEnemyPawn*> FinishedEnemyPool;
	
	UFUNCTION()
	void OnEnemyCrossedLine(class UPrimitiveComponent* ThisComp, class AActor* OtherActor,
					class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
					const FHitResult& SweepResult);

};
