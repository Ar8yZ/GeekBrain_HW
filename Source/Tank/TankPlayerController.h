// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class TANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

	//Called to bind functionality and input
	virtual void SetupInputComponent() override;

private:
	void MoveForward(float InAxisValue);

	void MoveRight(float InAxisValue);

	UPROPERTY()
	class ATankPawn* TankPawn;
	
};