// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/MovementAbility.h"
#include "TeleportAbility.generated.h"

class UParticleSystem;

/**
 * 
 */
UCLASS()
class EXAMPLEGAME_API UTeleportAbility : public UMovementAbility
{
	GENERATED_BODY()
	
public:
	float MaxVerticalDelta;

	float MaxDistance;

	UPROPERTY()
	UParticleSystem* ArriveEffect;

	UPROPERTY()
	UParticleSystem* DepartEffect;

	UTeleportAbility();
	
protected:

	virtual void OnCall() override;


	virtual bool CanCall() override;


	virtual bool Initialize(AActor* Owner) override;

};
