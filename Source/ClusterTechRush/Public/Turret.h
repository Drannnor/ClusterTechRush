// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Weapon.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Perception/PawnSensingComponent.h"

#include "Turret.generated.h"

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
	USkeletalMeshComponent* MeshComp;

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
	


	
};
