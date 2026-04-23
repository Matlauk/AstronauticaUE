// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/Player/AstroPlayerPawn.h"

// Sets default values
AAstroPlayerPawn::AAstroPlayerPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAstroPlayerPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAstroPlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AAstroPlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

