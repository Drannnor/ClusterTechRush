// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon.h"
#include "Weapon_Burst.generated.h"

/**
 * 
 */
UCLASS()
class CLUSTERTECHRUSH_API AWeapon_Burst : public AWeapon {
	GENERATED_BODY()

public:
	AWeapon_Burst();
protected:
	virtual void Trigger() override;

	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category= "Burst", meta = (EditCondition = "bBurst"))
	int BurstSize;

	int BurstCount;

	UPROPERTY(EditDefaultsOnly, Category= "Burst", meta = (EditCondition = "bBurst"))
	float BurstRateOfFire;

	float TimeBetweenBurstShots;

	FTimerHandle TimerHandle_BurstTimer;


	UFUNCTION()
	void BurstCheck();
};
