// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Movement/GroundedMovementSolver.h"
#include "Movement/MagBootMovementSolver.h"
#include "Movement/MovementModes.h"
#include "Movement/ZeroGravityMovementSolver.h"
#include "AstroPlayerMovementComponent.generated.h"

/**
 * 
 */
UCLASS()
class ASTRONAUTICA_API UAstroPlayerMovementComponent : public UPawnMovementComponent
{
	GENERATED_BODY()

public:
	UAstroPlayerMovementComponent();

	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	float GetGroundedMoveSpeed() const { return GroundedMoveSpeed; }
	float GetZeroGTranslationForce() const { return ZeroGTranslationForce; }
	float GetZeroGRotationTorque() const { return ZeroGRotationTorque; }
	float GetZeroGLinearDamping() const { return ZeroGLinearDamping; }
	float GetZeroGAngularDamping() const { return ZeroGAngularDamping; }
	void SetUpdatedComponentPhysicsState(bool bSimulatePhysics, bool bEnableGravity);

private:
	FGroundedMovementSolver GroundedMovementSolver;
	FMagBootMovementSolver MagBootMovementSolver;
	FZeroGravityMovementSolver ZeroGravityMovementSolver;
	
	FMovementSolverBase* CurrentMovementSolver = nullptr;
	
	UPROPERTY(VisibleAnywhere)
	EAstraMovementMode MovementMode = EAstraMovementMode::ZeroG;

	UPROPERTY(EditAnywhere, Category = "Movement|Grounded", meta = (ClampMin = "0.0"))
	float GroundedMoveSpeed = 600.0f;

	UPROPERTY(EditAnywhere, Category = "Movement|ZeroG", meta = (ClampMin = "0.0"))
	float ZeroGTranslationForce = 256.0f;

	UPROPERTY(EditAnywhere, Category = "Movement|ZeroG", meta = (ClampMin = "0.0"))
	float ZeroGRotationTorque = 1.0f;

	UPROPERTY(EditAnywhere, Category = "Movement|ZeroG", meta = (ClampMin = "0.0"))
	float ZeroGLinearDamping = 0.f;

	UPROPERTY(EditAnywhere, Category = "Movement|ZeroG", meta = (ClampMin = "0.0"))
	float ZeroGAngularDamping = 0.f;

	void SetMovementMode(EAstraMovementMode NewMode);
	FMovementSolverBase& GetMovementSolver(EAstraMovementMode InMovementMode);
};
