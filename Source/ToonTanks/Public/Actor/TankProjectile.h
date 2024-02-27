// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TankProjectile.generated.h"


class UProjectileMovementComponent;

UCLASS(Abstract)
class TOONTANKS_API ATankProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	ATankProjectile();

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

protected:
	
	UPROPERTY(EditDefaultsOnly, Category = "Components")
	TObjectPtr<UStaticMeshComponent> ProjectileMesh;
	
	UPROPERTY(EditDefaultsOnly, Category = "Components")
	TObjectPtr<UProjectileMovementComponent> ProjectileMovement;

	UPROPERTY(EditAnywhere, Category = "Defaults")
	float Damage = 50.f;

	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
};
