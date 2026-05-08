// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/PlayerBudgetUI.h"
#include "Components/TextBlock.h"

void UPlayerBudgetUI::NativeConstruct()
{
	Super::NativeConstruct();
}

void UPlayerBudgetUI::SetBudgetText_Implementation(const FText& NewText)
{
	PlayerBudgetText->SetText(NewText);
}

void UPlayerBudgetUI::SetEnemyCrossedLineText_Implementation(const FText& NewText)
{
	EnemiesCrossedLine->SetText(NewText);
}

