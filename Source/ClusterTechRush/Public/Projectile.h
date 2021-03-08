// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"

#include "Projectile.generated.h"

UCLASS()
class CLUSTERTECHRUSH_API AProjectile : public AActor {
	GENERATED_BODY()

	public:
	// Sets default values for this actor's properties
	AProjectile();

	// Sphere collision component.
	UPROPERTY(VisibleDefaultsOnly, Category = Projectile)
	USphereComponent* CollisionComponent;

	// Projectile movement component.
	UPROPERTY(VisibleAnywhere, Category = Movement)
	UProjectileMovementComponent* ProjectileMovementComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Weapon")
	TSubclassOf<UDamageType> DamageType;
	
	float BaseDamage;
	
	UPROPERTY(EditDefaultsOnly, Category= "Lifetime")
	float LifeTime;

	FTimerHandle TimerHandle_Lifetime;

	// Function that initializes the projectile's velocity in the shoot direction.
	void SetProjectileParameters(const FVector& ShotDirection, float ProjectileDamage, float ProjectileSpeed, TSubclassOf<UDamageType> DamageType);

	protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	UFUNCTION()
    void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
                        FVector NormalImpulse, const FHitResult& Hit);

	UFUNCTION()
	void DestroyProjectile();

	public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
