// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Tank.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"



ATank::ATank()
{
	SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	SpringArm->SetupAttachment(GetRootComponent());

	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	Camera->SetupAttachment(SpringArm);
}
