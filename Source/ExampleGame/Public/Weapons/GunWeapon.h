// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapons/Weapon.h"
#include "GunWeapon.generated.h"

class APlayerCharacter;




/**
 * 
 */
UCLASS()
class EXAMPLEGAME_API AGunWeapon : public AWeapon
{
	GENERATED_BODY()

	APlayerCharacter* Player;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Weapon, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* MeshComponent;

public:

	static FName Socket_GripPrimary;

	static FName Socket_GripSecondary;

	static FName Socket_Muzzle;






public:
	AGunWeapon();




	virtual void Use() override;


	virtual void EndUse() override;

	virtual UPrimitiveComponent* GetCollisionPrimitive() const override;


	virtual FWeaponGripData GetGripData() const override;

protected:
	virtual void OnOwnerChange() override;

	virtual FTransform GetShotTransform();

	virtual void WeaponTick(float DeltaSeconds) override;

};
