// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon_Burst.h"


AWeapon_Burst::AWeapon_Burst() {
	BurstSize = 1;
	BurstCount = 0;
	BurstRateOfFire = 800;

}

void AWeapon_Burst::Trigger() {
	float FirstDelay = LastFireTime + TimeBetweenBurstShots - GetWorld()->TimeSeconds;
	GetWorldTimerManager().SetTimer(TimerHandle_BurstTimer, this, &AWeapon_Burst::BurstCheck, TimeBetweenBurstShots, true,
                                    FMath::Max(FirstDelay, 0.0f));
}

void AWeapon_Burst::BeginPlay() {
	Super::BeginPlay();
	TimeBetweenBurstShots = 60 / BurstRateOfFire;
}

void AWeapon_Burst::BurstCheck() {
	BurstCount++;
	if(BurstCount >= BurstSize) {
		GetWorldTimerManager().ClearTimer(TimerHandle_BurstTimer);
		BurstCount = 0;
	}
	Fire();
}
