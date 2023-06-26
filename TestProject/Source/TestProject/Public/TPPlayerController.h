// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../TestProject.h"
#include "GameFramework/PlayerController.h"
#include "TPPlayerController.generated.h"

/**
 *
 */
UCLASS()
class TESTPROJECT_API ATPPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ATPPlayerController();

	virtual void PostInitializeComponents() override;
	//virtual void Possess(APawn* aPawn) override; 4.22미만 코드
	virtual void OnPossess(APawn* aPawn) override;
	virtual void OnUnPossess() override;

	class UTPHUDWidget* GetHUDWidget() const;
	void NPCKill(class ATPCharacter* KilledNPC) const;
	void AddGameScore() const;
	void ChangeInputMode(bool bGameMode = true);
	void ShowResultUI();

protected:
	virtual void SetupInputComponent() override;
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = UI)
		TSubclassOf<class UTPHUDWidget> HUDWidgetClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = UI)
		TSubclassOf<class UTPGameplayWidget> MenuWidgetClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = UI)
		TSubclassOf<class UTPGameplayResultWidget> ResultWidgetClass;

private:
	void OnGamePause();

	UPROPERTY()
		class UTPHUDWidget* HUDWidget;

	UPROPERTY()
		class ATPPlayerState* TPPlayerState;

	UPROPERTY()
		class UTPGameplayWidget* MenuWidget;

	UPROPERTY()
		class UTPGameplayResultWidget* ResultWidget;

	FInputModeGameOnly GameInputMode;
	FInputModeUIOnly UIInputMode;

//// 언리얼 엔진 -> 플레이어 컨트롤 -> 폰  따라서 이렇게 구현하면 폰에 넘어가는것을 막을수 있음
//protected:
//	virtual void SetupInputComponent() override;
//
//private:
//	void LeftRight(float NewAxisValue);
	
};
