// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSUserWidget.h"

void UFPSUserWidget::NativeConstruct()
{
	SetHealthBar(1.0);
	SetScoreText(1);

	/*if (ButtonWidgetRef) {
		for (int i = 0; i < 4; i++) {
			UUserWidget* widget = CreateWidget(this, ButtonWidgetRef);
			ButtonContainer->AddChildToVerticalBox(widget);

			UButtonWidget* button = Cast<UButtonWidget>(widget);
			button->SetText(i);
		}
	}*/
}

void UFPSUserWidget::SetHealthBar(float percentage)
{
	if (!HealthBar) return;

	HealthBar->SetPercent(percentage);
}

void UFPSUserWidget::SetScoreText(int scoreAmount)
{
	if (!ScoreText) return;

	score += scoreAmount;
	ScoreText->SetText(FText::FromString("Score: " + FString::FromInt(score)));
}
