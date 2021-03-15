// Fill out your copyright notice in the Description page of Project Settings.


#include "Turret.h"

#include "CTR_Character.h"
#include "DrawDebugHelpers.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
ATurret::ATurret()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MeshComp"));
	TurretDetection = CreateDefaultSubobject<USphereComponent>(TEXT("TurretDetection"));

	TurretDetection->SetSphereRadius(100.0f);
	
	RootComponent = MeshComp;

	WeaponSocket = "WeaponSocket";

}

// Called when the game starts or when spawned
void ATurret::BeginPlay()
{
	Super::BeginPlay();

	this->OnActorBeginOverlap.AddDynamic(this, &ATurret::OnOverlapBegin);
	this->OnActorEndOverlap.AddDynamic(this, &ATurret::OnOverlapEnd);

	FActorSpawnParameters SpawnParameters;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	TurretWeapon = GetWorld()->SpawnActor<AWeapon>(WeaponClass, FVector::ZeroVector,
                                                    FRotator::ZeroRotator,
                                                    SpawnParameters);

	if (TurretWeapon) {

		TurretWeapon->SetOwner(this);
		TurretWeapon->AttachToComponent(MeshComp, FAttachmentTransformRules::SnapToTargetNotIncludingScale,
                                         WeaponSocket);
	}
	
}

// Called every frame
void ATurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (TurretTarget)
	{
		const auto TurretPosition = MeshComp->GetSocketLocation(WeaponSocket);
		const auto TargetPosition = TurretTarget->GetActorLocation();
		const FVector AimPosition = FVector(TargetPosition.X, TargetPosition.Y, TurretPosition.Z);
		
		const FRotator LaunchDir =  UKismetMathLibrary::FindLookAtRotation(TurretPosition, AimPosition);
		const FRotator WeaponRotation = LaunchDir + FRotator(0.0f, - 90.0f,0.0f);
		DrawDebugSphere(GetWorld(), AimPosition, 50.f, 4, FColor::Red, false, 0.01, 0, 2 );
		DrawDebugSphere(GetWorld(), TurretPosition, 50.f, 4, FColor::Green, false, 0.01, 0, 2 );
		DrawDebugLine(GetWorld(), TurretPosition, TurretPosition+WeaponRotation.Vector()*50, FColor::Blue, false, 0.01, 0, 2);

		TurretWeapon->SetLaunchDirection(LaunchDir.Vector());
		TurretWeapon->SetActorRotation(WeaponRotation);
		
	}

}

void ATurret::OnOverlapBegin(AActor* OverlappedActor, AActor* OtherActor)
{

	ACTR_Character* Player = Cast<ACTR_Character>(OtherActor);

	if(Player)
	{
		TurretTarget = OtherActor;
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Yellow, TEXT("Overlap begin"));
		TurretWeapon->StartFire();
	}
	
}

void ATurret::OnOverlapEnd(AActor* OverlappedActor, AActor* OtherActor)
{
	if(TurretTarget == OtherActor)
	{
		TurretTarget = nullptr;
		TurretWeapon->StopFire();
	}
	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT("Overlap end"));
	
}