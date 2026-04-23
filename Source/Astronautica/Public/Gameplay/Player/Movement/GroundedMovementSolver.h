// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MovementSolverBase.h"

/**
 * 
 */
class ASTRONAUTICA_API FGroundedMovementSolver : public FMovementSolverBase
{
public:
	FGroundedMovementSolver();
	virtual ~FGroundedMovementSolver() override;
	
	virtual void Enter(UAstroPlayerMovementComponent& MovementComponent) override;
	virtual void Exit(UAstroPlayerMovementComponent& MovementComponent) override;
	virtual void Simulate(UAstroPlayerMovementComponent& MovementComponent, float DeltaTime) override;
};
