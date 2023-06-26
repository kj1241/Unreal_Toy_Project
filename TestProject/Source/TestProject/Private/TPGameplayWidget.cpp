// Fill out your copyright notice in the Description page of Project Settings.

#include "TPGameplayWidget.h"
#include "Components/Button.h"
#include "TPPlayerController.h"

void UTPGameplayWidget::NativeConstruct()
{
	Super::NativeConstruct();

	ResumeButton = Cast<UButton>(GetWidgetFromName(TEXT("btnResume")));
	if (nullptr != ResumeButton)
	{
		ResumeButton->OnClicked.AddDynamic(this, &UTPGameplayWidget::OnResumeClicked);
	}

	ReturnToTitleButton = Cast<UButton>(GetWidgetFromName(TEXT("btnReturnToTitle")));
	if (nullptr != ReturnToTitleButton)
	{
		ReturnToTitleButton->OnClicked.AddDynamic(this, &UTPGameplayWidget::OnReturnToTitleClicked);
	}

	RetryGameButton = Cast<UButton>(GetWidgetFromName(TEXT("btnRetryGame")));
	if (nullptr != RetryGameButton)
	{
		RetryGameButton->OnClicked.AddDynamic(this, &UTPGameplayWidget::OnRetryGameClicked);
	}
}

void UTPGameplayWidget::OnResumeClicked()
{
	auto TPPlayerController = Cast<ATPPlayerController>(GetOwningPlayer());
	ABCHECK(nullptr != TPPlayerController);

	RemoveFromParent();
	TPPlayerController->ChangeInputMode(true);
	TPPlayerController->SetPause(false);
}

void UTPGameplayWidget::OnReturnToTitleClicked()
{
	UGameplayStatics::OpenLevel(GetWorld(), TEXT("Title"));
}

void UTPGameplayWidget::OnRetryGameClicked()
{
	auto TPPlayerController = Cast<ATPPlayerController>(GetOwningPlayer());
	ABCHECK(nullptr != TPPlayerController);
	TPPlayerController->RestartLevel();
}

