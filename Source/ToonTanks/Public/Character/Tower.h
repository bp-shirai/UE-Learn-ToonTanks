// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/TankBase.h"
#include "Tower.generated.h"


class ATank;

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATower : public ATankBase
{
	GENERATED_BODY()

public:

	ATower();

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	virtual void HandleDestruction() override;

	TWeakObjectPtr<ATank> TargetTank;

	UPROPERTY(EditAnywhere, Category = "Defaults")
	float FireRange = 300.f;

	FTimerHandle FireRateTimerHandle;





	void CheckFireCondition(float DeltaTime);

	bool InFireRange(float DeltaTime);

};
