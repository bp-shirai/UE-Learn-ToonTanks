// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/TankBase.h"
#include "Tank.generated.h"


class USpringArmComponent;
class UCameraComponent;

/**
 * 
 */
UCLASS(Abstract)
class TOONTANKS_API ATank : public ATankBase
{
	GENERATED_BODY()
	
public:

	ATank();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void HandleDestruction() override;

	APlayerController* GetPlayerController() const { return Cast<APlayerController>(Controller); }

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<USpringArmComponent> SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UCameraComponent> Camera;

};
