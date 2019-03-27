// Fill out your copyright notice in the Description page of Project Settings.

#include "AbilityBase.h"




UAbilityBase::UAbilityBase()
{
	Owner = nullptr;
	bInitialized = false;
	SetCouldTick(false);
	bTickEnabled = false;
}

bool UAbilityBase::Setup(AActor* SetupOwner)
{
	ensureMsgf(!bInitialized, TEXT("Called initialization on already initialized ability"));

	if (!IsValid(SetupOwner)) return false;
	Owner = SetupOwner;

	bInitialized = Initialize(Owner);

	return bInitialized;
}



bool UAbilityBase::Call()
{
	if (!CanCall()) return false;

	OnCall();

#if WITH_EDITOR
	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Cyan, GetClass()->GetName() + TEXT(" Called"));
#endif

	if (GetCouldTick()) 
	{
		bTickEnabled = true;
	}

	return true;	
}

void UAbilityBase::EndCall()
{
	bTickEnabled = false;

	OnEndCall();
}





class UWorld* UAbilityBase::GetWorld() const
{
	if (Cast<UActorComponent>(GetOuter()) || Cast<AActor>(GetOuter()))
	{
		return GetOuter()->GetWorld();
	}

	return nullptr;
}



