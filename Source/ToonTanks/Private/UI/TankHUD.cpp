// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/TankHUD.h"
#include "UI/TankUserWidget.h"
#include "Blueprint/WidgetBlueprintLibrary.h"

void ATankHUD::InitHUD()
{
	if (!IsValid(HUDWidgetClass)) return;

	HUDWidget = CreateWidget<UTankUserWidget>(GetWorld(), HUDWidgetClass);
	
	//HUDWidget->SetWidgetController();

	HUDWidget->AddToViewport();
}

void ATankHUD::ShowFloatingDamage(const FVector& Target, float Damage)
{
	if (!IsValid(FloatingWidgetClass)) return;

	UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), FloatingWidgetClass);
	const APlayerController* PC = GetOwningPlayerController();
	FVector2D ScreenLocation;
	PC->ProjectWorldLocationToScreen(Target, ScreenLocation);

	Widget->AddToViewport();
	Widget->SetPositionInViewport(ScreenLocation);
}
