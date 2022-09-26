// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "Components/ActorComponent.h" 		     
#include "GameFramework/Controller.h"
#include "GameFramework/Character.h"
#include "Engine/World.h"
#include "CoreMinimal.h"            
#include "HealthSystemComponent.generated.h" 

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class RELIVE_API UHealthSystemComponent : public UActorComponent {
    GENERATED_BODY()

public:
    //! @brief: Sets Default Values
    UHealthSystemComponent();

    //! @brief: Triggered by Pawn Taking Damage | Damage Event
    UFUNCTION()
    void OnAnyDamaged(class AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, class AActor* DamageCauser);

    //! @brief: Event that will activate once the owner is destroyed
    UFUNCTION()
   void OnOwnerDestroyed(class AActor* Owner);

protected:
    //! @brief: Called When Game Starts
    virtual void BeginPlay() override;

private:
    float _Health;
    float _Stamina;
    float _Armor;
};
