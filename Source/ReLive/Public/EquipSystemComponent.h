// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Character.h" 
#include "Engine/SkeletalMesh.h"
#include "UObject/SoftObjectPath.h" 
#include "Engine/StreamableManager.h" 
#include "Engine/AssetManager.h" 
#include "Components/SphereComponent.h"
#include "Components/SkeletalMeshComponent.h"

#include "EquipSystemComponent.generated.h"

/**
 *
 */
DECLARE_DELEGATE_OneParam(FInputEquipSecondaryDelegate, class AActor* OtherActor);
DECLARE_DELEGATE_OneParam(FInputUnEquipSecondaryDelegate, class AActor* OtherActor);
DECLARE_DELEGATE(FInputFireSecondaryDelegate);
UCLASS()
class RELIVE_API UEquipSystemComponent : public USphereComponent {
	GENERATED_BODY()


public:
	UEquipSystemComponent();
	//! @brief: Shoots a projectile if a weapon is equiped 
	//! @note: [F] Key Action ability
	bool CanFire;
protected:

	//! @brief: Called when the game starts or when spawned
	virtual void BeginPlay() override;


	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);


private:

	//! @brief: Equips this actor to a character 
	//! @note: [E] Key that will add this actor to the players hand 
	void Equip(class AActor* OtherActor);

	//! @brief: Un-Equips this actor from a owners character 
	//! @note: [U] Key Action ability
	void UnEquip(class AActor* OtherActor);




};
