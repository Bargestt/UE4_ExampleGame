// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseCharacter.h"
#include "Public/Character/BaseCharaterAnimatorInterface.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "DrawDebugHelpers.h"
#include "AbilitySystemComponent.h"
#include "Animation/AnimInstance.h"
#include "GamePlayerController.h"



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
	if (animInstance && animInstance->Implements<UBaseCharaterAnimatorInterface>())
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
	if (CanRoll())
	{ 
		
	}
}

void ABaseCharacter::ActionDash()
{
	if (CanDash())
	{
		
	}
}

FRotator ABaseCharacter::GetAimOffsets() const
{
	if (GetController() == nullptr) return FRotator::ZeroRotator;

	const FVector AimDirectionWorld = GetBaseAimRotation().Vector();
	const FVector AimDirectionLocal = ActorToWorld().InverseTransformVectorNoScale(AimDirectionWorld);
	const FRotator AimRotator = AimDirectionLocal.Rotation();

	return AimRotator;
}
