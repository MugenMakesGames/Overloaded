// Fill out your copyright notice in the Description page of Project Settings.


#include "OverloadPlayerChararacter.h"
#include "CameraSwitcher.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
AOverloadPlayerChararacter::AOverloadPlayerChararacter()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	//Setting up camera
	MainPlayerCamera = CreateDefaultSubobject<UCameraComponent>("MainPlayerCamera");
	MainPlayerCamera->SetupAttachment(RootComponent);
	
	CameraSwitcherActorRef = Cast<ACameraSwitcher>(UGameplayStatics::GetActorOfClass(
		GetWorld(),
		ACameraSwitcher::StaticClass()
	));
	
}

// Called when the game starts or when spawned
void AOverloadPlayerChararacter::BeginPlay()
{
	Super::BeginPlay();
	
	//Creating the widget
	CameraSwitchingUI = CreateWidget(GetWorld(), CameraSwitchingUIClass);
	
	if (CameraSwitchingUIClass && CameraSwitchingUI)
	{
		CameraSwitchingUI->AddToViewport();
	}
	
	//Setting the camera to the main camera in camera switcher actor
	APlayerController* PlayerController = Cast<APlayerController>(GetWorld()->GetFirstPlayerController());
	
	PlayerController->SetViewTargetWithBlend(CameraSwitcherActorRef);
}

// Called every frame
void AOverloadPlayerChararacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AOverloadPlayerChararacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

