// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameModeBase.h"

//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("StartPlay = TRUE"));//@Test

AMainGameModeBase::AMainGameModeBase() {
	Super::DefaultPawnClass = AMainCharacter::StaticClass(); // @Default - (DO NOT CHANGE)
	//Super::HUDClass = AHUD::StaticClass(); // @Default - (DO NOT CHANGE)
}



void AMainGameModeBase::StartPlay() {
	Super::StartPlay();

	UWorld* const GAME_WORLD = Super::GetWorld();

	if (GAME_WORLD != NULL)
		GAME_WORLD->SpawnActor<AAssaultRifle>(FVector(0, 0, 0), FRotator(0, 0, 0)); // - Spawn AssaultRifle to the center of the map


}