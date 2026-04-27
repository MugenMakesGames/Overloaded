// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "Interface/InteractionInterface.h"
#include "TowerSpawningManager.generated.h"

class ATowers;
class ATowerBullet;

UCLASS()
class OVERLOADED_API ATowerSpawningManager : public AActor, public IInteractionInterface
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
	
	UPROPERTY(EditAnywhere, Category = "Tower Placement Area")
	UBoxComponent* TowerSpawningArea;
	
	UPROPERTY(editAnywhere, Category = "Bullet")
	TSubclassOf<ATowerBullet> BulletClass;
	
	//Tower Bullet Pooling
	UPROPERTY()
	TArray<ATowerBullet*> BulletPool;
	
	UPROPERTY()
	TArray<ATowerBullet*> ActiveBulletPool;
	
	UPROPERTY(EditAnywhere, Category = "Bullet")
	int32 BulletPoolSize = 50;
	
	UFUNCTION()
	void CreateBulletPool();
	
	UFUNCTION()
	void GetBullet(ATowerBullet*& GetBullet);
	
	UFUNCTION()
	void ReturnBullet(ATowerBullet* CurrentBullet);
	
	//Interface functions
	virtual void SpawnTowerAtMouseLocation_Implementation(APlayerController* PC, ATowers*& TowerToDrag) override;
};
