// Fill out your copyright notice in the Description page of Project Settings.

#include "TPHUDWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "TPCharacterStateComponent.h"
#include "TPPlayerState.h"

void UTPHUDWidget::BindCharacterState(UTPCharacterStateComponent * CharacterState)
{
	ABCHECK(nullptr != CharacterState);
	CurrentCharacterState = CharacterState;
	CharacterState->OnHPChanged.AddUObject(this, &UTPHUDWidget::UpdateCharacterState);
	UpdateCharacterState();
}

void UTPHUDWidget::BindPlayerState(ATPPlayerState * PlayerState)
{
	ABCHECK(nullptr != PlayerState);
	CurrentPlayerState = PlayerState;
	PlayerState->OnPlayerStateChanged.AddUObject(this, &UTPHUDWidget::UpdatePlayerState);
	UpdatePlayerState();
}

void UTPHUDWidget::NativeConstruct()
{
	Super::NativeConstruct();
	HPBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("pbHP")));
	ABCHECK(nullptr != HPBar);

	ExpBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("pbExp")));
	ABCHECK(nullptr != ExpBar);

	PlayerName = Cast<UTextBlock>(GetWidgetFromName(TEXT("txtPlayerName")));
	ABCHECK(nullptr != PlayerName);

	PlayerLevel = Cast<UTextBlock>(GetWidgetFromName(TEXT("txtLevel")));
	ABCHECK(nullptr != PlayerLevel);

	CurrentScore = Cast<UTextBlock>(GetWidgetFromName(TEXT("txtCurrentScore")));
	ABCHECK(nullptr != CurrentScore);

	HighScore = Cast<UTextBlock>(GetWidgetFromName(TEXT("txtHighScore")));
	ABCHECK(nullptr != HighScore);
}

void UTPHUDWidget::UpdateCharacterState()
{
	ABCHECK(CurrentCharacterState.IsValid());

	HPBar->SetPercent(CurrentCharacterState->GetHPRatio());
}

void UTPHUDWidget::UpdatePlayerState()
{
	ABCHECK(CurrentPlayerState.IsValid());

	ExpBar->SetPercent(CurrentPlayerState->GetExpRatio());
	PlayerName->SetText(FText::FromString(CurrentPlayerState->GetPlayerName()));
	PlayerLevel->SetText(FText::FromString(FString::FromInt(CurrentPlayerState->GetCharacterLevel())));
	CurrentScore->SetText(FText::FromString(FString::FromInt(CurrentPlayerState->GetGameScore())));
	HighScore->SetText(FText::FromString(FString::FromInt(CurrentPlayerState->GetGameHighScore())));
}