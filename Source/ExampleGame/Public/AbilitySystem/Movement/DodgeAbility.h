// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/MovementAbility.h"
#include "DodgeAbility.generated.h"

/**
 * 
 */
UCLASS()
class EXAMPLEGAME_API UDodgeAbility : public UMovementAbility
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability")
	float Strength;	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability")
	float InAirMultiplier;
	
	UDodgeAbility();

protected:
	virtual void OnCall() override;


	virtual bool CanCall() override;

};
