// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameModeBase.h"


AMainGameModeBase::AMainGameModeBase() {
    Super::DefaultPawnClass = AMainCharacter::StaticClass(); // @Default - (DO NOT CHANGE)
    //Super::HUDClass = AHUD::StaticClass(); // @Default - (DO NOT CHANGE)
}
