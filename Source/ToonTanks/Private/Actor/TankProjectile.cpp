// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/TankProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "GameFramework/DamageType.h"
#include "Components/SphereComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Kismet/GameplayStatics.h"
#include "ToonTanks.h"

ATankProjectile::ATankProjectile()
{
	PrimaryActorTick.bCanEverTick = false;

	Sphere = CreateDefaultSubobject<USphereComponent>("Sphere");
	RootComponent = Sphere;
	Sphere->SetCanEverAffectNavigation(false);
	Sphere->SetCollisionObjectType(ECC_Projectile);
	Sphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	Sphere->SetCollisionResponseToAllChannels(ECR_Ignore);
	Sphere->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Overlap);
	Sphere->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Overlap);
	Sphere->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>("ProjectileMesh");
	ProjectileMesh->SetupAttachment(RootComponent);



	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovement");
	//ProjectileMovement->InitialSpeed = InitialSpeed;
	//ProjectileMovement->MaxSpeed = InitialSpeed;

	TrailFX = CreateDefaultSubobject<UParticleSystemComponent>("SmokeTrail");
	TrailFX->SetupAttachment(RootComponent);
}

void ATankProjectile::BeginPlay()
{
	Super::BeginPlay();
	
	//ProjectileMesh->OnComponentHit.AddDynamic(this, &ThisClass::OnHit);
	Sphere->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnSphereBeginOverlap);
	if (IsValid(GetInstigator()))
	{
		Sphere->IgnoreActorWhenMoving(GetInstigator(), true);
	}
}

void ATankProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATankProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{

}

void ATankProjectile::OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor == Owner || !IsValid(OtherActor)) return;

	if (!bHit)
	{
		bHit = true;

		auto Controller = Owner->GetInstigatorController();
		auto DamageTypeClass = UDamageType::StaticClass();
		UGameplayStatics::ApplyDamage(OtherActor, Damage, Controller, this, DamageTypeClass);

		if (HitFX) UGameplayStatics::SpawnEmitterAtLocation(this, HitFX, GetActorLocation(), GetActorRotation(), true, EPSCPoolMethod::AutoRelease);;
		if (HitSound) UGameplayStatics::PlaySoundAtLocation(this, HitSound, GetActorLocation());
		if (HitCameraShakeClass) GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(HitCameraShakeClass);

		Destroy();
	}
}

