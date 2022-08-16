// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/MainCharacter.h"

//	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Working = TRUE"));


// Sets default values
AMainCharacter::AMainCharacter() {
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	// ------ [Collision Capsule] ------
	GetCapsuleComponent()->InitCapsuleSize(32.0f, 96.0f);
	GetCapsuleComponent()->SetCollisionProfileName("Hero");
	GetCapsuleComponent()->SetGenerateOverlapEvents(true); // Turn On for (Overlap Events)
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


void AMainCharacter::teleport() {
	// - Teleports the player to the center of the map 0,0

	const FVector CURRENT_LOCATION = (Super::GetActorForwardVector() * 750.0f) + Super::GetActorLocation();
	const FRotator CURRENT_ROTATION = Super::GetActorRotation();

	Super::TeleportTo(CURRENT_LOCATION, CURRENT_ROTATION);

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Working = TRUE"));
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AMainCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) {
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	check(PlayerInputComponent);

	// ---------------- Basic Key Binding Movement Events ----------------
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AMainCharacter::Jump);
	PlayerInputComponent->BindAction("teleport", IE_Pressed, this, &AMainCharacter::teleport);


	PlayerInputComponent->BindAxis("MoveForward", this, &AMainCharacter::moveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMainCharacter::moveRight);
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &AMainCharacter::turnRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AMainCharacter::lookUpRate);

}
