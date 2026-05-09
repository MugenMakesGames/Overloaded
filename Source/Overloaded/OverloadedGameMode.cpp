// Copyright Epic Games, Inc. All Rights Reserved.

#include "OverloadedGameMode.h"

AOverloadedGameMode::AOverloadedGameMode()
{
	// stub
}

void AOverloadedGameMode::BeginPlay()
{
	Super::BeginPlay();
	
	if (GEngine)
	{
		GEngine->bEnableOnScreenDebugMessages = false;
		GEngine->bEnableOnScreenDebugMessagesDisplay = false;
	}
}

