// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/SphereComponent.h"
#include "Components/BoxComponent.h"
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

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	bool PlayerDetected;
	bool CanAttackPlayer;

	UPROPERTY(BlueprintReadWrite)
	bool CanDoDamage;

	class AEnemy_AICharacter* PlayerRef;

	UPROPERTY(EditAnywhere)
	class USphereComponent* PlayerCollisionDetection;
	
	UPROPERTY(EditAnywhere)
	class USphereComponent* PlayerAttackCollisionDetection;
	
	UPROPERTY(EditAnywhere)
	class UBoxComponent* DamageCollision;

};
