// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "TankPawn.generated.h"

class UStaticMeshComponent;
class UCameraComponent;
class USpringArmComponent;

UCLASS()
class TANK_API ATankPawn : public APawn
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UStaticMeshComponent* BodyMesh;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UStaticMeshComponent* TurretMesh;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		class UArrowComponent* CannonSpawnPoint;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement|Speed")
		float MoveSpeed = 100.f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement|Speed")
		float RotationSpeed = 100.f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement|Speed")
		float MovementSmoothness = 0.5f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement|Speed")
		float RotationSmoothness = 0.5f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Turret")
		float TurretRotationSmoothness = 0.5f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Turret")
		TSubclassOf<class ACannon> DefaultCannonClass;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		USpringArmComponent* SpringArm;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UCameraComponent* Camera;


	float _targetForwardAxisValue;

	float _targetRightAxisValue;

public:
	// Sets default values for this pawn's properties
	ATankPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Movement")
		void MoveForward(float InAxisValue);
	UFUNCTION(BlueprintCallable, Category = "Movement")
		void RotateRight(float InAxisValue);
	UFUNCTION(BlueprintCallable, Category = "Turret")
		void SetTurretTargetPosition(const FVector& TargetPosition);
	UFUNCTION(BlueprintCallable, Category = "Turret")
		void Fire();
	UFUNCTION(BlueprintCallable, Category = "Turret")
		void FireSpecial();


	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	void SetupCannon();

	UPROPERTY()
	class ACannon* Cannon = nullptr;

	float TargetMoveForwardAxis = 0.f;
	float TargetRotateRightAxis = 0.f;
	float CurrentMoveForwardAxis = 0.f;
	float CurrentRotateRightAxis = 0.f;

	FVector TurretTargetPosition;
};
