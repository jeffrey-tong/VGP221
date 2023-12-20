// Fill out your copyright notice in the Description page of Project Settings.

#include "FPSCharacter.h"
#include "Enemy.h"
#include "GameFramework/Actor.h"


// Sets default values
AFPSCharacter::AFPSCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// FPS Camera
	// Instantiate in constructors
	FPSCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	check(FPSCameraComponent != nullptr);

	FPSCameraComponent->SetupAttachment(CastChecked<USceneComponent, UCapsuleComponent>(GetCapsuleComponent()));
	FPSCameraComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 50.0f + BaseEyeHeight));
	FPSCameraComponent->bUsePawnControlRotation = true;

	// Mesh
	FPSMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FirstPersonMesh"));
	check(FPSMesh != nullptr);

	FPSMesh->SetupAttachment(FPSCameraComponent);
	FPSMesh->bCastDynamicShadow = false;
	FPSMesh->CastShadow = false;

	GetMesh()->SetOwnerNoSee(true);

	UCharacterMovementComponent* CharacterMovementComponent = GetCharacterMovement();
	if (CharacterMovementComponent) {
		CharacterMovementComponent->MaxWalkSpeed = 600.0f;
		SprintSpeedMultiplier = 1.5f;
	}
	
}

// Called when the game starts or when spawned
void AFPSCharacter::BeginPlay()
{
	Super::BeginPlay();

	check(GEngine != nullptr)
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("Spawning BP_FPSCharacter")));

	UE_LOG(LogTemp, Warning, TEXT("Spawning BP_FPSCharacter"));
}

// Called every frame
void AFPSCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AFPSCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Movement
	PlayerInputComponent->BindAxis("MoveForward", this, &AFPSCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AFPSCharacter::MoveRight);

	// Look
	PlayerInputComponent->BindAxis("LookHorizontal", this, &AFPSCharacter::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookVertical", this, &AFPSCharacter::AddControllerPitchInput);

	// Jump
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AFPSCharacter::StartJump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &AFPSCharacter::EndJump);

	// Fire
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AFPSCharacter::Fire);

	//Sprint
	PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &AFPSCharacter::Sprint);
	PlayerInputComponent->BindAction("Sprint", IE_Released, this, &AFPSCharacter::EndSprint);

	//Interact
	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &AFPSCharacter::Interact);
}

void AFPSCharacter::MoveForward(float value)
{
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
	AddMovementInput(Direction, value);
}

void AFPSCharacter::MoveRight(float value)
{
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);
	AddMovementInput(Direction, value);
}

void AFPSCharacter::StartJump()
{
	bPressedJump = true;
}

void AFPSCharacter::EndJump()
{
	bPressedJump = false;
}

void AFPSCharacter::Fire()
{
	UE_LOG(LogTemp, Warning, TEXT("Pressing Fire From Character"));

	if (!ProjectileClass) return;

	// Precaculations of loc and rot
	FVector CameraLocation;
	FRotator CameraRotation;
	GetActorEyesViewPoint(CameraLocation, CameraRotation);

	MuzzleOffset.Set(100.0f, 0.0f, 0.0f);

	FVector MuzzleLocation = CameraLocation + FTransform(CameraRotation).TransformVector(MuzzleOffset);
	FRotator MuzzleRotation = CameraRotation;
	MuzzleRotation.Pitch += 10.0f;

	// Get World to spawn actor
	UWorld* World = GetWorld();
	if (!World) return;

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	SpawnParams.Instigator = GetInstigator();

	// Similar to unity Instantiate. Spawn Actor from class
	AFPSProjectile* Projectile = World->SpawnActor<AFPSProjectile>(ProjectileClass, MuzzleLocation, MuzzleRotation, SpawnParams);

	// Shoot projectile in direction
	if (!Projectile) return;
	Projectile->SetDamage(ProjectileDamageValue);
	FVector LaunchDirection = MuzzleRotation.Vector();
	Projectile->FireInDirection(LaunchDirection);
}

