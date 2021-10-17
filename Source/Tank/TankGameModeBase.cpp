// Copyright Epic Games, Inc. All Rights Reserved.


#include "TankGameModeBase.h"
#include "Scoreable.h"
#include "TankPlayerController.h"
#include "Tank.h"

void ATankGameModeBase::NotifyActorWasDestroyedByDamage(AACtor* Actor, const FDamageData& DamageData)
{
	if (IScoreable* Scoreable = Cast<IScoreable>(Actor))
	{
		ATankPlayerController* PlayerController = Cast<ATankPlayerController>(GetWorld()->GetFirstPlayerController());
		if (DamageData.Instigator == PlayerController->GetPawn())
		{
			PlayerController->Scores += Scoreable->GetScores();
		}
	}
}