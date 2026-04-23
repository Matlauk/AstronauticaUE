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

private:
	FGroundedMovementSolver GroundedMovementSolver;
	FMagBootMovementSolver MagBootMovementSolver;
	FZeroGravityMovementSolver ZeroGravityMovementSolver;
	
	FMovementSolverBase* CurrentMovementSolver = nullptr;
	
	UPROPERTY(VisibleAnywhere)
	EAstraMovementMode MovementMode = EAstraMovementMode::Grounded;

	UPROPERTY(EditAnywhere, Category = "Movement|Grounded", meta = (ClampMin = "0.0"))
	float GroundedMoveSpeed = 600.0f;
	
	void SetMovementMode(EAstraMovementMode NewMode);
	FMovementSolverBase& GetMovementSolver(EAstraMovementMode InMovementMode);
};
