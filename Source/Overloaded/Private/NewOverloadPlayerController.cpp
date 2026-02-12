// Fill out your copyright notice in the Description page of Project Settings.


#include "NewOverloadPlayerController.h"
#include "EnhancedInputSubsystems.h"

class UEnhancedInputLocalPlayerSubsystem;

ANewOverloadPlayerController::ANewOverloadPlayerController()
{
	
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
	}
	
}
