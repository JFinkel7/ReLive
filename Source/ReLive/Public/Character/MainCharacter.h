// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Particles/ParticleSystemComponent.h" // New 
#include "Character/AimSystemComponent.h" 
#include "Components/CapsuleComponent.h" 
#include "Components/ArrowComponent.h" 
#include "GameFramework/Controller.h" 
#include "Components/InputComponent.h" 
#include "Engine/StreamableManager.h" 
#include "UObject/SoftObjectPath.h" 
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h" 
#include "Engine/AssetManager.h" 
#include "DrawDebugHelpers.h"
#include "CoreMinimal.h"
#include "MainCharacter.generated.h"


UCLASS()
class RELIVE_API AMainCharacter : public ACharacter {
	GENERATED_BODY()

	//! @brief: Camera boom positioning the camera behind the character	(pulls in towards the player if there is a collision)
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* CameraBoom;

	//! @brief: Create a Follow Camera
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* FollowCamera;

	//! @brief: Create a Crosshair UI 
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UAimSystemComponent* CrosshairWidget;

public:
	//! @brief: Sets default values for this character's properties
	AMainCharacter();

protected:
	//! @brief: Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:

	//! @brief: Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	//! @brief: Sets Up Our Controller Input
	void moveForward(float Val);

	//! @brief: Handles stafing movement, left and right
	void moveRight(float Val);

	//! @brief: Called via input to turn at a given rate
	//! @param: (Rate) This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	//! @note: Calculate delta for this frame from the rate information
	void turnRate(float Rate);

	//! @brief: Called via input to turn look up/down at a given rate
	//! @param: (Rate) This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	//! @note: Calculate delta for this frame from the rate information
	void lookUpRate(float Rate);

};
