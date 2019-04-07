// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"


UCLASS( ClassGroup=(Damage), meta=(BlueprintSpawnableComponent) )
class EXAMPLEGAME_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, Category = "Health")
	float MaxHealth;

	float CurrentHealth;

public:	
	// Sets default values for this component's properties
	UHealthComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	virtual void Inititalize();

	UFUNCTION()
	virtual void RecievePointDamage(AActor* DamagedActor, float Damage, AController* InstigatedBy, FVector HitLocation, UPrimitiveComponent* FHitComponent, FName BoneName, FVector ShotFromDirection, const UDamageType* DamageType, AActor* DamageCauser);
	UFUNCTION()
	virtual void RecieveRadialDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, FVector Origin, FHitResult HitInfo, AController* InstigatedBy, AActor* DamageCauser);

	/** Final damage applied after all damage receiving logic is done */
	void ApplyDamageFinal(float Damage, TSubclassOf<UDamageType> DamageType, AController* InstigatedBy, AActor* DamageCauser);

	virtual void OnDeath(float LastDamage, float OverDamage, TSubclassOf<UDamageType> DamageType, AController* KilledBy, AActor* DamageCauser);

public:
	
	virtual bool IsAlive() const;

	virtual float GetMaxHealth() const;

	virtual float GetCurrentHealth() const;

	virtual void Restore();


};
