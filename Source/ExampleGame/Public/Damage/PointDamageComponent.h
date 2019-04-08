// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Damage/DamageDealerComponent.h"
#include "PointDamageComponent.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FDamageAppliedSignature, UPointDamageComponent*, DamageComponent, AActor*, DamagedActor);

/**
 * Apply PointDamage on RootComponent hits
 */
UCLASS(ClassGroup = (Damage), meta = (BlueprintSpawnableComponent))
class EXAMPLEGAME_API UPointDamageComponent : public UDamageDealerComponent
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintAssignable, Category="Damage")
	FDamageAppliedSignature OnDamageApply;
	

protected:

	bool bDamageAppled;

public:

	UPointDamageComponent();

	virtual bool CanActivate() const override;

	UFUNCTION(BlueprintCallable, Category="Damage|PointDamage")
	void Reset();
	
protected:
	virtual void InvokePointDamage(AActor* Target, const FVector& Direction, const FHitResult& Hit);


	virtual void BindToCollisionSource(UPrimitiveComponent* Source) override;

	UFUNCTION()
	virtual void Hit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
};
