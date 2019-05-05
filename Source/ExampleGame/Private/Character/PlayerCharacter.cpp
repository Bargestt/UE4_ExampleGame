// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerCharacter.h"



#include "Camera/CameraComponent.h"

#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "AbilitySystemComponent.h"

#include "DrawDebugHelpers.h"
#include "Weapon.h"
#include "GunWeapon.h"
#include "Components/PrimitiveComponent.h"
#include "GamePlayerController.h"








// Sets default values
APlayerCharacter::APlayerCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(40.f, 100.f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraArm"));
	CameraArm->SetupAttachment(RootComponent);
	CameraArm->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	CameraArm->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraArm, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (DefaultWeapon)
	{
		FActorSpawnParameters Params;
		Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
		AWeapon* weapon = GetWorld()->SpawnActor<AWeapon>(DefaultWeapon, GetActorTransform(), Params);
		SetWeapon(weapon);
	}
}



void APlayerCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}


//////////////////////////////////////////////////////////////////////////
// Input
// 

void APlayerCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);

	PlayerInputComponent->BindAxis("MoveForward", this, &APlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APlayerCharacter::MoveRight);

	PlayerInputComponent->BindAction("Dash", IE_Pressed, this, &APlayerCharacter::Dash);
	PlayerInputComponent->BindAction("Roll", IE_Pressed, this, &APlayerCharacter::Roll);

	PlayerInputComponent->BindAction("Shoot", IE_Pressed, this, &APlayerCharacter::StartShooting);
	PlayerInputComponent->BindAction("Shoot", IE_Released, this, &APlayerCharacter::EndShooting);

	PlayerInputComponent->BindAction("MoveCamera", IE_Released, this, &APlayerCharacter::MoveCamera);

	//AbilitySlot_X
	PlayerInputComponent->BindAction<FAbilitySlotDelegate>("AbilitySlot_1", IE_Pressed, this, &APlayerCharacter::CallAbilitySlot, 1);
	PlayerInputComponent->BindAction<FAbilitySlotDelegate>("AbilitySlot_2", IE_Pressed, this, &APlayerCharacter::CallAbilitySlot, 2);
	PlayerInputComponent->BindAction<FAbilitySlotDelegate>("AbilitySlot_3", IE_Pressed, this, &APlayerCharacter::CallAbilitySlot, 3);
	PlayerInputComponent->BindAction<FAbilitySlotDelegate>("AbilitySlot_4", IE_Pressed, this, &APlayerCharacter::CallAbilitySlot, 4);
	PlayerInputComponent->BindAction<FAbilitySlotDelegate>("AbilitySlot_5", IE_Pressed, this, &APlayerCharacter::CallAbilitySlot, 5);
	PlayerInputComponent->BindAction<FAbilitySlotDelegate>("AbilitySlot_6", IE_Pressed, this, &APlayerCharacter::CallAbilitySlot, 6);
	PlayerInputComponent->BindAction<FAbilitySlotDelegate>("AbilitySlot_7", IE_Pressed, this, &APlayerCharacter::CallAbilitySlot, 7);
	PlayerInputComponent->BindAction<FAbilitySlotDelegate>("AbilitySlot_8", IE_Pressed, this, &APlayerCharacter::CallAbilitySlot, 8);
	PlayerInputComponent->BindAction<FAbilitySlotDelegate>("AbilitySlot_9", IE_Pressed, this, &APlayerCharacter::CallAbilitySlot, 9);

}


void APlayerCharacter::MoveForward(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void APlayerCharacter::MoveRight(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}



void APlayerCharacter::Dash()
{
	ActionDash();
}

void APlayerCharacter::Roll()
{
	ActionRoll();
}



void APlayerCharacter::CallAbilitySlot(int32 SlotIndex)
{
	GetAbilitySystem()->ActivateAbilitySlot(SlotIndex-1);
}

void APlayerCharacter::StartShooting()
{
	if (Weapon == nullptr) return;

	Weapon->Use();
}

void APlayerCharacter::EndShooting()
{
	if (Weapon == nullptr) return;

	Weapon->EndUse();
}


void APlayerCharacter::MoveCamera()
{
	CameraArm->SetRelativeLocation(CameraArm->RelativeLocation * FVector(1, -1, 1));
}

void APlayerCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	PlayerController = Cast<AGamePlayerController>(NewController);
}

void APlayerCharacter::UnPossessed()
{
	Super::UnPossessed();

	PlayerController = nullptr;
}



FRotator APlayerCharacter::GetAimOffsets() const
{
	if (PlayerController)
	{		
		FVector EyeLoc = FVector(0.f, 0.f, BaseEyeHeight);
		FVector AimLocationLocal = GetTransform().InverseTransformPosition(PlayerController->GetAimLocation());

		FRotator AimRotaion = (AimLocationLocal - EyeLoc).GetSafeNormal().Rotation();
		return AimRotaion;
	}

	return Super::GetAimOffsets();
}


void APlayerCharacter::SetWeapon(AWeapon* NewWeapon)
{
	if (NewWeapon == nullptr) return;
	if (NewWeapon == Weapon) return;

	if (Weapon)
	{
		GetCapsuleComponent()->IgnoreComponentWhenMoving(Weapon->GetCollisionPrimitive(), false);
		Weapon->SetOwner(nullptr);
	}
	Weapon = NewWeapon;

	Weapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, TEXT("hand_r"));
	Weapon->SetActorRelativeRotation(FRotator(0, 180, 0)); // Fix hand transform
	GetCapsuleComponent()->IgnoreComponentWhenMoving(Weapon->GetCollisionPrimitive(), true);

	Weapon->SetOwner(this);
	OnWeaponChange();
}



