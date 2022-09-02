// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Character.h" // (REQUIRED)
#include "AssaultRifleWeapon.generated.h"

DECLARE_DELEGATE(FInputFireDelegate);
DECLARE_DELEGATE(FInputUnEquipDelegate);
UCLASS()
class RELIVE_API AAssaultRifleWeapon : public AActor {
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Rifle, meta = (AllowPrivateAccess = "true"))
		class UStaticMeshComponent* WeaponMeshComponent;

	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Projectile, meta = (AllowPrivateAccess = "true"))
	//	class UStaticMeshComponent* BulletProjectileMeshComponent;

public:
	//! @brief: Sets default values for this actor's properties
	//! @note: Loads static mesh visuals on component created
	//! @note: This class will typically be created when the player equips the weapon 
	AAssaultRifleWeapon();

protected:

	// Called Before Begin Play 
	virtual void PostInitializeComponents() override;


	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	//! @brief: Shoots a projectile if a weapon is equiped 
	//! @note: [F] Key Action ability
	void Fire();

	//! @brief: Un-Equips this actor from a owners character 
	//! @note: [U] Key Action ability
	void UnEquip();


public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
