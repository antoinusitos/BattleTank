// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

class ATank;

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
private:

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;
	
	ATank* GetControlledTank() const;

	//start the tank moving the barrel so that a shoot whould hit where
	//the crosshait intersects the world
	void AimTowardsCrosshair();

	bool GetSightRayHitLocation(FVector& outHitLocation) const;

	bool GetLookDirection(FVector2D screenLocation, FVector& lookDirection) const;

	bool GetLookVectorHitLocation(FVector dir, FVector& outHitLocation) const;
	
public:

UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	float crosshairXLocation = 0.5f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	float crosshairYLocation = 0.33333f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	float lineTraceRange = 1000000;

};
