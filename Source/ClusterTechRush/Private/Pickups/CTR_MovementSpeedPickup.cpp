// Fill out your copyright notice in the Description page of Project Settings.


#include "Pickups/CTR_MovementSpeedPickup.h"



// Sets default values
ACTR_MovementSpeedPickup::ACTR_MovementSpeedPickup()
{
	//Super();
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PickupRange = CreateDefaultSubobject<USphereComponent>(TEXT("PickupCollider"));
	PickupRange->SetupAttachment(RootComponent);
}

void ACTR_MovementSpeedPickup::BeginPlay()
{
	Super::BeginPlay();
	PickupRange->OnComponentBeginOverlap.AddDynamic(this,&ACTR_Pickup::OnOverlapBegin);
	
}

void ACTR_MovementSpeedPickup::ApplyEffect(ACTR_Character* Player)
{
	Player->IncreaseMovementSpeed();
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Speed Up"));

}


