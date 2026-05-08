// Fill out your copyright notice in the Description page of Project Settings.


#include "CameraSwitcher.h"
#include "Camera/CameraComponent.h"

// Sets default values
ACameraSwitcher::ACameraSwitcher()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Initializing all the camera components
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	
	MainCamera = CreateDefaultSubobject<UCameraComponent>("MainCamera");
	MainCamera->SetupAttachment(RootComponent);

	SecondCamera = CreateDefaultSubobject<UCameraComponent>("SecondCamera");
	SecondCamera->SetupAttachment(MainCamera);

	ThirdCamera = CreateDefaultSubobject<UCameraComponent>("ThirdCamera");
	ThirdCamera->SetupAttachment(MainCamera);

	FourthCamera = CreateDefaultSubobject<UCameraComponent>("FourthCamera");
	FourthCamera->SetupAttachment(MainCamera);
}

// Called when the game starts or when spawned
void ACameraSwitcher::BeginPlay()
{
	Super::BeginPlay();
	
	//Setting the player's cam to the cam at the start of the course
	MainCamera->SetActive(false);
	SecondCamera->SetActive(false);
	ThirdCamera->SetActive(false);
	FourthCamera->SetActive(true);
}

// Called every frame
void ACameraSwitcher::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACameraSwitcher::SetCorrectCamActive(int CameraID)
{
	if (CameraID == 1)
	{
		MainCamera->SetActive(true);
		SecondCamera->SetActive(false);
		ThirdCamera->SetActive(false);
		FourthCamera->SetActive(false);
		
	}else if (CameraID == 2)
	{
		MainCamera->SetActive(false);
		SecondCamera->SetActive(true);
		ThirdCamera->SetActive(false);
		FourthCamera->SetActive(false);
		
	}else if (CameraID == 3)
	{
		MainCamera->SetActive(false);
		SecondCamera->SetActive(false);
		ThirdCamera->SetActive(true);
		FourthCamera->SetActive(false);
		
	}else if (CameraID == 4)
	{
		MainCamera->SetActive(false);
		SecondCamera->SetActive(false);
		ThirdCamera->SetActive(false);
		FourthCamera->SetActive(true);
	}
}


