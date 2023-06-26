// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../TestProject.h"
#include "TPGameplayWidget.h"
#include "TPGameplayResultWidget.generated.h"

/**
 * 
 */
UCLASS()
class TESTPROJECT_API UTPGameplayResultWidget : public UTPGameplayWidget
{
	GENERATED_BODY()
	
public:
	void BindGameState(class ATPGameState* GameState);

protected:
	virtual void NativeConstruct() override;

private:
	TWeakObjectPtr<class ATPGameState> CurrentGameState;
};
