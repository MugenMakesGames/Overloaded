// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "Interface/InteractionInterface.h"
#include "Interface/TowerUpgradesInterface.h"
#include "TowerSpawningManager.generated.h"

class ATowers;
class ATowerBullet;
class UArrowComponent;

UCLASS()
class OVERLOADED_API ATowerSpawningManager : public AActor, public IInteractionInterface, public ITowerUpgradesInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATowerSpawningManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UPROPERTY(EditAnywhere, Category = "Tower")
	TSubclassOf<ATowers> TowerClass;
	
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* SpawnerMesh;
	
	UPROPERTY(EditAnywhere, Category = "Tower Placement Area")
	UBoxComponent* TowerSpawningArea;
	
	UPROPERTY(EditAnywhere, Category = "Tower Placement Area")
	UArrowComponent* TowerSpawnLocation;
	
	UPROPERTY(editAnywhere, Category = "Bullet")
	TSubclassOf<ATowerBullet> BulletClass;
	
	//Interface functions
	virtual void SpawnTowerAtMouseLocation_Implementation(ATowers*& SpawnedTower, const FVector& SpawnLocation) override;
};
