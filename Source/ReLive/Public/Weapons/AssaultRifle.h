// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "UObject/SoftObjectPath.h"
#include "Engine/StreamableManager.h"
#include "Engine/AssetManager.h"
#include "DrawDebugHelpers.h"
#include "Components/SkeletalMeshComponent.h" // Rifle Skeletal Mesh (REQUIRED)
#include "AssaultRifle.generated.h"

UCLASS()
class RELIVE_API AAssaultRifle : public AActor {
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Rifle, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* StaticMeshComponent;

public:
	// Sets default values for this actor's properties
	AAssaultRifle();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnOverLapStart(class AActor* ThisActor, class AActor* OtherActor);

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
