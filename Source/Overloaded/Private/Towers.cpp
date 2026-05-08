// Fill out your copyright notice in the Description page of Project Settings.


#include "Towers.h"

#include "NewOverloadPlayerController.h"
#include "Components/BillboardComponent.h"
#include "Enemy/EnemyPawn.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Towers/TowerBullet.h"
#include "Towers/TowerBulletHandler.h"

// Sets default values
ATowers::ATowers()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	TowerMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TowerMeshComponent"));
	RootComponent = TowerMeshComponent; 

	TowerShootingPoint = CreateDefaultSubobject<UArrowComponent>(TEXT("ShootingPoint"));
	TowerShootingPoint->SetupAttachment(RootComponent);

	EnemyDetectionRadius = CreateDefaultSubobject<USphereComponent>(TEXT("DetectionRadius"));
	EnemyDetectionRadius->SetupAttachment(RootComponent);
	
	EnemyDetectionRadius->SetGenerateOverlapEvents(true);
	EnemyDetectionRadius->SetCollisionResponseToAllChannels(ECR_Overlap);
	EnemyDetectionRadius->OnComponentBeginOverlap.AddDynamic(this, &ATowers::OnEnemyInRadius);
	EnemyDetectionRadius->OnComponentEndOverlap.AddDynamic(this, &ATowers::OnEnemyOutOfRadius);
	
	UpgradingTowerIndicator = CreateDefaultSubobject<UBillboardComponent>(TEXT("UpgradingTowerIndicator"));
	UpgradingTowerIndicator->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ATowers::BeginPlay()
{
	Super::BeginPlay();
	
	 BulletPoolClass = Cast<ATowerBulletHandler>(UGameplayStatics::GetActorOfClass(GetWorld(),
	 ATowerBulletHandler::StaticClass()));
	
	//Setting billboard to hidden by default
	UpgradingTowerIndicator->SetHiddenInGame(true);
}

// Called every frame
void ATowers::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	ChooseClosestEnemyInRadius();
	
	RotateTowardsEnemy(ClosestEnemy, DeltaTime);
}


void ATowers::AddToActiveBulletPool()
{
	//Don't shoot if there are no enemies in the radius
	if (EnemiesInRadius.Num() == 0) return;

	if (!BulletPoolClass)
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Yellow, TEXT("TOWER SPAWNER IS NOT VALID"));
		
		return;
	}
	
	ATowerBullet* Bullet = nullptr;
	
	BulletPoolClass->GetBullet(Bullet);
	
	if (!Bullet) return;
		
	if (Bullet->Implements<UInteractionInterface>())
	{
		ShootBullet(Bullet);
	}
}

void ATowers::ShootBullet(ATowerBullet* CurrentBulletToShoot)
{
	if (CurrentBulletToShoot && CurrentBulletToShoot->Implements<UInteractionInterface>())
	{
		FVector Location = TowerShootingPoint->GetComponentLocation();
		FRotator Rotation = TowerShootingPoint->GetComponentRotation();
		
		Execute_ActivateBullet(CurrentBulletToShoot, Location, Rotation);
		
		FTimerHandle DeactivateBullet;
		
		//Setting a timer and using lambda functions (function only to be used in the timer) to deactivate the bullet after it is shot
		GetWorldTimerManager().SetTimer(DeactivateBullet,[this, CurrentBulletToShoot]()
			{
				//Deactivating the bullet before adding back to the bullet-pool
				BulletPoolClass->ReturnBullet(CurrentBulletToShoot);
			},
			DeactivationSpeed, 
			false
		);
	}
}

void ATowers::OnEnemyInRadius(class UPrimitiveComponent* ThisComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (AEnemyPawn* CurrentEnemy = Cast<AEnemyPawn>(OtherActor))
	{
		//Adding the current overlapping enemy to an actor pool
		EnemiesInRadius.AddUnique(CurrentEnemy);
		
		//Running the timer as soon as the enemy is in the Tower radius
		if (EnemiesInRadius.Num() == 1)
		{
			GetWorldTimerManager().SetTimer(BulletShootingFrequency, this, &ATowers::AddToActiveBulletPool, ShootingSpeed, true);	
		}
	}
}

