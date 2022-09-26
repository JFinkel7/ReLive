// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"  // (REQUIRED)
#include "Animation/AnimInstance.h"  // (REQUIRED)
#include "KismetAnimationLibrary.h" // (REQUIRED)
#include "GameFramework/Character.h"// new
#include "AIController.h"// new
#include "GameFramework/PawnMovementComponent.h"  // (REQUIRED)
#include "CharacterAnimInstance.generated.h"

/**
 * 
 */

UCLASS()
class RELIVE_API UCharacterAnimInstance : public UAnimInstance{
	GENERATED_BODY()


protected:
	//! @brief: Updates Animation | Equal to Tick() Method
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	//! @brief: Executed when begin play is called on the owning component.
	virtual void NativeBeginPlay() override;

	//! @brief: Triggered by Pawn Taking Damage | Damage Event
	UFUNCTION()
		void OnAnyDamaged(class AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, class AActor* DamageCauser);

protected:
	//! @brief: Holds the current speed of our character
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Speed;

	//! @brief: Holds the current direction of our character
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Direction;

	//! @brief: True = Currently in Air or Falling
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool IsFalling;

	//! @brief: True = Owner Is destroyed and removed from the game 
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool IsDead;


private:
	float _Health;

	////! @brief: True = Currently started to jump
	//UPROPERTY(EditAnywhere, BlueprintReadOnly)
	//	bool IsJumping;



	////! @brief: True = Currently is Crouching
	//UPROPERTY(EditAnywhere, BlueprintReadOnly)
	//	bool IsCrouching;
	
};
