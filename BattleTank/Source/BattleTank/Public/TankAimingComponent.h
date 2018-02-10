// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "TankAimingComponent.generated.h"

// Forward declaration
class UTankBarrel;	

// Holds barrel's properties and Elevate method
UCLASS( meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

	void SetBarrelReference(UTankBarrel* BarrelToSet);

	// TODO add SetTurretReference

	void AimAt(FVector HitLocation, float LaunchSpeed);
	
private:
	UTankBarrel* Barrel = nullptr;
	void MoveBarrelTowards(FVector AimDirection);
};
