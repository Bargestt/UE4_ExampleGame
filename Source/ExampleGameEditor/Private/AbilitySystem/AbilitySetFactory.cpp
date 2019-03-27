// Fill out your copyright notice in the Description page of Project Settings.

#include "AbilitySetFactory.h"
#include "AbilitySet.h"




UAbilitySetFactory::UAbilitySetFactory()
{
	bCreateNew = true;
	bEditAfterNew = true;
	SupportedClass = UAbilitySet::StaticClass();
}


UObject* UAbilitySetFactory::FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn)
{
	return NewObject<UAbilitySet>(InParent, Class, Name, Flags);;
}

bool UAbilitySetFactory::ShouldShowInNewMenu() const
{
	return true;
}
