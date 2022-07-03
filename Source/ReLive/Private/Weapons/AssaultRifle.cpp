// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/AssaultRifle.h"


AAssaultRifle::AAssaultRifle() {
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
	SkeletalMeshComponent->SetupAttachment(RootComponent);
	SkeletalMeshComponent->SetGenerateOverlapEvents(true);
	SkeletalMeshComponent->SetNotifyRigidBodyCollision(false);
}

// Called when the game starts or when spawned
void AAssaultRifle::BeginPlay() {
	Super::BeginPlay();


	struct FStreamableManager& AssetLoader = UAssetManager::GetStreamableManager();
	class USkeletalMesh* SkeletalAsset = AssetLoader.LoadSynchronous<USkeletalMesh>(FSoftObjectPath(TEXT("/Game/MilitaryWeapSilver/Weapons/Assault_Rifle_A.Assault_Rifle_A")), true); // - Game/MilitaryWeapSilver/Weapons/Assault_Rifle_A.Assault_Rifle_A
	if (SkeletalAsset != NULL) {
		SkeletalMeshComponent->SetSkeletalMesh(SkeletalAsset, false);
		Super::OnActorBeginOverlap.AddDynamic(this, &AAssaultRifle::OnOverLapStart);
	}



}

void AAssaultRifle::OnOverLapStart(class AActor* ThisActor, class AActor* OtherActor) {
	if (OtherActor && (OtherActor != this))
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Actor STARTED"));

}

// Called every frame
void AAssaultRifle::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

}

