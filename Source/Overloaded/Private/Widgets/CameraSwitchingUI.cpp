// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/CameraSwitchingUI.h"

#include "CameraSwitcher.h"
#include "Kismet/GameplayStatics.h"

void UCameraSwitchingUI::NativeConstruct()
{
	//Setting the on clicked button events
	SwitchMainCamera->OnClicked.AddDynamic(this, &UCameraSwitchingUI::OnMainCamButtonclicked);
	SwitchSecondCamera->OnClicked.AddDynamic(this, &UCameraSwitchingUI::OnSecondCamButtonClicked);
	SwitchThirdCamera->OnClicked.AddDynamic(this, &UCameraSwitchingUI::OnThirdCamButtonClicked);
	SwitchFourthCamera->OnClicked.AddDynamic(this, &UCameraSwitchingUI::OnFourthCamButtonClicked);
	
	//Getting actor refs
	CameraSwitcherActorRef = Cast<ACameraSwitcher>(UGameplayStatics::GetActorOfClass(
		GetWorld(),
		ACameraSwitcher::StaticClass()
	));
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
	CamID = 2;
	
	CameraSwitcherActorRef->SetCorrectCamActive(CamID);
	
	GetOwningPlayer()->SetViewTargetWithBlend(CameraSwitcherActorRef);
}

void UCameraSwitchingUI::OnThirdCamButtonClicked()
{
	CamID = 3;
	
	CameraSwitcherActorRef->SetCorrectCamActive(CamID);
	
	GetOwningPlayer()->SetViewTargetWithBlend(CameraSwitcherActorRef);
}

void UCameraSwitchingUI::OnFourthCamButtonClicked()
{
	CamID = 4;
	
	CameraSwitcherActorRef->SetCorrectCamActive(CamID);
	
	GetOwningPlayer()->SetViewTargetWithBlend(CameraSwitcherActorRef);
}