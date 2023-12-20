// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "ButtonWidget.generated.h"

/**
 * 
 */
UCLASS()
class VGP221_API UButtonWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(meta = (BindWidget))
	UButton* Button;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* ButtonText;

	int num;

	UFUNCTION()
	void SetText(int value);

	UFUNCTION()
	void OnStartButtonClick();

	UFUNCTION()
	void OnQuitButtonClick();
};
