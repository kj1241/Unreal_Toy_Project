// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../TestProject.h"
#include "Engine/DataTable.h"
#include "Engine/GameInstance.h"
#include "Engine/StreamableManager.h"
#include "TPGameInstance.generated.h"

USTRUCT(BlueprintType)
struct FTPCharacterData : public FTableRowBase
{
	GENERATED_BODY()

public:
	FTPCharacterData() : Level(1), MaxHP(100.0f), Attack(10.0f), DropExp(10), NextExp(30) 
	{
	
	}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		int32 Level;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		float MaxHP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		float Attack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		int32 DropExp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		int32 NextExp;
};


/**
 * 
 */
UCLASS()
class TESTPROJECT_API UTPGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UTPGameInstance();

	virtual void Init() override;
	FTPCharacterData* GetTPCharacterData(int32 Level);

	FStreamableManager StreamableManager;

private:
	UPROPERTY()
		class UDataTable* TPCharacterTable;
	
};
