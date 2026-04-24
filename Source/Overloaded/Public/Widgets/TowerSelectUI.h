// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "TowerSelectUI.generated.h"

/**
 * 
 */
UCLASS()
class OVERLOADED_API UTowerSelectUI : public UUserWidget
{
	GENERATED_BODY()
	
	virtual void NativeConstruct() override;
	
public:
	
	UPROPERTY(meta = (BindWidget), BlueprintReadOnly)
	UButton* TowerSlot1;
	
	UFUNCTION(BlueprintCallable)
	void OnTowerSlot1Clicked();
	
};
