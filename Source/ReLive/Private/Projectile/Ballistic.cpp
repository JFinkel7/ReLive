// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile/Ballistic.h"

// Sets default values
ABallistic::ABallistic() {
	PrimaryActorTick.bCanEverTick = false;	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.

	// ------ [Root] ------
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("ROOT"));

	// ------ [Static Mesh Component] ------
	Material = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshMaterial"));
	Material->SetupAttachment(RootComponent); // - Attatched to the Parent  
	Material->SetWorldScale3D(FVector(0.3f, 0.3, 0.3)); // Size 
	Material->SetCollisionProfileName(TEXT("PhysicsActor"));// - Collision Profile 
	Material->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics); // - Turn On Collision and Physics
	Material->SetEnableGravity(true);// - (ON) Gravity
	Material->SetSimulatePhysics(false);// - (OFF) Physics
	Material->Mobility = EComponentMobility::Movable; // Make the object movable
	Material->SetGenerateOverlapEvents(false); // (ON) Overlap Events 
	Material->SetNotifyRigidBodyCollision(true);// (OFF) Hit Events
	Material->SetHiddenInGame(false);// (ON) Visible 
	Material->bCastDynamicShadow = false;
	Material->bReceivesDecals = false;
	Material->bOnlyOwnerSee = false; // otherwise won't be visible in the multiplayer
	Material->CastShadow = false;
	

	// ------ [Projectile Movement Component] ------
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComponent"));
	if (ProjectileMovement != NULL) {
		ProjectileMovement->UpdatedComponent = Material;
		ProjectileMovement->InitialSpeed = 3000.0f;
		ProjectileMovement->MaxSpeed = 3000.0f;
		ProjectileMovement->bRotationFollowsVelocity = true;
		ProjectileMovement->bShouldBounce = true;
		ProjectileMovement->Bounciness = 0.3f;
		ProjectileMovement->ProjectileGravityScale = 0.0f;
	}

	Super::InitialLifeSpan = 15.0f; // Destroy this actor in 15sec
}






// Called when the game starts or when spawned
void ABallistic::BeginPlay() {
	Super::BeginPlay();

	// Load Asset When The Game Starts
	class UStaticMesh* asset = LoadObject<UStaticMesh>(nullptr, TEXT("/Game/StarterContent/Props/MaterialSphere.MaterialSphere"));
	if (asset != NULL) {
		Material->SetStaticMesh(asset);
		// Activate The onHit Listener
		OnActorHit.AddDynamic(this, &ABallistic::OnHit);
	}
}




void ABallistic::OnHit(AActor* ThisActor, AActor* HitActor, FVector NormalImpulse, const FHitResult& HitInfo) {
	if ((HitActor != NULL) && (HitActor != this) && (ThisActor != NULL))
		if (HitInfo.bBlockingHit) {
			// Apply Damage on Hit
			UGameplayStatics::ApplyPointDamage(HitActor, 10.0f, GetActorLocation(), HitInfo, NULL, NULL, UDamageType::StaticClass());
			//@test message
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Actor Hit"));
		}
}


