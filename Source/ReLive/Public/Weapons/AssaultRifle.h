// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Character.h" 
#include "Engine/SkeletalMesh.h"
#include "Projectile/Ballistic.h" // Imported Class
#include "UObject/SoftObjectPath.h" 
#include "Engine/StreamableManager.h" 
#include "Engine/AssetManager.h" 
#include "Components/SphereComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "AssaultRifle.generated.h"

DECLARE_DELEGATE_OneParam(FInputEquipDelegate, class AActor* OtherActor);
DECLARE_DELEGATE_OneParam(FInputUnEquipDelegate, class AActor* OtherActor);
DECLARE_DELEGATE(FInputFireDelegate);
UCLASS()
class RELIVE_API AAssaultRifle : public AActor {
	GENERATED_BODY()

	UPROPERTY(VisibleDefaultsOnly, Category = Collision)
		class USphereComponent* CollisionSphere;


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Rifle, meta = (AllowPrivateAccess = "true"))
		class USkeletalMeshComponent* Gun;

public:
	//! @brief: Sets default values for this actor's properties
	//! @note: Loads static mesh visuals on component created
	//! @note: This class will typically be created when the player equips the weapon 
	AAssaultRifle();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//! @brief: Called when the main player overlaps this actor
	//! @note: Will add an action input binding
	UFUNCTION()
		void OnOverLapStart(class AActor* ThisActor, class AActor* OtherActor);


	//! @brief: Called when the main player has stoped overlaping this actor 
	//! @note: Will remove an action input binding equip
	UFUNCTION()
		void OnOverLapEnd(class AActor* ThisActor, class AActor* OtherActor);



private:

	//! @brief: Equips this actor to a character 
	//! @note: [E] Key that will add this actor to the players hand 
	void Equip(class AActor* OtherActor);

	//! @brief: Un-Equips this actor from a owners character 
	//! @note: [U] Key Action ability
	void UnEquip(class AActor* OtherActor);

	//! @brief: Shoots a projectile if a weapon is equiped 
	//! @note: [F] Key Action ability
	void Fire();


};
