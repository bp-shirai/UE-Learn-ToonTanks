// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "TankBase.generated.h"


class UCapsuleComponent;

UCLASS(Abstract)
class TOONTANKS_API ATankBase : public APawn
{
	GENERATED_BODY()

public:

	ATankBase();

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:

	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UCapsuleComponent> Capsule;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UStaticMeshComponent> BaseMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UStaticMeshComponent> TurretMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<USceneComponent> ProjectileSpawnPoint;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Defaults")
	float Speed = 400.f;
};