void AFPSCharacter::Sprint()
{
	GetCharacterMovement()->MaxWalkSpeed *= SprintSpeedMultiplier;
}

void AFPSCharacter::EndSprint()
{
	GetCharacterMovement()->MaxWalkSpeed /= SprintSpeedMultiplier;
}

void AFPSCharacter::Interact()
{
	UE_LOG(LogTemp, Warning, TEXT("Pressing Interact"));
	
	// Precaculations of loc and rot
	FVector CameraLocation;
	FRotator CameraRotation;
	GetActorEyesViewPoint(CameraLocation, CameraRotation);

	FVector Start = CameraLocation;
	FVector ForwardVector = CameraRotation.Vector();

	FVector End = Start + (ForwardVector * 1000.0f);
	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(this);

	//draw raycast
	DrawDebugLine(GetWorld(), Start, End, FColor::Red, false, 1, 0, 1);
	bool IsHit = GetWorld()->LineTraceSingleByChannel(InteractHitResult, Start, End, ECC_GameTraceChannel2, CollisionParams);

	if (IsHit) {
		if (Cast<AInteractionMachine>(InteractHitResult.GetActor())) {
			AInteractionMachine* interactMachine = Cast<AInteractionMachine>(InteractHitResult.GetActor());
			interactMachine->Interact();
		}
	}
}

int AFPSCharacter::GetMoney()
{
	return Money;
}

void AFPSCharacter::AddMoney(int num)
{
	Money += num;
	AVGP221GameModeBase* GameMode = Cast<AVGP221GameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	if (GameMode) {
		GameMode->CurrentWidget->SetMoneyText(Money);
	}
}

void AFPSCharacter::DealDamage(float DamageAmount)
{
	// Nice easy way to get game mode from anywhere
	AVGP221GameModeBase* GameMode = Cast<AVGP221GameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	if (GameMode) {
		Health -= DamageAmount;
		float healthPercent = Health / MaxHealth;

		GameMode->CurrentWidget->SetHealthBar(healthPercent);

		if (Health <= 0.0f) {
			GameOver();
		}
	}
}

void AFPSCharacter::GiveBuff()
{
	int randomBuff = FMath::RandRange(0, 3);
	switch (randomBuff) {
	case 0:
		UE_LOG(LogTemp, Warning, TEXT("Damage Buff"));
		ProjectileDamageValue += 5;
		break;
	case 1:
		UE_LOG(LogTemp, Warning, TEXT("MoveSpeed Buff"));
		GiveMoveSpeed();
		break;
	case 2:
		UE_LOG(LogTemp, Warning, TEXT("Sprint Buff"));
		GiveSprintSpeed();
		break;
	case 3:
		UE_LOG(LogTemp, Warning, TEXT("Heal Buff"));
		HealPlayer();
		break;
	}
}

void AFPSCharacter::GiveMoveSpeed()
{
	GetCharacterMovement()->MaxWalkSpeed += 100;
}

void AFPSCharacter::GiveSprintSpeed()
{
	SprintSpeedMultiplier += 0.5;
}

void AFPSCharacter::HealPlayer()
{
	// Nice easy way to get game mode from anywhere
	AVGP221GameModeBase* GameMode = Cast<AVGP221GameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	if (GameMode) {
		Health += 10;
		if (Health >= MaxHealth) {
			Health = MaxHealth;
		}
		float healthPercent = Health / MaxHealth;

		GameMode->CurrentWidget->SetHealthBar(healthPercent);
	}
}

void AFPSCharacter::GameOver()
{
	AVGP221GameModeBase* GameMode = Cast<AVGP221GameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	if (GameMode) {
		GameMode->ShowMenu();
		GameMode->PauseGame();
		Health = 100;
		ProjectileDamageValue = 20.0;
		SprintSpeedMultiplier = 1.5f;
		GetCharacterMovement()->MaxWalkSpeed = 600.0f;

		APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
		if (PlayerController) {
			PlayerController->bShowMouseCursor = true;

			FInputModeUIOnly InputMode;
			PlayerController->SetInputMode(InputMode);
		}
	}
}
