// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/TankBase.h"
#include "Components/CapsuleComponent.h"



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
}

void ATankBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void ATankBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATankBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

