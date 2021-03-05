

#include "CTR_Character.h"

#include "DrawDebugHelpers.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "HealthComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PawnMovementComponent.h"

// Sets default values
ACTR_Character::ACTR_Character() {
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetRelativeRotation(FRotator(-60.0f, 0.0f, 0.0f));

	CameraBoom->bIsCameraFixed = true;
	CameraBoom->bUsePawnControlRotation = false;

	// Create a follow camera
	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	CameraComp->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	// Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	CameraComp->bUsePawnControlRotation = false;

	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));
	HealthComponent->OnHealthChanged.AddDynamic(this, &ACTR_Character::OnHealthChanged);

	WeaponSocket = "WeaponSocket";

}

// Called when the game starts or when spawned
void ACTR_Character::BeginPlay() {
	Super::BeginPlay();

	CameraComp->SetFieldOfView(CameraFOV);
	CameraBoom->TargetArmLength = CameraDistance; // The camera follows at this distance behind the character

	APlayerController* MyController = GetWorld()->GetFirstPlayerController();
	MyController->bShowMouseCursor = true;

	FActorSpawnParameters SpawnParameters;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	CurrentWeapon = GetWorld()->SpawnActor<AWeapon>(WeaponClass, FVector::ZeroVector,
	                                                FRotator::ZeroRotator,
	                                                SpawnParameters);

	if (CurrentWeapon) {

		CurrentWeapon->SetOwner(this);
		CurrentWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale,
		                                 WeaponSocket);
	}

}

void ACTR_Character::MoveForward(const float Value) {
	AddMovementInput(FVector::ForwardVector * Value);
}


void ACTR_Character::MoveRight(const float Value) {
	AddMovementInput(FVector::RightVector * Value);
}

void ACTR_Character::StartFire() {
	bFiring = true;
	CurrentWeapon->StartFire();
}

void ACTR_Character::StopFire() {
	bFiring = false;
	CurrentWeapon->StopFire();
}

// Called every frame
void ACTR_Character::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();

	if (PlayerController) {
		const FVector ActorLocation = this->GetActorLocation();
		const FPlane XYPlane = FPlane(ActorLocation, FVector::UpVector);
		FVector PlayerViewPoint;
		FRotator PlayerViewRot;
		FVector MouseWorldLoc;
		FVector MouseWorldDir;

		// get mouse pos in world3D
		PlayerController->DeprojectMousePositionToWorld(MouseWorldLoc, MouseWorldDir);
		// get eyes position in world3D
		PlayerController->GetPlayerViewPoint(PlayerViewPoint, PlayerViewRot);

		//Intersect the ViewPoint to MousePosition Line with the XYPlane
		FVector AimPosition = FMath::LinePlaneIntersection(PlayerViewPoint, MouseWorldLoc, XYPlane);
		
		const FRotator PlayerRotation = UKismetMathLibrary::FindLookAtRotation(ActorLocation, AimPosition);

		DrawDebugLine(GetWorld(), ActorLocation, AimPosition, FColor::Red, false, 0.01, 0, 2);
		DrawDebugSphere(GetWorld(),AimPosition, 10, 4, FColor::Yellow, false, -1, 1, 1);
		this->SetActorRotation(PlayerRotation);	
		CurrentWeapon->SetLaunchDirection(PlayerRotation.Vector());
	}
	else {
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("No player controller found!!"));
	}
}

void ACTR_Character::OnHealthChanged(UHealthComponent* HealthComp, float Health, float HealthDelta,
                                  const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser) {

	if (Health <= 0.0f && !bDead) {
		//Die
		bDead = true;
		StopFire();
		GetMovementComponent()->StopMovementImmediately();
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		DetachFromControllerPendingDestroy();

		SetLifeSpan(10.0f);
	}
}


void ACTR_Character::IncreaseMovementSpeed() {
	UCharacterMovementComponent* CharacterMovementComponent = GetCharacterMovement();
	CharacterMovementComponent->MaxWalkSpeed += CharacterMovementComponent->MaxWalkSpeed * 0.1;
}

void ACTR_Character::IncreaseMaxHealth() {
	HealthComponent->IncreaseMaxHealth(25.0f);
}

void ACTR_Character::IncreaseHealth() {
	HealthComponent->Heal(50.0f);
}

// void ACTR_Character::ApplyPickUpEffect(EPickUpType PickUpType) {
// 	switch (PickUpType) {
// 	case EPickUpType::Health:
// 		IncreaseHealth();
// 		break;
// 	case EPickUpType::MaxHealth:
// 		IncreaseMaxHealth();
// 		break;
// 	case EPickUpType::MovementSpeed:
// 		IncreaseMovementSpeed();
// 		break;
// 	case EPickUpType::FireRate:
// 		CurrentWeapon->IncreaseFireRate();
// 		break;
// 	case EPickUpType::ProjectileDamage:
// 		CurrentWeapon->IncreaseProjectileDamage();
// 		break;
// 	case EPickUpType::MultiShot:
// 		CurrentWeapon->IncreaseMultiShot();
// 		break;
// 	case EPickUpType::EnergyCell:
// 		IncreaseDifficulty();
// 		break;
// 	default: ;
// 	}
// }

// Called to bind functionality to input
void ACTR_Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) {
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ACTR_Character::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ACTR_Character::MoveRight);

	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &ACTR_Character::StartFire);
	PlayerInputComponent->BindAction("Fire", IE_Released, this, &ACTR_Character::StopFire);
}
