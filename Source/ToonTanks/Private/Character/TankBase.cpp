// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/TankBase.h"
#include "Character/HealthComponent.h"
#include "Components/CapsuleComponent.h"
#include "Actor/TankProjectile.h"
#include "Kismet/GameplayStatics.h"
//#include "Particles/ParticleSystem.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
ATankBase::ATankBase()
{
	PrimaryActorTick.bCanEverTick = true;

	Capsule = CreateDefaultSubobject<UCapsuleComponent>("CapsuleCollider");
	RootComponent = Capsule;
	Capsule->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>("BaseMesh");
	BaseMesh->SetupAttachment(RootComponent);
	BaseMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	BaseMesh->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);

	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>("TurretMesh");
	TurretMesh->SetupAttachment(RootComponent);
	TurretMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	TurretMesh->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);

	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>("SpawnPoint");
	ProjectileSpawnPoint->SetupAttachment(TurretMesh);

	Health = CreateDefaultSubobject<UHealthComponent>("Health");

	//CharacterMovement = CreateDefaultSubobject<UCharacterMovementComponent>("CharacterMovement");
	//CharacterMovement->UpdatedComponent = RootComponent;
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
	//FVector ForwardDirection = GetActorForwardVector();
	//AddMovementInput(ForwardDirection, Value);
}

void ATankBase::Turn(float Value)
{
	float DeltaTime = UGameplayStatics::GetWorldDeltaSeconds(this);
	FRotator DeltaRotation = FRotator::ZeroRotator;

	DeltaRotation.Yaw = Value * TurnRate * DeltaTime;
	AddActorLocalRotation(DeltaRotation, true);
	//FVector RightDirection = GetActorRightVector();
	//AddMovementInput(RightDirection, Value);
}

void ATankBase::Fire()
{
	if (bCanFire)
	{
		bCanFire = false;
		FVector Location = ProjectileSpawnPoint->GetComponentLocation();
		FRotator Rotation = ProjectileSpawnPoint->GetComponentRotation();

		FActorSpawnParameters Params;
		Params.Owner = this;
		Params.Instigator = this;

		GetWorld()->SpawnActor<ATankProjectile>(ProjectileClass, Location, Rotation, Params);
		//Projectile->SetOwner(this);
		//Projectile->SetInstigator(this);

		FTimerHandle Handle;
		GetWorldTimerManager().SetTimer(Handle, [this] {bCanFire = true; }, FireRate, false);

		if (FireSound) UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
	}
}

bool ATankBase::IsAlive() const
{
	return IsValid(this) && Health->GetHealth() > 0.f;
}

void ATankBase::HandleDestruction()
{
	if (DeathFX)UGameplayStatics::SpawnEmitterAtLocation(this, DeathFX, GetActorLocation(), GetActorRotation(), true, EPSCPoolMethod::AutoRelease);
	if (DeathSound) UGameplayStatics::PlaySoundAtLocation(this, DeathSound, GetActorLocation());
	if (DeathCameraShakeClass) GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(DeathCameraShakeClass);
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

