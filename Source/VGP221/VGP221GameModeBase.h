// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "VGP221GameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class VGP221_API AVGP221GameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	virtual void StartPlay() override;
};
