// Copyright Spelgarden ENK and EmbraceIT Ltd.

#include "TankAIController.h"
#include "TankAimingComponent.h"
#include "Tank.h"	// So we can implement OnDeath
// Depends on movement component via pathfinding system


void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ATankAIController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);
	if (InPawn)
	{
		auto PossessedTank = Cast<ATank>(InPawn);
		if (!ensure(PossessedTank)) { return; }

		// Subscribe our local method to the tank's death event
		PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankAIController::OnPossessedTankDeath);
	}
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	auto ControlledTank = GetPawn();

	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();

	if (!ensure(PlayerTank && ControlledTank)) { return; }
	
	// Move towards the player
	MoveToActor(PlayerTank, AcceptanceRadius);	//TODO check radius is in cm.

	// Aim towards the player	
	auto AimingComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimingComponent)) { return; }
	AimingComponent->AimAt(PlayerTank->GetActorLocation());

	// if Aiming or Locked
	if (AimingComponent->GetFiringState() == EFiringState::Locked)
	{
		AimingComponent->Fire();	//TODO limit firing rate
	}
	
}

void ATankAIController::OnPossessedTankDeath()
{
	UE_LOG(LogTemp, Warning, TEXT("Death event received at TankAIController!"))

	auto ControlledTank = GetPawn();		
	if (!ensure(ControlledTank)) { return; }
	ControlledTank->DetachFromControllerPendingDestroy();
}
