// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTanks.h"
#include "TankAIController.h"

void ATankAIController::BeginPlay() {
	Super::BeginPlay();

	auto playerTank = GetPlayerTank();

	if (!playerTank) {
		UE_LOG(LogTemp, Warning, TEXT("AI controller did not found a player"));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("AI controller found player: %s"), *(playerTank->GetName()));
	}
}

void ATankAIController::Tick(float DeltaTime)  {
	Super::Tick(DeltaTime);
	
	if (GetPlayerTank()) {
		GetControlledTank()->AimAt(GetPlayerTank()->GetActorLocation());
	}
}

ATank* ATankAIController::GetControlledTank() const {
	return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerTank() const {

	auto playerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();

	if (!playerPawn) {
		return nullptr;
	}

	return Cast<ATank>(playerPawn);
}
