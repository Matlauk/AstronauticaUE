// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/Player/AstroPlayerMovementComponent.h"

#include "Gameplay/Player/AstroPlayerPawn.h"

UAstroPlayerMovementComponent::UAstroPlayerMovementComponent()
{
	CurrentMovementSolver = &GroundedMovementSolver;
}

void UAstroPlayerMovementComponent::BeginPlay()
{
	Super::BeginPlay();

	// Enter the default movement mode
	CurrentMovementSolver->Enter(*this);
}

void UAstroPlayerMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (CurrentMovementSolver)
	{
		CurrentMovementSolver->Simulate(*this, DeltaTime);
	}
}

void UAstroPlayerMovementComponent::SetMovementMode(EAstraMovementMode NewMode)
{
	if (NewMode == MovementMode)
	{
		return;
	}
	
	FMovementSolverBase& OldSolver = *CurrentMovementSolver;
	FMovementSolverBase& NewSolver = GetMovementSolver(NewMode);
	
	OldSolver.Exit(*this);
	MovementMode = NewMode;
	CurrentMovementSolver = &NewSolver;
	NewSolver.Enter(*this);
	
	if (AAstroPlayerPawn* Pawn = Cast<AAstroPlayerPawn>(GetPawnOwner()))
	{
		Pawn->HandleMovementModeChanged(NewMode);
	}
}

FMovementSolverBase& UAstroPlayerMovementComponent::GetMovementSolver(EAstraMovementMode InMovementMode)
{
	switch (InMovementMode)
	{
	case EAstraMovementMode::Grounded:
		return GroundedMovementSolver;
	case EAstraMovementMode::MagBoots:
		return MagBootMovementSolver;
	case EAstraMovementMode::ZeroG:
		return ZeroGravityMovementSolver;
	default:
		checkNoEntry();
		return GroundedMovementSolver; // Fallback
	}
}
