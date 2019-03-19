// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "AbilityBase.generated.h"

/**
 * 
 */
UCLASS(Abstract, ClassGroup = (Ability))
class EXAMPLEGAME_API UAbilityBase : public UObject
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

	/** Tick while call in progress */
	void Tick(float DeltaTime);

	/** End Call and tick */
	void EndCall();

protected:
	/** Actions on call */
	virtual void OnCall() {}

	/** Actions on tick */
	virtual void OnTick(float DeltaTime) {}

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

	virtual class UWorld* GetWorld() const override;

};
