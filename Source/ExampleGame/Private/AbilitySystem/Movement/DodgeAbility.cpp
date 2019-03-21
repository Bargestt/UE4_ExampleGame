// Fill out your copyright notice in the Description page of Project Settings.

#include "DodgeAbility.h"
#include "GameFramework/CharacterMovementComponent.h"



UDodgeAbility::UDodgeAbility()
{
	Strength = 3500;
	InAirMultiplier = 0.2f;
}

void UDodgeAbility::OnCall()
{	
	FVector dir = MovementComponent->GetLastInputVector();
	if (dir.IsNearlyZero()) dir = GetOwner()->GetActorForwardVector();

	float force = Strength * (MovementComponent->IsWalking() ? 1 : InAirMultiplier);

	MovementComponent->AddImpulse(dir * force, true);
}

bool UDodgeAbility::CanCall()
{
	return true;
}
