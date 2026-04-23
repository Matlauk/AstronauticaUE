// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/Player/Movement/GroundedMovementSolver.h"
#include "Gameplay/Player/AstroPlayerMovementComponent.h"
#include "Gameplay/Player/AstroPlayerPawn.h"

#include "Math/RotationMatrix.h"

FGroundedMovementSolver::FGroundedMovementSolver()
{
}

FGroundedMovementSolver::~FGroundedMovementSolver()
{
}

void FGroundedMovementSolver::Enter(UAstroPlayerMovementComponent& MovementComponent)
{
}

void FGroundedMovementSolver::Exit(UAstroPlayerMovementComponent& MovementComponent)
{
}

void FGroundedMovementSolver::Simulate(UAstroPlayerMovementComponent& MovementComponent, float DeltaTime)
{
	if (DeltaTime <= 0.0f || MovementComponent.UpdatedComponent == nullptr)
	{
		return;
	}

	const AAstroPlayerPawn* AstroPawn = Cast<AAstroPlayerPawn>(MovementComponent.GetPawnOwner());
	if (AstroPawn == nullptr)
	{
		return;
	}

	FVector2D MoveInput(
		AstroPawn->GetMoveForwardBackwardInput(),
		AstroPawn->GetMoveLeftRightInput());
	MoveInput = MoveInput.GetClampedToMaxSize(1.0f);

	if (MoveInput.IsNearlyZero())
	{
		return;
	}

	const FRotator ControlRotation = AstroPawn->GetControlRotation();
	const FRotator YawRotation(0.0f, ControlRotation.Yaw, 0.0f);
	const FVector ForwardVector = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightVector = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	const FVector MoveDirection = (ForwardVector * MoveInput.X) + (RightVector * MoveInput.Y);
	const FVector Delta = MoveDirection.GetSafeNormal() * MovementComponent.GetGroundedMoveSpeed() * DeltaTime;

	FHitResult Hit;
	MovementComponent.MoveUpdatedComponent(Delta, MovementComponent.UpdatedComponent->GetComponentQuat(), true, &Hit);
}
