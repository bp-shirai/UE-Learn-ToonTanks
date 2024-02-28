// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"


class UInputMappingContext;
class UInputAction;
struct FInputActionValue;


/**
 * 
 */
UCLASS(Abstract)
class TOONTANKS_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:

	ATankPlayerController();

	void SetPlayerEnableState(bool bPlayerEnabled);

protected:

	virtual void BeginPlay() override;

	virtual void SetupInputComponent() override;

	UPROPERTY(EditAnywhere, Category = "Defaults")
	TObjectPtr<UInputMappingContext> DefaultMappingContext;

	UPROPERTY(EditAnywhere, Category = "Defaults")
	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(EditAnywhere, Category = "Defaults")
	TObjectPtr<UInputAction> RotateAction;

	UPROPERTY(EditAnywhere, Category = "Defaults")
	TObjectPtr<UInputAction> FireAction;

	void Move(const FInputActionValue& ActionValue);
	void Rotate(const FInputActionValue& ActionValue);
	void Fire();

	bool bInputEnable = true;
};
