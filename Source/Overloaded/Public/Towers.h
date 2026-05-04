// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ArrowComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "Interface/InteractionInterface.h"
#include "Interface/TowerUpgradesInterface.h"
#include "Towers.generated.h"

class ATowerBulletHandler;

struct FNumberOfUpgradesPerType
{
	int32 NumberOfShootingSpeedUpgrades = 3;
	
	int32 NumberOfRotationSpeedUpgrades = 3;
	
	int32 NumberOfRadiusUpgrades = 3;
	
	int32 NumberOfDamageUpgrades = 3;
};

UCLASS()
class OVERLOADED_API ATowers : public AActor, public IInteractionInterface, public ITowerUpgradesInterface
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
	
	UPROPERTY(EditDefaultsOnly, Category = "Tower Spawner")
	ATowerBulletHandler* BulletPoolClass;
	
	UPROPERTY(EditInstanceOnly)
	TArray<AActor*> EnemiesInRadius;
	
	UPROPERTY(EditInstanceOnly)
	AActor* ClosestEnemy;
	
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* TowerMeshComponent;
	
	UPROPERTY(EditAnywhere, Category = "Detection Radius")
	USphereComponent* EnemyDetectionRadius;
	
	//Creating a FVector variable to store where the bullet should go when deactivated
	UPROPERTY(EditAnywhere, Category = "Bullet")
	FVector ResetBulletLocation;
	
	UPROPERTY(EditAnywhere)
	UArrowComponent* TowerShootingPoint;
	
	//Object Pooling 
	UPROPERTY(EditDefaultsOnly, Category = "Bullet")
	TSubclassOf<class ATowerBullet> BulletClass;
	
	UFUNCTION()
	void AddToActiveBulletPool();
	
	UFUNCTION()
	void ShootBullet(ATowerBullet* CurrentBulletToShoot);
	
	UFUNCTION()
	void OnEnemyInRadius(class UPrimitiveComponent* ThisComp, class AActor* OtherActor,
					class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
					const FHitResult& SweepResult);
	
	UFUNCTION()
	void OnEnemyOutOfRadius(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, 
		int32 OtherBodyIndex);
	
	//Enemy Tracking
	UFUNCTION()
	void ChooseClosestEnemyInRadius();
	
	UFUNCTION()
	void RotateTowardsEnemy(AActor* TargetEnemy, float DeltaTim);
	
	//Getting upgrade variables
	UPROPERTY()
	float ShootingSpeed = 2.f;
	
	UPROPERTY()
	float DeactivationSpeed = 3.f;
	
	UPROPERTY()
	float RotationSpeed = 2.f;
	
	//Creating interface function to change the upgrade values
	virtual void UpgradeShootingSpeed_Implementation(float NewShootingSpeed, float NewDeactivationSpeed) override;
	
	
};

