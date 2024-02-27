// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Tower.h"
#include "Character/Tank.h"
#include "Kismet/GameplayStatics.h"



ATower::ATower()
{
}

void ATower::BeginPlay()
{
	Super::BeginPlay();

	auto Target = UGameplayStatics::GetActorOfClass(this, ATank::StaticClass());
	TargetTank = Cast<ATank>(Target);
}

void ATower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	
	CheckFireCondition(DeltaTime);
}

void ATower::HandleDestruction()
{
	Super::HandleDestruction();
	Destroy();
}

void ATower::CheckFireCondition(float DeltaTime)
{
	if (InFireRange(DeltaTime))
	{
		Fire();
	}
}

bool ATower::InFireRange(float DeltaTime)
{
	if (auto Tank = TargetTank.Get())
	{
		if (!Tank->IsAlive()) return false;
		FVector TargetLocation = Tank->GetActorLocation();

		float Distance = FVector::Dist(GetActorLocation(), TargetLocation);

		if (Distance <= FireRange)
		{
			RotateTurret(TargetLocation, DeltaTime);
			return true;
		}
	}
	return false;
}
