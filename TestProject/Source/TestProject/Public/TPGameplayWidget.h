// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../TestProject.h"
#include "Blueprint/UserWidget.h"
#include "TPGameplayWidget.generated.h"

/**
 * 
 */
UCLASS()
class TESTPROJECT_API UTPGameplayWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;

	UFUNCTION()
		void OnResumeClicked();

	UFUNCTION()
		void OnReturnToTitleClicked();

	UFUNCTION()
		void OnRetryGameClicked();

protected:
	UPROPERTY()
		class UButton* ResumeButton;

	UPROPERTY()
		class UButton* ReturnToTitleButton;

	UPROPERTY()
		class UButton* RetryGameButton;
};
