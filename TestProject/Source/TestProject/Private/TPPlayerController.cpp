// Fill out your copyright notice in the Description page of Project Settings.


#include "TPPlayerController.h"
#include "TPHUDWidget.h"
#include "TPPlayerState.h"
#include "TPCharacter.h"
#include "TPGameplayWidget.h"
#include "TPGameplayResultWidget.h"
#include "TPGameState.h"

ATPPlayerController::ATPPlayerController()
{
	static ConstructorHelpers::FClassFinder<UTPHUDWidget>
		UI_HUD_C(TEXT("/Game/TestProject/UI/UI_HUD.UI_HUD_C"));
	if (UI_HUD_C.Succeeded())
	{
		HUDWidgetClass = UI_HUD_C.Class;
	}

	static ConstructorHelpers::FClassFinder<UTPGameplayWidget> 
		UI_MENU_C(TEXT("/Game/TestProject/UI/UI_Menu.UI_Menu_C"));
	if (UI_MENU_C.Succeeded())
	{
		MenuWidgetClass = UI_MENU_C.Class;
	}

	static ConstructorHelpers::FClassFinder<UTPGameplayResultWidget> 
		UI_RESULT_C(TEXT("/Game/TestProject/UI/UI_Result.UI_Result_C"));
	if (UI_RESULT_C.Succeeded())
	{
		ResultWidgetClass = UI_RESULT_C.Class;
	}
}

void ATPPlayerController::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	ABLOG_S(Warning);
}

void ATPPlayerController::OnPossess(APawn* aPawn)
{
	ABLOG_S(Warning);
	Super::OnPossess(aPawn); //상속받은게 잘못됬었네 
}
void ATPPlayerController::OnUnPossess()
{
	Super::OnUnPossess();
}
void ATPPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	InputComponent->BindAction(TEXT("GamePause"), EInputEvent::IE_Pressed, this, &ATPPlayerController::OnGamePause);
}

////화면 인터페이스를 책임지는데 UI를 패스할수 있음
void ATPPlayerController::BeginPlay()
{
	Super::BeginPlay();

	//FInputModeGameOnly InputMode;
	//SetInputMode(InputMode);

	ChangeInputMode(true);

	HUDWidget = CreateWidget<UTPHUDWidget>(this, HUDWidgetClass);
	ABCHECK(nullptr != HUDWidget);
	HUDWidget->AddToViewport(1);

	ResultWidget = CreateWidget<UTPGameplayResultWidget>(this, ResultWidgetClass);
	ABCHECK(nullptr != ResultWidget);

	TPPlayerState = Cast<ATPPlayerState>(PlayerState);
	ABCHECK(nullptr != TPPlayerState);
	HUDWidget->BindPlayerState(TPPlayerState);
	TPPlayerState->OnPlayerStateChanged.Broadcast();
}

UTPHUDWidget* ATPPlayerController::GetHUDWidget() const
{
	return HUDWidget;
}

void ATPPlayerController::NPCKill(ATPCharacter* KilledNPC) const
{
	TPPlayerState->AddExp(KilledNPC->GetExp());
}

void ATPPlayerController::AddGameScore() const
{
	TPPlayerState->AddGameScore();
}

void ATPPlayerController::ChangeInputMode(bool bGameMode)
{
	if (bGameMode)
	{
		SetInputMode(GameInputMode);
		bShowMouseCursor = false;
	}
	else
	{
		SetInputMode(UIInputMode);
		bShowMouseCursor = true;
	}
}

void ATPPlayerController::ShowResultUI()
{
	auto TPGameState = Cast<ATPGameState>(UGameplayStatics::GetGameState(this));
	ABCHECK(nullptr != TPGameState);
	ResultWidget->BindGameState(TPGameState);

	ResultWidget->AddToViewport();
	ChangeInputMode(false);
}

void ATPPlayerController::OnGamePause()
{
	MenuWidget = CreateWidget<UTPGameplayWidget>(this, MenuWidgetClass);
	ABCHECK(nullptr != MenuWidget);
	MenuWidget->AddToViewport(3);

	SetPause(true);
	ChangeInputMode(false);
}
//void ATPPlayerController::SetupInputComponent()
//{
//	Super::SetupInputComponent();
//	InputComponent->BindAxis(TEXT("LeftRight"), this, &ATPPlayerController::LeftRight);
//}
//void ATPPlayerController::LeftRight(float NewAxisValue)
//{
//	//DO Nothing...
//}