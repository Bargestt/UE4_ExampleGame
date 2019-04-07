// Fill out your copyright notice in the Description page of Project Settings.

#include "DamageDealerComponent.h"
#include "Kismet/GameplayStatics.h"

DEFINE_LOG_CATEGORY(LogDamageSystem);



// Sets default values for this component's properties
UDamageDealerComponent::UDamageDealerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	DamageType = UBasicDamageType::StaticClass();

	bAutoBind = true;
	bCollideWithIgnoredActors = false;

	// ...
}


// Called when the game starts
void UDamageDealerComponent::BeginPlay()
{
	Super::BeginPlay();	
	// ...

	if (bAutoBind)
	{
		Initialize();
	}
}





void UDamageDealerComponent::Initialize()
{
	CollisionSource = SetCollisionSource();

	if (CollisionSource == nullptr)
	{
		UE_LOG(LogDamageSystem, Warning, TEXT("CollisionSource is invalid"));
		return;
	}

	BindToCollisionSource(CollisionSource);
}

UPrimitiveComponent* UDamageDealerComponent::SetCollisionSource()
{
	return Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
}



TArray<AActor*> UDamageDealerComponent::GetIgnoreActors() const
{
	return IgnoreActors;
}

void UDamageDealerComponent::AddIgnoreActor(AActor* Ignore)
{
	ensureMsgf(CollisionSource, TEXT("Attempt to modify ignore actors when CollisionSource is not inititalized"));

	IgnoreActors.AddUnique(Ignore);

	if (!bCollideWithIgnoredActors)
	{
		CollisionSource->IgnoreActorWhenMoving(Ignore, true);
	}
}

void UDamageDealerComponent::RemoveIgnoreActor(AActor* IgnoredActor)
{
	ensureMsgf(CollisionSource, TEXT("Attempt to modify ignore actors when CollisionSource is not inititalized"));

	if (IgnoreActors.RemoveSingleSwap(IgnoredActor) != 0)
	{
		CollisionSource->IgnoreActorWhenMoving(IgnoredActor, false);
	}
}

bool UDamageDealerComponent::CanDamageActor(const AActor* Target) const
{
	return !GetIgnoreActors().Contains(Target);
}

bool UDamageDealerComponent::CanActivate() const
{
	return true;
}

float UDamageDealerComponent::GetDamage() const
{
	return BaseDamage;
}

UPrimitiveComponent* UDamageDealerComponent::GetCollisionSource() const
{
	return CollisionSource;
}

AController* UDamageDealerComponent::GetDamageInstigator() const
{
	return GetOwner()->GetInstigatorController();
}

AActor* UDamageDealerComponent::GetDamageCauser() const
{
	return GetOwner();
}

