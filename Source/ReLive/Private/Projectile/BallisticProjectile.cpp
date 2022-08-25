// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile/BallisticProjectile.h"

// Sets default values
ABallisticProjectile::ABallisticProjectile() {
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("RootComponent"));
	CollisionSphere->InitSphereRadius(25);
	CollisionSphere->SetCollisionProfileName(TEXT("Weapon"));                 // - Set Default Profile
	CollisionSphere->SetEnableGravity(true);                                 // - Allows Fireball drop
	CollisionSphere->SetSimulatePhysics(true);                                // - Turn On Physics
	CollisionSphere->SetGenerateOverlapEvents(true);                          // - Allow Overlapp
	CollisionSphere->SetNotifyRigidBodyCollision(true);
	CollisionSphere->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics); // - Turn Off Collision
	CollisionSphere->SetHiddenInGame(false);                                  //@Testing
	//CollisionSphere->ShapeColor = FColor::Purple;                                //@Testing
	RootComponent = CollisionSphere;
	//CollisionSphere->SetupAttachment(RootComponent);


	// - Create Visual Static Mesh Component
	SphereVisual = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VisualRepresentation"));
	SphereVisual->SetMobility(EComponentMobility::Movable);

	//C:\Users\slyfi\Documents\Unreal Projects\ReLive\Content\StarterContent\Shapes
	//"/Game/Weapons/Rifle/AssaultRifleA_Ammo.AssaultRifleA_Ammo"
	// - Load The Static Mesh
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereVisualAsset(TEXT("/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere"));
	if (SphereVisualAsset.Succeeded()) {
		SphereVisual->SetStaticMesh(SphereVisualAsset.Object);
		SphereVisual->SetupAttachment(CollisionSphere);
	}

	//Hit contains information about what the line trace hit.
	//FHitResult Hit;
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));

	if (ProjectileMovement != NULL) {
		// - Set Stats
		ProjectileMovement->UpdatedComponent = CollisionSphere;
		ProjectileMovement->InitialSpeed = 1000.f; // 3000.f
		ProjectileMovement->MaxSpeed = 1000.f; // 3000.f
		ProjectileMovement->bRotationFollowsVelocity = true;
		ProjectileMovement->bShouldBounce = true;
		ProjectileMovement->Bounciness = 0.3f;
	}

	// Die after 5 seconds by default
	InitialLifeSpan = 5.0f;
}

void ABallisticProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) {
	//if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr) && OtherComp->IsSimulatingPhysics()) {
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr)) {
		OtherComp->AddImpulseAtLocation(GetVelocity() * 100.0f, GetActorLocation());
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("I Hit Actor:  %s"), *OtherActor->GetName()));

		ABallisticProjectile::Destroy();
	}
}

// Called when the game starts or when spawned
void ABallisticProjectile::BeginPlay() {
	Super::BeginPlay();
	CollisionSphere->OnComponentHit.AddDynamic(this, &ABallisticProjectile::OnHit);
}

// Called every frame
void ABallisticProjectile::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

}

