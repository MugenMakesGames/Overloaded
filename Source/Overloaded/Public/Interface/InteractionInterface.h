// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "InteractionInterface.generated.h"

UINTERFACE(BlueprintType)
class OVERLOADED_API UInteractionInterface : public UInterface
{
	GENERATED_BODY()
};

class OVERLOADED_API IInteractionInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void ActivateBullet(const FVector& BulletLocation, const FRotator& BulletRotation);
};
