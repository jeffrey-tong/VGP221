// Fill out your copyright notice in the Description page of Project Settings.


#include "ButtonWidget.h"
#include "FPSUserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "VGP221GameModeBase.h"

void UButtonWidget::SetText(int value)
{
	if (!Button || !ButtonText) return;

	num = value;
	if (num == 0) {
		ButtonText->SetText(FText::FromString("Start Game"));
		Button->OnClicked.AddDynamic(this, &UButtonWidget::OnStartButtonClick);
	}
	if (num == 1) {
		ButtonText->SetText(FText::FromString("Quit Game"));
		Button->OnClicked.AddDynamic(this, &UButtonWidget::OnQuitButtonClick);
	}
	
}

void UButtonWidget::OnStartButtonClick()
{
	AVGP221GameModeBase* GameMode = Cast<AVGP221GameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	if (GameMode) {
		GameMode->HideMenu();
		GameMode->StartGame();
	}
}

void UButtonWidget::OnQuitButtonClick()
{
	GetWorld()->GetFirstPlayerController()->ConsoleCommand("quit");
}
