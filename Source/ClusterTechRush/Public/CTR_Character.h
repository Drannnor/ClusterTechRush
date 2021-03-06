#pragma once

#include "CoreMinimal.h"


// #include "PickUp.h"
#include "Weapon.h"
#include "GameFramework/Character.h"
#include "CTR_Character.generated.h"

class UHealthComponent;
class UCameraComponent;


UCLASS()
class CLUSTERTECHRUSH_API ACTR_Character : public ACharacter {
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACTR_Character();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	UCameraComponent* CameraComp;

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;


	UPROPERTY(BlueprintReadOnly, Category= "Player" )
	bool bFiring = false;

	UPROPERTY( BlueprintReadOnly, Category= "Player" )
	bool bDead = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	UHealthComponent* HealthComponent;

	float DefaultSpeed;

	UPROPERTY(EditDefaultsOnly, Category= "CameraOptions", meta = (ClampMin=0.0f))
	float CameraDistance = 900.0f;

	UPROPERTY(EditDefaultsOnly, Category= "CameraOptions", meta = (ClampMin=0.0f))
	float CameraFOV = 90.0f;

	UPROPERTY(EditDefaultsOnly, Category = Weapon)
	TSubclassOf<class AWeapon> DefaultWeaponClass;

	AWeapon* CurrentWeapon;

	UPROPERTY( VisibleDefaultsOnly, Category= "Player" )
	FName WeaponSocket;
	
	UFUNCTION()
	void MoveForward(float Value);

	UFUNCTION()
	void MoveRight(float Value);

	UFUNCTION()
	void Dash();
	



public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable, Category= "Player")
	void StartFire();

	UFUNCTION(BlueprintCallable, Category= "Player")
	void StopFire();

	UFUNCTION()
	void OnHealthChanged(UHealthComponent* HealthComp, float Health, float HealthDelta,
	                     const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);

	UFUNCTION(BlueprintImplementableEvent)
	void IncreaseDifficulty();

	void IncreaseMovementSpeed();

	void IncreaseMaxHealth();

	void IncreaseHealth();
	void SpawnWeapon(const TSubclassOf<AWeapon>& WeaponClass);

	void DropWeapon();
	
	void SwitchWeapon(const TSubclassOf<AWeapon>& WeaponClass);		
	// UFUNCTION(BlueprintCallable)
	// void ApplyPickUpEffect(EPickUpType PickUpType);

};
