// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "NewOverloadPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class OVERLOADED_API ANewOverloadPlayerController : public APlayerController
{
	GENERATED_BODY()
	
	/** MappingContext */
	UPROPERTY(EditAnywhere, Category="Input")
	UInputMappingContext* OverloadCharMappingContext;
	
public:
	
	ANewOverloadPlayerController();
	
	protected:
	
	/** Initialize input bindings */
	virtual void SetupInputComponent() override;
	
};
