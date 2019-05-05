// Fill out your copyright notice in the Description page of Project Settings.

#include "GamePlayerController.h"
#include "DrawDebugHelpers.h"
#include "Kismet/KismetMathLibrary.h"




AGamePlayerController::AGamePlayerController()
{
	AimRange = 3000;
}

void AGamePlayerController::Possess(APawn* aPawn)
{
	Super::Possess(aPawn);

}

void AGamePlayerController::UnPossess()
{
	Super::UnPossess();

}

void AGamePlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	UpdateAim();
}



FRotator AGamePlayerController::GetControlRotation() const
{
	return Super::GetControlRotation();
}

FRotator AGamePlayerController::GetDesiredRotation() const
{
	DrawDebugLine(GetWorld(), AimLocation, AimLocation + AimRotation.Vector() * -1000, FColor::Yellow);
	return AimRotation;
}

void AGamePlayerController::UpdateAim()
{
	if (PlayerCameraManager == nullptr || GetPawn() == nullptr) return;

	FVector TraceStart;
	FRotator CamRot;
	PlayerCameraManager->GetCameraViewPoint(TraceStart, CamRot);

	FCollisionQueryParams Params;
	Params.AddIgnoredActor(GetPawn());

	FHitResult Hit;
	GetWorld()->LineTraceSingleByChannel(Hit, TraceStart, TraceStart + CamRot.Vector() * AimRange, ECC_Visibility, Params);	

	AimLocation = Hit.bBlockingHit ? Hit.Location : Hit.TraceEnd;		
	AimRotation = (AimLocation - GetPawn()->GetPawnViewLocation()).Rotation();
	

	DrawDebugPoint(GetWorld(), AimLocation + Hit.Normal, 5, FColor::Green);
}


