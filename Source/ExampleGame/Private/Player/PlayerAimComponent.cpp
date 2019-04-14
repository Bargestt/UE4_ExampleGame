// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerAimComponent.h"
#include "DrawDebugHelpers.h"


// Sets default values for this component's properties
UPlayerAimComponent::UPlayerAimComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;


	Range = 1500;
	// ...
}


// Called every frame
void UPlayerAimComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (AimTransformComponent == nullptr)
	{
		SetComponentTickEnabled(false);
		return;
	}

	FVector From = AimTransformComponent->GetComponentLocation();
	FVector To = From + AimTransformComponent->GetForwardVector() * Range;
	
	GetWorld()->LineTraceSingleByChannel(LastHit, From, To, ECC_Visibility, AimingParameters);
	

	DrawDebugPoint(GetWorld(), GetAimLocation(), 15, FColor::Yellow);
	DrawDebugLine(GetWorld(), From, To, FColor::Green);

	GEngine->AddOnScreenDebugMessage(1, 5, FColor::Cyan, GetAimDirection().ToString());
}

void UPlayerAimComponent::SetAimTransfomrComponent(USceneComponent* NewAimTransform)
{
	AimTransformComponent = NewAimTransform;

	SetComponentTickEnabled(NewAimTransform != nullptr);


	AimingParameters = FCollisionQueryParams::DefaultQueryParam;	
	if (APlayerController* Player = Cast<APlayerController>(GetOwner()))
	{
		if (Player->GetPawn())
		{
			AimingParameters.AddIgnoredActor(Player->GetPawn());
		}
	}
	else
	{
		AimingParameters.AddIgnoredActor(GetOwner());
	}
}

AActor* UPlayerAimComponent::GetAimTarget() const
{
	return nullptr;
}

FVector UPlayerAimComponent::GetAimLocation() const
{
	return LastHit.bBlockingHit ? LastHit.Location : LastHit.TraceEnd;
}

FVector UPlayerAimComponent::GetAimDirection() const
{
	return AimTransformComponent->GetForwardVector();
}

