// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/TankPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"

ATankPlayerController::ATankPlayerController()
{
	bReplicates = true;
}

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	auto Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	check(Subsystem);
	Subsystem->AddMappingContext(DefaultMappingContext, 0);

	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;

	FInputModeGameAndUI InputMode;
	InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputMode.SetHideCursorDuringCapture(false);
	SetInputMode(InputMode);
}

void ATankPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	auto EIC = CastChecked<UEnhancedInputComponent>(InputComponent);
	EIC->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ThisClass::Move);
	EIC->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ThisClass::Rotate);
	EIC->BindAction(MoveAction, ETriggerEvent::Started , this, &ThisClass::Fire);


}

void ATankPlayerController::Move(const FInputActionValue& ActionValue)
{
	const FVector2D InputAxisVector = ActionValue.Get<FVector2D>();
	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	if (APawn* ControlledPawn = GetPawn())
	{
		ControlledPawn->AddMovementInput(ForwardDirection, InputAxisVector.Y);
		ControlledPawn->AddMovementInput(RightDirection, InputAxisVector.X);
	}
}

void ATankPlayerController::Rotate(const FInputActionValue& ActionValue)
{
}

void ATankPlayerController::Fire()
{
}
