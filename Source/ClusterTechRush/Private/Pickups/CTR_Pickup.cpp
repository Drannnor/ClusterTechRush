// Fill out your copyright notice in the Description page of Project Settings.


#include "Pickups/CTR_Pickup.h"


ACTR_Pickup::ACTR_Pickup() {
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	RootComponent = Root;
	PickupRange = CreateDefaultSubobject<USphereComponent>(TEXT("PickupCollider"));
	PickupRange->SetupAttachment(RootComponent);

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	MeshComp->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ACTR_Pickup::BeginPlay() {
	Super::BeginPlay();
	PickupRange->OnComponentBeginOverlap.AddDynamic(this, &ACTR_Pickup::OnOverlapBegin);
}

// Called every frame
void ACTR_Pickup::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

}

void ACTR_Pickup::ApplyEffect(ACTR_Character* Player) {
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("FAIL"));

}


void ACTR_Pickup::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
                                 class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                 const FHitResult& SweepResult) {
	ACTR_Character* Player = Cast<ACTR_Character>(OtherActor);
	if (Player) {
		ApplyEffect(Player);
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Pickup picked up"));
		Destroy();
	}
}
