// Fill out your copyright notice in the Description page of Project Settings.
#include "Pickup/AssaultRifle.h"


AAssaultRifle::AAssaultRifle() {
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SkeletalMesh"));
	StaticMeshComponent->SetCollisionProfileName("Pickup"); // Make sure to ignore players camera from the collision settings 	StaticMeshComponent->SetGenerateOverlapEvents(true); // Turn ON (Overlap Events)
	StaticMeshComponent->SetNotifyRigidBodyCollision(false);
	static ConstructorHelpers::FObjectFinder<UStaticMesh>mesh(TEXT("/Game/Weapons/Rifle/Assault_Rifle_SM.Assault_Rifle_SM"));
	if (mesh.Succeeded()) {
		StaticMeshComponent->SetStaticMesh(mesh.Object);
		RootComponent = StaticMeshComponent;
	}

}

void AAssaultRifle::OnOverLapStart(class AActor* ThisActor, class AActor* OtherActor) {
	if (OtherActor && (OtherActor != this)) {
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, TEXT("Enter [E] Equip This Item")); // Message hint to equip the pickup  
		class ACharacter* Character = Cast<ACharacter>(OtherActor);// @redundant 

		if (Character != NULL) {
			class APlayerController* Controller = Cast<APlayerController>(OtherActor->GetOwner());

			if (Controller != NULL) {
				Super::EnableInput(Controller);
				FInputActionBinding binding = Super::InputComponent->BindAction<FInputPickupDelegate>(TEXT("Equip"), IE_Pressed, this, &AAssaultRifle::Equip, OtherActor);
				binding.bConsumeInput = true;
			}
		}
	}
}





void AAssaultRifle::OnOverLapEnd(AActor* ThisActor, AActor* OtherActor) {
	if (OtherActor && (OtherActor != this)) {
		class APlayerController* Controller = Cast<APlayerController>(OtherActor->GetOwner());
		if (Controller != NULL)
			if (Super::InputComponent->HasBindings()) {
				Super::InputComponent->RemoveActionBinding(FName(TEXT("Equip")), EInputEvent::IE_Pressed);// Removes "Equip" Input Binding Key
			}
	}
}

//==================================================[ACTIONS]==================================================

void AAssaultRifle::Equip(class AActor* OtherActor) {
	const class ACharacter* CHARACTER = Cast<ACharacter>(OtherActor);// OtherActor->GetOwner() Gets The Character Reference
	if (CHARACTER != NULL) {
		struct FActorSpawnParameters spawnparams;	
		spawnparams.Owner = CHARACTER->GetOwner(); // Gets the PlayerController Reference | this helps me get references in other classes
		class AAssaultRifleWeapon* weapon = GetWorld()->SpawnActor<AAssaultRifleWeapon>(spawnparams); // Spawning the weapon 
		if (weapon != NULL) {
			USkeletalMeshComponent* characterMesh = CHARACTER->GetMesh();
			if (characterMesh != NULL) {
				const FName SOCKET = TEXT("hand_r");//  Right Hand
				weapon->AttachToComponent(characterMesh, FAttachmentTransformRules::SnapToTargetIncludingScale, SOCKET);
				weapon->SetActorRotation(FRotator(0.0f, 0.0f, -90.0f), ETeleportType::TeleportPhysics);
				GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, TEXT("WEAPON EQUIPED SUCCESSFULLY"));
				Super::Destroy(); // - Destroy AAssaultRifle pickup class  
			}
		}
	}

}





// Called when the game starts or when spawned
void AAssaultRifle::BeginPlay() {
	Super::BeginPlay();
	OnActorBeginOverlap.AddDynamic(this, &AAssaultRifle::OnOverLapStart);
	OnActorEndOverlap.AddDynamic(this, &AAssaultRifle::OnOverLapEnd);

}







// Called every frame
void AAssaultRifle::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
}

