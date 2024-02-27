// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TankGameModeBase.generated.h"



class ATank;
class ATankBase;
class ATower;
class ATankPlayerController;

/**
 * 
 */
UCLASS(Abstract)
class TOONTANKS_API ATankGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	

public:

	virtual void BeginPlay() override;

	void ActorDied(AActor* DeadActor);

	void HandleGameStart();

protected:

	TObjectPtr<ATank> Tank;
	TObjectPtr<ATankPlayerController> PlayerController;

	UPROPERTY(EditDefaultsOnly)
	float StartDelay = 3.f;
};
