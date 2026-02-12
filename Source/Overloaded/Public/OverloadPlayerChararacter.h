// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Pawn.h"
#include "OverloadPlayerChararacter.generated.h"

class UcameraSwitcher;

UCLASS()
class OVERLOADED_API AOverloadPlayerChararacter : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AOverloadPlayerChararacter();
	
	UPROPERTY(EditAnywhere, Category = "Camera")
	UCameraComponent* MainPlayerCamera;
	
	//Creating widget class
	UPROPERTY(EditAnywhere, Category = "Camera Switching Widget")
	TSubclassOf<UUserWidget> CameraSwitchingUIClass;

	//The widget instance that we are using
	UUserWidget* CameraSwitchingUI;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	AActor* CameraSwitcherActorRef;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	

};
