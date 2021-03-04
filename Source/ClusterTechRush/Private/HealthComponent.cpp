// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"
#include "GameFramework/GameModeBase.h"
#include "Net/UnrealNetwork.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent() {
    Health = MaxHealth;
    bIsDead = false;
    TeamNumber = 255;
}

// Called when the game starts
void UHealthComponent::BeginPlay() {
    Super::BeginPlay();
    SetIsReplicated( true );

    AActor* MyOwner = GetOwner();
    if( MyOwner ) {
        MyOwner->OnTakeAnyDamage.AddDynamic( this, &UHealthComponent::HandleTakeAnyDamage );
    }
}

void UHealthComponent::HandleTakeAnyDamage( AActor* DamagedActor, float Damage, const UDamageType* DamageType,
                                             AController* InstigatedBy, AActor* DamageCauser ) {


    if( Damage <= 0.0f || bIsDead ) {
        return;
    }

    //Update Health clamped
    Health = FMath::Clamp( Health - Damage, 0.0f, MaxHealth );

    UE_LOG( LogTemp, Log, TEXT("Health Changed: %s/%s"),*FString::SanitizeFloat(MaxHealth), *FString::SanitizeFloat( Health ) );


    bIsDead = Health <= 0.0f;
    OnHealthChanged.Broadcast( this, Health, Damage, DamageType, InstigatedBy, DamageCauser );

    if( bIsDead ) {
        // ASGameModeBase* GM = Cast<ASGameModeBase>( GetWorld()->GetAuthGameMode() );
        // if( GM ) {
        //     GM->OnActorKilled.Broadcast( GetOwner(), DamageCauser, InstigatedBy );
        // }
    }


}

float UHealthComponent::GetHealth() const {
    return Health;
}

void UHealthComponent::Heal( float HealAmount ) {
    if( HealAmount <= 0.0f || Health <= 0.0f ) {
        return;
    }
    Health = FMath::Clamp( Health + HealAmount, 0.0f, MaxHealth );

    UE_LOG( LogTemp, Log, TEXT( "Healed: %s (+ %s)" ), *FString::SanitizeFloat( Health ),
            *FString::SanitizeFloat( HealAmount ) );

    OnHealthChanged.Broadcast( this, Health, -HealAmount, nullptr, nullptr, nullptr );


}

void UHealthComponent::IncreaseMaxHealth(float HealthIncrease) {
    UE_LOG( LogTemp, Log, TEXT( "MaxHealth++: (+ %s)" ), *FString::SanitizeFloat( HealthIncrease ));

    MaxHealth += HealthIncrease;
    Health += HealthIncrease;
    OnHealthChanged.Broadcast( this, Health, -HealthIncrease, nullptr, nullptr, nullptr );
    
}

bool UHealthComponent::IsFriendly( AActor* A, AActor* B ) {

    if( !A || !B ) {
        return true;
    }

    UHealthComponent* HealthCompA = Cast<UHealthComponent>( A->GetComponentByClass( StaticClass() ) );
    UHealthComponent* HealthCompB = Cast<UHealthComponent>( B->GetComponentByClass( StaticClass() ) );

    if( !HealthCompA || !HealthCompB ) {
        return true;
    }

    return HealthCompA->TeamNumber == HealthCompB->TeamNumber;
}
