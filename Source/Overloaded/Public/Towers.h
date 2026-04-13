// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ArrowComponent.h"
#include "GameFramework/Actor.h"
#include "Interface/InteractionInterface.h"
#include "Towers.generated.h"

UCLASS()
class OVERLOADED_API ATowers : public AActor, public IInteractionInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATowers();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	bool bHasBulletHitEnemy;
	
	UPROPERTY()
	ATowerBullet* GetCurrentBullet;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UPROPERTY()
	UStaticMeshComponent* TowerMeshComponent;
	
	UPROPERTY()
	UArrowComponent* TowerShootingPoint;
	
	//Object Pooling 
	UPROPERTY(EditInstanceOnly, Category = "Bullet")
	TSubclassOf<ATowerBullet> BulletClass;
	
	UPROPERTY()
	TArray<ATowerBullet*> BulletPool; 
	
	UPROPERTY()
	TArray<ATowerBullet*> ActiveBulletPool;
	
	UPROPERTY(EditAnywhere)
	int32 BulletPoolAmount = 20;
	
	UFUNCTION()
	void CreateBulletPool();
	
	UFUNCTION()
	void ShootBullet();
	
	//Interface functions
	virtual void RefillBulletPool_Implementation(TArray<ATowerBullet*> ActiveBulletPoolRef, TArray<ATowerBullet*> BulletPoolRef) override;
	
};

