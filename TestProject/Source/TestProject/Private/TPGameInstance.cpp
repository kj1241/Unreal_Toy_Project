// Fill out your copyright notice in the Description page of Project Settings.

#include "TPGameInstance.h"

UTPGameInstance::UTPGameInstance()
{
    FString CharacterDataPath = TEXT("/Game/TestProject/GameData/TPCharacterData.TPCharacterData");
    static ConstructorHelpers::FObjectFinder<UDataTable> DT_ABCHARACTER(*CharacterDataPath);
    ABCHECK(DT_ABCHARACTER.Succeeded());
    TPCharacterTable = DT_ABCHARACTER.Object;
    ABCHECK(TPCharacterTable->GetRowMap().Num() > 0);
}

void UTPGameInstance::Init()
{
    Super::Init();
    //ABLOG(Warning, TEXT("DropExp of Level 20 ABCharacter : %d"), GetTPCharacterData(20)->DropExp);
}

FTPCharacterData* UTPGameInstance::GetTPCharacterData(int32 Level)
{
    return TPCharacterTable->FindRow<FTPCharacterData>(*FString::FromInt(Level), TEXT(""));
}