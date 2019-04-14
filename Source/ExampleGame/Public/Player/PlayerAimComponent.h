// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PlayerAimComponent.generated.h"

class ITargetInterface
{

public:

	virtual AActor* GetAimTarget() const = 0;

	virtual FVector GetAimLocation() const = 0;

	virtual FVector GetAimDirection() const = 0;
};


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class EXAMPLEGAME_API UPlayerAimComponent : public UActorComponent, public ITargetInterface
{
	GENERATED_BODY()

	USceneComponent* AimTransformComponent;

	FCollisionQueryParams AimingParameters;
	FHitResult LastHit;

	AActor* TargetedActor;
public:

	UPROPERTY(EditAnywhere, Category = "Aim")
	float Range;

public:	
	// Sets default values for this component's properties
	UPlayerAimComponent();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void SetAimTransfomrComponent(USceneComponent* NewAimTransform);

		
	
public:

	UFUNCTION(BlueprintCallable, Category = "Aim")
	virtual AActor* GetAimTarget() const override;

	UFUNCTION(BlueprintCallable, Category = "Aim")
	virtual FVector GetAimLocation() const override;

	UFUNCTION(BlueprintCallable, Category = "Aim")
	virtual FVector GetAimDirection() const override;

};
