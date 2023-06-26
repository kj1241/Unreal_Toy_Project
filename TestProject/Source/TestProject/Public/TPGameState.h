// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../TestProject.h"
#include "GameFramework/GameStateBase.h"
#include "TPGameState.generated.h"

/**
 * 
 */
UCLASS()
class TESTPROJECT_API ATPGameState : public AGameStateBase
{
	GENERATED_BODY()
	
public:
	ATPGameState();

public:
	int32 GetTotalGameScore() const;
	void AddGameScore();
	void SetGameCleared();
	bool IsGameCleared() const;

private:
	UPROPERTY(Transient)
		int32 TotalGameScore;

	UPROPERTY(Transient)
		bool bGameCleared;
};
