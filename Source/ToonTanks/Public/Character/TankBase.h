// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "TankBase.generated.h"


class UCapsuleComponent;
class ATankProjectile;
class UHealthComponent;

UCLASS(Abstract)
class TOONTANKS_API ATankBase : public APawn
{
	GENERATED_BODY()

public:

	ATankBase();

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	virtual void BeginPlay() override;

	virtual void Move(float Value);
	virtual void Turn(float Value);
	virtual void Fire();

	bool IsAlive() const;

	virtual void HandleDestruction();

protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UCapsuleComponent> Capsule;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UStaticMeshComponent> BaseMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UStaticMeshComponent> TurretMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<USceneComponent> ProjectileSpawnPoint;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UHealthComponent> Health;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Defaults")
	float Speed = 200.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Defaults")
	float TurnRate = 45.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Defaults")
	float TurretRotateSpeed = 20.f;

	UFUNCTION(BlueprintCallable)
	void RotateTurret(FVector LookAtTarget, float DeltaTime);

	UPROPERTY(EditDefaultsOnly, Category = "Defaults")
	TSubclassOf<ATankProjectile> ProjectileClass;
	
};
