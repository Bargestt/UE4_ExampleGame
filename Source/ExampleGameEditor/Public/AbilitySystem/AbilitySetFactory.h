// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Factories/Factory.h"
#include "AssetTypeCategories.h"
#include "AbilitySetFactory.generated.h"


/**
 * 
 */
UCLASS()
class EXAMPLEGAMEEDITOR_API UAbilitySetFactory : public UFactory
{
	GENERATED_BODY()
public:
	UAbilitySetFactory();
	
	// UFactory Interface
	virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;
	virtual bool ShouldShowInNewMenu() const override;
	// End of UFactory interface


};
