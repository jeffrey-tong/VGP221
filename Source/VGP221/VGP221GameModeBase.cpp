// Copyright Epic Games, Inc. All Rights Reserved.


#include "VGP221GameModeBase.h"

void AVGP221GameModeBase::StartPlay()
{
	Super::StartPlay();

	ChangeMenuWidget(StartingWidgetClass);

	check(GEngine != nullptr)
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Starting FPS Map")));
	UE_LOG(LogTemp, Warning, TEXT("Starting FPS Map"));
}

void AVGP221GameModeBase::ChangeMenuWidget(TSubclassOf<UFPSUserWidget> NewWidgetClass)
{
	//Check if theres a UI on screen
	if (CurrentWidget != nullptr) {
		CurrentWidget->RemoveFromParent();
		CurrentWidget = nullptr;
	}

	//Create a new UI and add to viewport
	if (NewWidgetClass != nullptr) {
		CurrentWidget = CreateWidget<UFPSUserWidget>(GetWorld(), NewWidgetClass);
		CurrentWidget->AddToViewport();
	}
}
