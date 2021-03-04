// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AProjectile::AProjectile() {
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	if (!RootComponent) {
		RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("ProjectileSceneComponent"));
	}
	if (!CollisionComponent) {
		// Use a sphere as a simple collision representation.
		CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
		// Set the sphere's collision radius.
		CollisionComponent->InitSphereRadius(15.0f);
		// Set the root component to be the collision component.
		RootComponent = CollisionComponent;
	}

	if (!ProjectileMovementComponent) {
		// Use this component to drive this projectile's movement.
		ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(
			TEXT("ProjectileMovementComponent"));
		ProjectileMovementComponent->SetUpdatedComponent(CollisionComponent);
		ProjectileMovementComponent->InitialSpeed = 3000.0f;
		ProjectileMovementComponent->MaxSpeed = 3000.0f;
		ProjectileMovementComponent->bRotationFollowsVelocity = true;
		ProjectileMovementComponent->ProjectileGravityScale = 0.0f;
	}


}


void AProjectile::SetProjectileParameters(const FVector& ShotDirection, float ProjectileDamage, float ProjectileSpeed, TSubclassOf<UDamageType> DmgType) {
	ProjectileMovementComponent->Velocity = ShotDirection * ProjectileMovementComponent->InitialSpeed;

	ProjectileMovementComponent->InitialSpeed = ProjectileSpeed;
	ProjectileMovementComponent->MaxSpeed = ProjectileSpeed;

	BaseDamage = ProjectileDamage;
	this->DamageType = DmgType;
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay() {
	Super::BeginPlay();
	CollisionComponent->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
	

}

// Called every frame
void AProjectile::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
}


void AProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
                        FVector NormalImpulse, const FHitResult& Hit) {

	AActor* MyOwner = GetOwner();
	UGameplayStatics::ApplyPointDamage( OtherActor, BaseDamage, -(Hit.ImpactNormal), Hit,
	                                    MyOwner->GetInstigatorController(), MyOwner, DamageType );


	bool Destroyed = Destroy();
	if (!Destroyed) {
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("Projectile not destroyed"));
	}
	
}
