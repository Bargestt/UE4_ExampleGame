// Fill out your copyright notice in the Description page of Project Settings.

#include "RollAbility.h"
#include "GameFramework/CharacterMovementComponent.h"



URollAbility::URollAbility()
{
	Strength = 500;
}

void URollAbility::OnCall()
{
	FVector dir = MovementComponent->GetLastInputVector();
	if (dir.IsNearlyZero()) dir = GetOwner()->GetActorForwardVector();

	// raise impulse vector a bit up
	dir.Z = dir.Size2D() * FMath::Tan(FMath::DegreesToRadians(15));

	MovementComponent->AddImpulse(dir * Strength, true);
}

bool URollAbility::CanCall()
{
	return MovementComponent->IsWalking();
}
