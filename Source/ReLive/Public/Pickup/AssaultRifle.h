// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h" // (REQUIRED)
#include "GameFramework/Actor.h" // (REQUIRED)
#include "GameFramework/Character.h" // (REQUIRED)
#include "Engine/SkeletalMeshSocket.h" // (REQUIRED)
#include "UObject/SoftObjectPath.h"
#include "Engine/StreamableManager.h"
#include "Engine/AssetManager.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "DrawDebugHelpers.h"
#include "Components/SkeletalMeshComponent.h" // Rifle Skeletal Mesh (REQUIRED)
#include "AssaultRifle.generated.h"

UCLASS()
class RELIVE_API AAssaultRifle : public AActor {
	GENERATED_BODY()

		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Rifle, meta = (AllowPrivateAccess = "true"))
		class UStaticMeshComponent* StaticMeshComponent;

public:
	//! @brief: Sets default values for this actor's properties
	//! @note: Loads static mesh visuals on component created
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
	void Equip();

	//! @brief: Un-Equips this actor from a character 
	void UnEquip();

public:
	//! @brief: Called every frame
	virtual void Tick(float DeltaTime) override;

};


