// Fill out your copyright notice in the Description page of Project Settings.


#include "TPWeapon.h"

// Sets default values
ATPWeapon::ATPWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

    Weapon = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WEAPON"));
    RootComponent = Weapon;

    static ConstructorHelpers::FObjectFinder<USkeletalMesh> 
        SK_WEAPON(TEXT("/Game/InfinityBladeWeapons/Weapons/Blade/Swords/Blade_DragonSword/SK_Blade_DragonSword.SK_Blade_DragonSword"));
    if (SK_WEAPON.Succeeded())
    {
        Weapon->SetSkeletalMesh(SK_WEAPON.Object);
    }
    Weapon->SetCollisionProfileName(TEXT("NoCollision"));

    AttackRange = 150.0f;
    AttackDamageMin = -2.5f;
    AttackDamageMax = 10.0f;
    AttackModifierMin = 0.85f;
    AttackModifierMax = 1.25f;

}

// Called when the game starts or when spawned
void ATPWeapon::BeginPlay()
{
	Super::BeginPlay();
	
    AttackDamage = FMath::RandRange(AttackDamageMin, AttackDamageMax);
    AttackModifier = FMath::RandRange(AttackModifierMin, AttackModifierMax);

    ABLOG(Warning, TEXT("Weapon Damage : %f, Modifier : %f"), AttackDamage, AttackModifier);
}

// Called every frame
void ATPWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

float ATPWeapon::GetAttackRange() const
{
    return AttackRange;
}

float ATPWeapon::GetAttackDamage() const
{
    return AttackDamage;
}

float ATPWeapon::GetAttackModifier() const
{
    return AttackModifier;
}

