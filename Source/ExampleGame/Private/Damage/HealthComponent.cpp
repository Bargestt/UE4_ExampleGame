// Fill out your copyright notice in the Description page of Project Settings.

#include "HealthComponent.h"


// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	MaxHealth = 100;
	CurrentHealth = MaxHealth;

	// ...
}

void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	Inititalize();
}

void UHealthComponent::Inititalize()
{
	GetOwner()->OnTakePointDamage.AddDynamic(this, &UHealthComponent::RecievePointDamage);

	GetOwner()->OnTakeRadialDamage.AddDynamic(this, &UHealthComponent::RecieveRadialDamage);
}

void UHealthComponent::RecievePointDamage(AActor* DamagedActor, float Damage, AController* InstigatedBy, FVector HitLocation, UPrimitiveComponent* FHitComponent, FName BoneName, FVector ShotFromDirection, const UDamageType* DamageType, AActor* DamageCauser)
{
	ensureMsgf(DamagedActor == GetOwner(), TEXT("Damaged Actor and Owne mismatch!"));

	ApplyDamageFinal(Damage, DamageType ? DamageType->GetClass() : nullptr, InstigatedBy, DamageCauser);
}

void UHealthComponent::RecieveRadialDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, FVector Origin, FHitResult HitInfo, AController* InstigatedBy, AActor* DamageCauser)
{
	ensureMsgf(DamagedActor == GetOwner(), TEXT("Damaged Actor and Owne mismatch!"));

	ApplyDamageFinal(Damage, DamageType ? DamageType->GetClass() : nullptr, InstigatedBy, DamageCauser);
}


void UHealthComponent::ApplyDamageFinal(float Damage, TSubclassOf<UDamageType> DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	if (IsAlive())
	{
		CurrentHealth -= Damage;
		if (!IsAlive())
		{
			OnDeath(Damage, -CurrentHealth, DamageType, InstigatedBy, DamageCauser);
		}
	}
}


void UHealthComponent::OnDeath(float LastDamage, float OverDamage, TSubclassOf<UDamageType> DamageType, AController* KilledBy, AActor* DamageCauser)
{

}

bool UHealthComponent::IsAlive() const
{
	return GetCurrentHealth() > 0;
}

float UHealthComponent::GetMaxHealth() const
{
	return MaxHealth;
}

float UHealthComponent::GetCurrentHealth() const
{
	return CurrentHealth;
}

void UHealthComponent::Restore()
{
	CurrentHealth = MaxHealth;
}

