// Fill out your copyright notice in the Description page of Project Settings.

#include "GamePlayerController.h"
#include "PlayerAimComponent.h"




AGamePlayerController::AGamePlayerController()
{
	AimComponent = CreateDefaultSubobject<UPlayerAimComponent>(TEXT("AimComponent"));
}

void AGamePlayerController::Possess(APawn* aPawn)
{
	Super::Possess(aPawn);

	AimComponent->SetAimTransfomrComponent(PlayerCameraManager->GetTransformComponent());
}

void AGamePlayerController::UnPossess()
{
	Super::UnPossess();

	AimComponent->SetAimTransfomrComponent(nullptr);
}
