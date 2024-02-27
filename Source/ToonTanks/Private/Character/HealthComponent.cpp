// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/HealthComponent.h"
#include "Game/TankGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

UHealthComponent::UHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = true;


}


void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	Health = MaxHealth;

	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &ThisClass::DamageTaken);
}


void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UHealthComponent::DamageTaken(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* Instigator, AActor* DamageCauser)
{
	if (Damage <= 0.f) return;

	Health -= Damage;

	if (Health <= 0.f)
	{
		if (auto GM = Cast<ATankGameModeBase>(UGameplayStatics::GetGameMode(this)))
		{
			GM->ActorDied(DamagedActor);
		}
	}
}

