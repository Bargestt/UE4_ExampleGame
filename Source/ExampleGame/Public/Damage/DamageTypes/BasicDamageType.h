// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/DamageType.h"
#include "BasicDamageType.generated.h"

/**
 * 
 */
UCLASS()
class EXAMPLEGAME_API UBasicDamageType : public UDamageType
{
	GENERATED_BODY()
	
public:

	UBasicDamageType()
	{
		bCausedByWorld = false;
	}
	
		
};
