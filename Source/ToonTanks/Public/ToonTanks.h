// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

DECLARE_LOG_CATEGORY_EXTERN(LogTank, Log, All)

constexpr int32 CUSTOM_DEPTH_RED = 250;

constexpr ECollisionChannel ECC_Projectile = ECollisionChannel::ECC_GameTraceChannel1;
constexpr ECollisionChannel ECC_AreaEffect = ECollisionChannel::ECC_GameTraceChannel2;
constexpr ECollisionChannel ECC_PickupItem = ECollisionChannel::ECC_GameTraceChannel3;

#define TEXT_BOOL(b) b ? TEXT("True") : TEXT("False")