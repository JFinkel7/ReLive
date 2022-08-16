// Fill out your copyright notice in the Description page of Project Settings.


#include "Animations/MainCharacterAnimInstance.h"

void UMainCharacterAnimInstance::NativeUpdateAnimation(float DeltaSeconds) {
    Super::NativeUpdateAnimation(DeltaSeconds);
    const class APawn* HOST = Super::TryGetPawnOwner();
    if (HOST != NULL) {
        //Update our falling property
        IsFalling = HOST->GetMovementComponent()->IsFalling();

        //Update our movement speed
        Speed = HOST->GetVelocity().Size();
        const FRotator roatation = HOST->GetActorRotation();
        Direction = UKismetAnimationLibrary::CalculateDirection((FVector)Speed, roatation);
    }
}