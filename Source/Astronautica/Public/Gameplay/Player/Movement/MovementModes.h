#pragma once

#include "MovementModes.generated.h"

UENUM(BlueprintType)
enum class EAstraMovementMode : uint8
{
	Grounded UMETA(DisplayName="Grounded"),
	ZeroG UMETA(DisplayName="Zero Gravity"),
	MagBoots UMETA(DisplayName="Mag Boots")
};