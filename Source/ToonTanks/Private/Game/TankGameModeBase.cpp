// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/TankGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Character/Tank.h"
#include "Character/Tower.h"
#include "Player/TankPlayerController.h"
#include "ToonTanks.h"

void ATankGameModeBase::ActorDied(AActor* DeadActor)
{
	if (Tank == nullptr)
		Tank = Cast<ATank>(PlayerController->GetPawn());

	if (DeadActor == Tank)
	{
		Tank->HandleDestruction();
		if (PlayerController) PlayerController->SetPlayerEnableState(false);
		
		GameOver(false);
	}
	else if (auto DestroyedTower = Cast<ATower>(DeadActor))
	{
		DestroyedTower->HandleDestruction();
		if (--TargetTowers == 0)
		{
			GameOver(true);
		}
	}
}

void ATankGameModeBase::HandleGameStart()
{
	TargetTowers = GetTargetTowerCount();

	StartGame();

	FTimerHandle TimerHandle;
	GetWorldTimerManager().SetTimer(TimerHandle, [this]() { if(PlayerController) PlayerController->SetPlayerEnableState(true); }, StartDelay, false);
}

void ATankGameModeBase::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);
	UE_LOG(LogTank, Log, TEXT("[%s] %s : NewPlayer = %s"), *GetNameSafe(this), TEXT(__FUNCTION__), *GetNameSafe(NewPlayer));

	PlayerController = Cast<ATankPlayerController>(NewPlayer);
	if (PlayerController)
	{
		PlayerController->SetPlayerEnableState(false);
	}
}

int32 ATankGameModeBase::GetTargetTowerCount() const
{
	TArray<AActor*> Towers;
	UGameplayStatics::GetAllActorsOfClass(this, ATower::StaticClass(), Towers);
	return Towers.Num();
}

void ATankGameModeBase::BeginPlay()
{
	Super::BeginPlay();


	HandleGameStart();
	//HandleGameStart();
	//GetWorldTimerManager().SetTimerForNextTick([this]{ HandleGameStart(); });
	
}
