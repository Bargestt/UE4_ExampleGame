// Fill out your copyright notice in the Description page of Project Settings.

#include "HitscanWeapon.h"
#include "Particles/ParticleSystemComponent.h"
#include "Kismet/GameplayStatics.h"




AHitscanWeapon::AHitscanWeapon()
{
	ShotEffectComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ShotEffect"));
	ShotEffectComponent->SetupAttachment(RootComponent, AGunWeapon::Socket_Muzzle);
	ShotEffectComponent->bAutoActivate = false;

}

void AHitscanWeapon::Use()
{
	FTransform Transform = GetShotTransform();

	FVector From = Transform.GetLocation();
	FVector To = From + Transform.GetUnitAxis(EAxis::X) * 1500;

	FCollisionQueryParams params;
	params.AddIgnoredActor(GetOwner());
	params.AddIgnoredActor(this);

	FHitResult Hit;
	GetWorld()->LineTraceSingleByChannel(Hit, From, To, ECC_Visibility, params);


	SetupShotEffect(ShotEffectComponent, Hit);
	ShotEffectComponent->Activate(true);

	if (Hit.bBlockingHit)
	{
		To = Hit.ImpactPoint;

		UParticleSystemComponent* HitEmitter = UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitEffect, FTransform(FRotator::ZeroRotator, To));
		HitEmitter->bAutoActivate = true;
		SetupHitEffect(HitEmitter, Hit);
	}
}

void AHitscanWeapon::BeginPlay()
{
	Super::BeginPlay();

	ShotEffectComponent->SetTemplate(ShotEffect);
	ShotEffectComponent->SetWorldTransform(GetShotTransform());
}
