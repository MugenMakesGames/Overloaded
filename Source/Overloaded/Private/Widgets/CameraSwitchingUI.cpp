// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/CameraSwitchingUI.h"
#include "CameraSwitcher.h"
#include "NewOverloadPlayerController.h"
#include "Towers.h"
#include "Enemy/EnemyFinishLine.h"
#include "Enemy/EnemySpawningManager.h"
#include "Kismet/GameplayStatics.h"
#include "Player/PlayerMoneyManager.h"

void UCameraSwitchingUI::NativeConstruct()
{
	//Setting the on clicked button events
	SwitchMainCamera->OnClicked.AddUniqueDynamic(this, &UCameraSwitchingUI::OnMainCamButtonClicked);
	SwitchSecondCamera->OnClicked.AddUniqueDynamic(this, &UCameraSwitchingUI::OnSecondCamButtonClicked);
	SwitchThirdCamera->OnClicked.AddUniqueDynamic(this, &UCameraSwitchingUI::OnThirdCamButtonClicked);
	SwitchFourthCamera->OnClicked.AddUniqueDynamic(this, &UCameraSwitchingUI::OnFourthCamButtonClicked);
	
	//The widget is being called multiple times, so I used AddUniqueDynamic to avoid duplicate bindings
	StartRound->OnClicked.AddUniqueDynamic(this, &UCameraSwitchingUI::OnStartRoundButtonClicked);
	
	//Getting actor refs
	CameraSwitcherActorRef = Cast<ACameraSwitcher>(UGameplayStatics::GetActorOfClass(GetWorld(), 
	ACameraSwitcher::StaticClass()));
	
	TowerClass = Cast<ATowers>(UGameplayStatics::GetActorOfClass(GetWorld(), 
	ATowers::StaticClass()));
	
	EnemySpawnerClass = Cast<AEnemySpawningManager>(UGameplayStatics::GetActorOfClass(GetWorld(), 
	AEnemySpawningManager::StaticClass()));
	
	FinishLineClass = Cast<AEnemyFinishLine>(UGameplayStatics::GetActorOfClass(GetWorld(),
	AEnemyFinishLine::StaticClass()));
	
	MoneyManagerClass = Cast<APlayerMoneyManager>(UGameplayStatics::GetActorOfClass(GetWorld(),
	APlayerMoneyManager::StaticClass()));
}


void UCameraSwitchingUI::OnMainCamButtonClicked()
{
	//Setting the cam ID to 1 so the main cam is switched to etc
	CamID = 1;
	
	CameraSwitcherActorRef->SetCorrectCamActive(CamID);
	
	//Setting player camera's the active camera in the camera switcher actor 
	GetOwningPlayer()->SetViewTargetWithBlend(CameraSwitcherActorRef);
}

void UCameraSwitchingUI::OnSecondCamButtonClicked()
{
	if (!CameraSwitcherActorRef) return;
	
	CamID = 2;
	
	CameraSwitcherActorRef->SetCorrectCamActive(CamID);
	
	GetOwningPlayer()->SetViewTargetWithBlend(CameraSwitcherActorRef);
}

void UCameraSwitchingUI::OnThirdCamButtonClicked()
{
	if (!CameraSwitcherActorRef) return;
	
	CamID = 3;
	
	CameraSwitcherActorRef->SetCorrectCamActive(CamID);
	
	GetOwningPlayer()->SetViewTargetWithBlend(CameraSwitcherActorRef);
}

void UCameraSwitchingUI::OnFourthCamButtonClicked()
{
	if (!CameraSwitcherActorRef) return;
	
	CamID = 4;
	
	CameraSwitcherActorRef->SetCorrectCamActive(CamID);
	
	GetOwningPlayer()->SetViewTargetWithBlend(CameraSwitcherActorRef);
}

void UCameraSwitchingUI::OnStartRoundButtonClicked()
{
	if (bIsRoundOver == false)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("ROUND IS NOT OVER"));
		
		return;
	}
	
	//Starting Round
	bIsRoundOver = false;

	if (!MoneyManagerClass) return;
	
	//Creating win condition using round survived;
	if (RoundsSurvived >= 10)
	{
		ANewOverloadPlayerController* PC = Cast<ANewOverloadPlayerController>(GetWorld()->GetFirstPlayerController());
		
		//Display Win Screen
		if (PC->WinScreenUI)
		{
			PC->WinScreenUI->AddToViewport();
		} 
	}
	else
	{
		MoneyManagerClass->AddToBudgetOnRoundWin();
	
		//Increasing number of enemies each round
		NumberOfEnemiesPerRound += 5;
	
		//Increasing the number of enemies each round
		Execute_CreateEnemyPool(EnemySpawnerClass, NumberOfEnemiesPerRound);
		
		EnemySpawnerClass->StartRound(NumberOfEnemiesPerRound);
	
		//Start shooting bullets
		TowerClass->AddToActiveBulletPool();
	
		SetEnemiesCrossedLineText();
	
		//Resetting the finished enemy pool length to match the number of enemies spawned
		EnemiesFinishedPool.Empty();
	
		RoundsSurvived++;
	
		FText NewText = FText::FromString(FString::Printf(TEXT("Round Survived: %d/%d"), RoundsSurvived, 10));
	
		RoundsSurvivedText->SetText(NewText);
	}
}

void UCameraSwitchingUI::SetEnemiesCrossedLineText()
{
	ANewOverloadPlayerController* PC = Cast<ANewOverloadPlayerController>(GetWorld()->GetFirstPlayerController());
	
	//Setting the text to reference the number of enemies being spawned at the start
	FText Text = FText::FromString(FString::Printf(TEXT("Enemies Crossed: 0/%d"), NumberOfEnemiesPerRound));
	
	Execute_SetEnemyCrossedLineText(PC->PlayerBudgetUI, Text);

	if (!FinishLineClass) return;
	
	FinishLineClass->SetFinishedPool(EnemiesFinishedPool);
}

void UCameraSwitchingUI::GetNumberOfEnemiesSpawned_Implementation(int32& GetEnemiesSpawned)
{
	GetEnemiesSpawned = NumberOfEnemiesPerRound;
}

void UCameraSwitchingUI::IsRoundOver_Implementation(bool bNewIsRoundOver)
{
	bIsRoundOver = bNewIsRoundOver;
}

