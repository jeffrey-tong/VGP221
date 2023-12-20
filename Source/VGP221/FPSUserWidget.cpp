// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSUserWidget.h"

void UFPSUserWidget::NativeConstruct()
{
	SetHealthBar(1.0);
	SetMoneyText(0);

	if (ButtonWidgetRef) {
		for (int i = 0; i < 2; i++) {
			UUserWidget* widget = CreateWidget(this, ButtonWidgetRef);
			ButtonContainer->AddChildToVerticalBox(widget);

			UButtonWidget* button = Cast<UButtonWidget>(widget);
			button->SetText(i);
		}
	}
}

void UFPSUserWidget::SetHealthBar(float percentage)
{
	if (!HealthBar) return;

	HealthBar->SetPercent(percentage);
}

void UFPSUserWidget::SetMoneyText(int moneyAmount)
{
	if (!MoneyText) return;

	money = moneyAmount;
	MoneyText->SetText(FText::FromString("Money: " + FString::FromInt(money)));
}

void UFPSUserWidget::HideMenu()
{
	ButtonContainer->SetVisibility(ESlateVisibility::Hidden);
	Background->SetVisibility(ESlateVisibility::Hidden);
	TitleText->SetVisibility(ESlateVisibility::Hidden);
}

void UFPSUserWidget::ShowMenu() {
	ButtonContainer->SetVisibility(ESlateVisibility::Visible);
	Background->SetVisibility(ESlateVisibility::Visible);
	TitleText->SetVisibility(ESlateVisibility::Visible);
}

