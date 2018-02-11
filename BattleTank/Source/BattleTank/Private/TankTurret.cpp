// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTurret.h"

void UTankTurret::Rotate(float RelativeSpeed)
{
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1.f, +1.f);
	auto RotationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto RawNewRotation = RelativeRotation.Pitch + RotationChange;
	auto Rotation = FMath::Clamp<float>(RawNewRotation, -180.f, 180.f);

	SetRelativeRotation(FRotator(0, Rotation, 0));
}


