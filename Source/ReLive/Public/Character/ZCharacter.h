// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/CapsuleComponent.h" 
#include "Perception/PawnSensingComponent.h" 
#include "GameFramework/PawnMovementComponent.h" 
#include "Components/PrimitiveComponent.h"
#include "Character/AISystemsController.h" 
#include "ZCharacter.generated.h"

UCLASS()
class RELIVE_API AZCharacter : public ACharacter {
	GENERATED_BODY()

	//! @brief: Pawn Sensory Component that will sense other Pawns
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = AI, meta = (AllowPrivateAccess = "true"))
		class UPawnSensingComponent* PawnSensingComp;

	//! @brief: Health System Component that will sense damage 
	//UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = AI, meta = (AllowPrivateAccess = "true"))
		//class UHealthSystemComponent* DamageSensingComp;

public:
	//! @brief: Sets default values for this character's properties
	AZCharacter();

protected:
	//! @brief: Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//! @brief: Function called whenever this actor is being removed from a level
    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason);

	//! @brief: Triggered if this character spots a pawn 
	UFUNCTION()
		void OnSeePlayer(class APawn* OtherPawn);

};
