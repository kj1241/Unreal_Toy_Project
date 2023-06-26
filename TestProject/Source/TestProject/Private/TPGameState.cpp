// Fill out your copyright notice in the Description page of Project Settings.

#include "TPGameState.h"

ATPGameState::ATPGameState()
{
	TotalGameScore = 0;
	bGameCleared = false;
}

int32 ATPGameState::GetTotalGameScore() const
{
	return TotalGameScore;
}

void ATPGameState::AddGameScore()
{
	TotalGameScore++;
}

void ATPGameState::SetGameCleared()
{
	bGameCleared = true;
}

bool ATPGameState::IsGameCleared() const
{
	return bGameCleared;
}
