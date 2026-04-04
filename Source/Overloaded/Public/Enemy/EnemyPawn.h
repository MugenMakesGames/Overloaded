 // Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "Components/SplineComponent.h"
#include "Components/TimelineComponent.h"
#include "GameFramework/Pawn.h"
#include "EnemyPawn.generated.h"

class CurveFloat;
class ATowerBullet;

//Creating a delegate to track when the enemy pawn is destroyed
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEnemyDestoryedDelegate, AEnemyPawn*, Actor);

UCLASS()
class OVERLOADED_API AEnemyPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AEnemyPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	float EnemySplineLength;
	
	UPROPERTY(EditInstanceOnly, Category = "TowerBullet Actor Ref")
	ATowerBullet* TowerBulletRef;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	//Components
	UPROPERTY(EditAnywhere, Category = "Static Mesh")
	UStaticMeshComponent* EnemyStaticMesh;
	
	UPROPERTY(EditAnywhere, Category = "Collision")
	UBoxComponent* EnemyCollision;
	
	//Enemy Health / Functions
	void TakeDamage(AActor* DamagedActor, float DamageAmount);
	
	float CurrentHealth;
	
	UPROPERTY(EditAnywhere, Category = "Enemy Health")
	float MaxHealth;
	
	//Object Pooling variables / Functions / Delegates
	FOnEnemyDestoryedDelegate OnEnemyDestoryed;
	
	void ResetActor();

};
