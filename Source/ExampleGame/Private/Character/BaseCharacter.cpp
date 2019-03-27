// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseCharacter.h"
#include "Public/Character/BaseCharaterAnimatorInterface.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "DrawDebugHelpers.h"
#include "AbilitySystemComponent.h"
#include "Animation/AnimInstance.h"



ABaseCharacter::ABaseCharacter()
{
	Animator = nullptr;

	RollStrength = 600;
	DashStrength = 3500;

	Abilities = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystem"));
}

void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	class UAnimInstance* animInstance = GetMesh()->GetAnimInstance();
	if (animInstance->Implements<UBaseCharaterAnimatorInterface>())
	{
		Animator = animInstance;
	}
	else
	{
		UKismetSystemLibrary::PrintWarning(TEXT("ABaseCharacter::AnimInstance must implement BaseCharaterAnimatorInterface to properly animate"));
	}
}

bool ABaseCharacter::CanRoll() const
{
	return GetCharacterMovement()->IsWalking();
}

bool ABaseCharacter::CanDash() const
{
	return true;
}

void ABaseCharacter::ActionRoll()
{
	if (!CanRoll())
	{ 
		return;
	}


	FVector dir = GetMovementComponent()->GetLastInputVector();
	if (dir.IsNearlyZero()) dir = GetActorForwardVector();

	// raise impulse vector a bit up
	dir.Z = dir.Size2D() * FMath::Tan(FMath::DegreesToRadians(15));

	GetCharacterMovement()->AddImpulse(dir * RollStrength, true);

	if (Animator)
	{
		IBaseCharaterAnimatorInterface::Execute_DodgeRollStart(Animator);
	}
}

void ABaseCharacter::ActionDash()
{
	if (!CanDash())
	{
		return;
	}

	FVector dir = GetMovementComponent()->GetLastInputVector();
	if (dir.IsNearlyZero()) dir = GetActorForwardVector();

	float force = DashStrength * (GetCharacterMovement()->IsWalking() ? 1 : 0.2f);

	GetCharacterMovement()->AddImpulse(dir * force , true);
	if (Animator)
	{
		IBaseCharaterAnimatorInterface::Execute_DodgeDashStart(Animator);
	}
}
