// Fill out your copyright notice in the Description page of Project Settings.


#include "TPGameMode.h"
//#include "TPPawn.h"
#include "TPCharacter.h"
#include "TPPlayerController.h"
#include "TPPlayerState.h"
#include "TPGameState.h"

ATPGameMode::ATPGameMode()
{
	DefaultPawnClass = ATPCharacter::StaticClass();
	PlayerControllerClass = ATPPlayerController::StaticClass();

	PlayerStateClass = ATPPlayerState::StaticClass();
	GameStateClass = ATPGameState::StaticClass();
	ScoreToClear = 2;
}

void ATPGameMode::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	TPGameState = Cast<ATPGameState>(GameState);
}


void ATPGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	auto TPPlayerState = Cast<ATPPlayerState>(NewPlayer->PlayerState);
	ABCHECK(nullptr != TPPlayerState);
	TPPlayerState->InitPlayerData();
}


void ATPGameMode::AddScore(ATPPlayerController* ScoredPlayer)
{
	for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; ++It)
	{
		const auto TPPlayerController = Cast<ATPPlayerController>(It->Get());
		if ((nullptr != TPPlayerController) && (ScoredPlayer == TPPlayerController))
		{
			TPPlayerController->AddGameScore();
			break;
		}
	}

	TPGameState->AddGameScore();

	if (GetScore() >= ScoreToClear)
	{
		TPGameState->SetGameCleared();

		for (FConstPawnIterator It = GetWorld()->GetPawnIterator(); It; ++It)
		{
			(*It)->TurnOff();
		}

		for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; ++It)
		{
			const auto TPPlayerController = Cast<ATPPlayerController>(It->Get());
			if (nullptr != TPPlayerController)
			{
				TPPlayerController->ShowResultUI();
			}
		}
	}
}

int32 ATPGameMode::GetScore() const
{
	return TPGameState->GetTotalGameScore();
}


