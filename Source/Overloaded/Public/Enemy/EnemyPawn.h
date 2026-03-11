 // Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SplineComponent.h"
#include "Components/TimelineComponent.h"
#include "GameFramework/Pawn.h"
#include "EnemyPawn.generated.h"

class CurveFloat;


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
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	UPROPERTY(EditAnywhere, Category = "Static Mesh")
	UStaticMeshComponent* EnemyStaticMesh;
	
	UPROPERTY(EditAnywhere, Category = "Timeline")
	UTimelineComponent* TimelineComponent;
	
	UPROPERTY(EditAnywhere, Category = "Timeline")
	UCurveFloat* MovementCurve;
	
	UPROPERTY(EditAnywhere, Category = "Timeline")
	float SetPlayRate;
	
	UFUNCTION(BlueprintCallable, Category = "Timeline")
	void UpdateTimeline(float Value);
	
	UFUNCTION(BlueprintCallable, Category = "Timeline")
	void FinishedTimeline();
	
	UPROPERTY(editAnywhere, Category = "Timeline")
	float StartingDistance = 0.f;
	
	FVector NewEnemyLocation;  
	FRotator NewEnemyRotation;
	
	//Creating a spline component to get a ref to the enemy spline component and length
	UPROPERTY()
	USplineComponent* EnemySplineComponent;
	
	//Enemy spawning
	//Adding a map to store the enemy actors and their active status
	UPROPERTY(EditAnywhere, Category = "Enemy Spawning")
	TMap<AActor*, bool> EnemiesToSpawn;
	
	UFUNCTION(BlueprintCallable)
	void SetEnemiesToSpawn(AActor* ActorToSpawn);
	

};
