// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/BaseCharacter.h"
#include "PlayerCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UPlayerAimComponent;
class AWeapon;
class AGamePlayerController;

/**
 * 
 */
UCLASS()
class EXAMPLEGAME_API APlayerCharacter : public ABaseCharacter
{
	GENERATED_BODY()
	
	

	AGamePlayerController* PlayerController;

protected:
	/** Camera arm positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraArm;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Weapon, meta = (AllowPrivateAccess = "true"))
	AWeapon* Weapon;

public:
	UPROPERTY(EditAnywhere, Category = "Debug")
	TSubclassOf<AWeapon> DefaultWeapon;


	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		float BaseLookUpRate;


	   


	



public:
	// Sets default values for this character's properties
	APlayerCharacter();

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;
protected:
	//~ Begin Basic Input 

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	/** Called for Dash input */
	void Dash();

	/** Called for Roll evasion */
	void Roll();

	DECLARE_DELEGATE_OneParam(FAbilitySlotDelegate, int32);
	void CallAbilitySlot(int32 SlotIndex);

	void StartShooting();

	void EndShooting();


	void MoveCamera();
	//~ End Basic Input



	virtual void PossessedBy(AController* NewController) override;

	virtual void UnPossessed() override;

	

//~ Begin BaseCharacter
	virtual FRotator GetAimOffsets() const override;
//~ End BaseCharacter



	//~ Begin WeaponInteraction

	UFUNCTION(BlueprintCallable, Category = "Player|Weapon")
	void SetWeapon(AWeapon* NewWeapon);

	virtual void OnWeaponChange() {};

	//~ End WeaponInteraction


public:
	//~ Getters / Setters

	/** Returns CameraArm subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraArm() const { return CameraArm; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
	/** Returns current Weapon */
	FORCEINLINE class AWeapon* GetWeapon() const { return Weapon; }


};
