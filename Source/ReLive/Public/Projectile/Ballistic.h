// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Ballistic.generated.h"

UCLASS()
class RELIVE_API ABallistic : public AActor {
	GENERATED_BODY()

	//! @brief: Ballistic Static Mesh Component
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = StaticMesh, meta = (AllowPrivateAccess = "true"))
		class UStaticMeshComponent* Material;
	
	//! @brief: Ballistic Projectile Movement Component
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Projectile, meta = (AllowPrivateAccess = "true"))
		class UProjectileMovementComponent* ProjectileMovement;

public:
	//! @brief: Sets default values for this actor's properties
	ABallistic();

	//! @brief: Listener event that will detect if this actor hit an object. 
	UFUNCTION()
	void OnHit(AActor* ThisActor, AActor* HitActor, FVector NormalImpulse, const FHitResult& HitInfo);

protected:
	//! @brief: Called when the game starts or when spawned
	virtual void BeginPlay() override;



};
