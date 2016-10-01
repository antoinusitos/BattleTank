// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankBarrel.h"
#include "TankAimingComponent.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


void UTankAimingComponent::SetBarrelReference(UTankBarrel* barrelToSet)
{
	barrel = barrelToSet;
}

void UTankAimingComponent::AimAt(FVector hitLocation, float launchSpeed)
{
	if (!barrel) return;

	FVector outLaunchVelocity;
	FVector startLocation = barrel->GetSocketLocation(FName("projectile"));

	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity
	(
		this,
		outLaunchVelocity,
		startLocation,
		hitLocation,
		launchSpeed,
		ESuggestProjVelocityTraceOption::DoNotTrace
	);

	if(bHaveAimSolution)
	{
		auto aimDirection = outLaunchVelocity.GetSafeNormal();
		MoveBarrelTowards(aimDirection);
		auto time = GetWorld()->GetTimeSeconds();
		UE_LOG(LogTemp, Warning, TEXT("%f : aim solve found"), time);
	}
	else
	{
		auto time = GetWorld()->GetTimeSeconds();
		UE_LOG(LogTemp, Warning, TEXT("%f : no aim solve found"), time);
	}
}

void UTankAimingComponent::MoveBarrelTowards(FVector aimDirection)
{
	// work out difference between current barrel reaction, and aim direction
	auto barrelRotator = barrel->GetForwardVector().Rotation();
	auto aimAsRotator = aimDirection.Rotation();
	auto deltaRotator = aimAsRotator - barrelRotator;

	barrel->Elevate(5);

}