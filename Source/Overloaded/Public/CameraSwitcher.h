// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "OverloadedCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "CameraSwitcher.generated.h"

UCLASS()
class OVERLOADED_API ACameraSwitcher : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACameraSwitcher();
	
	AOverloadedCharacter* OverloadedCharacterActorRef;

protected:
	// Called when the game starts or when spawnedf
	virtual void BeginPlay() override;
	
	//Creating cameras components
	UPROPERTY(EditAnywhere, Category = "Cameras")
	UCameraComponent* MainCamera;
	UPROPERTY(EditAnywhere, Category = "Cameras")
	UCameraComponent* SecondCamera;
	UPROPERTY(EditAnywhere, Category = "Cameras")
	UCameraComponent* ThirdCamera;
	UPROPERTY(EditAnywhere, Category = "Cameras")
	UCameraComponent* FourthCamera;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
