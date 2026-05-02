// Fill out your copyright notice in the Description page of Project Settings.


#include "NewOverloadPlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
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
		}
	}
}

void ANewOverloadPlayerController::OnLeftMouseButtonClicked()
{
	TowerSpawningClass = Cast<ATowerSpawningManager>(UGameplayStatics::GetActorOfClass(GetWorld(), ATowerSpawningManager::StaticClass()));
	
	if (!TowerSpawningClass) return;
	
	FHitResult HitResult;
		
	//Getting the HisResult for whatever is under the mouse cursor and putting it in an if statement to see if the line trace was successful
	if (GetHitResultUnderCursorByChannel(UEngineTypes::ConvertToTraceType(ECC_Visibility), true,  HitResult))
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

		if (ATowerSpawningManager* Spawner = Cast<ATowerSpawningManager>(HitResult.GetActor()))
		{
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan,  HitResult.GetActor()->GetName();

			if (!Spawner) return;
			
			if (TowerSpawners.Contains(Spawner) && TowerSpawners[Spawner] == true)
			{
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "TowerSpawner already exists");
			}
			else
			{
				//Getting spawning location
				SpawnLocation = Spawner->TowerSpawnLocation->GetComponentLocation();
				
				Execute_SpawnTowerAtMouseLocation(TowerSpawningClass, TowerToUpgrade, SpawnLocation);
				
				Spawner->TowerSpawningArea->ShapeColor = FColor::Emerald;
				
				TowerSpawners.Add(Spawner, true);
			}
		}	
	}
}


