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
class ANewOverloadPlayerController;
class UBillboardComponent;

USTRUCT(BlueprintType)
struct FNumberOfUpgradesPerType
{
	GENERATED_BODY()
	
	int32 NumberOfShootingSpeedUpgrades = 3;
	
	int32 NumberOfRotationSpeedUpgrades = 3;
	
	int32 NumberOfRadiusUpgrades = 3;
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
	
	UPROPERTY(EditAnywhere, Category = "Tower Placement Area")
	UBillboardComponent* UpgradingTowerIndicator;
	
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
	UPROPERTY(EditInstanceOnly, Category = "Tower Spawner")
	float ShootingSpeed = 1.5f;
	
	UPROPERTY(EditInstanceOnly, Category = "Tower Spawner")
	float DeactivationSpeed = 2.5f;
	
	UPROPERTY(EditInstanceOnly, Category = "Tower Spawner")
	float RotationSpeed = 3.f;
	
	UPROPERTY()
	TMap<ATowers*, FNumberOfUpgradesPerType> NumberOfUpgradesPerTower;
	
	UPROPERTY()
	int32 NumberOfUpgrades = 0;
	
	UFUNCTION()
	void SetTowerSelectText(ATowers* CurrentSelectedTower, ANewOverloadPlayerController* PC);
	
	UFUNCTION()
	void TrackingUpgrades(ATowers* CurrentTower, FName UpgradeType);
	
	//Creating interface function to change the upgrade values
	virtual void UpgradeShootingSpeed_Implementation(float& NewShootingSpeed, float& NewDeactivationSpeed, ATowers* CurrentTower) override;
	
	virtual void UpgradeDetectionRadius_Implementation(float& NewDetectionRadius, ATowers* CurrentTower) override;
	
	virtual void UpgradeRotationSpeed_Implementation(float& NewRotationSpeed, ATowers* CurrentTower) override;
};

