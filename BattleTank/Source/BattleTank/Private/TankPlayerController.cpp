// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "Tank.h"
#include "TankPlayerController.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	auto controlledTank = GetControlledTank();
	if (!controlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("player controller is not possessing a tank"));
	}
	else
	{
		FString pawnName = controlledTank->GetName();
		UE_LOG(LogTemp, Warning, TEXT("pawn possessed : %s"), *pawnName);
	}

}

void ATankPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	AimTowardsCrosshair();
}

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetControlledTank())
	{
		return;
	}

	FVector hitLocation; // out parameter
	if (GetSightRayHitLocation(hitLocation))
	{
		GetControlledTank()->AimAt(hitLocation);
	}
		
}

//Get world location through crosshair, true if hits the landscape
bool ATankPlayerController::GetSightRayHitLocation(FVector& outHitLocation) const
{
	//crosshair position in pixel coordinates
	int32 viewportSizeX;
	int32 viewportSizeY;
	GetViewportSize(viewportSizeX, viewportSizeY);
	auto screenLocation = FVector2D(viewportSizeX * crosshairXLocation, viewportSizeY * crosshairYLocation);

	//De-project crosshair screen position to a world direction
	FVector camDirection;
	if (GetLookDirection(screenLocation, camDirection))
	{
		//linetrace along that camDirection and see what we hit(up to max range)
		GetLookVectorHitLocation(camDirection, outHitLocation);
	}

	return true;
}

bool ATankPlayerController::GetLookDirection(FVector2D screenLocation, FVector& lookDirection) const
{
	FVector camLocation; //to be discarded
	return DeprojectScreenPositionToWorld(screenLocation.X, screenLocation.Y, camLocation, lookDirection);
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector dir, FVector& outHitLocation) const
{
	FHitResult hitResult;

	FVector start = PlayerCameraManager->GetCameraLocation();
	FVector end = start + (dir * lineTraceRange);

	if (GetWorld()->LineTraceSingleByChannel(hitResult, start, end, ECC_Visibility))
	{
		outHitLocation = hitResult.Location;
		return true;
	}

	outHitLocation = FVector(0);
	return false;
}
