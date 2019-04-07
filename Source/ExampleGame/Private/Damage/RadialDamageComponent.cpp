// Fill out your copyright notice in the Description page of Project Settings.

#include "RadialDamageComponent.h"
#include "Kismet/GameplayStatics.h"




URadialDamageComponent::URadialDamageComponent()
{
	DamagePreventionChannel = TEnumAsByte<ECollisionChannel>(ECC_Visibility);
}

void URadialDamageComponent::Explode()
{
	check(GetCollisionSource());

	InvokeRadialDamage(GetCollisionSource()->GetComponentLocation());
}

void URadialDamageComponent::InvokeRadialDamage(const FVector& Origin) const
{
	if (CanActivate()) 
	{
		UGameplayStatics::ApplyRadialDamage(GetWorld(), BaseDamage, Origin, Radius, DamageType, GetIgnoreActors(), GetDamageCauser(), GetDamageInstigator(), true, DamagePreventionChannel);
	}
}






