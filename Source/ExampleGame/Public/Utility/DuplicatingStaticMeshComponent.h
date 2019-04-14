// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "DuplicatingStaticMeshComponent.generated.h"

USTRUCT(BlueprintType)
struct FMeshInstance
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
	UStaticMeshComponent* Mesh;

	UPROPERTY(BlueprintReadOnly)
	UMaterialInstanceDynamic* Material;

	UPROPERTY(BlueprintReadOnly)
	float TimeLeft;
};



/**
 * 
 */
UCLASS(Blueprintable, BlueprintType, classGroup = "Utility", meta=(BlueprintSpawnableComponent) )
class EXAMPLEGAME_API UDuplicatingStaticMeshComponent : public UStaticMeshComponent
{
	GENERATED_BODY()

	UPROPERTY()
	TArray<FMeshInstance> Pool;	

	UPROPERTY()
	TArray<FMeshInstance> Active;

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Instances")
	float InstanceLifetime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Instances")
	int MaxPoolSize;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Instances")
	UMaterialInterface* InstanceMaterial;

public:
	UDuplicatingStaticMeshComponent();

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

	/** Duplicate mesh. 
	 * @return Data of created duplicate
	 */
	UFUNCTION(BlueprintCallable, Category="Components|DuplicatingMesh")
	FMeshInstance Duplicate();

protected:

	void Instantiate();

	UFUNCTION(BlueprintImplementableEvent)
	void OnDuplication(const FMeshInstance& InstanceData);

	UFUNCTION(BlueprintImplementableEvent)
	void OnUpdate(const FMeshInstance& InstanceData, float DeltaTime);

	UFUNCTION(BlueprintImplementableEvent)
	void OnRelease(const FMeshInstance& InstanceData);

	UFUNCTION(BlueprintNativeEvent)
	UMaterialInterface* GetInstanceMaterial() const;

	UFUNCTION(BlueprintNativeEvent)
	FTransform GetInstanceTransform() const;

public:

	UFUNCTION(BlueprintCallable, Category = "Components|DuplicatingMesh")
	TArray<FMeshInstance> GetActive() const;

	UFUNCTION(BlueprintCallable, Category = "Components|DuplicatingMesh")
	int GetActiveNum() const;

	UFUNCTION(BlueprintCallable, Category = "Components|DuplicatingMesh")
	void GetInstance(int Index, FMeshInstance& Instance) const;
};
