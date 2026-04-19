// Fill out your copyright notice in the Description page of Project Settings.


#include "NewOverloadPlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Blueprint/UserWidget.h"

ANewOverloadPlayerController::ANewOverloadPlayerController()
{
	
}

void ANewOverloadPlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	//Creating the widget
	CameraSwitchingUI = CreateWidget<UCameraSwitchingUI>(this, CameraSwitchingUIClass);
	
	if (CameraSwitchingUIClass && CameraSwitchingUI)
	{
		CameraSwitchingUI->AddToViewport();
	}
}

void ANewOverloadPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	
	// Only set up input on local player controllers
	if (IsLocalPlayerController())
	{
		// Add Input Mapping Context
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(OverloadCharMappingContext, 0);
		}
		
		// Add input action mappings
		if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
		{
			//Left mouse button clicked
			EnhancedInputComponent->BindAction(LeftMouseButtonAction, ETriggerEvent::Started, this, &ANewOverloadPlayerController::OnLeftMouseButtonClicked);
		}
		
		// Add input action mappings
		if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
		{
			EnhancedInputComponent->BindAction(SpawnEnemyAction, ETriggerEvent::Started, this, &ANewOverloadPlayerController::OnSpawnEnemyPressed);
		}
	}
}

void ANewOverloadPlayerController::OnLeftMouseButtonClicked()
{
	
}

void ANewOverloadPlayerController::OnSpawnEnemyPressed()
{
	
	
}
