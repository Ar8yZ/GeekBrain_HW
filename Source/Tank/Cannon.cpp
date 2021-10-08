// Fill out your copyright notice in the Description page of Project Settings.


#include "Cannon.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/ArrowComponent.h"
#include "TimerManager.h"
#include "Engine/Engine.h"
#include "Tank.h"

// Sets default values
ACannon::ACannon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	USceneComponent* SceeneCpm = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = SceeneCpm;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cannon mesh"));
	Mesh->SetupAttachment(RootComponent);

	ProjectileSpawnPoint = CreateDefaultSubobject<UArrowComponent>(TEXT("Spawn point"));
	ProjectileSpawnPoint->SetupAttachment(Mesh);
}

void ACannon::Fire()
{
	if (!IsReadyToFire())
	{
		return;
	}
	bIsReadyToFire = false;
	--NumAmmo;
	ShotsLeft = NumShotsInSeries;
	Shot();
}

void ACannon::FireSpecial()
{
	if (!HasSpecialFire() || !IsReadyToFire())
	{
		return;
	}
	bIsReadyToFire = false;
	--NumAmmo;
	if (Type == ECannonType::FireProjectile)
	{
		GEngine->AddOnScreenDebugMessage(10, 1, FColor::Green, TEXT("Fire special - projectile"));
	}
	else if (Type == ECannonType::FireTrace)
	{
		GEngine->AddOnScreenDebugMessage(10, 1, FColor::Green, TEXT("Fire special - trace"));
	}

	GetWorld()->GetTimerManager().SetTimer(ReloadTimerHandle, this, &ACannon::Reload, 1.f / FireRate, false);
}

bool ACannon::IsReadyToFire()
{
	return bIsReadyToFire && NumAmmo > 0 && ShotsLeft == 0;
}

bool ACannon::HasSpecialFire() const
{
	return bHasSpecialFire;
}

// Called when the game starts or when spawned
void ACannon::BeginPlay()
{
	Super::BeginPlay();

	bIsReadyToFire = true;
	NumAmmo = MaxAmmo;
	ShotsLeft = 0;
	
}

void ACannon::EndPlay(EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	GetWorld()->GetTimerManager().ClearTimer(ReloadTimerHandle);
	GetWorld()->GetTimerManager().ClearTimer(SeriesTimerHandle);
}

void ACannon::Reload()
{
	bIsReadyToFire = true;
}

void ACannon::Shot()
{
	check(ShotsLeft > 0);
	if (Type == ECannonType::FireProjectile)
	{
		GEngine->AddOnScreenDebugMessage(INDEX_NONE, 1, FColor::Green, TEXT("Fire - projectile"));
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(INDEX_NONE, 1, FColor::Green, TEXT("Fire - trace"));
	}

	if (--ShotsLeft > 0)
	{
		const float NextShotTime = SeriesLength / (NumShotsInSeries - 1);
		GetWorld()->GetTimerManager().SetTimer(SeriesTimerHandle, this, &ACannon::Shot, NextShotTime, false);
	}
	else
	{
		GetWorld()->GetTimerManager().SetTimer(ReloadTimerHandle, this, &ACannon::Reload, 1.f / FireRate, false);
	}
}
