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

	UPROPERTY(EditDefaultsOnly, Category = "Aim", meta = (AllowPrivateAccess = "true"))
	UPlayerAimComponent* AimComponent;
public:

	AGamePlayerController();	
	
	

	virtual void Possess(APawn* aPawn) override;

	virtual void UnPossess() override;

};
