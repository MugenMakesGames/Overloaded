// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/TowerSelectUI.h"

void UTowerSelectUI::NativeConstruct()
{
	Super::NativeConstruct();
	
	TowerSlot1->OnClicked.AddDynamic(this, &UTowerSelectUI::OnTowerSlot1Clicked);
}


void UTowerSelectUI::OnTowerSlot1Clicked()
{
	
}
