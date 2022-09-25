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
		owner->OnTakeAnyDamage.AddDynamic(this, &UHealthSystemComponent::OnDamaged);
	}

}

// Called When Damaged
//================================================================================================================
void UHealthSystemComponent::OnDamaged(class AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, class AActor* DamageCauser) {
	if (DamagedActor != NULL) {
		_Health = (_Health > 0) ? (_Health -= Damage) : (_Health = 0);
		//if (_Health > 0) {
		//	_Health -= Damage;
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Purple, FString::Printf(TEXT("Health = %f"), _Health));
			//@test message
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Purple, FString::Printf(TEXT("Health Address = %d"), &_Health));
		//}
	}
}
