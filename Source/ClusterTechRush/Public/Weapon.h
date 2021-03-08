// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.h"
#include "Weapon.generated.h"

UCLASS()
class CLUSTERTECHRUSH_API AWeapon : public AActor {
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AWeapon();

	virtual void StartFire();

	virtual void StopFire();
	
	void SetLaunchDirection(const FVector& Dir);
	
	void IncreaseFireRate();

	void IncreaseProjectileDamage();

	void IncreaseMultiShot();
	void PlayEffects();

protected:
	UPROPERTY(VisibleAnywhere, Category = "Components")
	USkeletalMeshComponent* MeshComp;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category= "Weapon")
	UParticleSystem* MuzzleEffect;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category= "Weapon")
	FName MuzzleSocketName;

	UPROPERTY(EditDefaultsOnly, Category= "Weapon")
	TSubclassOf<UMatineeCameraShake> FireCamShake;

	UPROPERTY(EditDefaultsOnly, Category= "Weapon")
	USoundBase* FireSoundEffect;

	//Bullet Spread in Degrees
	UPROPERTY(EditDefaultsOnly, Category= "Weapon", meta = (ClampMin=0.0f, ClampMax=90.0f))
	int BulletSpread;

	//RPM BULLETS per Minute
	UPROPERTY(EditDefaultsOnly, Category= "Weapon")
	float RateOfFire;

	//Derived from rate of fire
	float TimeBetweenShots;

	float LastFireTime;
	
	FTimerHandle TimerHandle_TimeBetweenShots;

	// Projectile class to spawn.
	UPROPERTY(EditDefaultsOnly, Category = Projectile)
	TSubclassOf<class AProjectile> ProjectileClass;

	FVector LaunchDirection;

	UPROPERTY(EditDefaultsOnly, Category= "Weapon", meta = (ClampMin=0.0f))
	float BaseDamage = 50.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Weapon")
	TSubclassOf<UDamageType> DamageType;

	UPROPERTY(EditDefaultsOnly, Category= "Weapon", meta = (ClampMin=0.0f))
	float ProjectileSpeed = 3000.0f;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void Fire();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
