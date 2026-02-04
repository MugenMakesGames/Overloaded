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

	//initializing collision components
	MainCameraSwitchArea = CreateDefaultSubobject<UBoxComponent>("MainCameraSwitchArea");
	MainCameraSwitchArea->SetupAttachment(RootComponent);
	MainCameraSwitchArea->SetGenerateOverlapEvents(true);
	MainCameraSwitchArea->SetCollisionResponseToChannels(ECollisionResponse::ECR_Overlap);

	SecondCameraSwitchArea = CreateDefaultSubobject<UBoxComponent>("SecondCameraSwitchArea");
	SecondCameraSwitchArea->SetupAttachment(RootComponent);
	SecondCameraSwitchArea->SetGenerateOverlapEvents(true);
	SecondCameraSwitchArea->SetCollisionResponseToChannels(ECollisionResponse::ECR_Overlap);

	//Setting the collision to dynamics and linking collision functions
	MainCameraSwitchArea->OnComponentBeginOverlap.AddDynamic(this, &ACameraSwitcher::OnOverlapSwitchToMainCam);
	SecondCameraSwitchArea->OnComponentBeginOverlap.AddDynamic(this, &ACameraSwitcher::OnOverlapSwitchToSecondCam);

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

void ACameraSwitcher::OnOverlapSwitchToMainCam(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//Checking if the overlapped actor is the player
	if (OtherActor && OtherActor == UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))
	{
		//GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Black, TEXT("Overlapping"));
		
		SetMainCamActive();
		
		//Setting the player's camera to the new camera
		UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetViewTargetWithBlend(this, 0.5f);
		
		
	}
}

void ACameraSwitcher::OnOverlapSwitchToSecondCam(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//Checking if the overlapped actor is the player
	if (OtherActor && OtherActor == UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))
	{
		//GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Black, TEXT("Working"));
		
		SetSecondCamActive();
		
		//Setting the player's camera to the new camera
		UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetViewTargetWithBlend(this, 0.5f);
	}
}

void ACameraSwitcher::SetMainCamActive()
{
	//Setting main camera to active and other cams to in-active to insure correct cam is switched to
	MainCamera->SetActive(true);
	SecondCamera->SetActive(false);
}

void ACameraSwitcher::SetSecondCamActive()
{
	SecondCamera->SetActive(true);
	MainCamera->SetActive(false);
}
