// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "IDetailCustomization.h"

class FReply;

/**
 * 
 */
class EXAMPLEGAMEEDITOR_API FAbilitySetCustomization : public IDetailCustomization
{
public:
	static TSharedRef< IDetailCustomization > MakeInstance();



	virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;

	FReply ButtonClickEvent();

};
