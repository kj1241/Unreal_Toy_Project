// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../TestProject.h"
#include "GameFramework/PlayerController.h"
#include "TPUIPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class TESTPROJECT_API ATPUIPlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = UI)
	TSubclassOf<class UUserWidget> UIWidgetClass;

	UPROPERTY()
		class UUserWidget* UIWidgetInstance;
};