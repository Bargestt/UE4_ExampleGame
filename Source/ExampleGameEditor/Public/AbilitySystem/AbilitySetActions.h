// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AssetTypeActions_Base.h"

//static EAssetTypeCategories::Type MY_AssetCategory;
/**
 * 
 */
class EXAMPLEGAMEEDITOR_API FAbilitySetActions : public FAssetTypeActions_Base
{


public:
	virtual FText GetName() const override;

	virtual FColor GetTypeColor() const override;

	virtual uint32 GetCategories() override;


	virtual UClass* GetSupportedClass() const override;

};
