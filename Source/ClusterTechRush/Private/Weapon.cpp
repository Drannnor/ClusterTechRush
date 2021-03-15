// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"


#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AWeapon::AWeapon() {
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));
	RootComponent = MeshComp;

	MuzzleSocketName = "MuzzleSocket";
	// TracerTargetName = "BeamEnd";
	// BaseDamage = 20;
	// VulnerableMultiplier = 4.0f;
	RateOfFire = 400;
	BulletSpread = 2.0f;
	bMultiShot = false;
	MultiShotProjectileAngles.Init(FRotator::ZeroRotator, 1);

}

// Called when the game starts or when spawned
void AWeapon::BeginPlay() {
	Super::BeginPlay();
	TimeBetweenShots = 60 / RateOfFire;


}

void AWeapon::StartFire() {
	float FirstDelay = LastFireTime + TimeBetweenShots - GetWorld()->TimeSeconds;
	GetWorldTimerManager().SetTimer(TimerHandle_TimeBetweenShots, this, &AWeapon::Trigger, TimeBetweenShots, true,
	                                FMath::Max(FirstDelay, 0.0f));
}


void AWeapon::StopFire() {
	GetWorldTimerManager().ClearTimer(TimerHandle_TimeBetweenShots);
}

void AWeapon::SetLaunchDirection(const FVector& Dir) {
	LaunchDirection = Dir;
}

void AWeapon::IncreaseFireRate() {
	RateOfFire = RateOfFire + RateOfFire * 0.1;
	TimeBetweenShots = 60 / RateOfFire;
}

void AWeapon::IncreaseProjectileDamage() {
	BaseDamage = BaseDamage + BaseDamage * 0.1;
}

void AWeapon::IncreaseMultiShot() {
	//TODO
}


void AWeapon::Trigger() {
	Fire();
}


void AWeapon::Fire() {
	UWorld* World = GetWorld();
	if (!World) return;


	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	SpawnParams.Instigator = GetInstigator();

	FVector MuzzleLocation = MeshComp->GetSocketLocation(MuzzleSocketName);

	for (auto ProjectileAngle : MultiShotProjectileAngles) {
		auto ProjectileDirection = LaunchDirection;
		ProjectileDirection = ProjectileAngle.RotateVector(ProjectileDirection);

		FRotator Spread = FRotator(0.0f, FMath::FRandRange(-BulletSpread, BulletSpread), 0.0f);

		ProjectileDirection = Spread.RotateVector(ProjectileDirection);
		
		ProjectileDirection.Normalize();
		// Spawn the projectile at the muzzle.
		AProjectile* Projectile = World->SpawnActor<AProjectile>(ProjectileClass, MuzzleLocation,
		                                                         ProjectileDirection.Rotation(), SpawnParams);
		if (Projectile) {
			// Set the projectile's initial trajectory.
			Projectile->SetProjectileParameters(ProjectileDirection, BaseDamage, ProjectileSpeed, DamageType);

			PlayEffects();
		}
		else {
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("No player projetile spawned!!"));
		}
	}
}

void AWeapon::PlayEffects() {
	if (FireSoundEffect) {
		float VolumeMultiplier = FMath::RandRange(0.2f, 0.5f);
		float PitchMultiplier = FMath::RandRange(0.9f, 1.5f);
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), FireSoundEffect,
		                                      MeshComp->GetSocketLocation(MuzzleSocketName),
		                                      FRotator::ZeroRotator,
		                                      VolumeMultiplier, PitchMultiplier, 0.02f);
		LastFireTime = GetWorld()->TimeSeconds;
	}

	//TODO play animation
	//TODO play camera shake
}


void AWeapon::Tick(float DeltaTime) {

}
