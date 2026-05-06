// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Interface/InteractionInterface.h"
#include "Interface/TowerUpgradesInterface.h"
#include "CameraSwitchingUI.generated.h"

class ACameraSwitcher;
class AEnemyPawn;

/**
 * 
 */

UCLASS()
class OVERLOADED_API UCameraSwitchingUI : public UUserWidget, public IInteractionInterface, public ITowerUpgradesInterface
{
	GENERATED_BODY()
	
	virtual void NativeConstruct() override;
	
private:
	
	UPROPERTY()
	AActor* TowerBulletClass;
	
	UPROPERTY()
	ACameraSwitcher* CameraSwitcherActorRef;
	
	UPROPERTY()
	class AEnemySpawningManager* EnemySpawnerClass;
	
	UPROPERTY()
	class ATowers* TowerClass;
	
	int CamID;
	
	int32 NumberOfEnemiesPerRound;
	
public:
	
	//Creating all the camera switching buttons
	UPROPERTY(meta = (BindWidget), BlueprintReadOnly, Category = "Camera Switching")
	UButton* SwitchMainCamera;
	
	UPROPERTY(meta = (BindWidget), BlueprintReadOnly, Category = "Camera Switching")
	UButton* SwitchSecondCamera;
	
	UPROPERTY(meta = (BindWidget), BlueprintReadOnly, Category = "Camera Switching")
	UButton* SwitchThirdCamera;
	
	UPROPERTY(meta = (BindWidget), BlueprintReadOnly, Category = "Camera Switching")
	UButton* SwitchFourthCamera;
	
	UPROPERTY(meta = (BindWidget), BlueprintReadOnly, Category = "Start Round")
	UButton* StartRound;
	
	UFUNCTION(BlueprintCallable)
	void OnStartRoundButtonClicked();
	
	UFUNCTION(BlueprintCallable)
	void OnMainCamButtonClicked();
	
	UFUNCTION(BlueprintCallable)
	void OnSecondCamButtonClicked();
	
	UFUNCTION(BlueprintCallable)
	void OnThirdCamButtonClicked();
	
	UFUNCTION(BlueprintCallable)
	void OnFourthCamButtonClicked();
};
