// Copyright Epic Games, Inc. All Rights Reserved.


#include "VGP221GameModeBase.h"
#include "FPSCharacter.h"
#include "Enemy.h"


AVGP221GameModeBase::AVGP221GameModeBase() : Super() {
	//PrimaryActorTick.bCanEverTick = true;
}

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

void AVGP221GameModeBase::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	EnemyTimer -= DeltaTime;
	if (EnemyTimer < 0.0f) {
		EnemyTimer = 3.0f;

		UWorld* world = GetWorld();
		if (world) {
			int playerIndex = 0;
			FVector playerLocation = UGameplayStatics::GetPlayerCharacter(GetWorld(), playerIndex)->GetActorLocation();
			FVector enemyLocation = playerLocation;
			float randomDistance = FMath::RandRange(200.0f, 800.0f);
			enemyLocation.X += randomDistance;
			enemyLocation.Y += randomDistance;

			int randomNumber = FMath::RandRange(0, 2);
			AEnemy* enemy = world->SpawnActor<AEnemy>(EnemyBlueprint, enemyLocation, FRotator::ZeroRotator);;
			switch (randomNumber) {
			case 0:
				enemy = world->SpawnActor<AEnemy>(EnemyBlueprint, enemyLocation, FRotator::ZeroRotator);
				break;
			case 1:
				enemy = world->SpawnActor<AEnemy>(FastEnemyBlueprint, enemyLocation, FRotator::ZeroRotator);
				break;
			case 2:
				enemy = world->SpawnActor<AEnemy>(SlowEnemyBlueprint, enemyLocation, FRotator::ZeroRotator);
				break;
			default:
				enemy = world->SpawnActor<AEnemy>(EnemyBlueprint, enemyLocation, FRotator::ZeroRotator);
				break;
			}
			
		}
	}
}

void AVGP221GameModeBase::BeginPlay() {
	Super::BeginPlay();
}

