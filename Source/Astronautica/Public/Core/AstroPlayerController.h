// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Gameplay/Player/Movement/MovementModes.h"
#include "AstroPlayerController.generated.h"

class AAstroPlayerPawn;
class UInputAction;
class UInputMappingContext;
struct FInputActionValue;

/**
 * 
 */
UCLASS()
class ASTRONAUTICA_API AAstroPlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditDefaultsOnly, Category="Input")
	TObjectPtr<UInputMappingContext> IMC_Common;
	
	UPROPERTY(EditDefaultsOnly, Category="Input")
	TObjectPtr<UInputMappingContext> IMC_Grounded;
	
	UPROPERTY(EditDefaultsOnly, Category="Input")
	TObjectPtr<UInputMappingContext> IMC_ZeroGravity;
	
	UPROPERTY(EditDefaultsOnly, Category="Input")
	TObjectPtr<UInputAction> IA_MoveForwardBackward;
	
	UPROPERTY(EditDefaultsOnly, Category="Input")
	TObjectPtr<UInputAction> IA_MoveLeftRight;
	
	UPROPERTY(EditDefaultsOnly, Category="Input")
	TObjectPtr<UInputAction> IA_MoveUpDown;
	
	UPROPERTY(EditDefaultsOnly, Category="Input")
	TObjectPtr<UInputAction> IA_Yaw;
	
	UPROPERTY(EditDefaultsOnly, Category="Input")
	TObjectPtr<UInputAction> IA_Pitch;
	
	UPROPERTY(EditDefaultsOnly, Category="Input")
	TObjectPtr<UInputAction> IA_Roll;
	
	UPROPERTY(EditDefaultsOnly, Category="Input")
	TObjectPtr<UInputAction> IA_Look;
	
	UPROPERTY(EditDefaultsOnly, Category="Input")
	TObjectPtr<UInputAction> IA_Sprint;
	
	UPROPERTY(EditDefaultsOnly, Category="Input")
	TObjectPtr<UInputAction> IA_Crouch;
	
	UPROPERTY(EditDefaultsOnly, Category="Input")
	TObjectPtr<UInputAction> IA_Jump;
	
	UPROPERTY(EditDefaultsOnly, Category="Input")
	TObjectPtr<UInputAction> IA_Interact;
	
	UPROPERTY(EditDefaultsOnly, Category="Input")
	TObjectPtr<UInputAction> IA_MagBootsOn;
	
	UPROPERTY(EditDefaultsOnly, Category="Input")
	TObjectPtr<UInputAction> IA_MagBootsOff;
	
	UPROPERTY(EditDefaultsOnly, Category="Input")
	TObjectPtr<UInputAction> IA_MagBootsToggle;
	
protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	void SetMovementInputContext(const UInputMappingContext* NewContext) const;

	AAstroPlayerPawn* GetAstroPawn() const;
	
	void HandleMoveForwardBackward(const FInputActionValue& Value);
	void HandleMoveLeftRight(const FInputActionValue& Value);
	void HandleMoveUpDown(const FInputActionValue& Value);
	void HandleYaw(const FInputActionValue& Value);
	void HandlePitch(const FInputActionValue& Value);
	void HandleRoll(const FInputActionValue& Value);
	void HandleLook(const FInputActionValue& Value);
	void HandleSprintStarted();
	void HandleSprintCompleted();
	void HandleCrouchStarted();
	void HandleCrouchCompleted();
	void HandleJumpStarted();
	void HandleJumpCompleted();
	void HandleInteract();
	void HandleMagBootsOn();
	void HandleMagBootsOff();
	void HandleMagBootsToggle();
	
public:
	void HandlePawnMovementModeChanged(EAstraMovementMode NewMode);
	void SetGroundedInputMappingContext() const;
	void SetZeroGravityInputMappingContext() const;
};
