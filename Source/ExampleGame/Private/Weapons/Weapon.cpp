// Fill out your copyright notice in the Description page of Project Settings.

#include "Weapon.h"
#include "Components/PrimitiveComponent.h"


// Sets default values
AWeapon::AWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	

}

// Called when the game starts or when spawned
void AWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}


void AWeapon::Tick(float DeltaSeconds)
{
	WeaponTick(DeltaSeconds);
	Super::Tick(DeltaSeconds);
}

void AWeapon::Use()
{
	
}

void AWeapon::SetOwner(AActor* NewOwner)
{
	AActor* PrevOwner = GetOwner();

	Super::SetOwner(NewOwner);

	if (GetOwner() != PrevOwner)
	{
		OnOwnerChange();
	}
}

UPrimitiveComponent* AWeapon::GetCollisionPrimitive() const
{
	return Cast<UPrimitiveComponent>(RootComponent);
}



FWeaponGripData AWeapon::GetGripData() const
{
	return FWeaponGripData();
}


void AWeapon::WeaponTick(float DeltaSeconds)
{

}

void AWeapon::OnOwnerChange()
{

}
