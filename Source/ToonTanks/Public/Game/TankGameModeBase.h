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

	virtual void PostLogin(APlayerController* NewPlayer) override;

	UFUNCTION(BlueprintImplementableEvent)
	void StartGame();

	UFUNCTION(BlueprintImplementableEvent)
	void GameOver(bool bWonGame);

protected:


	TObjectPtr<ATank> Tank;

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<ATankPlayerController> PlayerController;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float StartDelay = 3.f;

	int32 TargetTowers = 0;

	int32 GetTargetTowerCount() const;
};
