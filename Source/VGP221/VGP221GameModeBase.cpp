// Copyright Epic Games, Inc. All Rights Reserved.


#include "VGP221GameModeBase.h"

void AVGP221GameModeBase::StartPlay()
{
	Super::StartPlay();

	check(GEngine != nullptr)
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Starting FPS Map")));
	UE_LOG(LogTemp, Warning, TEXT("Starting FPS Map"));
}
