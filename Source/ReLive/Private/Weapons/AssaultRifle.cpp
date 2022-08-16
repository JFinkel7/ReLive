// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/AssaultRifle.h"


AAssaultRifle::AAssaultRifle() {
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SkeletalMesh"));
	StaticMeshComponent->SetupAttachment(RootComponent);
	StaticMeshComponent->SetCollisionProfileName("Pickup");
	StaticMeshComponent->SetGenerateOverlapEvents(true);
	StaticMeshComponent->SetNotifyRigidBodyCollision(false);
	// /Game/StarterContent/Shapes/Shape_Cube.Shape_Cube
	// /Game/Weapons/Rifle/Assault_Rifle_ASM.Assault_Rifle_ASM
	static ConstructorHelpers::FObjectFinder<UStaticMesh>mesh(TEXT("/Game/Weapons/Rifle/Assault_Rifle_ASM.Assault_Rifle_ASM"));
	if (mesh.Succeeded()) 
		StaticMeshComponent->SetStaticMesh(mesh.Object);
		

	

}

void AAssaultRifle::OnOverLapStart(class AActor* ThisActor, class AActor* OtherActor) {
	if (OtherActor && (OtherActor != this))
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Actor STARTED"));

}


// Called when the game starts or when spawned
void AAssaultRifle::BeginPlay() {
	Super::BeginPlay();
	//struct FStreamableManager& AssetLoader = UAssetManager::GetStreamableManager();
	//class UStaticMesh* StaticMesh = AssetLoader.LoadSynchronous<UStaticMesh>(FSoftObjectPath(TEXT("/Game/Weapons/Rifle/Assault_Rifle_ASM.Assault_Rifle_ASM")), true); // - Game/MilitaryWeapSilver/Weapons/Assault_Rifle_A.Assault_Rifle_A
	//if (StaticMesh != NULL) {
	//	//bool isLoaded = 
	//	StaticMeshComponent->SetStaticMesh(StaticMesh);
	//	//if(isLoaded)
	//	Super::OnActorBeginOverlap.AddDynamic(this, &AAssaultRifle::OnOverLapStart);
	//}
	OnActorBeginOverlap.AddDynamic(this, &AAssaultRifle::OnOverLapStart);
}


// Called every frame
void AAssaultRifle::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

}

