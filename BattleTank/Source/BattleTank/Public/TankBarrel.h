// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	// -1 is max downward speed and +1 is max up movement
	void Elevate(float relativeSpeed);
	
private:
	UPROPERTY(EditAnywhere, Category = "Setup")
	float maxDegreesPerSecond = 20;

	UPROPERTY(EditAnywhere, Category = "Setup")
	float maxElevationDegrees = 40;

	UPROPERTY(EditAnywhere, Category = "Setup")
	float minElevationDegrees = 0;
};
