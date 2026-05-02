// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/CameraSwitchingUI.h"
#include "CameraSwitcher.h"
#include "Towers.h"
#include "Enemy/EnemySpawningManager.h"
#include "Kismet/GameplayStatics.h"

void UCameraSwitchingUI::NativeConstruct()
{
	//Setting the on clicked button events
	SwitchMainCamera->OnClicked.AddDynamic(this, &UCameraSwitchingUI::OnMainCamButtonclicked);
	SwitchSecondCamera->OnClicked.AddDynamic(this, &UCameraSwitchingUI::OnSecondCamButtonClicked);
	SwitchThirdCamera->OnClicked.AddDynamic(this, &UCameraSwitchingUI::OnThirdCamButtonClicked);
	SwitchFourthCamera->OnClicked.AddDynamic(this, &UCameraSwitchingUI::OnFourthCamButtonClicked);
	
	StartRound->OnClicked.AddDynamic(this, &UCameraSwitchingUI::OnStartRoundButtonClicked);
	
	//Getting actor refs
	CameraSwitcherActorRef = Cast<ACameraSwitcher>(UGameplayStatics::GetActorOfClass(GetWorld(), 
	ACameraSwitcher::StaticClass()));
	
	TowerClass = Cast<ATowers>(UGameplayStatics::GetActorOfClass(GetWorld(), 
	ATowers::StaticClass()));
	
	EnemySpawnerClass = Cast<AEnemySpawningManager>(UGameplayStatics::GetActorOfClass(GetWorld(), 
	AEnemySpawningManager::StaticClass()));
}


void UCameraSwitchingUI::OnMainCamButtonclicked()
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
	if (!EnemySpawnerClass || !TowerClass)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green,TEXT("TOWER IS NOT PLACED INTO THE WORLD"));
		
		TowerClass = Cast<ATowers>(UGameplayStatics::GetActorOfClass(GetWorld(), ATowers::StaticClass()));
		
		return;
	};
	
	//Increasing number of enemies by 5 each round
	NumberOfEnemiesPerRound += 5;
	
	//Increasing the number of enemies each round
	Execute_CreateEnemyPool(EnemySpawnerClass, NumberOfEnemiesPerRound);
	
	//Start spawning enemies 
	EnemySpawnerClass->SpawnFromEnemyPool();
	
	//Start shooting bullets
	TowerClass->AddToActiveBulletPool();
}

void UCameraSwitchingUI::SetText(const FText& Text)
{
	//Text = FText::Format();
	PlayerBudget->SetText(Text);
}
