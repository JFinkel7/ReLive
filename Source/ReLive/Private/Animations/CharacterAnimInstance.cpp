// Fill out your copyright notice in the Description page of Project Settings.


#include "Animations/CharacterAnimInstance.h"

void UCharacterAnimInstance::NativeUpdateAnimation(float DeltaSeconds) {
    Super::NativeUpdateAnimation(DeltaSeconds);
    const class APawn* OWNER = Super::TryGetPawnOwner();
    if (OWNER != NULL) {
        //Update our falling property
        IsFalling = OWNER->GetMovementComponent()->IsFalling();

        //Update our movement speed
        Speed = OWNER->GetVelocity().Size();
        const FRotator roatation = OWNER->GetActorRotation();
        Direction = UKismetAnimationLibrary::CalculateDirection((FVector)Speed, roatation);
    }
}