// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h" // (REQUIRED)
#include "GameFramework/Actor.h" // (REQUIRED)
#include "GameFramework/Character.h" // (REQUIRED)
#include "Engine/SkeletalMeshSocket.h" 
#include "DrawDebugHelpers.h" // (REQUIRED) 
#include "Components/SkeletalMeshComponent.h" 
#include "Weapons/AssaultRifleWeapon.h" // (REQUIRED) - To Spawn The Weapon
#include "AssaultRifle.generated.h"



DECLARE_DELEGATE_OneParam(FInputPickupDelegate, class AActor* OtherActor);

UCLASS()
class RELIVE_API AAssaultRifle : public AActor {
	GENERATED_BODY()

		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Rifle, meta = (AllowPrivateAccess = "true"))
		class UStaticMeshComponent* StaticMeshComponent;

public:
	//! @brief: Sets default values for this actor's properties
	//! @note: Loads static mesh visuals on component created
	//! @note: Equip System 1.00
	//! @note: Equip System 1.00 could be further expanded with using a re-usable component (UWeaponEquipSystem)
	AAssaultRifle();

protected:
	//! @brief: Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//! @brief: Called when the main player overlaps this actor
	//! @note: Will add an action input binding
	UFUNCTION()
		void OnOverLapStart(class AActor* ThisActor, class AActor* OtherActor);

	//! @brief: Called when the main player has stoped overlaping this actor 
	//! @note: Will remove an action input binding equip
	UFUNCTION()
		void OnOverLapEnd(class AActor* ThisActor, class AActor* OtherActor);

	//! @brief: Equips this actor to a character 
	//! @note: Spawns The Weapon to the player's hand
	void Equip(class AActor* OtherActor);




public:
	//! @brief: Called every frame
	virtual void Tick(float DeltaTime) override;



};


