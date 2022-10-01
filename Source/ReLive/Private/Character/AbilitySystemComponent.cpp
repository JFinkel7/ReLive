// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/AbilitySystemComponent.h"

// Sets default values for this component's properties
UAbilitySystemComponent::UAbilitySystemComponent() {
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	const class AActor* OWNER = GetOwner();
	if (OWNER) {
		ParticleSystemComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ParticleSystemComponent"));
		ParticleSystemComponent->AttachToComponent(OWNER->GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform, FName(TEXT("spine_03")));
	}
}


// Called when the game starts
void UAbilitySystemComponent::BeginPlay() {
	Super::BeginPlay();
	// ...

}



void UAbilitySystemComponent::teleport() {
	//	PlayerInputComponent->BindAction("Teleport", IE_Pressed, this, &AMainCharacter::teleport);
	const FVector CURRENT_LOCATION = (GetOwner()->GetActorForwardVector() * 750.0f) + GetOwner()->GetActorLocation();
	const FRotator CURRENT_ROTATION = GetOwner()->GetActorRotation();
	GetOwner()->TeleportTo(CURRENT_LOCATION, CURRENT_ROTATION, false, true);
	if (ParticleSystemComponent != NULL) {
		// Load Asset When The Game Starts
		class UParticleSystem* particle = LoadObject<UParticleSystem>(nullptr, TEXT("/Game/RPGEffects/Particles/P_Status_Teleport_Burst.P_Status_Teleport_Burst"));
		if (particle != NULL) {
			ParticleSystemComponent->SetTemplate(particle);
		}
	}
}