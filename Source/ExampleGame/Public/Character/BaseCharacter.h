// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"


UCLASS()
class EXAMPLEGAME_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

	UAnimInstance* Animator;

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BaseCharacter")
	float RollStrength;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BaseCharacter")
	float DashStrength;

public:
	ABaseCharacter();

	virtual void BeginPlay() override;

protected:
	virtual bool CanRoll() const;

	virtual bool CanDash() const;

	void ActionRoll();

	void ActionDash();
};
