// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Character/MainCharacter.h" // (REQUIRED)
#include "Weapons/AssaultRifle.h" // (ADDED)
#include "MainGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class RELIVE_API AMainGameModeBase : public AGameModeBase{
	GENERATED_BODY()


public:
	AMainGameModeBase();


	//! @brief: start play is called when the game is called
	//! @note: when the game starts it will spawn a rifle 
	virtual void StartPlay() override;
	
	
};
