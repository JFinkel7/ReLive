// Fill out your copyright notice in the Description page of Project Settings.

#include "Character/HealthSystemComponent.h"



// Sets default values for this component's properties
UHealthSystemComponent::UHealthSystemComponent() {
	PrimaryComponentTick.bCanEverTick = false; // Turn Off to Improve performance if you don't need them.
	_Health = 100.0f;

	//@test message
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("[UHealthSystemComponent] Working = TRUE"));
}


void UHealthSystemComponent::BeginPlay() {
	Super::BeginPlay();
	class AActor* owner = GetOwner();
	if (owner != NULL) {
		// Register On Take Any Damage Event
		//owner->OnTakeAnyDamage.AddDynamic(this, &UHealthSystemComponent::OnDamaged);
		// Register On Destroyed Event
		//owner->OnDestroyed.AddDynamic(this, &UCharacterAnimInstance::OnOwnerDestroyed);
		
	}

}

// Called When Damaged
//================================================================================================================
void UHealthSystemComponent::OnAnyDamaged(class AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, class AActor* DamageCauser) {
	if (DamagedActor != NULL) {
		_Health = (_Health > 0) ? (_Health -= Damage) : (_Health = 0);
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Purple, FString::Printf(TEXT("Health = %f"), _Health));
		if (_Health == 0) {// Destroy the actor when his health is 0  
			class AActor* owner = GetOwner();
			if (owner != NULL) {
				owner->Destroy();
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, TEXT("OWNER IS ABOUT TO DIE"));
			
			}
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Purple, FString::Printf(TEXT("Health System Owner = %s"), *owner->GetName()));
		}
		
	}
}

void UHealthSystemComponent::OnOwnerDestroyed(AActor* Owner){
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("OWNER IS DESTROYED"));
}
