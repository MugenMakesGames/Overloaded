// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TowerSpawningManager.generated.h"

class ATowers;

UCLASS()
class OVERLOADED_API ATowerSpawningManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATowerSpawningManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UPROPERTY()
	bool IsTowerInPlacementRadius = false;
	
	UPROPERTY(EditInstanceOnly)
	ATowers* TowerClass;
	
	UPROPERTY(EditAnywhere, Category = "Tower Placement Area")
	UBoxComponent* TowerSpawningArea;
	
	UFUNCTION()
	void OnTowerInPlacementRadius(class UPrimitiveComponent* ThisComp, class AActor* OtherActor,
					class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
					const FHitResult& SweepResult);
	
	UFUNCTION()
	void OnTowerOutOfPlacementRadius(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, 
		int32 OtherBodyIndex);
};
