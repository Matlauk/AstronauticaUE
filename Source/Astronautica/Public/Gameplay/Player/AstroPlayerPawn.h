// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Movement/MovementModes.h"
#include "AstroPlayerPawn.generated.h"

class UCapsuleComponent;
class UAstroPlayerMovementComponent;

UCLASS()
class ASTRONAUTICA_API AAstroPlayerPawn : public APawn
{
	GENERATED_BODY()

private:
	float MoveForwardBackwardInput = 0.0f;
	float MoveLeftRightInput = 0.0f;
	float MoveUpDownInput = 0.0f;
	float YawInput = 0.0f;
	float PitchInput = 0.0f;
	float RollInput = 0.0f;
	FVector2D LookInput = FVector2D::Zero();
	bool bSprintInput = false;
	bool bCrouchInput = false;
	bool bJumpInput = false;
	bool bMagBootsEnabled = false;
	
public:
	// Sets default values for this pawn's properties
	AAstroPlayerPawn();
	virtual UPawnMovementComponent* GetMovementComponent() const override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void HandleMovementModeChanged(EAstraMovementMode NewMode);
	void SetMoveForwardBackwardInput(float Value);
	void SetMoveLeftRightInput(float Value);
	void SetMoveUpDownInput(float Value);
	void SetYawInput(float Value);
	void SetPitchInput(float Value);
	void SetRollInput(float Value);
	void SetLookInput(FVector2D Value);
	void SetSprintInput(bool Value);
	void SetCrouchInput(bool Value);
	void SetJumpInput(bool Value);
	void Interact();
	void SetMagBoots(bool Value);
	void ToggleMagBoots();

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCapsuleComponent> CapsuleComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UAstroPlayerMovementComponent> AstroMovementComponent;
};
