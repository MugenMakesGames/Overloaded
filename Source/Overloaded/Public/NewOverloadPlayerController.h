// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Widgets/CameraSwitchingUI.h"
#include "Widgets/PlayerBudgetUI.h"
#include "Widgets/EndScreenUI.h"
#include "Widgets/TowerSelectUI.h"
#include "Widgets/WinScreenUI.h"
#include "NewOverloadPlayerController.generated.h"

class UInputMappingContext;
class UInputAction;
class AEnemyPawn;
class ATowers;
class ATowerSpawningManager;

/**
 * 
 */

UCLASS()
class OVERLOADED_API ANewOverloadPlayerController : public APlayerController, public IInteractionInterface, public ITowerUpgradesInterface
{
	GENERATED_BODY()
	
protected:
	
	UPROPERTY()
	ATowerSpawningManager* TowerSpawningClass;
	
public:
	
	ANewOverloadPlayerController();
	
	virtual void Tick(float DeltaSeconds) override;
	
	/** MappingContext */
	UPROPERTY(EditAnywhere, Category = "Input")
	UInputMappingContext* OverloadCharMappingContext;
	
	UPROPERTY(EditAnywhere, Category = "Bullet Spawning")
	TSubclassOf<class ATowerBullet> BulletClassTemp;
	
	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* LeftMouseButtonAction;
	
	UPROPERTY(editAnywhere, Category = "Input")
	UInputAction* QButtonAction;
	
	//Creating widget classes
	UPROPERTY(EditAnywhere, Category = "Camera Switching Widget")
	TSubclassOf<UCameraSwitchingUI> CameraSwitchingUIClass;
	
	UPROPERTY(EditAnywhere, Category = "Tower Select Widget")
	TSubclassOf<UTowerSelectUI> TowerSelectUIClass;
	
	UPROPERTY(EditAnywhere, Category = "Player Budget Widget")
	TSubclassOf<UPlayerBudgetUI> PlayerBudgetUIClass;
	
	UPROPERTY(EditAnywhere, Category = "Loss Screen")
	TSubclassOf<UEndScreenUI> LossScreenUIClass;
	
	UPROPERTY(EditAnywhere, Category = "Win Screen")
	TSubclassOf<UWinScreenUI> WinScreenUIClass;
	
	UPROPERTY()
	UWinScreenUI* WinScreenUI;
	
	//Creating widget instances
	UPROPERTY()
	UEndScreenUI* LossScreenUI;
	
	UPROPERTY()
	UCameraSwitchingUI* CameraSwitchingUI;
	
	UPROPERTY()
	UTowerSelectUI* TowerSelectUI;
	
	UPROPERTY()
	UPlayerBudgetUI* PlayerBudgetUI;
	
	UPROPERTY()
	ATowerSpawningManager* CurrentSpawner;
	
	UPROPERTY()
	ATowers* TowerToUpgrade;
	
	UPROPERTY(EditAnywhere, Category = "Money Manager")
	class APlayerMoneyManager* MoneyManagerClass;
	
	UPROPERTY()
	TMap<ATowerSpawningManager*, bool> TowerSpawners;
	
	UPROPERTY()
	TMap<ATowerSpawningManager*, ATowers*> CurrentSpawnerTower;
	
	//Interface functions
	virtual void GetCurrentTower_Implementation(class ATowers*& CurrentTower) override;

protected:
	
	/** Initialize input bindings */
	virtual void SetupInputComponent() override;
	
	virtual void BeginPlay() override;
	
	UFUNCTION(blueprintCallable, Category = "Input")
	void OnLeftMouseButtonClicked();
	
	UFUNCTION(blueprintCallable, Category = "Input")
	void OnExitTowerUIClicked();
};
