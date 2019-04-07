// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BasicDamageType.h"

#include "DamageDealerComponent.generated.h"



DECLARE_LOG_CATEGORY_EXTERN(LogDamageSystem, All, All);



UCLASS(Abstract, ClassGroup=(Damage), meta=(BlueprintSpawnableComponent) )
class EXAMPLEGAME_API UDamageDealerComponent : public UActorComponent
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Damage")
	TSubclassOf<UBasicDamageType> DamageType;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Damage")
	float BaseDamage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Damage")
	bool bAutoBind;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Damage")
	bool bCollideWithIgnoredActors;

private:

	TArray<AActor*> IgnoreActors;

	UPrimitiveComponent* CollisionSource;

public:	
	// Sets default values for this component's properties
	UDamageDealerComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	/** Basic setup */
	virtual void Initialize();

	/** Find component that will be used for collision events */
	virtual UPrimitiveComponent* SetCollisionSource();

	virtual void BindToCollisionSource(UPrimitiveComponent* Source) {}


	// Events 
	virtual void OnDamageApply() {}
	// 

public:

	TArray<AActor*> GetIgnoreActors() const;

	void AddIgnoreActor(AActor* Ignore);

	void RemoveIgnoreActor(AActor* IgnoredActor);


	virtual bool CanDamageActor(const AActor* Target) const;


	virtual bool CanActivate() const;

	virtual float GetDamage() const;

	UPrimitiveComponent* GetCollisionSource() const;

	virtual AController* GetDamageInstigator() const;

	virtual AActor* GetDamageCauser() const;

};
