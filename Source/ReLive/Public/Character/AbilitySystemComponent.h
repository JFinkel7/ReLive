// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameFramework/Character.h"
#include "Particles/ParticleSystemComponent.h" // New 
#include "AbilitySystemComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class RELIVE_API UAbilitySystemComponent : public UActorComponent{
	GENERATED_BODY()
		//! @brief: Particle Effect
		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UParticleSystemComponent* ParticleSystemComponent;
public:	
	// Sets default values for this component's properties
	UAbilitySystemComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;


private:
	//! @brief: Teleports the player
	//! @note: [T] Action Key
	void teleport();

		
};
