// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Blueprint/UserWidget.h"
#include "FPSUserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "VGP221GameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class VGP221_API AVGP221GameModeBase : public AGameModeBase
{
	GENERATED_BODY()

	AVGP221GameModeBase();
	
public:
	virtual void StartPlay() override;

	virtual void Tick(float DeltaTime) override;

	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UMG UI")
	TSubclassOf<UFPSUserWidget> StartingWidgetClass;

	UPROPERTY()
	UFPSUserWidget* CurrentWidget;

	UFUNCTION(BlueprintCallable, Category = "UMG UI")
	void ChangeMenuWidget(TSubclassOf<UFPSUserWidget> NewWidgetClass);

	UPROPERTY(EditAnywhere, Category = "Spawn")
	TSubclassOf<class AEnemy> EnemyBlueprint;

	UPROPERTY(EditAnywhere, Category = "Spawn")
		TSubclassOf<class AEnemy> FastEnemyBlueprint;

	UPROPERTY(EditAnywhere, Category = "Spawn")
		TSubclassOf<class AEnemy> SlowEnemyBlueprint;

	float EnemyTimer;
};
