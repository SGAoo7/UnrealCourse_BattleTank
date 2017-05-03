// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTanks.h"
#include "TankPlayerController.h"


void ATankPlayerController::BeginPlay() {
	Super::BeginPlay();

	auto controlledTank = GetControlledTank();

	if (!controlledTank) {
		UE_LOG(LogTemp, Warning, TEXT("Player controller not possesing a tank"));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Player controller possesing: %s"), *(controlledTank->GetName()));
	}
}

void ATankPlayerController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
}

ATank* ATankPlayerController::GetControlledTank() const {
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair() {
	if (!GetControlledTank()) {
		return;
	}

	FVector hitLocation;

	if (GetSightRayHitLocation(hitLocation)) {
		GetControlledTank()->AimAt(hitLocation);
	}
}

bool ATankPlayerController::GetSightRayHitLocation(FVector& outHitLocation) const {
	
	int32 viewportSizeX, viewportSizeY;
	GetViewportSize(viewportSizeX, viewportSizeY);

	FVector2D screenLocation;
	screenLocation.X = viewportSizeX * crosshairXLocation;
	screenLocation.Y = viewportSizeY * crosshairYLocation;
	
	FVector LookDirection;
	if (GetLookDirection(screenLocation, LookDirection)) {
		// Line-trace along that LookDirection, and see what we hit (up to max range)
		GetLookVectorHitLocation(LookDirection, outHitLocation);
	}

	return true;
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector _lookDirection, FVector& _hitLocation) const {
	FHitResult outHitResult;
	auto startLocation = PlayerCameraManager->GetCameraLocation();
	auto endLocation = startLocation + (_lookDirection * lineTraceRnage);

	if (GetWorld()->LineTraceSingleByChannel(
		outHitResult,
		startLocation,
		endLocation,
		ECollisionChannel::ECC_Visibility)
		) 
	{
		_hitLocation = outHitResult.Location;
		return true;
	}

	_hitLocation = FVector(0);
	return false;
}

bool ATankPlayerController::GetLookDirection(FVector2D _screenLocation, FVector& _lookDirection) const {
	FVector CameraWorldLocation; // To be discarded
	
	return  DeprojectScreenPositionToWorld(
		_screenLocation.X,
		_screenLocation.Y,
		CameraWorldLocation,
		_lookDirection
	);
}