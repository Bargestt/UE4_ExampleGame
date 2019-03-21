// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Tickable.h"
#include "AbilityBase.generated.h"

/**
 * 
 */
UCLASS(Abstract, ClassGroup = (Ability))
class EXAMPLEGAME_API UAbilityBase : public UObject, public FTickableGameObject
{
	GENERATED_BODY()

	AActor* Owner;

	bool bInitialized;

protected:
	bool bCouldTick;

	bool bTickEnabled;

public:	
	UAbilityBase();

	/** 
	 * Initialize
	 * @return true if initialization was success 
	 */
	bool Setup(AActor* SetupOwner);


	/** 
	 * Call ability
	 * @return true if was successfully called 
	 */
	bool Call();

	/** End Call and tick */
	void EndCall();


	//~Begin FTickableGameObject
public:

	virtual void Tick(float DeltaTime) override { }

	virtual ETickableTickType GetTickableTickType() const override { return ETickableTickType::Conditional; }

	virtual bool IsTickable() const override { return bTickEnabled; }

	virtual TStatId GetStatId() const override { return UObject::GetStatID(); }

	//~ End FTickableGameObject


protected:
	/** Actions on call */
	virtual void OnCall() {}

	/** Actions on call end */
	virtual void OnEndCall() {}


	/** Called on setup
	 * @return true if initialization was success
	 */
	virtual bool Initialize(AActor* Owner) { return true; }
	
	/** Check if can be called before call */
	virtual bool CanCall() { return true; }


	/////////////////////////////////////////////////////////////////////
	// Getters / Setters

	FORCEINLINE bool IsInitialized() { return bInitialized; }

	FORCEINLINE bool GetCouldTick() const { return bCouldTick; }

	FORCEINLINE void SetCouldTick(bool val) { bCouldTick = val; }

	FORCEINLINE bool IsTickEnabled() const { return bTickEnabled; }

	FORCEINLINE AActor* GetOwner() { return Owner; }

	virtual class UWorld* GetWorld() const override;

};
