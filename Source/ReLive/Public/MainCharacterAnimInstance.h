// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "GameFramework/PawnMovementComponent.h"
#include "MainCharacterAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class RELIVE_API UMainCharacterAnimInstance : public UAnimInstance{
	GENERATED_BODY()


protected:
	//! @brief: Updates Animation | Equal to Tick() Method
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

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

	////! @brief: True = Currently started to jump
	//UPROPERTY(EditAnywhere, BlueprintReadOnly)
	//	bool IsJumping;



	////! @brief: True = Currently is Crouching
	//UPROPERTY(EditAnywhere, BlueprintReadOnly)
	//	bool IsCrouching;
	
};
