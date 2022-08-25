// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h" // (REQUIRED)
#include "GameFramework/Actor.h" // (REQUIRED)
#include "Components/SphereComponent.h" 	 // (REQUIRED)
#include "Kismet/GameplayStatics.h" // (REQUIRED)
#include "GameFramework/ProjectileMovementComponent.h"  // (REQUIRED)
#include "BallisticProjectile.generated.h"

UCLASS()
class RELIVE_API ABallisticProjectile : public AActor{
	GENERATED_BODY()
		/** Sphere collision component **/
		UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Collision, meta = (AllowPrivateAccess = "true"))
		class USphereComponent* CollisionSphere;

	/** Statich mesh component **/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Mesh, meta = (AllowPrivateAccess = "true"))
		class UStaticMeshComponent* SphereVisual;

	/** Projectile movement component **/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Projectile, meta = (AllowPrivateAccess = "true"))
		class UProjectileMovementComponent* ProjectileMovement;


	
public:	
	// Sets default values for this actor's properties
	ABallisticProjectile();

	/** called when projectile hits something **/
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
