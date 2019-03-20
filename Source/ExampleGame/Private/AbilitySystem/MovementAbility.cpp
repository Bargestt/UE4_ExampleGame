// Fill out your copyright notice in the Description page of Project Settings.

#include "MovementAbility.h"
#include "GameFramework/CharacterMovementComponent.h"





bool UMovementAbility::Initialize(AActor* Owner)
{
	MovementComponent = Owner->FindComponentByClass<UCharacterMovementComponent>();

	return MovementComponent != nullptr;
}
