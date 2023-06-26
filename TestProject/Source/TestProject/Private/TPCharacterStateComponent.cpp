// Fill out your copyright notice in the Description page of Project Settings.

#include "TPCharacterStateComponent.h"
#include "TPGameInstance.h"

// Sets default values for this component's properties
UTPCharacterStateComponent::UTPCharacterStateComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	bWantsInitializeComponent = true;

	Level = 1;
}


// Called when the game starts
void UTPCharacterStateComponent::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void UTPCharacterStateComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UTPCharacterStateComponent::InitializeComponent()
{
	Super::InitializeComponent();
	SetNewLevel(Level);
}

void UTPCharacterStateComponent::SetNewLevel(int32 NewLevel)
{
	auto TPGameInstance = Cast<UTPGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	ABCHECK(nullptr != TPGameInstance);
	CurrentStateData = TPGameInstance->GetTPCharacterData(NewLevel);
	if (nullptr != CurrentStateData)
	{
		Level = NewLevel;
		SetHP(CurrentStateData->MaxHP);
	}
	else
	{
		ABLOG(Error, TEXT("Level (%d) data doesn't exist"), NewLevel);
	}
}

void UTPCharacterStateComponent::SetDamage(float NewDamage)
{
	ABCHECK(nullptr != CurrentStateData);
	SetHP(FMath::Clamp<float>(CurrentHP - NewDamage, 0.0f, CurrentStateData->MaxHP));
}

void UTPCharacterStateComponent::SetHP(float NewHP)
{
	CurrentHP = NewHP;
	OnHPChanged.Broadcast();
	if (CurrentHP < KINDA_SMALL_NUMBER)
	{
		CurrentHP = 0.0f;
		OnHPIsZero.Broadcast();
	}
}

float UTPCharacterStateComponent::GetAttack()
{
	ABCHECK(nullptr != CurrentStateData, 0.0f);
	return CurrentStateData->Attack;
}

float UTPCharacterStateComponent::GetHPRatio()
{
	ABCHECK(nullptr != CurrentStateData, 0.0f);
	return (CurrentStateData->MaxHP < KINDA_SMALL_NUMBER) ? 0.0f : (CurrentHP / CurrentStateData->MaxHP);
}

int32 UTPCharacterStateComponent::GetDropExp() const
{
	return CurrentStateData->DropExp;
}