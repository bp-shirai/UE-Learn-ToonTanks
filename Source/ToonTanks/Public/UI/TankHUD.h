// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "TankHUD.generated.h"

class UTankUserWidget;

/**
 * 
 */
UCLASS(Abstract)
class TOONTANKS_API ATankHUD : public AHUD
{
	GENERATED_BODY()
	
public:

	void InitHUD();

	void ShowFloatingDamage(const FVector& Target, float Damage);

protected:

	UPROPERTY()
	TObjectPtr<UTankUserWidget> HUDWidget;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UTankUserWidget> HUDWidgetClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> FloatingWidgetClass;
};
