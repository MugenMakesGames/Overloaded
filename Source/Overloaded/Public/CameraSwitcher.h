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
	
	//Creating all the collision boxes
	UPROPERTY(EditAnywhere, Category = "Collision Zones")
	UBoxComponent* MainCameraSwitchArea;
	UPROPERTY(EditAnywhere, Category = "Collision Zones")
	UBoxComponent* SecondCameraSwitchArea;
	
	//Creating the overlap functions for the collision
	UFUNCTION(blueprintCallable)
	void OnOverlapSwitchToMainCam(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult);	
	
	//Creating the overlap functions for the collision
	UFUNCTION(blueprintCallable)
	void OnOverlapSwitchToSecondCam(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult);	
	
	UFUNCTION(blueprintCallable)
	void SetMainCamActive();
	UFUNCTION(blueprintCallable)
	void SetSecondCamActive();
	
	
	/*UFUNCTION(blueprintCallable)
	void SetThirdCamActive();
	UFUNCTION(blueprintCallable)
	void SetFourthCamActive();*/
	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
