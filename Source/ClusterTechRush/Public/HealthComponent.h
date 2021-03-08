// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CLUSTERTECHRUSH_API UHealthComponent : public UActorComponent {
    GENERATED_BODY()

    DECLARE_DYNAMIC_MULTICAST_DELEGATE_SixParams( FOnHealthChangedSignature, UHealthComponent*, HealthComp, float,
                                                  Health, float, HealthDelta, const class UDamageType*, DamageType,
                                                  class AController*, InstigatedBy, AActor*, DamageCauser );


public:
    // Sets default values for this component's properties
    UHealthComponent();

protected:

    UPROPERTY(BlueprintReadWrite, Category = "HealthComponent")
    float Health;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "HealthComponent")
    float MaxHealth = 100;

    bool bIsDead;
    // Called when the game starts
    virtual void BeginPlay() override;

    UFUNCTION()
    void HandleTakeAnyDamage( AActor* DamagedActor, float Damage, const class UDamageType* DamageType,
                              class AController* InstigatedBy, AActor* DamageCauser );


public:

    float GetHealth() const;

    UFUNCTION(BlueprintCallable, Category="HealthComponents" )
    void Heal( float HealAmount );
    void IncreaseMaxHealth(float HealthIncrease);

    UPROPERTY( BlueprintAssignable, Category = "Events" )
    FOnHealthChangedSignature OnHealthChanged;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category= "HealthComponent")
    uint8 TeamNumber;

    UFUNCTION(BlueprintCallable, BlueprintPure, Category="HealthComponents" )
    static bool IsFriendly( AActor* A, AActor* B );
};