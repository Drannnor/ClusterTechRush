// Fill out your copyright notice in the Description page of Project Settings.


#include "Pickups/CTR_WeaponPickUp.h"


void ACTR_WeaponPickUp::ApplyEffect(ACTR_Character* Player) {
	Player->SwitchWeapon(WeaponClass);
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("WeaponPickUp"));

}
