// Fill out your copyright notice in the Description page of Project Settings.

#include "TPCharacterSelectWidget.h"
#include "TPCharacterSetting.h"
#include "TPGameInstance.h"
#include "EngineUtils.h"
#include "Animation/SkeletalMeshActor.h"
#include "Components/Button.h"
#include "Components/EditableTextBox.h"
#include "TPSaveGame.h"
#include "TPPlayerState.h"

void UTPCharacterSelectWidget::NextCharacter(bool bForward)
{
	bForward ? CurrentIndex++ : CurrentIndex--;

	if (CurrentIndex == -1) CurrentIndex = MaxIndex - 1;
	if (CurrentIndex == MaxIndex) CurrentIndex = 0;

	auto CharacterSetting = GetDefault<UTPCharacterSetting>();
	auto AssetRef = CharacterSetting->CharacterAssets[CurrentIndex];

	auto TPGameInstance = GetWorld()->GetGameInstance<UTPGameInstance>();
	ABCHECK(nullptr != TPGameInstance);
	ABCHECK(TargetComponent.IsValid());

	USkeletalMesh* Asset = TPGameInstance->StreamableManager.LoadSynchronous<USkeletalMesh>(AssetRef);
	if (nullptr != Asset)
	{
		TargetComponent->SetSkeletalMesh(Asset);
	}
}

void UTPCharacterSelectWidget::NativeConstruct()
{
	Super::NativeConstruct();

	CurrentIndex = 0;
	auto CharacterSetting = GetDefault<UTPCharacterSetting>();
	MaxIndex = CharacterSetting->CharacterAssets.Num();

	for (TActorIterator<ASkeletalMeshActor> It(GetWorld()); It; ++It)
	{
		TargetComponent = It->GetSkeletalMeshComponent();
		break;
	}

	PrevButton = Cast<UButton>(GetWidgetFromName(TEXT("btnPrev")));
	ABCHECK(nullptr != PrevButton);

	NextButton = Cast<UButton>(GetWidgetFromName(TEXT("btnNext")));
	ABCHECK(nullptr != NextButton);

	TextBox = Cast<UEditableTextBox>(GetWidgetFromName(TEXT("edtPlayerName")));
	ABCHECK(nullptr != TextBox);

	ConfirmButton = Cast<UButton>(GetWidgetFromName(TEXT("btnConfirm")));
	ABCHECK(nullptr != ConfirmButton);

	PrevButton->OnClicked.AddDynamic(this, &UTPCharacterSelectWidget::OnPrevClicked);
	NextButton->OnClicked.AddDynamic(this, &UTPCharacterSelectWidget::OnNextClicked);
	ConfirmButton->OnClicked.AddDynamic(this, &UTPCharacterSelectWidget::OnConfirmClicked);
}

void UTPCharacterSelectWidget::OnPrevClicked()
{
	NextCharacter(false);
}

void UTPCharacterSelectWidget::OnNextClicked()
{
	NextCharacter(true);
}

void UTPCharacterSelectWidget::OnConfirmClicked()
{
	FString CharacterName = TextBox->GetText().ToString();
	if (CharacterName.Len() <= 0 || CharacterName.Len() > 10) 
		return;

	UTPSaveGame* NewPlayerData = NewObject<UTPSaveGame>();
	NewPlayerData->PlayerName = CharacterName;
	NewPlayerData->Level = 1;
	NewPlayerData->Exp = 0;
	NewPlayerData->HighScore = 0;
	NewPlayerData->CharacterIndex = CurrentIndex;

	auto TPPlayerState = GetDefault<ATPPlayerState>();
	if (UGameplayStatics::SaveGameToSlot(NewPlayerData, TPPlayerState->SaveSlotName, 0))
	{
		UGameplayStatics::OpenLevel(GetWorld(), TEXT("GamePlay"));
	}
	else
	{
		ABLOG(Error, TEXT("SaveGame Error!"));
	}
}

