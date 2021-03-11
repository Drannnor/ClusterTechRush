// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pickups/CTR_Pickup.h"
#include "CTR_MovementSpeedPickup.generated.h"

/**
 * 
 */
UCLASS()
class CLUSTERTECHRUSH_API ACTR_MovementSpeedPickup : public ACTR_Pickup
{
	GENERATED_BODY()

public:	
	// Sets default values for this actor's properties
	ACTR_MovementSpeedPickup();

	
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:
	virtual void ApplyEffect(ACTR_Character* player) override;

};
