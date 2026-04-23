// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/Player/AstroPlayerPawn.h"

#include "Core/AstroPlayerController.h"
#include "Components/CapsuleComponent.h"
#include "Gameplay/Player/AstroPlayerMovementComponent.h"

// Sets default values
AAstroPlayerPawn::AAstroPlayerPawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
	SetRootComponent(CapsuleComponent);
	CapsuleComponent->InitCapsuleSize(42.0f, 96.0f);
	CapsuleComponent->SetCollisionProfileName(TEXT("Pawn"));

	AstroMovementComponent = CreateDefaultSubobject<UAstroPlayerMovementComponent>(TEXT("MovementComponent"));
	AstroMovementComponent->SetUpdatedComponent(CapsuleComponent);

}

UPawnMovementComponent* AAstroPlayerPawn::GetMovementComponent() const
{
	return AstroMovementComponent;
}

// Called when the game starts or when spawned
void AAstroPlayerPawn::BeginPlay()
{
	Super::BeginPlay();

	if (AstroMovementComponent && CapsuleComponent)
	{
		AstroMovementComponent->SetUpdatedComponent(CapsuleComponent);
	}
	
}

// Called every frame
void AAstroPlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AAstroPlayerPawn::HandleMovementModeChanged(EAstraMovementMode NewMode)
{
	if (AAstroPlayerController* PC = Cast<AAstroPlayerController>(GetController()))
	{
		PC->HandlePawnMovementModeChanged(NewMode);
	}
}

// Called to bind functionality to input
void AAstroPlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AAstroPlayerPawn::SetMoveForwardBackwardInput(float Value)
{
	MoveForwardBackwardInput = Value;
}

void AAstroPlayerPawn::SetMoveLeftRightInput(float Value)
{
	MoveLeftRightInput = Value;
}

void AAstroPlayerPawn::SetMoveUpDownInput(float Value)
{
	MoveUpDownInput = Value;
}

void AAstroPlayerPawn::SetYawInput(float Value)
{
	YawInput = Value;
}

void AAstroPlayerPawn::SetPitchInput(float Value)
{
	PitchInput = Value;
}

void AAstroPlayerPawn::SetRollInput(float Value)
{
	RollInput = Value;
}

void AAstroPlayerPawn::SetLookInput(FVector2D Value)
{
	LookInput = Value;
}

void AAstroPlayerPawn::SetSprintInput(bool Value)
{
	bSprintInput = Value;
}

void AAstroPlayerPawn::SetCrouchInput(bool Value)
{
	bCrouchInput = Value;
}

void AAstroPlayerPawn::SetJumpInput(bool Value)
{
	bJumpInput = Value;
}

void AAstroPlayerPawn::Interact()
{
	
}

void AAstroPlayerPawn::SetMagBoots(bool Value)
{
	bMagBootsEnabled = Value;
}

void AAstroPlayerPawn::ToggleMagBoots()
{
	bMagBootsEnabled = !bMagBootsEnabled;
}

