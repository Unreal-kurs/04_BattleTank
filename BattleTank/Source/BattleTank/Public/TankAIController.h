// Copyright Spelgarden ENK and EmbraceIT Ltd.

#pragma once

#include "AIController.h"
#include "CoreMinimal.h"
#include "Engine/World.h"
#include "TankAIController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;
	
	virtual void Tick(float DeltaTime) override;

	// How close can the AI tank get (to the player)
	float AcceptanceRadius = 3000;
};
