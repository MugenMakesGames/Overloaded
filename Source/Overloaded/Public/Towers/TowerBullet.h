// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "Interface/InteractionInterface.h"
#include "Interface/TowerUpgradesInterface.h"
#include "TowerBullet.generated.h"


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

	UPROPERTY(EditAnywhere)
	USphereComponent* BulletCollision;
	
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* BulletMeshComponent;
	
	UPROPERTY(EditAnywhere)
	class UProjectileMovementComponent* BulletProjectile;
	
	UFUNCTION()
	void OnEnemyHit(class UPrimitiveComponent* ThisComp, class AActor* OtherActor,
	                class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
	                const FHitResult& SweepResult);
	
	UPROPERTY(EditAnywhere)
	float BulletSpeed = 10000.f;
	
	UPROPERTY()
	int32 DamageAmount = 10;
	
	UFUNCTION()
	void DeactivateBullet();
	
	//Interface functions
	virtual void ActivateBullet_Implementation(const FVector& BulletLocation, const FRotator& BulletRotation) override;
	
};
