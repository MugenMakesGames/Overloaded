// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Interface/TowerUpgradesInterface.h"
#include "PlayerBudgetUI.generated.h"

/**
 * 
 */
UCLASS()
class OVERLOADED_API UPlayerBudgetUI : public UUserWidget, public ITowerUpgradesInterface
{
	GENERATED_BODY()
	
	virtual void NativeConstruct() override;
	
	UPROPERTY(meta = (BindWidget))
	UTextBlock* PlayerBudgetText;
	
	//Interface Functions
	virtual void SetBudgetText_Implementation(const FText& NewText) override;
};
