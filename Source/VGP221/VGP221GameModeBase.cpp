// Copyright Epic Games, Inc. All Rights Reserved.


#include "VGP221GameModeBase.h"
#include "FPSCharacter.h"
#include "Enemy.h"


AVGP221GameModeBase::AVGP221GameModeBase() : Super() {
	PrimaryActorTick.bCanEverTick = true;
}

void AVGP221GameModeBase::StartPlay()
{
	Super::StartPlay();

	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	if (PlayerController) {
		PlayerController->bShowMouseCursor = true;

		FInputModeUIOnly InputMode;
		PlayerController->SetInputMode(InputMode);
	}
	PauseGame();
	ChangeMenuWidget(StartingWidgetClass);

	check(GEngine != nullptr)
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Starting FPS Map")));
	UE_LOG(LogTemp, Warning, TEXT("Starting FPS Map"));
}

void AVGP221GameModeBase::ChangeMenuWidget(TSubclassOf<UUserWidget> NewWidgetClass)
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

void AVGP221GameModeBase::HideMenu()
{
	CurrentWidget->HideMenu();
}

void AVGP221GameModeBase::ShowMenu()
{
	CurrentWidget->ShowMenu();
}

void AVGP221GameModeBase::PauseGame()
{
	UWorld* World = GetWorld();
	if (!World) return;
	World->GetWorldSettings()->SetTimeDilation(0);
}

void AVGP221GameModeBase::StartGame()
{
	UWorld* World = GetWorld();
	if (!World) return;
	World->GetWorldSettings()->SetTimeDilation(1);

	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	if (PlayerController) {
		PlayerController->bShowMouseCursor = false;

		FInputModeGameOnly InputMode;
		PlayerController->SetInputMode(InputMode);
	}
}

void AVGP221GameModeBase::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	EnemyTimer -= DeltaTime;
	if (EnemyTimer < 0.0f) {
		UE_LOG(LogTemp, Warning, TEXT("Spawning enemy"));
		EnemyTimer = 2.0f;

		UWorld* world = GetWorld();
		if (world) {
			ACharacter* myCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
			if (myCharacter) {
				FVector playerLocation = myCharacter->GetActorLocation();
				FVector enemyLocation = playerLocation;
				float randomDistance = FMath::RandRange(500.0f, 800.0f);
				enemyLocation.X += randomDistance;
				enemyLocation.Y += randomDistance;

				int randomNumber = FMath::RandRange(0, 2);
				AEnemy* enemy;
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
}

void AVGP221GameModeBase::BeginPlay() {
	Super::BeginPlay();
}

