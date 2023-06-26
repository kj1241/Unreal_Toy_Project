// Fill out your copyright notice in the Description page of Project Settings.


#include "TPCharacterWidget.h"
#include "TPCharacterStateComponent.h"
#include "Components/ProgressBar.h"

void UTPCharacterWidget::BindCharacterState(UTPCharacterStateComponent* NewCharacterState)
{
	ABCHECK(nullptr != NewCharacterState);

	CurrentCharacterState = NewCharacterState;
	NewCharacterState->OnHPChanged.AddUObject(this, &UTPCharacterWidget::UpdateHPWidget);

	//NewCharacterState->OnHPChanged.AddLambda([this]()->void{
	//	if (CurrentCharacterState.IsValid())
	//	{
	//		ABLOG(Warning, TEXT("HPRatio:%f"), CurrentCharacterState->GetHPRatio());
	//	}
	//});
}

void UTPCharacterWidget::NativeConstruct()
{
	Super::NativeConstruct();
	HPProgressBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("PB_HPBar")));
	ABCHECK(nullptr != HPProgressBar);
	UpdateHPWidget();
}

void UTPCharacterWidget::UpdateHPWidget()
{
	if (CurrentCharacterState.IsValid())
	{
		if (nullptr != HPProgressBar)
		{
			HPProgressBar->SetPercent(CurrentCharacterState->GetHPRatio());
		}
	}
}
