// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../TestProject.h"
#include "Blueprint/UserWidget.h"
#include "TPHUDWidget.generated.h"

/**
 * 
 */
UCLASS()
class TESTPROJECT_API UTPHUDWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void BindCharacterState(class UTPCharacterStateComponent* CharacterState);
	void BindPlayerState(class ATPPlayerState* PlayerState);

protected:
	virtual void NativeConstruct() override;
	void UpdateCharacterState();
	void UpdatePlayerState();
	
private:
	TWeakObjectPtr<class UTPCharacterStateComponent> CurrentCharacterState;
	TWeakObjectPtr<class ATPPlayerState> CurrentPlayerState;

	UPROPERTY()
		class UProgressBar* HPBar;

	UPROPERTY()
		class UProgressBar* ExpBar;

	UPROPERTY()
		class UTextBlock* PlayerName;

	UPROPERTY()
		class UTextBlock* PlayerLevel;

	UPROPERTY()
		class UTextBlock* CurrentScore;

	UPROPERTY()
		class UTextBlock* HighScore;
};
