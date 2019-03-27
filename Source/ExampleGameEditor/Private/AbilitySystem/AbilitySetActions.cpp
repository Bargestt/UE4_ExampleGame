// Fill out your copyright notice in the Description page of Project Settings.

#include "AbilitySetActions.h"
#include "AbilitySet.h"

#define LOCTEXT_NAMESPACE "AssetTypeActions"



FText FAbilitySetActions::GetName() const
{
	return NSLOCTEXT("AbilitySetActions", "AssetTypeActions_AbilitySet", "Ability Set Asset");
}

FColor FAbilitySetActions::GetTypeColor() const
{
	return FColor::Yellow;
}

uint32 FAbilitySetActions::GetCategories()
{
	return EAssetTypeCategories::Misc;;
}

UClass* FAbilitySetActions::GetSupportedClass() const
{
	return UAbilitySet::StaticClass();
}


#undef LOCTEXT_NAMESPACE
