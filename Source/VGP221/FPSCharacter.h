// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Animation/AnimInstance.h"
#include "VGP221GameModeBase.h"
#include "FPSProjectile.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "InteractionMachine.h"
#include "FPSCharacter.generated.h"

UCLASS()
class VGP221_API AFPSCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AFPSCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	UPROPERTY(VisibleAnywhere)
	UCameraComponent* FPSCameraComponent;

	UPROPERTY(VisibleDefaultsOnly, Category = "Mesh")
	USkeletalMeshComponent* FPSMesh;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
	FVector MuzzleOffset;

	UPROPERTY(EditDefaultsOnly, Category = "Projectile")
	TSubclassOf<class AFPSProjectile> ProjectileClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
	USoundBase* FireSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
	UAnimMontage* FireAnimation;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
	float SprintSpeedMultiplier;

	UFUNCTION()
	void MoveForward(float value);
	UFUNCTION()
	void MoveRight(float value);

	UFUNCTION()
	void StartJump();
	UFUNCTION()
	void EndJump();

	UFUNCTION()
	void Fire();

	UFUNCTION()
	void Sprint();
	UFUNCTION()
	void EndSprint();

	UFUNCTION()
	void Interact();
	
	FHitResult InteractHitResult;

	float Health = 100;
	const float MaxHealth = 100;

	float ProjectileDamageValue = 20.0;

	float Money = 0;
	
	UFUNCTION()
	int GetMoney();

	UFUNCTION()
	void AddMoney(int num);

	UFUNCTION()
	void DealDamage(float DamageAmount);

	UFUNCTION()
	void GiveBuff();

	UFUNCTION()
	void GiveMoveSpeed();

	UFUNCTION()
	void GiveSprintSpeed();

	UFUNCTION()
	void HealPlayer();

	UFUNCTION()
	void GameOver();
};
