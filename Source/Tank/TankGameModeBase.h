// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GameStructs.h"
#include "TankGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class TANK_API ATankGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:

	void NotifyActorWasDestroyedByDamage(AACtor* Actor, const FDamageData& DamageData);
	
};
