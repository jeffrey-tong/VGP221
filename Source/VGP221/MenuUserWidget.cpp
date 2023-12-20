// Fill out your copyright notice in the Description page of Project Settings.


#include "MenuUserWidget.h"

// Additional includes may be necessary depending on your logic

void UMenuUserWidget::NativeConstruct()
{
	if (ButtonWidgetRef) {
		for (int i = 0; i < 2; i++) {
			UUserWidget* widget = CreateWidget(this, ButtonWidgetRef);
			ButtonContainer->AddChildToVerticalBox(widget);

			UButtonWidget* button = Cast<UButtonWidget>(widget);
			button->SetText(i);
		}
	}
}
