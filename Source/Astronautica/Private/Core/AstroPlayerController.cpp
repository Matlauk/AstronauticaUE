// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/AstroPlayerController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "Gameplay/Player/AstroPlayerPawn.h"

void AAstroPlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	if (ULocalPlayer* LocalPlayer = GetLocalPlayer())
	{
		if (UEnhancedInputLocalPlayerSubsystem* InputSubsystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
		{
			InputSubsystem->ClearAllMappings();
			
			if (IMC_Common)
			{
				InputSubsystem->AddMappingContext(IMC_Common, 0);
			}
		}
	}
}

void AAstroPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		if (IA_MoveForwardBackward)
		{
			EnhancedInputComponent->BindAction(IA_MoveForwardBackward, ETriggerEvent::Triggered, this, &AAstroPlayerController::HandleMoveForwardBackward);
			EnhancedInputComponent->BindAction(IA_MoveForwardBackward, ETriggerEvent::Completed, this, &AAstroPlayerController::HandleMoveForwardBackward);
		}

		if (IA_MoveLeftRight)
		{
			EnhancedInputComponent->BindAction(IA_MoveLeftRight, ETriggerEvent::Triggered, this, &AAstroPlayerController::HandleMoveLeftRight);
			EnhancedInputComponent->BindAction(IA_MoveLeftRight, ETriggerEvent::Completed, this, &AAstroPlayerController::HandleMoveLeftRight);
		}

		if (IA_MoveUpDown)
		{
			EnhancedInputComponent->BindAction(IA_MoveUpDown, ETriggerEvent::Triggered, this, &AAstroPlayerController::HandleMoveUpDown);
			EnhancedInputComponent->BindAction(IA_MoveUpDown, ETriggerEvent::Completed, this, &AAstroPlayerController::HandleMoveUpDown);
		}

		if (IA_Yaw)
		{
			EnhancedInputComponent->BindAction(IA_Yaw, ETriggerEvent::Triggered, this, &AAstroPlayerController::HandleYaw);
			EnhancedInputComponent->BindAction(IA_Yaw, ETriggerEvent::Completed, this, &AAstroPlayerController::HandleYaw);
		}

		if (IA_Pitch)
		{
			EnhancedInputComponent->BindAction(IA_Pitch, ETriggerEvent::Triggered, this, &AAstroPlayerController::HandlePitch);
			EnhancedInputComponent->BindAction(IA_Pitch, ETriggerEvent::Completed, this, &AAstroPlayerController::HandlePitch);
		}

		if (IA_Roll)
		{
			EnhancedInputComponent->BindAction(IA_Roll, ETriggerEvent::Triggered, this, &AAstroPlayerController::HandleRoll);
			EnhancedInputComponent->BindAction(IA_Roll, ETriggerEvent::Completed, this, &AAstroPlayerController::HandleRoll);
		}

		if (IA_Look)
		{
			EnhancedInputComponent->BindAction(IA_Look, ETriggerEvent::Triggered, this, &AAstroPlayerController::HandleLook);
		}

		if (IA_Sprint)
		{
			EnhancedInputComponent->BindAction(IA_Sprint, ETriggerEvent::Started, this, &AAstroPlayerController::HandleSprintStarted);
			EnhancedInputComponent->BindAction(IA_Sprint, ETriggerEvent::Completed, this, &AAstroPlayerController::HandleSprintCompleted);
		}

		if (IA_Crouch)
		{
			EnhancedInputComponent->BindAction(IA_Crouch, ETriggerEvent::Started, this, &AAstroPlayerController::HandleCrouchStarted);
			EnhancedInputComponent->BindAction(IA_Crouch, ETriggerEvent::Completed, this, &AAstroPlayerController::HandleCrouchCompleted);
		}

		if (IA_Jump)
		{
			EnhancedInputComponent->BindAction(IA_Jump, ETriggerEvent::Started, this, &AAstroPlayerController::HandleJumpStarted);
			EnhancedInputComponent->BindAction(IA_Jump, ETriggerEvent::Completed, this, &AAstroPlayerController::HandleJumpCompleted);
		}

		if (IA_Interact)
		{
			EnhancedInputComponent->BindAction(IA_Interact, ETriggerEvent::Started, this, &AAstroPlayerController::HandleInteract);
		}

		if (IA_MagBootsOn)
		{
			EnhancedInputComponent->BindAction(IA_MagBootsOn, ETriggerEvent::Started, this, &AAstroPlayerController::HandleMagBootsOn);
		}

		if (IA_MagBootsOff)
		{
			EnhancedInputComponent->BindAction(IA_MagBootsOff, ETriggerEvent::Started, this, &AAstroPlayerController::HandleMagBootsOff);
		}

		if (IA_MagBootsToggle)
		{
			EnhancedInputComponent->BindAction(IA_MagBootsToggle, ETriggerEvent::Started, this, &AAstroPlayerController::HandleMagBootsToggle);
		}
	}
}

