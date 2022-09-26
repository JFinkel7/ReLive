// Fill out your copyright notice in the Description page of Project Settings.


#include "Animations/CharacterAnimInstance.h"

void UCharacterAnimInstance::NativeUpdateAnimation(float DeltaSeconds) {
	Super::NativeUpdateAnimation(DeltaSeconds);
	class APawn* OWNER = Super::TryGetPawnOwner();
	if (OWNER != NULL) {
		//Update our falling property
		//IsFalling = OWNER->GetMovementComponent()->IsFalling();
		//Update our movement speed
		Speed = OWNER->GetVelocity().Size();
		const FRotator roatation = OWNER->GetActorRotation();
		Direction = UKismetAnimationLibrary::CalculateDirection((FVector)Speed, roatation);
	}
}

void UCharacterAnimInstance::NativeBeginPlay() {
	class APawn* OWNER = Super::TryGetPawnOwner();
	if (OWNER != NULL) {
		_Health = 100.0f;

		// Register On Take Any Damage Event
		OWNER->OnTakeAnyDamage.AddDynamic(this, &UCharacterAnimInstance::OnAnyDamaged);

		//struct FAnimMontageInstance * montage = GetActiveMontageInstance();	
	}

}

void UCharacterAnimInstance::OnAnyDamaged(class AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, class AActor* DamageCauser) {
	if (DamagedActor != NULL) {
		// Get The Current Health Status 
		_Health = (_Health > 0) ? (_Health -= Damage) : (_Health = 0);
		// If health is 0
		if (_Health == 0) {
			// Set the owner to be dead 
			IsDead = true;
			// Get The Pawn Owner
			if (TryGetPawnOwner() != NULL) {
				class AController* OwnerController = Cast<AController>(TryGetPawnOwner()->GetController());
				if (OwnerController) {
					//TryGetPawnOwner()->GetMovementComponent()->StopActiveMovement();// Stop the owner's movement
					TryGetPawnOwner()->GetController()->StopMovement();
					TryGetPawnOwner()->GetController()->UnPossess();// Un-Posses the owner
					TryGetPawnOwner()->SetLifeSpan(2.5f); // Owner will Destroy in 3 seconds. 
					TryGetPawnOwner()->ClearGarbage();
					//@test message
					GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("DEAD"));
				}
			}
		}

		//@test Message
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, FString::Printf(TEXT("Health = %f"), _Health));
	}

}

