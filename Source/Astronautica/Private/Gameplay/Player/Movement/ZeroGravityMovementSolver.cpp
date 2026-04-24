// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/Player/Movement/ZeroGravityMovementSolver.h"
#include "Gameplay/Player/AstroPlayerMovementComponent.h"
#include "Gameplay/Player/AstroPlayerPawn.h"

#include "Components/PrimitiveComponent.h"

FZeroGravityMovementSolver::FZeroGravityMovementSolver()
{
}

FZeroGravityMovementSolver::~FZeroGravityMovementSolver()
{
}

void FZeroGravityMovementSolver::Enter(UAstroPlayerMovementComponent& MovementComponent)
{
	if (MovementComponent.UpdatedComponent == nullptr)
	{
		return;
	}

	UE_LOG(LogTemp, Log, TEXT("ZeroGravityMovementSolver Enter"));
	MovementComponent.SetUpdatedComponentPhysicsState(true, false);
}

void FZeroGravityMovementSolver::Exit(UAstroPlayerMovementComponent& MovementComponent)
{
	UE_LOG(LogTemp, Log, TEXT("ZeroGravityMovementSolver Exit"));
	MovementComponent.SetUpdatedComponentPhysicsState(false, false);
}

void FZeroGravityMovementSolver::Simulate(UAstroPlayerMovementComponent& MovementComponent, float DeltaTime)
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

	UPrimitiveComponent* PrimitiveComponent = Cast<UPrimitiveComponent>(MovementComponent.UpdatedComponent);
	if (PrimitiveComponent == nullptr || !PrimitiveComponent->IsSimulatingPhysics())
	{
		return;
	}

	FBodyInstance* BodyInstance = PrimitiveComponent->GetBodyInstance();
	if (BodyInstance == nullptr)
	{
		return;
	}

	FVector TranslationInput(
		AstroPawn->GetMoveForwardBackwardInput(),
		AstroPawn->GetMoveLeftRightInput(),
		AstroPawn->GetMoveUpDownInput());
	TranslationInput = TranslationInput.GetClampedToMaxSize(1.0f);

	const FTransform BodyTransform = BodyInstance->GetUnrealWorldTransform();
	const FVector Forward = BodyTransform.GetUnitAxis(EAxis::X);
	const FVector Right = BodyTransform.GetUnitAxis(EAxis::Y);
	const FVector Up = BodyTransform.GetUnitAxis(EAxis::Z);
	const FVector Force = (Forward * TranslationInput.X + Right * TranslationInput.Y + Up * TranslationInput.Z)
		* MovementComponent.GetZeroGTranslationForce();
	BodyInstance->AddForce(Force, false, true);

	FVector AngularInput(
		AstroPawn->GetRollInput(),
		AstroPawn->GetPitchInput(),
		AstroPawn->GetYawInput());
	AngularInput = AngularInput.GetClampedToMaxSize(1.0f);

	const FVector WorldTorque = BodyTransform.TransformVectorNoScale(AngularInput)
		* MovementComponent.GetZeroGRotationTorque();
	BodyInstance->AddTorqueInRadians(WorldTorque, false, true);

	const FVector CurrentLinearVelocity = BodyInstance->GetUnrealWorldVelocity();
	BodyInstance->AddForce(-CurrentLinearVelocity * MovementComponent.GetZeroGLinearDamping(), false, true);

	const FVector CurrentAngularVelocity = BodyInstance->GetUnrealWorldAngularVelocityInRadians();
	BodyInstance->AddTorqueInRadians(-CurrentAngularVelocity * MovementComponent.GetZeroGAngularDamping(), false, true);
}
