// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Character.h"
#include "InventorySystemComponent.generated.h"

DECLARE_DELEGATE_OneParam(FInputInventoryDelegate, class ACharacter* OtherActor);
DECLARE_DELEGATE_OneParam(FInputToggleDelegate,    class ACharacter* OtherActor);
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class RELIVE_API UInventorySystemComponent : public UActorComponent{
	GENERATED_BODY()

public:	
	//! @brief: Sets default values for this component's properties
	UInventorySystemComponent();

protected:
	//! @brief: Called when the game starts or when attached to the an actor 
	virtual void BeginPlay() override;

public:	
	//! @brief: Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


private:
	//! @brief: Adds Item to an array
	//! @note:  [I] Action Key
	void AddToInventory(class ACharacter* OtherActor);


	//! @brief: Adds Item to an array
	//! @note: [Shift] + [T] Action Key 
	void ToggleFromInventory(class ACharacter* OtherActor);

	//! @brief: Collection of actors
	TArray<AActor*> Inventory;


	
	
		
};
