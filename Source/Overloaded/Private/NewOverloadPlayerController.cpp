// Fill out your copyright notice in the Description page of Project Settings.


#include "NewOverloadPlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Towers.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Towers/TowerSpawningManager.h"

ANewOverloadPlayerController::ANewOverloadPlayerController()
{
	
}

void ANewOverloadPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
	if (TowerToDrag)
	{
		FVector WorldLocation;
		FVector WorldDirection;
	
		if (DeprojectMousePositionToWorld(WorldLocation, WorldDirection))
		{
			// Define your ground plane (Z = 0 or whatever your map height is)
			float PlaneZ = 31.f;
	
			float T = (PlaneZ - WorldLocation.Z) / WorldDirection.Z;
			FVector NewLocation = WorldLocation + (WorldDirection * T);
	
			NewLocation.Z += 20.f;
	
			TowerToDrag->SetActorLocation(NewLocation);
		}
	}
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
	TowerSpawningClass = Cast<ATowerSpawningManager>(
		UGameplayStatics::GetActorOfClass(GetWorld(), ATowerSpawningManager::StaticClass()));

	if (!TowerSpawningClass) return;
	
	Execute_SpawnTowerAtMouseLocation(TowerSpawningClass, this, TowerToDrag);
	
	if (TowerToDrag)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green,  TowerToDrag->GetName());
		
		TowerToDrag->IsTowerBeingDragged(true);
		TowerToDrag->SetActorEnableCollision(false);
	}
}

void ANewOverloadPlayerController::OnLeftMouseButtonReleased()
{
	if (TowerToDrag)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green,  TowerToDrag->GetName());
		
		TowerToDrag->IsTowerBeingDragged(false);
		TowerToDrag->SetActorEnableCollision(false);
		//Releasing the tower to drag at the desired location
		TowerToDrag = nullptr;
	}
}
