// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/InventorySystemComponent.h"
//#include "Weapons/AssaultRifle.h"
// Sets default values for this component's properties
UInventorySystemComponent::UInventorySystemComponent() {
	PrimaryComponentTick.bCanEverTick = false;

}


// Called when the game starts
void UInventorySystemComponent::BeginPlay() {
	Super::BeginPlay();
	if (Super::HasBegunPlay()) {
		class ACharacter* character = Cast<ACharacter>(GetOwner()); // Get the character who owns this component
		if (character != NULL) {
			class APlayerController* controller = Cast<APlayerController>(character->GetOwner());// Get The character's controller
			if (controller != NULL) {
				character->EnableInput(controller);	// Enable Input
				// [I] Key Action Binding Created 
				FInputActionBinding& inventoryBinding = character->InputComponent->BindAction<FInputInventoryDelegate>(TEXT("Inventory"), IE_Pressed, this, &UInventorySystemComponent::AddToInventory, character);
				// Consume the input
				inventoryBinding.bConsumeInput = false;

				// Message
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("[UInventorySystemComponent] OWNER = %s"), *character->GetName()));

				// [I] Key Action Binding Created 
				FInputActionBinding& toggleBinding = character->InputComponent->BindAction<FInputToggleDelegate>(TEXT("Toggle"), IE_Pressed, this, &UInventorySystemComponent::ToggleFromInventory, character);
				// Consume the input
				toggleBinding.bConsumeInput = false;
			}
		}
	}
}


void UInventorySystemComponent::AddToInventory(ACharacter* OtherActor) {
	if (OtherActor) {
		const class UActorComponent* CHILD = OtherActor->GetMesh()->GetChildComponent(0); // Get the attatched parent component | Example a weapon
		if (CHILD != NULL) {
			class AActor* item = Cast<AActor>(CHILD->GetOwner()); // Get the actor from the UActorComponent | could be a weapon, item, or a picked up object actor
			if (item != NULL) {
				// Add the item to the array	
				Inventory.Add(item);
				// Destroy the held item
				item->Destroy();
				// Message
				GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, FString::Printf(TEXT("Inventory Item Added = [%s]"), *item->GetName()));
				// @test
				/*for (AActor* a : Inventory) {
					GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Orange, FString::Printf(TEXT("OWNER = %s"), *a->GetName()));
				}*/
			}
		}
	}
}

void UInventorySystemComponent::ToggleFromInventory(ACharacter* OtherActor) {
	if (OtherActor && Inventory.Num() >= 1) {// Check if there are items in the inventory array
		class ACharacter* character = Cast<ACharacter>(OtherActor); // Get the character who owns this component
		if (character) {
			class APlayerController* controller = Cast<APlayerController>(character->GetOwner());// Get The character's controller
			if (controller) {
				const bool ONE_IS_PRESSED = controller->IsInputKeyDown(EKeys::One);
				const bool TWO_IS_PRESSED = controller->IsInputKeyDown(EKeys::Two);

				// [1] Pressed? 
				if (ONE_IS_PRESSED) {
					GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("[1] Key Pressed"));
					class UClass* pulled_item = Cast<UClass>(Inventory[0]->GetClass());// Get the class reference from the first actor in the array | TArray<AActor*> Inventory
					if (pulled_item != NULL) {
						// - (2) Spawn the new actor from the UClass 
						class AActor* inventory_item = GetWorld()->SpawnActor<AActor>(pulled_item);
						Inventory.RemoveAt(0);
						// ------------------------------ [NEXT UPDATE] ------------------------------
							// @note: attach the item to the character hands after the item is spawned make.
							//class ACharacter* player = Cast<ACharacter>(GetOwner()); // Get the character who owns this component
							//class USkeletalMeshComponent* mesh = player->GetMesh(); // Get character mesh reference
							//const FName HAND_R = TEXT("hand_r");// Bone Socket Name
							//inventory_item->SetOwner(player);
							//inventory_item->AttachToComponent(mesh, FAttachmentTransformRules::SnapToTargetIncludingScale, HAND_R);
							//inventory_item->SetActorRotation(FRotator(0.0f, 0.0f, -90.0f), ETeleportType::TeleportPhysics);
						//-----------------------------------------------------------------------------
					}
				}

				// [2] Pressed? 
				else if (TWO_IS_PRESSED) {
					if (Inventory.IsValidIndex(1)) {// - check if there are two items in the inventory
						GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("[2] Key Pressed"));
					}
				}

			}

		}
	}

}



// Called every frame
void UInventorySystemComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) {
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}
