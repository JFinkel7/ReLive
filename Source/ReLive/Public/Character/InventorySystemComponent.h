// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Character.h"
#include "InventorySystemComponent.generated.h"

DECLARE_DELEGATE_OneParam(FInputAddInventoryDelegate, class ACharacter* OtherActor);
DECLARE_DELEGATE_OneParam(FInputToggleInventoryDelegate,    class ACharacter* OtherActor);
DECLARE_DELEGATE(FInputShowInventoryDelegate);
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class RELIVE_API UInventorySystemComponent : public UActorComponent{
	GENERATED_BODY()

public:	
	//! @brief: Sets default values for this component's properties
	UInventorySystemComponent();

protected:
	//! @brief: Called when the game starts or when attached to the an actor 
	virtual void BeginPlay() override;

private:
	//! @brief: Adds Item to an array
	//! @note: [I] Action Key
	//! @ref: FInputAddInventoryDelegate
	void AddToInventory(class ACharacter* OtherActor);


	//! @brief: Adds Item to an array
	//! @note: [Left Shift] + [1] Action Key 
	//! @ref: FInputToggleInventoryDelegate
	void ToggleFromInventory(class ACharacter* OtherActor);

	//! @brief: Adds Item to an array
	//! @note: [Left Shift] + [M] Action Key 
	//! @ref: FInputShowInventoryDelegate 
	void ShowInventory();

	//! @brief: Collection of actors
	TArray<AActor*> Inventory;


	
	
		
};
