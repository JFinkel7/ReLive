// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "GameFramework/CharacterMovementComponent.h"  // (REQUIRED)
#include "GameFramework/SpringArmComponent.h" // (REQUIRED)
#include "Camera/CameraComponent.h" // (REQUIRED)
#include "GameFramework/Controller.h"  // (REQUIRED)
#include "Components/CapsuleComponent.h" // (REQUIRED)
#include "Components/ArrowComponent.h" // (REQUIRED)
#include "Components/InputComponent.h" // (REQUIRED)
#include "UObject/SoftObjectPath.h" // (REQUIRED)
#include "Engine/StreamableManager.h" // (REQUIRED)
#include "Engine/AssetManager.h" // (REQUIRED)
#include "DrawDebugHelpers.h"
//----------------------
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
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


public:
	//! @brief: Sets default values for this character's properties
	AMainCharacter();

protected:
	//! @brief: Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	//! @brief: Called every frame
	virtual void Tick(float DeltaTime) override;

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


private:
	//! @brief: Teleports the player 750m in the direction he is facing 
	//! @note: Action ability
	void teleport();

};
