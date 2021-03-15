// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Weapon.h"
#include "CoreMinimal.h"

#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "Turret.generated.h"

class UHealthComponent;


UCLASS()
class CLUSTERTECHRUSH_API ATurret : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATurret();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = Components)
	USceneComponent* Root;
	
	UPROPERTY(VisibleAnywhere, Category = Components)
	USkeletalMeshComponent* MeshComp;

	UPROPERTY(VisibleAnywhere, Category = Components)
	UBoxComponent* BoxCollider;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	UHealthComponent* TurretHealth;

	UPROPERTY(EditDefaultsOnly, Category= Components)
	USphereComponent* TurretDetection;
	
	UPROPERTY( VisibleDefaultsOnly, Category= Turret)
	FName WeaponSocket;

	UPROPERTY(EditDefaultsOnly, Category= Turret)
	AActor* TurretTarget;

	UPROPERTY(EditDefaultsOnly, Category = Weapon)
	TSubclassOf<class AWeapon> WeaponClass;
	
	AWeapon* TurretWeapon;

	float LastShot;

	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnOverlapBegin(AActor* OverlappedActor, AActor* OtherActor);

	UFUNCTION()
	void OnOverlapEnd(AActor* OverlappedActor, AActor* OtherActor);

	UFUNCTION()
	void OnHealthChanged(UHealthComponent* HealthComp, float Health, float HealthDelta,
                         const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);

	
};
