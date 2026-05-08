// Fill out your copyright notice in the Description page of Project Settings.


#include "NewOverloadPlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Towers.h"
#include "Blueprint/UserWidget.h"
#include "Components/ArrowComponent.h"
#include "Components/BillboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Player/PlayerMoneyManager.h"
#include "Towers/TowerSpawningManager.h"
#include "Widgets/PlayerBudgetUI.h"

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
	
	TowerSelectUI = CreateWidget<UTowerSelectUI>(this, TowerSelectUIClass);
	
	PlayerBudgetUI = CreateWidget<UPlayerBudgetUI>(this, PlayerBudgetUIClass);
	
	LossScreenUI = CreateWidget<UEndScreenUI>(this, LossScreenUIClass);
	
	WinScreenUI = CreateWidget<UWinScreenUI>(this, WinScreenUIClass);
	
	if (CameraSwitchingUIClass && CameraSwitchingUI)
	{
		CameraSwitchingUI->AddToViewport();
	}
	
	if (PlayerBudgetUIClass && PlayerBudgetUI)
	{
		PlayerBudgetUI->AddToViewport();
		
		MoneyManagerClass = Cast<APlayerMoneyManager>(UGameplayStatics::GetActorOfClass(GetWorld(), APlayerMoneyManager::StaticClass()));
		
		if (!MoneyManagerClass) return;
		
		//Setting the text to 1000
		FText NewBudgetText = FText::FromString(FString::Printf(TEXT("Your Budget: %d"), MoneyManagerClass->PlayerCurrentBudget));
		
		Execute_SetBudgetText(PlayerBudgetUI, NewBudgetText);
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
			
			EnhancedInputComponent->BindAction(QButtonAction, ETriggerEvent::Started, this, &ANewOverloadPlayerController::OnExitTowerUIClicked);
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
			CurrentSpawner = Spawner;

			if (!Spawner) return;
			
			if (TowerSpawners.Contains(Spawner) && TowerSpawners[Spawner] == true)
			{
				if (TowerSelectUI && TowerSelectUIClass)
				{
					CameraSwitchingUI->RemoveFromParent();
					
					TowerSelectUI->AddToViewport();

					if (ATowers* CurrentSelectedTower = Cast<ATowers>(CurrentSpawnerTower[Spawner]))
					{
						CurrentSelectedTower->SetTowerSelectText(CurrentSelectedTower, this);
					}
					
					for (auto& Elem : CurrentSpawnerTower)
					{
						//Setting all the tower's billboard to hidden so the selected one can be unhidden 
						Elem.Value->UpgradingTowerIndicator->SetHiddenInGame(true);
						
						if (Elem.Value == CurrentSpawnerTower[Spawner])
						{
							//Unhiding the current tower the player has selected
							CurrentSpawnerTower[Spawner]->UpgradingTowerIndicator->SetHiddenInGame(false);
						}
					}
				}
			}
			else
			{
				if (MoneyManagerClass)
				{
					MoneyManagerClass->SetBudget(TEXT("Tower"));
					
					//No more spawning towers
					if (MoneyManagerClass->PlayerCurrentBudget <= 0)
					{
						GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("BUDGET IS FINISHED"));
						
						return;
					}
				}
				//Getting spawning location
				SpawnLocation = Spawner->TowerSpawnLocation->GetComponentLocation();
	
				Execute_SpawnTowerAtMouseLocation(TowerSpawningClass, TowerToUpgrade, SpawnLocation);
	
				TowerSpawners.Add(Spawner, true);
	
				//Adding spawner with its tower to a map to get the exact tower we need to upgrade
				CurrentSpawnerTower.Add(Spawner, TowerToUpgrade);
			}
		}
	}	
}

void ANewOverloadPlayerController::OnExitTowerUIClicked()
{
	if (TowerSelectUI && TowerSelectUI->IsInViewport())
	{
		TowerSelectUI->RemoveFromParent();

		if (CameraSwitchingUIClass && CameraSwitchingUI)
		{
			CameraSwitchingUI->AddToViewport();
		}
	}
}

void ANewOverloadPlayerController::GetCurrentTower_Implementation(class ATowers*& CurrentTower)
{
	//Getting the current selected tower actor
	CurrentTower = CurrentSpawnerTower[CurrentSpawner];
}


