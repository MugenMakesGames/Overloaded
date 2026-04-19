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
	
	FTimerHandle BulletShootingFrequency;
	
	int32 BulletCount = 0;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UPROPERTY()
	UStaticMeshComponent* TowerMeshComponent;
	
	//Creating a FVector variable to store where the bullet should go when deactivated
	UPROPERTY(EditAnywhere, Category = "Bullet")
	FVector ResetBulletLocation;
	
	UPROPERTY()
	UArrowComponent* TowerShootingPoint;
	
	//Object Pooling 
	UPROPERTY(EditInstanceOnly, Category = "Bullet")
	TSubclassOf<class ATowerBullet> BulletClass;
	
	UPROPERTY()
	TArray<ATowerBullet*> BulletPool; 
	
	UPROPERTY()
	TArray<ATowerBullet*> ActiveBulletPool;
	
	UPROPERTY(EditAnywhere)
	int32 BulletPoolAmount = 20;
	
	UFUNCTION()
	void CreateBulletPool();
	
	UFUNCTION()
	void AddToActiveBulletPool();
	
	UFUNCTION()
	void ShootBullet(ATowerBullet* CurrentBulletToShoot);
	
};

