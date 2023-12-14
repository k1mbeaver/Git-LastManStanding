// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UW_GameMain.generated.h"

/**
 * 
 */
UCLASS()
class LASTMANSTANDING_API UUW_GameMain : public UUserWidget
{
	GENERATED_BODY()

public:
	TSharedPtr<class SWidget> GetChatInputTextObject();
	void AddChatMessage(const FString& Message);
	void SetPlayerMissionClear(int nMissionClear);
	void SetWinnerName(const FString& WinnerName);
	void VisibleGameover();
	void VisibleDeath();
	void HiddenGameReady();
	void InitServerUI(bool bServer);
	void SetCurrentPlayer(int nCurrentPlayer);
	void SetDefaultPlayer(int nDefaultPlayer);
	void StartEnabled(bool bCanStart);
	void SetReturnReady(bool bReturn);
private:
	UPROPERTY(Meta = (BindWidget))
		class UUW_Gameover* WB_GameOver;

	UPROPERTY(Meta = (BindWidget))
		class UUW_Chat* WB_Chat;

	UPROPERTY(Meta = (BindWidget))
		class UUW_Mission* WB_UserMission;

	UPROPERTY(Meta = (BindWidget))
		class UUW_Death* WB_Death;

	UPROPERTY(Meta = (BindWidget))
		class UUW_GameReady* WB_GameReady;

	UPROPERTY(Meta = (BindWidget))
		class UUW_ReturnReady* WB_ReturnReady;
};
