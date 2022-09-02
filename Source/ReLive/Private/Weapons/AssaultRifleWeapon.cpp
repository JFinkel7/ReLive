// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/AssaultRifleWeapon.h"

// Sets default values
AAssaultRifleWeapon::AAssaultRifleWeapon() {
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	// ------ [Weapon Static Mesh Component] ------
	WeaponMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SkeletalMesh"));
	WeaponMeshComponent->SetCollisionProfileName("Pickup"); // Make sure to ignore players camera from the collision settings 	StaticMeshComponent->SetGenerateOverlapEvents(true); // Turn ON (Overlap Events)
	WeaponMeshComponent->SetNotifyRigidBodyCollision(false);
	static ConstructorHelpers::FObjectFinder<UStaticMesh>mesh(TEXT("/Game/Weapons/Rifle/Assault_Rifle_SM.Assault_Rifle_SM"));
	if (mesh.Succeeded()) {
		WeaponMeshComponent->SetStaticMesh(mesh.Object);
		RootComponent = WeaponMeshComponent;
	}

}


void AAssaultRifleWeapon::PostInitializeComponents() {
	Super::PostInitializeComponents();
	class APlayerController* Controller = Cast<APlayerController>(AAssaultRifleWeapon::GetOwner());

	if (Controller != NULL) {
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, TEXT("AAssaultRifleWeapon = TRUE")); // Message hint to equip the pickup  
		Super::EnableInput(Controller); // Enable the input who ever is the owner of this weapon 
		FInputActionBinding bindOnFire = Super::InputComponent->BindAction<FInputFireDelegate>(TEXT("Fire"), IE_Pressed, this, &AAssaultRifleWeapon::Fire);// Listen for Key Event
		FInputActionBinding bindOnUnEquip = Super::InputComponent->BindAction<FInputUnEquipDelegate>(TEXT("UnEquip"), IE_Pressed, this, &AAssaultRifleWeapon::UnEquip);// Listen for Key Event
	}

}



// Called when the game starts or when spawned
void AAssaultRifleWeapon::BeginPlay() {
	Super::BeginPlay();

}





void AAssaultRifleWeapon::Fire() {
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Green, TEXT("FIRE IS CALLED"));

}

void AAssaultRifleWeapon::UnEquip() {
	AAssaultRifleWeapon::DetachFromActor(FDetachmentTransformRules::KeepRelativeTransform);//Detach this component from whatever it is attached to.
	class APlayerController* CHARACTER = Cast<APlayerController>(AAssaultRifleWeapon::GetOwner());// Get the weapon owner reference
	if (CHARACTER != NULL) {
		AAssaultRifleWeapon::SetActorLocation(CHARACTER->GetCharacter()->GetActorLocation());// set the weapon location near the owner 
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Green, TEXT("UnEquip IS CALLED | Weapon is Dropped"));
		// Next... Turn On Physics...
		// Next... Turn On Gravity...
		// Next... Make sure when weapon is droped it bounces like in the real world.
	}

}

// Called every frame
void AAssaultRifleWeapon::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

}

