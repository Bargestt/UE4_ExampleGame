// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Weapon.generated.h"

USTRUCT(BlueprintType)
struct FWeaponGripData
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite)
	bool HasPrimaryGrip;

	UPROPERTY(BlueprintReadWrite)
	bool HasSecondaryGrip;

	UPROPERTY(BlueprintReadWrite)
	FTransform PrimaryGripTransform;

	UPROPERTY(BlueprintReadWrite)
	FTransform SecondaryGripTransform;

	FWeaponGripData() : FWeaponGripData(false, false, FTransform::Identity, FTransform::Identity)
	{}

	FWeaponGripData(bool HasPrimaryGrip, bool HasSecondaryGrip, const FTransform& PrimaryGripTransform, const FTransform& SecondaryGripTransform)
		: HasPrimaryGrip(HasPrimaryGrip)
		, HasSecondaryGrip(HasSecondaryGrip)
		, PrimaryGripTransform(PrimaryGripTransform)
		, SecondaryGripTransform(SecondaryGripTransform)
	{}
};



UCLASS(Abstract, BlueprintType, Blueprintable, classGroup="Weapon")
class EXAMPLEGAME_API AWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeapon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:

	virtual void Tick(float DeltaSeconds) override;

	/** Primary use function by Owner*/
	virtual void Use();

	virtual void EndUse() {}

	virtual void SetOwner(AActor* NewOwner) override;

	virtual UPrimitiveComponent* GetCollisionPrimitive() const;



	UFUNCTION(BlueprintCallable, Category = "Weapon")
	virtual FWeaponGripData GetGripData() const;


protected:

	virtual void WeaponTick(float DeltaSeconds);

	virtual void OnOwnerChange();

};
