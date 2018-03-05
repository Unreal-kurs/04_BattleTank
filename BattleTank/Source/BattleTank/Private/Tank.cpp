// Copyright Spelgarden ENK

#include "Tank.h"
#include "TankBarrel.h"
#include "Projectile.h"
#include "TankAimingComponent.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();	// Needed for BP BeginPlay to run
	TankAimingComponent = FindComponentByClass<UTankAimingComponent>();

	LastFireTime = GetWorld()->TimeSeconds;
}

void ATank::AimAt(FVector HitLocation)
{
	if ( !ensure(TankAimingComponent) ) { return; }
	TankAimingComponent->AimAt(HitLocation, LaunchSpeed);
}

void ATank::Fire()
{
	if ( !ensure(Barrel) ) { return; }
	
	bool isReloaded = GetWorld()->TimeSeconds - LastFireTime > ReloadTimeInSeconds;

	if (isReloaded) 
	{		
		// Spawn a projectile at the socket location on the barrel
		auto Projectile = GetWorld()->SpawnActor<class AProjectile>(
			ProjectileBlueprint,
			Barrel->GetSocketLocation(FName("Projectile")),
			Barrel->GetSocketRotation(FName("Projectile"))
			);

		if (Projectile)
		{
			Projectile->LaunchProjectile(LaunchSpeed);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Projectile is null"))
		}

		LastFireTime = GetWorld()->TimeSeconds;
	}
}


