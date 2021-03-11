// Fill out your copyright notice in the Description page of Project Settings.


#include "Pickups/CTR_Pickup.h"

#include <activation.h>

#include "GenericPlatform/GenericPlatformMisc.h"

/** /
ACTR_Pickup::ACTR_Pickup()
{
	PrimaryActorTick.bCanEverTick = true;
	PickupRange = CreateDefaultSubobject<USphereComponent>(TEXT("PickupCollider"));
	PickupRange->SetupAttachment(RootComponent);
	
}
/**/

// Called when the game starts or when spawned
void ACTR_Pickup::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACTR_Pickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}
void ACTR_Pickup::ApplyEffect(ACTR_Character* player)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("FAIL"));

}


void ACTR_Pickup::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)

{
	ACTR_Character* Player = Cast<ACTR_Character>(OtherActor);
	if(Player)
	{
		ApplyEffect(Player);
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Pickup picked up"));
		
	}
}





