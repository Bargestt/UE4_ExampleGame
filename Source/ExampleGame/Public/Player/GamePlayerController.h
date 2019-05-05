// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GamePlayerController.generated.h"

class UPlayerAimComponent;
/**
 * 
 */
UCLASS()
class EXAMPLEGAME_API AGamePlayerController : public APlayerController
{
	GENERATED_BODY()


	FVector AimLocation;

	FRotator AimRotation;

	float AimRange;

public:

	AGamePlayerController();	
	
	

	virtual void Possess(APawn* aPawn) override;

	virtual void UnPossess() override;


	virtual void PlayerTick(float DeltaTime) override;



	virtual FRotator GetControlRotation() const override;

	virtual FRotator GetDesiredRotation() const override;

protected:
	virtual void UpdateAim();


public:

	UFUNCTION(BlueprintCallable, Category="Controller|Aim")
	FVector GetAimLocation() const { return AimLocation; }

	UFUNCTION(BlueprintCallable, Category = "Controller|Aim")
	FRotator GetAimRotation() const { return AimRotation; }






};
