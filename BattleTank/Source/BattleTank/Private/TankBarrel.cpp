// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankBarrel.h"

void UTankBarrel::Elevate(float relativeSpeed)
{
	// move the barrel ethee right amoiunt this frame
	// given a max elevation speed, and the frame time

	relativeSpeed = FMath::Clamp<float>(relativeSpeed, -1, 1);

	auto elevationChange = relativeSpeed * maxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto rawNewElevation = RelativeRotation.Pitch + elevationChange;
	
	auto elevation = FMath::Clamp<float>(rawNewElevation, minElevationDegrees, maxElevationDegrees);

	SetRelativeRotation(FRotator(elevation, 0, 0));
}
 