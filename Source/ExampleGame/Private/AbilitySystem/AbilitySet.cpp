// Fill out your copyright notice in the Description page of Project Settings.

#include "AbilitySet.h"



#if WITH_EDITOR
void UAbilitySet::PostInitProperties()
{
	Super::PostInitProperties();
}

void UAbilitySet::PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	for (TSubclassOf<UAbilityBase> ability : ABilityTypes)
	{
		
	}
}
#endif

void UAbilitySet::Add()
{	
	Abilities.Add(NewObject<UAbilityBase>(this, NewClass, NAME_None));
}
