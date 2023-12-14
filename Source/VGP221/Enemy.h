// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/BoxComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "FPSCharacter.h"
#include "Enemy.generated.h"

UCLASS()
class VGP221_API AEnemy : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	class UBoxComponent* DamageCollisionComponent;

	UPROPERTY(VisibleDefaultsOnly, Category = "Enemy")
	class UAIPerceptionComponent* AIPerceptionComponent;

	UPROPERTY(VisibleDefaultsOnly, Category = "Enemy")
	class UAISenseConfig_Sight* SightConfig;

	UPROPERTY(VisibleAnywhere, Category = "Movement")
	FRotator EnemyRotation;

	UPROPERTY(VisibleAnywhere, Category = "Movement")
	FVector BaseLocation;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
	FVector CurrentVelocity;

	UPROPERTY(VisibleAnywhere, Category = "Movement")
	float MovementSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Health = 100.0f;

	UPROPERTY(EditAnywhere)
	float DamageValue = 5.0f;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit);

	UFUNCTION()
	void OnSensed(const TArray<AActor*>& UpdatedActors);

	void SetNewRotation(FVector TargetPosition, FVector CurrentPosition);

	bool BackToBaseLocation;
	FVector NewLocation;
	float DistanceSquared;

	void DealDamage(float DamageAmount);
};
