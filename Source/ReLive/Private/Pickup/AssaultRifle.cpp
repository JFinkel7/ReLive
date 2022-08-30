// Fill out your copyright notice in the Description page of Project Settings.
#include "Pickup/AssaultRifle.h"


AAssaultRifle::AAssaultRifle() {
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SkeletalMesh"));
	StaticMeshComponent->SetCollisionProfileName("Pickup");
	StaticMeshComponent->SetGenerateOverlapEvents(true); // Turn ON (Overlap Events)
	StaticMeshComponent->SetNotifyRigidBodyCollision(false);

	static ConstructorHelpers::FObjectFinder<UStaticMesh>mesh(TEXT("/Game/Weapons/Rifle/Assault_Rifle_SM.Assault_Rifle_SM"));
	if (mesh.Succeeded()) {
		StaticMeshComponent->SetStaticMesh(mesh.Object);
		RootComponent = StaticMeshComponent;
	}

}

void AAssaultRifle::OnOverLapStart(class AActor* ThisActor, class AActor* OtherActor) {
	if (OtherActor && (OtherActor != this)) {
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, TEXT("Enter [E] Equip This Item"));
		class ACharacter* Character = Cast<ACharacter>(OtherActor);

		if (Character != NULL) {
			class APlayerController* Controller = Cast<APlayerController>(OtherActor->GetOwner());

			if (Controller != NULL) {
				Super::EnableInput(Controller);
				struct FInputActionBinding binding = Super::InputComponent->BindAction(TEXT("Equip"), IE_Pressed, this, &AAssaultRifle::Equip);
				binding.bConsumeInput = false;
				//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Orange, FString::Printf(TEXT("Owner Name = %s"), *Controller->GetName()));
			}

		}



	}
}





void AAssaultRifle::OnOverLapEnd(AActor* ThisActor, AActor* OtherActor) {
	if (OtherActor && (OtherActor != this)) {
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, TEXT("END OVERLAP = TRUE"));

		class APlayerController* Controller = Cast<APlayerController>(OtherActor->GetOwner());
		if (Controller != NULL) 
			if (Super::InputComponent->HasBindings()) {
				Super::InputComponent->RemoveActionBinding(FName(TEXT("Equip")), EInputEvent::IE_Pressed);// Removes "Equip" Input Binding Key
				GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Green, TEXT("Removed Key Binding"));
			}
	}
}

//==================================================[ACTIONS]==================================================
void AAssaultRifle::Equip() {
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Orange, TEXT("Item Equiped"));

}




// Called when the game starts or when spawned
void AAssaultRifle::BeginPlay() {
	Super::BeginPlay();
	//struct FStreamableManager& AssetLoader = UAssetManager::GetStreamableManager();
	//class UStaticMesh* StaticMesh = AssetLoader.LoadSynchronous<UStaticMesh>(FSoftObjectPath(TEXT("/Game/Weapons/Rifle/Assault_Rifle_SM.Assault_Rifle_SM")), true); // - Game/MilitaryWeapSilver/Weapons/Assault_Rifle_A.Assault_Rifle_A
	//if (StaticMesh != NULL) {
		//bool isLoaded = StaticMeshComponent->SetStaticMesh(StaticMesh);
		//if (isLoaded) {	
			//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Orange, TEXT("LOADED"));
	OnActorBeginOverlap.AddUniqueDynamic(this, &AAssaultRifle::OnOverLapStart);
	OnActorEndOverlap.AddUniqueDynamic(this, &AAssaultRifle::OnOverLapEnd);
	//}
//}
}







// Called every frame
void AAssaultRifle::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
}

