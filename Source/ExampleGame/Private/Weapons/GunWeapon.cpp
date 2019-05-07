// Fill out your copyright notice in the Description page of Project Settings.

#include "GunWeapon.h"
#include "PlayerCharacter.h"
#include "DrawDebugHelpers.h"
#include "Kismet/KismetMathLibrary.h"

FName AGunWeapon::Socket_GripPrimary(TEXT("Grip1"));
FName AGunWeapon::Socket_GripSecondary(TEXT("Grip2"));
FName AGunWeapon::Socket_Muzzle(TEXT("Muzzle"));











AGunWeapon::AGunWeapon()
{
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = MeshComponent;

	MeshComponent->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("StaticMesh'/Game/Weapons/Gun/SK_FPGun.SK_FPGun'"));
	if (MeshAsset.Succeeded())
	{
		MeshComponent->SetStaticMesh(MeshAsset.Object);
	}

}



void AGunWeapon::Use()
{
	FTransform Transform = GetShotTransform();

	FVector From = Transform.GetLocation();
	FVector To = From + Transform.GetUnitAxis(EAxis::X) * 1500;

	FCollisionQueryParams params;
	params.AddIgnoredActor(GetOwner());
	params.AddIgnoredActor(this);

	FHitResult Hit;
	GetWorld()->LineTraceSingleByChannel(Hit, From, To, ECC_Visibility, params);


	if (Hit.bBlockingHit)
	{
		To = Hit.ImpactPoint;
		DrawDebugSphere(GetWorld(), To, 25, 12, FColor::Yellow, false, 5);
	}
}

void AGunWeapon::EndUse()
{
	
}

UPrimitiveComponent* AGunWeapon::GetCollisionPrimitive() const
{
	return MeshComponent;
}

FWeaponGripData AGunWeapon::GetGripData() const
{
	if (MeshComponent && MeshComponent->HasAnySockets())
	{
		bool HasPrimary = MeshComponent->GetSocketByName(AGunWeapon::Socket_GripPrimary);
		bool HasSecondary = MeshComponent->GetSocketByName(AGunWeapon::Socket_GripSecondary);

		return FWeaponGripData(
			HasPrimary,
			HasSecondary,
			HasPrimary ? MeshComponent->GetSocketTransform(AGunWeapon::Socket_GripPrimary, RTS_World) : FTransform::Identity,
			HasSecondary ? MeshComponent->GetSocketTransform(AGunWeapon::Socket_GripSecondary, RTS_World) : FTransform::Identity
		);
	}

	return FWeaponGripData();
}

void AGunWeapon::OnOwnerChange()
{
	Player = Cast<APlayerCharacter>(GetOwner());


	SetActorTickEnabled(Player != nullptr);
}

FTransform AGunWeapon::GetShotTransform()
{
	return MeshComponent->GetSocketTransform(AGunWeapon::Socket_Muzzle, RTS_World);
}

void AGunWeapon::WeaponTick(float DeltaSeconds)
{
	if (Player == nullptr)
	{
		SetActorTickEnabled(false);
		return;
	}

	FRotator AimRotation = (Player->GetAimLocation() - GetActorLocation()).Rotation();
	SetActorRotation(AimRotation);

	FVector From = GetTransform().GetLocation();
	FVector To = From + GetTransform().GetUnitAxis(EAxis::X) * 2500;
	DrawDebugLine(GetWorld(), From, To, FColor::Red);


}
