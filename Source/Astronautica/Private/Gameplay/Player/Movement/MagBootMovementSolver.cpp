// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/Player/Movement/MagBootMovementSolver.h"
#include "Gameplay/Player/AstroPlayerMovementComponent.h"

FMagBootMovementSolver::FMagBootMovementSolver()
{
}

FMagBootMovementSolver::~FMagBootMovementSolver()
{
}

void FMagBootMovementSolver::Enter(UAstroPlayerMovementComponent& MovementComponent)
{
	UE_LOG(LogTemp, Log, TEXT("MagBootMovementSolver Enter"));
	MovementComponent.SetUpdatedComponentPhysicsState(false, false);
}

void FMagBootMovementSolver::Exit(UAstroPlayerMovementComponent& MovementComponent)
{
	UE_LOG(LogTemp, Log, TEXT("MagBootMovementSolver Exit"));
}

void FMagBootMovementSolver::Simulate(UAstroPlayerMovementComponent& MovementComponent, float DeltaTime)
{
}
