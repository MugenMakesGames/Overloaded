// Fill out your copyright notice in the Description page of Project Settings.


#include "Towers/TowerSpawningManager.h"

#include "OverloadedPlayerController.h"
#include "Towers.h"
#include "Components/BoxComponent.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
ATowerSpawningManager::ATowerSpawningManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	TowerSpawningArea = CreateDefaultSubobject<UBoxComponent>(TEXT("Tower Placement Area"));
	//owerSpawningArea->SetupAttachment(RootComponent);
	
	TowerSpawningArea->SetGenerateOverlapEvents(true);
	TowerSpawningArea->SetCollisionResponseToAllChannels(ECR_Overlap);
	TowerSpawningArea->OnComponentBeginOverlap.AddDynamic(this, &ATowerSpawningManager::OnTowerInPlacementRadius);
	TowerSpawningArea->OnComponentEndOverlap.AddDynamic(this, &ATowerSpawningManager::OnTowerOutOfPlacementRadius);
	

}

// Called when the game starts or when spawned
void ATowerSpawningManager::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATowerSpawningManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

void ATowerSpawningManager::OnTowerInPlacementRadius(class UPrimitiveComponent* ThisComp, class AActor* OtherActor,class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,const FHitResult& SweepResult)
{
	if (Cast<ATowers>(OtherActor))
	{
		
	}
}

void ATowerSpawningManager::OnTowerOutOfPlacementRadius(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (Cast<ATowers>(OtherActor))
	{
		
	}
}

void ATowerSpawningManager::SpawnTowerAtMouseLocation()
{
	APlayerController* PC = GetWorld()->GetFirstPlayerController();
	
	if (!TowerClass) return;
		
	if (PC)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Tower Spawned"));
		
		FHitResult HitResult;
		
		//Getting the HisResult for whatever is under the mouse cursor and putting it in an if statement to see if the line trace was successful
		if (PC->GetHitResultUnderCursorByChannel(UEngineTypes::ConvertToTraceType(ECC_Visibility), true,  HitResult))
		{
			FActorSpawnParameters SpawnParams;
			SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
		
			//Getting the surface contact of the mouse cursor and adding an FVector to avoid clipping
			FVector SpawnLocation = HitResult.ImpactPoint + FVector(0, 0, 20.f);
		
			//Spawning the tower at the hit location
			ATowers* SpawnedTower = GetWorld()->SpawnActor<ATowers>(TowerClass, SpawnLocation, FRotator::ZeroRotator, SpawnParams);	
			
			if (SpawnedTower)
			{
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Tower Spawned"));
			}
		}
	}
}

void ATowerSpawningManager::MoveTowerWithMouse()
{
	
}
