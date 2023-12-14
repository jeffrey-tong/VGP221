// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"

// Sets default values
AEnemy::AEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	if (!RootComponent) {
		RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("EnemyRootComponent"));
	}
	if (!DamageCollisionComponent) {
		DamageCollisionComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Damage Collision"));
		DamageCollisionComponent->SetupAttachment(RootComponent);
	}
	if (!AIPerceptionComponent) {
		AIPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AI Perception Component"));
		SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight Config"));

		SightConfig->SightRadius = 10000.0f;
		SightConfig->LoseSightRadius = 12000.0f;
		SightConfig->PeripheralVisionAngleDegrees = 180.0f;
		SightConfig->DetectionByAffiliation.bDetectEnemies = true;
		SightConfig->DetectionByAffiliation.bDetectFriendlies = false;
		SightConfig->DetectionByAffiliation.bDetectNeutrals = false;
		SightConfig->SetMaxAge(0.1f);
		
		AIPerceptionComponent->SetDominantSense(SightConfig->GetSenseImplementation());
		AIPerceptionComponent->OnPerceptionUpdated.AddDynamic(this, &AEnemy::OnSensed);
		AIPerceptionComponent->ConfigureSense(*SightConfig);

		AIPerceptionComponent->RegisterComponent();
	}

	CurrentVelocity = FVector::ZeroVector;
	MovementSpeed = 395.0f;
	DistanceSquared = BIG_NUMBER;
}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();

	DamageCollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &AEnemy::OnHit);
	BaseLocation = this->GetActorLocation();
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!CurrentVelocity.IsZero()) {
		NewLocation = GetActorLocation() + CurrentVelocity * DeltaTime;

		if (BackToBaseLocation) {
			if ((NewLocation - BaseLocation).SizeSquared2D() < DistanceSquared) {
				DistanceSquared = (NewLocation - BaseLocation).SizeSquared2D();
			}
			else {
				CurrentVelocity = FVector::ZeroVector;
				DistanceSquared = BIG_NUMBER;
				BackToBaseLocation = false;

				SetNewRotation(GetActorForwardVector(), GetActorLocation());
			}
		}

		SetActorLocation(NewLocation);
	}
}

void AEnemy::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit)
{
	AFPSCharacter* Player = Cast<AFPSCharacter>(OtherActor);
	if (Player) {
		Player->DealDamage(DamageValue);
	}
}
void AEnemy::OnSensed(const TArray<AActor*>& UpdatedActors)
{
	for (int i = 0; i < UpdatedActors.Num(); i++) {
		FActorPerceptionBlueprintInfo Info;

		AIPerceptionComponent->GetActorsPerception(UpdatedActors[i], Info);

		if (AFPSCharacter* PlayerCharacter = Cast<AFPSCharacter>(UpdatedActors[i])) {
			FVector dir = PlayerCharacter->GetActorLocation() - GetActorLocation();
			dir.Z = 0.0f;

			CurrentVelocity = dir.GetSafeNormal() * MovementSpeed;
			SetNewRotation(PlayerCharacter->GetActorLocation(), GetActorLocation());
		}
		/*else {
			FVector dir = BaseLocation - GetActorLocation();
			dir.Z = 0.0f;

			if (dir.SizeSquared2D() > 1.0f) {
				CurrentVelocity = dir.GetSafeNormal() * MovementSpeed;
				BackToBaseLocation = true;

				SetNewRotation(BaseLocation, GetActorLocation());
			}
		}*/
	}

}

void AEnemy::SetNewRotation(FVector TargetPosition, FVector CurrentPosition)
{
	FVector NewDirection = TargetPosition - CurrentPosition;
	NewDirection.Z = 0.0f;

	EnemyRotation = NewDirection.Rotation();

	SetActorRotation(EnemyRotation);
}

void AEnemy::DealDamage(float DamageAmount)
{
	Health -= DamageAmount;
	if (Health <= 0.0f) {
		Destroy();
	}
}