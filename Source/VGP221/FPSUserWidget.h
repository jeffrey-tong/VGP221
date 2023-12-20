// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"
#include "Components/Image.h"
#include "ButtonWidget.h"
#include "FPSUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class VGP221_API UFPSUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	UPROPERTY(meta = (BindWidget))
	UProgressBar* HealthBar;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* MoneyText;
	
	UPROPERTY(meta = (BindWidget))
	UVerticalBox* ButtonContainer;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* TitleText;

	UPROPERTY(meta = (BindWidget))
	UImage* Background;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UButtonWidget> ButtonWidgetRef;

	UFUNCTION()
	void SetHealthBar(float percentage);

	UFUNCTION()
	void SetMoneyText(int scoreAmount);

	UFUNCTION()
	void HideMenu();
	
	UFUNCTION()
	void ShowMenu();

private:
	int money = 0;
};