void AAstroPlayerController::SetMovementInputContext(const UInputMappingContext* NewContext) const
{
	if (NewContext == nullptr)
	{
		return;
	}

	if (ULocalPlayer* LocalPlayer = GetLocalPlayer())
	{
		if (UEnhancedInputLocalPlayerSubsystem* InputSubsystem =
			LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
		{
			if (IMC_Grounded)
			{
				InputSubsystem->RemoveMappingContext(IMC_Grounded);
			}

			if (IMC_ZeroGravity)
			{
				InputSubsystem->RemoveMappingContext(IMC_ZeroGravity);
			}

			InputSubsystem->AddMappingContext(NewContext, 1);
		}
	}
}

AAstroPlayerPawn* AAstroPlayerController::GetAstroPawn() const
{
	return Cast<AAstroPlayerPawn>(GetPawn());
}

void AAstroPlayerController::SetGroundedInputMappingContext() const
{
	SetMovementInputContext(IMC_Grounded);
}

void AAstroPlayerController::SetZeroGravityInputMappingContext() const
{
	SetMovementInputContext(IMC_ZeroGravity);
}

void AAstroPlayerController::HandleMoveForwardBackward(const FInputActionValue& Value)
{
	if (AAstroPlayerPawn* AstroPawn = GetAstroPawn())
	{
		AstroPawn->SetMoveForwardBackwardInput(Value.Get<float>());
	}
}

void AAstroPlayerController::HandleMoveLeftRight(const FInputActionValue& Value)
{
	if (AAstroPlayerPawn* AstroPawn = GetAstroPawn())
	{
		AstroPawn->SetMoveLeftRightInput(Value.Get<float>());
	}
}

void AAstroPlayerController::HandleMoveUpDown(const FInputActionValue& Value)
{
	if (AAstroPlayerPawn* AstroPawn = GetAstroPawn())
	{
		AstroPawn->SetMoveUpDownInput(Value.Get<float>());
	}
}

void AAstroPlayerController::HandleYaw(const FInputActionValue& Value)
{
	if (AAstroPlayerPawn* AstroPawn = GetAstroPawn())
	{
		AstroPawn->SetYawInput(Value.Get<float>());
	}
}

void AAstroPlayerController::HandlePitch(const FInputActionValue& Value)
{
	if (AAstroPlayerPawn* AstroPawn = GetAstroPawn())
	{
		AstroPawn->SetPitchInput(Value.Get<float>());
	}
}

void AAstroPlayerController::HandleRoll(const FInputActionValue& Value)
{
	if (AAstroPlayerPawn* AstroPawn = GetAstroPawn())
	{
		AstroPawn->SetRollInput(Value.Get<float>());
	}
}

void AAstroPlayerController::HandleLook(const FInputActionValue& Value)
{
	if (AAstroPlayerPawn* AstroPawn = GetAstroPawn())
	{
		AstroPawn->SetLookInput(Value.Get<FVector2D>());
	}
}

void AAstroPlayerController::HandleSprintStarted()
{
	if (AAstroPlayerPawn* AstroPawn = GetAstroPawn())
	{
		AstroPawn->SetSprintInput(true);
	}
}

void AAstroPlayerController::HandleSprintCompleted()
{
	if (AAstroPlayerPawn* AstroPawn = GetAstroPawn())
	{
		AstroPawn->SetSprintInput(false);
	}
}

void AAstroPlayerController::HandleCrouchStarted()
{
	if (AAstroPlayerPawn* AstroPawn = GetAstroPawn())
	{
		AstroPawn->SetCrouchInput(true);
	}
}

void AAstroPlayerController::HandleCrouchCompleted()
{
	if (AAstroPlayerPawn* AstroPawn = GetAstroPawn())
	{
		AstroPawn->SetCrouchInput(false);
	}
}

void AAstroPlayerController::HandleJumpStarted()
{
	if (AAstroPlayerPawn* AstroPawn = GetAstroPawn())
	{
		AstroPawn->SetJumpInput(true);
	}
}

void AAstroPlayerController::HandleJumpCompleted()
{
	if (AAstroPlayerPawn* AstroPawn = GetAstroPawn())
	{
		AstroPawn->SetJumpInput(false);
	}
}

void AAstroPlayerController::HandleInteract()
{
	if (AAstroPlayerPawn* AstroPawn = GetAstroPawn())
	{
		AstroPawn->Interact();
	}
}

void AAstroPlayerController::HandleMagBootsOn()
{
	if (AAstroPlayerPawn* AstroPawn = GetAstroPawn())
	{
		AstroPawn->SetMagBoots(true);
	}
}

void AAstroPlayerController::HandleMagBootsOff()
{
	if (AAstroPlayerPawn* AstroPawn = GetAstroPawn())
	{
		AstroPawn->SetMagBoots(false);
	}
}

void AAstroPlayerController::HandleMagBootsToggle()
{
	if (AAstroPlayerPawn* AstroPawn = GetAstroPawn())
	{
		AstroPawn->ToggleMagBoots();
	}
}

void AAstroPlayerController::HandlePawnMovementModeChanged(EAstraMovementMode NewMode)
{	switch (NewMode)
	{
	case EAstraMovementMode::Grounded:
		SetGroundedInputMappingContext();
		break;
	case EAstraMovementMode::ZeroG:
		SetZeroGravityInputMappingContext();
		break;
	default:
		break;
	}
}
