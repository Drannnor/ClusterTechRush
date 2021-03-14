// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pickups/CTR_Pickup.h"
#include "CTR_WeaponPickUp.generated.h"

/**
 * 
 */
UCLASS()
class CLUSTERTECHRUSH_API ACTR_WeaponPickUp : public ACTR_Pickup {
	GENERATED_BODY()
public:
	virtual void ApplyEffect(ACTR_Character* Player) override;
	
	UPROPERTY(EditDefaultsOnly, Category = Weapon)
	TSubclassOf<class AWeapon> WeaponClass;
};