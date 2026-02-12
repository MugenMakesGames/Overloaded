// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "NewOverloadPlayerController.generated.h"

class UInputMappingContext;
class UInputAction;

/**
 * 
 */
UCLASS()
class OVERLOADED_API ANewOverloadPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	
	ANewOverloadPlayerController();
	
	/** MappingContext */
	UPROPERTY(EditAnywhere, Category = "Input")
	UInputMappingContext* OverloadCharMappingContext;
	
	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* LeftMouseButtonAction;

protected:
	
	/** Initialize input bindings */
	virtual void SetupInputComponent() override;
	
	UFUNCTION(blueprintCallable, Category = "Input")
	void OnLeftMouseButtonClicked();
	
};
