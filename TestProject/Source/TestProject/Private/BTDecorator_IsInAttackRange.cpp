// Fill out your copyright notice in the Description page of Project Settings.

#include "BTDecorator_IsInAttackRange.h"
#include "TPAIController.h"
#include "TPCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTDecorator_IsInAttackRange::UBTDecorator_IsInAttackRange()
{
	NodeName = TEXT("CanAttack");
}

bool UBTDecorator_IsInAttackRange::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	bool bResult = Super::CalculateRawConditionValue(OwnerComp, NodeMemory);

	//auto ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	auto ControllingPawn = Cast<ATPCharacter>(OwnerComp.GetAIOwner()->GetPawn()); //에러이유: 캐스트로 형변환안해줘서
	if (nullptr == ControllingPawn)
		return false;

	auto Target = Cast<ATPCharacter>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(ATPAIController::TargetKey));
	if (nullptr == Target)
		return false;

	//bResult = (Target->GetDistanceTo(ControllingPawn) <= 200.0f);
	bResult = (Target->GetDistanceTo(ControllingPawn) <= ControllingPawn->GetFinalAttackRange());
	return bResult;
}