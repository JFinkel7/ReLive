// Fill out your copyright notice in the Description page of Project Settings.


#include "EquipSystemComponent.h"

UEquipSystemComponent::UEquipSystemComponent() {

}


void UEquipSystemComponent::BeginPlay() {
	Super::OnComponentBeginOverlap.AddDynamic(this, &UEquipSystemComponent::OnOverlapBegin);
	Super::OnComponentEndOverlap.AddDynamic(this, &UEquipSystemComponent::OnOverlapEnd);
}

void UEquipSystemComponent::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	if (OtherActor != NULL) {
		// Message
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("[Overlapped] Started: %s"), *OtherActor->GetName()));
		class APlayerController* Controller = Cast<APlayerController>(OtherActor->GetOwner());
		if (Controller != NULL) {
			OtherActor->EnableInput(Controller);// Enable Input 
			FInputActionBinding& binding = OtherActor->InputComponent->BindAction<FInputEquipSecondaryDelegate>(TEXT("Equip"), IE_Pressed, this, &UEquipSystemComponent::Equip, OtherActor);// [E] Key Action Binding Created 
			binding.bConsumeInput = true;
			GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, TEXT("Enter [E] To Equip This Weapon"));
		}
	}
}

void UEquipSystemComponent::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) {
	if (OtherActor != NULL) {
		if (OtherActor->InputComponent->HasBindings()) {// Check if this actor has any bindings  
			// [E] key action binding removed 
			OtherActor->InputComponent->RemoveActionBinding(FName(TEXT("Equip")), EInputEvent::IE_Pressed);// Removes "Equip" Input Binding Key
			//@test message
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("[Overlapped] Ended: %s"), *OtherActor->GetName()));
		}

	}

}




void UEquipSystemComponent::Equip(class AActor* OtherActor) {
	const class ACharacter* CHARACTER = Cast<ACharacter>(OtherActor);// Get character who equiped this actor  
	if (CHARACTER != NULL) {
		class USkeletalMeshComponent* mesh = CHARACTER->GetMesh(); // Get character mesh reference 
		if (mesh != NULL) {
			const FName SOCKET = TEXT("hand_r");// Bone Socket Name 
			const FRotator DIRECTION_OF_PLAYER = mesh->GetComponentRotation();
			Super::AttachToComponent(mesh, FAttachmentTransformRules::SnapToTargetIncludingScale, SOCKET);
			GetOwner()->SetActorRotation(DIRECTION_OF_PLAYER, ETeleportType::TeleportPhysics);
			if (OtherActor->InputComponent->HasBindings()) {// Check if this actor has any bindings  
				// (OFF)  Overlap Events
				Super::SetGenerateOverlapEvents(false);
				// [E] key action binding removed 
				OtherActor->InputComponent->RemoveActionBinding(FName(TEXT("Equip")), EInputEvent::IE_Pressed);

				CanFire = true;

				// [U] Key Action Binding Created 
				struct FInputActionBinding& bindOnUnEquip = OtherActor->InputComponent->BindAction<FInputUnEquipSecondaryDelegate>(TEXT("UnEquip"), IE_Pressed, this, &UEquipSystemComponent::UnEquip, OtherActor);
				// Message
				GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Weapon Equiped"));
			}
		}
	}
}



void UEquipSystemComponent::UnEquip(class AActor* OtherActor) {
	class APlayerController* Controller = Cast<APlayerController>(OtherActor->GetOwner());
	if (Controller != NULL) {
		GetOwner()->DetachFromActor(FDetachmentTransformRules::KeepRelativeTransform);// Detach this actor from the character 
		const FVector BONE_LOCATION = Controller->GetCharacter()->GetMesh()->GetBoneLocation(FName(TEXT("hand_r")), EBoneSpaces::Type::WorldSpace);
		GetOwner()->SetActorLocation(BONE_LOCATION);//  Set this actor near the character  
		Super::SetGenerateOverlapEvents(true); // (ON) Overlap Events 

		if (OtherActor->InputComponent->HasBindings()) {// Check if this actor has any bindings  
			// [U] Key action binding removed
			OtherActor->InputComponent->RemoveActionBinding(FName(TEXT("UnEquip")), EInputEvent::IE_Pressed);
			CanFire = false;
			// Message
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Weapon Dropped"));
			// To Be Continued.... 
			// NEXT I detatch and set this actor to the original location 
		}
	}
}


