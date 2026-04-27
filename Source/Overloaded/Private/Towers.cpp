// Fill out your copyright notice in the Description page of Project Settings.


#include "Towers.h"

#include "Enemy/EnemyPawn.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Towers/TowerBullet.h"
#include "Towers/TowerSpawningManager.h"

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
}

// Called when the game starts or when spawned
void ATowers::BeginPlay()
{
	Super::BeginPlay();
	
	TowerSpawnerClass = Cast<ATowerSpawningManager>(UGameplayStatics::GetActorOfClass(GetWorld(), 
	ATowerSpawningManager::StaticClass()));
}

// Called every frame
void ATowers::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (bIsTowerBeingDragged) return;
	
	ChooseClosestEnemyInRadius();
	
	RotateTowardsEnemy(ClosestEnemy, DeltaTime);
}

void ATowers::IsTowerBeingDragged(bool bIsBeingDragged)
{
	bIsTowerBeingDragged = bIsBeingDragged;
	
	if (bIsBeingDragged)
	{
		SetActorEnableCollision(true);
	}
	else
	{
		SetActorEnableCollision(false);
	}

	if (EnemyDetectionRadius)
	{
		//Setting collision based on if the tower is being dragged or not
		EnemyDetectionRadius->SetCollisionEnabled(bIsBeingDragged ? ECollisionEnabled::NoCollision : ECollisionEnabled::QueryOnly);
	}
}

void ATowers::AddToActiveBulletPool()
{
	//Don't shoot if there are no enemies in the radius
	if (EnemiesInRadius.Num() == 0) return;

	if (!TowerSpawnerClass)
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Yellow, TEXT("TOWER SPAWNER IS NOT VALID"));
		
		return;
	}
	
	ATowerBullet* Bullet = nullptr;
	
	TowerSpawnerClass->GetBullet(Bullet);
	
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
				TowerSpawnerClass->ReturnBullet(CurrentBulletToShoot);
			},
			3.0f, 
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
			GetWorldTimerManager().SetTimer(BulletShootingFrequency, this, &ATowers::AddToActiveBulletPool, 2.f, true);	
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
			//GetWorldTimerManager().ClearTimer(BulletShootingFrequency);
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
		FRotator NewRotation = FMath::RInterpTo(GetActorRotation(), TargetRotation, DeltaTime, 2.0f);
	
		SetActorRotation(NewRotation);
	}
}
