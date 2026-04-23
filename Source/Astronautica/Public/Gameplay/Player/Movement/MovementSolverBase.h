// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

class UAstroPlayerMovementComponent;
/**
 * 
 */
class ASTRONAUTICA_API FMovementSolverBase
{
public:
	FMovementSolverBase();
	virtual ~FMovementSolverBase();
	
	virtual void Enter(UAstroPlayerMovementComponent& MovementComponent) = 0;
	virtual void Exit(UAstroPlayerMovementComponent& MovementComponent) = 0;
	virtual void Simulate(UAstroPlayerMovementComponent& MovementComponent, float DeltaTime) = 0;
};
