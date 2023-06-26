// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../TestProject.h"
#include "GameFramework/GameModeBase.h"
#include "TPGameMode.generated.h"

/**
 *
 */
UCLASS()
class TESTPROJECT_API ATPGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ATPGameMode();

	virtual void PostInitializeComponents() override;
	virtual void PostLogin(APlayerController* NewPlayer) override;
	void AddScore(class ATPPlayerController* ScoredPlayer);
	int32 GetScore() const;

private:
	UPROPERTY()
		class ATPGameState* TPGameState;

	UPROPERTY()
		int32 ScoreToClear;
};
