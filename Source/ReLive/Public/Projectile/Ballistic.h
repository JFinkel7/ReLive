// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Ballistic.generated.h"

UCLASS()
class RELIVE_API ABallistic : public AActor {
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = StaticMesh, meta = (AllowPrivateAccess = "true"))
		class UStaticMeshComponent* Material;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Projectile, meta = (AllowPrivateAccess = "true"))
		class UProjectileMovementComponent* ProjectileMovement;

public:
	// Sets default values for this actor's properties
	ABallistic();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;



};
