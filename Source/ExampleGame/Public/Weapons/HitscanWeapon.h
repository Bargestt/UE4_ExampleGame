// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapons/GunWeapon.h"
#include "HitscanWeapon.generated.h"

class UParticleSystemComponent;

/**
 * 
 */
UCLASS()
class EXAMPLEGAME_API AHitscanWeapon : public AGunWeapon
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Effect, meta = (AllowPrivateAccess = "true"))
	UParticleSystemComponent* ShotEffectComponent;
	
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	UParticleSystem* HitEffect;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	UParticleSystem* ShotEffect;	



public:
	AHitscanWeapon();

	

	virtual void Use() override;

	UFUNCTION(BlueprintImplementableEvent)
	void SetupHitEffect(UParticleSystemComponent* Particles, FHitResult Hit);

	UFUNCTION(BlueprintImplementableEvent)
	void SetupShotEffect(UParticleSystemComponent* Particles, FHitResult Hit);

protected:
	virtual void BeginPlay() override;

};
