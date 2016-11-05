// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "Tank.h"
#include "TankAimingComponent.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	tankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("Aiming Component"));
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

}

void ATank::AimAt(FVector hitLocation) const
{
	if (tankAimingComponent != nullptr)
	{
		tankAimingComponent->AimAt(hitLocation, launchSpeed);
	}
}

void ATank::SetBarrelReference(UTankBarrel* barrelToSet)
{
	if (tankAimingComponent != nullptr)
	{
		tankAimingComponent->SetBarrelReference(barrelToSet);
	}
}