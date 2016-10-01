// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "TankAimingComponent.h"
#include "Tank.generated.h"

class UTankBarrel;

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:

	void AimAt(FVector hitLocation) const;

	UFUNCTION(BlueprintCallable, Category = "Component")
	void SetBarrelReference(UTankBarrel* barrelToSet);

protected:

	UTankAimingComponent* tankAimingComponent = nullptr;
	

private:
	// Sets default values for this pawn's properties
	ATank();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	UPROPERTY(EditAnywhere, Category = "Projectile")
	float launchSpeed = 100000; // TODO find sensible default
	
};
