// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tank.h"

#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANKS_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	ATank* GetControlledTank() const;

private:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	//aims towards crosshair;
	void AimTowardsCrosshair();

	//gets location from raycast;
	bool GetSightRayHitLocation(FVector& outHitLocation) const;

	UPROPERTY(EditAnywhere)
		float crosshairXLocation = 0.5f;

	UPROPERTY(EditAnywhere)
		float crosshairYLocation = 0.33333f;

	bool GetLookDirection(FVector2D _screenLocation, FVector& _lookDirection) const;
	bool GetLookVectorHitLocation(FVector _lookDirection, FVector& _hitLocation) const;

	UPROPERTY(EditAnywhere)
		float lineTraceRnage = 1000000;
};
