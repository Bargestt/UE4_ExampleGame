// Fill out your copyright notice in the Description page of Project Settings.

#include "PointDamageComponent.h"
#include "Kismet/GameplayStatics.h"






UPointDamageComponent::UPointDamageComponent()
{
	bDamageAppled = false;
}

bool UPointDamageComponent::CanActivate() const
{
	return !bDamageAppled;
}

void UPointDamageComponent::Reset()
{
	bDamageAppled = false;
}

void UPointDamageComponent::InvokePointDamage(AActor* Target, const FVector& Direction, const FHitResult& Hit)
{
	if (CanActivate() && CanDamageActor(Target))
	{
		UGameplayStatics::ApplyPointDamage(Target, BaseDamage, Direction, Hit, GetDamageInstigator(), GetDamageCauser(), DamageType);		
		bDamageAppled = true;
		OnDamageApply.Broadcast(this, Target);
	}
}

void UPointDamageComponent::BindToCollisionSource(UPrimitiveComponent* Source)
{
	Source->OnComponentHit.AddDynamic(this, &UPointDamageComponent::Hit);
}

void UPointDamageComponent::Hit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	InvokePointDamage(OtherActor, NormalImpulse, Hit);
}
