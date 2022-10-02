// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/AbilitySystemComponent.h"

// Sets default values for this component's properties
UAbilitySystemComponent::UAbilitySystemComponent() {
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	const class AActor* OWNER = GetOwner();
	if (OWNER) {
		//@note performance -> create component on teleport key event so the function variables can be destroyed;
		ParticleSystemComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ParticleSystemComponent"));
		ParticleSystemComponent->AttachToComponent(OWNER->GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform, FName(TEXT("spine_03")));
	}
}


// Called when the game starts
void UAbilitySystemComponent::BeginPlay() {
	Super::BeginPlay();
	// ...
	class ACharacter* character = Cast<ACharacter>(GetOwner()); // Get the character who owns this component
	if (character != NULL) {
		class APlayerController* controller = Cast<APlayerController>(character->GetOwner());// Get The character's controller
		if (controller != NULL) {
			character->EnableInput(controller);	// Enable Input
			// [T] Key Action Binding Created 
			FInputActionBinding& inventoryBinding = character->InputComponent->BindAction(TEXT("Ability"), IE_Pressed, this, &UAbilitySystemComponent::teleport);
			// Consume the input
			inventoryBinding.bConsumeInput = false;
		}
	}
}


//==================================================[ACTIONS]==================================================
void UAbilitySystemComponent::teleport() {
	// GET: Player's controller reference Who ever owns this Ability System Component
	class APlayerController* controller = Cast<APlayerController>(GetOwner()->GetOwner());
	if (controller) {
		// Check if Keyboard [1] Key || Playstation [L1+X] || XBox [LB + A] is Pressed 
		if (controller->IsInputKeyDown(EKeys::One)) {
			// GET: Player's Current Location 
			const FVector CURRENT_LOCATION = (GetOwner()->GetActorForwardVector() * 750.0f) + GetOwner()->GetActorLocation();
			// GET: Player's  Current Rotation 
			const FRotator CURRENT_ROTATION = GetOwner()->GetActorRotation();
			// Teleport Player
			GetOwner()->TeleportTo(CURRENT_LOCATION, CURRENT_ROTATION, false, true);
			if (ParticleSystemComponent != NULL) {
				// Load Asset When The Game Starts
				class UParticleSystem* particle = LoadObject<UParticleSystem>(nullptr, TEXT("/Game/RPGEffects/Particles/P_Status_Teleport_Burst.P_Status_Teleport_Burst"));
				if (particle != NULL) {
					// Activate the particle or FX system
					ParticleSystemComponent->SetTemplate(particle);
					// Message
					GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Teleport = TRUE"));
				}
			}
		}
	}
}