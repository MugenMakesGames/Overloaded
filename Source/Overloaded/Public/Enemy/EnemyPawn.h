 // Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Pawn.h"
#include "Interface/InteractionInterface.h"
#include "Interface/TowerUpgradesInterface.h"
#include "EnemyPawn.generated.h"

class CurveFloat;
class ATowerBullet;



UCLASS()
class OVERLOADED_API AEnemyPawn : public APawn, public IInteractionInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AEnemyPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	float EnemySplineLength;
	
	int32 CurrentHealth;
	
	const int32 MaxHealth = 10;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	UPROPERTY()
	class AEnemySpawningManager* EnemySpawningManagerClass;
	
	//Components
	UPROPERTY(EditAnywhere, Category = "Static Mesh")
	UStaticMeshComponent* EnemyStaticMesh;
	
	UPROPERTY(EditAnywhere, Category = "Collision")
	UBoxComponent* EnemyCollision;
	
	//Enemy Health / Functions
	void ResetActor();
	
	//Interface functions
	virtual void EnemyTakeDamage_Implementation(int32 DamageAmount) override;
};
