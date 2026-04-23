// Fill out your copyright notice in the Description page of Project Settings.


#include "Towers.h"

#include "Enemy/EnemyPawn.h"
#include "Kismet/KismetMathLibrary.h"
#include "Towers/TowerBullet.h"

// Sets default values
ATowers::ATowers()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	TowerMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TowerMeshComponent"));
	TowerMeshComponent->SetupAttachment(RootComponent);
	
	//Creating an arrow component create a point in which the bullet can shoot from
	TowerShootingPoint = CreateDefaultSubobject<UArrowComponent>(TEXT("ShootingPoint"));
	TowerShootingPoint->SetupAttachment(RootComponent);
	
	EnemyDetectionRadius = CreateDefaultSubobject<USphereComponent>(TEXT("DetectionRadius"));
	EnemyDetectionRadius->SetupAttachment(TowerMeshComponent);
	
	EnemyDetectionRadius->SetGenerateOverlapEvents(true);
	EnemyDetectionRadius->SetCollisionResponseToAllChannels(ECR_Overlap);
	EnemyDetectionRadius->OnComponentBeginOverlap.AddDynamic(this, &ATowers::OnEnemyInRadius);
	EnemyDetectionRadius->OnComponentEndOverlap.AddDynamic(this, &ATowers::OnEnemyOutOfRadius);
	
}

// Called when the game starts or when spawned
void ATowers::BeginPlay()
{
	Super::BeginPlay();
	
	CreateBulletPool();
	
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
	ATowerBullet* Bullet = BulletPool[BulletCount];
	
	//Checking if bullet count is a valid index
	if (!BulletPool.IsValidIndex(BulletCount)) return;
	
	if (!Bullet) return;
	
	//Checking if the enemies are the radius before shooting bullets
	if (EnemiesInRadius.Num() <= 0) return;
	
	//Adding the bullets to the active bullet pool when they need to be shot
	ActiveBulletPool.Add(Bullet);
	//Remove swap is safer than .Remove
	BulletPool.RemoveSwap(Bullet);
		
	if (Bullet->Implements<UInteractionInterface>())
	{
		//Getting the in game time
		FTimerManager& TimerManager = GetWorld()->GetTimerManager();
			
		//You have to turn the ShootBullet function into a delegate to be used in the timer as it has parameters
		FTimerDelegate TimerDelegate;
		TimerDelegate.BindUFunction(this, FName("ShootBullet"), Bullet);
			
		TimerManager.SetTimer(BulletShootingFrequency, TimerDelegate, 2, false, -1);
	}
}

void ATowers::CreateBulletPool()
{
	for (int i = 0; i < BulletPoolAmount; ++i)
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
		
		ATowerBullet* CurrentBullet = GetWorld()->SpawnActor<ATowerBullet>(BulletClass, SpawnParams);
		
		if (CurrentBullet)
		{
			CurrentBullet->DeactivateBullet(CurrentBullet);
			
			BulletPool.Add(CurrentBullet);
		}
	}
}

void ATowers::ShootBullet(ATowerBullet* CurrentBulletToShoot)
{
	if (CurrentBulletToShoot && CurrentBulletToShoot->Implements<UInteractionInterface>())
	{
		FVector Location = TowerShootingPoint->GetComponentLocation();
		FRotator Rotation = TowerShootingPoint->GetComponentRotation();
		
		Execute_ActivateBullet(CurrentBulletToShoot, Location, Rotation);
		
		ActiveBulletPool.Remove(CurrentBulletToShoot);
		BulletPool.Add(CurrentBulletToShoot);
		
		FTimerHandle DeactivateBullet;
		
		//Setting a timer and using lambda functions (function only to be used in the timer) to deactivate the bullet after it is shot
		GetWorldTimerManager().SetTimer(DeactivateBullet,[this, CurrentBulletToShoot]()
			{
				//Deactivating the bullet before adding back to the bullet-pool
				CurrentBulletToShoot->DeactivateBullet(CurrentBulletToShoot);
		
				ActiveBulletPool.Remove(CurrentBulletToShoot);
				BulletPool.Add(CurrentBulletToShoot);
			},
			3.0f, 
			false
		);
		
		BulletCount++;
		
		if (BulletCount >= BulletPool.Num())
		{
			//Resetting the bullet count
			BulletCount = 0;
		}
		
		AddToActiveBulletPool();
	}
}

void ATowers::OnEnemyInRadius(class UPrimitiveComponent* ThisComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (AEnemyPawn* CurrentEnemy = Cast<AEnemyPawn>(OtherActor))
	{
		//Adding the current overlapping enemy to an actor pool
		EnemiesInRadius.AddUnique(CurrentEnemy);
	}
}

void ATowers::OnEnemyOutOfRadius(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (AEnemyPawn* CurrentEnemy = Cast<AEnemyPawn>(OtherActor))
	{
		//Adding the current overlapping enemy from the EnemiesInRadius pool when they leave the radius
		EnemiesInRadius.Remove(CurrentEnemy);
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
