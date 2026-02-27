// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SplineComponent.h"
#include "GameFramework/Actor.h"
#include "EnemySplinePath.generated.h"


UCLASS()
class OVERLOADED_API AEnemySplinePath : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemySplinePath();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USplineComponent* EnemySplinePath;

};
