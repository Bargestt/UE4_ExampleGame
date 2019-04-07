// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Damage/DamageDealerComponent.h"
#include "RadialDamageComponent.generated.h"

/**
 * 
 */
UCLASS()
class EXAMPLEGAME_API URadialDamageComponent : public UDamageDealerComponent
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Damage Radial")
	float Radius;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Damage Radial")
	TEnumAsByte<ECollisionChannel> DamagePreventionChannel;

public:

	URadialDamageComponent();


	virtual void Explode();

protected:
	virtual void InvokeRadialDamage(const FVector& Origin) const;


};
