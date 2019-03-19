// Fill out your copyright notice in the Description page of Project Settings.

#include "AbilitySystemComponent.h"
#include "Public/AbilitySystem/AbilityBase.h"


// Sets default values for this component's properties
UAbilitySystemComponent::UAbilitySystemComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UAbilitySystemComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	for (UAbilityBase* ability : AbilitySlots)
	{
		ability->Tick(DeltaTime);
	}
}


// Called when the game starts
void UAbilitySystemComponent::BeginPlay()
{
	Super::BeginPlay();

	Initialize();
	// ...	
}



void UAbilitySystemComponent::Initialize()
{
	for (TSubclassOf<UAbilityBase> abilityClass : DefaultAbilities)
	{
		UAbilityBase* ability = NewObject<UAbilityBase>(this, NAME_None, RF_Transient | RF_Transactional | RF_TextExportTransient);
		if (ability->Setup(GetOwner()))
		{
			AbilitySlots.Add(ability);
		}
	}
}

bool UAbilitySystemComponent::ActivateAbilitySlot(int SlotIndex)
{
	if (AbilitySlots.IsValidIndex(SlotIndex))
	{
		UAbilityBase* Ability = AbilitySlots[SlotIndex];

		return Ability->Call();		
	}

	return false;
}

void UAbilitySystemComponent::DeactivateAbilitySlot(int SlotIndex)
{
	if (AbilitySlots.IsValidIndex(SlotIndex))
	{
		UAbilityBase* Ability = AbilitySlots[SlotIndex];
		Ability->EndCall();
	}
}

