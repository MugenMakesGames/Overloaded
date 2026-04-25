// Fill out your copyright notice in the Description page of Project Settings.


#include "NewOverloadPlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Towers.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Towers/TowerSpawningManager.h"

ANewOverloadPlayerController::ANewOverloadPlayerController()
{
	
}

void ANewOverloadPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
	
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
			EnhancedInputComponent->BindAction(LeftMouseButtonAction, ETriggerEvent::Completed, this, &ANewOverloadPlayerController::OnLeftMouseButtonReleased);
		}
		
	}
}

void ANewOverloadPlayerController::OnLeftMouseButtonClicked()
{
	TowerSpawningClass = Cast<ATowerSpawningManager>(UGameplayStatics::GetActorOfClass(GetWorld(), 
	ATowerSpawningManager::StaticClass()));
	
	if (TowerSpawningClass)
	{
		TowerSpawningClass->SpawnTowerAtMouseLocation();
	}
}

void ANewOverloadPlayerController::OnLeftMouseButtonReleased()
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("OnLeftMouseButtonReleased"));
}