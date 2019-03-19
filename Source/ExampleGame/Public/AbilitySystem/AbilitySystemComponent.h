// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AbilitySystemComponent.generated.h"

class UAbilityBase;


UCLASS( ClassGroup=(Ability), meta=(BlueprintSpawnableComponent), BlueprintType )
class EXAMPLEGAME_API UAbilitySystemComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category = "AbilitySystem")
	TSet<TSubclassOf<UAbilityBase>> DefaultAbilities;

private:
	UPROPERTY()
	TArray<UAbilityBase*> AbilitySlots;

public:	
	// Sets default values for this component's properties
	UAbilitySystemComponent();

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	void Initialize();

	UFUNCTION(BlueprintCallable, Category = "Abilities|AbilitySystem")
	bool ActivateAbilitySlot(int SlotIndex);

	UFUNCTION(BlueprintCallable, Category = "Abilities|AbilitySystem")
	void DeactivateAbilitySlot(int SlotIndex);

	UFUNCTION(BlueprintCallable, Category = "Abilities|AbilitySystem")
	TArray<UAbilityBase*> GetAbilitySlots() { return AbilitySlots; }
};