void ATowers::OnEnemyOutOfRadius(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (AEnemyPawn* CurrentEnemy = Cast<AEnemyPawn>(OtherActor))
	{
		//Adding the current overlapping enemy from the EnemiesInRadius pool when they leave the radius
		EnemiesInRadius.Remove(CurrentEnemy);
		
		//Clearing timer if there are no enemies in the radius
		if (EnemiesInRadius.Num() == 0)
		{
			GetWorldTimerManager().ClearTimer(BulletShootingFrequency);
		}
	}
}

void ATowers::ChooseClosestEnemyInRadius()
{
	//Setting the closest distance to an infinite number initially
	float ClosestDistance = FLT_MAX;
	
	for (AActor* CurrentActor : EnemiesInRadius)
	{
		//Running code even if CurrentActor is null
		if (!CurrentActor) continue;
		
		//Getting the distance between the Tower and the Enemy (Using DistSquare because it's faster for comparison)
		float Distance = FVector::DistSquared(GetActorLocation(), CurrentActor->GetActorLocation());
		
		if (Distance < ClosestDistance)
		{
			ClosestDistance = Distance;
			ClosestEnemy = CurrentActor;
		}
	}
	
	if (EnemiesInRadius.Num() == 0)
	{
		ClosestEnemy = nullptr;
	}
}

void ATowers::RotateTowardsEnemy(AActor* TargetEnemy, float DeltaTime)
{
	if (TargetEnemy)
	{
		//Getting the target actor's location
		FVector TargetActorLocation = TargetEnemy->GetActorLocation();
	
		//Updating the target actor's rotation based on the actor's location
		FRotator TargetRotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), TargetActorLocation);;
	
		//Ignoring the pitch & roll
		TargetRotation.Pitch = 0.f;
		TargetRotation.Roll = 0.f;
	
		//Smoothing rotating this actor towards the target actor's location using tick and setting the speed
		FRotator NewRotation = FMath::RInterpTo(GetActorRotation(), TargetRotation, DeltaTime, RotationSpeed);
	
		SetActorRotation(NewRotation);
	}
}

void ATowers::UpgradeShootingSpeed_Implementation(float& NewShootingSpeed, float& NewDeactivationSpeed, ATowers* CurrentTower)
{
	//Decrementing the value of the ShootingSpeed to increase shooting frequency
	CurrentTower->ShootingSpeed -= 0.5;
	CurrentTower->DeactivationSpeed -= 0.5;
	
	//Setting new shooting and deactivation speeds
	NewShootingSpeed = CurrentTower->ShootingSpeed;
	NewDeactivationSpeed = CurrentTower->DeactivationSpeed;
	
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, FString::Printf(TEXT("Radius: %f|%f"), NewShootingSpeed, NewDeactivationSpeed));
}

void ATowers::UpgradeDetectionRadius_Implementation(float& NewDetectionRadius, ATowers* CurrentTower)
{
	float NewRadiusSize = CurrentTower->EnemyDetectionRadius->GetUnscaledSphereRadius();
	
	NewRadiusSize += 10.f;
	
	NewDetectionRadius = NewRadiusSize;
	
	CurrentTower->EnemyDetectionRadius->SetSphereRadius(NewDetectionRadius);
	
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, FString::Printf(TEXT("Radius: %f"), NewDetectionRadius));
}

void ATowers::UpgradeRotationSpeed_Implementation(float& NewRotationSpeed, ATowers* CurrentTower)
{
	CurrentTower->RotationSpeed += 1.f;
	
	NewRotationSpeed = CurrentTower->RotationSpeed;
	
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, FString::Printf(TEXT("Radius: %f"), RotationSpeed));
}

