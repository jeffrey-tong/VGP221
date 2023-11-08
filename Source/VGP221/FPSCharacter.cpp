// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSCharacter.h"

// Sets default values
AFPSCharacter::AFPSCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// FPS Camera
	// Instantiate in constructors 
	FPSCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FPSCamera"));
	check(FPSCameraComponent != nullptr);

	FPSCameraComponent->SetupAttachment(CastChecked<USceneComponent, UCapsuleComponent>(GetCapsuleComponent()));
	FPSCameraComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 50.0f + BaseEyeHeight));
	FPSCameraComponent->bUsePawnControlRotation = true;

	// Mesh
	FPSMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FPSMesh"));
	check(FPSMesh != nullptr);

	FPSMesh->SetupAttachment(FPSCameraComponent);
	FPSMesh->bCastDynamicShadow = false;
	FPSMesh->CastShadow = false;

	GetMesh()->SetOwnerNoSee(true);

}

// Called when the game starts or when spawned
void AFPSCharacter::BeginPlay()
{
	Super::BeginPlay();


	check(GEngine != nullptr)
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Spawning BP_FPSCharacter")));
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
	
	//Movement
	PlayerInputComponent->BindAxis("MoveForward", this, &AFPSCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AFPSCharacter::MoveRight);
	//Look
	PlayerInputComponent->BindAxis("LookHorizontal", this, &AFPSCharacter::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookVertical", this, &AFPSCharacter::AddControllerPitchInput);
	//Jump
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AFPSCharacter::StartJump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &AFPSCharacter::EndJump);
	//Fire
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AFPSCharacter::Fire);
	//Sprint
	PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &AFPSCharacter::Sprint);
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

	FVector CameraLocation;
	FRotator CameraRotation;
	GetActorEyesViewPoint(CameraLocation, CameraRotation);

	MuzzleOffset.Set(100.0f, 0.0f, 0.0f);

	FVector MuzzleLocation = CameraLocation + FTransform(CameraRotation).TransformVector(MuzzleOffset);
	FRotator MuzzleRotation = CameraRotation;
	MuzzleRotation.Pitch += 10.0f;

	UWorld* World = GetWorld();
	if (!World) return;

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	SpawnParams.Instigator = GetInstigator();

	AFPSProjectile* Projectile = World->SpawnActor<AFPSProjectile>(ProjectileClass, MuzzleLocation, MuzzleRotation, SpawnParams);
	if (!Projectile) return;

	FVector LaunchDirection = MuzzleRotation.Vector();
	Projectile->FireInDirection(LaunchDirection);
}

void AFPSCharacter::Sprint()
{
	
}


