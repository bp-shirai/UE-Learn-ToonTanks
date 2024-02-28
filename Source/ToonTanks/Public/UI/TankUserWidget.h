// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TankUserWidget.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class TOONTANKS_API UTankUserWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

	

protected:

	UPROPERTY()
	TObjectPtr<AActor> WidgetController;
};
