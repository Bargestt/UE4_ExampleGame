// Fill out your copyright notice in the Description page of Project Settings.

#include "DuplicatingStaticMeshComponent.h"
#include "Kismet/KismetMaterialLibrary.h"
#include "DrawDebugHelpers.h"
#include "MessageLog.h"




UDuplicatingStaticMeshComponent::UDuplicatingStaticMeshComponent()
{
	MaxPoolSize = 5;
	InstanceLifetime = 5.f;
	PrimaryComponentTick.bCanEverTick = true;
}

void UDuplicatingStaticMeshComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	int n = 12;
	FString debug = FString::Printf(TEXT("Pool: %d, Active: %d"), Pool.Num(), Active.Num());
	GEngine->AddOnScreenDebugMessage(n++, 5, FColor::Yellow, debug);

	for (int Index = 0; Index < Active.Num() ; Index++)
	{
		FMeshInstance& Instance = Active[Index];

		ensureMsgf(Instance.Mesh, TEXT("WTF? U CANT DELET DIS!!"));

		Instance.TimeLeft -= DeltaTime;
		OnUpdate(Instance, DeltaTime);

		if (Instance.TimeLeft <= 0)
		{
			Instance.Mesh->SetVisibility(false);
			OnRelease(Instance);

			if (Pool.Num() < MaxPoolSize) 
			{
				Pool.Add(MoveTemp(Instance));
			}
			Active.RemoveAtSwap(Index);
		}
	}

}

FMeshInstance UDuplicatingStaticMeshComponent::Duplicate()
{
	if (Pool.Num() <= 0)
	{
		Instantiate();
	}

	Active.Add(Pool.Pop());

	FMeshInstance& Instance = Active.Last();
	Instance.TimeLeft = InstanceLifetime;	
	Instance.Mesh->SetVisibility(true);	

	OnDuplication(Instance);
	return Instance;
}

void UDuplicatingStaticMeshComponent::Instantiate()
{
	UMaterialInstanceDynamic* DynamicMaterial = UKismetMaterialLibrary::CreateDynamicMaterialInstance(this, GetInstanceMaterial());

	UStaticMeshComponent* Mesh = NewObject<UStaticMeshComponent>(this, NAME_None);
	Mesh->SetupAttachment(this);
	Mesh->SetRelativeTransform(GetInstanceTransform());
	Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Mesh->SetCanEverAffectNavigation(false);

	Mesh->SetMaterial(0, DynamicMaterial);
	Mesh->SetStaticMesh(GetStaticMesh());

	Mesh->RegisterComponent();

	Pool.Add({ Mesh, DynamicMaterial });
}



TArray<FMeshInstance> UDuplicatingStaticMeshComponent::GetActive() const
{
	return Active;
}

int UDuplicatingStaticMeshComponent::GetActiveNum() const
{
	return Active.Num();
}

void UDuplicatingStaticMeshComponent::GetInstance(int Index, FMeshInstance& Instance) const
{
	if (Active.IsValidIndex(Index))
	{
		Instance = Active[Index];
	}
	else
	{
		FString Message = FString::Printf(TEXT("Attempted to get instance %d out of %d active instances in %s"), Index, GetActiveNum(), *GetPathName(GetWorld()));
		FMessageLog("PIE").Error(FText::FromString(Message));
	}
}


UMaterialInterface* UDuplicatingStaticMeshComponent::GetInstanceMaterial_Implementation() const
{
	return InstanceMaterial;
}

FTransform UDuplicatingStaticMeshComponent::GetInstanceTransform_Implementation() const
{
	return FTransform::Identity;
}



