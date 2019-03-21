// Fill out your copyright notice in the Description page of Project Settings.

#include "TeleportAbility.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystem.h"




UTeleportAbility::UTeleportAbility()
{
	MaxVerticalDelta = 120;

	MaxDistance = 1000;
}

void UTeleportAbility::OnCall()
{
	FVector Direction = MovementComponent->GetLastInputVector();
	if (Direction.IsNearlyZero())
	{
		Direction = GetOwner()->GetActorForwardVector();
	}
	
	const FVector Start = GetOwner()->GetActorLocation();
	FVector End = Start + Direction * MaxDistance;

	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(GetOwner());

	FHitResult HitResult;
	if (GetWorld()->LineTraceSingleByProfile(HitResult, Start, End, TEXT("Pawn"), QueryParams))
	{
		FVector BoundsOrigin, BoundsExtent;
		GetOwner()->GetActorBounds(true, BoundsOrigin, BoundsExtent);

		const float BoundsRadius = BoundsExtent.Size2D();
		const FVector PotentialLedge = HitResult.ImpactPoint + Direction * BoundsRadius + FVector(0, 0, MaxVerticalDelta);

		FFindFloorResult FloorResult;
		MovementComponent->FindFloor(PotentialLedge, FloorResult, false);

		if (FloorResult.bWalkableFloor)
		{
			End = FloorResult.HitResult.ImpactPoint + FVector(0, 0, BoundsExtent.Z);
		}
		else
		{
			End = HitResult.ImpactPoint - Direction * BoundsRadius;
		}
	}

	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), DepartEffect, GetOwner()->GetActorTransform());

	GetOwner()->SetActorLocation(End);

	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ArriveEffect, GetOwner()->GetActorTransform());
}

bool UTeleportAbility::CanCall()
{
	return MovementComponent->IsWalking();
}

bool UTeleportAbility::Initialize(AActor* Owner)
{
	ArriveEffect = LoadObject<UParticleSystem>(nullptr, TEXT("ParticleSystem'/Game/Includes/StarterContent/Particles/P_Explosion.P_Explosion'"));
	DepartEffect = LoadObject<UParticleSystem>(nullptr, TEXT("ParticleSystem'/Game/Includes/StarterContent/Particles/P_Explosion.P_Explosion'"));

	return Super::Initialize(Owner);
}
