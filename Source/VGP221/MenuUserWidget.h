// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/VerticalBox.h"
#include "ButtonWidget.h"
#include "MenuUserWidget.generated.h"
/**
 * 
 */
UCLASS()
class VGP221_API UMenuUserWidget : public UUserWidget
{
	GENERATED_BODY()
public:
    virtual void NativeConstruct() override;

	UPROPERTY(meta = (BindWidget))
		UVerticalBox* ButtonContainer;

	UPROPERTY(EditAnywhere)
		TSubclassOf<class UButtonWidget> ButtonWidgetRef;
    
};
