// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/TankGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Character/Tank.h"
#include "Character/Tower.h"
#include "Player/TankPlayerController.h"

void ATankGameModeBase::ActorDied(AActor* DeadActor)
{


	if (DeadActor == Tank)
	{
		Tank->HandleDestruction();
		
		if (PlayerController)
		{
			PlayerController->SetPlayerEnableState(false);
		}
	}
	else if (auto DestroyedTower = Cast<ATower>(DeadActor))
	{
		DestroyedTower->HandleDestruction();
	}
}

void ATankGameModeBase::HandleGameStart()
{
	if (Tank == nullptr)
	{
		Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
		PlayerController = Cast<ATankPlayerController>(UGameplayStatics::GetPlayerController(this, 0));
	}

	if (PlayerController)
	{
		PlayerController->SetPlayerEnableState(false);
	}

	FTimerHandle TimerHandle;
	GetWorldTimerManager().SetTimer(TimerHandle, [this] {PlayerController->SetPlayerEnableState(true); }, StartDelay, false);
}

void ATankGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	GetWorldTimerManager().SetTimerForNextTick([this]{ HandleGameStart(); });
	
}
