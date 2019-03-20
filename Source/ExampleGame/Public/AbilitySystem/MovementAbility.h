// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/AbilityBase.h"
#include "MovementAbility.generated.h"

class UCharacterMovementComponent;

/**
 * 
 */
UCLASS(Abstract)
class EXAMPLEGAME_API UMovementAbility : public UAbilityBase
{
	GENERATED_BODY()
	
protected:
	UCharacterMovementComponent* MovementComponent;

	virtual bool Initialize(AActor* Owner) override;
};
