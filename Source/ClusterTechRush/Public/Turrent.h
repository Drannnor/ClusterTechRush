// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Weapon.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Turrent.generated.h"

UCLASS()
class CLUSTERTECHRUSH_API ATurrent : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATurrent();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(EditDefaultsOnly)
	AWeapon* TurretWeapon;

	UPROPERTY(EditDefaultsOnly)
	AActor* TurretTarget;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
