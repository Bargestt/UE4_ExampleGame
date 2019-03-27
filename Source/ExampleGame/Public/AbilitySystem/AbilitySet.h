// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "AbilityBase.h"
#include "AbilitySet.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class EXAMPLEGAME_API UAbilitySet : public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly, Category = "AbilitySet")
	TSet<TSubclassOf<UAbilityBase>> ABilityTypes;
	
	UPROPERTY(VisibleAnywhere, Instanced, Category = "AbilitySet")
	TArray<UAbilityBase*> Abilities;
	
#if WITH_EDITOR
	virtual void PostInitProperties() override;

	virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;
#endif

	UPROPERTY(EditDefaultsOnly, Category = "AbilitySet")
	TSubclassOf<UAbilityBase> NewClass;

	UFUNCTION(CallInEditor, Category = "AbilitySet")
	void Add();

};
