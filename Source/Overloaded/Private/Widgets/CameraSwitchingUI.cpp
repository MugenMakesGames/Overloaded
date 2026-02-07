// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/CameraSwitchingUI.h"

void UCameraSwitchingUI::NativeConstruct()
{
	//Setting the on clicked button events
	SwitchMainCamera->OnClicked.AddDynamic(this, &UCameraSwitchingUI::OnMainCamButtonclicked);
	SwitchSecondCamera->OnClicked.AddDynamic(this, &UCameraSwitchingUI::OnSecondCamButtonClicked);
	SwitchThirdCamera->OnClicked.AddDynamic(this, &UCameraSwitchingUI::OnThirdCamButtonClicked);
	SwitchFourthCamera->OnClicked.AddDynamic(this, &UCameraSwitchingUI::OnFourthCamButtonClicked);
	
}

void UCameraSwitchingUI::OnMainCamButtonclicked()
{
	
}

void UCameraSwitchingUI::OnSecondCamButtonClicked()
{
	
}

void UCameraSwitchingUI::OnThirdCamButtonClicked()
{
	
}

void UCameraSwitchingUI::OnFourthCamButtonClicked()
{
	
}