void ATowers::TrackingUpgrades(ATowers* CurrentTower, FName UpgradeType)
{
	//Adding the current tower the player has selected to the map or finding an already existing tower 
	FNumberOfUpgradesPerType& UpgradesPerTower = NumberOfUpgradesPerTower.FindOrAdd(CurrentTower);
	
	ANewOverloadPlayerController* PC = Cast<ANewOverloadPlayerController>(GetWorld()->GetFirstPlayerController());
	
	if (UpgradeType.IsEqual(TEXT("ShootingUpgrades")))
	{
		//Getting the decremented values shooting upgrades
		NumberOfUpgrades = UpgradesPerTower.NumberOfShootingSpeedUpgrades;
		
		if (UpgradesPerTower.NumberOfShootingSpeedUpgrades == 1)
		{
			FText NewText = FText::FromString(TEXT("Sold Out"));
 			
			Execute_SetSoldOutTextBlock(PC->TowerSelectUI, NewText, TEXT("ShootingSpeedText"));
			
			return;
		}
		
		UpgradesPerTower.NumberOfShootingSpeedUpgrades--;
		
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::FromInt(NumberOfUpgrades));
	}
	else if (UpgradeType.IsEqual(TEXT("DetectionRadiusUpgrades")))
	{
		//Getting the decremented values of dadius upgrades
		NumberOfUpgrades = UpgradesPerTower.NumberOfRadiusUpgrades;
		
		if (UpgradesPerTower.NumberOfRadiusUpgrades == 1)
		{
			FText NewText = FText::FromString(TEXT("Sold Out"));
 			
			Execute_SetSoldOutTextBlock(PC->TowerSelectUI, NewText, TEXT("DetectionRadiusText"));
			
			return;
		}
		
		UpgradesPerTower.NumberOfRadiusUpgrades--;
		
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::FromInt(NumberOfUpgrades));
	}
	else if (UpgradeType.IsEqual(TEXT("RotationSpeedUpgrades")))
	{
		//Getting the decremented values of dadius upgrades
		NumberOfUpgrades = UpgradesPerTower.NumberOfRotationSpeedUpgrades;
		
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::FromInt(NumberOfUpgrades));
		
		if (UpgradesPerTower.NumberOfRotationSpeedUpgrades == 1)
		{
			FText NewText = FText::FromString(TEXT("Sold Out"));
 			
			Execute_SetSoldOutTextBlock(PC->TowerSelectUI, NewText, TEXT("RotationSpeedText"));
			
			return;
		}
		
		UpgradesPerTower.NumberOfRotationSpeedUpgrades--;
	}
}

void ATowers::SetTowerSelectText(ATowers* CurrentSelectedTower, ANewOverloadPlayerController* PC)
{
	FNumberOfUpgradesPerType& UpgradesPerTower = NumberOfUpgradesPerTower.FindOrAdd(CurrentSelectedTower);
	
	//Getting the current tower number of upgrades for each type and setting text
	if (UpgradesPerTower.NumberOfShootingSpeedUpgrades > 0)
	{
		FText NewText = FText::FromString(TEXT("Upgrade Shooting Speed"));
 			
		Execute_SetSoldOutTextBlock(PC->TowerSelectUI, NewText, TEXT("ShootingSpeedText"));
	} 
	else if (UpgradesPerTower.NumberOfShootingSpeedUpgrades <= 0)
	{
		FText NewText = FText::FromString(TEXT("Sold Out"));
 			
		Execute_SetSoldOutTextBlock(PC->TowerSelectUI, NewText, TEXT("ShootingSpeedText"));
	}

	if (UpgradesPerTower.NumberOfRadiusUpgrades > 0)
	{
		FText NewText = FText::FromString(TEXT("Upgrade Detection Radius"));
 			
		Execute_SetSoldOutTextBlock(PC->TowerSelectUI, NewText, TEXT("DetectionRadiusText"));
	} 
	else if (UpgradesPerTower.NumberOfRadiusUpgrades <= 0)
	{
		FText NewText = FText::FromString(TEXT("Sold Out"));
 			
		Execute_SetSoldOutTextBlock(PC->TowerSelectUI, NewText, TEXT("DetectionRadiusText"));
	}
	
	if (UpgradesPerTower.NumberOfRotationSpeedUpgrades > 0)
	{
		FText NewText = FText::FromString(TEXT("Upgrade Rotation Speed"));
 			
		Execute_SetSoldOutTextBlock(PC->TowerSelectUI, NewText, TEXT("RotationSpeedText"));
	} 
	else if (UpgradesPerTower.NumberOfRotationSpeedUpgrades <= 0)
	{
		FText NewText = FText::FromString(TEXT("Sold Out"));
 			
		Execute_SetSoldOutTextBlock(PC->TowerSelectUI, NewText, TEXT("RotationSpeedText"));
	}
}
