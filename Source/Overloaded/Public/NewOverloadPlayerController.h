// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Widgets/CameraSwitchingUI.h"
#include "NewOverloadPlayerController.generated.h"

class UInputMappingContext;
class UInputAction;
class AEnemyPawn;

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
	
	//Creating widget class
	UPROPERTY(EditAnywhere, Category = "Camera Switching Widget")
	TSubclassOf<UCameraSwitchingUI> CameraSwitchingUIClass;

	//The widget instance that we are using
	UPROPERTY()
	UCameraSwitchingUI* CameraSwitchingUI;

protected:
	
	/** Initialize input bindings */
	virtual void SetupInputComponent() override;
	
	virtual void BeginPlay() override;
	
	UFUNCTION(blueprintCallable, Category = "Input")
	void OnLeftMouseButtonClicked();
	
	
};
