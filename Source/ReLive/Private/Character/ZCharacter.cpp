// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/ZCharacter.h"

// Sets default values
AZCharacter::AZCharacter() {
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// - [Pawn Sensory]
	PawnSensingComp = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensingComp"));
	PawnSensingComp->SetPeripheralVisionAngle(60.0f);
	PawnSensingComp->SightRadius = 2000;
	PawnSensingComp->HearingThreshold = 600;
	PawnSensingComp->LOSHearingThreshold = 1200;
	PawnSensingComp->SensingInterval = 3.0f;
	PawnSensingComp->bSeePawns = true;
	PawnSensingComp->bHearNoises = false;
	PawnSensingComp->bOnlySensePlayers = true; // Will Only Sense Players | Other Pawns
	PawnSensingComp->SetSensingUpdatesEnabled(true);

	// - [Capsule Collision]
	GetCapsuleComponent()->InitCapsuleSize(32.0f, 96.0f);//@Default 32.0f, 96.0f
	GetCapsuleComponent()->SetCollisionProfileName("Pawn"); // (DEFAULT) - Pawn 
	GetCapsuleComponent()->SetGenerateOverlapEvents(false); // Turn On for (Overlap Events)
	GetCapsuleComponent()->SetNotifyRigidBodyCollision(false);

	// - [Skeletal Mesh]

	GetMesh()->SetRelativeLocation(FVector(0.0f, 0.0f, -100.0f));
	GetMesh()->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));
	GetMesh()->AttachToComponent(GetCapsuleComponent(), FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	GetMesh()->SetCollisionProfileName("AI"); // (DEFAULT) - Enemy 
	GetMesh()->CanCharacterStepUpOn = ECB_No;
	GetMesh()->SetGenerateOverlapEvents(true); // Turn On for (Overlap Events)
	GetMesh()->SetNotifyRigidBodyCollision(false);


	// - [Movement Component]
	/* These values are matched up to the CapsuleComponent above and are used to find navigation paths */
	GetMovementComponent()->SetJumpAllowed(false);
	GetMovementComponent()->SetUpdateNavAgentWithOwnersCollisions(true);
	GetMovementComponent()->NavAgentProps.AgentRadius = 42;
	GetMovementComponent()->NavAgentProps.AgentHeight = 192;
}

// Called when the game starts or when spawned
void AZCharacter::BeginPlay() {
	Super::BeginPlay();
	if (PawnSensingComp) {
		PawnSensingComp->OnSeePawn.AddDynamic(this, &AZCharacter::OnSeePlayer);
	}
}


void AZCharacter::OnSeePlayer(APawn* OtherPawn) {
	if (OtherPawn) {
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("Z1 Sight Detection"));

	}
}


//void AZCharacter::EndPlay(const EEndPlayReason::Type EndPlayReason) {
//	Super::EndPlay(EndPlayReason);
//}

