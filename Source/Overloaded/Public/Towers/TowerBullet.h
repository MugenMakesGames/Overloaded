// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "Interface/InteractionInterface.h"
#include "TowerBullet.generated.h"


//Creating a delegate to apply damage to the enemy when they are hit by a bullet
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnEnemyDamagedDelegate, AActor*, DamagedEnemy, float, DamageAmount);

UCLASS
()
class OVERLOADED_API ATowerBullet : public AActor, public IInteractionInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ATowerBullet();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UPROPERTY(EditInstanceOnly, Category = "Tower")
	class ATowers* TowerClass;
	
	UPROPERTY(BlueprintCallable)
	FOnEnemyDamagedDelegate OnEnemyDamaged;

	UPROPERTY(EditAnywhere)
	USphereComponent* BulletCollision;
	
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* BulletMeshComponent;
	
	UPROPERTY()
	class UProjectileMovementComponent* BulletProjectile;
	
	UFUNCTION()
	void OnEnemyHit(class UPrimitiveComponent* ThisComp, class AActor* OtherActor,
	                class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
	                const FHitResult& SweepResult);
	
	UPROPERTY(EditAnywhere)
	float BulletSpeed = 2000.f;
	
	UFUNCTION()
	void DeactivateBullet();
	
	bool bIsBulletActive;
	
	//Interface functions
	virtual void ActivateBullet_Implementation(const FVector& BulletLocation, const FRotator& BulletRotation) override;
	
	
	
};
