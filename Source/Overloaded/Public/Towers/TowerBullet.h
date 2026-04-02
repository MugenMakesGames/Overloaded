// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "TowerBullet.generated.h"

//Creating a delegate to apply damage to the enemy when they are hit by a bullet
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEnemyDamagedDelegate, AActor*, DamagedEnemy);

UCLASS
()
class OVERLOADED_API ATowerBullet : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ATowerBullet();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Enemy Pawn Actor Ref")
	class AEnemyPawn* EnemyPawnRef;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	FOnEnemyDamagedDelegate OnEnemyDamaged;

	UPROPERTY(EditAnywhere)
	UBoxComponent* BulletCollision;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* BulletMesh;
	
	UFUNCTION()
	void OnEnemyHit(class UPrimitiveComponent* ThisComp, class AActor* OtherActor,
	                class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
	                const FHitResult& SweepResult);
};
