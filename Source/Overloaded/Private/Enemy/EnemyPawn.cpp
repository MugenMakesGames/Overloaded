// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/EnemyPawn.h"

#include "Enemy/EnemySplinePath.h"
#include "Kismet/GameplayStatics.h"



// Sets default values
AEnemyPawn::AEnemyPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	//Initializing all components 
	EnemyStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("EnemyStaticMesh"));
	EnemyStaticMesh->SetupAttachment(RootComponent);
	TimelineComponent = CreateDefaultSubobject<UTimelineComponent>(FName("TimelineComponent"));

}

// Called when the game starts or when spawned
void AEnemyPawn::BeginPlay()
{
	Super::BeginPlay();
	
	AEnemySplinePath* EnemySplinePathActor = Cast<AEnemySplinePath>(UGameplayStatics::GetActorOfClass(
		GetWorld(),
		AEnemySplinePath::StaticClass()
	));

	if (EnemySplinePathActor)
	{
		//Setting the spline component in this actor to the original enemy spline component
		EnemySplineComponent = EnemySplinePathActor->FindComponentByClass<USplineComponent>();
	}

	if (EnemySplineComponent)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red,'VALID');
		
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, "SPLINE ACTOR IS VALID");
		
		//Getting the length of the spline component
		EnemySplineLength = EnemySplineComponent->GetSplineLength();
	}
	
	MovementCurve = NewObject<UCurveFloat>(this);
	
	if (MovementCurve)
	{
		//Adding the float keys like using a time and value like in the blueprint float track
		MovementCurve->FloatCurve.AddKey(0.f, 0.f);
		MovementCurve->FloatCurve.AddKey(1.f, 1.f);
		
		//Bind the timeline events like in blueprints, this is the update function
		FOnTimelineFloat UpdateFunction;
		UpdateFunction.BindUFunction(this, FName("UpdateTimeline"));
		
		FOnTimelineEvent FinishedFunction;
		FinishedFunction.BindUFunction(this, FName("FinishedTimeline"));
		
		//Telling the timeline comp to start at 0 with a value of 0 and finished the timeline at 1 with a value of 1 
		//(Use blueprint node to understand better)
		TimelineComponent->AddInterpFloat(MovementCurve, UpdateFunction);
		
		TimelineComponent->SetTimelineFinishedFunc(FinishedFunction);
		
		TimelineComponent->SetPlayRate(SetPlayRate);
		
		TimelineComponent->SetLooping(false);
		
		//Starting the time at 1.25 second to space out enemies
		TimelineComponent->SetNewTime((StartingDistance / EnemySplineLength) * TimelineComponent->GetTimelineLength());
		
		//PLay the timeline, call where ended
		TimelineComponent->PlayFromStart();
		
	}
}

// Called every frame
void AEnemyPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AEnemyPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}


void AEnemyPawn::UpdateTimeline(float CompletionPercent)
{
	if (EnemySplineComponent)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, "Update func is working");
		
		float Distance = CompletionPercent * EnemySplineLength;
		
		//Getting the new transform (Location, rotation and scale) for the enemy to go to along the spline
		NewEnemyLocation = EnemySplineComponent->GetLocationAtDistanceAlongSpline(
			Distance,
			ESplineCoordinateSpace::World);
		
		NewEnemyRotation = EnemySplineComponent->GetRotationAtDistanceAlongSpline(
			Distance,
			ESplineCoordinateSpace::World);
		
		SetActorLocation(NewEnemyLocation);
		SetActorRotation(NewEnemyRotation);
	}
}

void AEnemyPawn::FinishedTimeline()
{
}




