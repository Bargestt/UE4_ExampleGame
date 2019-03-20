// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/MovementAbility.h"
#include "RollAbility.generated.h"

/**
 * 
 */
UCLASS()
class EXAMPLEGAME_API URollAbility : public UMovementAbility
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability")
	float Strength;


	URollAbility();

protected:
	virtual void OnCall() override;


	virtual bool CanCall() override;
	
	
};
