// Fill out your copyright notice in the Description page of Project Settings.


#include "NewOverloadPlayerController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

ANewOverloadPlayerController::ANewOverloadPlayerController()
{
	//Setting inout mode to game and UI only and showing mouse cursor
	FInputModeGameAndUI();
	SetShowMouseCursor(true);
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
	}
	
}

void ANewOverloadPlayerController::OnLeftMouseButtonClicked()
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, "It's Working");
}
