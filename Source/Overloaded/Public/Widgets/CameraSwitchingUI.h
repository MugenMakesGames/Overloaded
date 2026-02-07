// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "CameraSwitchingUI.generated.h"

/**
 * 
 */
UCLASS()
class OVERLOADED_API UCameraSwitchingUI : public UUserWidget
{
	GENERATED_BODY()
	
	virtual void NativeConstruct() override;
	
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
	
	UFUNCTION(BlueprintCallable)
	void OnMainCamButtonclicked();
	
	UFUNCTION(BlueprintCallable)
	void OnSecondCamButtonClicked();
	
	UFUNCTION(BlueprintCallable)
	void OnThirdCamButtonClicked();
	
	UFUNCTION(BlueprintCallable)
	void OnFourthCamButtonClicked();
	
	
	
};
