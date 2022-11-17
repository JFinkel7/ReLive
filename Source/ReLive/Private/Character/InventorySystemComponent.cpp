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
				FInputActionBinding& inventoryBinding = character->InputComponent->BindAction<FInputAddInventoryDelegate>(TEXT("Inventory"), IE_Pressed, this, &UInventorySystemComponent::AddToInventory, character);
				// Consume the input
				inventoryBinding.bConsumeInput = false;

				// Message
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("[UInventorySystemComponent] OWNER = %s"), *character->GetName()));

				// [I] Key Action Binding Created 
				FInputActionBinding& toggleBinding = character->InputComponent->BindAction<FInputToggleInventoryDelegate>(TEXT("Toggle"), IE_Pressed, this, &UInventorySystemComponent::ToggleFromInventory, character);
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
				Inventory.Add(item);// Add the item to the array			
				item->Destroy();// Destroy the held item
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
	// Check if there > 1 items in the inventory array
	if (OtherActor && Inventory.Num() >= 1) {
		// Get the character who owns this component
		class ACharacter* character = Cast<ACharacter>(OtherActor);
		if (character) {
			class APlayerController* controller = Cast<APlayerController>(character->GetOwner());// Get The character's controller
			// Check if the player controller is Valid
			if (controller) {
				// [Shift] + [1] Pressed? 
				if (controller->IsInputKeyDown(EKeys::LeftShift) && controller->IsInputKeyDown(EKeys::One)) {
					//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, TEXT("[1] Key Pressed"));
					class UClass* pulled_item = Cast<UClass>(Inventory[0]->GetClass());// Get the class reference from the first actor in the array | TArray<AActor*> Inventory
					if (pulled_item != NULL) {
						// - (2) Spawn the new actor from the UClass 				
						class AActor* inventory_item = GetWorld()->SpawnActor<AActor>(pulled_item, character->GetActorLocation(), character->GetActorRotation());
						// Remove The Item From The Inventory
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
				else if (controller->IsInputKeyDown(EKeys::LeftShift) && controller->IsInputKeyDown(EKeys::Two)) {
					if (Inventory.IsValidIndex(1)) {// - check if there are two items in the inventory
						GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("[2] Key Pressed"));
					}
				}

			}

		}
	}

}


#include "Components/HorizontalBox.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h" 
// [Tab] Key
void UInventorySystemComponent::ShowInventory(){
	// Set Path 
	const FString PATH = "/Game/InventoryWidget.InventoryWidget_C";
	// Set Owner
	class ACharacter* OWNER = Cast<ACharacter>(GetOwner()); // Get the character who owns this component
	// Load The BP 
	TSubclassOf<UUserWidget> InventoryWidgetBP = LoadClass<UUserWidget>(GetWorld(), *PATH);
	
	if (InventoryWidgetBP) {
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, TEXT("InventoryWidgetBP = TRUE"));
		//class UTextBlock* TextBlock_1 = CreateWidget<UTextBlock>(OWNER->GetController(), InventoryWidgetBP);
		//if (TextBlock_1 != NULL) {
			//TextBlock_1->SetText(FText::FromString("TEST!"));
			//InventoryWidgetBP->AddToV
		//}
	
	}
}



