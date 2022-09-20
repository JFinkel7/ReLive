// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/AssaultRifle.h"

AAssaultRifle::AAssaultRifle() {
	PrimaryActorTick.bCanEverTick = false;

	// ------ [CollisionSphere Component] ------
	CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionSphereComponent"));
	CollisionSphere->SetupAttachment(RootComponent);// Attaches to the Gun Static Mesh 
	CollisionSphere->SetCollisionProfileName(TEXT("Weapon")); // Set Default Profile
	CollisionSphere->Mobility = EComponentMobility::Movable;
	CollisionSphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly); // (DEFAULT)
	CollisionSphere->SetNotifyRigidBodyCollision(false); // (OFF) Hit Events 
	CollisionSphere->SetGenerateOverlapEvents(true); // (ON) Overlap Events 
	CollisionSphere->ShapeColor = FColor::Green; //@Testing
	CollisionSphere->InitSphereRadius(15); // Add Collision Radius
	CollisionSphere->SetHiddenInGame(true);// @Testing - OFF makes it Visible
	CollisionSphere->SetAllMassScale(3.8f); // Add Weight

	// ------ [Weapon Static Mesh Component] ------
	Gun = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMeshComponent"));
	Gun->AttachToComponent(CollisionSphere, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	Gun->SetCollisionEnabled(ECollisionEnabled::NoCollision); // (DEFAULT)
	Gun->SetGenerateOverlapEvents(false); // (ON) Overlap Events 
	Gun->SetNotifyRigidBodyCollision(false);// (OFF) Hit Events
	Gun->CanCharacterStepUpOn = ECB_No;
	Gun->bCastDynamicShadow = false;
	Gun->bReceivesDecals = false;
	Gun->bOnlyOwnerSee = false; // otherwise won't be visible in the multiplayer
	Gun->CastShadow = false;
	// @test
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, TEXT("[AAssaultRifle] CREATED = True"));
}


// Called when the game starts or when spawned
void AAssaultRifle::BeginPlay() {
	Super::BeginPlay();
	FStreamableManager& AssetLoader = UAssetManager::GetStreamableManager(); // Create a Streamable Manager
	USkeletalMesh* frame = AssetLoader.LoadSynchronous<USkeletalMesh>(FSoftObjectPath(TEXT("/Game/Weapons/Rifle/Assault_Rifle_A.Assault_Rifle_A")), true);
	if (frame != NULL) {
		Gun->SetSkeletalMesh(frame); // Set Asset
		if (frame->IsAsset()) {
			OnActorBeginOverlap.AddDynamic(this, &AAssaultRifle::OnOverLapStart); // Register OnOverlapStart
			OnActorEndOverlap.AddDynamic(this, &AAssaultRifle::OnOverLapEnd); // Register OnOverlapEnd
		}
	}
}




void AAssaultRifle::OnOverLapStart(class AActor* ThisActor, class AActor* OtherActor) {
	if (OtherActor && (OtherActor != this)) {
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, TEXT("Enter [E] Equip This Item")); // Message 		
		class APlayerController* Controller = Cast<APlayerController>(OtherActor->GetOwner());
		if (Controller != NULL) {
			Super::EnableInput(Controller);// Enable Input 
			FInputActionBinding binding = Super::InputComponent->BindAction<FInputEquipDelegate>(TEXT("Equip"), IE_Pressed, this, &AAssaultRifle::Equip, OtherActor);// [E] Key Action Binding Created 
			binding.bConsumeInput = true;
		}
	}
}






void AAssaultRifle::OnOverLapEnd(AActor* ThisActor, AActor* OtherActor) {
	if (OtherActor && (OtherActor != this)) {
		if (Super::InputComponent->HasBindings()) {// Check if this actor has any bindings  
			// [E] key action binding removed 
			Super::InputComponent->RemoveActionBinding(FName(TEXT("Equip")), EInputEvent::IE_Pressed);// Removes "Equip" Input Binding Key
			// Message
			GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, TEXT("OnOverLapEnd = True"));
		}
	}
}



void AAssaultRifle::Equip(class AActor* OtherActor) {
	const class ACharacter* CHARACTER = Cast<ACharacter>(OtherActor);// Get character who equiped this actor  
	if (CHARACTER != NULL) {
		class USkeletalMeshComponent* mesh = CHARACTER->GetMesh(); // Get character mesh reference 
		if (mesh != NULL) {
			const FName SOCKET = TEXT("hand_r");// Bone Socket Name 
			const FRotator DIRECTION_OF_PLAYER = mesh->GetComponentRotation();
			Super::AttachToComponent(mesh, FAttachmentTransformRules::SnapToTargetIncludingScale, SOCKET);
			Super::SetActorRotation(DIRECTION_OF_PLAYER, ETeleportType::TeleportPhysics);

			if (Super::InputComponent->HasBindings()) {// Check if this actor has any bindings  
				// (OFF)  Overlap Events
				CollisionSphere->SetGenerateOverlapEvents(false);
				// [E] key action binding removed 
				Super::InputComponent->RemoveActionBinding(FName(TEXT("Equip")), EInputEvent::IE_Pressed);

				// [F] Key Action Binding Created 
				struct FInputActionBinding OnFireBinding = Super::InputComponent->BindAction<FInputFireDelegate>(TEXT("Fire"), IE_Pressed, this, &AAssaultRifle::Fire);
				OnFireBinding.bConsumeInput = true;

				// [U] Key Action Binding Created 
				struct FInputActionBinding bindOnUnEquip = Super::InputComponent->BindAction<FInputUnEquipDelegate>(TEXT("UnEquip"), IE_Pressed, this, &AAssaultRifle::UnEquip, OtherActor);
				// Message
				GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Weapon is Equiped"));
			}
		}
	}
}


void AAssaultRifle::UnEquip(class AActor* OtherActor) {
	class APlayerController* Controller = Cast<APlayerController>(OtherActor->GetOwner());
	if (Controller != NULL) {
		Super::DetachFromActor(FDetachmentTransformRules::KeepRelativeTransform);// Detach this actor from the character 
		const FVector BONE_LOCATION = Controller->GetCharacter()->GetMesh()->GetBoneLocation(FName(TEXT("hand_r")), EBoneSpaces::Type::WorldSpace);
		Super::SetActorLocation(BONE_LOCATION);//  Set this actor near the character  
		CollisionSphere->SetGenerateOverlapEvents(true); // (ON) Overlap Events 

		if (Super::InputComponent->HasBindings()) {// Check if this actor has any bindings  
			// [U] Key action binding removed
			Super::InputComponent->RemoveActionBinding(FName(TEXT("UnEquip")), EInputEvent::IE_Pressed);
			// [F] Key action binding removed
			Super::InputComponent->RemoveActionBinding(FName(TEXT("Fire")), EInputEvent::IE_Pressed);
			// Message
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Weapon is UnEquiped"));
			// To Be Continued.... 
			// NEXT I detatch and set this actor to the original location 
		}
	}
}


void AAssaultRifle::Fire() {
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Green, TEXT("FIRE IS CALLED"));
	class UWorld* World = GetWorld();
	if (World) {
		const FVector Location = Gun->GetSocketLocation(FName(TEXT("MuzzleFlash"))); // Get The Gun Socket FName  Location 
		const FRotator Rotation = Gun->GetSocketRotation(FName(TEXT("MuzzleFlash"))); // Get The Gun Socket FName Rotation
		struct FActorSpawnParameters ActorSpawnParams;
		ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;
		// Spawns the projectile 
		World->SpawnActor<ABallistic>(Location, Rotation, ActorSpawnParams);
	}
}











