// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/TankProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "GameFramework/DamageType.h"
#include "Kismet/GameplayStatics.h"

ATankProjectile::ATankProjectile()
{
	PrimaryActorTick.bCanEverTick = false;

	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>("ProjectileMesh");
	SetRootComponent(ProjectileMesh);

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovement");
	//ProjectileMovement->InitialSpeed = InitialSpeed;
	//ProjectileMovement->MaxSpeed = InitialSpeed;
}

void ATankProjectile::BeginPlay()
{
	Super::BeginPlay();
	
	ProjectileMesh->OnComponentHit.AddDynamic(this, &ThisClass::OnHit);
}

void ATankProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATankProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	//auto MyOwner = GetOwner();
	if (!IsValid(Owner)) return;

	auto Controller = Owner->GetInstigatorController();
	auto DamageTypeClass = UDamageType::StaticClass();

	if (OtherActor && OtherActor != this && OtherActor != Owner)
	{
		UGameplayStatics::ApplyDamage(OtherActor, Damage, Controller, this, DamageTypeClass);

		Destroy();
	}
}

