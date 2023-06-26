// Fill out your copyright notice in the Description page of Project Settings.

#include "TPItemBox.h"
#include "TPCharacter.h"
#include "TPWeapon.h"

// Sets default values
ATPItemBox::ATPItemBox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

    Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("TRIGGER"));
    Box = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BOX"));
    Effect = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("EFFECT"));

    RootComponent = Trigger;
    Box->SetupAttachment(RootComponent);
    Effect->SetupAttachment(RootComponent);

    Trigger->SetBoxExtent(FVector(40.0f, 42.0f, 30.0f));
    static ConstructorHelpers::FObjectFinder<UStaticMesh> 
        SM_BOX(TEXT("/Game/InfinityBladeGrassLands/Environments/Breakables/StaticMesh/Box/SM_Env_Breakables_Box1.SM_Env_Breakables_Box1"));
    if (SM_BOX.Succeeded())
    {
        Box->SetStaticMesh(SM_BOX.Object);
    }
    

    static ConstructorHelpers::FObjectFinder<UParticleSystem> 
        P_CHESTOPEN(TEXT("/Game/InfinityBladeGrassLands/Effects/FX_Treasure/Chest/P_TreasureChest_Open_Mesh.P_TreasureChest_Open_Mesh"));
    if (P_CHESTOPEN.Succeeded())
    {
        Effect->SetTemplate(P_CHESTOPEN.Object);
        Effect->bAutoActivate = false;
    }

    Box->SetRelativeLocation(FVector(0.0f, -3.5f, -30.0f));

    Trigger->SetCollisionProfileName(TEXT("ItemBox"));
    Box->SetCollisionProfileName(TEXT("NoCollision"));

    WeaponItemClass = ATPWeapon::StaticClass();

}

// Called when the game starts or when spawned
void ATPItemBox::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATPItemBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATPItemBox::PostInitializeComponents()
{
    Super::PostInitializeComponents();
    Trigger->OnComponentBeginOverlap.AddDynamic(this, &ATPItemBox::OnCharacterOverlap);
}

void ATPItemBox::OnCharacterOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    ABLOG_S(Warning);

    auto TPCharacter = Cast<ATPCharacter>(OtherActor);
    ABCHECK(nullptr != TPCharacter);

    if (nullptr != TPCharacter && nullptr != WeaponItemClass)
    {
        if (TPCharacter->CanSetWeapon())
        {
            auto NewWeapon = GetWorld()->SpawnActor<ATPWeapon>(WeaponItemClass, FVector::ZeroVector, FRotator::ZeroRotator);
            TPCharacter->SetWeapon(NewWeapon);
            Effect->Activate(true);
            Box->SetHiddenInGame(true, true);
            SetActorEnableCollision(false);
            Effect->OnSystemFinished.AddDynamic(this, &ATPItemBox::OnEffectFinished);
        }
        else
        {
            ABLOG(Warning, TEXT("%s can't equip weapon currently."), *TPCharacter->GetName());
        }
    }
}

void ATPItemBox::OnEffectFinished(UParticleSystemComponent* PSystem)
{
    Destroy();
}
