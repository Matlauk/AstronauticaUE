// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/AstroGameMode.h"

#include "Core/AstroGameState.h"
#include "Core/AstroPlayerController.h"
#include "Core/AstroPlayerState.h"
#include "Gameplay/Player/AstroPlayerPawn.h"

AAstroGameMode::AAstroGameMode()
{
	DefaultPawnClass = AAstroPlayerPawn::StaticClass();
	PlayerControllerClass = AAstroPlayerController::StaticClass();
	GameStateClass = AAstroGameState::StaticClass();
	PlayerStateClass = AAstroPlayerState::StaticClass();
}
