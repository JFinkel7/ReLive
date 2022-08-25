// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/MainCharacter.h"

//	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Working = TRUE"));


// Sets default values
AMainCharacter::AMainCharacter() {
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	// ------ [Collision Capsule] ------
	GetCapsuleComponent()->InitCapsuleSize(32.0f, 96.0f);
	GetCapsuleComponent()->SetCollisionProfileName("Hero");
	GetCapsuleComponent()->SetGenerateOverlapEvents(true); // Turn On (Overlap Events)
	GetCapsuleComponent()->SetNotifyRigidBodyCollision(false);

	// set our turn rates for input
	//BaseTurnRate = 45.f;
	//BaseLookUpRate = 45.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// ------ [Spring Arm Component] ------
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f;       // The camera follows at this distance behind the character
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// ------ [Camera Component] ------
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false;

	// ------ [Character Mesh] ------
	GetMesh()->SetRelativeLocation(FVector(0.0f, 0.0f, -100.0f));
	GetMesh()->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));
	GetMesh()->AttachToComponent(GetCapsuleComponent(), FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	GetMesh()->SetCollisionProfileName("CharacterMesh");
	GetMesh()->CanCharacterStepUpOn = ECB_No;
	GetMesh()->SetGenerateOverlapEvents(false); // Turn On for (Overlap Events)
	GetMesh()->SetNotifyRigidBodyCollision(false);

	// ------ [Movement Component] ------
	GetCharacterMovement()->MaxWalkSpeed = 900; // Walk Speed = 300.0f Job Speed = 600.0f
	GetCharacterMovement()->bCanWalkOffLedges = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->bUseControllerDesiredRotation = true;
	GetCharacterMovement()->JumpZVelocity = 2;
	GetCharacterMovement()->bApplyGravityWhileJumping = true;
	GetCharacterMovement()->bIgnoreBaseRotation = true;

	// ------ [GUN Component] ------
	Gun = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Gun"));
	Gun->SetOnlyOwnerSee(false); // otherwise won't be visible in the multiplayer
	Gun->bCastDynamicShadow = false;
	Gun->CastShadow = false;
	

	// ------ [Muzzle Flash Component] ------
	ShootingLocation = CreateDefaultSubobject<USceneComponent>(TEXT("MuzzleLocation"));
	ShootingLocation->SetupAttachment(Gun);
	ShootingLocation->SetRelativeLocationAndRotation(Gun->GetRelativeLocation(), FRotator(180,0,0));
}

// Called when the game starts or when spawned
void AMainCharacter::BeginPlay() {
	Super::BeginPlay();
	if (GetMesh() != NULL) {
		FStreamableManager& AssetLoader = UAssetManager::GetStreamableManager();
		// Loads T100 Skeletal Mesh
		class USkeletalMesh* SkeletalAsset = AssetLoader.LoadSynchronous<USkeletalMesh>(FSoftObjectPath(TEXT("/Game/Characters/T100/Skeletal/T100.T100")), true);
		// Loads T100 Animation Blueprint
		class UAnimBlueprint* MainAnimation = AssetLoader.LoadSynchronous<UAnimBlueprint>(FSoftObjectPath(TEXT("/Game/Characters/T100/Animations/T100_AnimBP.T100_AnimBP")), true);

		if (SkeletalAsset != NULL) {
			GetMesh()->SetSkeletalMesh(SkeletalAsset, false);
			if (MainAnimation != NULL)
				GetMesh()->SetAnimInstanceClass(MainAnimation->GetAnimBlueprintGeneratedClass());
		}
	
		// Loads Assault Rifle Then Attaches it to the character hand

		class USkeletalMesh* GunSkeletalAsset = AssetLoader.LoadSynchronous<USkeletalMesh>(FSoftObjectPath(TEXT("/Game/Weapons/Rifle/Assault_Rifle_A.Assault_Rifle_A")), true);
		if (GunSkeletalAsset != NULL) {
			Gun->SetSkeletalMesh(GunSkeletalAsset);
			const FName SOCKET = TEXT("hand_r");//  middle_03_r	
			Gun->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, SOCKET);
			Gun->SetRelativeRotation(FRotator(0.0f, 0.0f, -90.0f));
			//Gun->SetupAttachment(GetMesh(), FName(TEXT("hand_r")));		
		}
	}
}

// Called every frame
void AMainCharacter::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

}

void AMainCharacter::moveForward(float Val) {
	if ((Controller != nullptr) && (Val != 0.0f)) {
		// Find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
		// Get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Val);

	}
}



void AMainCharacter::moveRight(float Val) {
	if ((Controller != nullptr) && (Val != 0.0f)) {
		// Find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
		// Get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// Add movement in that direction
		AddMovementInput(Direction, Val);
	}
}

void AMainCharacter::turnRate(float Rate) {
	AddControllerYawInput(Rate * (45.0f) * GetWorld()->GetDeltaSeconds()); // BaseTurnRate = 45.0f
}

void AMainCharacter::lookUpRate(float Rate) {
	AddControllerPitchInput(Rate * (45.0f) * GetWorld()->GetDeltaSeconds()); // BaseLoopUpRate = 45.0f
}

//==================================================[ACTIONS]==================================================
void AMainCharacter::teleport() {
	const FVector CURRENT_LOCATION = (Super::GetActorForwardVector() * 750.0f) + Super::GetActorLocation();
	const FRotator CURRENT_ROTATION = Super::GetActorRotation();

	Super::TeleportTo(CURRENT_LOCATION, CURRENT_ROTATION, false, true);

}


void AMainCharacter::fire() {
	class UWorld* const WORLD = Super::GetWorld();
	if (WORLD != nullptr) {
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Shot Fired"));
		struct FActorSpawnParameters ActorSpawnParams;
		ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;
		const FVector SPAWN_LOCATION = ShootingLocation->GetComponentLocation();
		const FRotator SPAWN_ROTATION = ShootingLocation->GetComponentRotation();
		WORLD->SpawnActor<ABallisticProjectile>(SPAWN_LOCATION, SPAWN_ROTATION, ActorSpawnParams);

	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AMainCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) {
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	check(PlayerInputComponent);

	// ---------------- [Action] Key Binding Movement Events
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AMainCharacter::Jump);
	PlayerInputComponent->BindAction("Teleport", IE_Pressed, this, &AMainCharacter::teleport);
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AMainCharacter::fire);
	// ---------------- [Axis] Key Binding Movement Events
	PlayerInputComponent->BindAxis("MoveForward", this, &AMainCharacter::moveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMainCharacter::moveRight);
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &AMainCharacter::turnRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AMainCharacter::lookUpRate);

}
