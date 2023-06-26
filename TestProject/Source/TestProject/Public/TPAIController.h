// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../TestProject.h"
#include "AIController.h"
#include "TPAIController.generated.h"

/**
 * 
 */
UCLASS()
class TESTPROJECT_API ATPAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	ATPAIController();
	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;

	static const FName HomePosKey;
	static const FName PatrolPosKey;
	static const FName TargetKey;

	void RunAI();
	void StopAI();

private:
//	void OnRepeatTimer();
//
//	FTimerHandle RepeatTimerHandle;
//	float RepeatInterval;

	UPROPERTY()
		class UBehaviorTree* BTAsset;

	UPROPERTY()
		class UBlackboardData* BBAsset;
};
