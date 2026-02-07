// Fill out your copyright notice in the Description page of Project Settings.


#include "CameraSwitcher.h"

#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ACameraSwitcher::ACameraSwitcher()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Initializing all the camera components
	MainCamera = CreateDefaultSubobject<UCameraComponent>("MainCamera");
	MainCamera->SetupAttachment(RootComponent);

	SecondCamera = CreateDefaultSubobject<UCameraComponent>("SecondCamera");
	SecondCamera->SetupAttachment(RootComponent);

	ThirdCamera = CreateDefaultSubobject<UCameraComponent>("ThirdCamera");
	ThirdCamera->SetupAttachment(RootComponent);

	FourthCamera = CreateDefaultSubobject<UCameraComponent>("FourthCamera");
	FourthCamera->SetupAttachment(RootComponent);
	
	
	//Automatic camera switching (No longer needed)
	
	
	//Getting actor refs
	OverloadedCharacterActorRef = Cast<AOverloadedCharacter>(UGameplayStatics::GetActorOfClass(
		GetWorld(),
		AOverloadedCharacter::StaticClass()
	));
}

// Called when the game starts or when spawned
void ACameraSwitcher::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ACameraSwitcher::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


