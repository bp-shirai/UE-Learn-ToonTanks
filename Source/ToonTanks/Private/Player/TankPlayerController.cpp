// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/TankPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"

#include "Character/TankBase.h"
#include "Blueprint/WidgetBlueprintLibrary.h"

ATankPlayerController::ATankPlayerController()
{
	bReplicates = true;

	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;
}

void ATankPlayerController::SetPlayerEnableState(bool bPlayerEnabled)
{
	
	bInputEnable = bPlayerEnabled;
	bShowMouseCursor = bPlayerEnabled;
}

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	auto Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	check(Subsystem);
	Subsystem->AddMappingContext(DefaultMappingContext, 0);

	
	FInputModeGameAndUI InputMode;
	InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputMode.SetHideCursorDuringCapture(false);
	SetInputMode(InputMode);
	

	//SetPlayerEnableState(false);
}

void ATankPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	auto EIC = CastChecked<UEnhancedInputComponent>(InputComponent);
	EIC->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ThisClass::Move);
	EIC->BindAction(RotateAction, ETriggerEvent::Triggered, this, &ThisClass::Rotate);
	EIC->BindAction(FireAction, ETriggerEvent::Started , this, &ThisClass::Fire);


}

void ATankPlayerController::Move(const FInputActionValue& ActionValue)
{
	if (!bInputEnable) return;
	const FVector2D InputAxisVector = ActionValue.Get<FVector2D>();
	/*
	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	if (APawn* ControlledPawn = GetPawn())
	{
		ControlledPawn->AddMovementInput(ForwardDirection, InputAxisVector.Y);
		ControlledPawn->AddMovementInput(RightDirection, InputAxisVector.X);
	}*/
	if (auto Tank = GetPawn<ATankBase>())
	{
		if (Tank->IsAlive())
		{
			Tank->Move(InputAxisVector.Y);
			Tank->Turn(InputAxisVector.X);
		}
	}
}

void ATankPlayerController::Rotate(const FInputActionValue& ActionValue)
{
}

void ATankPlayerController::Fire()
{
	if (!bInputEnable) return;
	if (auto Tank = GetPawn<ATankBase>())
	{
		if (Tank->IsAlive())
		{
			Tank->Fire();
		}
	}
}
