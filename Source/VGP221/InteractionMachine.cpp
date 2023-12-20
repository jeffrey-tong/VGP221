// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractionMachine.h"
#include <Kismet/GameplayStatics.h>
#include "FPSCharacter.h"

// Sets default values
AInteractionMachine::AInteractionMachine()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AInteractionMachine::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AInteractionMachine::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AInteractionMachine::Interact()
{
	AFPSCharacter* Player = Cast<AFPSCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	if (!Player) return;
	if (Player->GetMoney() >= 5) {
		Player->AddMoney(-5);
		Player->GiveBuff();
	}
	
}

