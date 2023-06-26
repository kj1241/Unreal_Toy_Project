// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../TestProject.h"
#include "Blueprint/UserWidget.h"
#include "TPCharacterWidget.generated.h"

/**
 * 
 */
UCLASS()
class TESTPROJECT_API UTPCharacterWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void BindCharacterState(class UTPCharacterStateComponent* NewCharacterState);

protected:
	virtual void NativeConstruct() override;
	void UpdateHPWidget();

private:
	TWeakObjectPtr<class UTPCharacterStateComponent> CurrentCharacterState;

	UPROPERTY()
		class UProgressBar* HPProgressBar;
};
