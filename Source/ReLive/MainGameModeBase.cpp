// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameModeBase.h"

//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("StartPlay = TRUE"));//@Test

AMainGameModeBase::AMainGameModeBase() {
	Super::DefaultPawnClass = AMainCharacter::StaticClass(); // @Default - (DO NOT CHANGE)
	//Super::HUDClass = AHUD::StaticClass(); // @Default - (DO NOT CHANGE)
}



void AMainGameModeBase::StartPlay() {
	Super::StartPlay();



}