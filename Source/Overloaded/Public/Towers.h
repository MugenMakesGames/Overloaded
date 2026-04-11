// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ArrowComponent.h"
#include "GameFramework/Actor.h"
#include "Towers.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnBulletDestroyed, ATowerBullet*, CurrentBullet);

UCLASS()
class OVERLOADED_API ATowers : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATowers();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UPROPERTY()
	UStaticMeshComponent* TowerMeshComponent;
	
	UPROPERTY()
	UArrowComponent* TowerShootingPoint;
	
	FOnBulletDestroyed OnBulletDestroyed;
	
	//Object Pooling 
	UPROPERTY(EditInstanceOnly, Category = "Bullet")
	TSubclassOf<ATowerBullet> BulletClass;
	
	UFUNCTION()
	void ShootBullet();
};
