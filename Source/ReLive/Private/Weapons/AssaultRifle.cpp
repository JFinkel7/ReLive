// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/AssaultRifle.h"


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
		//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Orange, FString::Printf(TEXT("You Hit: %s"), *ThisActor->GetName()));
		//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Orange, FString::Printf(TEXT("Who Hit Me?: %s"), *OtherActor->GetName()));
		class ACharacter* MAIN_CHARACTER = Cast<ACharacter>(OtherActor);

		if (MAIN_CHARACTER != NULL) {
			USkeletalMeshComponent* mesh = MAIN_CHARACTER->GetMesh();
			if (mesh != NULL) {
				const FName SOCKET = TEXT("hand_r");//  middle_03_r	
				const FRotator new_rotation = FRotator(90, 90, 0);
				ThisActor->SetActorRotation(new_rotation, ETeleportType::TeleportPhysics);
				ThisActor->AttachToComponent(mesh, FAttachmentTransformRules::SnapToTargetIncludingScale, SOCKET);
				StaticMeshComponent->SetGenerateOverlapEvents(false); // Turn OFF (Overlap Events)
			}
		}
	}
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
		//}
	//}
}


// Called every frame
void AAssaultRifle::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	//FRotator currentR = this->GetActorRotation();
	//float speed = DeltaTime * 50.0f;

	//currentR.Yaw += speed;
	//currentR.Roll += speed;
	//currentR.Pitch -= speed;
	//this->SetActorRotation(currentR);
}

