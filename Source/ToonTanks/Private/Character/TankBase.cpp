// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/TankBase.h"
#include "Character/HealthComponent.h"
#include "Components/CapsuleComponent.h"
#include "Actor/TankProjectile.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
ATankBase::ATankBase()
{
	PrimaryActorTick.bCanEverTick = true;

	Capsule = CreateDefaultSubobject<UCapsuleComponent>("CapsuleCollider");
	SetRootComponent(Capsule);
	Capsule->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>("BaseMesh");
	BaseMesh->SetupAttachment(Capsule);
	BaseMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	BaseMesh->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);

	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>("TurretMesh");
	TurretMesh->SetupAttachment(Capsule);
	TurretMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	TurretMesh->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);

	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>("SpawnPoint");
	ProjectileSpawnPoint->SetupAttachment(TurretMesh);

	Health = CreateDefaultSubobject<UHealthComponent>("Health");
}

void ATankBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void ATankBase::Move(float Value)
{
	float DeltaTime = UGameplayStatics::GetWorldDeltaSeconds(this);
	FVector DeltaLocation = FVector::ZeroVector;

	DeltaLocation.X = Value * Speed * DeltaTime;
	AddActorLocalOffset(DeltaLocation, true);
}

void ATankBase::Turn(float Value)
{
	float DeltaTime = UGameplayStatics::GetWorldDeltaSeconds(this);
	FRotator DeltaRotation = FRotator::ZeroRotator;

	DeltaRotation.Yaw = Value * TurnRate * DeltaTime;
	AddActorLocalRotation(DeltaRotation, true);
}

void ATankBase::Fire()
{
	FVector Location = ProjectileSpawnPoint->GetComponentLocation();
	FRotator Rotation = ProjectileSpawnPoint->GetComponentRotation();

	FTransform Transform;
	auto Projectile = GetWorld()->SpawnActorDeferred<ATankProjectile>(ProjectileClass, Transform, this, this, ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
	Projectile->FinishSpawning(Transform);
}

bool ATankBase::IsAlive() const
{
	return IsValid(this) && Health->GetHealth() > 0.f;
}

void ATankBase::HandleDestruction()
{
}

void ATankBase::RotateTurret(FVector LookAtTarget, float DeltaTime)
{
	FVector ToTarget = LookAtTarget - TurretMesh->GetComponentLocation();
	FRotator LookAtRotation = ToTarget.Rotation();
	LookAtRotation.Pitch = 0.f;
	LookAtRotation.Roll = 0.f;

	FRotator CurrentRotation = TurretMesh->GetComponentRotation();
	FRotator NewRotation = FMath::RInterpTo(CurrentRotation, LookAtRotation, DeltaTime, TurretRotateSpeed);
	TurretMesh->SetWorldRotation(NewRotation);
}

void ATankBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);



}

void ATankBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

